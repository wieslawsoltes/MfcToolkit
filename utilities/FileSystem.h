// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <string>
#include <vector>

namespace util
{
    class IFileSystem
    {
    public:
        virtual ~IFileSystem() {}
        virtual std::wstring FsGenerateUuidString() = 0;
        virtual std::wstring FsCombinePath(const std::wstring& szPath, const std::wstring& szFile) = 0;
        virtual std::wstring FsGetFileName(const std::wstring& szFilePath) = 0;
        virtual std::wstring FsGetFilePath(const std::wstring& szFilePath) = 0;
        virtual std::wstring FsGetFileExtension(const std::wstring& szFilePath) = 0;
        virtual std::wstring FsGetOnlyFileName(const std::wstring& szFilePath) = 0;
        virtual __int64 FsGetFileSize64(void* hFile) = 0;
        virtual __int64 FsGetFileSize64(const std::wstring& szFileName) = 0;
        virtual __int64 FsGetFileSizeInt64(FILE *fp) = 0;
        virtual std::wstring FsGetExeFilePath() = 0;
        virtual std::wstring FsGetSettingsFilePath(const std::wstring& szFileName, const std::wstring& szConfigDirectory) = 0;
        virtual std::wstring FsGetFullPathName(const std::wstring& szFilePath) = 0;
        virtual bool FsFileExists(const std::wstring& szPath) = 0;
        virtual bool FsPathFileExists(const std::wstring& szFilePath) = 0;
        virtual void FsDeleteFile(const std::wstring& szFilePath) = 0;
        virtual bool FsCreateDirectory(const std::wstring& szPath) = 0;
        virtual std::wstring FsGetCurrentDirectory() = 0;
        virtual void FsSetCurrentDirectory(const std::wstring& szPath) = 0;
        virtual bool FsDirectoryExists(const std::wstring& szPath) = 0;
        virtual bool FsMakeFullPath(const std::wstring& szTargetPath) = 0;
        virtual std::vector<std::wstring> FsFindFiles(const std::wstring& pattern) = 0;
        virtual bool FsFindFiles(const std::wstring path, std::vector<std::wstring>& files, const bool bRecurse = false) = 0;
    };
}
