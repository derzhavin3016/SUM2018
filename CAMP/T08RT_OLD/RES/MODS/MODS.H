/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : MODS.H
* PURPOSE     : Ray tracing.
*               Modificators classes.
*               Base class and his inheritors.
* PROGRAMMER  : AD6.
* LAST UPDATE : 15.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __MODS_H_
#define __MODS_H_

#include "../../DEF.H"
#include "../../RT/IMAGE.H"
#include "../LIGHTS/LIGHTS.H"


namespace dert
{
  // Base modificators class
  class base_mods
  {
  public:
    // Default constructor
    base_mods( VOID )
    {
    }

    /* Modificator apply function (virtual).
     * ARGUMENTS:
     *   - reference to projection camera:
     *        camera &Cam;
     *   - reference to shade data type:
     *        shade_data *Shd;
     * RETURNS: None.
     */
    virtual VOID Apply( shade_data *Shd )
    {
    } /* End of 'Apply' function */

    /* Modificator ray transform function (virtual).
     * ARGUMENTS:
     *   - reference to ray to transform:
     *        ray &R;
     * RETURNS: 
     *       (DBL) length of direction transform vector;
     */
    virtual DBL RayTrans( ray &R )
    {
      return 1.0;
    } /* End of 'RayTrans' function */
  }; // End of 'base_mods' class

   // Sphere texture modificators class
  class plane_tex_mods : public base_mods
  {
  private:
    image *Img;  // Image
  public:
    // Default constructor
    plane_tex_mods( VOID )
    {
    }

    /* Plane texture modificator constructor function.
     * ARGUMENTS:
     *   - reference to filename to load image:
     *        std::string &FileName;
     * RETURNS: None.
     */
    plane_tex_mods( const std::string &FileName );

    /* Plane texture modificator apply function.
     * ARGUMENTS:
     *   - pointer to shade data type:
     *        shade_data *Shd;
     * RETURNS: None.
     */
    VOID Apply( shade_data *Shd ) override;

    // Class destructor
    ~plane_tex_mods( VOID );

  }; // End of 'base_mods' class

  // Sphere texture modificators class
  class sphere_tex_mods : public base_mods
  {
  private:
    image *Img;  // Image
    vec Center;
  public:
    // Default constructor
    sphere_tex_mods( VOID )
    {
    }

    /* Sphere texture modificator constructor function.
     * ARGUMENTS:
     *   - reference to filename to load image:
     *        std::string &FileName;
     * RETURNS: None.
     */
    sphere_tex_mods( const std::string &FileName );

    /* Sphere texture modificator apply function.
     * ARGUMENTS:
     *   - pointer to shade data type:
     *        shade_data *Shd;
     * RETURNS: None.
     */
    VOID Apply( shade_data *Shd ) override;

    // Class destructor
    ~sphere_tex_mods( VOID );

  }; // End of 'sphere_tex_mods' class

  // Cylinder texture modificators class
  class cylin_tex_mods : public base_mods
  {
  private:
    image *Img;  // Image
    vec Center;
  public:
    // Default constructor
    cylin_tex_mods( VOID )
    {
    }

    /* Cylinder texture modificator constructor function.
     * ARGUMENTS:
     *   - reference to filename to load image:
     *        std::string &FileName;
     * RETURNS: None.
     */
    cylin_tex_mods( const std::string &FileName );

    /* Cylinder texture modificator apply function.
     * ARGUMENTS:
     *   - pointer to shade data type:
     *        shade_data *Shd;
     * RETURNS: None.
     */
    VOID Apply( shade_data *Shd ) override;

    // Class destructor
    ~cylin_tex_mods( VOID );

  }; // End of 'sphere_tex_mods' class

  // Point modificators class
  class point_mods : public base_mods
  {
  private:
    matr Main;  // matrix
  public:
    // Default constructor
    point_mods( VOID )
    {
    }

    /* Point modificator constructor function (rotation).
     * ARGUMENTS:
     *   - rotate angle:
     *        DBL AngleInDegree;
     *   - reference to rotate axis:
     *        vec &Rot;
     * RETURNS: None.
     */
    point_mods( DBL AngleInDegree, const vec &Rot );

    /* Point modificator constructor function (translate).
     * ARGUMENTS:
     *   - reference to translate vector:
     *        vec &Tr;
     * RETURNS: None.
     */
    point_mods( const vec &Tr );

    /* Point modificator constructor function (scale).
     * ARGUMENTS:
     *   - reference to scale vector:
     *        vec &Sc;
     *   - dummy argument (for overload):
     *        INT Dummy;
     * RETURNS: None.
     */
    point_mods( const vec &Sc, INT Dummy );

    /* Point modificator apply function.
     * ARGUMENTS:
     *   - pointer to shade data type:
     *        shade_data *Shd;
     * RETURNS: None.
     */
    VOID Apply( shade_data *Shd ) override;

    /* Modificator ray transform function.
     * ARGUMENTS:
     *   - reference to ray to transform:
     *        ray &R;
     * RETURNS: 
     *       (DBL) length of direction transform vector;
     */
    DBL RayTrans( ray &R ) override;

    // Class destructor
    ~point_mods( VOID );

  }; // End of 'point_mods' class

} /* End of 'dert' namespace */

#endif /* __MODS_H_ */
/* End of 'MODS.H' file */
