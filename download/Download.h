// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <afxstr.h>
#include <afxcmn.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

class CDownloadCallback : public IBindStatusCallback
{
public:
    CDownloadCallback() : m_LastPercent(0)
    {
    }
    virtual ~CDownloadCallback()
    {
    }
public:
    int m_LastPercent;
    CProgressCtrl *pProgressCtrl;
public:
    HRESULT STDMETHODCALLTYPE OnStartBinding(DWORD dwReserved, __RPC__in_opt IBinding *pib)
    {
        return E_NOTIMPL;
    }
    HRESULT STDMETHODCALLTYPE GetPriority(__RPC__out LONG *pnPriority)
    {
        return E_NOTIMPL;
    }
    HRESULT STDMETHODCALLTYPE OnLowResource(DWORD reserved)
    {
        return E_NOTIMPL;
    }
    HRESULT STDMETHODCALLTYPE OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, __RPC__in_opt LPCWSTR szStatusText)
    {
        switch (ulStatusCode)
        {
        case BINDSTATUS_FINDINGRESOURCE:
            OutputDebugString(_T("Finding resource...\r\n"));
            break;
        case BINDSTATUS_CONNECTING:
            OutputDebugString(_T("Connecting...\r\n"));
            break;
        case BINDSTATUS_SENDINGREQUEST:
            OutputDebugString(_T("Sending request...\r\n"));
            break;
        case BINDSTATUS_MIMETYPEAVAILABLE:
            OutputDebugString(_T("Mime type available\r\n"));
            break;
        case BINDSTATUS_CACHEFILENAMEAVAILABLE:
            OutputDebugString(_T("Cache filename available\r\n"));
            break;
        case BINDSTATUS_BEGINDOWNLOADDATA:
            OutputDebugString(_T("Begin download\r\n"));
            if (pProgressCtrl != NULL)
            {
                pProgressCtrl->SetPos(0);
            }
            break;
        case BINDSTATUS_DOWNLOADINGDATA:
        case BINDSTATUS_ENDDOWNLOADDATA:
        {
            int percent = (int)(100.0 * static_cast<double>(ulProgress) / static_cast<double>(ulProgressMax));
            if (m_LastPercent < percent)
            {
                if (pProgressCtrl != NULL)
                {
                    pProgressCtrl->SetPos(percent);
                }
                m_LastPercent = percent;

                CString szOutput;
                szOutput.Format(_T("%d%%\r\n"), percent);
                OutputDebugString(szOutput);
            }

            if (ulStatusCode == BINDSTATUS_ENDDOWNLOADDATA)
            {
                OutputDebugString(_T("End download\r\n"));
            }
        }
        break;
        default:
        {
            CString szOutput;
            szOutput.Format(_T("Status code : %d\r\n"), ulStatusCode);
            OutputDebugString(szOutput);
        }
        }
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnStopBinding(HRESULT hresult, __RPC__in_opt LPCWSTR szError)
    {
        return E_NOTIMPL;
    }
    HRESULT STDMETHODCALLTYPE GetBindInfo(DWORD *grfBINDF, BINDINFO *pbindinfo)
    {
        return E_NOTIMPL;
    }
    HRESULT STDMETHODCALLTYPE OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC *pformatetc, STGMEDIUM *pstgmed)
    {
        return E_NOTIMPL;
    }
    HRESULT STDMETHODCALLTYPE OnObjectAvailable(__RPC__in REFIID riid, __RPC__in_opt IUnknown *punk)
    {
        return E_NOTIMPL;
    }
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject)
    {
        if (IsEqualIID(IID_IBindStatusCallback, riid) || IsEqualIID(IID_IUnknown, riid))
        {
            *ppvObject = reinterpret_cast<void*>(this);
            return S_OK;
        }
        return E_NOINTERFACE;
    }
    ULONG STDMETHODCALLTYPE AddRef(void)
    {
        return 2UL;
    }
    ULONG STDMETHODCALLTYPE Release(void)
    {
        return 1UL;
    }
};

class CDownload
{
public:
    CDownload()
    {
    }
    virtual ~CDownload()
    {
    }
public:
    bool Download(CString szUrl, CString szPath, CProgressCtrl *pProgressCtrl = NULL)
    {
        CDownloadCallback m_Callback;
        m_Callback.pProgressCtrl = pProgressCtrl;

        IBindStatusCallback* pBindStatusCallback = NULL;
        m_Callback.QueryInterface(IID_IBindStatusCallback, reinterpret_cast<void**>(&pBindStatusCallback));

        HRESULT m_Result = URLDownloadToFile(NULL, CT2W(szUrl), CT2W(szPath), 0, pBindStatusCallback);
        if (SUCCEEDED(m_Result))
        {
            return true;
        }
        return false;
    }
};
