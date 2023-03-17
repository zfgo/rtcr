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

        ray(const point3& origin, const vector& direction) : origin(origin), dir(direction) {}

};

#endif /* _RAY_H_ */
