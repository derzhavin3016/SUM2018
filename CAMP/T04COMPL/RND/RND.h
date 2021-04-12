#include <windows.h>
#include <conio.h>
#include <cmath>
#include <ctime>
/*#define GLEW_STATIC
#include <glew.h>*/
#include <gl/GL.h>
#include <gl/GLU.h>
#include "../MTH/Compl.h"


#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

#define WND_CLASS_NAME "My window class"

extern HWND AD6_hRndWnd;                           /* Work window handle */
extern HDC AD6_hRndDC;                        /* Work window device context */
extern HGLRC AD6_hRndRC;                           /* OpenGL rendering context */
extern INT AD6_RndFrameW, AD6_RndFrameH;      /* Frame size */

VOID AD6_RndInit( VOID );
VOID AD6_RndResize( VOID );
VOID AD6_RndStart( VOID );
VOID AD6_RndRender( VOID );
VOID AD6_RndEnd( VOID );
VOID AD6_RndClose( VOID );
VOID AD6_RndFlipFullScreen( HWND hWnd );
VOID AD6_MdlInit( VOID );

/* End of 'RND.H' file */
