/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : PLANE.CPP
* PURPOSE     : Ray tracing.
*               Shapes.
*               Plane.
*               Function realizations.
* PROGRAMMER  : AD6.
* LAST UPDATE : 27.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "PLANE.H"

/* Find intersection with plane function
 * ARGUMENTS: 
 *   - reference to ray to find intersection with:
 *        ray &R;
 *   - reference to intersection type:
 *        intr &Intr;
 * RETURNS:
 *       (BOOL) TRUE if intersection is found, FALSE otherwise.
 */
BOOL dert::plane::Intersect( const ray &R, intr *Intr )
{
  DBL nd = N & R.Dir, T;
  if (nd == 0)
    return FALSE;
  T = -((N & R.Org) - D) / nd;
  if (T < 0)
    return FALSE;
  Intr->T = T;
  Intr->Shp = this;
  Intr->IsEnter = TRUE;
  return TRUE;
} /* End of 'dert::plane::Intersect' function */

/* Find all intersections with plane function
 * ARGUMENTS: 
 *   - reference to ray to find intersections with:
 *        ray &R;
 *   - pointer to intersections type:
 *        intr_list *Intr;
 * RETURNS:
 *       (INT) Amount of intersections.
 */
INT dert::plane::AllIntersect( const ray &R, intr_list *IList )
{
  intr Intr;
  if (Intersect(R, &Intr))
  {
    IList->push_back(Intr);
    return 1;
  }
  return 0;
} /* End of 'dert::plane::AllIntersect' function */

/* Plane normal evaluation function
 * ARGUMENTS:
 *   - pointer to intersection type:
 *        intr *Intr;
 * RETURNS: None.
 */
VOID dert::plane::EvalNormal( intr *Intr )
{
  Intr->N = N;
} /* End of 'dert::plane::EvalNormal' function */



/* End of 'plane.cpp' file */