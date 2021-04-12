#include "Win.h"

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
LRESULT CALLBACK win::MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps; /* Paint structure */
  MINMAXINFO *minmax;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    minmax = (MINMAXINFO *)lParam;
    minmax->ptMaxTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK) + 
      GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;
  case WM_CREATE:
    AD6_hRndWnd = hWnd;

    /* Render initialization */
    AD6_RndInit();
    SetTimer(hWnd, 30, 100, NULL);
    return 0;
  case WM_SIZE:
    AD6_RndFrameW = LOWORD(lParam);
    AD6_RndFrameH = HIWORD(lParam);
    glViewport(0, 0, AD6_RndFrameW, AD6_RndFrameH);
    SendMessage(AD6_hRndWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_TIMER:
    AD6_RndStart();

    AD6_RndRender();

    AD6_RndEnd();

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_PAINT:
    AD6_hRndDC = BeginPaint(hWnd, &ps);
    SwapBuffers(AD6_hRndDC);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    else if (wParam == 'F')
      AD6_RndFlipFullScreen(hWnd);
    return 0;
  case WM_CLOSE:
    if (MessageBox(NULL, "Are you sure you want to quit?", "QIUT", MB_YESNO | MB_DEFBUTTON1 | MB_ICONERROR) 
      == IDYES)
      SendMessage(hWnd, WM_DESTROY, 0, 0);
    return 0;
  case WM_DESTROY:
    AD6_RndClose();
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}  /* End of 'MyWindowFunc' function */