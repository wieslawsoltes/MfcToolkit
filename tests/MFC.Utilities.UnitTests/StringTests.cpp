#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(String_Tests)
    {
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

        TEST_METHOD(String_Split_string)
        {
            std::string str = "Test string to split";
            auto result = util::string::Split(str.c_str(), ' ');
            Assert::AreEqual(size_t(4), result.size());
            Assert::AreEqual("Test", result[0].c_str());
            Assert::AreEqual("string", result[1].c_str());
            Assert::AreEqual("to", result[2].c_str());
            Assert::AreEqual("split", result[3].c_str());
        }

        TEST_METHOD(String_TowLower_string)
        {
            std::string str = "Test STRING TO split";
            std::string result = util::string::TowLower(str);
            Assert::AreEqual("test string to split", result.c_str());
        }

        TEST_METHOD(String_ToUpper_string)
        {
            std::string str = "Test string To split";
            std::string result = util::string::ToUpper(str);
            Assert::AreEqual("TEST STRING TO SPLIT", result.c_str());
        }

        TEST_METHOD(String_CompareNoCase_string)
        {
            std::string str1 = "Test";
            std::string str2 = "tEsT";
            Assert::IsTrue(util::string::CompareNoCase(str1, str2));
        }

        TEST_METHOD(String_ContainsNoCase_string)
        {
            std::string str = "Test sTrinG To split";
            Assert::IsTrue(util::string::ContainsNoCase(str, "STring", ' '));
        }

        TEST_METHOD(String_ReplaceNoCase_string)
        {
            std::string str = "Test sTriNg To split Test StrinG To split";
            std::string from = "sTriNg";
            std::string to = "TEST";
            int count = util::string::ReplaceNoCase(str, from, to);
            Assert::AreEqual(2, count);
            Assert::AreEqual("Test TEST To split Test TEST To split", str.c_str());
        }

        TEST_METHOD(String_FindNoCase_string)
        {
            std::string str = "Test STring To split Test";
            std::string find = "sTrINg";
            size_t pos = util::string::FindNoCase(str, find);
            Assert::AreEqual(size_t(5), pos);
        }

        TEST_METHOD(String_Replace_string)
        {
            std::string str = "Test string to split Test string to split";
            std::string from = "string";
            std::string to = "other";
            int count = util::string::Replace(str, from, to);
            Assert::AreEqual(2, count);
            Assert::AreEqual("Test other to split Test other to split", str.c_str());
        }

        TEST_METHOD(String_TrimLeft_string)
        {
            std::string str = "  Test test  ";
            util::string::TrimLeft(str);
            Assert::AreEqual("Test test  ", str.c_str());
        }

        TEST_METHOD(String_TrimRight_string)
        {
            std::string str = "  Test test  ";
            util::string::TrimRight(str);
            Assert::AreEqual("  Test test", str.c_str());
        }

        TEST_METHOD(String_Trim_string)
        {
            std::string str = "  Test test  ";
            util::string::Trim(str);
            Assert::AreEqual("Test test", str.c_str());
        }

        TEST_METHOD(String_TrimLeft_Arg_string)
        {
            std::string str = "---Test-test---";
            util::string::TrimLeft(str, '-');
            Assert::AreEqual("Test-test---", str.c_str());
        }

        TEST_METHOD(String_TrimRight_Arg_string)
        {
            std::string str = "---Test-test---";
            util::string::TrimRight(str, '-');
            Assert::AreEqual("---Test-test", str.c_str());
        }

        TEST_METHOD(String_Trim_Arg_string)
        {
            std::string str = "---Test-test---";
            util::string::Trim(str, '-');
            Assert::AreEqual("Test-test", str.c_str());
        }

        TEST_METHOD(String_ToWStringHex_wstring)
        {
        }

        TEST_METHOD(String_ToIntFromHex_wstring)
        {
        }

        TEST_METHOD(String_ToInt_wstring)
        {
        }

        TEST_METHOD(String_Split_wstring)
        {
        }

        TEST_METHOD(String_TowLower_wstring)
        {
        }

        TEST_METHOD(String_ToUpper_wstring)
        {
        }

        TEST_METHOD(String_CompareNoCase_wstring)
        {
        }

        TEST_METHOD(String_ContainsNoCase_wstring)
        {
        }

        TEST_METHOD(String_ReplaceNoCase_wstring)
        {
        }

        TEST_METHOD(String_FindNoCase_wstring)
        {
        }

        TEST_METHOD(String_Replace_wstring)
        {
        }

        TEST_METHOD(String_TrimLeft_wstring)
        {
        }

        TEST_METHOD(String_TrimRight_wstring)
        {
        }

        TEST_METHOD(String_Trim_wstring)
        {
        }

        TEST_METHOD(String_TrimLeft_Arg_wstring)
        {
        }

        TEST_METHOD(String_TrimRight_Arg_wstring)
        {
        }

        TEST_METHOD(String_Trim_Arg_wstring)
        {
        }
    };
}
