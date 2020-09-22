#pragma once

namespace controls
{
    class CMySpinButtonCtrl : public CSpinButtonCtrl
    {
        DECLARE_DYNAMIC(CMySpinButtonCtrl)
    public:
        CMySpinButtonCtrl();
        virtual ~CMySpinButtonCtrl();
    protected:
        DECLARE_MESSAGE_MAP()
    };
}
