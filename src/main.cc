#include "datatypes/color.h"
#include "datatypes/ray.h"
#include "datatypes/vector.h"

#include <iostream>
#include <fstream>

bool hit_sphere(const point3& center, double radius, const ray& r)
{
    float a, b, c, discriminant;

    vec3 ray_to_sphere = r.origin() - center;
    
    a = dot(r.direction(), r.direction());
    b = 2.0 * dot(ray_to_sphere, r.direction());
    c = dot(ray_to_sphere, ray_to_sphere) - radius * radius;
    
    discriminant = b * b - 4.0 * a * c;

    return (discriminant > 0);
}

color ray_color(const ray& r)
{
    if (hit_sphere(point3(0.0, 0.0, -1.0), 0.5, r)) {
        // if the ray hits the sphere, return red, else return the blue gradient
        return color(1.0, 0.0, 0.0);
    }
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
    const float aspect_ratio = 16.0 / 9.0; // same aspect ration as a 1080p or 1440p screen
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    /* set up Camera */
    float viewport_height = 2.0;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_len = 1.0;

    point3 origin = point3(0.0, 0.0, 0.0);
    vec3 horizontal = vec3(viewport_width, 0.0, 0.0);
    vec3 vertical = vec3(0.0, viewport_height, 0.0);
    vector lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - vec3(0.0, 0.0, focal_len);

    /* set up output file */
    std::ofstream fp("img/out_03.ppm");

    /* Simple rendering loop */
    fp << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (j = image_height-1; j >= 0; --j) {

        /* \r denotes a carriage return
         * std::flush flushes the output sequence os
         */
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (i = 0; i < image_width; ++i) {
            float u = (float)i / (image_width - 1);
            float v = (float)j / (image_height - 1);
            
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);

            color c = ray_color(r);
            write_color(fp, c);
        }
    }

    fp.close();
    std::cerr << "\nDone.\n";

    return 0;
}
