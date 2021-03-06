/* FILE NAME: Main.cpp
 * PROGRAMMER: AD6
 * LAST UPDATE: 11.07.2018
 * PURPOSE
 */

#include "ANIM/UNIT/U_CONTROL.H"



/* The main program function.
* ARGUMENTS:
*   - handle of application instance:
*       HINSTANCE hInstance;
*   - dummy handle of previous application instance (not used):
*       HINSTANCE hPrevInstance;
*   - command line string:
*       CHAR *CmdLine;
*   - show window command parameter (see SW_***):
*       INT CmdShow;
* RETURNS:
*   (INT) Error level for operation system (0 for success).
*/
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
  CHAR *CmdLine, INT ShowCmd )
{
  //win myw(hInstance);
  degl::anim &Ani = degl::anim::Get();

  Ani.Units.push_back(new degl::unit_cow((degl::anim *)&Ani));
  Ani.Units.push_back(new degl::u_control());

  Ani.Run();

  //myw.Run();
} /* End of 'WinMain' function */

/* End of 'Main.cpp' file */