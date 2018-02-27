#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\Synchronize.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(CSynchronize_Tests)
    {
    public:
        TEST_METHOD(CSynchronize_Constructor)
        {
            util::CSynchronize sync;
        }
    };
}
