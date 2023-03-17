#ifndef _RAY_H_
#define _RAY_H_

#include "datatypes/vector.h"

/* TODO
 */
class ray {
    /* public member functions of the ray class
     */
    public: 
        /* constructors for the ray class
         */
        ray() {}

        ray(const point3& origin, const vec3& direction) : origin(origin), dir(direction) {}

        /* getters for the class variables
         */
        point3 origin() const
        {
            return origin;
        }

        vec3 direction() const 
        {
            return dir;
        }

};

#endif /* _RAY_H_ */
