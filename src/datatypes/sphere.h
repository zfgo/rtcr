#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "include.h"
#include "datatypes/hittable.h"

/* because a sphere can be hit by a ray, it inherits from the hittable
 * class.
 */
class sphere : public hittable
{
    public:
        /* constructors 
         */
        sphere() { }
        sphere(point3 cen, float r, shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) { };

        /* inherited fxn from the hittable class 
         */
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

    public:
        point3 center;
        float radius;
        shared_ptr<material> mat_ptr;
};

/* this fxn calculates whether or not a ray hits a sphere, and returns 
 * a time, t, value that is the time at which the ray hits the sphere
 * 
 * There is a good description of the usefulness of discriminants as
 * well as the math going on here in "The Ray Tracer Challenge" by 
 * Jamis Buck in Chapter 5.
 */
bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    float 
        a, 
        half_b, 
        c, 
        discriminant, 
        root,
        sqrt_disc;

    // calculate discriminant
    vec3 ray_to_sphere = r.origin() - center;
    
    a = r.direction().norm_squared();
    half_b = dot(ray_to_sphere, r.direction());
    c = ray_to_sphere.norm_squared() - radius * radius;
    
    discriminant = half_b * half_b - a * c;

    if (discriminant < 0) {
        return false;
    }

    // if the discriminant > 0, then we need to find the nearest root
    sqrt_disc = sqrt(discriminant);
    root = (-half_b - sqrt_disc) / a;

    // the root needs to be within an ``acceptable range''
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrt_disc) / a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    // update the hit record
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif /* _SPHERE_H_ */
