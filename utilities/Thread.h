#pragma once

#include <functional>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace util
{
    typedef struct
    {
        std::function<int(void *param)> fEntry;
        void *param;
    } Params;

    inline DWORD WINAPI ThreadStartRoutine(LPVOID lpParam)
    {
        Params *pParams = (Params *)lpParam;
        return (DWORD)pParams->fEntry(pParams->param);
    }

    class CThread
    {
        DWORD dwThreadID = 0L;
        HANDLE hThread = nullptr;
        Params params;
    public:
        bool Start(std::function<void()> fEntry, bool bSuspended = false)
        {
            return this->Start(
                [fEntry](void *param)->int
            {
                fEntry();
                return TRUE;
            });
        }
        bool Start(std::function<int(void *param)> fEntry, void *param = nullptr, bool bSuspended = false)
        {
            params.fEntry = fEntry;
            params.param = param;
            hThread = ::CreateThread(
                nullptr,
                0,
                (LPTHREAD_START_ROUTINE)ThreadStartRoutine,
                (LPVOID)&params,
                bSuspended == true ? CREATE_SUSPENDED : 0,
                &dwThreadID);
            if (hThread == nullptr)
                return false;
            return true;
        }
        bool Wait()
        {
            DWORD dwRet = ::WaitForSingleObject(hThread, INFINITE);
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
            DWORD dwRet = ::WaitForSingleObject(hThread, (DWORD)milliseconds);
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
        bool Resume()
        {
            return ::ResumeThread(hThread) != (DWORD)-1;
        }
        bool Pause()
        {
            return ::SuspendThread(hThread) != (DWORD)-1;
        }
        bool Terminate(int code = 0)
        {
            #pragma warning(push)
            #pragma warning(disable:6258)
            return ::TerminateThread(hThread, (DWORD)code) == TRUE;
            #pragma warning(pop)
        }
        bool Close()
        {
            return ::CloseHandle(hThread) == TRUE;
        }
    };
}
