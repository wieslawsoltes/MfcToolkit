// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <string>
#include "LanguagesList.h"
#include "Language.h"

namespace lang
{
    class CLanguageContext
    {
    public:
        CLanguagesList m_Languages;
        CLanguage* pLanguage;
    public:
        bool LookupString(const int nKey, std::wstring& rValue)
        {
            if (this->pLanguage != nullptr)
            {
                if (this->pLanguage->m_Strings.TryGet(nKey, rValue) == true)
                    return true;
            }
            return false;
        }
    public:
        std::wstring GetString(int nKey, const std::wstring& szDefault)
        {
            std::wstring rValue;
            if (this->LookupString(nKey, rValue))
                return rValue;
            return szDefault;
        }
    };
}
