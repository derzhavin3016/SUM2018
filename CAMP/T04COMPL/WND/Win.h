#include"../RND/RND.h"

struct win
{

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
  static LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );


  win( void )
  {
    WNDCLASS wc;
    HWND hWnd;
    HINSTANCE hInstance = GetModuleHandle(NULL);

    wc.style = CS_VREDRAW | CS_HREDRAW;                    /* Window style */
    wc.cbClsExtra = 0;                                     /* Additional bytes amount for class */
    wc.cbWndExtra = 0;                                     /* Additional bytes amount for window */
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;               /* Background color */
    wc.hCursor = LoadCursor(NULL, IDC_HAND);               /* Cursor loading */
    wc.hIcon = LoadIcon(NULL, IDI_INFORMATION);            /* Icon loading */
    wc.lpszMenuName = NULL;                                /* Menu resource name */
    wc.hInstance = hInstance;                              /* Handle application class register */
    wc.lpfnWndProc = MyWindowFunc;                         /* Pointer to rendering function */
    wc.lpszClassName = "My window class";                     /* Window class name */                                                           /* Registering window class */    if (!RegisterClass(&wc))
    {
      MessageBox(NULL, "Error register window class", "ERROR", MB_OK | MB_ICONERROR);
      return;
    }

    /* Window create */
    hWnd = 
      CreateWindow(WND_CLASS_NAME, 
        "CGSG forever",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);

    /* Show and draw the window */
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);
  }

  int Run( void )
  {
    MSG msg;
    
    /* Dispatch messages loop */
    while (GetMessage(&msg, NULL, 0, 0))
    {
      /* Translate mesages from keyboard */
      TranslateMessage(&msg);

      /* Messages to window function */
      DispatchMessage(&msg);
    }
    return msg.wParam;
  }
};
