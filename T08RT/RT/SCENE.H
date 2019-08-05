/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : SCENE.H
* PURPOSE     : Ray tracing.
*               Scene class.
* PROGRAMMER  : AD6.
* LAST UPDATE : 17.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __SCENE_H_
#define __SCENE_H_

#include "IMAGE.H"
#include "SHAPES/SHAPE.H"
#include "../RES/LIGHTS/LIGHTS.H"
#include "SHAPES/SPHERE.H"
#include "SHAPES/PLANE.H"
#include "SHAPES/BOX.H"
#include "SHAPES/TRIAN.H"
#include "SHAPES/PRIM.H"
#include "SHAPES/QUAD.H"
#include "SHAPES/TORUS.H"
#include <thread>



namespace dert
{

  const environment AirEnvi(0, 1);
  const material DefMtl(vec(0.2), vec(0.8), vec(0.3),
                             vec(0), vec(0), 24);
  class scene
  {
  private:
    shape_list SList;
    INT CurrentLevel, MaxLevel;
    vec AmbientColor;
    std::vector<base_light *> Lights;
  public:

    scene( VOID );

    ~scene( VOID );

   /* Render scene function.
    * ARGUMENTS:
    *   - reference to projection camera:
    *        camera &Cam;    
    *   - pointer to image to draw:
    *        image *Img;
    * RETURNS: None.
    */
    VOID Render( camera &Cam, image *Img);

   /* Trace rays function.
    * ARGUMENTS:
    *   - reference to ray:
    *        ray &R;
    * RETURNS:
    *      (vec) color;
    */
    vec Trace( const ray &R, const environment &Envi, const vec &Weight );

   /* Shade function.
    * ARGUMENTS:
    *   - reference to direction vector (viewer):
    *        vec &V;    
    *   - pointer to intersection type:
    *        intr *Intr;
    *   - reference to environment coefficients:
    *        environment &Envi;    
    *   - reference to weight of a ray:
    *       vec &Weight;
    * RETURNS:
    *      (vec) color;
    */
    vec Shade( const vec &V, const intr &Intr, 
               const environment &Envi, const vec &Weight );
  };
} // End of 'dert' namespace




#endif /* __SCENE_H_ */

/* End of 'scene.h' file */

