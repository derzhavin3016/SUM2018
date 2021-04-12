/* FILE NAME: textures.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#ifndef __TEXTURES_H_
#define __TEXTURES_H_

#include "../../../DEF.H"
#include "IMAGE.H"

namespace degl
{
  class texture : public image
  {
  public:
    UINT TexId;       // OpenGL texture Id

    // Textures stock
    std::vector<texture> Textures;
    texture( VOID )
    {
      TexId = 0;
    }

    texture & operator=( const texture &T )
    {
      TexId = T.TexId;
      return *this;
    }

    texture &TextureCreate( std::string Nam, INT w, INT h, BYTE *mem)
    {
      return *this;
    }
    INT TexAddImg( std::string N, INT W, INT H, DWORD *Bits )
    {
      if (Textures.size() >= 30)
        return -1;
      else if (Textures.size() == 0)
        Textures.push_back(texture());

      // Alocate texture space
      glGenTextures(1, &Textures[Textures.size() - 1].TexId);
      glBindTexture(GL_TEXTURE_2D, Textures[Textures.size() - 1].TexId);

      // Upload texture
      gluBuild2DMipmaps(GL_TEXTURE_2D, 4, W, H,
        GL_BGRA_EXT, GL_UNSIGNED_BYTE, Bits);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      //Textures[Textures.size() - 1] = (TextureCreate(N, W, H, (BYTE *)Bits));
      glBindTexture(GL_TEXTURE_2D, Textures[Textures.size() - 1].TexId);

      return Textures[Textures.size() - 1].TexId;
    }

    texture &CreateTex( std::string N, INT W, INT H, DWORD *Bits )
    {
      TexAddImg(N, W, H, Bits);
      return *this;
    }

    /* Add texture to stock from file function.
    * ARGUMENTS:
    *   - texture file name:
    *       std::string FileName;
    * RETURNS:
    *   (INT) new texture stock number (-1 if error occured).
    */
    INT TexAdd( std::string FileName )
    {
      INT n;
      image Img;

      if (!Img.ImgLoad(FileName))
        return -1;
      n = TexAddImg(FileName, Img.W, Img.H, Img.Bits);
      return n;
    } /* End of 'TexAdd' function */

  };

 /* class texture_manager : public texture
  {
  public:

    INT TexAddImg( CHAR *Name, INT W, INT H, DWORD *Bits )
    {
      if (Textures.size() >= 30)
        return -1;

      // Alocate texture space
      glGenTextures(1, &Textures[Textures.size()].TexId);
      glBindTexture(GL_TEXTURE_2D, Textures[Textures.size()].TexId);
      
      // Upload texture
      gluBuild2DMipmaps(GL_TEXTURE_2D, 4, W, H,
        GL_BGRA_EXT, GL_UNSIGNED_BYTE, Bits);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      Textures.push_back(TextureCreate(Name, W, H, (BYTE *)Bits));
      glBindTexture(GL_TEXTURE_2D, 0);

      return Textures.size();
    }
    
 



  }; */
}

#endif /* __TEXTURES_H_ */
