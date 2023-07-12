/* FILE NAME: Camera.h
* PROGRAMMER: AD6
* LAST UPDATE: 11.07.2018
* PURPOSE
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
      T right, left, top, bottom, farclip = 10000, neard = 0.1;
      matr<T> view, frustum, Proj;
    public:

      camera( VOID )
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

      camera<T> & CamSet( const vec<T> &L, const vec<T> &A, const vec<T> &U1 )
      {
        CamLoc = L;
        At = A;
        Up1 = U1;
        view = matr<T>::MatrView(L, A, U1);
        Proj = view * frustum;
        return *this;
      }

      camera<T> & CamSet( VOID )
      {
        view = matr<T>::MatrView(CamLoc, At, Up1);
        Proj = view * frustum;
        return *this;
      }
      
      camera<T> & ProjSet( const INT W, const INT H )
      {
        DBL ratio_x, ratio_y;

        ratio_x = ratio_y = 0.1 / 2;        if ( W > H )          ratio_x *= (DBL) W / H;        else          ratio_y *= (DBL) H / W;         frustum = matr<T>::MatrFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y, neard, farclip);
         Proj = view * frustum;
         return *this;
      }     
      
      matr<T> & GetProj( VOID )
      {
        return Proj;
      }

      VOID CamRotY( T AngleInDegree )
      {        CamLoc = CamLoc * matr<T>::Rotate(AngleInDegree, Up1);        CamSet();
      }

  };

}

#endif

/* End of 'Camera.h' file */
