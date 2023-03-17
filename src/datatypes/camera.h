#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "include.h"

class camera
{
    public:
        /* constructor */
        camera() { 
            float aspect_ratio = 16.0 / 9.0;
            float viewport_height = 2.0;
            float viewport_width = aspect_ratio * viewport_height;
            float focal_len = 1.0;

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
