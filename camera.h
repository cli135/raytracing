#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera {
  private:
    point3 origin; // where the camera is, I think
    point3 lower_left_corner; // hmm but i thought upper left corner?
    vec3 horizontal; // direction of horizontal across screen
    vec3 vertical; // direction of vertical across screen
  public:
    camera() {
      double aspect_ratio = 16.0 / 9.0;
      double viewport_height = 2.0; // hardcoded
      double viewport_width = viewport_height * aspect_ratio; // width is longer
      double focal_length = 1.0; // play with this
      // distance between projective plane and projective point

      origin = point3(0, 0, 0);
      horizontal = vec3(viewport_width, 0.0, 0.0);
      vertical = vec3(0.0, viewport_height, 0.0);
      // start at origin in center of screen, go left, then down, then into the screen
      // to get to the lower left corner
      // I guess we are going with the lower left corner of the screen
      lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    }

    // where u and v are the double parameters for how
    // far along the horizontal and vertical we are. in some ways like (i, j) ? 
    ray get_ray(double u, double v) {
      // start at lower left, go u horizontal and v vertical (I think both u and v are in [0, 1],)
      // and then you finally subtract off origin to get a vector rooted at origin and going
      // to that particular point represented by the coordinates (u, v)
      return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }
};

#endif