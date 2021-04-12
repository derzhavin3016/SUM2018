/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : WIN.H
* PURPOSE     : Ray tracing.
*               Window class.
* PROGRAMMER  : AD6.
* LAST UPDATE : 24.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/


#ifndef __WIN_H_
#define __WIN_H_


#include "../DEF.H"

#define MY_WINDOW_WS (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU)

namespace dert
{
  class win
  {
  protected:
    HWND hWnd;                         /* Window handle */
    INT W, H;                          /* Window size    */
    HINSTANCE hInstance;               /* Application handle */
    const CHAR *WND_CLASS_NAME;        /* Window class name    */
    BOOL IsInit;
  private:
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
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
  public:
    BOOL IsActive;

    win( HINSTANCE hInst = GetModuleHandle(NULL) );


    ~win( VOID )
    {
    } 

    INT Run( VOID );

    /* Flip full screen function
    * ARGUMENTS: 
    *   - window handle:
    *       HWND hWnd;
    * RETURNS: NONE
    */
    VOID FlipFullScreen( HWND hWnd );

    /* message cracks */
    VOID OnGetMinMaxInfo( MINMAXINFO *MinMax );
    BOOL OnCreate( CREATESTRUCT *CS );
    VOID OnSize( UINT State, INT W, INT H );
    VOID OnTimer( INT Id );
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );
    BOOL OnEraseBackground( HDC hDC );
    VOID OnPaint( VOID );
    VOID OnClose( VOID );
    VOID OnDestroy( VOID );
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
    VOID OnKeyDown( WPARAM wParam );

    /***
    * Virtual functions for window customization
    ***/

    /* Initialization function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    virtual VOID Init( VOID )
    {
    } /* End of 'Init' function */

    /* Deinitialization function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    virtual VOID Close( VOID )
    {
    } /* End of 'Close' function */

    /* Change window size handle function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    virtual VOID Resize( VOID )
    { 
    } /* End of 'Resize' function */

    /* Erase background handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Erase( HDC hDC )
    {
    } /* End of 'Erase' function */

    /* Paint window content function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Paint( HDC hDC )
    {
    } /* End of 'Paint' function */

    /* Timer handle function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    virtual VOID Timer( VOID )
    {

    } /* End of 'Timer' function */

    /* Activate handle function.
    * ARGUMENTS:
    *   - activation window flag:
    *       BOOL IsActive;
    * RETURNS: None.
    */
    virtual VOID Activate( BOOL IsActive )
    {
    } /* End of 'Activate' function */

    /* Free CPU time handling function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    virtual VOID Idle( VOID )
    {
    } /* End of 'Idle' function */
  };
}

#endif /* __WIN_H_ */

/* End of 'Win.h' file */
