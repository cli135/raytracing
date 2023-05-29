#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
  point3 p;
  vec3 normal;
  double t;
  bool front_face;

  // given the ray and the outward normal,
  // check the dot product and determine whether inside or outside
  inline void set_face_normal(const ray & r, const vec3 & outward_normal) {
    if (dot(r.direction(), outward_normal) < 0) {
      front_face = true; // ray coming from outside
      normal = outward_normal;
    }
    else {
      front_face = false; // ray coming from inside
      normal = -outward_normal;
    }
  }
};


// abstract hittable class
class hittable {
  public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record & rec) const = 0;
}

#endif