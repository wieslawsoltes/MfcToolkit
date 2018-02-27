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
            #pragma warning(push)
            #pragma warning(disable:4101)
            util::Utilities utilities;
            #pragma warning(pop)
        }
    };
}
