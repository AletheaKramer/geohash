#include <cstdlib>
#include <iostream>

#include "../include/location.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <latitude> <longitude> <precision>" << std::endl;
        return 1;
    }

    try {
        double latitude = std::strtod(argv[1], nullptr);
        double longitude = std::strtod(argv[2], nullptr);
        int precision = std::atoi(argv[3]);

        Location geohash(latitude, longitude, precision);

        std::string hash = geohash.generateHash();
        std::cout << "Hash: " << hash << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error creating Location object: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}