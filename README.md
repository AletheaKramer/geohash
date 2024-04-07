# Geohash Implementation in C++
This a readable and lightweight implementation of [geohash encoding](https://en.wikipedia.org/wiki/Geohash). Geohashing is a widely used method for encoding latitude and longitude coordinates into strings without losing spatial context. The underlying principle divides the world into 32 areas, each labeled by a character from a base-32 set. The first character in a geohash specifies the area containing the given coordinates. This area is then subdivided into 32 smaller regions, with the next character in the geohash corresponding to one of these subdivisions. This process of division and character addition recurses, providing incredible precision. As a result, geohash strings can be compared through prefix matching to assess proximity, making geohashes extremely useful for a variety of spatial and geographical computations.
![geohash](https://github.com/AletheaKramer/geohash/assets/97807473/20ad2cb1-1ec8-4d14-9305-b409d82befb2)

## Inspiration
During a recent hackathon, I developed a [location-based mobile application](https://github.com/ameschen/pupspot) that enables users to interact with digital representations of dogs nearby. The concept was straightforward: to show dogs on the user's screen if they were within a certain range. However, one significant challenge we couldn't face in the 24 hours time frame was optimizing the comparison of user locations. It was clear that iterating through an entire database of latitude/longitude coordinates and calculating the distance for each was not a practical approach for scalability. This led me to discover geohashing, which seemed like an ideal solution for our problem.

Wanting to both strengthen my programming skills and gain a deeper understanding of the algorithm, I decided to implement geohashing myself. Furthermore, I'm keen to investigate whether a microservice architecture could be beneficial for this project. I'm excited about the potential to integrate this program with the application, opening up new possibilities for efficient location-based interactions.

## How I made this

I took the opportunity to develop a C++ program from scratch, aiming for a lightweight design by minimizing the use of external tools and libraries.

In pursuit of best practices for organizing C++ projects, I delved into researching and learned how to craft my own Makefile. I structured my program around a single class, encapsulating functionality within private/protected functions. Embracing a test-driven development approach, I discovered a straightforward testing library and constructed a comprehensive test suite to accompany my code.

Although the geohash algorithm is extensively documented, with numerous implementations readily available, a direct C++ version seemed elusive. Many existing versions were succinct, but my goal was to foster a profound understanding of the algorithm over merely achieving coding conciseness. A particularly informative [Youtube video](https://www.youtube.com/watch?v=vGKs-c1nQYU&ab_channel=JosiahParry) offered a detailed breakdown of the implementation, using R for demonstration. Inspired by this, I embarked on writing my own C++ implementation, closely following the computational steps outlined. 

## Next Steps
Moving forward, I'm eager to explore WebAssembly as a means to make the functionality accessible via a web interface. My subsequent goal is to determine the best way to integrate geohashing into my mobile app project—whether by utilizing an existing library or by embedding this streamlined version directly.
