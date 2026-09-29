#pragma once
#include <nlohmann/json.hpp>
#include <string>

namespace sentinel {

    // Every metric source implements this. The sampler, MCP layer and GUI
    // will all talk to collectors through this one interface.
    class Collector {
    public:
        virtual ~Collector() = default;          // virtual destructor: required for base classes
        virtual std::string name() const = 0;    // "= 0" means pure virtual: derived classes must override
        virtual nlohmann::json collect() = 0;
    };

} // namespace sentinel