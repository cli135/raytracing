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
color ray_color(const ray& r, const hittable & world, const int bounce_recursion_depth) {
  
  double percent_of_light_reflected_off_bounce = 0.5;

  hit_record rec;
  // checking collisions with all objects in world
  // and saving the closest collision hit event in rec
  // such that it is in the time bound 0 and infinity.
  // and we update the max infinity to be the closest such one so far
  // so that infinity acts like the min initialized and we are finding
  // min hit distance and that occurrence of the collision.

  // we start t_min at 0.001 to avoid immediate collisions
  // if light hits a jagged surface off of what it immediately reflected off of
  // due to some floating point artifact or computational error.
  // this is called preventing shadow acne and I think it is an unintended
  // geometric artifact of some surfaces' geometry I think
  if (world.hit(r, 0.001, infinity, rec)) {
    if (bounce_recursion_depth <= 0) {
      return 0.5 * (rec.normal + color(1, 1, 1)); 
    }
    // color scaling based on normal of the collision
    // to get a nice rainbow look all around the surface
    // of the sphere
    // return 0.5 * (rec.normal + color(1, 1, 1));
    else {
      // bounce and do recursion on ray_color to get that
      // bounced color. But extending the solution here looks
      // like doing a 0.5 exponential mulitplicative drive down
      // of the color intensity so it gets dimmer with each bounce,
      // i.e. some color is absorbed and with more bounces it fades to black.
      // I wonder what this will look like lol
      
      
      // assuming that all light rays come from outside the sphere, so we use
      // + n meaning that the reflected ray is going out away from the center of the sphere
      // always (this is an assumption)

      // oops, I messed up tip to tail vector addition
      // below is the correct formula
      // vec3 target = rec.p + unit_vector(rec.normal) + random_vec_in_unit_sphere();

      // picking points in the unit sphere and then normalizing those
      // in order to pick points on the unit sphere
      // and achieve the true lambertian
      vec3 target = rec.p + unit_vector(rec.normal) + unit_vector(random_vec_in_unit_sphere());


      // hemispherical scattering (not quite uniform but hemispherical i think??)
      // there is a difference between these three but not quite sure what it is.
      // need to diagram more closely.
      // vec3 target = rec.p + random_in_same_hemisphere(rec.normal);



      
      // new beam of reflected light starts at collision site rec.p
      // and goes in any random direction in the unit sphere, which is
      // unit_vector(rec.normal) + random_vec_in_unit_sphere()
      return percent_of_light_reflected_off_bounce *
            ray_color(ray(rec.p, target - rec.p), world, bounce_recursion_depth - 1);
    }
  }

// wait there is no recursion if you just hit the sky directly
// you're done, there is no reflection here. otherwise it'd be all muddly
// and stuff would reflect off of literally everything even the air lol
// wait air is not a collision check so we'd be good i think
// wait that's the point we'd just keep reflecting and there wouldn't
// even be a normal to reflect off of it no collision rec and rec.normal
  // if (bounce_recursion_depth <= 0) {
    // second base case: background
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0); 
  // }
  // else {
  //   return percent_of_light_reflected_off_bounce *
  //           ray_color(ray(rec.p + unit_vector(rec.normal), random_vec_in_unit_sphere()), world, bounce_recursion_depth - 1);
  // }

  // below code is now in hittable.h, sphere.h
  // auto t = hit_sphere(point3(0,0,-1), 0.5, r);
  // if (t > 0.0) {
    ////where this is the center of the sphere vvvvv
  //     vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
  //     return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
  // }
  
  // background color gradient based on y coordinate of ray
  // ray direction unit vector
  
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

  // increasing this bounce depth causes program
  // to take significantly longer, but it increases
  // shadow difference because it allows crevices to
  // be shadows while other light can bounce away
  const int max_bounce_recursion_depth = 20;


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
        pixel_color += ray_color(r, world, max_bounce_recursion_depth); // find logic for whether we intersect
        // with an object and find the closest such intersection to simulate
        // object occlusion, and return that color - i.e. rendering the closest
        // surface's color, as a superficial gild on top of all of the 3d vector math
        // and structures that we are calculating with point/spot check math formulas
        // as a kind of mathematical yes/no hitbox computed on the fly and never stored
        // in memory besides the code formula used to produce it and the result temporarily
        // generated at runtime.

        // antialiasing is having multiple small randomly perturbed rays per pixel
        // and averaging those pixels out
        // to make it a little more random and smooth out the sharp edges that are
        // too deterministic
      }
      write_color(std::cout, pixel_color, samples_per_pixel);
    }
  }

  std::cerr << "\nDone.\n";

}