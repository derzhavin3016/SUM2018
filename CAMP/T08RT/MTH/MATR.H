/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : MATR.H
* PURPOSE     : Ray tracing.
*               Matrix handle.
* PROGRAMMER  : AD6.
* LAST UPDATE : 24.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __MATR_H_
#define __MATR_H_


#include "MTHDEF.H"

namespace mth
{
  template <class T>
    class matr
    {
    private:
    public:
      T A[4][4];

    static T Determ3x3( T A11, T A12, T A13,
                  T A21, T A22, T A23, 
                  T A31, T A32, T A33 )
    {
      return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + 
             A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
    }

    public:
      friend mth::vec<T>;
      friend mth::camera<T>;

      matr( T A11, T A12, T A13, T A14,
                      T A21, T A22, T A23, T A24, 
                      T A31, T A32, T A33, T A34, 
                      T A41, T A42, T A43, T A44 )
      {
        A[0][0] = A11;
        A[0][1] = A12;
        A[0][2] = A13;
        A[0][3] = A14;
        A[1][0] = A21;
        A[1][1] = A22;
        A[1][2] = A23;
        A[1][3] = A24;
        A[2][0] = A31;
        A[2][1] = A32;
        A[2][2] = A33;
        A[2][3] = A34;
        A[3][0] = A41;
        A[3][1] = A42;
        A[3][2] = A43;
        A[3][3] = A44;
      }

      matr( VOID )
      {
        A[0][0] = 1;
        A[0][1] = 0;
        A[0][2] = 0;
        A[0][3] = 0;
        A[1][0] = 0;
        A[1][1] = 1;
        A[1][2] = 0;
        A[1][3] = 0;
        A[2][0] = 0;
        A[2][1] = 0;
        A[2][2] = 1;
        A[2][3] = 0;
        A[3][0] = 0;
        A[3][1] = 0;
        A[3][2] = 0;
        A[3][3] = 1;
      }

      static matr<T> Identity( VOID )
      {
        return matr(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
      }

      matr( const matr<T> &M )
      {
        for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
            A[i][j] = M.A[i][j];
      }



      matr<T> & operator=( const matr<T> &M )
      {
        for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
            A[i][j] = M.A[i][j];
        return *this;
      } 

      matr<T> & Transpose( const matr<T> &M ) 
      {                 
        for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
            A[i][j] = M.A[j][i];
        return *this;
      }

      matr<T> & Transpose( VOID ) 
      {                 
        for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
            A[i][j] = A[j][i];
        return *this;
      }

      matr<T> Transpose( VOID ) const
      {             
        matr<T> r;

        for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
            r.A[i][j] = A[j][i];
        return r;
      }

      matr<T> operator*( const matr<T> &M ) const
      {
        matr<T> r;
        int k;

        for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
            for (r.A[i][j] = 0, k = 0; k < 4; k++)
              r.A[i][j] += A[i][k] * M.A[k][j];
        return r;
      }
 
      T operator!( VOID ) const
      {
        return
          A[0][0] * Determ3x3(A[1][1], A[1][2], A[1][3],
            A[2][1], A[2][2], A[2][3],
            A[3][1], A[3][2], A[3][3]) -
          A[0][1] * Determ3x3(A[1][0], A[1][2], A[1][3],
            A[2][0], A[2][2], A[2][3],
            A[3][0], A[3][2], A[3][3]) +
          A[0][2] * Determ3x3(A[1][0], A[1][1], A[1][3],
            A[2][0], A[2][1], A[2][3],
            A[3][0], A[3][1], A[3][3]) -
          A[0][3] * Determ3x3(A[1][0], A[1][1], A[1][2],
            A[2][0], A[2][1], A[2][2],
            A[3][0], A[3][1], A[3][2]);
      }

      matr<T> Inverse( VOID ) const
      {
        matr<T> r;
        T det = !(*this);

        if (det == 0)
          return Identity();

        r.A[0][0] =
          Determ3x3(A[1][1], A[1][2], A[1][3],
            A[2][1], A[2][2], A[2][3],
            A[3][1], A[3][2], A[3][3]);
        r.A[1][0] =
          -Determ3x3(A[1][0], A[1][2], A[1][3],
            A[2][0], A[2][2], A[2][3],
            A[3][0], A[3][2], A[3][3]);
        r.A[2][0] =
          Determ3x3(A[1][0], A[1][1], A[1][3],
            A[2][0], A[2][1], A[2][3],
            A[3][0], A[3][1], A[3][3]);
        r.A[3][0] =
          -Determ3x3(A[1][0], A[1][1], A[1][2],
            A[2][0], A[2][1], A[2][2],
            A[3][0], A[3][1], A[3][2]);
        r.A[0][1] =
          -Determ3x3(A[0][1], A[0][2], A[0][3],
            A[2][1], A[2][2], A[2][3],
            A[3][1], A[3][2], A[3][3]);
        r.A[1][1] =
          Determ3x3(A[0][0], A[0][2], A[0][3],
            A[2][0], A[2][2], A[2][3],
            A[3][0], A[3][2], A[3][3]);
        r.A[2][1] =
          -Determ3x3(A[0][0], A[0][1], A[0][3],
            A[2][0], A[2][1], A[2][3],
            A[3][0], A[3][1], A[3][3]);
        r.A[3][1] =
          Determ3x3(A[0][0], A[0][1], A[0][2],
            A[2][0], A[2][1], A[2][2],
            A[3][0], A[3][1], A[3][2]);
        r.A[0][2] =
          Determ3x3(A[0][1], A[0][2], A[0][3],
            A[1][1], A[1][2], A[1][3],
            A[3][1], A[3][2], A[3][3]);
        r.A[1][2] =
          -Determ3x3(A[0][0], A[0][2], A[0][3],
            A[1][0], A[1][2], A[1][3],
            A[3][0], A[3][2], A[3][3]);
        r.A[2][2] =
          Determ3x3(A[0][0], A[0][1], A[0][3],
            A[1][0], A[1][1], A[1][3],
            A[3][0], A[3][1], A[3][3]);
        r.A[3][2] =
          -Determ3x3(A[0][0], A[0][1], A[0][2],
            A[1][0], A[1][1], A[1][2],
            A[3][0], A[3][1], A[3][2]);
        r.A[0][3] =
          -Determ3x3(A[0][1], A[0][2], A[0][3],
            A[1][1], A[1][2], A[1][3],
            A[2][1], A[2][2], A[2][3]); 
        r.A[1][3] =
          Determ3x3(A[0][0], A[0][2], A[0][3],
            A[1][0], A[1][2], A[1][3],
            A[2][0], A[2][2], A[2][3]);
        r.A[2][3] =
          -Determ3x3(A[0][0], A[0][1], A[0][3],
            A[1][0], A[1][1], A[1][3],
            A[2][0], A[2][1], A[2][3]);
        r.A[3][3] =
          Determ3x3(A[0][0], A[0][1], A[0][2],
            A[1][0], A[1][1], A[1][2],
            A[2][0], A[2][1], A[2][2]);

        r.A[0][0] /= det;
        r.A[1][0] /= det;
        r.A[2][0] /= det;
        r.A[3][0] /= det;
        r.A[0][1] /= det;
        r.A[1][1] /= det;
        r.A[2][1] /= det;
        r.A[3][1] /= det;
        r.A[0][2] /= det;
        r.A[1][2] /= det;
        r.A[2][2] /= det;
        r.A[3][2] /= det;
        r.A[0][3] /= det;
        r.A[1][3] /= det;
        r.A[2][3] /= det;
        r.A[3][3] /= det;

        return r;
      }

      static matr<T> Translate( const vec<T> &V )
      {
        matr<T> m(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  V.x, V.y, V.z, 1);

        return  m;
      }

      static matr<T> Scale( const vec<T> &S )
      {
        matr<T> m(S.x, 0, 0, 0,
                  0, S.y, 0, 0,
                  0, 0, S.z, 0,
                  0, 0, 0, 1);

        return  m;
      }

      static matr<T> RotateX( T AngleInDegree )
      { 
        T A = D2R( AngleInDegree );

        matr<T> m(1, 0, 0, 0,
                  0, cos(A), sin(A), 0,
                  0, -sin(A), cos(A), 0,
                  0, 0, 0, 1);

        return  m;
      }

      static matr<T> RotateY( T AngleInDegree )
      { 
        T A = D2R( AngleInDegree );

        matr<T> m(cos(A), 0, -sin(A), 0,
                  0, 1, 0, 0,
                  sin(A), 0, cos(A), 0,
                  0, 0, 0, 1);

        return  m;
      }

      static matr<T> RotateZ( T AngleInDegree )
      { 
        T A = D2R( AngleInDegree );

        matr<T> m(cos(A), sin(A), 0, 0,
                 -sin(A), cos(A), 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1);

        return  m;
      }

      static matr<T> Rotate( T AngleInDegree, const vec<T> &R )
      { 
        T A = D2R( AngleInDegree );
        T si = sin(A), co = cos(A);
        vec<T> V;
        V = R.Normalize();

        matr<T> m(co + V[0] * V[0] * (1 - co),
                V[0] * V[1] * (1- co) + V[2] * si,
                  V[0] * V[2] * (1 - co) - V[1] * si, 0,
            V[1] * V[0] * (1 - co) - V[2] * si,
                co + V[1] * V[1] * (1 - co),
                  V[1] * V[2] * (1 - co) + V[0] * si, 0,
            V[2] * V[0] * (1 - co) + V[1] * si,
                V[2] * V[1] * (1 - co) - V[0] * si,
                  co + V[2] * V[2] * (1 - co), 0,
            0, 0, 0, 1);

        return  m;
      }

      static matr<T> MatrView( const vec<T> &Loc, const vec<T> &At, const vec<T> &Up1 )
      {
        vec<T>
          Dir = vec<T>::Normalizing(At - Loc),
          Right = vec<T>::Normalizing(Dir % Up1),
          Up = vec<T>::Normalizing(Right % Dir);

        matr<T> v(Right[0], Up[0], -Dir[0], 0, 
        Right[1], Up[1], -Dir[1], 0, 
        Right[2], Up[2], -Dir[2], 0,
        -(Loc & Right), -(Loc & Up), Loc & Dir, 1);
        return v;
      }

      static matr<T> MatrFrustum( const T l, const T r, const T b, const T t, const T n, const T f )
      {

        matr<T> fr ((2 * n) / (r - l), 0, 0, 0,
          0, (2 * n) / (t - b), 0, 0,
          (r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1,
          0, 0, -(2 * n * f) / (f - n), 0);
        return fr;
      }
    };
}

#endif /* __MATR_H_ */

/* End of 'matr.h' file */
