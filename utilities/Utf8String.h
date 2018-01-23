// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include <string>
#else
#include <locale>
#include <codecvt>
#endif

namespace util
{
    class CUtf8String
    {
    public:
#if defined(_WIN32) || defined(_WIN64)
        static std::string ToUtf8(const std::wstring &szText)
        {
            if (szText.empty())
                return std::string();
            int size_needed = WideCharToMultiByte(CP_UTF8, 0, &szText[0], (int)szText.size(), NULL, 0, NULL, NULL);
            std::string strTo(size_needed, 0);
            WideCharToMultiByte(CP_UTF8, 0, &szText[0], (int)szText.size(), &strTo[0], size_needed, NULL, NULL);
            return strTo;
        }
        static std::string ToUtf8(const wchar_t* szText)
        {
            if (wcslen(szText))
                return std::string();
            int size_needed = WideCharToMultiByte(CP_UTF8, 0, &szText[0], (int)wcslen(szText), NULL, 0, NULL, NULL);
            std::string strTo(size_needed, 0);
            WideCharToMultiByte(CP_UTF8, 0, &szText[0], (int)wcslen(szText), &strTo[0], size_needed, NULL, NULL);
            return strTo;
        }
        static std::wstring ToUnicode(const std::string &szText)
        {
            if (szText.empty())
                return std::wstring();
            int size_needed = MultiByteToWideChar(CP_UTF8, 0, &szText[0], (int)szText.size(), NULL, 0);
            std::wstring wstrTo(size_needed, 0);
            MultiByteToWideChar(CP_UTF8, 0, &szText[0], (int)szText.size(), &wstrTo[0], size_needed);
            return wstrTo;
        }
        static std::wstring ToUnicode(const char* szText)
        {
            if (strlen(szText) == 0)
                return std::wstring();
            int size_needed = MultiByteToWideChar(CP_UTF8, 0, &szText[0], (int)strlen(szText), NULL, 0);
            std::wstring wstrTo(size_needed, 0);
            MultiByteToWideChar(CP_UTF8, 0, &szText[0], (int)strlen(szText), &wstrTo[0], size_needed);
            return wstrTo;
        }
#else
        static std::string ToUtf8(const std::wstring& szText)
        {
            static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
            return convert.to_bytes(szText);
        }
        static std::string ToUtf8(const wchar_t* szText)
        {
            static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
            return convert.to_bytes(szText);
        }
        static std::wstring ToUnicode(const std::string& szText)
        {
            static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
            return convert.from_bytes(szText);
        }
        static std::wstring ToUnicode(const char* szText)
        {
            static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
            return convert.from_bytes(szText);
        }
#endif
    };
}
