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
        int nLangId;
    public:
        bool LookupString(const int nKey, std::wstring& rValue)
        {
            if (this->nLangId >= 0 && this->nLangId < this->m_Languages.Count())
            {
                auto& language = this->m_Languages.Get(this->nLangId);
                if (language.m_Strings.TryGet(nKey, rValue) == true)
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
