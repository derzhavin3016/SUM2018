/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : TRIAN.CPP
* PURPOSE     : Ray tracing.
*               Shapes.
*               Triangle.
*               Functions realization.
* PROGRAMMER  : AD6.
* LAST UPDATE : 20.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "TRIAN.H"

/* Triangle constructor function
 * ARGUMENTS: 
 *   - reference to 3 points:
 *        vec &P0, &P1, &P2;
 *   - reference to material type:
 *        material &Mtl;
 *   - reference to environment type:
 *        environment &Env;
 * RETURNS: None.
 */
dert::triangle::triangle( const vec &P0, const vec &P1, const vec &P2,
          const material &Mtl, const environment &Env ) : 
  A(P0), B(P1), C(P2), shape(Mtl, Env), P(A, B, C)
{
  vec 
    s1(B - A),
    s2(C - A);

   U1 = (s1 * (s2.Length2()) - s2 * (s1 & s2)) / 
         (s1.Length2() * s2.Length2() - mth::sqr(s1 & s2));
   u0 = A & U1;

   V1 = (s2 * (s1.Length2()) - s1 * (s1 & s2)) / 
         (s1.Length2() * s2.Length2() - mth::sqr(s1 & s2));
   v0 = A & V1;
} /* End of 'triangle' function */

/* Find intersection with triangle function
 * ARGUMENTS: 
 *   - reference to ray to find intersection with:
 *        ray &R;
 *   - reference to intersection type:
 *        intr *Intr;
 * RETURNS:
 *       (BOOL) TRUE if intersection is found, FALSE otherwise.
 */
BOOL dert::triangle::Intersect( const ray &R, intr *Intr )
{
  intr In;

  if (P.Intersect(R, &In))
  {
    vec P(R(In.T));
    DBL 
      u = (P & U1) - u0,
      v = (P & V1) - v0;

    if (u >= 0 && u <= 1 && v >= 0 && v <= 1 && u + v <= 1)
    {
      Intr->SetIntr(this, In.T, TRUE);
      return TRUE;
    }
  }
  return FALSE;
} /* End of 'Intersect' function */

/* Find all intersections with triangle function
 * ARGUMENTS: 
 *   - reference to ray to find intersections with:
 *        ray &R;
 *   - pointer to intersections type:
 *        intr_list *Intr;
 * RETURNS:
 *       (INT) Amount of intersections.
 */
INT dert::triangle::AllIntersect( const ray &R, intr_list *IList )
{
  intr Intr;
  if (Intersect(R, &Intr))
  {
    IList->push_back(Intr);
    return 1;
  }

  return 0;
} /* End of 'AllIntersect' function */

/* Normal evaluation function
 * ARGUMENTS:
 *   - pointer to intersection type:
 *        intr *Intr;
 * RETURNS: None.
 */
VOID dert::triangle::EvalNormal( intr *Intr )
{
  Intr->N = ((B - A) % (C - A)).Normalize();
} /* End of 'EvalNormal' function */

/* End of 'TRIAN.CPP' file */