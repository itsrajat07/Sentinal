#include <catch2/catch_test_macros.hpp>
#include "sentinel/version.h"

TEST_CASE("version is not empty") {
    REQUIRE_FALSE(sentinel::version().empty());
}
