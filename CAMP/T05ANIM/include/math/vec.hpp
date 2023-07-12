/* FILE NAME: vec.h
 * PROGRAMMER: AD6
 * LAST UPDATE: 11.07.2018
 * PURPOSE
 */

#ifndef __VEC_H_
#define __VEC_H_

#include "mthdef.hpp"
#include <iostream>

namespace mth
{
/* Vector class template */
template <Number T>
struct Vec
{
  T x{};
  T y{};
  T z{};


  /* Vector constructor method */
  Vec(T a, T b, T c) : x(a), y(b), z(c)
  {}

  /* Vector constructor method with similar coordinates */
  explicit Vec(T a = T{}) : x(a), y(a), z(a)
  {}


  /* Vector add and equal vector (reload +=) function
   * ARGUMENTS:
   *   - link to vector:
   *       vec<T> &V;
   * RETURNS:
   *       (vec<T> &) link to result vector;
   */
  Vec &operator+=(const Vec &V)
  {
    x += V.x;
    y += V.y;
    z += V.z;
    return *this;
  } /* End of 'operator+=' function */

  T operator[](int i) const
  {
    return *(&x + i);
  }

  T &operator[](int i)
  {
    return *(&x + i);
  }

  /* Vector substraction and equal vector (reload -=) function
   * ARGUMENTS:
   *   - link to Vector:
   *       vec<T> &V;
   * RETURNS:
   *       (vec<T> &) link to result vector;
   */
  Vec &operator-=(const Vec &V)
  {
    x -= V.x;
    y -= V.y;
    z -= V.z;
    return *this;
  } /* End of 'operator+=' function */

  Vec &operator*=(const Vec &V)
  {
    x *= V.x;
    y *= V.y;
    z *= V.z;
    return *this;
  }

  T length(VOID) const
  {
    return sqrt(x * x + y * y + z * z);
  }

  T dot(const Vec &V) const
  {
    return x * V.x + y * V.y + z * V.z;
  }

  Vec cross(const vec &V) const
  {
    return vec(y * V.z - z * V.y, z * V.x - x * V.z, x * V.y - y * V.x);
  }

  vec<T> operator*(const vec<T> &V) const
  {
    return vec<T>(x * V.x, y * V.y, z * V.z);
  }

  vec<T> operator*(const matr<T> &M) const
  {
    T w = x * M.A[0][3] + y * M.A[1][3] + z * M.A[2][3] + M.A[3][3];

    return vec<T>((M.A[0][0] * x + M.A[1][0] * y + M.A[2][0] * z + M.A[3][0]) / w,
                  (M.A[0][1] * x + M.A[1][1] * y + M.A[2][1] * z + M.A[3][1]) / w,
                  (M.A[0][2] * x + M.A[1][2] * y + M.A[2][2] * z + M.A[3][2]) / w);
  }

  /* Vector transform function.
   * ARGUMENTS:
   *   - transform matrix:
   *       MATR M;
   * RETURNS:
   *   (VEC) result vector.
   */
  vec<T> VecTrans(const matr<T> &M) const
  {
    return vec<T>(M.A[0][0] * x + M.A[0][1] * y + M.A[0][2] * z,
                  M.A[1][0] * x + M.A[1][1] * y + M.A[1][2] * z,
                  M.A[2][0] * x + M.A[2][1] * y + M.A[2][2] * z);
  } /* End of 'VecTrans' function */

  vec<T> operator*(const T number) const
  {
    return vec<T>(x * number, y * number, z * number);
  }

  vec<T> operator/(const T number) const
  {
    return vec<T>(x / number, y / number, z / number);
  }

  vec<T> &operator*=(const T number)
  {
    x *= number;
    y *= number;
    z *= number;
    return *this;
  }

  vec<T> &operator/=(const T number)
  {
    x /= number;
    y /= number;
    z /= number;
    return *this;
  }

  vec<T> Normalize(VOID) const
  {
    T len = !(*this);
    vec<T> V = *this;
    if (len == 0 || len == 1)
      return V;
    V /= len;
    return V;
  }

  static vec<T> Normalizing(const vec<T> &V)
  {

    T len = !V;
    if (len == 0 || len == 1)
      return V;
    return V / len;
  }

  T Length2(VOID)
  {
    return (*this) & (*this);
  }

  T Distance(const vec<T> &V)
  {
    return !(*this - V);
  }
};

template <class T>
class vec2
{
protected:
  T x, y;

public:
  /* Vector constructor method */
  vec2(T a, T b) : x(a), y(b)
  {}

  /* Vector constructor method with similar coordinates */
  explicit vec2(T a = 0) : x(a), y(a)
  {}

  /* Vector add vector (reload +) function
   * ARGUMENTS:
   *   - link to vector:
   *       vec2<T> &V;
   * RETURNS:
   *       (vec2<T>) result vector;
   */
  vec2<T> operator+(const vec2<T> &V) const
  {
    return vec2<T>(x + V.x, y + V.y);
  } /* End of 'operator+' function */

  /* Vector subtraction vector (reload -) function
   * ARGUMENTS:
   *   - link to vector:
   *       vec2<T> &V;
   * RETURNS:
   *       (vec2<T>) result vector;
   */
  vec2<T> operator-(const vec2<T> &V) const
  {
    return vec2<T>(x - V.x, y - V.y);
  } /* End of 'operator-' function */

  /* Vector negative vector (reload -) function
   * ARGUMENTS: NONE.
   * RETURNS:
   *       (vec2<T> &) link to result vector;
   */
  vec2<T> &operator-(VOID)
  {
    x = -x;
    y = -y;
    return *this;
  } /* End of 'operator-' function */

  /* Vector equal vector (reload =) function
   * ARGUMENTS:
   *   - link to vector:
   *       vec2<T> &V;
   * RETURNS:
   *       (vec2<T> &) link to result vector;
   */
  vec2<T> &operator=(const vec2<T> &V)
  {
    x = V.x;
    y = V.y;
    return *this;
  } /* End of 'operator=' function */

  /* Vector add and equal vector (reload +=) function
   * ARGUMENTS:
   *   - link to vector:
   *       vec2<T> &V;
   * RETURNS:
   *       (vec2<T> &) link to result vector;
   */
  vec2<T> &operator+=(const vec2<T> &V)
  {
    x += V.x;
    y += V.y;
    return *this;
  } /* End of 'operator+=' function */

  T operator[](int i) const
  {
    return *(&x + i);
  }

  T &operator[](int i)
  {
    return *(&x + i);
  }

  /* Vector substraction and equal vector (reload -=) function
   * ARGUMENTS:
   *   - link to vector:
   *       vec2<T> &V;
   * RETURNS:
   *       (vec2<T> &) link to result vector;
   */
  vec2<T> &operator-=(const vec2<T> &V)
  {
    x -= V.x;
    y -= V.y;
    return *this;
  } /* End of 'operator+=' function */

  vec2<T> &operator*=(const vec2<T> &V)
  {
    x *= V.x;
    y *= V.y;
    return *this;
  }

  T operator!(VOID) const
  {
    return sqrt(x * x + y * y);
  }

  T operator&(const vec2<T> &V) const
  {
    return x * V.x + y * V.y;
  }

  vec2<T> operator*(const vec2<T> &V) const
  {
    return vec2<T>(x * V.x, y * V.y);
  }

  vec2<T> operator*(const T number) const
  {
    return vec2<T>(x * number, y * number);
  }

  vec2<T> operator/(const T number) const
  {
    return vec2<T>(x / number, y / number);
  }

  vec2<T> &operator*=(const T number)
  {
    x *= number;
    y *= number;
    return *this;
  }

  vec2<T> &operator/=(const T number)
  {
    x /= number;
    y /= number;
    return *this;
  }

  vec2<T> &Normalize(VOID)
  {
    T len = !(*this);
    if (len == 0 || len == 0)
      return *this;
    *this /= len;
    return *this;
  }

  vec2<T> &Normalize(const vec2<T> &V)
  {
    vec2<T> X = V;
    *this = X.Normalize();
    return *this;
  }

  T Length2(VOID)
  {
    return !(*this) * !(*this);
  }

  T Distance(const vec2<T> &V)
  {
    return !(*this - V);
  }
};

template <class T>
class vec4
{
protected:
  T x, y, z, w;

public:
  /* Vector constructor method */
  vec4(T a, T b, T c, T d) : x(a), y(b), z(c), w(d)
  {}

  /* Vector constructor method with similar coordinates */
  explicit vec4(T a = 0) : x(a), y(a), z(a), w(a)
  {}

  /* Vector add vector (reload +) function
   * ARGUMENTS:
   *   - link to vector:
   *       vec4<T> &V;
   * RETURNS:
   *       (vec4<T>) result vector;
   */
  vec4<T> operator+(const vec4<T> &V) const
  {
    return vec4<T>(x + V.x, y + V.y, z + V.z, w + V.w);
  } /* End of 'operator+' function */

  /* Vector subtraction vector (reload -) function
   * ARGUMENTS:
   *   - link to vector:
   *       vec4<T> &V;
   * RETURNS:
   *       (vec4<T>) result vector;
   */
  vec4<T> operator-(const vec4<T> &V) const
  {
    return vec4<T>(x - V.x, y - V.y, z - V.z, w - V.w);
  } /* End of 'operator-' function */

  /* Vector negative vector (reload -) function
   * ARGUMENTS: NONE.
   * RETURNS:
   *       (vec4<T> &) link to result vector;
   */
  vec4<T> &operator-(VOID)
  {
    x = -x;
    y = -y;
    z = -z;
    w = -w;
    return *this;
  } /* End of 'operator-' function */

  /* Vector equal vector (reload =) function
   * ARGUMENTS:
   *   - link to vector:
   *       vec4<T> &V;
   * RETURNS:
   *       (vec4<T> &) link to result vector;
   */
  vec4<T> &operator=(const vec4<T> &V)
  {
    x = V.x;
    y = V.y;
    z = V.z;
    w = V.w;
    return *this;
  } /* End of 'operator=' function */

  /* Vector add and equal vector (reload +=) function
   * ARGUMENTS:
   *   - link to vector:
   *       vec4<T> &V;
   * RETURNS:
   *       (vec4<T> &) link to result vector;
   */
  vec4<T> &operator+=(const vec4<T> &V)
  {
    x += V.x;
    y += V.y;
    z += V.z;
    w += V.w;
    return *this;
  } /* End of 'operator+=' function */

  T operator[](int i) const
  {
    return *(&x + i);
  }

  T &operator[](int i)
  {
    return *(&x + i);
  }

  /* Vector substraction and equal vector (reload -=) function
   * ARGUMENTS:
   *   - link to vector:
   *       vec4<T> &V;
   * RETURNS:
   *       (vec4<T> &) link to result vector;
   */
  vec4<T> &operator-=(const vec4<T> &V)
  {
    x -= V.x;
    y -= V.y;
    z -= V.z;
    w -= V.w;
    return *this;
  } /* End of 'operator+=' function */

  vec4<T> &operator*=(const vec4<T> &V)
  {
    x *= V.x;
    y *= V.y;
    z *= V.z;
    w *= V.w;
    return *this;
  }

  T operator!(VOID) const
  {
    return sqrt(x * x + y * y + z * z + w * w);
  }

  T operator&(const vec4<T> &V) const
  {
    return x * V.x + y * V.y + z * V.z + w * V.w;
  }

  vec4<T> operator*(const vec4<T> &V) const
  {
    return vec4<T>(x * V.x, y * V.y, z * V.z, w * V.w);
  }

  vec4<T> operator*(const T number) const
  {
    return vec4<T>(x * number, y * number, z * number, w * number);
  }

  vec4<T> operator/(const T number) const
  {
    return vec4<T>(x / number, y / number, z / number, w / number);
  }

  vec4<T> &operator*=(const T number)
  {
    x *= number;
    y *= number;
    z *= number;
    w *= number;
    return *this;
  }

  vec4<T> &operator/=(const T number)
  {
    x /= number;
    y /= number;
    z /= number;
    w /= number;
    return *this;
  }

  vec4<T> &Normalize(VOID)
  {
    T len = !(*this);
    if (len == 0 || len == 0)
      return *this;
    *this /= len;
    return *this;
  }

  vec4<T> &Normalize(const vec4<T> &V)
  {
    vec4<T> X = V;
    *this = X.Normalize();
    return *this;
  }

  T Length2(VOID)
  {
    return !(*this) * !(*this);
  }

  T Distance(const vec4<T> &V)
  {
    return !(*this - V);
  }
};
} // namespace mth

#endif /* __VEC_H_ */

/* End of 'vec.h' file */
