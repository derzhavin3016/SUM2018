/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : TRIAN.H
* PURPOSE     : Ray tracing.
*               Shapes.
*               Triangle.
* PROGRAMMER  : AD6.
* LAST UPDATE : 20.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __TRIAN_H_
#define __TRIAN_H_

#include "PLANE.H"

namespace dert
{
  class triangle : public shape
  {
  private:
    vec A, B, C;  // 3 verticies
    plane P;      // Plane which contain triangle
    vec U1, V1;   // Addon vectors for barycentric coordinates
    DBL u0, v0;   // Addon parameters for barycentric coordinates
  public:

    // Default constructor
    triangle( VOID )
    {
    }

    /* Triangle constructor function
     * ARGUMENTS: 
     *   - reference to 3 points:
     *        vec &P0, &P1, &P2;
     *   - reference to material type:
     *        material &Mtl;
     *   - reference to environment type:
     *        environment &Env;
     * RETURNS: None.
     */
    triangle( const vec &P0, const vec &P1, const vec &P2,
              const material &Mtl, const environment &Env );

    /* Find intersection with triangle function
     * ARGUMENTS: 
     *   - reference to ray to find intersection with:
     *        ray &R;
     *   - reference to intersection type:
     *        intr *Intr;
     * RETURNS:
     *       (BOOL) TRUE if intersection is found, FALSE otherwise.
     */
    BOOL Intersect( const ray &R, intr *Intr ) override;

     /* Find all intersections with triangle function
      * ARGUMENTS: 
      *   - reference to ray to find intersections with:
      *        ray &R;
      *   - pointer to intersections type:
      *        intr_list *Intr;
      * RETURNS:
      *       (INT) Amount of intersections.
      */
     INT AllIntersect( const ray &R, intr_list *IList ) override;

     /* Normal evaluation function
      * ARGUMENTS:
      *   - pointer to intersection type:
      *        intr *Intr;
      * RETURNS: None.
      */
      VOID EvalNormal( intr *Intr ) override;
  };
} /* End of 'dert' namespace */

#endif /* __TRIAN_H_ */

/* End of 'TRIAN.H' file */
