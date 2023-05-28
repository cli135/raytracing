#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>

using namespace std;

color ray_color(const ray & r) {
  vec3 unit_direction = unit_vector(r.direction());
  double t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

  // image dimensions
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);

  // camera
  double viewport_height = 2.0;
  double viewport_width = viewport_height * aspect_ratio;
  double focal_length = 1.0; // distance between projective plane and camera point

  point3 origin = point3(0, 0, 0);
  vec3 horizontal = vec3(viewport_width, 0, 0);
  vec3 vertical = vec3(0, viewport_height, 0);
  point3 upper_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

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
      double a = static_cast<double>(i) / (image_width - 1);
      double b = static_cast<double>(j) / (image_height - 1);
      ray r = ray(origin, upper_left_corner + a * horizontal + b * vertical - origin);
      color pixel_color = ray_color(r);
      // vec3 current_pixel(j/static_cast<double>(image_height-1),
                        //  1.0 - i/static_cast<double>(image_width-1),
                        //  0.25);
      // write_color(std::cout, current_pixel);
      write_color(std::cout, pixel_color);
    }
  }

  std::cerr << "\nDone.\n";

}