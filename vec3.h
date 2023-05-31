#ifndef VEC3_H
#define VEC3_H



#include <cmath>
#include <iostream>

#include "rtweekend.h"

class vec3 {

  // instance variables
  public:
    double e[3];

  // methods:
  public:
    // constructors, initializer list
    vec3() : e{0, 0, 0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    // getters
    double x() const {return e[0];}
    double y() const {return e[1];}
    double z() const {return e[2];}

    // negate overload
    vec3 operator-() const {
      return vec3(-e[0], -e[1], -e[2]);
    }

    // what is the point of these two methods?
    // this is a cosmetic wrapper
    // for array access, so you can just
    // call brackets on the vec3 object now
    // and it will do a getter here
    double operator[](int i) const {
      return e[i];
    }
    // ohh this is for setter
    // non const means that we can call
    // brackets on the vec3 object
    // and this operator overload semantically
    // defines that to set / mutate the underlying
    // array by returning a reference to the underlying
    // double in that array (the exact same double,
    // because of reference)
    double& operator[](int i) {
      return e[i];
    }
    

    // plus gets (add assign) overload -- remember to return
    // a reference for chaining, like
    // (a += b) += c
    // take a const refernce to the rhs
    vec3& operator+=(const vec3 &rhs) {
      // you can't make a copy, you have to modify this object
      // in memory using the *this reference
      this->e[0] += rhs.x();
      this->e[1] += rhs.y();
      this->e[2] += rhs.z();
      return *this; // return this object as a whole
      // for any other chained references
    }

    // take a const refernce to the rhs
    vec3& operator*=(const double t) {
      // you can't make a copy, you have to modify this object
      // in memory using the *this reference
      this->e[0] *= t;
      this->e[1] *= t;
      this->e[2] *= t;
      return *this; // return this object as a whole
      // for any other chained references
    }

    // take a const refernce to the rhs
    vec3& operator/=(const double t) {
      // using the assign-multiply (times-gets)
      // method above
      return *this *= 1.0/t;
    }

    double length() const {
      return std::sqrt(length_squared());
    }

    double length_squared() const {
      return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    // random vec3 with components each between [0, 1)
    inline static vec3 random_vec() {
      return vec3(random_double(), random_double(), random_double());
    }

    // random vec3 with components each between [min, max)
    inline static vec3 random_vec(double min, double max) {
      return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

};

// Type aliasing for vec3
using point3 = vec3;  // 3D point
using color = vec3;   // RGB color

// vec3 utility functions

// methods outside of the class that also overload operators
// kind of like static methods

// no const modifiers supplied on methods here
// because they are not part of a class and therefore
// do not have any instance variables to keep const
// in the first place

// return an ostream reference
// you can't return ostream by value
// https://cplusplus.com/forum/beginner/243358/

// you need to return a reference to the same ostream
// in case things are chained to it later

inline std::ostream& operator<<(std::ostream & out, const vec3 & v) {
  // remember to put out at the beginning and return the whole string
  return out << v.x() << " " << v.y() << " " << v.z();
  // a more clear way of the binary fold left accumulation recursion
  // that the << and most binary argument operators are doing like +=
  // in this case
  // return (((out << v.x()) << " " << v.y()) << " " << v.z());
}


// vector addition
inline vec3 operator+(const vec3 & lhs, const vec3 & rhs) {
  return vec3(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

// vector subtraction
inline vec3 operator-(const vec3 & lhs, const vec3 & rhs) {
  return lhs + (-rhs);
}

// hadamard coordinate wise vector multiplcation
inline vec3 operator*(const vec3 & lhs, const vec3 & rhs) {
  return vec3(lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z());
}

// scalar before
inline vec3 operator*(double t, const vec3 & v) {
  return vec3(t * v.x(), t * v.y(), t * v.z());
}

// scalar after
inline vec3 operator*(const vec3 & v, double t) {
  // scalar multiplcation with vector commutes
  // so just turn it around and use the other definition
  return t * v;
}

// scalar division
inline vec3 operator/(const vec3 & v, double t) {
  // scalar multiplcation with vector commutes
  // and use the inverse (1.0/t) to scale down and do division
  return (1.0/t) * v;
}

// dot product
inline double dot(const vec3 & u, const vec3 & v) {
  return  u.x() * v.x() +
          u.y() * v.y() +
          u.z() * v.z();
}

// cross product
inline vec3 cross(const vec3 & u, const vec3 & v) {
  return vec3(u.y() * v.z() - u.z() * v.y(),
              u.x() * v.z() - u.z() * v.x(),
              u.x() * v.y() - u.y() * v.x());
}

// unit vector
inline vec3 unit_vector(const vec3 & v) {
  return v / v.length();
}

// random vector in the unit sphere
// by picking random points in [-1, 1]^3
// and repeating until we finally get one in
// the unit sphere
// it's a geometric random variable for the number
// of tries until it succeeds.
vec3 random_vec_in_unit_sphere() {
  vec3 test;
  do {
    test = vec3::random_vec(-1, 1); // some vector in [-1, 1]^3
  } while (test.length() >= 1);
  return test;
}

vec3 random_in_same_hemisphere(const vec3 & normal) {
  vec3 v = random_vec_in_unit_sphere();
  if (dot(v, normal) <= 0.0) {
    // try again
    return random_in_same_hemisphere();
  }
  else {
    // success!
    // literally just any vec
    // across the whole hemisphere works,
    // although I am not sure if it is a uniform
    // probability distribution
    // but many are the same.
    return v;
  }
}

#endif