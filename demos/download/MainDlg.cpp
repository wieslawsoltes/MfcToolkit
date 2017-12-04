// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "stdafx.h"
#include "MainApp.h"
#include "MainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
    : CDialog(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_UrlEdit);
    DDX_Control(pDX, IDC_EDIT2, m_PathEdit);
    DDX_Control(pDX, IDC_PROGRESS1, m_ProgressCtrl);
    DDX_Control(pDX, IDC_BUTTON1, m_DownloadButton);
    DDX_Control(pDX, IDC_EDIT3, m_EdtStatus);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CMainDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

BOOL CMainDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    m_UrlEdit.SetWindowText(_T(""));
    m_PathEdit.SetWindowText(_T(""));

    m_ProgressCtrl.SetRange32(0, 100);

    return TRUE;
}

void CMainDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

HCURSOR CMainDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

//int DownloadThread(void *param)
//{
//    CMainDlg* pMainDlg = (CMainDlg*)param;
//    if (pMainDlg == NULL)
//        return FALSE;
//    pMainDlg->Download();
//    return pMainDlg->m_Worker.Close();
//}

void CMainDlg::OnBnClickedButton1()
{
    m_ProgressCtrl.SetPos(0);
    m_EdtStatus.SetWindowText(_T(""));
    m_Worker.Start(
        [](void *param)->int 
        {
            CMainDlg* pMainDlg = (CMainDlg*)param;
            pMainDlg->Download();
            return pMainDlg->m_Worker.Close();
        },
        this, false);
    //m_Worker.Start(DownloadThread, this, false);
}

void CMainDlg::Download()
{
    CString szUrl;
    CString szPath;
    m_UrlEdit.GetWindowText(szUrl);
    m_PathEdit.GetWindowText(szPath);
    m_Download.Download(szUrl, szPath, 
        [this](int nProgress, CString szStatus)
        {
            this->m_ProgressCtrl.SetPos(nProgress);
            m_EdtStatus.SetWindowText(szStatus);
        });
}
