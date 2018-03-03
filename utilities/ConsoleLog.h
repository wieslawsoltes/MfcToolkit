#pragma once

#include <string>
#include <wchar.h>
#include <memory>
#include <cstdio>
#include "Log.h"
#include "utilities\StringHelper.h"

namespace util
{
    class ConsoleLog : public ILog
    {
    public:
        ConsoleLog()
        {
        };
        virtual ~ConsoleLog()
        {
            Close();
        }
    public:
        bool Open()
        {
            return true;
        }
        void Close()
        {
        }
        void Log(const std::wstring szMessage, const bool bNewLine = true)
        {
            try
            {
                std::wstring szData = szMessage;
                if (bNewLine)
                    szData += L"\n";
                std::string szAnsi = util::StringHelper::Convert(szData);
                std::fwrite(szAnsi.data(), sizeof(char), szAnsi.size(), stderr);
                std::fflush(stderr);
            }
            catch (...) {}
        }
    };
}
