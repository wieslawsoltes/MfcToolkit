﻿// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <afxstr.h>
#include "..\utilities\ListT.h"
#include "Language.h"

namespace lang
{
    class CLanguagesList : public util::CListT<CLanguage>
    {
    public:
        int GetLanguageById(CString szLanguageId)
        {
            int nCount = this->Count();
            for (int i = 0; i < nCount; i++)
            {
                CLanguage& language = this->Get(i);
                if (szLanguageId.CompareNoCase(language.szId) == 0)
                    return i;
            }
            return -1;
        }
    };
}
