#include "datatypes/color.h"

 void write_color(std::ostream &out, color c)
 {
     /* we need to translate the color from a float that is 0 < x < 1
      * to a integere that is 0 < x < 255
      */
    out << static_cast<int>(255.9999 * c.x()) << ' '
        << static_cast<int>(255.9999 * c.y()) << ' '
        << static_cast<int>(255.9999 * c.z()) << '\n';
 }
