///////////////////////////////////////////////////////////////////////////////
// TOOLS
///////////////////////////////////////////////////////////////////////////////

#tool "nuget:?package=Microsoft.TestPlatform&version=15.9.0"

///////////////////////////////////////////////////////////////////////////////
// USINGS
///////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;

///////////////////////////////////////////////////////////////////////////////
// ARGUMENTS
///////////////////////////////////////////////////////////////////////////////

var target = Argument("target", "Default");

///////////////////////////////////////////////////////////////////////////////
// SETTINGS
///////////////////////////////////////////////////////////////////////////////

var platforms = new string[] { "Win32", "x64" }.ToList();
var configurations = new string[] { "Release" }.ToList();
var tests = new string[] { "Utilities.UnitTests" }.ToList();
var solution = "./MfcToolkit.sln";
var artifactsDir = (DirectoryPath)Directory("./artifacts");

///////////////////////////////////////////////////////////////////////////////
// SETUP
///////////////////////////////////////////////////////////////////////////////

Setup(context =>
{
    context.Log.Verbosity = Verbosity.Normal;
});

///////////////////////////////////////////////////////////////////////////////
// TEARDOWN
///////////////////////////////////////////////////////////////////////////////

Teardown(context =>
{
    Information("Finished running tasks.");
});

///////////////////////////////////////////////////////////////////////////////
// ACTIONS
///////////////////////////////////////////////////////////////////////////////

var buildSolutionAction = new Action<string,string,string> ((solution, configuration, platform) =>
{
    Information("Building: {0}, {1} / {2}", solution, configuration, platform);
    MSBuild(solution, settings => {
        settings.SetConfiguration(configuration);
        settings.WithProperty("Platform", "\"" + platform + "\"");
        settings.SetVerbosity(Verbosity.Minimal); });
});

var runTestAction = new Action<string,string,string> ((test, configuration, platform) =>
{
    Information("Test: {0}, {1} / {2}", test, configuration, platform);
    var logFileName = "VsTestResults-" + test + "-" + configuration + "-" + platform + ".xml";
    var resultsDirectory = artifactsDir.Combine("TestResults").FullPath;
    var pattern = "./tests/" + test + "/bin/" + configuration + "/" + platform + "/" + test + ".dll";
    VSTest(pattern, new VSTestSettings() {
        ToolPath = Context.Tools.Resolve("vstest.console.exe"),
        PlatformArchitecture = (platform == "Win32" || platform == "x86") ? VSTestPlatform.x86 : VSTestPlatform.x64,
        InIsolation = (platform == "Win32" || platform == "x86") ? false : true,
        ArgumentCustomization = arg => arg.Append("/logger:trx;LogFileName=" + logFileName + ",ResultsDirectory=" + resultsDirectory) });
});

///////////////////////////////////////////////////////////////////////////////
// TASKS
///////////////////////////////////////////////////////////////////////////////

Task("Clean")
    .Does(() =>
{
    CleanDirectory(artifactsDir);
    CleanDirectories("./**/bin/**");
    CleanDirectories("./**/obj/**");
});

Task("Build")
    .IsDependentOn("Clean")
    .Does(() =>
{
    configurations.ForEach(c => platforms.ForEach(p => buildSolutionAction(solution, c, p)));
});

Task("Run-Unit-Tests")
    .IsDependentOn("Build")
    .Does(() =>
{
    configurations.ForEach(c => platforms.ForEach(p => tests.ForEach(t => runTestAction(t, c, p))));
});

///////////////////////////////////////////////////////////////////////////////
// TARGETS
///////////////////////////////////////////////////////////////////////////////

Task("Default")
  .IsDependentOn("Run-Unit-Tests");

///////////////////////////////////////////////////////////////////////////////
// EXECUTE
///////////////////////////////////////////////////////////////////////////////

RunTarget(target);
