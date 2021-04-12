/* FILE NAME: input.cpp
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#include "INPUT.H"

VOID degl::keyboard::RespK( VOID )
{
  GetKeyboardState(Keys);
  
  for(INT i = 0; i < 256; i++)
  {
    Keys[i] >>= 7;
    KeysClick[i] = Keys[i] && !KeysOld[i];
  }
  memcpy(KeysOld, Keys, sizeof(KeysOld));
}

VOID degl::mouse::RespM( HWND hWnd )
{
  POINT pt;
  
  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);

  Mdx = pt.x - Mx;
  Mdy = pt.y - My;

  Mx = pt.x;
  My = pt.y;
}

VOID degl::input::Resp( VOID )
{
  //RespM();
  RespK();
  RespJ();
}

VOID degl::joystick::RespJ( VOID )
{
  // Joystick
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;
    // Get joystick info
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        // Buttons
        for (INT i = 0; i < 32; i++)
        {
          JBut[i] = (ji.dwButtons >> i) & 1;
          JButClick[i] = JBut[i] && !JButOld[i];
          JButOld[i] = JBut[i];
        }
        // Axes
        JX = AD6_GET_JOYSTICK_AXIS(X);
        JY = AD6_GET_JOYSTICK_AXIS(Y);
        JZ = AD6_GET_JOYSTICK_AXIS(Z);
        JR = AD6_GET_JOYSTICK_AXIS(R);

        // Point of view
        JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }
}






/* End of 'input.cpp' file */

