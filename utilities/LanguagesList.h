// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <string>
#include "ListT.h"
#include "StringHelper.h"
#include "Language.h"

namespace lang
{
    class CLanguagesList : public util::CListT<CLanguage>
    {
    public:
        int GetLanguageById(const std::wstring& szLanguageId)
        {
            int nCount = this->Count();
            for (int i = 0; i < nCount; i++)
            {
                CLanguage& language = this->Get(i);
                if (util::StringHelper::CompareNoCase(szLanguageId, language.szId))
                    return i;
            }
            return -1;
        }
    };
}
