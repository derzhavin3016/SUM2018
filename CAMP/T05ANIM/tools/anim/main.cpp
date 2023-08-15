/* FILE NAME: Main.cpp
 * PROGRAMMER: AD6
 * LAST UPDATE: 11.07.2018
 * PURPOSE
 */

// #include "ANIM/UNIT/U_CONTROL.H"

#include <windows.h>

#include "Math/vec.hpp"

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
INT WINAPI WinMain([[maybe_unused]] HINSTANCE hInstance, [[maybe_unused]] HINSTANCE hPrevInstance,
                   [[maybe_unused]] CHAR *CmdLine, [[maybe_unused]] INT ShowCmd)
{
  mth::Vec<double> v{1, 2, 3};
  v.z();
} /* End of 'WinMain' function */

/* End of 'Main.cpp' file */
