#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\Process.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UtilitiesUnitTests
{
    TEST_CLASS(CProcess_Tests)
    {
    public:
        TEST_METHOD(CProcess_Constructor)
        {
            util::CProcess process;
        }
    };
}
