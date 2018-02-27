#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\Thread.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(CThread_Tests)
    {
    public:
        TEST_METHOD(CThread_Constructor)
        {
            util::CThread thread;
        }
    };
}
