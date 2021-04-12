/* FILE NAME: anim.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#ifndef __ANIM_H_
#define __ANIM_H_

#include "INPUT/INPUT.H"


#include "RND/RENDER.H"



namespace degl
{

  class anim;

  class unit 
  {
  public:
    unit( VOID )
    {
      
    }
    virtual ~unit( VOID )
    {
    }



    virtual VOID Render( anim *Ani )
    {
    }
    virtual VOID Response( anim *Ani )
    {
    }
  };


  class anim : public win, public render, public input, public unit
  {
  private:
    //stock<unit *> Units;
    anim( VOID );
    ~anim( VOID );
  public:
    std::vector<unit *> Units;
    static anim & Get( VOID );
    /* Initialization function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    VOID Init( VOID );

    /* Deinitialization function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    VOID Close( VOID );

    /* Change window size handle function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    VOID Resize( INT W, INT H );

    /* Erase background handle function.
    * ARGUMENTS:
    *   - device context of client area:
    *       HDC hDC;
    * RETURNS: None.
    */
    VOID Erase( HDC hDC );

    /* Paint window content function.
    * ARGUMENTS:
    *   - device context of client area:
    *       HDC hDC;
    * RETURNS: None.
    */
    VOID Paint( VOID );

    /* Timer handle function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    VOID Timer( VOID );

  };

  
}

#endif