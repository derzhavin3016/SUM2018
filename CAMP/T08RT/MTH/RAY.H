/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : Ray.H
* PURPOSE     : Ray tracing.
*               Ray class.
* PROGRAMMER  : AD6.
* LAST UPDATE : 25.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __RAY_H_
#define __RAY_H_

#include "MTHDEF.H"

namespace mth
{
  template<class T>
    class ray
    {
    public:
      vec<T> Org, Dir; // Origin and Direction vectors

      /* Default ray constructor
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      ray( VOID ) : Org(0), Dir(0)
      {
      } /* End of 'ray' function */

      /* Copying ray constructor
       * ARGUMENTS: 
       *   - refernce to ray to copy:
       *        ray<T> &R;
       * RETURNS: None.
       */
      ray( const ray<T> &R ) : Org(R.Org), Dir(R.Dir.Normalize())
      {
      } /* End of 'ray' function */

      /* Ray constructor
       * ARGUMENTS: 
       *   - refernce to origin and direction vectors:
       *        vec<T> &R, &D;
       * RETURNS: None.
       */
      ray( const vec<T> &O, const vec<T> &D ) : Org(O), Dir(D)
      {
        Dir.Normalizing();
      } /* End of 'ray' function */

      /* Get point on ray function ( reload ())
       * ARGUMENTS: 
       *   - coefficient:
       *        T t;
       * RETURNS:
       *       (vec<T>) result vector
       */
      vec<T> operator()( const T t ) const
      {
        return Org + Dir * t;
      } /* End of 'operator()' function */

      vec<T> GetDir( VOID )
      {
        return Dir;
      }

    };
} /* End of 'mth' namespace */

#endif /* __RAY_H_ */


