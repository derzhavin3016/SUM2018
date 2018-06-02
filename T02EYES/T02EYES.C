 /* FILE NAME: T02EYES
  * PROGRAMMER: AD6
  * DATE: 01.06.2018
  */

#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define WND_CLASS_NAME "My window class"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
/* Main program function */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_INFORMATION);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }
  hWnd = 
    CreateWindow(WND_CLASS_NAME,
    "Eyes",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
} /* End of 'WinMain' function */

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDc;
  POINT pt;
  RECT rc;
  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 47, 30, NULL);
    return 0;
  case WM_TIMER:
    GetClientRect(hWnd, &rc);
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    hDc = GetDC(hWnd);
    Rectangle(hDc, 0, 0, rc.right, rc.bottom);
    SelectObject(hDc, GetStockObject(DC_PEN));
    SelectObject(hDc, GetStockObject(DC_BRUSH));
    SetDCPenColor(hDc, RGB(255, 0, 0));
    SetDCBrushColor(hDc, RGB(0, 255, 255));
    Ellipse(hDc, 0, 0, rc.right, rc.bottom);
    MoveToEx(hDc, rc.right / 2, rc.bottom / 2, NULL);
    //LineTo(hDc, pt.x, pt.y);
    DOUBLE R = (sqrt((pt.y - rc.bottom / 2) * (pt.y - rc.bottom / 2) + (pt.x - rc.right / 2) * (pt.x - rc.right / 2)),
      sine = (pt.y - rc.bottom / 2) / R), 
      cosine = (pt.x - rc.right / 2) / R);
    SetDCPenColor(hDc, RGB(255, 0, 255));
    SetDCBrushColor(hDc, RGB(255, 255, 255));
    Ellipse(hDc, cosine * (R - ) +  );
    ReleaseDC(hWnd, hDc);
    return 0;
  case WM_DESTROY:
    PostMessage(hWnd, WM_QUIT, 0, 0);
    KillTimer(hWnd, 47);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);

} /* End of 'MyWindowFunc' function */

/* END OF 'T02EYES.C' FILE */ 

