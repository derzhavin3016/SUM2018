/* FILE NAME: T07SPHERE
  * PROGRAMMER: AD6
  * DATE: 06.06.2018
  */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>


#define PI 3.14159265358979323846
#define N 8
#define M 18
/* Main window class name */
#define WND_CLASS_NAME "My window class"

typedef DOUBLE DBL;

typedef struct
{
  DBL x, y, z;
} VECT;
VECT S[N][M]

VECT Veccor( INT X, INT Y, INT Z )
{
  VECT V = {X, Y, Z};
  return V;
}
VOID RotateZ( VECT V, INT R )
{
  INT i, j;
  DBL teta, phi, sit = sin(teta), cot = cos(teta), cop = cos(phi), sip = sin(phi);

  for (j = 0; j < N; j++)
  {
    teta = j * PI / (N - 1);
    for (i = 0; i < M; i++)
    {
      phi = i * 2 * PI / (M - 1);
      S[j][i] = (R * sip * sint, R * cot, )
    }
  }

}

VOID DrawSphere( HDC hDc, INT x, INT y, INT r )
{
  INT i, j, x1, y1;
  DBL teta = 0;
 
  for (j = 0; z < N; z++)
  {
    teta = z * PI / N;
  for (i = 0; i < M; i++)
  {
    x1 = x + r * sin(teta) * cos(i * 2 * PI / N);
    y1 = y - r * sin(teta) * sin(i * 2 * PI / N);
    SetPixel(hDc, x1, y1, RGB(0, 200, 0));
  
  }
  }
}


/* Forward references */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

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
    "SPHERE",
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
  SYSTEMTIME tm;
  static INT w, h;
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
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;
  case WM_TIMER:
    SelectObject(hMemDc, GetStockObject(DC_PEN));
    SelectObject(hMemDc, GetStockObject(DC_BRUSH));
    SetDCPenColor(hMemDc, RGB(255, 255, 255));
    SetDCBrushColor(hMemDc, RGB(0, 0, 0));
    Rectangle(hMemDc, 0, 0, w, h);
    
    DrawSphere(hMemDc, w / 2, h / 2, 250);

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

/* END OF 'T03CLOCK.C' FILE */