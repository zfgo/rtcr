#ifndef _COLOR_H_
#define _COLOR_H_

#include "include.h"
#include <iostream>

/* write a color to a stream
 *
 * We need to translate the color from a float that is 0 < x < 1
 * to a integere that is 0 < x < 255, and then write it to the out 
 * stream.
 * 
 * The color will appear darker than we originally intend, because it
 * is not ``gamma corrected''. We fix this by taking the sqrt of the
 * color.
 */
 void write_color(std::ostream &out, color c, int samples_per_pix)
 {
    float r, g, b,
          scale;

    // get the color components
    r = c.x();
    g = c.y();
    b = c.z();

    // divide each color by the number of samples, and gamma correct
    // for gamma = 2.0 (raise to power of 1/gamma, or sqrt)
    scale = 1.0 / samples_per_pix;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0.0, 0.9999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.9999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.9999)) << '\n';
 }
#endif
