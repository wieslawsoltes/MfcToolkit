// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "afxcmn.h"
#include "afxwin.h"
#include "..\..\controls\MyButton.h"
#include "..\..\controls\MyEdit.h"
#include "..\..\controls\MyProgressCtrl.h"
#include "..\..\utilities\Download.h"
#include "..\..\utilities\Thread.h"

class CMainDlg : public CDialog
{
public:
    CMainDlg(CWnd* pParent = nullptr);
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif
protected:
    virtual void DoDataExchange(CDataExchange* pDX);
protected:
    HICON m_hIcon;
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
public:
    void Download();
public:
    controls::CMyEdit m_UrlEdit;
    controls::CMyEdit m_PathEdit;
    controls::CMyProgressCtrl m_ProgressCtrl;
    controls::CMyEdit m_EdtStatus;
    controls::CMyButton m_DownloadButton;
public:
    util::CDownload m_Download;
    util::CThread m_Worker;
};
