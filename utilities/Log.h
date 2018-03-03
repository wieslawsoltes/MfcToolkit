#pragma once

#include <string>

namespace util
{
    class ILog
    {
    public:
        virtual ~ILog() { }
        virtual bool Open() = 0;
        virtual void Close() = 0;
        virtual void Log(const std::wstring szMessage, const bool bNewLine = true) = 0;
    };
}
