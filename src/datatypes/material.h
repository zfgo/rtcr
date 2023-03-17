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

/* class for diffuse lambertian surfaces, inheriting from the material
 * parent class
 */
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

            /* if the scatter direction is very close to 0, this can 
             * yield poor results (infinities, NaNs, etc.), so we catch
             * these ``degenerate'' cases
             */
            if (scatter_dir.near_zero()) {
                scatter_dir = rec.normal;
            }
            scattered = ray(rec.p, scatter_dir);
            attenuation = albedo;
            return true;
        }

    public:
        color albedo;
};

/* class for metallic reflective surfaces, inheriting from the material
 * parent class
 */
class metal : public material
{
    public:
        /* constructor */
        metal(const color& a) : albedo(a) { }

        /* metallic surfaces reflect light using the `reflect()` fxn
         * defined in vector.h
         */
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override 
        {
            vector reflected = reflect(normalize(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    public:
        color albedo;
};

#endif /* _MATERIAL_H_ */
