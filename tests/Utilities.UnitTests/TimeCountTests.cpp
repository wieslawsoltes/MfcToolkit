#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\TimeCount.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UtilitiesUnitTests
{
    TEST_CLASS(CTimeCount_Tests)
    {
    public:
        TEST_METHOD(CTimeCount_Constructor)
        {
            util::CTimeCount timeCount;
        }
    };
}
