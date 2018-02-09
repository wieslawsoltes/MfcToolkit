#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\ListT.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(CListT_Tests)
    {
    public:
        TEST_METHOD(CListT_IsEmpty_Returns_True)
        {
            util::CListT<std::string> l;
            Assert::IsTrue(l.IsEmpty());
        }
        TEST_METHOD(CListT_IsEmpty_Returns_False)
        {
            util::CListT<std::string> l;
            l.Insert("Test");
            Assert::IsFalse(l.IsEmpty());
        }
    };
}
