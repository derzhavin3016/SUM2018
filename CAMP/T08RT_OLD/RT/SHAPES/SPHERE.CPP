/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : SPHERE.CPP
* PURPOSE     : Ray tracing.
*               Shapes.
*               Sphere.
*               Functions realization.
* PROGRAMMER  : AD6.
* LAST UPDATE : 25.07.2018.
* NOTE        : Module prefix 'dert'.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "SPHERE.H"

/* Find intersection with sphere function
 * ARGUMENTS: 
 *   - reference to ray to find intersection with:
 *        ray &R;
 *   - reference to intersection type:
 *        intr *Intr;
 * RETURNS:
 *       (BOOL) TRUE if intersection is found, FALSE otherwise.
 */
BOOL dert::sphere::Intersect( const ray &
                              R, intr *Intr )
{
  vec OC = C - R.Org;
  DBL
    oc2 = OC & OC,
    OK, ok2, h2;

  // Ray starts inside sphere
  if (oc2 < R2)
  {
    OK = OC & R.Dir;
    h2 = R2 - (oc2 - OK * OK);
    Intr->SetIntr(this, OK + sqrt(h2), FALSE);
    return TRUE;
  }
  // Ray starts after sphere
  OK = OC & R.Dir;
  if (OK < Threshold)
    return FALSE;
  // Ray passes by sphere
  h2 = R2 - (oc2 - OK * OK);

  if (h2 < Threshold)
    return FALSE;
  // Ray intersection sphere
  Intr->SetIntr(this, OK - sqrt(h2), TRUE);
  Intr->V[4] = C;
  return TRUE;
} /* End of 'dert::sphere::Intersect' function */

/* Find all intersections with sphere function
 * ARGUMENTS: 
 *   - reference to ray to find intersections with:
 *        ray &R;
 *   - reference
 to intersections type:
 *        intr_list &Intr;
 * RETURNS:
 *       (INT) Amount of intersections.
 */
INT dert::sphere::AllIntersect( const ray &R, intr_list *IList )
{
  vec OC = C - R.Org;
  DBL
    oc2 = OC & OC,
    OK, ok2, h2;

  // Ray starts inside sphere
  if (oc2 < R2)
  {
    OK = OC & R.Dir;
    h2 = R2 - (oc2 - OK * OK);
    IList->push_back(intr(this, OK + sqrt(h2), FALSE));
    return 1;
  }
  // Ray starts after sphere
  OK = OC & R.Dir;
  if (OK < Threshold)
    return 0;
  // Ray passes by sphere
  h2 = R2 - (oc2 - OK * OK);

  if (h2 < Threshold)
    return 0;
  // Ray intersection sphere
  IList->push_back(intr(this, OK - sqrt(h2), TRUE));
  IList->push_back(intr(this, OK + sqrt(h2), FALSE));
  return 2;
} /* End of 'AllIntersect' function */

/* Sphere normal evaluation function
 * ARGUMENTS:
 *   - pointer to intersection type:
 *        intr *Intr;
 * RETURNS: None.
 */
VOID dert::sphere::EvalNormal( intr *Intr )
{
   Intr->N = (Intr->P - C).Normalize();
} /* End of 'dert::sphere::EvalNormal' function */

/* End of 'SPHERE.CPP' file */