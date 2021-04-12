/* FILE NAME: u_control.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#ifndef __U_CONTROL_H_
#define __U_CONTROL_H_

#include "U_FLY.H"

namespace degl
{
  class u_control : public unit
  {
  public:

    u_control( VOID );

    VOID Render( anim *Ani );

    VOID Response( anim *Ani );

    ~u_control( VOID );
  };
} /* End of 'degl' namespace */


#endif /* __U_CONTROL_ */




/* End of 'u_control.h' file */