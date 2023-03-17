#include "include.h"
#include "datatypes/camera.h"
#include "datatypes/color.h"
#include "datatypes/hittable_list.h"
#include "datatypes/sphere.h"

#include <iostream>
#include <fstream>

/* render each pixel by calculating its color
 */
color ray_color(const ray& r, const hittable& world, int depth)
{
    hit_record rec;
    float t;

    // base case, where depth = 0 (bounce limit has been reached)
    if (depth <= 0) {
        return color(0.0, 0.0, 0.0);
    }

    // use 0.001 instead of 0.0 to add "tolerance" to floating point
    // errors. This also helps smooth the image, and reduce some of the
    // graininess
    if (world.hit(r, 0.001, infinity, rec)) {
        // random scattering, adding a random normalized vector. This
        // gives the property of higher ray scattering closer to the
        // normal, but with a more uniform distribution
        point3 target = rec.p + rec.normal + random_unit_vector();

        // decrement the depth in the recursive call
        return 0.5 * ray_color(ray(rec.p, target-rec.p), world, depth-1);
    }

    vec3 unit_dir = normalize(r.direction());
    t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main(void)
{
    int i, j, s;

    /* set up Image 
     * 
     * As is, we should have a 1920x1080 pixel image
     */
    const float aspect_ratio = 16.0 / 9.0; // same aspect ration as a 1080p or 1440p screen
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pix = 100;
    const int max_depth = 16;

    /* set up World */
    hittable_list world;
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5));
    world.add(make_shared<sphere>(point3(0.0, -100.5, -1), 100.0));

    /* set up Camera */
    camera cam;

    /* set up output file */
    std::ofstream fp("img/out_11.ppm");

    /* Simple rendering loop */
    fp << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (j = image_height-1; j >= 0; --j) {

        /* \r denotes a carriage return,
         * std::flush flushes the output sequence os
         */
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (i = 0; i < image_width; ++i) {
            color c(0.0, 0.0, 0.0);

            for (s = 0; s < samples_per_pix; ++s) {
                float u = ((float)i + random_float()) / (image_width - 1);
                float v = ((float)j + random_float()) / (image_height - 1);
                
                // get the ray from the camera
                ray r = cam.get_ray(u, v);

                // accumulate color
                c += ray_color(r, world, max_depth);
            }
            write_color(fp, c, samples_per_pix);
        }
    }

    fp.close();
    std::cerr << "\nDone.\n";

    return 0;
}
