#include "../include/geohash.h"

#include <cmath>
#include <iostream>

Geohash::Geohash(double longitude, double latitude, int precision) : latitude(latitude), longitude(longitude), precision(precision) {
}

std::string Geohash::generateHash() const {
    // Dummy implementation - replace with actual logic
    return "abc123";
}

std::vector<int> Geohash::encodeX() {
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

std::vector<int> Geohash::encodeY() {
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

std::vector<int> Geohash::interleave(std::vector<int> xbin, std::vector<int> ybin) {
    std::vector<int> interleaved;
    for (int i = 0; i < 32; i++) {
        interleaved.push_back(xbin[i]);
        interleaved.push_back(ybin[i]);
    }
    return interleaved;
}

std::vector<std::vector<int>> Geohash::split(std::vector<int> interleaved) {
    std::vector<std::vector<int>> groups;
    std::vector<int> group;

    for (int i = 0; i < 64; i++) {
        group.push_back(interleaved[i]);
        if (group.size() == 5 || i == 59) {
            groups.push_back(group);
            group.clear();
        }
    }

    return groups;
}
