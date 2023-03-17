#include "datatypes/color.h"
#include "datatypes/ray.h"
#include "datatypes/vector.h"

#include <iostream>
#include <fstream>

color ray_color(const ray& r)
{
    vec3 unit_dir = normalize(r.direction());
    float t = 0.5 * (unit_dir.y() + 1.0);

    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main(void)
{
    int i, j;

    /* set up Image 
     * 
     * As is, we should have a 1920x1080 pixel image
     */
    const float aspect_ration = 16.0 / 9.0; // same aspect ration as a 1080p or 1440p screen
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    /* set up output file */
    std::ofstream fp("img/out_02.ppm");

    /* Simple rendering loop */
    fp << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (j = image_height-1; j >= 0; --j) {

        /* \r denotes a carriage return
         * std::flush flushes the output sequence os
         */
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (i = 0; i < image_width; ++i) {
            color c((float)i/(image_width - 1), (float)j / (image_height - 1), 0.25);
            write_color(fp, c);
        }
    }

    fp.close();
    std::cerr << "\nDone.\n";

    return 0;
}
