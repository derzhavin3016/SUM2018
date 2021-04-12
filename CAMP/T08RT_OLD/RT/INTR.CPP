/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : INTR.CPP
* PURPOSE     : Ray tracing.
*               Intersect info class.
*               Functions realization.
* PROGRAMMER  : AD6.
* LAST UPDATE : 17.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "INTR.H"

// Default constructor
dert::intr::intr( VOID )
{
}

dert::intr & dert::intr::operator=( const intr &Intr )
{
  Shp = Intr.Shp;
  T = Intr.T;
  IsEnter = Intr.IsEnter;
  N = Intr.N;
  IsN = Intr.IsN;
  P = Intr.P;
  IsP = Intr.IsP;

  for (INT i = 0; i < 5; i++)
  {
    V[i] = Intr.V[i];
    D[i] = Intr.D[i];
    I[i] = Intr.I[i];
  }

  return *this;
}

// Copy constructor by reference
dert::intr::intr( const intr &Intr )
{
  Shp = Intr.Shp;
  T = Intr.T;
  IsEnter = Intr.IsEnter;
  N = Intr.N;
  IsN = Intr.IsN;
  P = Intr.P;
  IsP = Intr.IsP;
  for (INT i = 0; i < 5; i++)
  {
    V[i] = Intr.V[i];
    D[i] = Intr.D[i];
    I[i] = Intr.I[i];
  }
}

VOID dert::intr::SetIntr( const intr &Intr )
{
  Shp = Intr.Shp;
  T = Intr.T;
  IsEnter = Intr.IsEnter;
  N = Intr.N;
  IsN = Intr.IsN;
  P = Intr.P;
  IsP = Intr.IsP;
  for (INT i = 0; i < 5; i++)
  {
    V[i] = Intr.V[i];
    D[i] = Intr.D[i];
    I[i] = Intr.I[i];
  }

}

// Copy constructor by pointer
dert::intr::intr( intr *Intr )
{
  Shp = Intr->Shp;
  T = Intr->T;
  IsEnter = Intr->IsEnter;
  N = Intr->N;
  IsN = Intr->IsN;
  P = Intr->P;
  IsP = Intr->IsP;
  for (INT i = 0; i < 5; i++)
  {
    V[i] = Intr->V[i];
    D[i] = Intr->D[i];
    I[i] = Intr->I[i];
  }
}

/* Constructor function.
 * ARGUMENTS: 
 *   - object pointer:
 *         shape *Shp;
 *   - Ray parameter:
 *          DBL T;
 *   - Is enter flag:
 *          BOOL IsEnter(TRUE default);
 * RETURNS: None.
 */
dert::intr::intr( shape *Shp, DBL T, BOOL IsEnter ) : Shp(Shp), T(T), IsEnter(IsEnter)
{
} /* End of 'intr' function */

/* Constructor function.
 * ARGUMENTS: 
 *   - object pointer:
 *         shape *Shp;
 *   - Ray parameter:
 *          DBL T;
 *   - Is enter flag:
 *          BOOL IsEnter;
 *   - reference to normal:
 *          vec &Norm;
 * RETURNS: None.
  */
dert::intr::intr( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm ) : Shp(Shp), T(T), IsEnter(IsEnter), N(Norm)
{
} /* End of 'intr' function */

/* Constructor function.
 * ARGUMENTS: 
 *   - object pointer:
 *         shape *Shp;
 *   - Ray parameter:
 *          DBL T;
 *   - Is enter flag:
 *          BOOL IsEnter;
 *   - reference to normal:
 *          vec &Norm;
 *   - reference to position:
 *          vec &Pos;
 * RETURNS: None.
 */
dert::intr::intr( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm, const vec &Pos ) : Shp(Shp), T(T), IsEnter(IsEnter), N(Norm), P(Pos)
{
} /* End of 'intr' function */

/* Intersect set function.
 * ARGUMENTS: 
 *   - object pointer:
 *         shape *Shp;
 *   - Ray parameter:
 *          DBL T;
 *   - Is enter flag:
 *          BOOL IsEnter(TRUE default);
 * RETURNS: None.
 */
VOID dert::intr::SetIntr( shape *Shp, DBL T, BOOL IsEnter )
{
  this->Shp = Shp;
  this->T = T;
  this->IsEnter = IsEnter;
  this->IsN = FALSE;
  this->IsP = FALSE;
} /* End of 'intr' function */

/* Intersect set function.
 * ARGUMENTS: 
 *   - object pointer:
 *         shape *Shp;
 *   - Ray parameter:
 *          DBL T;
 *   - Is enter flag:
 *          BOOL IsEnter;
 *   - reference to normal:
 *          vec &Norm;
 * RETURNS: None.
 */
VOID dert::intr::SetIntr( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm )
{
  this->Shp = Shp;
  this->T = T;
  this->IsEnter = IsEnter;
  this->N = Norm;
  this->IsN = TRUE;
  this->IsP = FALSE;
} /* End of 'intr' function */

/* Intersect set function.
 * ARGUMENTS: 
 *   - object pointer:
 *         shape *Shp;
 *   - Ray parameter:
 *          DBL T;
 *   - Is enter flag:
 *          BOOL IsEnter;
 *   - reference to normal:
 *          vec &Norm;
 *   - reference to position:
 *          vec &Pos;
 * RETURNS: None.
 */
VOID dert::intr::SetIntr( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm, const vec &Pos )
{
  this->Shp = Shp;
  this->T = T;
  this->IsEnter = IsEnter;
  this->N = Norm;
  this->IsN = TRUE;
  this->P = Pos;
  this->IsP = TRUE;
} /* End of 'intr' function */

/* End of 'intr.cpp' file */