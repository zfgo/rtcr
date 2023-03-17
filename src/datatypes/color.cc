#include "include.h"
#include "datatypes/color.h"

 void write_color(std::ostream &out, color c, int samples_per_pix)
 {
    float r, g, b,
          scale;

    // get the color components
    r = c.x();
    g = c.y();
    b = c.z();

    // divide each color by the number of samples
    scale = 1.0 / samples_per_pix;
    r *= scale;
    g *= scale;
    b *= scale;


    out << static_cast<int>(256 * clamp(r, 0.0, 0.9999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.9999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.9999)) << '\n';
 }
