#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\Utilities.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(Utilities_Tests)
    {
    public:
        TEST_METHOD(Utilities_Constructor)
        {
            util::Utilities utilities;
        }
    };
}
