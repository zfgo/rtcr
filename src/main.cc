#include "include.h"
#include "datatypes/camera.h"
#include "datatypes/color.h"
#include "datatypes/hittable_list.h"
#include "datatypes/material.h"
#include "datatypes/sphere.h"

#include <iostream>
#include <fstream>
#include <string>

float lerp(float f_a, float f_b, float a, float b, float x)
{
    float t, f_x;

    if (a == b)
        return f_a;

    t = (x - a) / (b - a);
    f_x = f_a + (t * (f_b - f_a));

    return f_x;
}

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
        ray scattered;
        color attenuation;

        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            // random scattering, adding a random normalized vector. This
            // gives the property of higher ray scattering closer to the
            // normal, but with a more uniform distribution
            return attenuation * ray_color(scattered, world, depth-1);
        }
        return color(0.0, 0.0, 0.0);
    }

    vec3 unit_dir = normalize(r.direction());
    t = 0.5 * (unit_dir.y() + 1.0);
    //return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.1, 0.5);
}

hittable_list random_scene()
{
    int a, b;
    hittable_list world;

    auto ground_mat = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0.0, -1000.0, 0.0), 1000.0, ground_mat));

    for (a = -11; a < 11; ++a) {
        for (b = -11; b < 11; ++b) {
            float choose_mat = random_float();
            point3 center((float)a+0.9*random_float(), 0.2, b+0.9*random_float());

            if ((center - point3(4.0, 0.2, 0.0)).norm() > 0.9) {
                shared_ptr<material> sphere_mat;

                if (choose_mat < 0.8) {
                    // choose a diffuse material
                    color albedo = color::random_vec() * color::random_vec();
                    sphere_mat = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_mat));
                }
                else if (choose_mat < 0.95) {
                    // choose a metal
                    color albedo = color::random_vec(0.5, 1.0);
                    float fuzz = random_float(0.0, 0.5);
                    sphere_mat = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_mat));
                }
                else {
                    // choose a dielectric (glass)
                    sphere_mat = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_mat));
                }
            }
        }
    }

    auto mat1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0.0, 1.0, 0.0), 1.0, mat1));

    auto mat2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4.0, 1.0, 0.0), 1.0, mat2));

    auto mat3 = make_shared<metal>(color(0.8, 0.1, 0.1), 0.0);
    world.add(make_shared<sphere>(point3(4.0, 1.0, 0.0), 1.0, mat3));

    return world;
}

camera get_cam_for_random_scene(float aspect_ratio)
{
    /* set up Camera */
    point3 lookfrom(13.0, 3.0, 3.0);
    point3 lookat(0.0, 0.0, 0.0);
    vec3 vup(0.0, 1.0, 0.0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;
    float vfov = 20.0;

    camera cam(
        lookfrom,
        lookat,
        vup,
        vfov,
        aspect_ratio,
        aperture,
        dist_to_focus
    );

    return cam;
}

camera get_cam_for_4_spheres(float aspect_ratio, point3 lookfrom, float vfov)
{
    /* set up Camera */
    //point3 lookfrom(4.0, 0.0, 2.75);
    //point3 lookfrom(1.5, 0.0, 1.03125);
    point3 lookat(0.0, 0.0, 0.0);
    vec3 vup(0.0, 1.0, 0.0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;
    //float vfov = 20.0;
    //float vfov = 70.0;

    camera cam(
        lookfrom,
        lookat,
        vup,
        vfov,
        aspect_ratio,
        aperture,
        dist_to_focus
    );

    return cam;
}

hittable_list four_spheres_scene()
{
    hittable_list world;
    auto sphere_mat = make_shared<metal>(color(0.7, 0.7, 0.7), 0.0);
    float radius = 1.0;
    float inv_sqrt2 = 1.0 / sqrt(2.0);

    world.add(make_shared<sphere>(point3( 1.0,  0.0, -inv_sqrt2), radius, sphere_mat));
    world.add(make_shared<sphere>(point3(-1.0,  0.0, -inv_sqrt2), radius, sphere_mat));
    world.add(make_shared<sphere>(point3( 0.0,  1.0,  inv_sqrt2), radius, sphere_mat));
    world.add(make_shared<sphere>(point3( 0.0, -1.0,  inv_sqrt2), radius, sphere_mat));

    return world;
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
    const int samples_per_pix = 256;
    const int max_depth = 16;

    /* set up World */
    hittable_list world = four_spheres_scene();

    const int n_imgs = 100;
    const float vfov_a = 20.0;
    const float vfov_b = 70.0;
    const float vfov_diff = vfov_b - vfov_a;
    const float vfov_increment = vfov_diff / n_imgs;
    const point3 lookfrom_a(4.0, 0.0, 2.75);
    const point3 lookfrom_b(1.5, 0.0, 1.03125);
    const point3 lookfrom_diff = lookfrom_b - lookfrom_a;
    const point3 lookfrom_increment = lookfrom_diff / n_imgs;

    for (int n = 0; n < n_imgs; ++n) {
        std::cout << "working on frame " << n << '\n';
        /* set up Camera */
        camera cam = get_cam_for_4_spheres(
            aspect_ratio, 
            lookfrom_a+(lookfrom_increment*n),
            vfov_a+(vfov_increment*n)
        );

        /* set up output file */
        std::string fname = "frames/out_";
        fname += std::to_string(n);
        fname += ".ppm";

        std::ofstream fp(fname);

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
    }

    std::cerr << "\nDone.\n";

    return 0;
}
