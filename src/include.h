#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include "datatypes/ray.h"
#include "datatypes/vector.h"

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.141592653589793;

inline double deg_to_rad(float deg)
{
    return deg * pi / 180.0;
}

#endif /* _INCLUDE_H_ */
