#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(String_Tests)
    {
    public:
        TEST_METHOD(String_Convert_To_wstring)
        {
            std::string str = "Test string!";
            std::wstring wstr = util::string::Convert(str);
            Assert::AreEqual(L"Test string!", wstr.c_str());
        }

        TEST_METHOD(String_Convert_To_string)
        {
            std::wstring wstr = L"Test string!";
            std::string str = util::string::Convert(wstr);
            Assert::AreEqual("Test string!", str.c_str());
        }
    public:
        TEST_METHOD(String_ToStringHex_string)
        {
            std::string str = util::string::ToStringHex(0x00310010);
            Assert::AreEqual("0x00310010", str.c_str());
        }

        TEST_METHOD(String_ToIntFromHex_string)
        {
            std::string str = "0x00310010";
            int n = util::string::ToIntFromHex(str);
            Assert::AreEqual(0x00310010, n);
        }

        TEST_METHOD(String_ToInt_string)
        {
            std::string str1 = "5";
            int n1 = util::string::ToInt(str1);
            Assert::AreEqual(5, n1);

            std::string str2 = "-5";
            int n2 = util::string::ToInt(str2);
            Assert::AreEqual(-5, n2);
        }

        TEST_METHOD(String_Split)
        {
            std::string str = "Test string to split";
            auto result = util::string::Split(str.c_str(), ' ');
            Assert::AreEqual(size_t(4), result.size());
            Assert::AreEqual("Test", result[0].c_str());
            Assert::AreEqual("string", result[1].c_str());
            Assert::AreEqual("to", result[2].c_str());
            Assert::AreEqual("split", result[3].c_str());
        }
    };
}
