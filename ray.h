#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
  public:
    point3 orig;
    vec3 dir;
  public:
    // need to provide default constructor
    // since we will add a nondefault constructor
    // i think
    ray() {}
    ray(const point3 & origin, const vec3 & direction) : orig(origin), dir(direction) {}

    // const getters
    point3 origin() const {return orig;}
    vec3 direction() const {return dir;}

    // const A + t * b calculation
    // i.e. linear interpolation with scalar t
    point3 at(double t) const {
      // using overloaded vec3 operators
      return orig + t * dir;
    }

}

#endif