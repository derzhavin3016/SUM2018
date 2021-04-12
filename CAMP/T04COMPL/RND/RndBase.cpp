#include "RND.H"


/* Render initialization function
* ARGUMENTS: NONE
* RETURNS: NONE
*/

const int W = 1024, H = 1024;

unsigned char Frame[H][W][3];

VOID AD6_MdlInit( VOID )
{
  int X0 = -1, X1 = 1, Y0 = -1, Y1 = 1;

  for (int ys = 0; ys < H; ys++)
    for (int xs = 0; xs < W; xs++)
    {
      Frame[xs][ys][0] = Frame[xs][ys][1] = Frame[xs][ys][2] = Compl(xs * (X1 - X0) / DBL(W) + X0, ys * (Y1 - Y0) / DBL(H) + Y0)();
    }
}

VOID AD6_JulInit( VOID )
{
  int X0 = -1, X1 = 1, Y0 = -1, Y1 = 1;
  DBL Time = (DBL)clock() / CLOCKS_PER_SEC;

  Compl C(sin(Time * 0.3) * 0.03 + 0.82, cos(Time * 0.3) * 0.03 + 0.82);

  for (int ys = 0; ys < H; ys++)
    for (int xs = 0; xs < W; xs++)
    {
      Frame[xs][ys][0] = Frame[xs][ys][1] = Frame[xs][ys][2] = Compl(xs * (X1 - X0) / DBL(W) + X0, ys * (Y1 - Y0) / DBL(H) + Y0)(C);
      Frame[xs][ys][0] *= 10;
      Frame[xs][ys][1] *= 12;
      Frame[xs][ys][2] *= 90;
    }
}

VOID AD6_RndInit( VOID )
{
  PIXELFORMATDESCRIPTOR pfd = {0};
  INT i;

  AD6_hRndDC = GetDC(AD6_hRndWnd);

  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(AD6_hRndDC, &pfd);
  DescribePixelFormat(AD6_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(AD6_hRndDC, i, &pfd);

  AD6_hRndRC = wglCreateContext(AD6_hRndDC);
  wglMakeCurrent(AD6_hRndDC, AD6_hRndRC);

  glClearColor(0.3, 0.5, 0.7, 1);
  glEnable(GL_DEPTH_TEST);

  //AD6_MdlInit();
  //AD6_JulInit();
} /* End of 'AD6_RndInit' function */


  /* Render resize function
  * ARGUMENTS: NONE
  * RETURNS: NONE
  */
VOID AD6_RndResize( VOID )
{
  glViewport(0, 0, AD6_RndFrameW, AD6_RndFrameH);
  SendMessage(AD6_hRndWnd, WM_TIMER, 0, 0);
} /* End of 'AD6_RndResize' function */


  /* Render start function
  * ARGUMENTS: NONE
  * RETURNS: NONE
  */
VOID AD6_RndStart( VOID )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  AD6_MdlInit();
} /* End of 'AD6_RndStart' function */

  /* Render function
  * ARGUMENTS: NONE
  * RETURNS: NONE
  */
VOID AD6_RndRender( VOID )
{
  //AD6_JulInit();
  DBL s = AD6_RndFrameH < AD6_RndFrameW ? AD6_RndFrameH / DBL(H) : AD6_RndFrameW / DBL(W); 

  
  glRasterPos2d(-0.5, -1);
  glPixelZoom(GLfloat(s), GLfloat(s));
  glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_BYTE, Frame);

    //glTranslatef(1000, AD6_RndFrameH, 0);
    //glPixelZoom(AD6_RndFrameW / W, AD6_RndFrameH / W);

} /* End of 'AD6_RndRender' function */

  /* Render end function
  * ARGUMENTS: NONE
  * RETURNS: NONE
  */
VOID AD6_RndEnd( VOID )
{
  glEnd();
  glFinish();
} /* End of 'AD6_RndEnd' function */

  /* Render close function
  * ARGUMENTS: NONE
  * RETURNS: NONE
  */
VOID AD6_RndClose( VOID )
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(AD6_hRndRC);
  ReleaseDC(AD6_hRndWnd, AD6_hRndDC);
  KillTimer(AD6_hRndWnd, 30);
  PostQuitMessage(0);
} /* End of 'AD6_RndClose' function */

  /* Flip full screen function
  * ARGUMENTS: 
  *   - window handle:
  *       HWND hWnd;
  * RETURNS: NONE
  */
VOID AD6_RndFlipFullScreen( HWND hWnd )
{
  static BOOL IsFullScreen = FALSE; 
  static RECT SaveRC;

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    GetWindowRect(hWnd, &SaveRC);

    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    rc.left = 0;
    rc.top = 0;
    rc.right = GetSystemMetrics(SM_CXSCREEN);
    rc.bottom = GetSystemMetrics(SM_CYSCREEN);

    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top + 201,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    SetWindowPos(hWnd, HWND_TOPMOST,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'AD6_RndFlipFullScreen' function */

  /* End of 'RndBase.C' file */