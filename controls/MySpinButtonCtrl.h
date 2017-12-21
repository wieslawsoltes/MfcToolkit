// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

class CMySpinButtonCtrl : public CSpinButtonCtrl
{
    DECLARE_DYNAMIC(CMySpinButtonCtrl)
public:
    CMySpinButtonCtrl();
    virtual ~CMySpinButtonCtrl();
protected:
    DECLARE_MESSAGE_MAP()
};
