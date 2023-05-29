#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>


// ok so this is a list of hittable objects
// that can be added to. I guess this is good for
// the growth of the program to manage many objects at once.
class hittable_list : public hittable {
  public:
    std::vector<std::shared_ptr<hittable>> objects;
  public:
    hittable_list() {}
    hittable_list(std::shared_ptr<hittable> object) {add(object);}

    // wrapping std::vector::clear() function
    void clear() {objects.clear();}

    // adding an object to the std::vector via a shared pointer
    void add(std::shared_ptr<hittable> object) {
      objects.push_back(object);
    }

    // preparing to override the hit function here.
    // probably to make it polymorphic and apply over the whole list of
    // hittable objects
    virtual bool hit(const ray & r, double t_min, double t_max, hit_record & rec) const override;

};

bool hittable_list::hit(const ray & r, double t_min, double t_max, hit_record & rec) const {
  hit_record test_rec;
  // did we hit anything at all over the whole hittable list
  bool hit_anything_at_all = false; // init
  double t_of_closest_hit_so_far = t_max; // init, we are finding min t here still in range

  // get the closest collision so that you do object occlusion
  // wow that is cool.

  for (const std::shared_ptr<hittable> object : objects) {
    // dereference the object shared pointer to get the actual object
    // and call its particular implementation of the hit function
    // because every object has a particular hitbox
    if (object->hit(r, t_min, t_of_closest_hit_so_far, test_rec)) {
      // success, hit within the time bounds
      // update min variables and bool flags
      hit_anything_at_all = true;
      t_of_closest_hit_so_far = test_rec.t;
      rec = test_rec;
      // test_rec will be populated with all
      // of the normal and point information
      // from that hit
      // so we save it
    }
    else {
      // fail, didn't hit
      continue;
    }
  }

  return hit_anything_at_all;

}

#endif