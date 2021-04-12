/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : WINMSG.CPP
* PURPOSE     : Ray tracing.
*               Window class.
*               Message crackers.
* PROGRAMMER  : AD6.
* LAST UPDATE : 07.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "WIN.h"

/* WM_CREATE window message handle function.
* ARGUMENTS:
*   - structure with creation data:
*       CREATESTRUCT *CS;
* RETURNS:
*   (BOOL) TRUE to continue creation window, FALSE to terminate.
*/
BOOL dert::win::OnCreate( CREATESTRUCT *CS )
{
  Init();

  SetTimer(hWnd, 30, 1, NULL);
  return TRUE;
} /* End of 'win::OnCreate' function */

/* WM_GETMINMAXINFO window message handle function.
* ARGUMENTS:
*   - structure with min max data:
*       MINMAXINFO *MinMax;
* RETURNS: NONE.
*/
VOID dert::win::OnGetMinMaxInfo( MINMAXINFO *MinMax )
{
  MinMax->ptMaxTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK) + 
    GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
} /* End of 'win::OnGetMinMaxInfo' function */

/* WM_DESTROY window message handle function.
* ARGUMENTS: None.
* RETURNS: None.
*/
VOID dert::win::OnDestroy( VOID )
{
  Close();
  KillTimer(hWnd, 47);
  DestroyWindow(hWnd);
  PostQuitMessage(0);
} /* End of 'win::OnDestroy' function */

/* WM_CLOSE window message handle function.
* ARGUMENTS: None.
* RETURNS: None.
*/
VOID dert::win::OnClose( VOID )
{
    SendMessage(hWnd, WM_DESTROY, 0, 0);
} /* End of 'win::OnCLose' function */

/* WM_SIZE window message handle function.
* ARGUMENTS:
*   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
*       UINT State;
*   - new width and height of client area:
*       INT nW, nH;
* RETURNS: None.
*/
VOID dert::win::OnSize( UINT State, INT W, INT H )
{
  Resize();
  SendMessage(hWnd, WM_TIMER, 0, 0);
} /* End of 'win::OnSize' function */

/* WM_ERASEBKGND window message handle function.
* ARGUMENTS:
*   - device context of client area:
*       HDC hDC;
* RETURNS:
*   (BOOL) TRUE if background is erased, FALSE otherwise.
*/
BOOL dert::win::OnEraseBackground( HDC hDC )
{
  return TRUE;
} /* End of 'win::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
* ARGUMENTS: None.
* RETURNS: None.
*/
VOID dert::win::OnPaint( VOID )
{
  PAINTSTRUCT ps;
  HDC hDC;

  hDC = BeginPaint(hWnd, &ps);
  if (IsInit)
    Paint(hDC);
  EndPaint(hWnd, &ps);
  ReleaseDC(hWnd, hDC);
} /* End of 'win::OnPaint' function */ 

/* WM_ACTIVATE window message handle function.
* ARGUMENTS:
*   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
*       UINT Reason;
*   - handle of active window:
*       HWND hWndActDeact;
*   - minimized flag:
*       BOOL IsMinimized;
* RETURNS: None.
*/
VOID dert::win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
} /* End of 'win::OnActivate' function */

/* WM_TIMER window message handle function.
* ARGUMENTS:
*   - specified the timer identifier.
*       INT Id;
* RETURNS: None.
*/
VOID dert::win::OnTimer( INT Id ) 
{   
  if (!IsInit && Id == 30)
  {
    KillTimer(hWnd, Id);
    SetTimer(hWnd, 47, 0, NULL);
    IsInit = TRUE;
    Init();
   // Resize();
    Timer();
  }
  else
  {
    Timer();
  } 


  InvalidateRect(hWnd, NULL, FALSE);
} /* End of 'win::OnTimer' function */

/* WM_MOUSEWHEEL window message handle function.
* ARGUMENTS:
*   - mouse window position:
*       INT X, Y;
*   - mouse wheel relative delta value:
*       INT Z;
*   - mouse keys bits (see MK_*** bits constants):
*       UINT Keys;
* RETURNS: None.
*/
VOID dert::win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
} /* End of 'win::OnMouseWheel' function */

/* WM_KEYDOWN window message handle function.
* ARGUMENTS:
*   - W parametr.
*       WPARAM wParam;
* RETURNS: None.
*/
VOID dert::win::OnKeyDown( WPARAM wParam )
{
  if (wParam == VK_ESCAPE)
    SendMessage(hWnd, WM_CLOSE, 0, 0);
} /* End of 'win::OnKeyDown' function */


/* End of 'WINMSG.CPP' file */