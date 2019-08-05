/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : SPHERE.H
* PURPOSE     : Ray tracing.
*               Shapes.
*               Sphere.
* PROGRAMMER  : AD6.
* LAST UPDATE : 25.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __SPHERE_H_
#define __SPHERE_H_

#include "SHAPE.H"

namespace dert
{
  class sphere : public shape
  {
  private:
    vec C;            // Center of sphere
    DBL R, R2;        // Radius and square radius of sphere
  public:
    // Default constructor
    sphere( VOID )
    {
    
    }

    vec GetCenter( VOID )
    {
      return C;
    }

   /* Sphere constructor function
    * ARGUMENTS: 
    *   - reference to center of a sphere:
    *        ray &R;
    *   - radius of a sphere:
    *        DBL R;
    *   - reference to material type:
    *        material &Mtl;
    *   - reference to environment type:
    *        environment &Env;
    * RETURNS: None.
    */
    sphere( const vec &Center, DBL Rad, const material &Mt, const environment &Env ) : C(Center), R(Rad), R2(Rad * Rad), shape(Mt, Env)
    {
    } /* End of 'sphere' function */


   /* Find intersection with sphere function
    * ARGUMENTS: 
    *   - reference to ray to find intersection with:
    *        ray &R;
    *   - reference to intersection type:
    *        intr *Intr;
    * RETURNS:
    *       (BOOL) TRUE if intersection is found, FALSE otherwise.
    */
    BOOL Intersect( const ray &R, intr *Intr ) override;

    /* Find all intersections with sphere function
     * ARGUMENTS: 
     *   - reference to ray to find intersections with:
     *        ray &R;
     *   - pointer to intersections type:
     *        intr_list *Intr;
     * RETURNS:
     *       (INT) Amount of intersections.
     */
     INT AllIntersect( const ray &R, intr_list *IList ) override;

    /* Sphere normal evaluation function
     * ARGUMENTS:
     *   - pointer to intersection type:
     *        intr *Intr;
     * RETURNS: None.
     */
     VOID EvalNormal( intr *Intr ) override;
  };
} /* End of 'dert' namespace */




#endif /* __SPHERE_H_ */

/* End of 'SPHERE.H' file */
