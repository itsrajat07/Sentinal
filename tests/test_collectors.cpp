#include <catch2/catch_test_macros.hpp>
#include "sentinel/cpu_collector.h"
#include "sentinel/memory_collector.h"
#include <chrono>
#include <thread>

TEST_CASE("memory collector reports sane values") {
    sentinel::MemoryCollector m;
    auto j = m.collect();

    REQUIRE(j.contains("total_bytes"));
    REQUIRE(j["total_bytes"].get<unsigned long long>() > 0);
    REQUIRE(j["used_bytes"].get<unsigned long long>() <= j["total_bytes"].get<unsigned long long>());
    REQUIRE(j["load_percent"].get<int>() <= 100);
}

TEST_CASE("cpu collector stays within 0-100%") {
    sentinel::CpuCollector c;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    auto j = c.collect();

    double u = j["usage_percent"].get<double>();
    REQUIRE(u >= 0.0);
    REQUIRE(u <= 100.0);
    REQUIRE(j["logical_cores"].get<unsigned>() >= 1);
}