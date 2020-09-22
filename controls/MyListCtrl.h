#pragma once

#define WM_ITEMCHANGED (WM_USER + 0x20)

namespace controls
{
    class CMyListCtrl : public CListCtrl
    {
        DECLARE_DYNAMIC(CMyListCtrl)
    public:
        CMyListCtrl();
        virtual ~CMyListCtrl();
    protected:
        afx_msg void PreSubclassWindow();
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg BOOL OnToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
    protected:
        DECLARE_MESSAGE_MAP()
    public:
        afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        afx_msg void OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
    protected:
        virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO *pTI) const;
    private:
        CMyListCtrl(const CMyListCtrl &x);
    public:
        bool bUseTooltipsList; // use only for LVS_REPORT style
        CList<CString, CString&> listTooltips;
    private:
        CString szToolTipText;
        bool bHaveToolTipText;
    public:
        void SetTooltipText(CString szText);
        CString GetTooltipText();
        void DelTooltipText();
        bool HaveTooltipText();
    };
}
