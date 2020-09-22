#include "StdAfx.h"
#include "MyStatusBarCtrl.h"

namespace controls
{
    IMPLEMENT_DYNAMIC(CMyStatusBarCtrl, CStatusBarCtrl)
    CMyStatusBarCtrl::CMyStatusBarCtrl()
    {
    }

    CMyStatusBarCtrl::~CMyStatusBarCtrl()
    {
    }

    BEGIN_MESSAGE_MAP(CMyStatusBarCtrl, CStatusBarCtrl)
    END_MESSAGE_MAP()
}
