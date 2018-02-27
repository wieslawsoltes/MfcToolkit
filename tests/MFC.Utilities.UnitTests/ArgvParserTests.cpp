#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\ArgvParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(ArgvParser_Tests)
    {
    public:
        TEST_METHOD(ArgvParser_Constructor)
        {
            util::ArgvParser parser;
        }
    };
}
