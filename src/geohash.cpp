#include "../include/geohash.h"

#include <bitset>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const char BASE32_CHARS[] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'j', 'k', 'm', 'n', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

Geohash::Geohash(double latitude, double longitude, int precision) : latitude(latitude), longitude(longitude), precision(precision) {
}

std::string Geohash::generateHash() const {
    std::string geohash;

    auto xbin = this->encodeX();
    auto ybin = this->encodeY();
    auto interleaved = this->interleave(xbin, ybin);
    auto groups = this->split(interleaved);
    std::vector<int> nums = this->convertToNum(groups);

    for (int num : nums) {
        geohash.push_back(BASE32_CHARS[num]);
    }

    return geohash.substr(0, precision);
}

std::vector<int> Geohash::encodeX() const {
    std::vector<int> xbin;
    double xvals[3] = {-180, 0, 180};

    for (int i = 0; i < 32; i++) {
        if (this->longitude >= xvals[1]) {
            xbin.push_back(1);
            xvals[0] = xvals[1];
        } else {
            xbin.push_back(0);
            xvals[2] = xvals[1];
        }
        xvals[1] = (xvals[0] + xvals[2]) / 2;
    }

    return xbin;
}

std::vector<int> Geohash::encodeY() const {
    std::vector<int> ybin;
    double yvals[3] = {-90, 0, 90};

    for (int i = 0; i < 32; i++) {
        if (this->latitude >= yvals[1]) {
            ybin.push_back(1);
            yvals[0] = yvals[1];
        } else {
            ybin.push_back(0);
            yvals[2] = yvals[1];
        }
        yvals[1] = (yvals[0] + yvals[2]) / 2;
    }

    return ybin;
}

std::vector<int> Geohash::interleave(std::vector<int> xbin, std::vector<int> ybin) const {
    std::vector<int> interleaved;
    for (int i = 0; i < 32; i++) {
        interleaved.push_back(xbin[i]);
        interleaved.push_back(ybin[i]);
    }
    return interleaved;
}

std::vector<std::vector<int>> Geohash::split(std::vector<int> interleaved) const {
    std::vector<std::vector<int>> groups;
    std::vector<int> group;

    for (int i = 0; i < 60; i++) {
        group.push_back(interleaved[i]);
        if (group.size() == 5) {
            groups.push_back(group);
            group.clear();
        }
    }

    return groups;
}

std::vector<int> Geohash::convertToNum(std::vector<std::vector<int>> groups) const {
    std::vector<int> result;

    for (auto group : groups) {
        std::stringstream ss;
        for (int bit : group) {
            ss << bit;
        }
        std::string binaryString = ss.str();
        int decimalNumber = std::stoi(binaryString, nullptr, 2);
        result.push_back(decimalNumber);
    }

    return result;
}
