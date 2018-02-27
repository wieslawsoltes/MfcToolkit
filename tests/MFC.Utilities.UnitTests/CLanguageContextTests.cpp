#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\LanguageContext.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(CLanguageContext_Tests)
    {
    public:
        TEST_METHOD(CLanguageContext_Constructor)
        {
            lang::CLanguageContext context;
        }
    };
}
