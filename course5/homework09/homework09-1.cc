#include "benchmark/benchmark.h"
#include <cstring>
#include <string>
#include <fstream>
#include <exception>
/*
---------------------------------------------------------------------------------------
Benchmark                                                Time           CPU Iterations
---------------------------------------------------------------------------------------
DataSourceFixture/test_is_greater_str/1                 61 ns         61 ns   10850546
DataSourceFixture/test_is_greater_str/8                 80 ns         80 ns    7604072
DataSourceFixture/test_is_greater_str/64               177 ns        177 ns    4124238
DataSourceFixture/test_is_greater_str/512              283 ns        283 ns    2416691
DataSourceFixture/test_is_greater_str/4096             769 ns        769 ns     849670
DataSourceFixture/test_is_greater_str/32768           7157 ns       7161 ns      92723
DataSourceFixture/test_is_greater_str/262144         79661 ns      79706 ns       8050
DataSourceFixture/test_is_greater_str/1048576      1222100 ns    1222772 ns        507
DataSourceFixture/test_is_greather_char/2               17 ns         17 ns   41464765
DataSourceFixture/test_is_greather_char/8               17 ns         17 ns   39859245
DataSourceFixture/test_is_greather_char/64              18 ns         18 ns   41394314
DataSourceFixture/test_is_greather_char/512             16 ns         16 ns   41832781
DataSourceFixture/test_is_greather_char/4096            16 ns         16 ns   43379640
DataSourceFixture/test_is_greather_char/32768           16 ns         16 ns   41883490
DataSourceFixture/test_is_greather_char/262144          17 ns         17 ns   43402680
DataSourceFixture/test_is_greather_char/1048576         16 ns         16 ns   43053713
*/

class DataSourceFixture: public benchmark::Fixture
{
public:
    DataSourceFixture() = default;

    void SetUp(const benchmark::State&) override
    {
        std::fstream data;
        data.open("data.txt", std::fstream::in);
        if (!data.is_open())
            throw std::runtime_error("cannot open file with data");
        std::getline(data, this->dataString);
        data.close();
        this->dataLength = this->dataString.size();
    }

    void TearDown(const benchmark::State&) override
    {
    }

    ~DataSourceFixture() = default;

    std::string dataString;
    std::size_t dataLength;
};

bool is_greater_str(const std::string& a, const std::string& b) { return a > b; }

bool is_greater_char(const char* a, const char* b) { return std::strcmp(a, b) > 0; }


BENCHMARK_DEFINE_F(DataSourceFixture, test_is_greater_str)(benchmark::State& st)
{
    std::size_t offset = 0;
    std::size_t length = st.range(0);
    auto s1 = std::string(dataString, offset, length);
    auto s2 = std::string(dataString, offset+1, length);

    const char* a = s1.c_str();
    const char* b = s2.c_str();

//    const char* a = std::string(dataString, offset, length).c_str();
//    const char* b = std::string(dataString, offset + 1, length).c_str();

    while (st.KeepRunning())
    {
        benchmark::DoNotOptimize(is_greater_str(a, b));
    }
}


BENCHMARK_REGISTER_F(DataSourceFixture, test_is_greater_str)->Range(1, 1<<20);

BENCHMARK_DEFINE_F(DataSourceFixture, test_is_greather_char)(benchmark::State& st)
{
    std::size_t offset = 0;
    std::size_t length = st.range(0);
//    auto s1 = std::string(dataString, offset, length);
//    auto s2 = std::string(dataString, offset+1, length);

//    const char* a = s1.c_str();
//    const char* b = s2.c_str();

    const char* a = std::string(dataString, offset, length).c_str();
    const char* b = std::string(dataString, offset + 1, length).c_str();

    while (st.KeepRunning())
    {
        benchmark::DoNotOptimize(is_greater_char(a, b));
    }
}

BENCHMARK_REGISTER_F(DataSourceFixture, test_is_greather_char)->Range(2, 1<<20);

BENCHMARK_MAIN();
