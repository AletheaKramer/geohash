#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"

TEST_CASE("Simple test") {
    CHECK(1 + 1 == 2);
}
