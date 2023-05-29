#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
  public:
    point3 center;
    double radius;
  public:
    sphere() {}
    sphere(point3 cen, double r) : center(cen), radius(r) {};

    virtual bool hit(const ray & r, double t_min, double t_max, hit_record & rec) const override;
};

// defining the custom hitbox for an object,
// in this case a sphere
// using the formula (P - C) . (P - C) == r * r
// where P(t) = A + t * b
// basically space diagonal pythagorean theorem to define
// points precisely on a sphere
bool sphere::hit(const ray & r, double t_min, double t_max, hit_record & rec) const {
  // return true or false
  // quadratic coeffiecients
  vec3 oc = r.origin() - center; // (A - C)
  double a = dot(r.direction(), r.direction()); // (b . b)
  double b = 2.0 * dot(r.direction(), oc); // (2 * b . (A - C))
  double c = dot(oc, oc) - radius * radius; // (A - C) . (A - C) - r^2
  double discriminant = b * b - 4 * a * c; // quadratic
  if (discriminant < 0) {
    return false; // ray missed sphere
  }
  // Find the nearest root in the acceptable range
  double first_root = (-b - std::sqrt(discriminant)) / (2 * a);
  double second_root = (-b + std::sqrt(discriminant)) / (2 * a);

  // first root is closer and gets priority
  // but why do we choose the more negative root, I don't understand.
  // instead of closest in absolute value to 0.
  double root = first_root;
  if (root < t_min || t_max < root) {
    root = second_root;
    if (root < t_min || t_max < root) {
      return false; // both roots out of t range
    }
  }
  rec.t = root; // saving the collision time
  rec.p = r.at(root);
  // making the normal vector a unit vector
  vec3 outward_normal = (rec.p - center) / radius;
  // if (dot(rec.normal, rec.p))
  // not all rays have origin as A, because they bounce
  // so you need to consider the direction of the ray
  // and check its dot product with the surface normal
  rec.set_face_normal(r, outward_normal);

  return true;
}

#endif