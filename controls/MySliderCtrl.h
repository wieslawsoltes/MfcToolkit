﻿#pragma once

namespace controls
{
    class CMySliderCtrl : public CSliderCtrl
    {
    public:
        CMySliderCtrl();
        virtual ~CMySliderCtrl();
    protected:
        virtual void PreSubclassWindow();
    protected:
        DECLARE_MESSAGE_MAP()
    protected:
        afx_msg BOOL OnToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
    public:
        virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
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
