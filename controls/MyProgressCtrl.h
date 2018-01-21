// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
