#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "rtweekend.h"
#include <iostream>

// still don't fully understand samples per pixel, what are we
// sending like more rays through each pixel and treating them
// each equal 1/n weight?
void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
  
  // x y z maps to r g b in point3, vec3 and color equivalency
  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();

  // Divide the color in each coordinate
  // by the total number of samples per pixel
  // implicit upcast to double because 1.0, so floating point division

  double scale = 1.0 / samples_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;
  
  // and gamma-correct for gamma=2.0
  r = sqrt(r);
  g = sqrt(g);
  b = sqrt(b);


  // Write the shifted color output, beteween [0, 255]
  // Why do we need to clamp here, just for safety I think?
  // Since they should already be in [0, 1] semantically?
  out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << " "
      << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << " "
      << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << "\n";
}

#endif