/* FILE NAME: RNDBASE.C
  * PROGRAMMER: AD6
  * DATE: 09.06.2018
  */
#include "rnd.h"
VOID AD6_RndInit( HWND hWnd )
{
  HDC hDc;
  AD6_hWndRnd = hWnd;
  hDc = GetDC(AD6_hWndRnd);
  AD6_hDCRndFrame = CreateCompatibleDC(hDc);
  ReleaseDC(AD6_hWndRnd, hDc);
  AD6_RndCamSet(VecSet(8, 8, 8), VecSet(0, 0, 0), VecSet(0, 1, 0));
  //AD6_RndProjSet();
}
VOID AD6_RndClose( VOID )
{
  DeleteObject(AD6_hBmRndFrame);
  DeleteDC(AD6_hDCRndFrame);
}

VOID AD6_RndResize( INT W, INT H )
{
  HDC hDC;

  if (AD6_hBmRndFrame != NULL)
    DeleteObject(AD6_hBmRndFrame);
  hDC = GetDC(AD6_hWndRnd);
  AD6_hBmRndFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(AD6_hWndRnd, hDC);
  SelectObject(AD6_hDCRndFrame, AD6_hBmRndFrame);
 
  AD6_RndFrameW = W;
  AD6_RndFrameH = H;
  //AD6_RndProjSet();
}

VOID AD6_RndStart( VOID )
{
  SelectObject(AD6_hDCRndFrame, GetStockObject(NULL_PEN));
  SelectObject(AD6_hDCRndFrame, GetStockObject(LTGRAY_BRUSH));
  Rectangle(AD6_hDCRndFrame, 0, 0, AD6_RndFrameW, AD6_RndFrameH);

  SelectObject(AD6_hDCRndFrame, GetStockObject(BLACK_PEN));
  SelectObject(AD6_hDCRndFrame, GetStockObject(NULL_BRUSH));
}
VOID AD6_RndEnd( VOID )
{

}

VOID AD6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, AD6_RndFrameW, AD6_RndFrameH, AD6_hDCRndFrame, 0, 0,
    SRCCOPY);
}

VOID AD6_RndProjSet( VOID )
{
  DBL ratio_x, ratio_y;

  ratio_x = ratio_y = AD6_RndProjSize / 2;
  if (AD6_RndFrameW > AD6_RndFrameH) 
    ratio_x *= (DBL)(AD6_RndFrameW / AD6_RndFrameH);
  else
    ratio_y *= (DBL)(AD6_RndFrameH / AD6_RndFrameW);

  AD6_RndMatrProj = MatrFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y,
    AD6_RndProjDist, AD6_RndProjFarClip);
  AD6_RndMatrVP = MatrMulMatr(AD6_RndMatrView, AD6_RndMatrProj);
}

VOID AD6_RndCamSet( VEC Loc, VEC At, VEC Up1 )
{
  AD6_RndMatrView = MatrView(Loc, At, Up1);
  AD6_RndMatrVP = MatrMulMatr(AD6_RndMatrView, AD6_RndMatrProj);
}