#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include "datatypes/ray.h"
#include "datatypes/vector.h"

#include <cmath>        // sqrt, math fxns
#include <cstdlib>      // random numbers
#include <limits>       // infinity
#include <memory>       // shared_ptr and make_shared

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.141592653589793;

/* convert degrees to radians
 */
inline double deg_to_rad(float deg)
{
    return deg * pi / 180.0;
}

/* return a random real number x s.t. 0 <= x < 1
 */
inline float random_float()
{
    return rand() / (RAND_MAX + 1.0);
}

/* return a random real number x s.t. min <= x < max
 */
inline float random_float(float min, float max)
{
    return min + (max - min) * random_float();
}

/* ``clamp'' a value x between a minimum and a maximum
 */
inline float clamp(float x, float min, float max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

#endif /* _INCLUDE_H_ */
