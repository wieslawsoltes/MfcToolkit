// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "StdAfx.h"
#include "MyDialogEx.h"

CMyDialogEx::CMyDialogEx()
{
    InitVars();
}

CMyDialogEx::CMyDialogEx(UINT nIDTemplate, CWnd *pParentWnd)
    : CDialogEx(nIDTemplate, pParentWnd)
{
    InitVars();
}

CMyDialogEx::CMyDialogEx(LPCTSTR lpszTemplateName, CWnd *pParentWnd)
    : CDialogEx(lpszTemplateName, pParentWnd)
{
    InitVars();
}

CMyDialogEx::~CMyDialogEx()
{
}

BEGIN_MESSAGE_MAP(CMyDialogEx, CDialogEx)
    ON_WM_GETMINMAXINFO()
    ON_WM_SIZE()
END_MESSAGE_MAP()

void CMyDialogEx::InitVars()
{
    m_bInitDone = FALSE;
    m_bUseMinTrack = TRUE;
    m_bUseMaxTrack = FALSE;
    m_bUseMaxRect = FALSE;
}

BOOL CMyDialogEx::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    CRect rc;
    GetWindowRect(&rc);

    m_ptMinTrackSize.x = rc.Width();
    m_ptMinTrackSize.y = rc.Height();

    m_bInitDone = TRUE;

    return TRUE;
}

void CMyDialogEx::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if ((nType == SIZE_MAXHIDE) || (nType == SIZE_MAXSHOW))
        return;
}

void CMyDialogEx::OnGetMinMaxInfo(MINMAXINFO FAR *lpMMI)
{
    if (!m_bInitDone)
        return;

    if (m_bUseMinTrack)
        lpMMI->ptMinTrackSize = m_ptMinTrackSize;

    if (m_bUseMaxTrack)
        lpMMI->ptMaxTrackSize = m_ptMaxTrackSize;

    if (m_bUseMaxRect)
    {
        lpMMI->ptMaxPosition = m_ptMaxPos;
        lpMMI->ptMaxSize = m_ptMaxSize;
    }
}

void CMyDialogEx::SetMaximizedRect(const CRect& rc)
{
    m_bUseMaxRect = TRUE;
    m_ptMaxPos = rc.TopLeft();
    m_ptMaxSize.x = rc.Width();
    m_ptMaxSize.y = rc.Height();
}

void CMyDialogEx::ResetMaximizedRect()
{
    m_bUseMaxRect = FALSE;
}

void CMyDialogEx::SetMinTrackSize(const CSize &size)
{
    m_bUseMinTrack = TRUE;
    m_ptMinTrackSize.x = size.cx;
    m_ptMinTrackSize.y = size.cy;
}

void CMyDialogEx::ResetMinTrackSize()
{
    m_bUseMinTrack = FALSE;
}

void CMyDialogEx::SetMaxTrackSize(const CSize &size)
{
    m_bUseMaxTrack = TRUE;
    m_ptMaxTrackSize.x = size.cx;
    m_ptMaxTrackSize.y = size.cy;
}

void CMyDialogEx::ResetMaxTrackSize()
{
    m_bUseMaxTrack = FALSE;
}

void CMyDialogEx::UpdateWindowPos(HWND hWnd, CRect newRC)
{
    HDWP hDwp = BeginDeferWindowPos(1);

    DeferWindowPos(hDwp, hWnd,
        nullptr,
        newRC.left, newRC.top,
        newRC.Width(), newRC.Height(),
        SWP_NOZORDER | SWP_NOACTIVATE);

    EndDeferWindowPos(hDwp);
}

CString CMyDialogEx::GetWindowRectStr()
{
    CString szData;
    WINDOWPLACEMENT wp;

    ZeroMemory(&wp, sizeof(WINDOWPLACEMENT));
    wp.length = sizeof(WINDOWPLACEMENT);

    GetWindowPlacement(&wp);
    RECT &rc = wp.rcNormalPosition;

    szData.Format(_T("%d %d %d %d %d %d"),
        rc.left, rc.top,
        rc.right, rc.bottom,
        wp.showCmd, wp.flags);

    return szData;
}

void CMyDialogEx::SetWindowRectStr(CString szData)
{
    WINDOWPLACEMENT wp;

    if (szData.IsEmpty())
        return;

    ZeroMemory(&wp, sizeof(WINDOWPLACEMENT));
    wp.length = sizeof(WINDOWPLACEMENT);

    GetWindowPlacement(&wp);
    RECT &rc = wp.rcNormalPosition;

    if (_stscanf_s(szData, _T("%d %d %d %d %d %d"),
        &rc.left, &rc.top,
        &rc.right, &rc.bottom,
        &wp.showCmd, &wp.flags) == 6)
    {
        SetWindowPlacement(&wp);
    }
}
