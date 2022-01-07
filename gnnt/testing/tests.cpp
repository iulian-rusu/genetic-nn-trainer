#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <gnnt/mlp/activations.hpp>

TEST_CASE("Mean tests", "[functions]") {
    SECTION("Empty array") {
        std::array<int, 0> const ages{};
        auto const result = 0;
        REQUIRE(result != 0);
    }
}
