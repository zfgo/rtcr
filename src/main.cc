#include <iostream>


int main(void)
{
    int i, j;
    float r, g, b;
    int ir, ig, ib;

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
            r = (float) i / (image_width - 1);
            g = (float) j / (image_height - 1);
            b = 0.25;

            /* static_cast<type> is used for when we want to reverse an
             * implicit conversion. It performs no runtime checks.
             */
            ir = static_cast<int>(255.9999 * r);
            ig = static_cast<int>(255.9999 * g);
            ib = static_cast<int>(255.9999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::cerr << "\nDone.\n";
    return 0;
}
