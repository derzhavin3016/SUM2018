/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : MATERIALS.H
* PURPOSE     : Ray tracing.
*               Materials stock.
*               Environment class.
* PROGRAMMER  : AD6.
* LAST UPDATE : 27.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __MATERIALS_H_
#define __MATERIALS_H_

#include <vector>
#include "../DEF.H"

namespace dert
{
  /* Materials class */
  class material
  {
  public:
    // Illumination coefficients
    vec 
      Ka,              // Ambient coefficient
      Kd,              // Diffuse coefficient
      Ks,              // Specular coefficient
      Krefl,           // Reflect coefficient
      Ktrans;          // Transparency coefficient
    FLT Ph;            // Phong power coefficient

    /* Constructor function.
     * ARGUMENTS:
     *   - reference to ambient, diffuse, specular,
     *       reflect and transparency coefficients:
     *        vec &A, &D, &S, &R, &Tr;    
     *   - phong coefficient:
     *        DBL P;
     * RETURNS: None.
     */
    material( const vec &A, const vec &D, const vec &S, 
              const vec &R, const vec &Tr, const FLT P );

    // Default constructor
    material( VOID );

    // Copy constructor
    material( material *Mtl );

    /* Copy constructor function (reload = operator).
     * ARGUMENTS:
     *   - reference to material (RValue):
     *        material &Mtl;
     * RETURNS:
     *   (material &) self-pointer (to multi-equal).
     */
    material & operator=( const material &Mtl );
  };

  /* Environment class */
  class environment
  {
  public:
    DBL Decay, NRefr;
    
    environment( DBL Dec, DBL NR );

    // Default constructor
    environment( VOID );

    // Copy constructor
    environment( const environment &Envi );

    /* Copy constructor function (reload = operator).
     * ARGUMENTS:
     *   - reference to material (RValue):
     *        material &Mtl;
     * RETURNS:
     *   (material &) self-pointer (to multi-equal).
     */
    environment & operator=( const environment &Envi );
  };
} /* End of 'dert' namespace */

#endif /* __MATERIALS_H_ */

