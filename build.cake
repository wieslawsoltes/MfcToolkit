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

var platforms = new [] { "Win32", "x64" }.ToList();
var configurations = new [] { "Release" }.ToList();
var tests = new [] { "MFC.Utilities.UnitTests" }.ToList();
var solution = "./MfcToolkit.sln";

///////////////////////////////////////////////////////////////////////////////
// TASKS
///////////////////////////////////////////////////////////////////////////////

Task("Clean")
    .Does(() =>
{
    CleanDirectories("./**/bin");
    CleanDirectories("./**/obj");
});

Task("Build")
    .IsDependentOn("Clean")
    .Does(() =>
{
    configurations.ForEach(configuration => 
    {
        platforms.ForEach(platform => 
        {
            Information("Building: {0}, {1} / {2}", solution, configuration, platform);
            MSBuild(solution, settings => {
                settings.SetConfiguration(configuration);
                settings.WithProperty("Platform", "\"" + platform + "\"");
                settings.SetVerbosity(Verbosity.Minimal); });
       });
    });
});

Task("Run-Unit-Tests")
    .IsDependentOn("Build")
    .Does(() =>
{
    configurations.ForEach(configuration => 
    {
        platforms.ForEach(platform => 
        {
            tests.ForEach(test => 
            {
                Information("Test: {0}, {1} / {2}", test, configuration, platform);
                var pattern = "./tests/" + test + "/bin/" + configuration + "/" + platform + "/" + test + ".dll";
                VSTest(pattern, new VSTestSettings() { 
                    PlatformArchitecture = (platform == "Win32" || platform == "x86") ? VSTestPlatform.x86 : VSTestPlatform.x64,
                    InIsolation = (platform == "Win32" || platform == "x86") ? false : true,
                    Logger = "AppVeyor" });
            });
        });
    });
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
