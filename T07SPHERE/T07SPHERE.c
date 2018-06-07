/* FILE NAME: T07SPH
  * PROGRAMMER: AD6
  * DATE: 06.06.2018
  */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

/* PI contstant */
#define PI 3.14159265358979323846

/* Grid size */
#define N 10
#define M 21

/* Main window class name */
#define WND_CLASS_NAME "My window class"

/* Useful float point type */
typedef DOUBLE DBL;

/* Space vector representation type */
typedef struct
{
  DBL x, y, z; /* Cartesian coordinates */
} VECT;

/* Geometry grid */
static VECT S[N][M]; 


/* Vector set function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       DBL X, Y, Z;
 * RETURNS:
 *   (VECT) result vector.
 */
VECT Veccor( DBL X, DBL Y, DBL Z )
{
  VECT V = {X, Y, Z};
  return V;
} /* End of 'Veccor' function */

/* Vector rotate around Z axis function.
 * ARGUMENTS:
 *   - vector:
 *       VECT V;
 *   - rotation angle in degree:
 *       DBL Angled;
 * RETURNS:
 * (VECT) result vector.
 */   
VECT RotateZ( VECT V, DBL Angled )
{
  DBL a = Angled * PI / 180, co = cos(a), si = sin(a);

  return Veccor(V.x * co - V.y * si, V.x * si + V.y * co, V.z);
} /* End of 'RotateZ' function */

/* Vector rotate around Y axis function.
 * ARGUMENTS:
 *   - vector:
 *       VECT V;
 *   - rotation angle in degree:
 *       DBL Angled;
 * RETURNS:
 *   (VECT) result vector.
 */
VECT RotateY( VECT V, DBL Angled )
{
  DBL a = Angled * PI / 180, co = cos(a), si = sin(a);

  return Veccor(V.z * si + V.x * co, V.y, V.z * co - V.x * si);
} /* End of 'RotateY' function */

/* Vector rotate around X axis function.
 * ARGUMENTS:
 *   - vector:
 *       VECT V;
 *   - rotation angle in degree:
 *       DBL Angled;
 * RETURNS:
 *   (VECT) result vector.
 */
VECT RotateX( VECT V, DBL Angled )
{
  DBL a = Angled * PI / 180, co = cos(a), si = sin(a);

  return Veccor(V.x, V.y * co + V.z * si, V.z * co - V.y * si);
} /* End of 'RotateX' function */

/* Make sphere points and finding coordinates.
 * ARGUMENTS: 
 *   - radius:
         INT R
 * RETURNS: None.
 */
VOID MakeSphere( INT R )
{
  INT i, j;

  for (i = 0; i < N; i++)
  {
    DBL teta = i * PI / (N - 1), sit = sin(teta), cot = cos(teta);
    for (j = 0; j < M; j++)
    {
      DBL phi = j * 2 * PI / (M - 1), sip = sin(phi), cop = cos(phi);

      S[i][j] = Veccor(R * sip * sit, R * cot, R * cop * sit);
    }
  }
} /* End of 'MakeSphere' function */

/* Draw sphere function.
 * ARGUMENTS:
 *   - device context:
 *       HDC hDC;
 *   - center point coordinates:
 *       INT X0, Y0;
 *   - radius:
 *       INT R;
 * RETURNS: None.
 */
VOID DrawSphere( HDC hDc, INT x0, INT y0, INT r )
{
  INT i, j, x1, y1;
  DBL t = clock() / (DBL)CLOCKS_PER_SEC;
  static POINT P[N][M];
 
  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
    {
      VECT V = RotateX(RotateY(RotateZ(S[i][j], 18 * t), - 30 * t),  - 20 * t);
      P[i][j].x = (INT)(x0 + r * V.x);
      P[i][j].y = (INT)(y0 - r * V.y);
      SetDCPenColor(hDc, RGB( 0, 200, 200));
      SetDCBrushColor(hDc, RGB(0, 200, 0));
      Ellipse(hDc, P[i][j].x - 5, P[i][j].y - 5, P[i][j].x + 5, P[i][j].y + 5);
      //SetPixel(hDc, P[i][j].x, P[i][j].y, RGB(0, 0, 200));
    }
  for (i = 0; i < N; i++)
  {
    MoveToEx(hDc, P[i][0].x, P[i][0].y, 0);
    SetDCPenColor(hDc, RGB(200, 60, 0));
    for (j = 1; j < M; j++)

      LineTo(hDc, P[i][j].x, P[i][j].y);
  }
  for (i = 0; i < M; i++)
  {
    MoveToEx(hDc, P[0][i].x, P[0][i].y, 0);
    for (j = 1; j < N; j++)
      LineTo(hDc, P[j][i].x, P[j][i].y);
  }
}  /* End of 'DrawSphere' function */


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
  INT R = 1;
  POINT pt;
  PAINTSTRUCT ps;
  SYSTEMTIME tm;
  static INT w, h;
  static HBITMAP hBm;
  static HDC hMemDc;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 47, 3, NULL);
    hDc = GetDC(hWnd);
    hMemDc = CreateCompatibleDC(hDc);
    ReleaseDC(hWnd, hDc);

    MakeSphere(R);
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
    
    MakeSphere(R);
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

/* END OF 'T07SPH.C' FILE */