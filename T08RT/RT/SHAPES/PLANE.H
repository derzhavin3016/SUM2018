/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : PLANE.H
* PURPOSE     : Ray tracing.
*               Shapes.
*               Plane.
* PROGRAMMER  : AD6.
* LAST UPDATE : 27.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __PLANE_H_
#define __PLANE_H_

#include "SHAPE.H"

namespace dert
{
  class plane : public shape
  {
  private:
    vec N;            // Plane normal
    DBL D;            // Distance from plane to 0 (cartesian coordinates)
  public:
    // Default constructor
    plane( VOID )
    {
    
    }

   /* Plane constructor function
    * ARGUMENTS: 
    *   - reference to plane normal:
    *        vec &Nr;
    *   - distance from plane to 0:
    *        DBL Di;
    * RETURNS: None.
    */
    plane( const vec &Nr, DBL Di, const material &Mt, const environment &Env ) : N(Nr), D(Di), shape(Mt, Env)
    {
      N.Normalizing();
    } /* End of 'plane' function */


   /* Plane constructor function (by point of plane and normal)
    * ARGUMENTS: 
    *   - reference to plane normal:
    *        vec &Nr;
    *   - reference to plane point:
    *        vec &M;
    * RETURNS: None.
    */
    plane( const vec &Nr, const vec &M, const material &Mt, const environment &Env ) : N(Nr), shape(Mt, Env)
    {
      N.Normalizing();
      D = M & N;
    } /* End of 'plane' function */

   /* Plane constructor function (by 3 points)
    * ARGUMENTS: 
    *   - reference to 3 points:
    *        vec &P0, &P1, &P2;
    * RETURNS: None.
    */
    plane( const vec &P0, const vec &P1, const vec &P2, const material &Mt, const environment &Env ) : shape(Mt, Env)
    {
      N = ((P1 - P0) % (P2 - P0)).Normalize();
      D = N & P1;
    } /* End of 'plane' function */

    /* Plane constructor function (by 3 points)
    * ARGUMENTS: 
    *   - reference to 3 points:
    *        vec &P0, &P1, &P2;
    * RETURNS: None.
    */
    plane( const vec &P0, const vec &P1, const vec &P2 )
    {
      N = ((P1 - P0) % (P2 - P0)).Normalize();
      D = N & P1;
    } /* End of 'plane' function */

   /* Find intersection with plane function
    * ARGUMENTS: 
    *   - reference to ray to find intersection with:
    *        ray &R;
    *   - reference to intersection type:
    *        intr &Intr;
    * RETURNS:
    *       (BOOL) TRUE if intersection is found, FALSE otherwise.
    */
    BOOL Intersect( const ray &R, intr *Intr ) override;

    /* Find all intersections with plane function
     * ARGUMENTS: 
     *   - reference to ray to find intersections with:
     *        ray &R;
     *   - pointer to intersections type:
     *        intr_list *Intr;
     * RETURNS:
     *       (INT) Amount of intersections.
     */
     INT AllIntersect( const ray &R, intr_list *IList ) override;

    /* Plane normal evaluation function
     * ARGUMENTS:
     *   - pointer to intersection type:
     *        intr *Intr;
     * RETURNS: None.
     */
     VOID EvalNormal( intr *Intr ) override;

     vec GetNormal( VOID ) const
     {
       return N;
     }
  };
} /* End of 'dert' namespace */




#endif /* __SPHERE_H_ */

/* End of 'SPHERE.H' file */
