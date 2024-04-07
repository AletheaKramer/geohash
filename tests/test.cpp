#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../include/location.h"

class TestableLocation : public Location {
   public:
    using Location::Location;  // Inherit constructors

    // Publicly expose private methods for testing
    using Location::convertToNum;
    using Location::encodeX;
    using Location::encodeY;
    using Location::interleave;
    using Location::split;
};

TEST_CASE("geohash helpers") {
    TestableLocation gh(47.02345234657234, 19.036236263, 6);

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

TEST_CASE("Location Simple Tests") {
    // tutorial exampls
    Location gh4719(47.02345234657234, 19.036236263, 6);
    std::string expectedGeo4719 = "u2me90";
    CHECK(gh4719.generateHash() == expectedGeo4719);

    // UBC cpsc building
    Location gh49123(49.26137917043368, -123.24890983809497, 8);
    std::string expectedGeo49123 = "c2b25rub";
    CHECK(gh49123.generateHash() == expectedGeo49123);

    // Kalepolepo Beach Park, Maui
    Location gh20156(20.765007448204823, -156.4588380355431, 12);
    std::string expectedGeo20156 = "8e8wpsnhuvfw";
    CHECK(gh20156.generateHash() == expectedGeo20156);

    // Mai Poina Beach Park, Maui (close by!!)
    Location ghclose(20.775500315035178, -156.4606945926068, 12);
    std::string expectedGeoClose = "8e8wpwhf19fq";
    CHECK(ghclose.generateHash() == expectedGeoClose);
}

TEST_CASE("Location Constructor Exception Tests") {
    // Test for latitude out of bounds
    CHECK_THROWS_AS(Location(91.0, 10.0, 5), std::out_of_range);
    CHECK_THROWS_AS(Location(-91.0, 10.0, 5), std::out_of_range);

    // Test for longitude out of bounds
    CHECK_THROWS_AS(Location(45.0, 181.0, 5), std::out_of_range);
    CHECK_THROWS_AS(Location(45.0, -181.0, 5), std::out_of_range);

    // Test for precision out of bounds
    CHECK_THROWS_AS(Location(45.0, 10.0, -1), std::out_of_range);
    CHECK_THROWS_AS(Location(45.0, 10.0, 13), std::out_of_range);

    CHECK_THROWS_WITH(Location(91.0, 10.0, 5), "Latitude must be between -90 and 90 degrees.");
    CHECK_THROWS_WITH(Location(45.0, 181.0, 5), "Longitude must be between -180 and 180 degrees.");
    CHECK_THROWS_WITH(Location(45.0, 10.0, -1), "Precision must be between 1 and 12.");
}
