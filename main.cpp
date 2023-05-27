#include "vec3.h"
#include "color.h"

#include <iostream>

using namespace std;

int main() {

  const int image_width = 256;
  const int image_height = 256;

  // header which denotes ASCII
  cout << "P3" << endl;

  // image dimensions
  cout << image_width << " " << image_height << endl;

  // max color
  cout << 255 << endl;

  for (int i = 0; i < image_width; i++) {
    
    // progress indicator
    std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;

    for (int j = 0; j < image_height; j++) {
      // current pixel at (i, j)
      vec3 current_pixel(j/static_cast<double>(image_height-1),
                         1.0 - i/static_cast<double>(image_width-1),
                         0.25);
      write_color(std::cout, current_pixel);
    }
  }

  std::cerr << "\nDone.\n";

}