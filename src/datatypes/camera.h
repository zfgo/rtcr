#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "include.h"

class camera
{
    public:
        /* constructor
         */
        camera(
            point3 lookfrom,        // point where the camera is looking from
            point3 lookat,          // point the camera is looking at 
            vector vup,             // up vector
            float vfov,             // vertical field of view in deg
            float aspect_ratio,
            float aperture,
            float focus_dist
        ) {
            float theta, h, 
                  viewport_height,
                  viewport_width;

            theta = deg_to_rad(vfov);
            h = tan(theta / 2.0);
            viewport_height = 2.0 * h;
            viewport_width = aspect_ratio * viewport_height;
            
            // creat w, u, v vectors (like in P1E)
            w = normalize(lookfrom - lookat);
            u = normalize(cross(vup, w));
            v = cross(w, u);
            
            origin = lookfrom;
            horizontal = focus_dist * viewport_width * u;
            vertical = focus_dist * viewport_height * v;
            lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - focus_dist * w;

            lens_radius = aperture / 2;
        }

        /* get a ray that shoots from the camera and goes through the
         * pixel located at image[u][v]
         */
        ray get_ray(float i, float j) const
        {
            vec3 rd = lens_radius * random_in_unit_disk();
            vec3 offset = u * rd.x() + v * rd.y();

            return ray(
                origin + offset, 
                lower_left_corner + i * horizontal + j * vertical - origin - offset
            );
        }

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vector u, v, w;
        float lens_radius;
};

#endif /* _CAMERA_H_ */
