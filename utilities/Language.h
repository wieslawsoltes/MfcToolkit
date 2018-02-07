// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <string>
#include "MapT.h"

namespace lang
{
    class CLanguage
    {
    public:
        std::wstring szId;
        std::wstring szOriginalName;
        std::wstring szTranslatedName;
        util::CMapT<int,std::wstring> m_Strings;
    };
}
