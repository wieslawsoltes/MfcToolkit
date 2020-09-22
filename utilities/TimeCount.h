#pragma once

#include <string>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <tuple>

namespace util
{
    class CTimeCount
    {
    private:
        std::chrono::milliseconds ms;
        std::chrono::time_point<std::chrono::steady_clock> start;
        std::chrono::time_point<std::chrono::steady_clock> end;
    private:
        template <typename Container, typename Fun>
        static void TupleForEach(const Container& c, Fun fun)
        {
            for (auto& e : c)
                fun(std::get<0>(e), std::get<1>(e), std::get<2>(e));
        }
    public:
        static std::string ToString(std::chrono::milliseconds time)
        {
            using T = std::tuple<std::chrono::milliseconds, int, const char *>;
            constexpr T formats[] = 
            {
                T { std::chrono::hours(1),        2, ""  },
                T { std::chrono::minutes(1),      2, ":" },
                T { std::chrono::seconds(1),      2, ":" },
                T { std::chrono::milliseconds(1), 3, "." }
            };
            std::ostringstream o;
            TupleForEach(formats, [&time, &o](auto denominator, auto width, auto separator) 
            {
                o << separator << std::setw(width) << std::setfill('0') << (time / denominator);
                time = time % denominator;
            });
            return o.str();
        }
    public:
        static std::wstring Format(std::chrono::milliseconds ms)
        {
            std::string s = ToString(ms);
            std::wstring w(s.begin(), s.end());
            return w;
        }
    public:
        void Start()
        {
            start = std::chrono::steady_clock::now();
        }
        void Stop()
        {
            end = std::chrono::steady_clock::now();
        }
        std::chrono::milliseconds ElapsedTime()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        }
    };
}
