/* FILE NAME: input.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#ifndef __INPUT_H_
#define __INPUT_H_

#include "../../WND/WIN.H"

#include <mmsystem.h>
#pragma comment(lib, "winmm")

#define AD6_GET_JOYSTICK_AXIS(A) \
  (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min) - 1)

namespace degl
{

  class keyboard
  {
  public:
    BYTE 
      Keys[256],
      KeysOld[256],
      KeysClick[256];
    VOID RespK( VOID );
  };

  class mouse
  {
  public:
    INT 
      Mx, My, Mz, Mdx, Mdy, Mdz;

    VOID RespM( HWND hWnd );
  };

  class joystick
  {
  public:
    INT JPov;                                   // Joystick point-of-view control
    DBL 
      JX, JY, JZ, JR;                           // Joystick axes
    BYTE 
      JBut[32], JButOld[32], JButClick[32];    // Joystick button states

    VOID RespJ( VOID );
  };

  class input : public mouse, public keyboard, public joystick
  {
  public:
    VOID Resp( VOID );
  };
}

#endif






/* End of 'input.h' file */
