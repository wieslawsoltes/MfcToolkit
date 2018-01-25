// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <Rpc.h>
#include <Windows.h>
#include <CommCtrl.h>
#include <Shlwapi.h>
#include <ShlObj.h>
#include <string>
#include <tchar.h>
#include <cstringt.h>
#include "StringHelper.h"

namespace util
{
    class Utilities
    {
    public:
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
        static DWORD CountSetBits(ULONG_PTR bitMask)
        {
            DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
            DWORD bitSetCount = 0;
            ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
            DWORD i;

            for (i = 0; i <= LSHIFT; ++i)
            {
                bitSetCount += ((bitMask & bitTest) ? 1 : 0);
                bitTest /= 2;
            }

            return bitSetCount;
        }
        static int GetLogicalProcessorInformation(LogicalProcessorInformation* info)
        {
            LPFN_GLPI glpi;
            BOOL done = FALSE;
            PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = nullptr;
            PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = nullptr;
            DWORD returnLength = 0;
            DWORD byteOffset = 0;
            PCACHE_DESCRIPTOR Cache;

            glpi = (LPFN_GLPI)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "GetLogicalProcessorInformation");
            if (nullptr == glpi)
            {
#ifdef _DEBUG
                _tprintf(_T("\nGetLogicalProcessorInformation is not supported.\n"));
#endif
                return (1);
            }

            while (!done)
            {
                DWORD rc = glpi(buffer, &returnLength);
                if (FALSE == rc)
                {
                    if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
                    {
                        if (buffer)
                            free(buffer);

                        buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(returnLength);
                        if (nullptr == buffer)
                        {
#ifdef _DEBUG
                            _tprintf(_T("\nError: Allocation failure\n"));
#endif
                            return (2);
                        }
                    }
                    else
                    {
#ifdef _DEBUG
                        _tprintf(_T("\nError %d\n"), GetLastError());
#endif
                        return (3);
                    }
                }
                else
                {
                    done = TRUE;
                }
            }

            ptr = buffer;

            while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
            {
                switch (ptr->Relationship)
                {
                case RelationNumaNode:
                    // Non-NUMA systems report a single record of this type.
                    info->numaNodeCount++;
                    break;
                case RelationProcessorCore:
                    info->processorCoreCount++;
                    // A hyperthreaded core supplies more than one logical processor.
                    info->logicalProcessorCount += CountSetBits(ptr->ProcessorMask);
                    break;
                case RelationCache:
                    // Cache data is in ptr->Cache, one CACHE_DESCRIPTOR structure for each cache. 
                    Cache = &ptr->Cache;
                    if (Cache->Level == 1)
                    {
                        info->processorL1CacheCount++;
                    }
                    else if (Cache->Level == 2)
                    {
                        info->processorL2CacheCount++;
                    }
                    else if (Cache->Level == 3)
                    {
                        info->processorL3CacheCount++;
                    }
                    break;
                case RelationProcessorPackage:
                    // Logical processors share a physical package.
                    info->processorPackageCount++;
                    break;
                default:
#ifdef _DEBUG
                    _tprintf(_T("\nError: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.\n"));
#endif
                    break;
                }
                byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
                ptr++;
            }

#ifdef _DEBUG
            _tprintf(_T("\nGetLogicalProcessorInformation results:\n"));
            _tprintf(_T("Number of NUMA nodes: %d\n"), info->numaNodeCount);
            _tprintf(_T("Number of physical processor packages: %d\n"), info->processorPackageCount);
            _tprintf(_T("Number of processor cores: %d\n"), info->processorCoreCount);
            _tprintf(_T("Number of logical processors: %d\n"), info->logicalProcessorCount);
            _tprintf(_T("Number of processor L1/L2/L3 caches: %d/%d/%d\n"),
                info->processorL1CacheCount,
                info->processorL2CacheCount,
                info->processorL3CacheCount);
#endif

            free(buffer);
            return (0);
        }
    public:
        static void ShutdownWindows()
        {
            HANDLE m_hToken;
            if (::OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &m_hToken))
            {
                LUID m_Luid;
                if (::LookupPrivilegeValue(nullptr, _T("SeShutdownPrivilege"), &m_Luid))
                {
                    TOKEN_PRIVILEGES tp;
                    tp.PrivilegeCount = 1;
                    tp.Privileges[0].Luid = m_Luid;
                    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
                    ::AdjustTokenPrivileges(m_hToken, FALSE, &tp, 0, nullptr, nullptr);
                }
                ::CloseHandle(m_hToken);
            }
            ::ExitWindowsEx(EWX_SHUTDOWN | EWX_POWEROFF | EWX_FORCEIFHUNG, 0);
            ::PostQuitMessage(0);
        }
        static void LaunchAndWait(const std::wstring& file, const std::wstring& params, BOOL bWait)
        {
            SHELLEXECUTEINFO sei;
            ::ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));
            sei.cbSize = sizeof(SHELLEXECUTEINFO);
            sei.fMask = SEE_MASK_NOCLOSEPROCESS;
            // leave sei.lpVerb uninitialized for default action
            sei.nShow = SW_SHOWNORMAL;
            sei.lpFile = file.c_str();
            sei.lpParameters = params.c_str();
            ::ShellExecuteEx(&sei);
            if (bWait == TRUE)
                ::WaitForSingleObject(sei.hProcess, INFINITE);
            ::CloseHandle(sei.hProcess);
        }
    public:
        static void SetComboBoxHeight(HWND hDlg, int nComboBoxID, int nSizeLimit)
        {
            HWND hComboxBox = ::GetDlgItem(hDlg, nComboBoxID);
            if (hComboxBox != nullptr)
                ::SendMessage(hComboxBox, CB_SETMINVISIBLE, (WPARAM)nSizeLimit, 0);
        }
    public:
        static std::wstring CombinePath(const std::wstring& szPath, const std::wstring& szFile)
        {
            std::wstring szOutputFile = szFile;
            if (szPath.length() >= 1)
            {
                auto cLast = szPath[szPath.length() - 1];
                if ((cLast == '\\') || (cLast == '/'))
                    szOutputFile = szPath + szOutputFile;
                else
                    szOutputFile = szPath + L"\\" + szOutputFile;
            }
            return szOutputFile;
        }
        static std::wstring GetFileName(const std::wstring& szFilePath)
        {
            return ::PathFindFileName(szFilePath.c_str());
        }
        static std::wstring GetFilePath(const std::wstring& szFilePath)
        {
            std::wstring szFileName = GetFileName(szFilePath);
            return szFilePath.substr(0, szFilePath.length() - szFileName.length());
        }
        static std::wstring GetFileExtension(const std::wstring& szFilePath)
        {
            std::wstring szExt = ::PathFindExtension(szFilePath.c_str());
            size_t pos = szExt.find('.');
            if (pos != std::string::npos)
                return szExt.substr(pos + 1, szExt.length() - 1);
            return szExt;
        }
        static std::wstring GetOnlyFileName(const std::wstring& szFilePath)
        {
            std::wstring szFileName = GetFileName(szFilePath);
            std::wstring szExt = GetFileExtension(szFilePath);
            return szFileName.substr(0, szFileName.length() - szExt.length());
        }
        static ULONGLONG GetFileSize64(HANDLE hFile)
        {
            ULARGE_INTEGER liSize;
            liSize.LowPart = ::GetFileSize(hFile, &liSize.HighPart);
            if (liSize.LowPart == (DWORD)-1)
            {
                if (::GetLastError() != NO_ERROR)
                    return(0);
            }
            return liSize.QuadPart;
        }
        static ULONGLONG GetFileSize64(const std::wstring& szFileName)
        {
            WIN32_FIND_DATA FindFileData;
            HANDLE hFind;
            ULARGE_INTEGER ulSize;
            ULONGLONG nFileSize;

            hFind = ::FindFirstFile(szFileName.c_str(), &FindFileData);
            if (hFind == INVALID_HANDLE_VALUE)
                return 0;

            ::FindClose(hFind);

            ulSize.HighPart = FindFileData.nFileSizeHigh;
            ulSize.LowPart = FindFileData.nFileSizeLow;
            nFileSize = ulSize.QuadPart;

            return nFileSize;
        }
        static __int64 GetFileSizeInt64(FILE *fp)
        {
            __int64 nCurPos, nSize;
            nCurPos = _ftelli64(fp);
            _fseeki64(fp, 0, SEEK_END);
            nSize = _ftelli64(fp);
            _fseeki64(fp, nCurPos, SEEK_SET);
            return nSize;
        }
        static std::wstring GetExeFilePath()
        {
            TCHAR szExeFilePath[MAX_PATH + 1] = _T("");
            DWORD dwRet = ::GetModuleFileName(::GetModuleHandle(nullptr), szExeFilePath, MAX_PATH);
            if (dwRet > 0)
            {
                std::wstring szTempBuff1 = szExeFilePath;
                std::wstring szTempBuff2 = GetFileName(szTempBuff1);
                return szTempBuff1.substr(0, szTempBuff1.length() - szTempBuff2.length());
            }
            return nullptr;
        }
        static std::wstring GetSettingsFilePath(const std::wstring& szFileName, const std::wstring& szConfigDirectory)
        {
            TCHAR szPath[MAX_PATH];
            if (SUCCEEDED(SHGetFolderPath(nullptr,
                CSIDL_APPDATA | CSIDL_FLAG_CREATE,
                nullptr,
                0,
                szPath)))
            {
                PathAppend(szPath, szConfigDirectory.c_str());
                PathAppend(szPath, szFileName.c_str());
                return szPath;
            }
            return nullptr;
        }
        static std::wstring GetFullPathName(const std::wstring& szFilePath)
        {
            TCHAR szFullPath[MAX_PATH + 2] = _T("");
            LPTSTR pszFilePos = nullptr;
            ::GetFullPathName(szFilePath.c_str(), MAX_PATH + 1, szFullPath, &pszFilePos);
            return szFullPath;
        }
        static bool FileExists(const std::wstring& szPath)
        {
            WIN32_FIND_DATA w32FileData;
            ZeroMemory(&w32FileData, sizeof(WIN32_FIND_DATA));
            HANDLE hFind = ::FindFirstFile(szPath.c_str(), &w32FileData);
            bool bInvalidHandle = hFind == INVALID_HANDLE_VALUE;
            ::FindClose(hFind);
            return bInvalidHandle == false;
        }
    public:
        static BOOL DirectoryExists(const std::wstring& szPath)
        {
            if (_taccess_s(szPath.c_str(), 0) == 0)
            {
                struct _stat status;
                _tstat(szPath.c_str(), &status);
                return (status.st_mode & S_IFDIR) != 0;
            }
            return FALSE;
        }
        static bool MakeFullPath(const std::wstring& szTargetPath)
        {
            std::wstring szPath = szTargetPath;
            if (szPath[szPath.length() - 1] != '\\')
                szPath = szPath + L"\\";

            std::wstring szTmpDir = szPath.substr(0, 2);
            _tchdir(szTmpDir.c_str());

            int nStart = 3;
            int nEnd = 0;
            while (true)
            {
                nEnd = szPath.find('\\', nStart);
                if (nEnd == -1)
                    return true;

                std::wstring szNextDir = szPath.substr(nStart, nEnd - nStart);
                std::wstring szCurDir = szTmpDir + L"\\" + szNextDir;
                if (_tchdir(szCurDir.c_str()) != 0)
                {
                    _tchdir(szTmpDir.c_str());
                    if (_tmkdir(szNextDir.c_str()) != 0)
                        return false;
                }

                szTmpDir += L"\\" + szNextDir;
                nStart = nEnd + 1;
            }
            return false;
        }
    public:
        static std::wstring GenerateUuidString()
        {
            std::wstring strKey;
            UUID uuid;
            if (UuidCreate(&uuid) == RPC_S_OK)
            {
                RPC_WSTR szUuid;
                if (UuidToString(&uuid, &szUuid) == RPC_S_OK)
                {
                    strKey = (LPTSTR)szUuid;
                    strKey = StringHelper::ToUpper(strKey);
                    RpcStringFree(&szUuid);
                }
            }
            return strKey;
        }
    public:
        static void ConvertAnsiToUnicode(const char *szAnsi, wchar_t *szUnicode, ULONG nLength)
        {
            // use always + 1 to null-terminate string
            _mbstowcsz(szUnicode, szAnsi, nLength + 1);
        }
        static void ConvertUnicodeToAnsi(const wchar_t *szUnicode, char *szAnsi, ULONG nLength)
        {
            // use always + 1 to null-terminate string
            _wcstombsz(szAnsi, szUnicode, nLength + 1);
        }
    public:
        static PTCHAR* MyCommandLineToArgv(PTCHAR pszCmdLine, int *pnArgc)
        {
            BOOLEAN bHaveQuotationMark, bHaveText, bHaveSpace;
            ULONG nLength, nArgc, nI, nJ;
            PTCHAR *pszArgv;
            PTCHAR pszTmpArgv;
            TCHAR cNext;

            nLength = _tcslen(pszCmdLine);
            nI = ((nLength + 2) / 2) * sizeof(PVOID) + sizeof(PVOID);
            pszArgv = (PTCHAR *)GlobalAlloc(GMEM_FIXED, nI + (nLength + 2) * sizeof(TCHAR));
            pszTmpArgv = (PTCHAR)(((PUCHAR)pszArgv) + nI);
            nArgc = nI = nJ = 0;
            pszArgv[nArgc] = pszTmpArgv;
            bHaveQuotationMark = FALSE;
            bHaveText = FALSE;
            bHaveSpace = TRUE;

            while (cNext = pszCmdLine[nI])
            {
                if (bHaveQuotationMark)
                {
                    if (cNext == '\"')
                    {
                        bHaveQuotationMark = FALSE;
                    }
                    else
                    {
                        pszTmpArgv[nJ] = cNext;
                        nJ++;
                    }
                }
                else
                {
                    if (cNext == '\"')
                    {
                        bHaveQuotationMark = TRUE;
                        bHaveText = TRUE;

                        if (bHaveSpace)
                        {
                            pszArgv[nArgc] = pszTmpArgv + nJ;
                            nArgc++;
                        }

                        bHaveSpace = FALSE;
                    }
                    else if ((cNext == ' ') || (cNext == '\t') || (cNext == '\n') || (cNext == '\r'))
                    {
                        if (bHaveText)
                        {
                            pszTmpArgv[nJ] = '\0';
                            nJ++;
                        }

                        bHaveText = FALSE;
                        bHaveSpace = TRUE;
                    }
                    else
                    {
                        bHaveText = TRUE;

                        if (bHaveSpace)
                        {
                            pszArgv[nArgc] = pszTmpArgv + nJ;
                            nArgc++;
                        }

                        pszTmpArgv[nJ] = cNext;
                        nJ++;
                        bHaveSpace = FALSE;
                    }
                }

                nI++;
            }

            pszTmpArgv[nJ] = '\0';
            pszArgv[nArgc] = nullptr;
            (*pnArgc) = nArgc;

            return pszArgv;
        }
    public:
        static bool Unzip2Folder(BSTR lpZipFile, BSTR lpFolder)
        {
            IShellDispatch *pISD;
            Folder *pZippedFile = 0L;
            Folder *pDestination = 0L;
            long FilesCount = 0;
            IDispatch* pItem = 0L;
            FolderItems *pFilesInside = 0L;
            VARIANT Options, OutFolder, InZipFile, Item;
            CoInitialize(nullptr);

            __try
            {
                if (CoCreateInstance(CLSID_Shell, nullptr, CLSCTX_INPROC_SERVER, IID_IShellDispatch, (void **)&pISD) != S_OK)
                    return false;

                InZipFile.vt = VT_BSTR;
                InZipFile.bstrVal = lpZipFile;
                pISD->NameSpace(InZipFile, &pZippedFile);
                if (!pZippedFile)
                {
                    pISD->Release();
                    return false;
                }

                OutFolder.vt = VT_BSTR;
                OutFolder.bstrVal = lpFolder;
                pISD->NameSpace(OutFolder, &pDestination);
                if (!pDestination)
                {
                    pZippedFile->Release();
                    pISD->Release();
                    return false;
                }

                pZippedFile->Items(&pFilesInside);
                if (!pFilesInside)
                {
                    pDestination->Release();
                    pZippedFile->Release();
                    pISD->Release();
                    return false;
                }

                pFilesInside->get_Count(&FilesCount);
                if (FilesCount < 1)
                {
                    pFilesInside->Release();
                    pDestination->Release();
                    pZippedFile->Release();
                    pISD->Release();
                    return true;
                }

                pFilesInside->QueryInterface(IID_IDispatch, (void**)&pItem);

                Item.vt = VT_DISPATCH;
                Item.pdispVal = pItem;

                Options.vt = VT_I4;
                Options.lVal = 1024 | 512 | 16 | 4;

                bool retval = pDestination->CopyHere(Item, Options) == S_OK;

                pItem->Release(); pItem = 0L;
                pFilesInside->Release(); pFilesInside = 0L;
                pDestination->Release(); pDestination = 0L;
                pZippedFile->Release(); pZippedFile = 0L;
                pISD->Release(); pISD = 0L;

                return retval;
            }
            __finally
            {
                CoUninitialize();
            }
        }
    };
}
