/* FILE NAME: anim.cpp
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#include "ANIM.H"


degl::anim::anim( VOID ) : degl::win::win(), degl::render::render(win::hWnd, win::W, win::H) 
{

}

degl::anim & degl::anim::Get( VOID )
{
  static anim Instance;

  return Instance;
} 


/* Initialization function.
* ARGUMENTS: None.
* RETURNS: None.
*/
VOID degl::anim::Init( VOID )
{
} /* End of 'Init' function */

/* Deinitialization function.
* ARGUMENTS: None.
* RETURNS: None.
*/
VOID degl::anim::Close( VOID )
{

} /* End of 'Close' function */

  /* Change window size handle function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID degl::anim::Resize( INT W, INT H )
{
  RndResize(W, H);
} /* End of 'Resize' function */

/* Erase background handle function.
* ARGUMENTS:
*   - device context of client area:
*       HDC hDC;
* RETURNS: None.
*/
VOID degl::anim::Erase( HDC hDC )
{
} /* End of 'Erase' function */

/* Paint window content function.
* ARGUMENTS:
*   - device context of client area:
*       HDC hDC;
* RETURNS: None.
*/
VOID degl::anim::Paint( VOID )
{
  FrameCopy();
} /* End of 'Paint' function */

/* Timer handle function.
* ARGUMENTS: None.
* RETURNS: None.
*/
VOID degl::anim::Timer( VOID )
{
  static DBL ReloadTime = 0;


  timer::Responce();
  input::Resp();

  if (GlobalTime - ReloadTime > 2)
  {
    ReloadTime = GlobalTime;
    ShdUpdate();
  }
 


  if (IsInit)
  {
    for (auto p : Units)
      p->Response(this);
  }

  FrameStart();
/*  
  glBegin(GL_POLYGON);

  glColor3d(1, 1, 0);
  glVertex3d(1, -1, 0);

  glColor3d(1, 1, 0);
  glVertex3d(-1, -1, 0);

  glColor3d(0, 0, 1);
  glVertex3d(-1, 1, 0);

  glColor3d(0, 0, 1);
  glVertex3d(1, 1, 0); */
  if (IsInit)
  {
    for (auto p : Units)
      p->Render(this);
  }

  IsInit = TRUE;
  

  FrameEnd();
}

degl::anim::~anim( VOID )
{
  if (IsInit)
  {
    for (auto p : Units)
      delete p;
  }
}

