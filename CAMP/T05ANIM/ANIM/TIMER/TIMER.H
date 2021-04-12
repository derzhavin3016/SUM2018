/* FILE NAME: TIMER.H
* PROGRAMMER: AD6
* LAST UPDATE: 13.07.2018
* PURPOSE
*/


#ifndef __TIMER_H_
#define __TIMER_H_

#include <ctime>
//#include "../../WND/WIN.H"
#include "../../DEF.H"




namespace degl
{
  class timer
  {
  public:
    unsigned __int64
      StartTime,    /* Start program time */
      OldTime,      /* Previous frame time */
      OldTimeFPS,   /* Old time FPS measurement */
      PauseTime,    /* Time during pause period */
      TimePerSec,   /* Timer resolution */
      FrameCounter; /* Frames counter */
    DBL
      GlobalTime, GlobalDeltaTime,  /* Global time and interframe interval */
      Time, DeltaTime,              /* Time with pause and interframe interval */
      FPS;                          /* Frames per second value */
    BOOL
      IsPause;                      /* Pause flag */

    timer( VOID );
    VOID Responce( VOID );

  };
}

#endif
/* End of 'TIMER.H' file */