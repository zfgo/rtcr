#include "datatypes/vector.h"

inline std::ostream& operator<<(std::ostream &out, const vector &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vector operator+(const vector &u, const vector &v)
{
    return vector(u[0]+v[0], u[1]+v[1], u[2]+v[2]);
}

inline vector operator-(const vector &u, const vector &v)
{
    return vector(u[0]-v[0], u[1]-v[1], u[2]-v[2]);
}

inline vector operator*(const vector &u, const vector &v)
{
    return vector(u[0]*v[0], u[1]*v[1], u[2]*v[2]);
}


inline vector operator*(float f, const vector &v)
{
    return vector(f*v[0], f*v[1], f*v[2]);
}

inline vector operator*(const vector &v, float f)
{
    return f * v;
}
