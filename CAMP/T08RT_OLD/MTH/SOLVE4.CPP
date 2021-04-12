/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : SOLVE4.CPP
* PURPOSE     : Ray tracing.
*               Math support.
*               Solve fourth-degree equation header.
*               Functions realization;
* PROGRAMMER  : AD6.
* LAST UPDATE : 31.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "SOLVE4.H"

/* Solve equation of the fourth degree function.
 * ARGUMENTS:
 *    - pointer to roots array:
 *        DBL *Roots;
 *    - Equation coefficients:
 *        DBL A, B, C, D, E;
 * RETURNS:
 *   (INT) amount of real roots.
 */
INT mth::Solve4( DBL *Roots, DBL A, DBL B, DBL C, DBL D, DBL E )
{
  if (A == 0)
    return Solve3(Roots, B, C, D, E);
  if (fabs(E) < 0.00001)
  {
      *Roots = 0;
      return 1 + Solve3(Roots + 1, A, B, C, D);
  }
  DBL a, b, c, d, p, q, r;

  if (A != 1)
  {
    a = B / A;
    b = C / A;
    c = D / A;
    d = E / A;
  }
  else
  {
    a = B;
    b = C;
    c = D;
    d = E;
  }

  p = b - (3 * a * a) / 8.0;
  q = (a * a * a) / 8 - (a * b) / 2 + c;
  r = ((-3 * a * a * a * a) / 256) + ((a * a * b) / 16) + ((-c * a) / 4) + d;

  DBL s[3];

  INT n = Solve3(s, 2, -p, -2 * r, r * p - (q * q) / 4);
  
  if (n == 0)
    return 0;

  DBL sp2 = 2 * s[0] - p, sqr2sp, y[4];
  if (sp2 < 0.00001)
    return 0;
  sqr2sp = sqrt(2 * s[0] - p);
  n = Solve2(y, 1, -sqr2sp, (q / (2 * sqr2sp))+ s[0]);
  if (n == 1)
    n += Solve2(y + 1, 1.0, sqr2sp, -(q / (2 * sqr2sp)) + s[0]);
  else if(n == 0)
    n += Solve2(y, 1.0, sqr2sp, -(q / (2 * sqr2sp)) + s[0]);
  else
    n += Solve2(y + 2, 1.0, sqr2sp, -(q / (2 * sqr2sp)) + s[0]);

  for (INT i = 0; i < n; i++)
    Roots[i] = y[i] - a / 4;

  // Sort roots array
  for (INT j = 0; j < n; j++)
    for (INT i = j + 1; i < n; i++)
    {
      if (Roots[j] > Roots[i])
        mth::Swap(Roots[j], Roots[i]);
    }
  
  return n;
} /* End of 'Solve4' function */

/* Solve equation of the third degree function (static).
 * ARGUMENTS:
 *    - pointer to roots array:
 *        DBL *Roots;
 *    - Equation coefficients:
 *        DBL A, B, C, D;
 * RETURNS:
 *   (INT) amount of real roots.
 */
INT mth::Solve3( DBL *Roots, DBL A, DBL B, DBL C, DBL D )
{

  if (A == 0)
    return Solve2(Roots, B, C, D);
  if (D == 0)
  {
    *Roots = 0;
    return 1 + Solve2(Roots + 1, A, B, C);
  }

  DBL a, b, c, Q, R;

  a = B / A;
  b = C / A;
  c = D / A;


  Q = (a * a - 3.0 * b) / 9.0;
  R = (a * (2.0 * a * a - 9.0 * b) + 27.0 * c) / 54.0;
  DBL
    R2 = R * R,
    Q3 = Q * Q * Q;

  if (R2 < Q3)
  {
    DBL t = acos(R / sqrt(Q3)) / 3;
    a /= 3.0;
    Q = -2 * sqrt(Q);
    *Roots = Q * cos(t) - a;
    *(Roots + 1) = Q * cos(t + (2 * mth::PI / 3)) - a;
    *(Roots + 2) = Q * cos(t - (2 * mth::PI / 3)) - a;

    // Sort roots array
    for (INT j = 0; j < 3; j++)
      for (INT i = j + 1; i < 3; i++)
      {
        if (Roots[j] > Roots[i])
          mth::Swap(Roots[j], Roots[i]);
      }
    return 3;
  }

  DBL aa, bb;

  aa = -mth::Sign(R) * pow(fabs(R) + sqrt(R2 - Q3), 1.0 / 3.0);
  if (aa != 0)
    bb = Q / aa;
  else 
    bb = 0.0;
  
  a /= 3.0;

  Q = aa + bb;
  R = aa - bb;

  *Roots = Q - a;
  *(Roots + 1) = -0.5 * Q - a;
  *(Roots + 2) = sqrt(3.0) * 0.5 * R;

  if (*(Roots + 2) == 0)
    return 2;
  return 1;
} /* End of 'Solve3' function */

/* Solve equation of the second degree function (static).
 * ARGUMENTS:
 *    - pointer to roots array:
 *        DBL *Roots;
 *    - Equation coefficients:
 *        DBL A, B, C;
 * RETURNS:
 *   (INT) amount of real roots.
 */
INT mth::Solve2( DBL *Roots, DBL A, DBL B, DBL C )
{
  if (A == 0)
  {
    if (B == 0)
    {
      if (C == 0)
        return 9999;
      return 0;
    }
    *Roots = -C / B;
    return 1;
  }

  DBL D, p, q;

  D = B * B - 4 * A * C;

  if (D < 0)
    return 0;

  p = -B / (2 * A);

  if (D == 0)
  {
    *Roots = p;
    return 1;
  }
  
  q = sqrt(D) / (2 * A);
  DBL
    x1 = p + q,
    x2 = p - q;
  if (x1 > x2)
    mth::Swap(x1, x2);

  *Roots = x1;
  *(Roots + 1) = x2;
  return 2;
} /* End of 'Solve2' function */

/* End of 'SOLVE4.CPP' file */