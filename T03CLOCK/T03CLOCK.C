 /* FILE NAME: T03CLOCK
  * PROGRAMMER: AD6
  * DATE: 04.06.2018
  */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#include "resource.h"

/* Main window class name */
#define WND_CLASS_NAME "My window class"
#define PI 3.14159265358979323846

/* Forward references */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* Turn full screen window mode function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID FlipFullScreen( HWND hWnd )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRC;

  if (IsFullScreen)
  {
    /* Restore window size and position */
    IsFullScreen = FALSE;

    SetWindowPos(hWnd, HWND_TOP, SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top, SWP_NOOWNERZORDER);
  }
  else
  {
    RECT rc;
    HMONITOR hMon;
    MONITORINFOEX moninfo;

    /* Go to full screen mode */
    IsFullScreen = TRUE;

    /* Save window position and size */
    GetWindowRect(hWnd, &SaveRC);

    /* Obtain closest monitor info */
    hMon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    moninfo.cbSize = sizeof(MONITORINFOEX);
    GetMonitorInfo(hMon, (MONITORINFO *)&moninfo);

    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOP, rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top, SWP_NOOWNERZORDER);
  }
} /* End of 'FlipFullScreen' function */

VOID DrawHand( HDC hDc, INT x0, INT y0, INT L, INT W, DOUBLE si, DOUBLE co , INT color)
{
  POINT pts[] = {{0, L}, {-W, 0}, {0, -W}, {W, 0}}, pts1[sizeof(pts) / sizeof(pts[0])];
  INT i, N = sizeof(pts) / sizeof(pts[0]);

  for (i = 0; i < N; i++)
  {
    pts1[i].x = x0 + pts[i].x * co + pts[i].y * si;
    pts1[i].y = y0 - pts[i].y * co + pts[i].x * si;
  }
  SelectObject(hDc, GetStockObject(DC_PEN));
  SelectObject(hDc, GetStockObject(DC_BRUSH));
  SetDCPenColor(hDc, RGB(255, 255, 255));
  SetDCBrushColor(hDc, color);
  Polygon(hDc, pts1, N);
}

VOID DrawClock( HDC hDc, INT X, INT Y, INT H )
{
  DOUBLE phis, phimin, phih;
  INT lh, lm, lsec;
  SYSTEMTIME tm;
  lsec = H / 2 - 50;
  lm = lsec - 100;
  lh = lm - 50;
  GetLocalTime(&tm);

  phis = tm.wSecond * 2 * PI / 60 + tm.wMilliseconds * 2 * PI / 60000;
  phimin = 2 * PI  * tm.wMinute / 60 + phis / 60;
  phih = (tm.wHour % 12) * 2 * PI / 12 + phimin / 12;

  DrawHand(hDc, X, Y, lh - 35, 35, sin(phih), cos(phih), RGB(0, 0, 0));
  DrawHand(hDc, X, Y, lm - 25, 25, sin(phimin), cos(phimin), RGB(0, 0, 0));
  DrawHand(hDc, X, Y, lsec - 10, 10, sin(phis), cos(phis), RGB(255, 0, 0));
}

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

  ShowWindow(hWnd, SW_SHOWMAXIMIZED);
  UpdateWindow(hWnd);
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
} /* End of 'WinMain' function */

/* Main window messages processing function.
 * ARGUMENTS:
 *   - descriptor of window:
 *       HWND hWnd;
 *   - number of mesage:
 *       UINT Msg;
 *   - parameter of mesage ('word parameter'):
 *       WPARAM wParam;
 *   - parameter of mesage ('long parameter'):
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) - depends on mesage.
 */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDc;  
  POINT pt;
  PAINTSTRUCT ps;
  BITMAP bm;
  INT x, y, len;
  SYSTEMTIME tm;
  MINMAXINFO *minmax;
  CREATESTRUCT *cs;
  CHAR *week[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  static SIZE s;
  static INT w, h;
  static HBITMAP hBm, hBmAnd, hBmXor;
  static HDC hMemDc, hDcAnd, hDcXor;
  static HFONT hFnt;
  static CHAR Buf[1000];

  switch (Msg)
  {
  case WM_CREATE:
    cs = (LPARAM *)lParam;
    hDc = GetDC(hWnd);
    hMemDc = CreateCompatibleDC(hDc);
    hDcAnd = CreateCompatibleDC(hDc);
    hDcXor = CreateCompatibleDC(hDc);
    ReleaseDC(hWnd, hDc);

    hBmAnd = LoadImage(cs->hInstance, (CHAR *)IDB_BITMAP1, IMAGE_BITMAP, 0, 0, 0);
    hBmXor = LoadImage(cs->hInstance, (CHAR *)IDB_BITMAP2, IMAGE_BITMAP, 0, 0, 0);
    hFnt = CreateFont(70, 0, 0, 300, FW_BOLD, TRUE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
      PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "Comic Sans MS");
 
    SelectObject(hDcAnd, hBmAnd);
    SelectObject(hDcXor, hBmXor);
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
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    else if (wParam == 'F')
      FlipFullScreen(hWnd);
    return 0;
  case WM_TIMER:
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    hDc = hMemDc;
    SelectObject(hDc, GetStockObject(DC_PEN));
    SelectObject(hDc, GetStockObject(DC_BRUSH));
    SetDCPenColor(hDc, RGB(255, 255, 255));
    SetDCBrushColor(hDc, RGB(0, 255, 255));
    Rectangle(hDc, 0, 0, w, h);
    GetObject(hBmAnd, sizeof(BITMAP), &bm);
    BitBlt(hDc, w / 2 - bm.bmWidth / 2, h / 2 - bm.bmHeight / 2, bm.bmWidth, bm.bmHeight, hDcAnd, 0, 0, SRCAND);
    BitBlt(hDc, w / 2 - bm.bmWidth / 2, h / 2 - bm.bmHeight / 2, bm.bmWidth, bm.bmHeight, hDcXor, 0, 0, SRCINVERT);
    DrawClock(hDc, w / 2, h / 2, bm.bmWidth);

    GetLocalTime(&tm);
    SelectObject(hMemDc, hFnt);
    len = sprintf(Buf, "%s %02i.%02i.%i %02i:%02i:%02i", week[tm.wDayOfWeek], tm.wDay, tm.wMonth, tm.wYear, tm.wHour, tm.wMinute, tm.wSecond);
    GetTextExtentPoint(hDc, Buf, len, &s);
    SetBkMode(hDc, TRANSPARENT);
    TextOut(hDc, w / 2 - s.cx / 2, h - 70, Buf, len);
    SetDCPenColor(hDc, RGB(255, 255, 255));
    SetDCBrushColor(hDc, RGB(0, 255, 255));
    Ellipse(hDc, w / 2- 35, h / 2 - 35, w / 2 + 35, h / 2 + 35);

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_PAINT:
    hDc = BeginPaint(hWnd, &ps);
    BitBlt(hDc, 0, 0, w, h, hMemDc, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_GETMINMAXINFO:
    minmax = (MINMAXINFO *)lParam;
    minmax->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) +
      GetSystemMetrics(SM_CYBORDER) * 2 + 500;
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
    DeleteObject(hFnt);
    DeleteDC(hDcAnd);
    DeleteDC(hDcXor);
    DeleteObject(hBmAnd);
    DeleteObject(hBmXor);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    KillTimer(hWnd, 47);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);

} /* End of 'MyWindowFunc' function */

/* END OF 'T03CLOCK.C' FILE */
