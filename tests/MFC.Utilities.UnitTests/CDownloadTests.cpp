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
            util::CDownload download;
        }
    };
}
