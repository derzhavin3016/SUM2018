/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : FRAME.CPP
* PURPOSE     : Ray tracing.
*               Head class.
*               Function realizations.
* PROGRAMMER  : AD6.
* LAST UPDATE : 25.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "FRAME.H"


/* Frame class constructor
* ARGUMENTS: None.
* RETURNS: None.
*/
dert::frame::frame( VOID ) : win(), Cam(win::W, win::H), scene()
{
  Cam.SetLocAtUp(vec(25, 20, 0), vec(0, 2, 0), vec(0, 1, 0));
  Cam.SetProj();
  Img.Resize(W, H);
  Render(Cam, &Img);
  Img.SaveBMP();
} /* End of render class constructor */

dert::frame::~frame( VOID )
{
}

/* Change window size handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID dert::frame::Resize( VOID )
{
  Cam.SetProj();

} /* End of 'dert::frame::Resize' function */

/* Paint window content function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID dert::frame::Paint( HDC hDC )
{
  Img.Draw(hDC);
} /* End of 'dert::frame::Paint' function */

/* Initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID dert::frame::Init( VOID )
{

} /* End of 'dert::frame::Init' function */

/* End of 'FRAME.CPP' file */