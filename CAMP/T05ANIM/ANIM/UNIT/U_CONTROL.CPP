/* FILE NAME: u_control.cpp
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#include "U_CONTROL.H"

degl::u_control::u_control( VOID )
{
}
degl::u_control::~u_control( VOID )
{
}

VOID degl::u_control::Render( anim *Ani )
{
  static CHAR Buf[1000];
  glLoadIdentity();
  glColor3d(0.4, 0.2, 0);
  glRasterPos2d(-0.96, 0.85);
  glListBase(102);
  INT len = sprintf(Buf, "FPS: %.3f, Loc: %f, %f, %f", Ani->FPS, Ani->Cam.GetLoc()[0], Ani->Cam.GetLoc()[1], Ani->Cam.GetLoc()[2]);
  glCallLists(len, GL_UNSIGNED_BYTE, Buf);
  glLoadIdentity();
  glColor3d(1, 1, 1);
  glRasterPos2d(0.7, -0.85);
  glListBase(102);
  
  len =  Ani->IsPause ? sprintf(Buf, "PAUSE") : sprintf(Buf, "");
  glCallLists(len, GL_UNSIGNED_BYTE, Buf);

}
VOID degl::u_control::Response( anim *Ani )
{
}

/* End of 'u_control.cpp' file */