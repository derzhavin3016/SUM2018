/* FILE NAME: prim.cpp
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#include "PRIM.H"


/* Primitive constructor by vertex and index sizes function.
* ARGUMENTS:
*   - link to primitive type:
*       prim_type &T;
*   - vertex array:
*       VERTEX *V;
*   - vertex array size:
*       INT NoofV;
*   - index array:
*       INT *I;
*   - index array size:
*       INT NoofI;
* RETURNS: NONE:
*/
VOID degl::prim::create( const prim_type &T, const std::vector<VERTEX> &V, const std::vector<INT> &I )
{
  
  glGenBuffers(1, &VBuf);
  glGenVertexArrays(1, &VA);

  glBindVertexArray(VA);
  glBindBuffer(GL_ARRAY_BUFFER, VBuf);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX) * V.size(), &V[0], GL_STATIC_DRAW);
  //glBindBuffer(GL_ARRAY_BUFFER, VBuf);

  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)sizeof(vec));
  glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)(sizeof(vec) + sizeof(vec2)));
  glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)(sizeof(vec) * 2 + sizeof(vec2)));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);

  glBindVertexArray(0);


  if (I.size() != 0)
  {
    glGenBuffers(1, &IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * I.size(), &I[0], GL_STATIC_DRAW);
  }


/*  memset(this, 0, sizeof(prim));

  V = new VERTEX[NoofV];
  I = new INT[NoofI];
  NumOfI = NoofI;
  NumOfV = NoofV;*/
  Type = T;
  ICount = I.size();



  /* Set default transform (identity) */
  Trans = matr::Identity();
} /* End of prim constructor */

/* Primitive destructor */
degl::prim::~prim( VOID )
{
    glBindVertexArray(VA);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBuf);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VA);
 
  if (IBuf != 0)
    glDeleteBuffers(1, &IBuf);



  memset(this, 0, sizeof(prim));

}

/* Load primitive from "*.OBJ" file function.
* ARGUMENTS:
*   - primitive to be load to:
*        *Pr;
*   - filename to load from:
*       CHAR *FileName;
* RETURNS:
*   (BOOL) TRUE if success, FALSE otherwise.
*/
BOOL degl::prim::Load( const CHAR *FileName )
{
  FILE *F;
  CHAR Buf[1000];
  std::vector<VERTEX> V;
  std::vector<INT> I;

  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Load primitive data */
  rewind(F);
  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);

      V.push_back(VERTEX(vec(x, y, z)));
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

  /* Create primitive */
  create(MESH, V, I);

  return TRUE;
} /* End of 'PrimLoad' function */


degl::prim::prim( const prim_type &T, const std::vector<VERTEX> &V, const std::vector<INT> &I ) : VA(0), VBuf(0), IBuf(0), Type(T)
{
  create(T, V, I);
}