#pragma once

#include <string>
#include <vector>
#include <tchar.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace util
{
    class CProcess
    {
        PROCESS_INFORMATION pInfo;
        STARTUPINFO sInfo;
    public:
        CProcess()
        {
            ZeroMemory(&this->pInfo, sizeof(this->pInfo));
            ZeroMemory(&this->sInfo, sizeof(this->sInfo));
            this->sInfo.cb = sizeof(this->sInfo);
            this->sInfo.dwFlags = STARTF_USESTDHANDLES;
        }
        virtual ~CProcess()
        {
        }
    public:
        void ConnectStdInput(HANDLE hPipeStdin)
        {
            this->sInfo.hStdInput = hPipeStdin;
        }
        void ConnectStdOutput(HANDLE hPipeStdout)
        {
            this->sInfo.hStdOutput = hPipeStdout;
        }
        void ConnectStdError(HANDLE hPipeStderr)
        {
            this->sInfo.hStdError = hPipeStderr;
        }
    public:
        bool Start(const std::wstring& szCommandLine, bool bNoWindow)
        {
            std::vector<wchar_t> convert(szCommandLine.begin(), szCommandLine.end());
            convert.push_back(0);
            LPTSTR lpCommandLine = convert.data();
            DWORD dwCreationFlags = NORMAL_PRIORITY_CLASS;
            if (bNoWindow == true)
                dwCreationFlags |= CREATE_NO_WINDOW;
            #pragma warning(push)
            #pragma warning(disable:6335)
            BOOL bResult = ::CreateProcess(nullptr,
                lpCommandLine,
                nullptr,
                nullptr,
                TRUE,
                dwCreationFlags,
                nullptr,
                nullptr,
                &this->sInfo,
                &this->pInfo);
            #pragma warning(pop)
            return bResult == TRUE;
        }
        bool Wait()
        {
            DWORD dwRet = ::WaitForSingleObject(this->pInfo.hProcess, INFINITE);
            switch (dwRet)
            {
            case WAIT_FAILED:
                return false;
                break;
            case WAIT_ABANDONED:
                break;
            case WAIT_OBJECT_0:
                break;
            case WAIT_TIMEOUT:
                return false;
                break;
            };
            return true;
        }
        bool Wait(int milliseconds)
        {
            DWORD dwRet = ::WaitForSingleObject(this->pInfo.hProcess, (DWORD)milliseconds);
            switch (dwRet)
            {
            case WAIT_FAILED:
                return false;
                break;
            case WAIT_ABANDONED:
                break;
            case WAIT_OBJECT_0:
                break;
            case WAIT_TIMEOUT:
                return false;
                break;
            };
            return true;

        }
        bool Terminate(int code = 0)
        {
            return ::TerminateProcess(this->pInfo.hProcess, (DWORD)code) == TRUE;
        }
        bool Close()
        {
            BOOL bCloseProcess = ::CloseHandle(this->pInfo.hProcess);
            BOOL bCloseThread = ::CloseHandle(this->pInfo.hThread);
            return (bCloseProcess == TRUE) && (bCloseThread == TRUE);
        }
        bool Stop(bool bWait, int nExitCodeSucess)
        {
            bool bResult = false;
            if (bWait == true)
            {
                if (this->Wait() == false)
                {
                    this->Terminate();
                    DWORD dwExitCode;
                    ::GetExitCodeProcess(this->pInfo.hProcess, &dwExitCode);
                    bResult = false;
                }
                else
                {
                    DWORD dwExitCode;
                    ::GetExitCodeProcess(this->pInfo.hProcess, &dwExitCode);
                    bResult = (DWORD)nExitCodeSucess == dwExitCode;
                }
            }
            else
            {
                this->Terminate();
                this->Wait(5000);
                DWORD dwExitCode;
                ::GetExitCodeProcess(this->pInfo.hProcess, &dwExitCode);
                bResult = false;
            }
            this->Close();
            return bResult;
        }
    };
}
