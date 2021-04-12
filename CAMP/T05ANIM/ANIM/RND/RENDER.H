/* FILE NAME: render.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/


#ifndef __RENDER_H_
#define __RENDER_H_

#include "../PRIM/PRIMS.H"
#include "../TIMER/TIMER.H"
#include "../../DEF.H"

namespace degl
{
  class render : public timer, public prims
  {
  protected:
    HWND hWndWork;
    HDC hDC;
    HGLRC hGLRC;
    INT W, H;
    /*stock<prim> Prim; 
    prim *Pr;*/
  public:
    camera Cam;

    render(HWND hWorkWnd, INT WRef, INT HRef);


    ~render( VOID );

    VOID FrameStart( VOID );

    VOID FrameEnd( VOID );

    VOID FrameCopy( VOID );

    VOID RndResize( INT Wh, INT Hh );

    VOID PrimDraw( prim *P, matr World , INT Count);

    VOID PrsDraw( prims *Pr, const matr &World );


  };
}
#endif


/* End of 'render.h' file */
