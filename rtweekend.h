#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>

#include <random>

// std::shared_ptr
// std::make_shared
// std::sqrt

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utilty functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}


inline double random_double() {
  // Returns a random real in [0, 1)
  return rand() / (RAND_MAX + 1.0); // 1 excluded
}

inline double random_double(double min, double max) {
  // Returns a random real in [min, max)
  return min + random_double() * (max - min);
}

// alternate implemention of random_double()
// inline random_double() {
//   static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//   static std::mt19937 generator;
//   return distribution(generator);
// }

// basically like clamping x to get within min and max,
// rounding up or down as necessary to get it into this range
inline double clamp(double x, double min, double max) {
  if (x > max) {
    return max;
  }
  else if (x < min) {
    return min;
  }
  else {
    return x;
  }
}


// Common headers

// since we have header guards
// on all .h files, we can just include
// them multiple times and there will be
// no problems since it will include only once
// due to header guards
#include "ray.h"
#include "vec3.h"


#endif