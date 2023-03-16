#include "datatypes/color.h"
#include "datatypes/vector.h"
#include <iostream>

int main(void)
{
    int i, j;

    /* set up image dimensions */
    const int image_width = 256;
    const int image_height = 256;

    /* Simple rendering loop */
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (j = image_height-1; j >= 0; --j) {

        /* \r denotes a carriage return
         * std::flush flushes the output sequence os
         */
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (i = 0; i < image_width; ++i) {
            color c((float)i/(image_width - 1), (float)j / (image_height - 1), 0.25);
            write_color(std::cout, c);
        }
    }

    std::cerr << "\nDone.\n";
    return 0;
}
