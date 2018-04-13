#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\ConsoleLog.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UtilitiesUnitTests
{
    TEST_CLASS(ConsoleLog_Tests)
    {
    public:
        TEST_METHOD(ConsoleLog_Constructor)
        {
            #pragma warning(push)
            #pragma warning(disable:4101)
            util::ConsoleLog log;
            #pragma warning(pop)
        }
    };
}
