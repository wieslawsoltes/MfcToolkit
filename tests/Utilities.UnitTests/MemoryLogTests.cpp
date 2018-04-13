#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\MemoryLog.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UtilitiesUnitTests
{
    TEST_CLASS(MemoryLog_Tests)
    {
    public:
        TEST_METHOD(MemoryLog_Constructor)
        {
            util::MemoryLog log;
            Assert::AreEqual(size_t(0), log.m_Messages.size());
        }

        TEST_METHOD(MemoryLog_Message_NewLine)
        {
            util::MemoryLog log;
            std::wstring szMessage = L"[Info] Log message";
            log.Log(szMessage);
            Assert::AreEqual(size_t(1), log.m_Messages.size());
            Assert::AreEqual(szMessage + L"\n", log.m_Messages[0]);
        }

        TEST_METHOD(MemoryLog_Message_No_NewLine)
        {
            util::MemoryLog log;
            std::wstring szMessage = L"[Info] Log message";
            log.Log(szMessage, false);
            Assert::AreEqual(size_t(1), log.m_Messages.size());
            Assert::AreEqual(szMessage, log.m_Messages[0]);
        }
    };
}
