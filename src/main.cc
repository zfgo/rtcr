#include "datatypes/color.h"
#include "datatypes/ray.h"
#include "datatypes/vector.h"

#include <iostream>
#include <fstream>

/* this fxn calculates whether or not a ray hits a sphere, and returns 
 * a time, t, value that is the time at which the ray hits the sphere
 */
float hit_sphere(const point3& center, double radius, const ray& r)
{
    float a, half_b, c, discriminant, t;

    vec3 ray_to_sphere = r.origin() - center;
    
    a = r.direction().length_squared();
    half_b = dot(ray_to_sphere, r.direction());
    c = ray_to_sphere.length_squared() - radius * radius;
    
    discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0) {
        return -1.0;
    }
    else {
        t = (-half_b - sqrt(discriminant)) / a;

        return t;
    }
}

/* calculate the color of a ray
 */
color ray_color(const ray& r)
{
    float t;

    t = hit_sphere(point3(0.0, 0.0, -1.0), 0.5, r);

    if (t > 0.0) {
        vec3 N = normalize(r.at(t) - vec3(0.0, 0.0, -1.0));
        return 0.5 * color(N.x()+1.0, N.y()+1.0, N.z()+1.0);
    }

    vec3 unit_dir = normalize(r.direction());
    t = 0.5 * (unit_dir.y() + 1.0);

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
    std::ofstream fp("img/out_05.ppm");

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
