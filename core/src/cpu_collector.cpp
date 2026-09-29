#include "sentinel/cpu_collector.h"
#include <windows.h>

namespace {

    // FILETIME is two 32-bit halves; combine them into one 64-bit number.
    uint64_t toU64(const FILETIME& ft) {
        return (static_cast<uint64_t>(ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
    }

    struct Times { uint64_t idle, kernel, user; };

    Times readTimes() {
        FILETIME idle{}, kernel{}, user{};
        GetSystemTimes(&idle, &kernel, &user);
        return { toU64(idle), toU64(kernel), toU64(user) };
    }

} // namespace

namespace sentinel {

    CpuCollector::CpuCollector() {
        // Baseline reading so the first collect() has something to diff against.
        auto t = readTimes();
        prevIdle_ = t.idle;
        prevKernel_ = t.kernel;
        prevUser_ = t.user;
    }

    nlohmann::json CpuCollector::collect() {
        auto t = readTimes();

        uint64_t dIdle = t.idle - prevIdle_;
        uint64_t dKernel = t.kernel - prevKernel_;
        uint64_t dUser = t.user - prevUser_;
        prevIdle_ = t.idle; prevKernel_ = t.kernel; prevUser_ = t.user;

        // Gotcha: kernel time INCLUDES idle time, so total = kernel + user.
        uint64_t total = dKernel + dUser;
        double usage = total
            ? 100.0 * static_cast<double>(total - dIdle) / static_cast<double>(total)
            : 0.0;

        SYSTEM_INFO si{};
        GetSystemInfo(&si);

        return {
            {"usage_percent", usage},
            {"logical_cores", si.dwNumberOfProcessors}
        };
    }

} // namespace sentinel