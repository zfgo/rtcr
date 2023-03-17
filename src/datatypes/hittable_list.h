#ifndef _HITTABLE_LIST_H_
#define _HITTABLE_LIST_H_

#include "datatypes/hittable.h"

#include <memory>
#include <vector>


/* shared_ptr<type> is a pointer to some alloc'd type with ``reference
 * counting semantics''. Once the count goes to 0, the object is 
 * deleted.
 */
using std::shared_ptr;
using std::make_shared;

/* inherits from hittable
 *
 * Contains a vector that holds pointers to all hittables in the scene.
 */
class hittable_list : public hittable
{
    public:
        /* constructors
         */
        hittable_list() { }
        hittable_list(shared_ptr<hittable> object)
        {
            add(object);
        }

        /* clear the vector of hittables
         */
        void clear()
        {
            objects.clear();
        }
        
        /* add an object to the vector of hittables
         */
        void add(shared_ptr<hittable> object)
        {
            objects.push_back(object);
        }

        /* inherited fxn from the hittable class 
         */
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record* rec) const override;

    public:
        std::vector<shared_ptr<hittable>> objects;
};

/* implementation of hit, inherited from hittable.h
 * 
 * Loop through every object in the hittable list. For each object, 
 * check if the ray hits that object, and check if that hit was the
 * closest hit to the camera(?). If so, then update the hit record.
 */
bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    hit_record tmp;
    bool if_hit = false;
    float cur_closest = t_max;
    
    for (const auto& obj : objects) {
        if (obj->hit(r, t_min, cur_closest, tmp)) {
            if_hit = true;
            cur_closest = tmp.t;
            rec = tmp;
        }
    }

    return if_hit;
}

#endif /* _HITTABLE_LIST_H_ */
