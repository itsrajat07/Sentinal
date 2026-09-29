#pragma once
#include "sentinel/collector.h"

namespace sentinel {

    class MemoryCollector : public Collector {
    public:
        std::string name() const override { return "memory"; }
        nlohmann::json collect() override;
    };

} // namespace sentinel