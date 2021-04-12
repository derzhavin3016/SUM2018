/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : Win.CPP
* PURPOSE     : Ray tracing.
*               Window class.
*               Functions realizations.
* PROGRAMMER  : AD6.
* LAST UPDATE : 24.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "Win.h"


dert::win::win( HINSTANCE hInst ) : hInstance(hInst), WND_CLASS_NAME("My window class")
{
  WNDCLASS wc;

  wc.style = CS_VREDRAW | CS_HREDRAW;                    /* Window style */
  wc.cbClsExtra = 0;                                     /* Additional bytes amount for class */
  wc.cbWndExtra = sizeof(VOID *);                        /* Additional bytes amount for window */
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;               /* Background color */
  wc.hCursor = LoadCursor(NULL, IDC_HAND);               /* Cursor loading */
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);                 /* Icon loading */
  wc.lpszMenuName = NULL;                                /* Menu resource name */
  wc.hInstance = hInstance;                              /* Handle application class register */  wc.lpfnWndProc = WinFunc;                              /* Pointer to rendering function */  wc.lpszClassName = WND_CLASS_NAME;                     /* Window class name */  /* Registering window class */  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK | MB_ICONERROR);
    return;
  }
  /* Window create */
  hWnd = 
  CreateWindow(WND_CLASS_NAME, 
    "CGSG forever",
    MY_WINDOW_WS,
    CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    (VOID *)this);

  // Show and draw the window
  ShowWindow(hWnd, SW_SHOWDEFAULT);
  UpdateWindow(hWnd);
}

INT dert::win::Run( VOID )
{
  MSG msg;
  IsInit = FALSE;

  while (TRUE)
  {
    /* Check message at window message queue */
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      else
      {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      }
    }    
    else
    {
      Timer();
      Paint(GetDC(hWnd));
      Resize();
      IsInit = TRUE;
    }
  }
  return msg.wParam;
}

/* Window message dispatch function
* ARGUMENTS:
*   - work window handle:
*       HWND hWnd;
*   - Message number:
*       UINT Msg;
*   - word parameter:
*       WPARAM wParam;
*   - long parameter:
*       LPARAM lParam;
* RETURNS:
*       (LRESULT);
*/
LRESULT CALLBACK dert::win::WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  win *Win;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    MINMAXINFO *MinMax;
    MinMax = (MINMAXINFO *)lParam;
    MinMax->ptMaxTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK) + 
      GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
    //Win->OnGetMinMaxInfo((MINMAXINFO *)lParam);
    return 0;
  case WM_CREATE:
    // Attach 'this' pointer to window class to window
    SetWindowLong(hWnd, 0, (DWORD) ((CREATESTRUCT *)lParam)->lpCreateParams);
    return 0;
  default:
    Win = (win *)GetWindowLong(hWnd, 0);
    if (Win != NULL)
      switch (Msg)
      {
      case WM_ACTIVATE:
        //Win->OnActivate();
        return 0;
      case WM_CREATE:
        Win->hWnd = hWnd;
        Win->H = HIWORD(lParam);
        Win->W = LOWORD(lParam);
        return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;
      case WM_SIZE:
        Win->H = HIWORD(lParam);
        Win->W = LOWORD(lParam);
        Win->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
        return 0;
      case WM_TIMER:
        Win->OnTimer((UINT)wParam);
        return 0;
      case WM_ERASEBKGND:
        return (LRESULT)Win->OnEraseBackground((HDC)wParam);
      case WM_PAINT:
        Win->OnPaint();
        break;
      case WM_MOUSEWHEEL:
        Win->OnMouseWheel((INT)(SHORT)LOWORD(lParam),
          (INT)(SHORT)HIWORD(lParam),
          (INT)(SHORT)HIWORD(wParam),
          (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_KEYDOWN:
        Win->OnKeyDown(wParam);
        return 0;
      case WM_CLOSE:
        Win->OnClose();
        return 0;
      case WM_DESTROY:
        Win->OnDestroy();
        return 0;
      }
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);

}  /* End of 'MyWindowFunc' function */

/* Flip full screen function
* ARGUMENTS: 
*   - window handle:
*       HWND hWnd;
* RETURNS: NONE
*/
VOID dert::win::FlipFullScreen( HWND hWnd )
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
    SetWindowPos(hWnd, HWND_TOP,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} // End of 'FlipFullScreen' function

/* End of 'Win.cpp' file */