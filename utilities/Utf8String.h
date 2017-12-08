// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <atlstr.h>
#include "UnicodeUtf8.h"

class CUtf8String
{
public:
    char *m_Result;
public:
    CUtf8String()
    {
        m_Result = nullptr;
    }
    CUtf8String(CString szText)
    {
        Convert(szText);
    }
    ~CUtf8String()
    {
        Free();
    }
public:
#ifdef _UNICODE
    char *Convert(CString szText)
    {
        if (szText.GetLength() > 0)
        {
            m_Result = (char *)MakeUtf8String(szText);
        }
        else
        {
            m_Result = (char *)malloc(1);
            m_Result[0] = '\0';
        }
        return m_Result;
    }
#else
    char *Convert(CString szText)
    {
        if (szText.GetLength() > 0)
        {
            Utf8Encode(szText, &m_Result);
        }
        else
        {
            m_Result = (char *)malloc(1);
            m_Result[0] = '\0';
        }
        return m_Result;
    }
#endif
    void Free()
    {
        if (m_Result != nullptr)
        {
            free(m_Result);
            m_Result = nullptr;
        }
    }
};
