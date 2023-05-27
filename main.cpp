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

  // pixels rgb values
  double r = 0.0;
  double g = 1.0;
  double b = 63.0 / 255;
  for (int i = 0; i < image_width; i++) {
    
    // progress indicator
    std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;

    for (int j = 0; j < image_height; j++) {
      // current pixel at (i, j)
      int ir = static_cast<int>(255.99 * r);
      int ig = static_cast<int>(255.99 * g);
      int ib = static_cast<int>(255.99 * b);
      
      cout << ir << " " << ig << " " << ib << endl;

      // make sure to cast one operand
      // to avoid integer division
      r = 0.0 + j/static_cast<double>(image_height);
      g = 1.0 - i/static_cast<double>(image_width);
      b = b;
    }
  }

  std::cerr << "\nDone.\n";

}