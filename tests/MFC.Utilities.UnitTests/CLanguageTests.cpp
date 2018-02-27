#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\Language.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(CLanguage_Tests)
    {
    public:
        TEST_METHOD(CLanguage_Constructor)
        {
            lang::CLanguage language;
        }
    };
}
