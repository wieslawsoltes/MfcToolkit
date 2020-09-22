#pragma once

namespace controls
{
    class CMyStatusBarCtrl : public CStatusBarCtrl
    {
        DECLARE_DYNAMIC(CMyStatusBarCtrl)
    public:
        CMyStatusBarCtrl();
        virtual ~CMyStatusBarCtrl();
    protected:
        DECLARE_MESSAGE_MAP()
    };
}
