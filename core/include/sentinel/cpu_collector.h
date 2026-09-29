#pragma once
#include "sentinel/collector.h"
#include <cstdint>

namespace sentinel {

    class CpuCollector : public Collector {
    public:
        CpuCollector();
        std::string name() const override { return "cpu"; }
        nlohmann::json collect() override;

    private:
        uint64_t prevIdle_{ 0 }, prevKernel_{ 0 }, prevUser_{ 0 };
    };

} // namespace sentinel