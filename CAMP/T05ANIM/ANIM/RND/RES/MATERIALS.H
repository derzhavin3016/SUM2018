/* FILE NAME: materials.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#ifndef __MATERIALS_H_
#define __MATERIALS_H_

#include "SHADERS.H"
#include "TEXTURES.H"
#include <vector>

namespace degl
{
  class material : public shader,  public texture
  {
  public:
    CHAR Name[300];
    // Illumination coefficients
    vec Ka, Kd, Ks;          // Ambient, diffuse, specular coefficients
    FLT Ph;                  // Phong power coefficient
    FLT Trans;               // Transparency factor
    INT Tex[8];              // Texture references from texture table

    // Shader string
    std::string ShaderStr;
    material &CreateMaterial( CHAR *N, INT size, vec A, vec D, vec S, FLT P, FLT Tr )
    {
      strncpy(Name, N, size);
      Ka = A;
      Kd = D;
      Ks = S;
      Ph = P;
      Trans = Tr;
      return *this;
    }

    material & operator=( const material &M )
    {
      for (INT i = 0; i < 300; i++)
        Name[i] = M.Name[i];
      Ka = M.Ka;
      Kd = M.Kd;
      Ks = M.Ks;
      Ph = M.Ph;
      Trans = M.Trans;
      for (INT i = 0; i < 8; i++)
        Tex[i] = M.Tex[i];
      return *this;
    }

    material( VOID )
    {
      for (INT i = 0; i < 8; i++)
        Tex[i] = -1;
    }

    INT MtlApply( VOID )
    {
      // Set program Id
      INT prg = 0;// = shaders[ShaderStr];
      if (prg <= 0 || prg >= shaders.size())
        prg = shaders["BIN/SHADERS/DEFAULT"];
      else
        prg = shaders[ShaderStr];
      glUseProgram(prg);
      INT loc;

      if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
        glUniform3fv(loc, 1, &Ka[0]);
      if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
        glUniform3fv(loc, 1, &Kd[0]);
      if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
        glUniform3fv(loc, 1, &Ks[0]);
      if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
        glUniform1f(loc, Ph);
      if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
        glUniform1f(loc, Trans);

      for (INT i = 0; i < 8; i++)
      {

        CHAR Buf[100] = "IsTexture0";

        Buf[9] = '0' + i;
        if ((loc = glGetUniformLocation(prg, Buf)) != -1)
          glUniform1i(loc, Tex[i] != -1);
        if (Tex[i] != -1)
        {
          glActiveTexture(GL_TEXTURE0 + i);
          glBindTexture(GL_TEXTURE_2D, Tex[i]);
        }
      }

      return prg;
    }
  };

  class material_manager : public material
  {
  public:
    vector<material> Materials;

    

    INT MtlApply( INT MtlNo )
    {
      INT prg;
      material *mtl;

      // Set material pointer
      MtlNo = mth::Clamp(MtlNo, 0, INT(Materials.size()));
      
      mtl = &Materials[MtlNo];

      // Set program Id
      prg = shaders[mtl->ShaderStr];

      if (prg < 0 || prg >= shaders.size())
        prg = shaders["BIN/SHADERS/DEFAULT"];
      else
        prg = shaders[mtl->ShaderStr];
      glUseProgram(prg);
      INT loc;

      if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
        glUniform3fv(loc, 3, &mtl->Ka[0]);
      if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
        glUniform3fv(loc, 3, &mtl->Kd[0]);
      if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
        glUniform3fv(loc, 3, &mtl->Ks[0]);
      if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
        glUniform1f(loc, mtl->Ph);
      if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
        glUniform1f(loc, mtl->Trans);

      for (INT i = 0; i < 8; i++)
      {
        CHAR Buf[100] = "IsTexture0";

        Buf[9] = '0' + i;
        if ((loc = glGetUniformLocation(prg, Buf)) != -1)
          glUniform1i(loc, mtl->Tex[i] != -1);
        if (mtl->Tex[i] != -1)
        {
          glActiveTexture(GL_TEXTURE0 + i);
          glBindTexture(GL_TEXTURE_2D, Textures[mtl->Tex[i]].TexId);
        }
      }
      
      return prg;
    }

    VOID MtlAdd( const material &Mtl )
    {
      Materials.push_back(Mtl);
      MtlApply(Materials.size() - 1);
    }

    VOID MtlInit( VOID )
    {
      CHAR Buf[300] = "default material";
      material defmtl = CreateMaterial(Buf, 300, vec(0.1, 0.1, 0.1), 
                       vec(0.5, 0.3, 0.4),
                       vec(0.1, 0.3, 0.4),
                       10, 1); 
      for (int i = 0; i < 8; i++)
        defmtl.Tex[i] = -1;
      defmtl.ShaderStr = "";
      Materials.push_back(defmtl);
    }
  };
} /* End of 'degl' namespace */

#endif /* __MATERIALS_H_ */
