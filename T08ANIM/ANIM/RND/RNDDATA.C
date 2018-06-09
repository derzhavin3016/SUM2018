/* FILE NAME: RNDDATA.C
  * PROGRAMMER: AD6
  * DATE: 09.06.2018
  */
#include "rnd.h"
HWND AD6_hWndRnd;
HDC AD6_hDCRndFrame;
HBITMAP AD6_hBmRndFrame;
INT AD6_RndFrameW, AD6_RndFrameH;
DBL
  AD6_RndProjSize = 0.1,  /* Project plane fit square */
  AD6_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
  AD6_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */

MATR
  AD6_RndMatrView, /* View coordinate system matrix */
  AD6_RndMatrProj, /* Projection coordinate system matrix */
  AD6_RndMatrVP;   /* Stored (View * Proj) matrix */

