/* FILE NAME: u_fly.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/


#ifndef __U_FLY_H_
#define __U_FLY_H_

#include"../../DEF.H"
#include "../RND/RENDER.H"
#include "../ANIM.H"

namespace degl
{
  class unit_cow : public unit
  {
  public:
    prims *E45 = new prims;
    matr M, T;
    vec Pos;
    BOOL IsW = 1;
    BOOL IsFreeCam = 0;
    vec Loc = vec(0, 10, 10);//vec(256, 500, 1032);
    vec Dir = vec(0) - Loc;

    unit_cow( anim *Ani );

    VOID Render( anim *Ani );

    VOID Response( anim *Ani );

    ~unit_cow( VOID );
  };
} /* End of 'degl' namespace */





#endif /* __UNITCOW_H_ */

/* End of 'u_fly.h' file */