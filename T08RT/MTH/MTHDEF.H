/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : MTHDEF.H
* PURPOSE     : Ray tracing.
*               Math definitions.
* PROGRAMMER  : AD6.
* LAST UPDATE : 24.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/


#ifndef __MTHDEF_H_
#define __MTHDEF_H_

#include <COMMONDF.H>
#include <cmath>
#include <windows.h>

typedef double DBL;
typedef float FLT;


namespace mth
{
  template <class T>
    class camera;

  template <class T>
    class matr;

  template <class T>
    class ray;

  const DBL PI = 3.14159265358979323846;

  template<typename T>
    T D2R( T AngleinDegree )
    {
      return AngleinDegree * PI / 180;
    }

  template<typename T>
    T Clamp( T Value, T A, T B )
    {
      return Value < A ? A : Value > B ? B : Value;
    }

  template<typename T>
    T Min( T A, T B )
    {
      return A < B ? A : B;
    }

  template<typename T>
    T Max( T A, T B )
    {
      return A > B ? A : B;
    }

  template<typename T>
    VOID Swap( T &A, T &B )
    {
      T tmp = A;
      A = B;
      B = tmp;
    }

  template<typename T>
    T sqr( T A )
    {
      return A * A;
    }

    /* Number sign function (template).
     * ARGUMENTS:
     *   - number:
     *      T A;
     * RETURNS:
     *     (INT) 0 if A is zero, 1 if A positive, -1 if A negative.
     */
    template <class T>
      INT Sign( T A )
      {
        return A == 0 ? 0 : A > 0 ? 1 : -1;
      } /* End of 'Sign' function */

    
    const auto Infinity = 1e30;

  template <class T>
    class vec;

  template <class T>
    class vec2;

  template <class T>
    class vec4;
} /* End of 'mth' namespace */ 

#endif /* __MTHDEF_H_ */

/* End of 'mthdef.h' file */
