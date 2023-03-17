#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "datatypes/hittable.h"
#include "datatypes/vector.h"

/* because a sphere can be hit by a ray, it inherits from the hittable
 * class.
 */
class sphere : public hittable
{
    public:
        sphere() {}


    public:
        point3 center;
        float radius;
};
    

#endif /* _SPHERE_H_ */
