#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\MapT.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(CMapT_Tests)
    {
    public:
        TEST_METHOD(CMapT_IsEmpty_Returns_True)
        {
            util::CMapT<int, std::string> m;
            Assert::IsTrue(m.IsEmpty());
        }

        TEST_METHOD(CMapT_IsEmpty_Returns_False)
        {
            util::CMapT<int, std::string> m;
            m.Insert(0, "Test");
            Assert::IsFalse(m.IsEmpty());
        }
    };
}
