#ifndef LOCATION_H
#define LOCATION_H
#include <string>

// c++ Implementation of Geohashing
// Algorithm derived from explaination video:
// https://www.youtube.com/watch?v=vGKs-c1nQYU&ab_channel=JosiahParry

class Location {
   public:
    Location(double latitude, double longitude, int precision);
    std::string generateHash() const;
    double latitude;
    double longitude;
    int precision;

   protected:
    std::vector<int> encodeX() const;
    std::vector<int> encodeY() const;
    std::vector<int> interleave(std::vector<int> xbin, std::vector<int> ybin) const;
    std::vector<std::vector<int>> split(std::vector<int> interleaved) const;
    std::vector<int> convertToNum(std::vector<std::vector<int>> groups) const;
};

#endif