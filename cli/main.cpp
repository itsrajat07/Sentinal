#include "sentinel/cpu_collector.h"
#include "sentinel/memory_collector.h"
#include "sentinel/version.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

int main() {
    using namespace sentinel;

    std::vector<std::unique_ptr<Collector>> collectors;
    collectors.push_back(std::make_unique<CpuCollector>());
    collectors.push_back(std::make_unique<MemoryCollector>());

    // CPU needs two samples separated by time to produce a meaningful delta.
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    nlohmann::json out;
    out["version"] = version();
    for (auto& c : collectors) {
        out[c->name()] = c->collect();
    }
    std::cout << out.dump(2) << '\n';
}