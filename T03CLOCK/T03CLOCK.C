 /* FILE NAME: T03CLOCK
  * PROGRAMMER: AD6
  * DATE: 04.06.2018
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
    "CLOCK",
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
  PAINTSTRUCT ps;
  INT x, y;
  static INT w, h, mode = 1;
  static HBITMAP hBm;
  static HDC hMemDc;

  switch (Msg)
  {
  case WM_CREATE:
    hDc = GetDC(hWnd);
    hMemDc = CreateCompatibleDC(hDc);
    ReleaseDC(hWnd, hDc);

    SetTimer(hWnd, 47, 30, NULL);
    return 0;
  case WM_SIZE:
    h = HIWORD(lParam);
    w = LOWORD(lParam);

    if (hBm != NULL)
      DeleteObject(hBm);

    hDc = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDc, w, h);
    ReleaseDC(hWnd, hDc);

    SelectObject(hMemDc, hBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_SPACE)
      mode = 1 - mode;
    else if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
  case WM_TIMER:
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    hDc = hMemDc;

    SelectObject(hDc, GetStockObject(DC_PEN));
    SelectObject(hDc, GetStockObject(DC_BRUSH));
    SetDCPenColor(hDc, RGB(0, 60, 255));
    SetDCBrushColor(hDc, RGB(0, 60, 255));

    Rectangle(hDc, 0, 0, w, h);
    if (mode == 1)
    {
      srand(30);
      for (x = 0; x < 500; x++)
      DrawEye(hDc, rand() % 3000, rand() % 2000,  20 + rand() % 50, 4 + rand() % 15, pt.x, pt.y);
    }
    else
    {
    for (x = 0; x < w; x +=101)
      for (y = 0; y < h; y += 101)
        DrawEye(hDc, x, y, 50, 25, pt.x, pt.y);
    }

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_PAINT:
    hDc = BeginPaint(hWnd, &ps);
    BitBlt(hDc, 0, 0, w, h, hMemDc, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:    
    return 1;
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure to close window?", "Quit", MB_YESNO | MB_DEFBUTTON2 | MB_ICONINFORMATION ) == IDYES)
      SendMessage(hWnd, WM_DESTROY, 0, 0);
    return 0;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDc);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    KillTimer(hWnd, 47);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);

} /* End of 'MyWindowFunc' function */

/* END OF 'T02EYES.C' FILE */
