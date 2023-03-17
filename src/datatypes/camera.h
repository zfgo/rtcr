#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "include.h"

class camera
{
    public:
        camera() { } // TODO

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
};

#endif /* _CAMERA_H_ */
