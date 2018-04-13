#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\Pipe.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UtilitiesUnitTests
{
    TEST_CLASS(CPipe_Tests)
    {
    public:
        TEST_METHOD(CPipe_Constructor_Inherit_False)
        {
            util::CPipe pipe(false);
        }

        TEST_METHOD(CPipe_Constructor_Inherit_True)
        {
            util::CPipe pipe(true);
        }
    };
}
