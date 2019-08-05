/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : QUAD.H
* PURPOSE     : Ray tracing.
*               Shapes.
*               Quadrics.
* PROGRAMMER  : AD6.
* LAST UPDATE : 27.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __QUAD_H_
#define __QUAD_H_

#include "SHAPE.H"

namespace dert
{
  class quad : public shape
  {
  private:
    DBL 
      A, B, C, D, E, F, G, H, I, J; // Coefficients
  public:

    // Default constructor
    quad( VOID )
    {
    }

    /* Quadrics constructor function
     * ARGUMENTS: 
     *   - quadrics coefficients:
     *        DBL A1, B1, C1, D1, E1, F1, G1, H1, I1, J1;
     *   - reference to material type:
     *        material &Mtl;
     *   - reference to environment type:
     *        environment &Env;
     * RETURNS: None.
     */
     quad( DBL A1, DBL B1, DBL C1, DBL D1, DBL E1, DBL F1, DBL G1, DBL H1, DBL I1, DBL J1,
           const material &Mt, const environment &Env ) : 
       A(A1), B(B1), C(C1), D(D1), E(E1), F(F1), G(G1), H(H1), I(I1), J(J1),
       shape(Mt, Env)
     {
     } /* End of 'quad' function */

    /* Find intersection with quadrics function
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

    /* Quadrics normal evaluation function
     * ARGUMENTS:
     *   - pointer to intersection type:
     *        intr &Intr;
     * RETURNS: None.
     */
     VOID EvalNormal( intr *Intr ) override;

  };
} /* End of 'dert' namespace */




#endif /* __BOX_H_ */

/* End of 'BOX.H' file */
