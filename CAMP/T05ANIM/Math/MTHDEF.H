/* FILE NAME: mtdefh.h
* PROGRAMMER: AD6
* LAST UPDATE: 13.07.2018
* PURPOSE
*/


#ifndef __MTHDEF_H_
#define __MTHDEF_H_

#include <COMMONDF.H>
#include <windows.h>

typedef double DBL;
typedef float FLT;


namespace mth
{
  template <class T>
    class camera;

  template <class T>
    class matr;

  const DBL PI = 3.14159265358979323846;

  template<typename T>
  T D2R( T AngleinDegree )
  {
    return AngleinDegree * PI / 180;
  }

  template<typename T>
  T Clamp( T Value, T A, T B )
  {
    return Value <= A ? A : Value >= B ? B : Value;
  }



  template <class T>
    class vec;

  template <class T>
    class vec2;

  template <class T>
    class vec4;
} /* End of 'mth' namespace */ 

#endif /* __MTHDEF_H_ */

/* End of 'mthdef.h' file */
