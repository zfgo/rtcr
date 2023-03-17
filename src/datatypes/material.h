#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "include.h"

struct hit_record; // forward declaration

class material
{
    public:
        /* fxn to be implemented by base classes
         */
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const = 0;
};

#endif /* _MATERIAL_H_ */
