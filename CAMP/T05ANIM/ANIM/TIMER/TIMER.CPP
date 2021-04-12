/* FILE NAME: TIMER.CPP
* PROGRAMMER: AD6
* LAST UPDATE: 13.07.2018
* PURPOSE
*/

#include "TIMER.H"

degl::timer::timer( VOID ) : FrameCounter(0), GlobalDeltaTime(0), GlobalTime(0), Time(0), DeltaTime(0), PauseTime(0), FPS(30.0),
                       IsPause(FALSE)
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
}

VOID degl::timer::Responce( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  
  /* Global time */
  GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (IsPause)
  {
    DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    DeltaTime = GlobalDeltaTime;
    Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  OldTime = t.QuadPart;

  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }

 
}


/* End of 'TIMER.CPP' file */
