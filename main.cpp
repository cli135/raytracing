#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "camera.h"
#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

using namespace std;

// we will pass in a huge world object right
// yeah world is actually a hittable list
// now instead of hardcoding a sphere check
// we are checking collisions to color points
// for all objects in the hittable_list world
// so we basically have many sphere checks for all
// objects in world
color ray_color(const ray& r, const hittable & world) {
  hit_record rec;
  // checking collisions with all objects in world
  // and saving the closest collision hit event in rec
  // such that it is in the time bound 0 and infinity.
  // and we update the max infinity to be the closest such one so far
  // so that infinity acts like the min initialized and we are finding
  // min hit distance and that occurrence of the collision.
  if (world.hit(r, 0, infinity, rec)) {
    // color scaling based on normal of the collision
    return 0.5 * (rec.normal + color(1, 1, 1));
  }
  // below code is now in hittable.h, sphere.h
  // auto t = hit_sphere(point3(0,0,-1), 0.5, r);
  // if (t > 0.0) {
  //     vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
  //     return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
  // }
  
  // background color gradient based on y coordinate of ray
  // ray direction unit vector
  vec3 unit_direction = unit_vector(r.direction());
  double t = 0.5*(unit_direction.y() + 1.0);
  return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

  // image dimensions
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100; // wow that is a lot per pixel
  // like is each a random ray being sent through that pixel in a random
  // direction??? well this is certainly diffuse light or at least
  // antialiasing. A lot of randomness done here


  // world
  hittable_list world;
  // world.add(make_shared<sphere>(point3(0, 0, -0.75), 0.5));
  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  
  // normal ground, tangent spheres
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
  
  // or, occlude with a sphere to make it stuck in ground
  // and light hits the ground first instead of the rainbow sphere
  // world.add(make_shared<sphere>(point3(0, -100, -1), 100));
  
  // TODO: why is the camera like already tilted up,
  // is it because of the focal length. at least the 0.5 measurements
  // seem fine
  // focal length is important though.
  // need a real time rendering for ppm. or any image format.
  // like khan academy.

  // camera
  camera cam;

  // rendering

    // header which denotes ASCII
    cout << "P3" << endl;
    // image dimensions
    cout << image_width << " " << image_height << endl;
    // max color
    cout << 255 << endl;
    // std::cout << "P3\n" << image_width << " " << image_height << "\n" << 255 << "\n";
  for (int j = image_height - 1; j >= 0; j--) {
  
    
    // progress indicator
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

    for (int i = 0; i < image_width; i++) {
  
      // current pixel at (i, j)

      color pixel_color(0, 0, 0);
      // Ok so we're indexing literally into the pixel
      // itself and going more granular using floating point arithmetic
      // and we're doing this samples_per_pixel number of times
      for (int s = 0; s < samples_per_pixel; s++) {
        // what if random_double() makes it exceed 1 as as final ratio u or v
        double u = (static_cast<double>(i) + random_double()) / (image_width - 1.0);
        double v = (static_cast<double>(j) + random_double()) / (image_height - 1.0);
        ray r = cam.get_ray(u, v); // already adjusted granular into that pixel
        // sum up the pixel color and then find the average of the accumulated sum
        // to average out among the samples_per_pixel samples per every pixel
        // like each weighted equally, like a nice random couple of rays per pixel.
        // So we get some blur on the boundaries because some are bound to miss the
        // edge of the sphere and veer off left or right and that allows for some
        // randomness to smooth out and blur out the edges and not make it so deterministic
        // and sharp edges each time but allow fate to determine like where the edge is
        // by chance each time with random_double() little adjustments to the end
        // coordinates of the ray (u, v).
        pixel_color += ray_color(r, world); // find logic for whether we intersect
        // with an object and find the closest such intersection to simulate
        // object occlusion, and return that color - i.e. rendering the closest
        // surface's color, as a superficial gild on top of all of the 3d vector math
        // and structures that we are calculating with point/spot check formulas.
      }
      write_color(std::cout, pixel_color, samples_per_pixel);
    }
  }

  std::cerr << "\nDone.\n";

}