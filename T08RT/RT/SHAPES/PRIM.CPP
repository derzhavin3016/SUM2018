/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : PRIM.CPP
* PURPOSE     : Ray tracing.
*               Shapes.
*               Primitive.
*               Functions realization.
* PROGRAMMER  : AD6.
* LAST UPDATE : 23.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "PRIM.H"


/* Primitive constructor function.
 * ARGUMENTS:
 *   - filename to load from:
 *       std::string &FileName;
 *   - reference to material type:
 *       material &Mt;
 *   - reference to environment type:
 *       environment &Env;
 * RETURNS: None.
 */
dert::prim::prim( const std::string &FileName, const material &Mt,
                  const environment &Env ) :
  shape(Mt, Env)
{
  LoadObj(FileName);
}

/* Primitive destructor */
dert::prim::~prim( VOID )
{
  for(auto &t : Tr)
    delete t;
}

/* Load primitive from "*.OBJ" file function.
 * ARGUMENTS:
 *   - filename to load from:
 *       std::string &FileName;
 * RETURNS:
 *  (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL dert::prim::LoadObj( const std::string &FileName )
{
  FILE *F;
  CHAR Buf[1000];
  vec Max(-mth::Infinity), Min(mth::Infinity);  // Coordinates to bound-box
  std::vector<vec> V;
  std::vector<INT> I;
  std::string Name = "BIN/MODELS/";
  Name += FileName;


  if ((F = fopen(Name.c_str(), "r")) == NULL)
    return FALSE;

  /* Load primitive data */
  rewind(F);
  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      vec Vertex(x, y, z);
      Max = vec::Max(Max, Vertex);
      Min = vec::Min(Min, Vertex);
      V.push_back(Vertex);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);
      I.push_back(n1 - 1);
      I.push_back(n2 - 1);
      I.push_back(n3 - 1);
    }
  fclose(F);

  for(INT i = 0; i < I.size(); i += 3)
    Tr.push_back(new triangle(V[I[i]], V[I[i + 1]], V[I[i + 2]], Mtl, Envi));

  BoundBox.SetVertex(Min, Max);

  V.clear();
  I.clear();

  return TRUE;
} /* End of 'prim' function */

/* Find intersection with primitive function.
 * ARGUMENTS: 
 *   - reference to ray to find intersection with:
 *        ray &R;
 *   - pointer to intersection type:
 *        intr *Intr;
 * RETURNS:
 *       (BOOL) TRUE if there is a intersection, FALSE otherwise.
 */
BOOL dert::prim::Intersect( const ray &R, intr *Intr )
{
  DBL t_min = mth::Infinity;
  intr I;
  I.Shp = nullptr;

  if (BoundBox.IsIntersect(R))
  {
    for (auto &t : Tr)
    {
      if (!t->Intersect(R, &I))
        continue;
      if (I.T < t_min && I.T > 0)
      {
        t_min = I.T;
        Intr->SetIntr(I.Shp, I.T, I.IsEnter);
      }
    }
    
    if (I.Shp == nullptr)
      return FALSE;
    return TRUE;
  }

  return FALSE;
} /* End of 'Intersect' function */

/* Find all intersections with primitive function.
 * ARGUMENTS: 
 *   - reference to ray to find intersections with:
 *        ray &R;
 *   - pointer to intersections type:
 *        intr_list *IList;
 * RETURNS:
 *       (INT) Amount of intersections.
 */
INT dert::prim::AllIntersect( const ray &R, intr_list *IList )
{
  INT n = 0;

  if (BoundBox.IsIntersect(R))
  {
    for (auto &t : Tr)
      n += t->AllIntersect(R, IList);
  }

  return n;
} /* End of 'AllIntersect' function */

/* Normal evaluation function
 * ARGUMENTS:
 *   - pointer to intersection type:
 *        intr *Intr;
 * RETURNS: None.
 */
VOID dert::prim::EvalNormal( intr *Intr )
{
  Intr->Shp->EvalNormal(Intr);
} /* End of 'EvalNormal' function */

/* End of 'PRIM.CPP' file */