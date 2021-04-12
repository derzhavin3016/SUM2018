/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : MATERIALS.CPP
* PURPOSE     : Ray tracing.
*               Materials stock.
*               Environment class.
*               Functions realization.
* PROGRAMMER  : AD6.
* LAST UPDATE : 17.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "MATERIALS.H"

/* Constructor function.
 * ARGUMENTS:
 *   - reference to ambient, diffuse, specular,
 *       reflect and transparency coefficients:
 *        vec &A, &D, &S, &R, &Tr;    
 *   - phong coefficient:
 *        DBL P;
 * RETURNS: None.
 */
dert::material::material( const vec &A, const vec &D, const vec &S,
                        const vec &R, const vec &Tr, const FLT P ) : 
  Ka(A), Kd(D), Ks(S), Ph(P), Krefl(R), Ktrans(Tr)
{
}

// Default constructor
dert::material::material( VOID ) : 
  Ka(0.2), Kd(0.8), Ks(0.3), Ph(24), Krefl(0), Ktrans(0)
{
}

// Copy constructor by pointer
dert::material::material( material *Mtl )
{
  Ka = Mtl->Ka;
  Kd = Mtl->Kd;
  Ks = Mtl->Ks;
  Krefl = Mtl->Krefl;
  Ktrans = Mtl->Ktrans;
  Ph = Mtl->Ph;
}

/* Copy constructor function (reload = operator).
 * ARGUMENTS:
 *   - reference to material (RValue):
 *        material &Mtl;
 * RETURNS:
 *   (material &) self-pointer (to multi-equal).
 */
dert::material & dert::material::operator=( const material &Mtl )
{
  Ka = Mtl.Ka;
  Kd = Mtl.Kd;
  Ks = Mtl.Ks;
  Krefl = Mtl.Krefl;
  Ktrans = Mtl.Ktrans;
  Ph = Mtl.Ph;
  return *this;
} /* End of '' function */

dert::environment::environment( DBL Dec, DBL NR ) : Decay(Dec), NRefr(NR)
{
}

// Default constructor
dert::environment::environment( VOID ) : Decay(0), NRefr(1)
{
}

// Copy constructor
dert::environment::environment( const environment &Envi )
{
  Decay = Envi.Decay;
  NRefr = Envi.NRefr;
}

/* Copy constructor function (reload = operator).
 * ARGUMENTS:
 *   - reference to reference (RValue):
 *        environment &Envi;
 * RETURNS:
 *   (environment &) self-pointer (to multi-equal).
 */
dert::environment & dert::environment::operator=( const environment &Envi )
{
  Decay = Envi.Decay;
  NRefr = Envi.NRefr;
  return *this;
} /* End of 'operator=' function */

/* End of 'MATERIALS.CPP' file */