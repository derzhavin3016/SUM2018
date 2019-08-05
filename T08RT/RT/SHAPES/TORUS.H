/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : TORUS.H
* PURPOSE     : Ray tracing.
*               Shapes.
*               Torus.
* PROGRAMMER  : AD6.
* LAST UPDATE : 28.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __TORUS_H_
#define __TORUS_H_

#include "SHAPE.H"

namespace dert
{
  class torus : public shape
  {
  private:
    DBL
      Rad, Rad2, r, C;  // Main and second radiuses
  public:

    // Default constructor
    torus( VOID )
    {
    }
    

    /* Toruss constructor function
     * ARGUMENTS: 
     *   - torus radiuses:
     *        DBL R1, r1;
     *   - reference to material type:
     *        material &Mtl;
     *   - reference to environment type:
     *        environment &Env;
     * RETURNS: None.
     */
    torus( DBL R1, DBL r1, const material &Mt, const environment &Env ) : 
       Rad(R1), Rad2(R1 * R1), r(r1), shape(Mt, Env)
     {
       C = (Rad2 - r * r);
     } /* End of 'torus' function */

    /* Find intersection with torus function
     * ARGUMENTS: 
     *   - reference to ray to find intersection with:
     *        ray &R;
     *   - pointer to intersection type:
     *        intr *Intr;
     * RETURNS:
     *       (BOOL) TRUE if intersection is found, FALSE otherwise.
     */
    BOOL Intersect( const ray &R, intr *Intr ) override;

    /* Find all intersections function
     * ARGUMENTS: 
     *   - reference to ray to find intersections with:
     *        ray &R;
     *   - pointer to intersections type:
     *        intr_list *IList;
     * RETURNS:
     *       (INT) Amount of intersections.
     */
    INT AllIntersect( const ray &R, intr_list *IList ) override;

    /* Torus normal evaluation function
     * ARGUMENTS:
     *   - pointer to intersection type:
     *        intr &Intr;
     * RETURNS: None.
     */
    VOID EvalNormal( intr *Intr ) override;
  };
} // End of 'dert' namespace


#endif /* __TORUS_H_ */


/* End of 'TORUS.H' file */

