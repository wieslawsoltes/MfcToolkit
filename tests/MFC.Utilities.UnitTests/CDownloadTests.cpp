#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\Download.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MFCUtilitiesUnitTests
{
    TEST_CLASS(CDownload_Tests)
    {
    public:
        TEST_METHOD(CDownloadCallback_Constructor)
        {
            util::CDownloadCallback callback;
        }
    public:
        TEST_METHOD(CDownload_Constructor)
        {
            #pragma warning(push)
            #pragma warning(disable:4101)
            util::CDownload download;
            #pragma warning(pop)
        }
    };
}
