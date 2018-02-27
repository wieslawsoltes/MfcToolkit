#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\LanguageContext.h"
#include "utilities\LanguageHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(CLanguageHelper_Tests)
    {
    public:
        TEST_METHOD(CLanguageHelper_Constructor)
        {
            util::CLanguageContext context;
            util::CLanguageHelper helper(&context);
        }
    };
}
