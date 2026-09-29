find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_library(sentinel_core
    src/version.cpp
    src/cpu_collector.cpp
    src/memory_collector.cpp)

target_include_directories(sentinel_core PUBLIC include)
target_link_libraries(sentinel_core PUBLIC
    nlohmann_json::nlohmann_json
    spdlog::spdlog)
target_compile_definitions(sentinel_core PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)