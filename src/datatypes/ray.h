#ifndef _RAY_H_
#define _RAY_H_

#include "datatypes/vector.h"

/* the ray class, consisting of a origin (where the ray began it's life),
 * and a direction, the direction towards which the ray is pointing.
 */
class ray {
    /* public member functions of the ray class
     */
    public: 
        /* constructors for the ray class
         */
        ray() {}

        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        /* getters for the class variables
         */
        point3 origin() const
        {
            return orig;
        }

        vec3 direction() const 
        {
            return dir;
        }

        /* find the position of a ray at some time t
         */
        point3 at(float t) const
        {
            return orig + (t * dir);
        }
    
    /* public member variables
     */
    public:
        point3 orig;
        vec3 dir;

};

#endif /* _RAY_H_ */
