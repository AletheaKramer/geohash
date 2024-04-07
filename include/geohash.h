#ifndef GEOHASH_H
#define GEOHASH_H
#include <string>

// c++ Implementation of Geohashing
// Algorithm derived from explaination video:
// https://www.youtube.com/watch?v=vGKs-c1nQYU&ab_channel=JosiahParry

class Geohash {
   public:
    Geohash(double longitude, double latitude, int precision);
    std::string generateHash() const;
    std::vector<int> encodeX();
    std::vector<int> encodeY();
    std::vector<int> interleave(std::vector<int> xbin, std::vector<int> ybin);
    std::vector<std::vector<int>> split(std::vector<int> interleaved);

   protected:
    double latitude;
    double longitude;
    int precision;

   private:
};

#endif