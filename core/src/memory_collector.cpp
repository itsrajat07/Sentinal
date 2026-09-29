#include "sentinel/memory_collector.h"
#include <windows.h>

namespace sentinel {

    nlohmann::json MemoryCollector::collect() {
        MEMORYSTATUSEX ms{};
        ms.dwLength = sizeof(ms);   // Win32 convention: caller sets the struct size first
        if (!GlobalMemoryStatusEx(&ms)) {
            return { {"error", "GlobalMemoryStatusEx failed"}, {"code", GetLastError()} };
        }

        return {
            {"load_percent", ms.dwMemoryLoad},
            {"total_bytes", ms.ullTotalPhys},
            {"available_bytes", ms.ullAvailPhys},
            {"used_bytes", ms.ullTotalPhys - ms.ullAvailPhys},
            {"commit_total_bytes", ms.ullTotalPageFile},
            {"commit_available_bytes", ms.ullAvailPageFile}
        };
    }

} // namespace sentinel