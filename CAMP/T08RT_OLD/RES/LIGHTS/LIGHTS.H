/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : LIGHTS.H
* PURPOSE     : Ray tracing.
*               Lights class.
* PROGRAMMER  : AD6.
* LAST UPDATE : 26.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __LIGHTS_H_
#define __LIGHTS_H_

#include "../../DEF.H"
#include "../../RT/INTR.H"
#include "../../RT/MATERIALS.H"

namespace dert
{
  class shade_data : public intr
  {
  public:
    material Mtl;
    environment Envi;

    shade_data( const intr &Intr );
  };

  class light_attenuation
  {
  public:
    vec L;          // Direction to light
    vec Color;
    DBL 
      CC,
      CL,
      CQ,
      Dist,
      Fatt;
  };

  /* Base light class */
  class base_light
  {
  public:
    DBL 
      CC,
      CL,
      CQ;
    vec Color;

    // Default constructor
    base_light( VOID );

    base_light( DBL C, DBL L, DBL Q, const vec &Col );

    virtual BOOL GetData( const shade_data &Shd, light_attenuation *Att );
  };

  // Light with a fixed direction class
  class dir_light : public base_light
  {
  public:
    vec Direct;    // Direction to light

    // Default constructor
    dir_light( VOID );

    dir_light( const vec &Dir, const vec &Col );

    BOOL GetData( const shade_data &Shd, light_attenuation *Att ) override;
  };

  // Light with a fixed position class
  class pos_light : public base_light
  {
  public:
    vec Pos;  // Light position

    // Default constructor
    pos_light( VOID );

    pos_light( const vec &P, DBL C, DBL L, DBL Q, const vec &Col );

    BOOL GetData( const shade_data &Shd, light_attenuation *Att ) override;
  };

  // Spotlight
  class spot_light : public base_light
  {
  public:
    vec
      Pos,         // Light position
      Dir;         // Spot direction
    DBL 
      Inn, con,    // Angle of solution and cosine of inner cone
      Out, cou;  // Angle of solution and cosine of outer cone

    // Default constructor
    spot_light( VOID );

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
    spot_light( const vec &P, const vec &D, DBL AngleInDegreeIn, 
                DBL AngleInDegreeOu, const vec &Col );

    BOOL GetData( const shade_data &Shd, light_attenuation *Att ) override;
  };

  // Reflector
  class refl_light : public base_light
  {
  public:
    vec
      Pos,         // Light position
      Dir;         // Reflect direction

    // Default constructor
    refl_light( VOID );

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
    refl_light( const vec &P, const vec &D, const vec &Col );

    BOOL GetData( const shade_data &Shd, light_attenuation *Att ) override;
  };
} /* End of 'dert' namespace */

#endif /* __LIGHTS_H_ */

/* End of 'lights.h' file */
