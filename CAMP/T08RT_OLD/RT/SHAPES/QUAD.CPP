/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : QUAD.CPP
* PURPOSE     : Ray tracing.
*               Shapes.
*               Quadrics.
*               Functions realization.
* PROGRAMMER  : AD6.
* LAST UPDATE : 27.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "QUAD.H"

/* Find intersection with quadrics function
 * ARGUMENTS: 
 *   - reference to ray to find intersection with:
 *        ray &R;
 *   - pointer to intersection type:
 *        intr *Intr;
 * RETURNS:
 *       (BOOL) TRUE if intersection is found, FALSE otherwise.
 */
BOOL dert::quad::Intersect( const ray &R, intr *Intr )
{
  DBL a, b, c, t0, t1, p, q;

  a = 
    A * mth::sqr(R.Dir[0]) + 2 * B * R.Dir[0] * R.Dir[1] + 
    2 * C * R.Dir[0] * R.Dir[2] + E * mth::sqr(R.Dir[1]) + 
    2 * F * R.Dir[1] * R.Dir[2] + H * mth::sqr(R.Dir[2]);
  b = 
    2 * (A * R.Org[0] * R.Dir[0] + B * (R.Org[0] * R.Dir[1] + R.Org[1] * R.Dir[0]) + 
         C * (R.Org[0] * R.Dir[2] + R.Org[2] * R.Dir[0]) + D * R.Dir[0] + E * R.Org[1] * R.Dir[1] + 
         F * (R.Org[1] * R.Dir[2] + R.Org[2] * R.Dir[1]) + G * R.Dir[1] + H * R.Org[2] * R.Dir[2] + I * R.Dir[2]);
  c = 
    A * mth::sqr(R.Org[0]) + 2 * B * R.Org[0] * R.Org[1] + 2 * C * R.Org[0] * R.Org[2] + 
    2 * D * R.Org[0] + E * mth::sqr(R.Org[1]) + 2 * F * R.Org[2] * R.Org[1] + 2 * G * R.Org[1] +
    H * mth::sqr(R.Org[2]) + 2 * I * R.Org[2] + J;
  p = -b / (2 * a);
  q = sqrt(mth::sqr(b) - 4 * a * c) / (2 * a);
  t0 = p + q;
  t1 = p - q;

  if (t0 > t1)
    mth::Swap(t0, t1);

  if (t1 <= 0)
    return FALSE;

  Intr->SetIntr(this, t0 > 0 ? t0 : t1, TRUE);
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
INT dert::quad::AllIntersect( const ray &R, intr_list *IList )
{
  DBL 
    a, b, c, t0, t1, p, q,
    Ox(R.Org[0]), Oy(R.Org[1]), Oz(R.Org[2]),
    Dx(R.Dir[0]), Dy(R.Dir[1]), Dz(R.Dir[2]);

  a = 
    A * mth::sqr(Dx) + 2 * B * Dx * Dy + 
    2 * C * Dx * Dz + E * mth::sqr(Dy) + 
    2 * F * Dy * Dz + H * mth::sqr(Dz);
  b = 
    2 * (A * Ox * Dx + B * (Ox * Dy + Oy * Dx) + 
         C * (Ox * Dz + Oz * Dx) + D * Dx + E * Oy * Dy + 
         F * (Oy * Dz + Oz * Dy) + G * Dy + H * Oz * Dz + I * Dz);
  c = 
    A * mth::sqr(Ox) + 2 * B * Ox * Oy + 2 * C * Ox * Oz + 
    2 * D * Ox + E * mth::sqr(Oy) + 2 * F * Oz * Oy + 2 * G * Oy +
    H * mth::sqr(Oz) + 2 * I * Oz + J;
  p = -b / (2 * a);
  q = sqrt(mth::sqr(b) - 4 * a * c) / (2 * a);
  t0 = p + q;
  t1 = p - q;

  if (t0 > t1)
    mth::Swap(t0, t1);

  if (t1 < 0)
    return 0;

  if (t0 > 0)
  {
    IList->push_back(intr(this, t0, TRUE));
    IList->push_back(intr(this, t1, FALSE));
    return 2;
  }

  IList->push_back(intr(this, t1, FALSE));
  return 1;
} /* End of 'AllIntersect' function */

/* uadrics normal evaluation function
 * ARGUMENTS:
 *   - pointer to intersection type:
 *        intr *Intr;
 * RETURNS: None.
 */
VOID dert::quad::EvalNormal( intr *Intr )
{
  DBL 
    x0(Intr->P[0]),
    y0(Intr->P[1]),
    z0(Intr->P[2]), Dx, Dy, Dz;

  Dx = 2 * A * x0 + 2 * B * y0 + 2 * C * z0 + 2 * D;
  Dy = 2 * E * y0 + 2 * B * x0 + 2 * F * z0 + 2 * G;
  Dz = 2 * H * z0 + 2 * I + 2 * F * y0 + 2 * C * x0;
  Intr->N = vec(Dx, Dy, Dz).Normalize();
} /* End of 'EvalNormal' function */

/* End of 'QUAD.CPP' file */