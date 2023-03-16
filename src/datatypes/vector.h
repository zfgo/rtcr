#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>
#include <iostream>

// so we can use sqrt() instead of std::sqrt()
using std::sqrt;

/* TODO
 */
class vec3 {
    public:
        // TODO
}

/* add aliases so we can use vec3 for points and colors
 */
 using point3 = vec3; // 3D point (x, y, z)
 using color = vec3; // color (r, g, b)

#endif /* _VECTOR_H_ */
