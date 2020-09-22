#pragma once

namespace controls
{
    class CMyDialogEx : public CDialog
    {
    private:
        BOOL m_bUseMaxTrack, m_bUseMinTrack, m_bUseMaxRect;
        BOOL m_bInitDone;
        POINT m_ptMinTrackSize, m_ptMaxTrackSize;
        POINT m_ptMaxPos, m_ptMaxSize;
    private:
        void InitVars();
    protected:
        virtual BOOL OnInitDialog();
    protected:
        afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR *lpMMI);
        afx_msg void OnSize(UINT nType, int cx, int cy);
    protected:
        DECLARE_MESSAGE_MAP()
    public:
        CMyDialogEx();
        CMyDialogEx(UINT nIDTemplate, CWnd *pParentWnd = nullptr);
        CMyDialogEx(LPCTSTR lpszTemplateName, CWnd *pParentWnd = nullptr);
        virtual ~CMyDialogEx();
    public:
        void SetMaximizedRect(const CRect &rc);
        void ResetMaximizedRect();
        void SetMinTrackSize(const CSize &size);
        void ResetMinTrackSize();
        void SetMaxTrackSize(const CSize &size);
        void ResetMaxTrackSize();
        void UpdateWindowPos(HWND hWnd, CRect newRC);
        CString GetWindowRectStr();
        void SetWindowRectStr(CString szData);
    };
}
