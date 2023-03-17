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
        camera(float vfov, float aspect_ratio) {
            float theta, h, 
                  viewport_height,
                  viewport_width,
                  focal_len;

            theta = degrees_to_radians(vfov);
            h = tan(theta / 2.0);
            viewport_height = 2.0 * h;
            viewport_width = aspect_ratio * viewport_height;
            
            focal_len = 1.0;

            origin = point3(0.0, 0.0, 0.0);
            horizontal = vec3(viewport_width, 0.0, 0.0);
            vertical = vec3(0.0, viewport_height, 0.0);
            lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - vec3(0.0, 0.0, focal_len);
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
