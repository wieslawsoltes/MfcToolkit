#pragma once

#include <string>
#include <vector>
#include "Log.h"

namespace util
{
    class MemoryLog : public ILog
    {
    public:
        std::vector<std::wstring> m_Messages;
    public:
        MemoryLog()
        {
        };
        virtual ~MemoryLog()
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
                m_Messages.emplace_back(szData);
            }
            catch (...) {}
        }
    };
}
