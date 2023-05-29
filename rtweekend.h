#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>

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

// Common headers

// since we have header guards
// on all .h files, we can just include
// them multiple times and there will be
// no problems since it will include only once
// due to header guards
#include "ray.h"
#include "vec3.h"


#endif