/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : SHAPE.H
* PURPOSE     : Ray tracing.
*               Shapes.
*               Base class.
* PROGRAMMER  : AD6.
* LAST UPDATE : 16.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __SHAPE_H_
#define __SHAPE_H_

#include "../INTR.H"
#include "../MATERIALS.H"
#include "../../RES/MODS/MODS.H"


namespace dert
{
  class shape
  {
  public:
    material Mtl;                        // Shape material
    environment Envi;                    // Shape environment
    std::vector<base_mods *> Mods;       // Modificators array

    shape( VOID )
    {
    }

    ~shape( VOID )
    {
      for (auto m : Mods)
        delete m;
    }

    shape( const material &Mtl, const environment &Envi ) : Mtl(Mtl), Envi(Envi)
    {
    }

    shape &operator<<( base_mods *M )
    {
      Mods.push_back(M);
      return *this;
    }

   /* Find intersection function (virtual)
    * ARGUMENTS: 
    *   - reference to ray to find intersection with:
    *        ray &R;
    *   - pointer to intersection type:
    *        intr *Intr;
    * RETURNS:
    *       (BOOL) TRUE if there is a intersection, FALSE otherwise.
    */
    virtual BOOL Intersect( const ray &R, intr *Intr )
    {
      return TRUE;
    } /* End of 'Intersect' function */

   /* Find all intersections function (virtual)
    * ARGUMENTS: 
    *   - reference to ray to find intersections with:
    *        ray &R;
    *   - pointer to intersections type:
    *        intr_list *IList;
    * RETURNS:
    *       (INT) Amount of intersections.
    */
    virtual INT AllIntersect( const ray &R, intr_list *IList )
    {
      return 0;
    } /* End of 'AllIntersect' function */

   /* Normal evaluation function
    * ARGUMENTS:
    *   - pointer to intersection type:
    *        intr *Intr;
    * RETURNS: None.
    */
    virtual VOID EvalNormal( intr *Intr )
    {
    } /* End of 'EvalNormal' function */

  };

  class shape_list
  {
  public:
    std::vector<shape *> Shapes;

   /* Find intersection function
    * ARGUMENTS: 
    *   - reference to ray to find intersection with:
    *        ray &R;
    *   - pointer to intersection type:
    *        intr *Intr;
    * RETURNS:
    *       (BOOL) TRUE if there is a intersection, FALSE otherwise.
    */
    BOOL Intersect( const ray &R, intr *Intr )
    {
      DBL t_min = mth::Infinity;
      intr I;
      shape *S;
      S = nullptr;

      for (auto &s : Shapes)
      {
        if (!s->Intersect(R, &I))
          continue;
        if (I.T < t_min && I.T > 0)
        {
          t_min = I.T;
          Intr->SetIntr(I);
          S = I.Shp;
        }
      }

      if (S == nullptr)
        return FALSE;

      return TRUE;
    } /* End of 'Intersect' function */

   /* Find all intersections function
    * ARGUMENTS: 
    *   - reference to ray to find intersections with:
    *        ray &R;
    *   - pointer to intersections type:
    *        intr_list *IList;
    * RETURNS:
    *       (INT) Amount of intersections.
    */
    INT AllIntersect( const ray &R, intr_list *IList )
    {
      INT n = 0;
      for (auto s : Shapes)
        n += s->AllIntersect(R, IList);
      return n;
    } /* End of 'AllIntersect' function */

   /* Normal evaluation function
    * ARGUMENTS:
    *   - pointer to intersection type:
    *        intr *Intr;
    * RETURNS: None.
    */
    VOID EvalNormal( intr *Intr )
    {
      Intr->Shp->EvalNormal(Intr);
    } /* End of 'EvalNormal' function */

    shape_list &operator<<( shape *Shp )
    {
      Shapes.push_back(Shp);
      return *this;
    }
  };
} /* End of 'dert' namespace */




#endif /* __SHAPE_H_ */

  /* End of 'SHAPE.H' file */
