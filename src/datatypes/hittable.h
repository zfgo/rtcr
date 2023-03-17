#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include "include.h"

class material; // forward declaration

/* structure for each hit record (where a ray bounces off of an object.
 * The hit point, normal at that point, and time need to be recorded.
 */
struct hit_record {
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    float t;
    bool front_face;

    /* when we have a ray that hits an object, we need to know where
     * that ray bounces to, but some rays bounce around the insides of
     * objects (e.g., a glass ball).
     * 
     * This function allows us to calculate inside and outside hits
     */
    inline void set_face_normal(const ray& r, const vec3& outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    };
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
