#ifndef _COLOR_H_
#define _COLOR_H_

#include "include.h"
#include <iostream>

/* write a color to a stream
 *
 * We need to translate the color from a float that is 0 < x < 1
 * to a integere that is 0 < x < 255, and then write it to the out 
 * stream.
 */
 void write_color(std::ostream &out, color c, int samples_per_pix);

#endif
