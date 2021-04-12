/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : SOLVE4.H
* PURPOSE     : Ray tracing.
*               Math support.
*               Solve fourth-degree equation header.
* PROGRAMMER  : AD6.
* LAST UPDATE : 31.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __SOLVE4_H_
#define __SOLVE4_H_

#include "MTHDEF.H"

namespace mth
{
  /* Solve equation of the fourth degree function.
   * ARGUMENTS:
   *    - pointer to roots array:
   *        DBL *Roots;
   *    - Equation coefficients:
   *        DBL A, B, C, D, E;
   * RETURNS:
   *   (INT) amount of real roots.
   */
  INT Solve4( DBL *Roots, DBL A, DBL B, DBL C, DBL D, DBL E );
  
  /* Solve equation of the third degree function (static).
   * ARGUMENTS:
   *    - pointer to roots array:
   *        DBL *Roots;
   *    - Equation coefficients:
   *        DBL A, B, C, D;
   * RETURNS:
   *   (INT) amount of real roots.
   */
  INT Solve3( DBL *Roots, DBL A, DBL B, DBL C, DBL D );
  
  /* Solve equation of the second degree function (static).
   * ARGUMENTS:
   *    - pointer to roots array:
   *        DBL *Roots;
   *    - Equation coefficients:
   *        DBL A, B, C;
   * RETURNS:
   *   (INT) amount of real roots.
   */
  INT Solve2( DBL *Roots, DBL A, DBL B, DBL C );
}

#endif /* __SOLVE4_H_ */

/* End of 'SOLVE4.H' file */