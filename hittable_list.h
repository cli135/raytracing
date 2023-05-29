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
    std::vector<shared_ptr<hittable>> objects;
  public:
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) {add(object);}

    // wrapping std::vector::clear() function
    void clear() {objects.clear();}

    // adding an object to the vector via a shared pointer
    void add(shared_ptr<hittable> object) {
      objects.push_back(object);
    }

    // preparing to override the hit function here.
    // probably to make it polymorphic and apply over the whole list of
    // hittable objects
    virtual bool hit(const ray & r, double t_min, double t_max, hit_record & rec) const override;

};

bool hittable_list::hit(const ray & r, double t_min, double t_max, hit_record & rec) const {
  hit_record temp_rec;
  // did we hit anything at all over the whole hittable list
  bool hit_anything_at_all = false; // init
  double t_of_closest_hit_so_far = t_max; // init, we are finding min t here still in range

  // for ()
}

#endif