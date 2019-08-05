/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : MODS.CPP
* PURPOSE     : Ray tracing.
*               Modificators classes.
*               Function realizations.
* PROGRAMMER  : AD6.
* LAST UPDATE : 16.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "MODS.H"

/* Plane texture modificator constructor function.
 * ARGUMENTS:
 *   - reference to filename to load image:
 *        std::string &FileName;
 * RETURNS: None.
 */
dert::plane_tex_mods::plane_tex_mods( const std::string &FileName )
{
  Img = new image;
  Img->Load("BIN/TEXTURES/" + FileName);
} /* End of 'plane_tex_mods' function */
 
/* Plane texture modificator apply function.
 * ARGUMENTS:
 *   - pointer to shade data type:
 *        shade_data *Shd;
 * RETURNS: None.
 */
VOID dert::plane_tex_mods::Apply( shade_data *Shd )
{
  Shd->Mtl.Kd = image::ToRgb(Img->GetPixel(Shd->P[0],
                                            Shd->P[2]));
  Shd->Mtl.Kd.Clamp(0.0, 1.0);
} /* End of 'Apply' function */

/* Plane texture modificator destructor function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
dert::plane_tex_mods::~plane_tex_mods( VOID )
{
  delete Img;
} /* End of '~plane_tex_mods' function */

/* Sphere texture modificator constructor function.
 * ARGUMENTS:
 *   - reference to filename to load image:
 *        std::string &FileName;
 * RETURNS: None.
 */
dert::sphere_tex_mods::sphere_tex_mods( const std::string &FileName )
{
  Img = new image;
  Img->Load("BIN/TEXTURES/" + FileName);
} /* End of 'sphere_tex_mods' function */

/* Sphere texture modificator apply function.
 * ARGUMENTS:
 *   - reference to projection camera:
 *        camera &Cam;
 *   - pointer to shade data type:
 *        shade_data *Shd;
 * RETURNS: None.
 */
VOID dert::sphere_tex_mods::Apply( shade_data *Shd )
{
  /* Get radius vector (translate sphere to zero) */
  vec Tr = Shd->P - Shd->V[4];

  /* Get spherical coordinates from cartesian */
  DBL 
    Theta = acos(Tr[1] / !Tr),
    Phi = 2 * atan2(Tr[2], Tr[0]) + mth::PI, Kh, Kw;

  /* Get coefficients */
  Kh = Img->GetHeight() / mth::PI;
  Kw = Img->GetWidth() / (2 * mth::PI);

  /* Get pixel from image */
  DWORD Pixel = Img->GetPixel(Phi * Kw, -Theta * Kh);

  /* Convert to RGB */
  Shd->Mtl.Kd = image::ToRgb(Pixel);

  /* Clamping color */
  Shd->Mtl.Kd.Clamp(0.0, 1.0); 
} /* End of 'Apply' function */

/* Point modificator destructor function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
dert::sphere_tex_mods::~sphere_tex_mods( VOID )
{
  delete Img;
} /* End of '~sphere_tex_mods' function */

/* Cylinder texture modificator constructor function.
  * ARGUMENTS:
  *   - reference to filename to load image:
  *        std::string &FileName;
  * RETURNS: None.
  */
dert::cylin_tex_mods::cylin_tex_mods( const std::string &FileName )
{
  Img = new image;
  Img->Load("BIN/TEXTURES/" + FileName);
} /* End of 'cylin_tex_mods' function */

/* Cylinder texture modificator apply function.
 * ARGUMENTS:
 *   - pointer to shade data type:
 *        shade_data *Shd;
 * RETURNS: None.
 */
VOID dert::cylin_tex_mods::Apply( shade_data *Shd )
{
  /* Get Cylinder coordinates from cartesian */
  DBL 
    R = sqrt(mth::sqr(Shd->P[1]) + mth::sqr(Shd->P[2])),
    Phi = 2 * atan2(Shd->P[0], Shd->P[1]) + mth::PI, Kw;

  /* Get coefficients */
  Kw = Img->GetWidth() / (2 * mth::PI);

  /* Get pixel from image */
  DWORD Pixel = Img->GetPixel(Phi * Kw, Shd->P[2]);

  /* Convert to RGB */
  Shd->Mtl.Kd = image::ToRgb(Pixel);

  /* Clamping color */
  Shd->Mtl.Kd.Clamp(0.0, 1.0); 
} /* End of 'Apply' function */

// Class destructor
dert::cylin_tex_mods::~cylin_tex_mods( VOID )
{
  delete Img;
} /* End of '~cylin_tex_mods' function */

/* Torus texture modificator constructor function.
 * ARGUMENTS:
 *   - reference to filename to load image:
 *        std::string &FileName;
 * RETURNS: None.
 */
dert::torus_tex_mods::torus_tex_mods( const std::string &FileName )
{
  Img = new image;
  Img->Load("BIN/TEXTURES/" + FileName);
} /* End of 'torus_tex_mods' function */

/* Torus texture modificator apply function.
 * ARGUMENTS:
 *   - reference to projection camera:
 *        camera &Cam;
 *   - pointer to shade data type:
 *        shade_data *Shd;
 * RETURNS: None.
 */
VOID dert::torus_tex_mods::Apply( shade_data *Shd )
{
  vec V = (Shd->P - Shd->D[0] * vec(Shd->P[0], 0, Shd->P[2]).Normalize()).Normalize();

  /* Get directional angles */
  DBL 
    Phi = 2 * atan2(Shd->P[2], Shd->P[0]) + mth::PI, 
    Theta = acos(V[1]), Kw, Kh;

  
  /* Get coefficients */
  Kh = Img->GetHeight() / mth::PI;
  Kw = Img->GetWidth() / (2 * mth::PI);

  /* Get pixel from image */
  DWORD Pixel = Img->GetPixel(Phi * Kw, -Theta * Kh);

  /* Convert to RGB */
  Shd->Mtl.Kd = image::ToRgb(Pixel);

  /* Clamping color */
  Shd->Mtl.Kd.Clamp(0.0, 1.0); 
} /* End of 'Apply' function */

/* Torus modificator destructor function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
dert::torus_tex_mods::~torus_tex_mods( VOID )
{
  delete Img;
} /* End of '~torus_tex_mods' function */

/* Point modificator constructor function (rotation).
 * ARGUMENTS:
 *   - rotate angle:
 *        DBL AngleInDegree;
 *   - reference to rotate axis:
 *        vec &Rot;
 * RETURNS: None.
 */
dert::point_mods::point_mods( DBL AngleInDegree, const vec &Rot )
{
  Main = matr::Rotate(AngleInDegree, Rot);
} /* End of constructor */

/* Point modificator constructor function (translate).
 * ARGUMENTS:
 *   - reference to translate vector:
 *        vec &Tr;
 * RETURNS: None.
 */
dert::point_mods::point_mods( const vec &Tr )
{
  Main = matr::Translate(Tr);
} /* End of constructor */

/* Point modificator constructor function (scale).
 * ARGUMENTS:
 *   - reference to scale vector:
 *        vec &Sc;
 *   - dummy argument (for overload):
 *        INT Dummy;
 * RETURNS: None.
 */
dert::point_mods::point_mods( const vec &Sc, INT Dummy )
{
  Main = matr::Scale(Sc);
} /* End of constructor */

/* Point modificator apply function.
 * ARGUMENTS:
 *   - pointer to shade data type:
 *        shade_data *Shd;
 * RETURNS: None.
 */
VOID dert::point_mods::Apply( shade_data *Shd )
{
  Shd->P = Shd->P * Main;
  Shd->N = Shd->N * (Main.Inverse()).Transpose();
} /* End of 'Apply' function */

/* Modificator ray transform function.
 * ARGUMENTS:
 *   - reference to ray to transform:
 *        ray &R;
 * RETURNS: 
 *       (DBL) length of direction transform vector;
 */
DBL dert::point_mods::RayTrans( ray &R )
{
  R.Org.VecTrans(Main.Inverse());
  vec r = R.Dir.PointTrans(Main.Inverse());
  R.Dir = r.Normalize();
  return !r;
} /* End of 'RayTrans' function */

dert::point_mods::~point_mods( VOID )
{
}

/* End of 'MODS.CPP' file */