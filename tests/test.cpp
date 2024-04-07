#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../include/geohash.h"

TEST_CASE("geohash helpers") {
    Geohash gh(47.02345234657234, 19.036236263, 6);

    std::vector<int> expectedX = {1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0};

    auto resultX = gh.encodeX();

    CHECK(resultX == expectedX);

    std::vector<int> expectedY = {1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1};

    auto resultY = gh.encodeY();

    CHECK(resultY == expectedY);

    std::vector<int> expectedInterleaved = {
        1, 1, 0, 1, 0,
        0, 0, 0, 1, 0,
        1, 0, 0, 1, 1,
        0, 1, 1, 0, 1,
        0, 1, 0, 0, 1,
        0, 0, 0, 0, 0,
        1, 0, 0, 1, 1,
        0, 1, 1, 1, 1,
        0, 0, 0, 1, 0,
        1, 0, 1, 1, 0,
        1, 1, 1, 1, 0,
        0, 1, 1, 0, 1,
        0, 0, 0, 1};

    auto resultInterleaved = gh.interleave(resultX, resultY);

    CHECK(expectedInterleaved == resultInterleaved);

    std::vector<std::vector<int>> expectedGroups = {
        {1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 0, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 0, 1, 1},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 1, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 1, 1, 0},
        {0, 1, 1, 0, 1}};

    auto resultGroups = gh.split(resultInterleaved);

    // for (const auto& group : resultGroups) {
    //     for (int num : group) {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl;
    // }

    CHECK(expectedGroups == resultGroups);

    bool isEqual = (expectedGroups.size() == resultGroups.size());
    // for (size_t i = 0; isEqual && i < expectedGroups.size(); ++i) {
    //     if (expectedGroups[i] != resultGroups[i]) {
    //         isEqual = false;
    //         std::cout << "Mismatch found in group " << i << std::endl;
    //     }
    // }
    CHECK(isEqual);

    std::vector<int> expectedNums = {26, 2, 19, 13, 9, 0, 19, 15, 2, 22, 30, 13};

    std::vector<int> resultNums = gh.convertToNum(resultGroups);

    CHECK(expectedNums == resultNums);
}

TEST_CASE("Geohash") {
    Geohash gh(47.02345234657234, 19.036236263, 6);
    std::string resultGeo = gh.generateHash();
    std::string expectedGeo = "u2me90";
    CHECK(resultGeo == expectedGeo);
}
