#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities\ArgvParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UtilitiesUnitTests
{
    enum OptionId : int
    {
        Presets,
        Preset,
        Engines,
        Engine,
        Files,
        Mono,
        Input,
        Output,
        Help
    };

    std::vector<util::Option> options
    {
        { OptionId::Presets,    { L"--presets"       }, 1  },
        { OptionId::Preset,     { L"--preset", L"-p" }, 1  },
        { OptionId::Engines,    { L"--engines"       }, 1  },
        { OptionId::Engine,     { L"--engine", L"-e" }, 1  },
        { OptionId::Files,      { L"--files"         }, 1  },
        { OptionId::Mono,       { L"--mono", L"-m"   }, 0  },
        { OptionId::Input,      { L"--input", L"-i"  }, -1 },
        { OptionId::Output,     { L"--output", L"-o" }, 1  },
        { OptionId::Help,       { L"--help", L"-h"   }, 0  }
    };

    TEST_CLASS(ArgvParser_Tests)
    {
    public:
        TEST_METHOD(ArgvParser_Test_Invalid_Params)
        {
            int argc = 2;
            wchar_t *argv[]
            {
                L"program.exe", L"--files"
            };

            std::vector<util::Result> results;
            util::ArgvParser parser{ false };
            int nResult = parser.ParseOptions(argc, argv, options, results);

            Assert::AreEqual(-1, nResult);
            Assert::AreEqual(size_t(0), results.size());
        }

        TEST_METHOD(ArgvParser_Test_Mixed_Params)
        {
            int argc = 6;
            wchar_t *argv[]
            {
                L"program.exe", L"--files", L"input.files", L"--preset", L"0", L"-m"
            };

            std::vector<util::Result> results;
            util::ArgvParser parser{ false };
            int nResult = parser.ParseOptions(argc, argv, options, results);

            Assert::AreEqual(0, nResult);
            Assert::AreEqual(size_t(3), results.size());

            Assert::IsTrue(OptionId::Preset == static_cast<OptionId>(results[0].Id));
            Assert::AreEqual(L"--preset", results[0].Arg.c_str());
            Assert::AreEqual(size_t(1), results[0].Params.size());
            Assert::AreEqual(L"0", results[0].Params[0].c_str());

            Assert::IsTrue(OptionId::Files == static_cast<OptionId>(results[1].Id));
            Assert::AreEqual(L"--files", results[1].Arg.c_str());
            Assert::AreEqual(size_t(1), results[1].Params.size());
            Assert::AreEqual(L"input.files", results[1].Params[0].c_str());

            Assert::IsTrue(OptionId::Mono == static_cast<OptionId>(results[2].Id));
            Assert::AreEqual(L"-m", results[2].Arg.c_str());
            Assert::AreEqual(size_t(0), results[2].Params.size());
        }

        TEST_METHOD(ArgvParser_Test_Option_Multi_Params)
        {
            int argc = 6;
            wchar_t *argv[]
            {
                L"program.exe", L"--input", L"L.wav", L"R.wav", L"C.wav", L"-m"
            };

            std::vector<util::Result> results;
            util::ArgvParser parser{ false };
            int nResult = parser.ParseOptions(argc, argv, options, results);

            Assert::AreEqual(0, nResult);
            Assert::AreEqual(size_t(2), results.size());

            Assert::IsTrue(OptionId::Mono == static_cast<OptionId>(results[0].Id));
            Assert::AreEqual(L"-m", results[0].Arg.c_str());
            Assert::AreEqual(size_t(0), results[0].Params.size());

            Assert::IsTrue(OptionId::Input == static_cast<OptionId>(results[1].Id));
            Assert::AreEqual(L"--input", results[1].Arg.c_str());
            Assert::AreEqual(size_t(3), results[1].Params.size());
            Assert::AreEqual(L"L.wav", results[1].Params[0].c_str());
            Assert::AreEqual(L"R.wav", results[1].Params[1].c_str());
            Assert::AreEqual(L"C.wav", results[1].Params[2].c_str());
        }

        TEST_METHOD(ArgvParser_Test_HasDuplicates_True)
        {
            int argc = 5;
            wchar_t *argv[]
            {
                L"program.exe", L"-m", L"-m", L"-i", L"input.wav"
            };

            std::vector<util::Result> results;
            util::ArgvParser parser{ false };
            int nResult = parser.ParseOptions(argc, argv, options, results);

            Assert::AreEqual(-1, nResult);
            Assert::AreEqual(size_t(3), results.size());
        }
    };
}
