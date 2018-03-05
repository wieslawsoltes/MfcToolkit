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
            std::string str = "Test string!";
            std::wstring wstr = util::StringHelper::Convert(str);
            Assert::AreEqual(L"Test string!", wstr.c_str());
        }

        TEST_METHOD(StringHelper_Convert_To_string)
        {
            std::wstring wstr = L"Test string!";
            std::string str = util::StringHelper::Convert(wstr);
            Assert::AreEqual("Test string!", str.c_str());
        }
    public:
        TEST_METHOD(StringHelper_ToStringHex_string)
        {
            std::string str = util::StringHelper::ToStringHex(0x00310010);
            Assert::AreEqual("0x00310010", str.c_str());
        }

        TEST_METHOD(StringHelper_ToIntFromHex_string)
        {
            std::string str = "0x00310010";
            int n = util::StringHelper::ToIntFromHex(str);
            Assert::AreEqual(0x00310010, n);
        }

        TEST_METHOD(StringHelper_ToInt_string)
        {
            std::string str1 = "5";
            int n1 = util::StringHelper::ToInt(str1);
            Assert::AreEqual(5, n1);

            std::string str2 = "-5";
            int n2 = util::StringHelper::ToInt(str2);
            Assert::AreEqual(-5, n2);
        }
    };
}
