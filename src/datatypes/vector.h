#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>
#include <iostream>

// so we can use sqrt() instead of std::sqrt()
using std::sqrt;

/* vector member functions and data members
 */
class vector 
{
    /* member functions
     */
    public:
        /* constructors
         */
        vector() : e{0.0, 0.0, 0.0} { }
        vector(float e0, float e1, float e2) : e{e0, e1, e2} { }

        /* functions to get the x, y, or z parts of the vector
         */
        float x() const 
        {
            return e[0];
        }

        float y() const 
        {
            return e[1];
        }

        
        float z() const 
        {
            return e[2];
        }

        /* functions to get vector value at index i
         */
        float operator[](int i) const 
        {
            return e[i];
        }

        float& operator[](int i)
        {
            return e[i];
        }

        /* vector negation
         */
        vector operator-() const 
        {
            return vector(-e[0], -e[1], -e[2]);
        }

        /* implementation of the += operator
         */
        vector& operator+=(const vector &v)
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            
            return *this;
        }
        
        /* implementation of the *= operator for vectors and scalars
         */
        vector& operator*=(const float f)
        {
            e[0] *= f;
            e[1] *= f;
            e[2] *= f;

            return *this;
        }

        /* implemenation of the /= operator for vectors and scalars
         */
        vector& operator/=(const float f)
        {
            return *this *= 1 / f;
        }

        /* return the norm of a vector
         */
        float norm() const 
        {
            return sqrt(norm_squared());
        }

        /* helper fxn for norm
         */
        float norm_squared() const 
        {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }


    /* member variables
     */
    public: 
        float e[3];
};

/* add aliases so we can use vec3 for points and colors
 */
 using vec3 = vector; // 3D point (x, y, z)
 using point3 = vector; // 3D point (x, y, z)
 using color = vector; // color (r, g, b)

/* print a vector to a give stream
 */
inline std::ostream& operator<<(std::ostream &out, const vector &v);

/* add two vectors together
 */
inline vector operator+(const vector &u, const vector &v);

/* subtract two vectors from each other
 */
inline vector operator-(const vector &u, const vector &v);

/* multiply two vectors together
 */
inline vector operator*(const vector &u, const vector &v);

/* multiply a vector by a constant (scalar)
 */
inline vector operator*(float f, const vector &v);
inline vector operator*(const vector &v, float f);

/* divide a vector by a scalar
 */
inline vector operator/(vector v, float f);

/* calculate the dot product of a vector
 */
inline float dot(const vector &u, const vector &v);

#endif /* _VECTOR_H_ */
