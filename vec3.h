#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

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
      vec3(-e[0], -e[1], -e[2]);
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
      return std::sqrt(length_squared);
    }

    double length_squared() const {
      return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }


}

// Type aliasing for vec3
using point3 = vec3;  // 3D point
using color = vec3;   // RGB color

#endif