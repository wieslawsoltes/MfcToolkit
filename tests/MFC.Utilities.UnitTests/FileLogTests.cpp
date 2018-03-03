#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\FileLog.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(FileLog_Tests)
    {
    public:
        TEST_METHOD(FileLog_Constructor)
        {
            #pragma warning(push)
            #pragma warning(disable:4101)
            util::FileLog log(L"");
            #pragma warning(pop)
        }
    };
}
