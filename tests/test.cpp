#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../include/geohash.h"

TEST_CASE("Simple test") {
    CHECK(1 + 1 == 2);
    // CHECK(returnFalse() == true);
}

TEST_CASE("true/fase") {
    CHECK(returnFalse() == false);
}
