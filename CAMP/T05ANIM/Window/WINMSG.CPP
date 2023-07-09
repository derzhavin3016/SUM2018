/* FILE NAME: WINMSG.CPP
* PROGRAMMER: AD6
* LAST UPDATE: 11.07.2018
* PURPOSE
*/

#include "WIN.h"

/* WM_CREATE window message handle function.
* ARGUMENTS:
*   - structure with creation data:
*       CREATESTRUCT *CS;
* RETURNS:
*   (BOOL) TRUE to continue creation window, FALSE to terminate.
*/
BOOL degl::win::OnCreate( CREATESTRUCT *CS )
{
  Init();
  
  
  
  SetTimer(hWnd, 30, 10, NULL);
  SendMessage(hWnd, WM_TIMER, 0, 0);
  return TRUE;
} /* End of 'win::OnCreate' function */

/* WM_GETMINMAXINFO window message handle function.
* ARGUMENTS:
*   - structure with min max data:
*       MINMAXINFO *MinMax;
* RETURNS: NONE.
*/
VOID degl::win::OnGetMinMaxInfo( MINMAXINFO *MinMax )
{
  MinMax->ptMaxTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK) + 
    GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
} /* End of 'win::OnGetMinMaxInfo' function */

/* WM_DESTROY window message handle function.
* ARGUMENTS: None.
* RETURNS: None.
*/
VOID degl::win::OnDestroy( VOID )
{
  Close();
  KillTimer(hWnd, 30);
  PostQuitMessage(0);
} /* End of 'win::OnDestroy' function */

/* WM_CLOSE window message handle function.
* ARGUMENTS: None.
* RETURNS: None.
*/
VOID degl::win::OnClose( VOID )
{
  if (MessageBox(NULL, "Are you sure you want to quit?", "QIUT", MB_YESNO | MB_DEFBUTTON1 | MB_ICONQUESTION) 
    == IDYES)
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
VOID degl::win::OnSize( UINT State, INT W, INT H )
{
  Resize(W, H);
  //glViewport(0, 0, W, H);
  SendMessage(hWnd, WM_TIMER, 0, 0);
} /* End of 'win::OnSize' function */

/* WM_ERASEBKGND window message handle function.
* ARGUMENTS:
*   - device context of client area:
*       HDC hDC;
* RETURNS:
*   (BOOL) TRUE if background is erased, FALSE otherwise.
*/
BOOL degl::win::OnEraseBackground( HDC hDC )
{
  return TRUE;
} /* End of 'win::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
* ARGUMENTS: None.
* RETURNS: None.
*/
VOID degl::win::OnPaint( VOID )
{
  Paint();
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
VOID degl::win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
} /* End of 'win::OnActivate' function */

/* WM_TIMER window message handle function.
* ARGUMENTS:
*   - specified the timer identifier.
*       INT Id;
* RETURNS: None.
*/
VOID degl::win::OnTimer( INT Id ) 
{   
  if (!IsInit)
  {
    KillTimer(hWnd, Id);
    //SendMessage(hWnd, WM_TIMER, 0, 0);
    IsInit = TRUE;
    Init();
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
VOID degl::win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
} /* End of 'win::OnMouseWheel' function */

/* WM_KEYDOWN window message handle function.
* ARGUMENTS:
*   - W parametr.
*       WPARAM wParam;
* RETURNS: None.
*/
VOID degl::win::OnKeyDown( WPARAM wParam )
{
  if (wParam == VK_ESCAPE)
    SendMessage(hWnd, WM_CLOSE, 0, 0);
  else if (wParam == 'F')
    FlipFullScreen(hWnd);
} /* End of 'win::OnKeyDown' function */


/* End of 'WINMSG.CPP' file */