#ifndef _HITTABLE_LIST_H_
#define _HITTABLE_LIST_H_

#include "datatypes/hittable.h"

#include <memory>
#include <vector>


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
            add(object)
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

#endif /* _HITTABLE_LIST_H_ */
