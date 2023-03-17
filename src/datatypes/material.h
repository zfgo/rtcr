#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "include.h"

struct hit_record; // forward declaration

class material
{
    public:
        /* fxn to be implemented by base classes
         */
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material
{
    public:
        /* constructor */
        lambertian(const color& a) : albedo(a) { }


        /* implement the scatter fxn inherited from the parent class.
         * This function calculates a random scattering of a ray on a 
         * lambertian surface
         */
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override 
        {
            vector scatter_dir = rec.normal + random_unit_vector();
            scattered = ray(rec.p, scatter_dir);
            attenuation = albedo;
            return true;
        }

};

#endif /* _MATERIAL_H_ */
