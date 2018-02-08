#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\StringHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{		
    TEST_CLASS(StringHelper_Tests)
    {
    public:
        TEST_METHOD(StringHelper_Convert_To_wstring)
        {
            std::string str = "Test string.";
            std::wstring wstr = StringHelper::Convert(str);
            Assert::AreEqual(L"Test string.", wstr);
        }
        TEST_METHOD(StringHelper_Convert_To_string)
        {
            std::string wstr = L"Test string.";
            std::wstring str = StringHelper::Convert(wstr);
            Assert::AreEqual("Test string.", str);
        }
    };
}
