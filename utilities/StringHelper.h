// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <algorithm>
#include <cctype>
#include <locale>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

namespace util
{
    class StringHelper
    {
    public:
        static inline std::wstring Convert(const std::string& str)
        {
            std::wstring w(str.begin(), str.end());
            return w;
        }
        static inline std::string Convert(const std::wstring& str)
        {
            std::string s(str.begin(), str.end());
            return s;
        }
    public:
        static inline std::string ToStringHex(int i)
        {
            const char fill = '0';
            std::ostringstream stream;
            stream << "0x"
                << std::setfill(fill) << std::setw(sizeof(int) * 2)
                << std::hex << i;
            return stream.str();
        }
        static inline int ToIntFromHex(const std::string& str)
        {
            return std::stoi(str, nullptr, 16);
        }
        static inline int ToInt(const std::string& str)
        {
            return std::stoi(str);
        }
        static inline std::vector<std::string> Split(const char *str, char c)
        {
            std::vector<std::string> result;
            do
            {
                const char *begin = str;
                while (*str != c && *str)
                    str++;
                result.push_back(std::string(begin, str));
            } while (0 != *str++);
            return result;
        }
        static inline std::string TowLower(const std::string& str)
        {
            std::string s = str;
            std::transform(s.begin(), s.end(), s.begin(), ::towlower);
            return s;
        }
        static inline std::string ToUpper(const std::string& str)
        {
            std::string s = str;
            std::transform(s.begin(), s.end(), s.begin(), ::toupper);
            return s;
        }
        static inline bool CompareNoCase(const std::string& str1, const std::string& str2)
        {
            std::string s1 = ToUpper(str1);
            std::string s2 = ToUpper(str2);
            return s1 == s2;
        }
        static inline bool ContainsNoCase(const std::string& str, const std::string& value, char token)
        {
            std::string v = ToUpper(value);
            auto tokens = Split(str.c_str(), token);
            for (auto& t : tokens)
            {
                if (ToUpper(t) == v)
                    return true;
            }
            return false;
        }
        static inline bool ReplaceNoCase(std::string& str, const std::string& from, const std::string& to)
        {
            std::string s = ToUpper(str);
            std::string f = ToUpper(from);
            auto pos = s.find(f);
            if (pos != std::string::npos)
            {
                str.replace(pos, f.length(), to);
                return true;
            }
            return false;
        }
        static inline size_t FindNoCase(const std::string& str, const std::string& find)
        {
            std::string s = ToUpper(str);
            std::string f = ToUpper(find);
            return s.find(f);
        }
        static inline void Replace(std::string& str, const std::string& from, const std::string& to)
        {
            size_t pos = 0;
            while ((pos = str.find(from, pos)) != std::string::npos)
            {
                str.replace(pos, from.length(), to);
                pos += to.length();
            }
        }
        static inline void TrimLeft(std::string &s)
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                return !std::isspace(ch);
            }));
        }
        static inline void TrimRight(std::string &s)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return !std::isspace(ch);
            }).base(), s.end());
        }
        static inline void Trim(std::string &s)
        {
            TrimLeft(s);
            TrimRight(s);
        }
        static inline void TrimLeft(std::string &s, int c)
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [c](int ch) {
                return !(c == ch);
            }));
        }
        static inline void TrimRight(std::string &s, int c)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(), [c](int ch) {
                return !(c == ch);
            }).base(), s.end());
        }
        static inline void Trim(std::string &s, int c)
        {
            TrimLeft(s, c);
            TrimRight(s, c);
        }
    public:
        static inline std::wstring ToWStringHex(int i)
        {
            const wchar_t fill = '0';
            std::wostringstream stream;
            stream << L"0x" 
                   << std::setfill(fill) << std::setw(sizeof(int)*2) 
                   << std::hex << i;
          return stream.str();
        }
        static inline int ToIntFromHex(const std::wstring& str)
        {
            return std::stoi(str, nullptr, 16);
        }
        static inline int ToInt(const std::wstring& str)
        {
            return std::stoi(str);
        }
        static inline std::vector<std::wstring> Split(const wchar_t *str, wchar_t c)
        {
            std::vector<std::wstring> result;
            do
            {
                const wchar_t *begin = str;
                while(*str != c && *str)
                    str++;
                result.push_back(std::wstring(begin, str));
            } while (0 != *str++);
            return result;
        }
        static inline std::wstring TowLower(const std::wstring& str)
        {
            std::wstring s = str;
            std::transform(s.begin(), s.end(), s.begin(), ::towlower);
            return s;
        }
        static inline std::wstring ToUpper(const std::wstring& str)
        {
            std::wstring s = str;
            std::transform(s.begin(), s.end(), s.begin(), ::toupper);
            return s;
        }
        static inline bool CompareNoCase(const std::wstring& str1, const std::wstring& str2)
        {
            std::wstring s1 = ToUpper(str1);
            std::wstring s2 = ToUpper(str2);
            return s1 == s2;
        }
        static inline bool ContainsNoCase(const std::wstring& str, const std::wstring& value, wchar_t token)
        {
            std::wstring v = ToUpper(value);
            auto tokens = Split(str.c_str(), token);
            for (auto& t : tokens) 
            {
                if (ToUpper(t) == v)
                    return true;
            }
            return false;
        }
        static inline bool ReplaceNoCase(std::wstring& str, const std::wstring& from, const std::wstring& to)
        {
            std::wstring s = ToUpper(str);
            std::wstring f = ToUpper(from);
            auto pos = s.find(f);
            if (pos != std::string::npos)
            {
                str.replace(pos, f.length(), to);
                return true;
            }
            return false;
        }
        static inline size_t FindNoCase(const std::wstring& str, const std::wstring& find)
        {
            std::wstring s = ToUpper(str);
            std::wstring f = ToUpper(find);
            return s.find(f);
        }
        static inline void Replace(std::wstring& str, const std::wstring& from, const std::wstring& to)
        {
            size_t pos = 0;
            while ((pos = str.find(from, pos)) != std::wstring::npos)
            {
                str.replace(pos, from.length(), to);
                pos += to.length();
            }
        }
        static inline void TrimLeft(std::wstring &s)
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                return !std::isspace(ch);
            }));
        }
        static inline void TrimRight(std::wstring &s)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return !std::isspace(ch);
            }).base(), s.end());
        }
        static inline void Trim(std::wstring &s)
        {
            TrimLeft(s);
            TrimRight(s);
        }
        static inline void TrimLeft(std::wstring &s, int c)
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [c](int ch) {
                return !(c == ch);
            }));
        }
        static inline void TrimRight(std::wstring &s, int c)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(), [c](int ch) {
                return !(c == ch);
            }).base(), s.end());
        }
        static inline void Trim(std::wstring &s, int c)
        {
            TrimLeft(s, c);
            TrimRight(s, c);
        }
    };
}
