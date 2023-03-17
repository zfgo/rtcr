#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "include.h"

class camera
{
    public:
        /* constructor
         * 
         * vfov is the vertical field of view in degrees, and aspect 
         * ratio is the aspect ratio
         */
        camera(
            point3 lookfrom, 
            point3 lookat, 
            vector vup, 
            float vfov, 
            float aspect_ratio
        ) {
            float theta, h, 
                  viewport_height,
                  viewport_width;
            vector w, u, v;

            theta = deg_to_rad(vfov);
            h = tan(theta / 2.0);
            viewport_height = 2.0 * h;
            viewport_width = aspect_ratio * viewport_height;

            // creat w, u, v vectors (like in P1E)
            w = normalize(lookfrom - lookat);
            u = normalize(cross(vup, w));
            v = cross(w, u);
            
            origin = lookfrom;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - w;
        }

        /* get a ray that shoots from the camera and goes through the
         * pixel located at image[u][v]
         */
        ray get_ray(float u, float v) const
        {
            return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
        }

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
};

#endif /* _CAMERA_H_ */
