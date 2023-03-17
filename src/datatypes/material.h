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
        metal(const color& a, float f) : albedo(a), fuzz(f < 1.0 ? f : 1.0) { }

        /* metallic surfaces reflect light using the `reflect()` fxn
         * defined in vector.h
         */
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override 
        {
            vector reflected = reflect(normalize(r_in.direction()), rec.normal);
            // add fuzz to  create "fuzzy" reflections (i.e., a rough
            // metal ball (not a perfect mirror))
            scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
            attenuation = albedo;

            return (dot(scattered.direction(), rec.normal) > 0);
        }

    public:
        color albedo;
        float fuzz; 
};

/* class for dielectrics (materials that refract light), inheriting from
 * the material parent class
 */
class dielectric : public material
{
    public:
        /* constructor */
        dielectric(float refractive_ind) : ir(refractive_ind) { }

        /* dielectrics refract light using the `refract()` fxn 
         * defined in vector.h
         */
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override 
        {
            float refraction_ratio,
                  cos_theta, 
                  sin_theta;
            bool cannot_refract;
            vector dir;

            attenuation = color(1.0, 1.0, 1.0);
            refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

            vector unit_dir = normalize(r_in.direction());
            cos_theta = fmin(dot(-unit_dir, rec.normal), 1.0);
            sin_theta = sqrt(1.0 - cos_theta * cos_theta);

            /* a ray can not refract if it is inside denser material 
             * and the angle of incidence is beyond a certain angle. In
             * this case, the ray can only reflect (This is called 
             * Total Internal Reflection)
             */
            cannot_refract = refraction_ratio * sin_theta > 1.0;

            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_float()) {
                dir = reflect(unit_dir, rec.normal);
            }
            else {
                dir = refract(unit_dir, rec.normal, refraction_ratio);
            }

            scattered = ray(rec.p, dir);

            return true;
        }
        
    public:
        float ir; // refractive index

    private:
        /* private function that approximates reflectance using the 
         * Schlick approximation
         */
        static float reflectance(float cos_theta, float refractive_ind)
        {
            float r0 = (1.0 - refractive_ind) / (1.0 + refractive_ind);
            r0 = r0 * r0;

            return r0 + (1.0 - r0) * pow((1.0 - cos_theta), 5.0);
        }
};

#endif /* _MATERIAL_H_ */
