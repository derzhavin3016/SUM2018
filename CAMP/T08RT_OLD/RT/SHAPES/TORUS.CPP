/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : TORUS.CPP
* PURPOSE     : Ray tracing.
*               Shapes.
*               Torus.
*               Functions realization.
* PROGRAMMER  : AD6.
* LAST UPDATE : 28.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "TORUS.H"

/* Find intersection with torus function
 * ARGUMENTS: 
 *   - reference to ray to find intersection with:
 *        ray &R;
 *   - pointer to intersection type:
 *        intr *Intr;
 * RETURNS:
 *       (BOOL) TRUE if intersection is found, FALSE otherwise.
 */
BOOL dert::torus::Intersect( const ray &R, intr *Intr )
{
  DBL Roots[4], OD, O2;
  vec 
    O(R.Org),
    D(R.Dir);
  vec2
    O_2(R.Org[0], R.Org[2]),
    D_2(R.Dir[0], R.Dir[2]);
  OD = O & D;
  O2 = O.Length2();

  INT n = mth::Solve4(Roots, 1.0, 4 * OD, 2 * (2 * OD * OD + C + O2 - 2 * Rad2 * D_2.Length2()),
                       4 * (OD * O2 + C * OD - 2 * Rad2 * (O_2 & D_2)), O2 * O2 + C * C + 2 * C * O2 - 4 * Rad2 * O_2.Length2());

  if (!n || Roots[n - 1] < 0)
  {
    return FALSE;
  }
  INT i;

  for (i = 0; i < n && Roots[i] < 0.00001; i++);

  Intr->SetIntr(this, Roots[i], TRUE);
  return TRUE;
} /* End of 'Intersect' function */

/* Find all intersections function
 * ARGUMENTS: 
 *   - reference to ray to find intersections with:
 *        ray &R;
 *   - pointer to intersections type:
 *        intr_list *IList;
 * RETURNS:
 *       (INT) Amount of intersections.
 */
INT dert::torus::AllIntersect( const ray &R, intr_list *IList )
{
  DBL Roots[4], OD, O2;
  vec 
    O(R.Org),
    D(R.Dir);
  vec2
    O_2(R.Org[0], R.Org[2]),
    D_2(R.Dir[0], R.Dir[2]);
  OD = O & D;
  O2 = O.Length2();

  INT n = mth::Solve4(Roots, 1.0, 4 * OD, 2 * (2 * OD * OD + C + O2 - 2 * Rad2 * D_2.Length2()),
                       4 * (OD * O2 + C * OD - 2 * Rad2 * (O_2 & D_2)), O2 * O2 + C * C + 2 * C * O2 - 4 * Rad2 * O_2.Length2());

  if (!n || Roots[n - 1] < 0)
  {
    return 0;
  }
  INT j = 0;
  INT i;

  for (i = 0; i < n && Roots[i] < 0; i++)

  for (INT u = i; u < n; u++)
  {
    IList->push_back(intr(this, Roots[i], (n - u) % 2 == 0));
    j++;
  }
  return j;
} /* End of 'AllIntersect' function */

/* Torus normal evaluation function
 * ARGUMENTS:
 *   - pointer to intersection type:
 *        intr &Intr;
 * RETURNS: None.
 */
VOID dert::torus::EvalNormal( intr *Intr )
{
   DBL 
    x(Intr->P[0]),
    y(Intr->P[1]),
    z(Intr->P[2]), Dx, Dy, Dz, x2 = x * x, y2 = y * y, z2 = z * z;

   Dx = 4 * x * x * x + 4 * x * y2 + 4 * x * z2 + 4 * x * C - 8 * Rad2 * x;
   Dy = 4 * y * y * y + 4 * x2 * y + 4 * y * z2 + 4 * y * C;
   Dz = 4 * z * z * z + 4 * x2 * z + 4 * z * y2 + 4 * z * C - 8 * Rad2 * z;
   Intr->N = vec(Dx, Dy, Dz).Normalize();
} /* End of 'EvalNormal' function */

/* End of 'TORUS.CPP' file */