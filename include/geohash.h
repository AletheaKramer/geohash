#ifndef GEOHASH_H
#define GEOHASH_H
#include <string>

// c++ Implementation of Geohashing
// Algorithm derived from explaination video:
// https://www.youtube.com/watch?v=vGKs-c1nQYU&ab_channel=JosiahParry

class Geohash {
   public:
    Geohash(double latitude, double longitude, int precision);
    std::string generateHash() const;
    std::vector<int> encodeX() const;
    std::vector<int> encodeY() const;
    std::vector<int> interleave(std::vector<int> xbin, std::vector<int> ybin) const;
    std::vector<std::vector<int>> split(std::vector<int> interleaved) const;
    std::vector<int> convertToNum(std::vector<std::vector<int>> groups) const;
    double latitude;
    double longitude;

   protected:
    int precision;

   private:
};

#endif