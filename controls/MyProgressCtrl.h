#pragma once

namespace controls
{
    class CMyProgressCtrl : public CProgressCtrl
    {
        DECLARE_DYNAMIC(CMyProgressCtrl)
    public:
        CMyProgressCtrl();
        virtual ~CMyProgressCtrl();
    protected:
        DECLARE_MESSAGE_MAP()
    };
}
