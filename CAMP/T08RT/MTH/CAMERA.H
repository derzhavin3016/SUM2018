/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : CAMERA.H
* PURPOSE     : Ray tracing.
*               Camera handle.
* PROGRAMMER  : AD6.
* LAST UPDATE : 24.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "MTHDEF.H"

namespace mth
{
  template <class T>
    class camera
    {
    private:
      vec<T> Dir, Right, Up, CamLoc, Up1, At;
      T farclip, neard, ProjDist;
      INT W, H, Size;
      T Wp, Hp;
    public:

      camera( VOID )
      {
      }

      camera( INT &WRef, INT &HRef ) : W(WRef * 2), H(HRef * 2)
      {
      }

      vec<T> & GetLoc( VOID )
      {
        return CamLoc;
      }

      vec<T> & GetAt( VOID )
      {
        return At;
      }

      INT GetWidth( VOID )
      {
        return W;
      }

      INT GetHeight( VOID )
      {
        return H;
      }

      VOID SetLocAtUp( const vec<T> &L, const vec<T> &A, const vec<T> &U1 )
      {
        CamLoc = L;
        At = A;
        Up1 = U1;
        Dir = vec<T>(At - CamLoc).Normalize();
        Right = vec<T>(Dir % Up1).Normalize();
        Up = vec<T>(Right % Dir).Normalize();
      }
      
      VOID SetProj( VOID )
      {
        T ratio_x, ratio_y;
        Size = 1;

        ratio_y = ratio_x = 1;        if ( W > H )          ratio_x *= ((T) W) / H;        else          ratio_y *= ((T) H) / W;        Wp = ratio_x * Size;
        Hp = ratio_y * Size;      }

      /* Get ray function
       * ARGUMENTS:
       *   - screen coordinates:
       *       INT xs, ys;
       * RETURNS:
       *     (ray<T>) result ray;
       */
      ray<T> ToRay( INT xs, INT ys )
      {
        ProjDist = 1;
        vec<T>
          A = Dir * ProjDist,
          B = Right * (xs + 0.5 - W / 2) / W * Wp,
          C = Up * (-ys - 0.5 + H / 2) / H * Hp,
          X = A + B + C;
        return ray<T>(CamLoc + X, X.Normalize());
      } /* End of 'ToRay' function */

      /* Get anti-alising ray function
       * ARGUMENTS:
       *   - screen coordinates:
       *       INT xs, ys;
       *   - coordinates translation:
       *       DBL Dx, Dy;
       * RETURNS:
       *     (ray<T>) result ray;
       */
      ray<T> ToRayAA( INT xs, INT ys, DBL Dx, DBL Dy )
      {
        ProjDist = 1;
        vec<T>
          A = Dir * ProjDist,
          B = Right * (xs + Dx - W / 2) / W * Wp,
          C = Up * (-ys - Dy + H / 2) / H * Hp,
          X = A + B + C;
        return ray<T>(CamLoc + X, X.Normalize());
      } /* End of 'ToRay' function */

  };

}

#endif /* __CAMERA_H_ */

/* End of 'Camera.h' file */
