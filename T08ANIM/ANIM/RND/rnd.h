/* FILE NAME: RND.H
  * PROGRAMMER: AD6
  * DATE: 09.06.2018
  */
#ifndef __RND_H_
#define __RND_H_
#include "../../def.h"
extern HWND AD6_hWndRnd;
extern HDC AD6_hDCRndFrame;
extern HBITMAP AD6_hBmRndFrame;
extern INT AD6_RndFrameW, AD6_RndFrameH;
extern DBL AD6_RndProjSize;
extern DBL AD6_RndProjDist;
extern DBL AD6_RndProjFarClip;
extern MATR AD6_RndMatrView;
extern MATR AD6_RndMatrProj;
extern MATR AD6_RndMatrVP;
typedef struct tagad6VERTEX
{
  VEC P;  /* Vertex position */
} ad6VERTEX;
typedef struct tagad6PRIM
{
  ad6VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */
  INT *I;       /* Index array (for trimesh – by 3 ones) */
  INT NumOfI;   /* Number of indices */
  MATR Trans;   /* Additional transformation matrix */
} ad6PRIM;
VOID AD6_RndInit( HWND hWnd );
VOID AD6_RndClose( VOID );
VOID AD6_RndResize( INT W, INT H );
VOID AD6_RndStart( VOID );
VOID AD6_RndEnd( VOID );
VOID AD6_RndCopyFrame( HDC hDC );
VOID AD6_RndProjSet( VOID );
VOID AD6_RndCamSet( VEC Loc, VEC At, VEC Up1 );
BOOL AD6_RndPrimCreate( ad6PRIM *Pr, INT NoofV, INT NoofI );
VOID AD6_RndPrimFree( ad6PRIM *Pr );
VOID AD6_RndPrimDraw( ad6PRIM *Pr, MATR World );
BOOL AD6_RndPrimLoad( ad6PRIM *Pr, CHAR *FileName );
#endif #endif /* __RND_H_ */
