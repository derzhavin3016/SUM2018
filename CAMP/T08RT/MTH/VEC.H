/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : VEC.H
* PURPOSE     : Ray tracing.
*               Vector class.
* PROGRAMMER  : AD6.
* LAST UPDATE : 24.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __VEC_H_
#define __VEC_H_

#include "MTHDEF.H"
#include <iostream>



namespace mth
{
  /* Vector class template */
  template <class T>
    class vec
    {      
    protected:
      T x, y, z;
    
    public:
      friend mth::matr<T>;
      friend mth::camera<T>;
      /* Vector constructor method */
      vec( T a, T b, T c ) : x(a), y(b), z(c) 
      {
      }

      /* Vector constructor method with similar coordinates */
      vec( T a = 0 ) : x(a), y(a), z(a)
      {
      }

      /* Vector copy constructor */
      vec( const vec<T> &V ) : x(V.x), y(V.y), z(V.z)
      {
      }

      /* Vector add vector (reload +) function
      * ARGUMENTS:
      *   - link to vector:
      *       vec<T> &V;
      * RETURNS:
      *       (vec<T>) result vector;
      */
      vec<T> operator+( const vec<T> &V) const
      {
        return vec<T>(x + V.x, y + V.y, z + V.z);
      } /* End of 'operator+' function */

      /* Vector subtraction vector (reload -) function
      * ARGUMENTS:
      *   - link to vector:
      *       vec<T> &V;
      * RETURNS:
      *       (vec<T>) result vector;
      */
      vec<T> operator-( const vec<T> &V) const
      {
        return vec<T>(x - V.x, y - V.y, z - V.z);
      } /* End of 'operator-' function */

      /* Vector negative vector (reload -) function
      * ARGUMENTS: NONE.
      * RETURNS:
      *       (vec<T> &) link to result vector;
      */
      vec<T> operator-( VOID ) const
      {
        vec r;

        r.x = -x;
        r.y = -y;
        r.z = -z;
        return r;
      } /* End of 'operator-' function */

      /* Vector equal vector (reload =) function
      * ARGUMENTS:
      *   - link to vector:
      *       vec<T> &V;
      * RETURNS:
      *       (vec<T> &) link to result vector;
      */
      vec<T> & operator=( const vec<T> &V)
      {
        x = V.x;
        y = V.y;
        z = V.z;
        return *this;
      } /* End of 'operator=' function */

      /* Vector add and equal vector (reload +=) function
      * ARGUMENTS:
      *   - link to vector:
      *       vec<T> &V;
      * RETURNS:
      *       (vec<T> &) link to result vector;
      */
      vec<T> & operator+=( const vec<T> &V)
      {
        x += V.x;
        y += V.y;
        z += V.z;
        return *this;
      } /* End of 'operator+=' function */

      T operator[]( int i ) const
      {
        return *(&x + i);
      }

      T & operator[]( int i )
      {
        return *(&x + i);
      }

      /* Vector substraction and equal vector (reload -=) function
      * ARGUMENTS:
      *   - link to vector:
      *       vec<T> &V;
      * RETURNS:
      *       (vec<T> &) link to result vector;
      */
      vec<T> & operator-=( const vec<T> &V)
      {
        x -= V.x;
        y -= V.y;
        z -= V.z;
        return *this;
      } /* End of 'operator+=' function */

      vec<T> & operator*=( const vec<T> &V)
      {
        x *= V.x;
        y *= V.y;
        z *= V.z;
        return *this;
      }

      T operator!( VOID ) const
      {
        return sqrt(x * x + y * y + z * z);
      }

      T operator&( const vec<T> &V ) const
      {
        return x * V.x + y * V.y + z * V.z;
      }

      vec<T> operator%( const vec<T> &V ) const
      {
        return vec<T>(y * V.z - z * V.y, z * V.x - x * V.z, x * V.y - y * V.x);
      }

      vec<T> operator*( const vec<T> &V ) const
      {
        return vec<T>(x * V.x, y * V.y, z * V.z);
      }

      vec<T> operator*( const matr<T> &M) const
      {
        T w = x * M.A[0][3] + y * M.A[1][3] + z * M.A[2][3] + M.A[3][3];
             
        return vec<T>((M.A[0][0] * x + M.A[1][0] * y + M.A[2][0] * z + M.A[3][0]) / w,
                      (M.A[0][1] * x + M.A[1][1] * y + M.A[2][1] * z + M.A[3][1]) / w, 
                      (M.A[0][2] * x + M.A[1][2] * y + M.A[2][2] * z + M.A[3][2]) / w);
      }

      /* Point transform function.
      * ARGUMENTS:
      *   - transform matrix:
      *       matr M;
      * RETURNS:
      *   (vec<T>) result vector.
      */
      vec<T> PointTrans( const matr<T> &M ) const
      {
        return vec<T>(M.A[0][0] * x + M.A[0][1] * y + M.A[0][2] * z, 
                      M.A[1][0] * x + M.A[1][1] * y + M.A[1][2] * z,
                      M.A[2][0] * x + M.A[2][1] * y + M.A[2][2] * z);
      } /* End of 'PointTrans' function */

      /* Vector transform function.
       * ARGUMENTS:
       *   - transform matrix:
       *       matr M;
       * RETURNS:
       *   (vec<T>) result vector.
       */
      vec<T> VecTrans( const matr<T> &M ) const
      {
        return vec<T>(M.A[0][0] * x + M.A[0][1] * y + M.A[0][2] * z + M.A[0][3], 
                      M.A[1][0] * x + M.A[1][1] * y + M.A[1][2] * z + M.A[1][3],
                      M.A[2][0] * x + M.A[2][1] * y + M.A[2][2] * z + M.A[2][3]);
      } /* End of 'VecTrans' function */

      vec<T> operator*( const T number ) const
      {
        return vec<T>(x * number, y * number, z * number);
      }

      vec<T> operator/( const T number ) const
      {
        return vec<T>(x / number, y / number, z / number);
      }

      vec<T> & operator*=( const T number)
      {
        x *= number;
        y *= number;
        z *= number;
        return *this;
      }

      vec<T> & operator/=( const T number)
      {
        x /= number;
        y /= number;
        z /= number;
        return *this;
      }
    
      vec<T> Normalize( VOID ) const
      {
        T len= !(*this);
        vec<T> V = *this;
        if (len == 0 || len == 1)
          return V;
        V /= len;
        return V;
      }

      vec<T> &Normalizing( VOID )
      {
        T len= !(*this);
        if (len == 0 || len == 1)
          return *this;
        *this /= len;
        return *this;
      }

      T Length2( VOID ) const
      {
        return x * x + y * y + z * z;
      }

      T Distance( const vec<T> &V )
      {
        return !(*this - V);
      }
      
      static vec<T> Min( vec<T> &V1, vec<T> &V2 )
      {
        return vec<T>(mth::Min(V1.x, V2.x), mth::Min(V1.y, V2.y), mth::Min(V1.z, V2.z));
      }

      static vec<T> Max( vec<T> &V1, vec<T> &V2 )
      {
        return vec<T>(mth::Max(V1.x, V2.x), mth::Max(V1.y, V2.y), mth::Max(V1.z, V2.z));
      }

    /*  vec<T> &Clamp( T A, T B )
      {
        x = mth::Clamp(x, A, B);
        y = mth::Clamp(y, A, B);
        z = mth::Clamp(z, A, B);
        return *this;
      }  */

      vec<T> Clamp( T A, T B )
      {
        x = mth::Clamp(x, A, B);
        y = mth::Clamp(y, A, B);
        z = mth::Clamp(z, A, B);
        return *this;
      }

      BOOL operator<( const vec &V ) const
      {
        if(x < V.x && y < V.y && z < V.z)
          return TRUE;
        return FALSE;
      }

      BOOL operator>( const vec &V ) const
      {
        if(x > V.x && y > V.y && z > V.z)
          return TRUE;
        return FALSE;
      }

      BOOL operator<=( const vec &V ) const
      {
        if(x <= V.x && y <= V.y && z <= V.z)
          return TRUE;
        return FALSE;
      }

      BOOL operator>=( const vec &V ) const
      {
        if(x >= V.x && y >= V.y && z >= V.z)
          return TRUE;
        return FALSE;
      }
    };

    template <class T>
      class vec2
      {      
      protected:
        T x, y;

      public:
        /* Vector constructor method */
        vec2( T a, T b ) : x(a), y(b) 
        {
        }

        /* Vector constructor method with similar coordinates */
        explicit vec2( T a = 0 ) : x(a), y(a)
        {
        }

        /* Vector add vector (reload +) function
        * ARGUMENTS:
        *   - link to vector:
        *       vec2<T> &V;
        * RETURNS:
        *       (vec2<T>) result vector;
        */
        vec2<T> operator+( const vec2<T> &V) const
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
        vec2<T> operator-( const vec2<T> &V) const
        {
          return vec2<T>(x - V.x, y - V.y);
        } /* End of 'operator-' function */

        /* Vector negative vector (reload -) function
        * ARGUMENTS: NONE.
        * RETURNS:
        *       (vec2<T>) result vector;
        */
        vec2<T> & operator-( VOID ) const
        {
          vec2<T> r;
          r.x = -x;
          r.y = -y;
          return r;
        } /* End of 'operator-' function */

        /* Vector equal vector (reload =) function
        * ARGUMENTS:
        *   - link to vector:
        *       vec2<T> &V;
        * RETURNS:
        *       (vec2<T> &) link to result vector;
        */
        vec2<T> & operator=( const vec2<T> &V)
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
        vec2<T> & operator+=( const vec2<T> &V)
        {
          x += V.x;
          y += V.y;
          return *this;
        } /* End of 'operator+=' function */

        T operator[]( int i ) const
        {
          return *(&x + i);
        }

        T & operator[]( int i )
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
        vec2<T> & operator-=( const vec2<T> &V)
        {
          x -= V.x;
          y -= V.y;
          return *this;
        } /* End of 'operator+=' function */

        vec2<T> & operator*=( const vec2<T> &V)
        {
          x *= V.x;
          y *= V.y;
          return *this;
        }

        T operator!( VOID ) const
        {
          return sqrt(x * x + y * y);
        }

        T operator&( const vec2<T> &V ) const
        {
          return x * V.x + y * V.y;
        }


        vec2<T> operator*( const vec2<T> &V ) const
        {
          return vec2<T>(x * V.x, y * V.y);
        }


        vec2<T> operator*( const T number ) const
        {
          return vec2<T>(x * number, y * number);
        }

        vec2<T> operator/( const T number ) const
        {
          return vec2<T>(x / number, y / number);
        }

        vec2<T> & operator*=( const T number)
        {
          x *= number;
          y *= number;
          return *this;
        }

        vec2<T> & operator/=( const T number)
        {
          x /= number;
          y /= number;
          return *this;
        }

        vec<T> Normalize( VOID ) const
        {
          T len= !(*this);
          vec<T> V = *this;
          if (len == 0 || len == 1)
            return V;
          V /= len;
          return V;
        }
        
        vec<T> &Normalizing( VOID )
        {
          T len= !(*this);
          if (len == 0 || len == 1)
            return *this;
          *this /= len;
          return *this;
        }

        T Length2( VOID )
        {
          return (x * x + y * y);
        }

        T Distance( const vec2<T> &V )
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
        vec4( T a, T b, T c, T d ) : x(a), y(b), z(c), w(d) 
        {
        }

        /* Vector constructor method with similar coordinates */
        explicit vec4( T a = 0 ) : x(a), y(a), z(a), w(a) 
        {
        }

        /* Vector add vector (reload +) function
        * ARGUMENTS:
        *   - link to vector:
        *       vec4<T> &V;
        * RETURNS:
        *       (vec4<T>) result vector;
        */
        vec4<T> operator+( const vec4<T> &V) const
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
        vec4<T> operator-( const vec4<T> &V) const
        {
          return vec4<T>(x - V.x, y - V.y, z -V.z, w - V.w);
        } /* End of 'operator-' function */

          /* Vector negative vector (reload -) function
          * ARGUMENTS: NONE.
          * RETURNS:
          *       (vec4<T> &) link to result vector;
          */
        vec4<T> & operator-( VOID )
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
        vec4<T> & operator=( const vec4<T> &V)
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
        vec4<T> & operator+=( const vec4<T> &V)
        {
          x += V.x;
          y += V.y;
          z += V.z;
          w += V.w;
          return *this;
        } /* End of 'operator+=' function */

        T operator[]( int i ) const
        {
          return *(&x + i);
        }

        T & operator[]( int i )
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
        vec4<T> & operator-=( const vec4<T> &V)
        {
          x -= V.x;
          y -= V.y;
          z -= V.z;
          w -= V.w;
          return *this;
        } /* End of 'operator+=' function */

        vec4<T> & operator*=( const vec4<T> &V)
        {
          x *= V.x;
          y *= V.y;
          z *= V.z;
          w *= V.w;
          return *this;
        }

        T operator!( VOID ) const
        {
          return sqrt(x * x + y * y + z * z + w * w);
        }

        T operator&( const vec4<T> &V ) const
        {
          return x * V.x + y * V.y + z * V.z + w * V.w;
        }


        vec4<T> operator*( const vec4<T> &V ) const
        {
          return vec4<T>(x * V.x, y * V.y, z * V.z, w * V.w);
        }


        vec4<T> operator*( const T number ) const
        {
          return vec4<T>(x * number, y * number, z * number, w * number);
        }

        vec4<T> operator/( const T number ) const
        {
          return vec4<T>(x / number, y / number, z / number, w / number);
        }

        vec4<T> & operator*=( const T number)
        {
          x *= number;
          y *= number;
          z *= number;
          w *= number;
          return *this;
        }

        vec4<T> & operator/=( const T number)
        {
          x /= number;
          y /= number;
          z /= number;
          w /= number;
          return *this;
        }

        vec4<T> & Normalize( VOID )
        {
          T len= !(*this);
          if  (len== 0 || len == 0)
            return *this;
          *this /= len;
          return *this;
        }

        vec4<T> & Normalize( const vec4<T> &V )
        {
          vec4<T> X = V;
          *this = X.Normalize();
          return *this;
        }

        T Length2( VOID )
        {
          return !(*this) * !(*this);
        }

        T Distance( const vec4<T> &V )
        {
          return !(*this - V);
        }
      };

      template<class T>
        vec<T> operator*( const T number, const vec<T> &V )
        {
          return V * number;
        }
}

#endif /* __VEC_H_ */


/* End of 'vec.h' file */
