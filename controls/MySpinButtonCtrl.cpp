// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "StdAfx.h"
#include "MySpinButtonCtrl.h"

namespace controls
{
    IMPLEMENT_DYNAMIC(CMySpinButtonCtrl, CSpinButtonCtrl)
    CMySpinButtonCtrl::CMySpinButtonCtrl()
    {
    }

    CMySpinButtonCtrl::~CMySpinButtonCtrl()
    {
    }

    BEGIN_MESSAGE_MAP(CMySpinButtonCtrl, CSpinButtonCtrl)
    END_MESSAGE_MAP()
}
