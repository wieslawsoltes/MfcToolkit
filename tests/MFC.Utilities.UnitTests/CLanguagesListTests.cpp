#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\LanguagesList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(CLanguagesList_Tests)
    {
    public:
        TEST_METHOD(CLanguagesList_Constructor)
        {
            util::CLanguagesList languages;
        }
    };
}
