/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : LIGHTS.CPP
* PURPOSE     : Ray tracing.
*               Lights class.
*               Functions realizations.
* PROGRAMMER  : AD6.
* LAST UPDATE : 26.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "LIGHTS.H"

dert::shade_data::shade_data( const intr &Intr ) : intr(Intr)
{
}

// Default constructor
dert::base_light::base_light( VOID )
{
}

dert::base_light::base_light( DBL C, DBL L, DBL Q, const vec &Col ) : CC(C), CL(L), CQ(Q), Color(Col)
{
}

BOOL dert::base_light::GetData( const shade_data &Shd, light_attenuation *Att )
{
  return TRUE;
}

dert::dir_light::dir_light( VOID )
{
}

dert::dir_light::dir_light( const vec &Dir,  const vec &Col ) : 
  base_light(0.0, 0.0, 0.0, Col), Direct(Dir.Normalize())
{

}

BOOL dert::dir_light::GetData( const shade_data &Shd, light_attenuation *Att )
{
  Att->L = Direct; 
  Att->CC = CC;
  Att->CL = CL;
  Att->CQ = CQ;
  Att->Color = Color;
  Att->Dist = mth::Infinity;

  // Light attenuation
  Att->Fatt = mth::Min(1 / 
    (Att->CC + Att->CL * Att->Dist + Att->CQ * mth::sqr(Att->Dist)), 1.0);

  return TRUE;
}

dert::pos_light::pos_light( VOID )
{
}

dert::pos_light::pos_light( const vec &P, DBL C, DBL L, DBL Q, const vec &Col ) : Pos(P), base_light(C, L, Q, Col)
{
}

BOOL dert::pos_light::GetData( const shade_data &Shd, light_attenuation *Att )
{
  Att->L = (Pos - Shd.P).Normalize();
  Att->CC = CC;
  Att->CL = CL;
  Att->CQ = CQ;
  Att->Color = Color;
  Att->Dist = !(Pos - Shd.P); 

  // Light attenuation
  Att->Fatt = mth::Min(1 / 
    (Att->CC + Att->CL * Att->Dist + Att->CQ * mth::sqr(Att->Dist)), 1.0);
  return TRUE;
}

// Default constructor
dert::spot_light::spot_light( VOID )
{
}


/* Spotlight constructor function.
 * ARGUMENTS:
 *   - reference to position vector:
 *        vec &P;
 *   - reference to direction vector:
 *        vec &D;
 *   - inner cone angle:
 *        DBL AngleInDegreeIn;
 *   - outer cone angle:
 *        DBL AngleInDegreeOu;
 *   - reference to color vector:
 *        vec &Col; 
 * RETURNS: None.
 */
dert::spot_light::spot_light( const vec &P, const vec &D, DBL AngleInDegreeIn, 
                              DBL AngleInDegreeOu, const vec &Col ) : 
  base_light(0.0, 0.0, 0.0, Col), Pos(P), Dir(D.Normalize())
{
  Inn = mth::D2R(AngleInDegreeIn);
  con = cos(Inn);
  Out = mth::D2R(AngleInDegreeOu);
  cou = cos(Out);
}

BOOL dert::spot_light::GetData( const shade_data &Shd, light_attenuation *Att )
{
  Att->L = (Pos - Shd.P).Normalize();
  Att->Color = Color;
  Att->Dist = !(Pos - Shd.P);
  DBL Gamma = (-Att->L & Dir);
  if (Gamma > con)
    Att->Fatt = 1.0;
  else if(Gamma > cou)
    Att->Fatt = (Gamma - cou) / (con - cou);
  else
    Att->Fatt = 0;

  return TRUE;
}

// Default constructor
dert::refl_light::refl_light( VOID )
{

}

/* Reflector constructor function.
 * ARGUMENTS:
 *   - reference to position vector:
 *        vec &P;
 *   - reference to direction vector:
 *        vec &D;
 *   - reference to color vector:
 *        vec &Col; 
 * RETURNS: None.
 */
dert::refl_light::refl_light( const vec &P, const vec &D, const vec &Col ) :
  base_light(0.0, 0.0, 0.0, Col), Pos(P), Dir(D.Normalize())
{
}

BOOL dert::refl_light::GetData( const shade_data &Shd, light_attenuation *Att )
{
  Att->L = (Pos - Shd.P).Normalize();
  Att->Color = Color;
  Att->Dist = !(Pos - Shd.P);
  
  Att->Fatt = mth::Max(-Att->L & Dir, 0.0);

  return TRUE;
}


/* End of 'lights.cpp' file */

