/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : BOX.CPP
* PURPOSE     : Ray tracing.
*               Shapes.
*               Box (rectangular parallelepiped).
*               Functions realization.
* PROGRAMMER  : AD6.
* LAST UPDATE : 19.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "BOX.H"

/* Find intersection with box function
 * ARGUMENTS: 
 *   - reference to ray to find intersection with:
 *        ray &R;
 *   - pointer to intersection type:
 *        intr *Intr;
 * RETURNS:
 *       (BOOL) TRUE if intersection is found, FALSE otherwise.
 */
BOOL dert::box::Intersect( const ray &R, intr *Intr )
{
  DBL t_near = 0, t_far = mth::Infinity, t0, t1;
  INT ax(0), ax1(0);
  //BB1 = vec::Min

  // Calculating for all of three axes
  for (INT a = 0; a < 3; a++)
  {
    if (fabs(R.Dir[a]) < 0.0001)
    {
      if (R.Org[a] < mth::Min(B1[a], B2[a]) || R.Org[a] > mth::Max(B1[a], B2[a]))
        return FALSE;
      continue;
    }
    t0 = (B1[a] - R.Org[a]) / R.Dir[a];
    t1 = (B2[a] - R.Org[a]) / R.Dir[a];
    if (t0 > t1)
      mth::Swap(t0, t1);
    if (t0 > t_near)
    {
      t_near = t0;
      ax = a;
    }
    if (t1 < t_far)
    {
      t_far = t1;
      ax1 = a;
    }
    if (t_near > t_far)
      return FALSE;
    if (t_far < 0.001)
      continue;
  }

  Intr->SetIntr(intr(this, t_near < 0.001 ? t_far : t_near, TRUE));
  Intr->I[0] = t_near < 0.001 ? ax1 : ax;
  return TRUE;
} /* End of 'Intersect' function */

/* Find all intersections function (virtual)
 * ARGUMENTS: 
 *   - reference to ray to find intersections with:
 *        ray &R;
 *   - pointer to intersections type:
 *        intr_list *IList;

 * RETURNS:
 *       (INT) Amount of intersections.
 */
INT dert::box::AllIntersect( const ray &R, intr_list *IList )
{
  DBL t_near = 0, t_far = mth::Infinity, t0, t1;
  vec BB1, BB2;
  //BB1 = vec::Min

  // Calculating for all of three axes
  for (INT a = 0; a < 3; a++)
  {
    if (R.Dir[a] == 0)
    {
      if (R.Org[a] < B1[a] || R.Org[a] > B2[a])
        return 0;
      continue;
    }
    t0 = (B1[a] - R.Org[a]) / R.Dir[a];
    t1 = (B2[a] - R.Org[a]) / R.Dir[a];
    if (t0 > t1)
      mth::Swap(t0, t1);
    if (t0 > t_near)
      t_near = t0;
    if (t1 < t_far)
      t_far = t1;
    if (t_near > t_far)
      return 0;
    if (t_far < 0.0001)
      continue;
  }
  if (t_near == 0 || t_far == mth::Infinity || t_far < 0)
    return 0;
  if (t_near < 0.001)
  {
    IList->push_back(intr(this, t_far, FALSE));
    return 1;
  }

  IList->push_back(intr(this, t_near, TRUE));
  IList->push_back(intr(this, t_far, FALSE));
  return 2;
} /* End of 'AllIntersect' function */

/* Box normal evaluation function
 * ARGUMENTS:
 *   - pointer to intersection type:
 *        intr *Intr;
 * RETURNS: None.
 */
 VOID dert::box::EvalNormal( intr *Intr )
{
   switch (Intr->I[0])
   {
   case 0:
     Intr->N = vec(1, 0, 0);
     break;
   case 1:
     Intr->N = vec(0, 1, 0);
     break;
   case 2:
     Intr->N = vec(0, 0, 1);
     break;
   }
} /* End of 'EvalNormal' function */

 
/* Set verticies of box function
 * ARGUMENTS: 
 *   - reference to opposite verticies:
 *        vec &BF, vec &BS;
 * RETURNS: None.
 */
VOID dert::box::SetVertex( const vec &BF, const vec &BS )
{
  B1 = BF;
  B2 = BS;
}

/* Find intersection with box function
 * ARGUMENTS: 
 *   - reference to ray to find intersection with:
 *        ray &R;
 * RETURNS:
 *       (BOOL) TRUE if intersection is found, FALSE otherwise.
 */
BOOL dert::box::IsIntersect( const ray &R )
{
  DBL t_near = 0, t_far = mth::Infinity, t0, t1;

  // Calculating for all of three axes
  for (INT a = 0; a < 3; a++)
  {
    if (fabs(R.Dir[a]) < 0.0001)
    {
      if (R.Org[a] < B1[a] || R.Org[a] > B2[a])
        return FALSE;
      continue;
    }
    t0 = (B1[a] - R.Org[a]) / R.Dir[a];
    t1 = (B2[a] - R.Org[a]) / R.Dir[a];
    if (t0 > t1)
      mth::Swap(t0, t1);
    if (t0 > t_near)
      t_near = t0;
    if (t1 < t_far)
      t_far = t1;
    if (t_near > t_far)
      return FALSE;
    if (t_far < 0.0001)
      continue;
  }
  if (t_near == 0)
    return FALSE;
  return TRUE;
} /* End of 'IsIntersect' function */

/* End of 'BOX.CPP' file */