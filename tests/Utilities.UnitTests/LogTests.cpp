#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\Log.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UtilitiesUnitTests
{
    class TestLog : public util::ILog
    {
    public:
        TestLog() { };
        virtual ~TestLog()
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
        }
    };

    TEST_CLASS(Log_Tests)
    {
    public:
        TEST_METHOD(Log_Constructor)
        {
            #pragma warning(push)
            #pragma warning(disable:4101)
            TestLog log;
            #pragma warning(pop)
        }
    };
}
