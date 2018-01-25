// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <Windows.h>
#include <string>

namespace util
{
    typedef BOOL(WINAPI *LPFN_GLPI)(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, PDWORD);

    typedef struct tagLogicalProcessorInformation
    {
        DWORD logicalProcessorCount = 0;
        DWORD numaNodeCount = 0;
        DWORD processorCoreCount = 0;
        DWORD processorL1CacheCount = 0;
        DWORD processorL2CacheCount = 0;
        DWORD processorL3CacheCount = 0;
        DWORD processorPackageCount = 0;
    } LogicalProcessorInformation;

    int GetLogicalProcessorInformation(LogicalProcessorInformation* info);

    void ShutdownWindows();

    void LaunchAndWait(const std::wstring& file, const std::wstring& params, BOOL bWait);

    void SetComboBoxHeight(HWND hDlg, int nComboBoxID, int nSizeLimit);

    std::wstring CombinePath(const std::wstring& szPath, const std::wstring& szFile);

    std::wstring GetFileName(const std::wstring& szFilePath);

    std::wstring GetFilePath(const std::wstring& szFilePath);

    std::wstring GetFileExtension(const std::wstring& szFilePath);

    std::wstring GetOnlyFileName(const std::wstring& szFilePath);

    ULONGLONG GetFileSize64(HANDLE hFile);

    ULONGLONG GetFileSize64(const std::wstring& szFileName);

    __int64 GetFileSizeInt64(FILE *fp);

    std::wstring GetExeFilePath();

    std::wstring GetSettingsFilePath(const std::wstring& szFileName, const std::wstring& szConfigDirectory);

    std::wstring GetFullPathName(const std::wstring& szFilePath);

    BOOL DirectoryExists(const std::wstring& szPath);

    bool MakeFullPath(const std::wstring& szTargetPath);

    bool FileExists(const std::wstring& szPath);

    std::wstring GenerateUuidString();

    void ConvertAnsiToUnicode(const char *szAnsi, wchar_t *szUnicode, ULONG nLength);

    void ConvertUnicodeToAnsi(const wchar_t *szUnicode, char *szAnsi, ULONG nLength);

    PTCHAR* MyCommandLineToArgv(PTCHAR pszCmdLine, int *pnArgc);

    bool Unzip2Folder(BSTR lpZipFile, BSTR lpFolder);
}
