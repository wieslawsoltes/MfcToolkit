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
        virtual std::wstring GenerateUuidString() = 0;
        virtual std::wstring CombinePath(const std::wstring& szPath, const std::wstring& szFile) = 0;
        virtual std::wstring GetFileName(const std::wstring& szFilePath) = 0;
        virtual std::wstring GetFilePath(const std::wstring& szFilePath) = 0;
        virtual std::wstring FsGetFileExtension(const std::wstring& szFilePath) = 0;
        virtual std::wstring GetOnlyFileName(const std::wstring& szFilePath) = 0;
        virtual __int64 GetFileSize64(void* hFile) = 0;
        virtual __int64 GetFileSize64(const std::wstring& szFileName) = 0;
        virtual __int64 GetFileSizeInt64(FILE *fp) = 0;
        virtual std::wstring GetExeFilePath() = 0;
        virtual std::wstring GetSettingsFilePath(const std::wstring& szFileName, const std::wstring& szConfigDirectory) = 0;
        virtual std::wstring GetFullPathName_(const std::wstring& szFilePath) = 0;
        virtual bool FileExists(const std::wstring& szPath) = 0;
        virtual bool PathFileExists_(const std::wstring& szFilePath) = 0;
        virtual void DeleteFile_(const std::wstring& szFilePath) = 0;
        virtual bool CreateDirectory_(const std::wstring& szPath) = 0;
        virtual std::wstring GetCurrentDirectory_() = 0;
        virtual void SetCurrentDirectory_(const std::wstring& szPath) = 0;
        virtual bool DirectoryExists(const std::wstring& szPath) = 0;
        virtual bool MakeFullPath(const std::wstring& szTargetPath) = 0;
        virtual std::vector<std::wstring> FindFiles(const std::wstring& pattern) = 0;
        virtual bool FindFiles(const std::wstring path, std::vector<std::wstring>& files, const bool bRecurse = false) = 0;
    };
}
