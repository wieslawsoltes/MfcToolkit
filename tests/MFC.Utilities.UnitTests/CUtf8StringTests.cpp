#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\Utf8String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(CUtf8String_Tests)
    {
    public:
        TEST_METHOD(CUtf8String_Constructor)
        {
            #pragma warning(push)
            #pragma warning(disable:4101)
            util::CUtf8String converter;
            #pragma warning(pop)
        }
    };
}
