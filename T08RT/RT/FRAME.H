/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : FRAME.H
* PURPOSE     : Ray tracing.
*               Head class.
* PROGRAMMER  : AD6.
* LAST UPDATE : 25.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __FRAME_H_
#define __FRAME_H_

#include "../WND/WIN.H"
#include "SCENE.H"

namespace dert
{
  class frame : public win, public scene
  {
  private:
    HDC hDC;
    image Img;
  public:
    camera Cam;

    /* Frame class constructor
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    frame( VOID );

    ~frame( VOID );


    /* Initialization function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    VOID Init( VOID ) override;

    /* Change window size handle function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    VOID Resize( VOID ) override;

    /* Paint window content function.
    * ARGUMENTS:
    *   - device context of client area:
    *       HDC hDC;
    * RETURNS: None.
    */
    VOID Paint( HDC hDC ) override;
  };
} /* End of 'dert' namespace */




#endif /* __FRAME_H_ */

/* End of 'FRAME.H' file */

