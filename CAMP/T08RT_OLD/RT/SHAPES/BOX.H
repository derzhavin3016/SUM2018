/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : BOX.H
* PURPOSE     : Ray tracing.
*               Shapes.
*               Box (rectangular parallelepiped).
* PROGRAMMER  : AD6.
* LAST UPDATE : 25.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __BOX_H_
#define __BOX_H_

#include "SHAPE.H"

namespace dert
{
  class box : public shape
  {
  private:
    vec B1, B2;  // Two opposite verticies
  public:

    // Default constructor
    box( VOID )
    {
    }


    /* Set verticies of box function
     * ARGUMENTS: 
     *   - reference to opposite verticies:
     *        vec &BF, vec &BS;
     * RETURNS: None.
     */
    VOID SetVertex( const vec &BF, const vec &BS );

    /* Box constructor function
     * ARGUMENTS: 
     *   - reference to opposite verticies:
     *        vec &BF, vec &BS;
     *   - reference to material type:
     *        material &Mtl;
     *   - reference to environment type:
     *        environment &Env;
     * RETURNS: None.
     */
     box( const vec &BF, const vec &BS, const material &Mt, const environment &Env ) : B1(BF),  
       B2(BS), shape(Mt, Env)
     {
     } /* End of 'box' function */
    
    /* Find intersection with box function
     * ARGUMENTS: 
     *   - reference to ray to find intersection with:
     *        ray &R;
     * RETURNS:
     *       (BOOL) TRUE if intersection is found, FALSE otherwise.
     */
     BOOL IsIntersect( const ray &R );

    /* Find intersection with box function
     * ARGUMENTS: 
     *   - reference to ray to find intersection with:
     *        ray &R;
     *   - pointer to intersection type:
     *        intr *Intr;
     * RETURNS:
     *       (BOOL) TRUE if intersection is found, FALSE otherwise.
     */
     BOOL Intersect( const ray &R, intr *Intr ) override;

    /* Find all intersections function (virtual)
     * ARGUMENTS: 
     *   - reference to ray to find intersections with:
     *        ray &R;
     *   - pointer to intersections type:
     *        intr_list *IList;
     * RETURNS:
     *       (INT) Amount of intersections.
     */
     INT AllIntersect( const ray &R, intr_list *IList ) override;

    /* Box normal evaluation function
     * ARGUMENTS:
     *   - pointer to intersection type:
     *        intr *Intr;
     * RETURNS: None.
     */
     VOID EvalNormal( intr *Intr ) override;

  };
} /* End of 'dert' namespace */




#endif /* __BOX_H_ */

/* End of 'BOX.H' file */
