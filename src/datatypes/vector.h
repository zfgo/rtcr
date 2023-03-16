#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>
#include <iostream>

// so we can use sqrt() instead of std::sqrt()
using std::sqrt;

/* TODO
 */
class vec3 {
    /* member functions
     */
    public:
        /* constructors
         */
        vec3() : e{0.0, 0.0, 0.0} {}
        vec3(float e0, float e1, float e2) : e{e0, e1, e2} {}

        /* functions to get the x, y, or z parts of the vector
         */
        double x() const {
            return e[0];
        }
        double y() const {
            return e[1];
        }
        double z() const {
            return e[2];
        }

    /* member variables
     */
    public: 
        double e[3];
}

/* add aliases so we can use vec3 for points and colors
 */
 using point3 = vec3; // 3D point (x, y, z)
 using color = vec3; // color (r, g, b)

#endif /* _VECTOR_H_ */
