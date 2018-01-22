// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <locale>
#include <codecvt>

namespace util
{
    class CUtf8String
    {
    public:
        static const std::string ConvertToUtf8(const std::wstring& szText)
        {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
            return convert.to_bytes(szText);
        }
        static const std::wstring ConvertToUnicode(const std::string& szText)
        {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
            return convert.from_bytes(szText);
        }
        static const std::string ConvertToUtf8(const wchar_t* szText)
        {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
            return convert.to_bytes(szText);
        }
        static const std::wstring ConvertToUnicode(const char* szText)
        {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
            return convert.from_bytes(szText);
        }
    };
}
