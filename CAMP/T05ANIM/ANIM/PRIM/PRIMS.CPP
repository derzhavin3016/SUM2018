/* FILE NAME: prims.cpp
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#include "PRIMS.H"

degl::prims::~prims( VOID )
{
  for ( auto s : Primitives)
    delete s;
}

degl::prims::prims( VOID ) : prim()
{
}

/* Load primitives from 'G3DM' file function.
* ARGUMENTS:
*   - file name:
*       const std::string &FileName;
*   - transformation matrix:
*       const matr &Transform;
* RETURNS:
*   (BOOL) TRUE if success, FALSE otherwise.
*/
BOOL degl::prims::Load( const std::string &FileName, const matr &Transform )
{
  FILE *F;
  DWORD Sign;
  INT NoofP = 0, NoofM = 0, NoofT = 0, i;

  /* Open file */
  if ((F = fopen(FileName.c_str(), "rb")) == NULL)
    return FALSE;
  /* Check signature */
  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3DM")
  {
    fclose(F);
    return FALSE;
  }

  /* Read quantities */
  fread(&NoofP, 4, 1, F);
  fread(&NoofM, 4, 1, F);
  fread(&NoofT, 4, 1, F);

  Primitives.resize(NoofP);

  /* Primitive material indices */
  std::vector<INT> prims_mtl;
  prims_mtl.resize(NoofP);

  /* Load primitives */
  for (i = 0; i < NoofP; i++)
  {
    INT nv = 0, ni = 0, j;

    std::vector<VERTEX> V;
    std::vector<INT> I;
    fread(&nv, 4, 1, F);
    fread(&ni, 4, 1, F);
    fread(&prims_mtl[i], 4, 1, F);
    V.resize(nv);
    I.resize(ni);

    fread(&V[0], 1, sizeof(VERTEX) * nv, F);
    fread(&I[0], 1, sizeof(INT) * ni, F);

    for (j = 0; j < nv; j++)
    {
      V[j].P = V[j].P * Transform;
      V[j].N = V[j].N * Transform.Inverse().Transpose();
    }
    Primitives[i] = new prim(MESH, V, I);
    //Primitives[i]->create(MESH, V, I);
  }

  /* Load materials */
  struct STORE_MATERIAL
  {
    CHAR Name[300]; /* Material name */

                    /* Illumination coefficients */ 
    vec Ka, Kd, Ks;        /* Ambient, diffuse, specular coefficients */
    FLT Ph;                /* Phong power coefficient */
    FLT Trans;             /* Transparency factor */
    INT Tex[8];            /* Texture references */

                           /* Shader string */
    CHAR ShaderStr[300];
    INT Shader;                        /* Texture references */
  }; /* End of 'STORE_MATERIAL' struct */

  std::vector<material> mtls;
  std::vector<STORE_MATERIAL> store_mtls;
  Materials.resize(NoofM);
  store_mtls.resize(NoofM);
  if (NoofM > 0)
  {
    fread(&store_mtls[0], sizeof(STORE_MATERIAL), NoofM, F);
    for (INT i = 0; i < NoofM; i++)
      Materials[i] =  CreateMaterial(store_mtls[i].Name, 300,
        store_mtls[i].Ka, store_mtls[i].Kd, store_mtls[i].Ks,
        store_mtls[i].Ph, store_mtls[i].Trans);
  }
  /* Load textures */
  std::vector<texture *> texs;
  texs.resize(NoofT);
  for (i = 0; i < NoofT; i++)
  {
    CHAR *Name;
    Name = new CHAR [300];
    INT W, H, C;
    BYTE *mem;
    texs[i] = new texture;

    fread(Name, 1, 300, F);
    fread(&W, 4, 1, F);
    fread(&H, 4, 1, F);
    fread(&C, 4, 1, F);
    //mem = new BYTE[W * H * 4];

    mem = new BYTE[W * H * C];
    fread(mem, C, W * H, F);
    //Textures[i].TextureCreate(Name, W, H, C, mem);

    //fread(mem, 4, W * H, F);
    texs[i]->TexId = TexAddImg(std::string(Name), W, H, /*C,*/ (DWORD *)mem);
    delete[] mem;
    delete[] Name;
  }
  fclose(F);

  /* Correct material texture references */
  for (INT i = 0; i < NoofM; i++)
    for (INT t = 0; t < 8; t++)
      if (store_mtls[i].Tex[t] != -1)
        Materials[i].Tex[t] = texs[store_mtls[i].Tex[t]]->TexId;

  /* Correct primitives material references */
  for (INT i = 0; i < NoofP; i++)
    if (prims_mtl[i] != -1)
      Primitives[i]->Mtl = Materials[prims_mtl[i]];

  for (INT i = 0; i < NoofT; i++)
    delete texs[i];


  return TRUE;
} /* End of 'Load' function */

/* End of 'prims.cpp' file */