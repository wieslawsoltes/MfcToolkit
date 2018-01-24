// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <string>
#include <string.h>
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
                if (_wcsicmp(szLanguageId.c_str(), language.szId).c_str()) == 0)
                    return i;
            }
            return -1;
        }
    };
}
