// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

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
        CLanguageContext() : pLanguage(nullptr)
        {
        }
        CLanguageContext(const CLanguageContext &other)
        {
            Copy(other);
        }
        CLanguageContext& operator=(const CLanguageContext &other)
        {
            Copy(other);
            return *this;
        }
        virtual ~CLanguageContext()
        {
        }
    public:
        void Copy(const CLanguageContext &other)
        {
            this->m_Languages = other.m_Languages;
            this->pLanguage = nullptr;
        }
    public:
        bool LookupString(const int nKey, CString& rValue)
        {
            if (this->pLanguage != nullptr)
            {
                if (this->pLanguage->m_Strings.TryGet(nKey, rValue) == TRUE)
                    return true;
            }
            return false;
        }
    public:
        CString GetString(int nKey, const TCHAR* szDefault)
        {
            CString rValue;
            if (this->LookupString(nKey, rValue))
                return rValue;
            return szDefault;
        }
    };
}
