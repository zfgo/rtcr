#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include "datatypes/ray.h"

/* structure for each hit record (where a ray bounces off of an object.
 * The hit point, normal at that point, and time need to be recorded.
 */
struct hit_record {
    point3 p;
    vec3 normal;
    float t;
};

/* Because we have many rays bouncing off of many objects, we keep 
 * track of them in a large array
 */
class hittable 
{
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};


#endif /* _HITTABLE_H_ */
