find_package(Catch2 3 CONFIG REQUIRED)

add_executable(sentinel_tests test_version.cpp)
target_link_libraries(sentinel_tests PRIVATE sentinel_core Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(sentinel_tests)