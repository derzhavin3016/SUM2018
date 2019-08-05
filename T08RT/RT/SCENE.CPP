/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : SCENE.CPP
* PURPOSE     : Ray tracing.
*               Scene class.
*               Functions realization.
* PROGRAMMER  : AD6.
* LAST UPDATE : 01.09.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "SCENE.H"

/* Scene constructor function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
dert::scene::scene( VOID )
{
  material 
    Gold(vec(0.24725, 0.1995, 0.0745), vec(0.75164, 0.60648, 0.22648),
                   vec(0.628281, 0.555802, 0.366065), vec(0), vec(0), 51.2),
    Mirror(vec(0), vec(0), vec(1), vec(1), vec(0), 50),
    Glass(vec(0), vec(0), vec(1), vec(0.1), vec(0.9), 50),
    Plane(vec(0.2), vec(0.8), vec(0.3), vec(0.9), vec(0), 24),
    Black(vec(0), vec(0), vec(0), vec(0), vec(0), 0);
  environment
    GlassEnvi(0.08, 0.96);
  SList << //new quad(0.05, 0, 0, 0, 0.05, 0, 0, -0.25, 0-, -1, Gold, AirEnvi) <<
    new torus(4.0, 1.0, DefMtl, AirEnvi) <<
    //new triangle(vec(0, 5, 0), vec(0, 0, -5), vec(0, 0, 5), Gold, AirEnvi) <<
    new sphere(vec(-9, 4, -5), 5.0, Mirror, environment(0, 1)) <<
    new sphere(vec(-2, 3, 9), 4.0, DefMtl, environment(0, 1)) <<
    new sphere(vec(1, 3, -8), 4.0, Glass, GlassEnvi) <<
    //new prim("cow.object", Gold, AirEnvi) <<
    new plane(vec(0, 1, 0), -1.0, Plane, environment(0, 1)) <<
    new box(vec(-50), vec(50), Black, AirEnvi);
  AmbientColor = vec(0);
  SList.Shapes[0]->Mods.push_back(new torus_tex_mods("bun.bmp"));
  SList.Shapes[2]->Mods.push_back(new sphere_tex_mods("earth.bmp"));
  SList.Shapes[4]->Mods.push_back(new plane_tex_mods("checker.bmp"));
  //SList.Shapes[0]->Mods.push_back(new cylin_tex_mods("bat.bmp"));
  //Lights.push_back(new pos_light(vec(18, 10, 1), 1.0, 0.0001, 0.0001, vec(1)));
  //Lights.push_back(new pos_light(vec(0, 8, 8), 0.01, 0.01, 0.01, vec(0, 0, 1)));
  //Lights.push_back(new spot_light(vec(18, 10, -15), vec(-18, -10, 15), 30, 45, vec(0.94, 0.56, 0.357)));
  Lights.push_back(new spot_light(vec(18, 15, 5), vec(-18, -15, -5), 40, 45, vec(1)));
  Lights.push_back(new dir_light(vec(0, 1, 0), vec(0.3, 0.6, 0.4)));
} /* End of 'scene' function */

/* Scene destructor function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
dert::scene::~scene( VOID )
{
  for (auto s : SList.Shapes)
    delete s;
  for (auto l : Lights)
    delete l;
} /* End of '~scene' function */

/* Render scene function.
 * ARGUMENTS:
 *   - reference to projection camera:
 *        camera &Cam;
 *   - pointer to image to draw:
 *        image *Img;
 * RETURNS: None.
 */
VOID dert::scene::Render( camera &Cam, image *Img )
{
  INT n = std::thread::hardware_concurrency() - 1;

  std::vector<std::thread > T;
  T.resize(n);
  std::vector<vec> Bits;
  Bits.resize(Cam.GetHeight() * Cam.GetWidth());

  for (INT i = 0; i < n; i++)
  {
    T[i] = std::thread([&]()
                      {
                        for (INT ys = i * 2; ys < Cam.GetHeight(); ys += 2 * n)
                          for (INT xs = 0; xs < Cam.GetWidth(); xs += 2)
                          {
                            ray 
                              R1(Cam.ToRay(xs, ys)),
                              R2(Cam.ToRay(xs + 1, ys)),
                              R3(Cam.ToRay(xs, ys + 1)),
                              R4(Cam.ToRay(xs + 1, ys + 1));
                            vec 
                              Color1, Color2, Color3, Color4, Result;
                            CurrentLevel = 0;
                            Color1 = Trace(R1, AirEnvi, vec(1));
                            CurrentLevel = 0;
                            Color2 = Trace(R2, AirEnvi, vec(1));
                            CurrentLevel = 0;
                            Color3 = Trace(R3, AirEnvi, vec(1));
                            CurrentLevel = 0;
                            Color4 = Trace(R4, AirEnvi, vec(1));
                            Color1.Clamp(0.0, 1.0);
                            Color2.Clamp(0.0, 1.0);
                            Color3.Clamp(0.0, 1.0);
                            Color4.Clamp(0.0, 1.0);
                          
                            Result = (Color1 + Color2 + Color3 + Color4) / 4.0;
                            Result.Clamp(0.0, 1.0);
                            Img->PutPixel(xs / 2, ys / 2, image::ToDWORD(Result));
                          }
                      });
    //T[i].join();
  }

  for (auto &t : T)
    t.join();
} /* End of 'Render' function */


/* Trace rays function.
 * ARGUMENTS:
 *   - reference to ray:
 *        ray &R;
 * RETURNS:
 *      (vec) color;
 */
dert::vec dert::scene::Trace( const ray &R, const environment &Envi,
                              const vec &Weight )
{
  vec Color, FogColor(0.05);
  intr Intr;
  DBL 
    Threshold = 0.1,
    ColorThreshold = 1 / 255,
    start = 10.0,
    end = 60.0;
  MaxLevel = 4;


  if (CurrentLevel <= MaxLevel && (vec)Weight >= vec(Threshold))
  {
    if (SList.Intersect(R, &Intr))
    {
      if (!Intr.IsP)
      {
        Intr.P = R(Intr.T);
        Intr.IsP = TRUE;
      }

      if (!Intr.IsN)
      {
        SList.EvalNormal(&Intr);
        Intr.IsN = TRUE;
      }
      // Fog
      DBL fog = Intr.T < start ? 1 : Intr.T > end ? 0 : 
        (-Intr.T + end) / (end - start);
      if (fog == 0)
        return FogColor;
      
      Color = Shade(R.Dir, Intr, Envi, Weight) * exp(-Envi.Decay * Intr.T);
      
      Color = Color * fog + (1 - fog) * FogColor;
      CurrentLevel++;
    }
  }
  return Color;
} /* End of 'Trace' function */

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
dert::vec dert::scene::Shade( const vec &V, const intr &Intr,
                              const environment &Envi, const vec &Weight )
{
  shade_data Shd(Intr);
  DBL ColorThreshold = 1 / 255;
  // Normal face forward
  DBL vn = Shd.N.Normalizing() & V;

  if (vn > Threshold)
  {
    vn = -vn;
    Shd.N = -Shd.N;
    Shd.IsEnter = 1 - Shd.IsEnter;
  }
  Shd.Mtl = Intr.Shp->Mtl;
  Shd.Envi = Intr.Shp->Envi;

  vec Color(0);
  Color += AmbientColor * Shd.Mtl.Ka;

  for (auto &m : Intr.Shp->Mods)
    m->Apply(&Shd);

  vec R = (V - Shd.N * 2 * vn).Normalize();
  for (auto Lig : Lights)
  {
    light_attenuation Att;
    if (Lig->GetData(Shd, &Att))
    {
      intr_list il;

      if (SList.AllIntersect(ray(Shd.P + Att.L * Threshold, Att.L), &il) > 0)
      {
        for (auto &i : il)
          if (i.T < Att.Dist && i.IsEnter)
            Att.Color *= i.Shp->Mtl.Ktrans;
      }
      
      // Light attenuation
      Att.Color *= Att.Fatt;

      if (Att.Color < vec(ColorThreshold))
        continue;

      // Diffuse color
      DBL nl = Shd.N & Att.L;
      if (nl > Threshold)
        Color += Shd.Mtl.Kd * Att.Color * nl;
     
      // Specular color
      DBL rl = R & Att.L;
      if (rl > Threshold)
        Color += Shd.Mtl.Ks * Att.Color * pow(rl, Shd.Mtl.Ph);
    }
  }

  // Reflected ray
  vec wr = Weight * Shd.Mtl.Krefl;
  if (wr > vec(ColorThreshold))
  {
    ray Ra(Shd.P + R * Threshold, R);
    Color += Trace(Ra, Envi, wr) * Shd.Mtl.Krefl;
  }

  // Refracted ray
  vec wt = Weight * Shd.Mtl.Ktrans;
  if (wt > vec(ColorThreshold))
  {
    DBL Eta = Shd.IsEnter ? Shd.Envi.NRefr / Envi.NRefr : AirEnvi.NRefr / Envi.NRefr;
    DBL coef = 1 - (1 - vn * vn) * mth::sqr(Eta);
  if (coef > Threshold)
  {
    vec T = (V - Shd.N * vn) * Eta - sqrt(coef) * Shd.N;
    ray Rays(Shd.P + T * Threshold, T);
    Color += Trace(Rays, Shd.IsEnter ? Shd.Envi : AirEnvi, wt) * Shd.Mtl.Ktrans;
  }
  }
  return Color;
} /* End of 'Shade' function */

/* End of 'scene.cpp' file */