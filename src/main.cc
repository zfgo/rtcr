#include <iostream>


int main(void)
{
    int i, j;
    float r, g, b;
    int ir, ig, ib;

    /* set up image dimensions */
    const int image_width = 256;
    const int image_height = 256;

    /* Simple rendering */
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (j = image_height-1; j >= 0; --j) {
        for (i = 0; i < image_width; ++i) {
            r = (float) i / (image_width - 1);
            g = (float) j / (image_height - 1);
            b = 0.25;

            ir = static_cast<int>(255.9999 * r);
            ig = static_cast<int>(255.9999 * g);
            ib = static_cast<int>(255.9999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    return 0;
}
