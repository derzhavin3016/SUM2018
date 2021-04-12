/* FILE NAME: image.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include "../../../DEF.H"

namespace degl
{
  class image
  {
  public:
    INT W, H;                   // Image size in pixels
    DWORD *Bits;    // Image pixels: pixel(X, Y) = Bits[Y * W + X]
    HBITMAP *hBm;               // WinAPI bitmap handle
  public:
    // default class constructor
    image( VOID ) : W(0), H(0), hBm(nullptr)
    {    
    }
    
    /* Load image from BMP file function.
     * ARGUMENTS: 
     *   - image file name:
     *       std::string FileName;
     * RETURNS:
     *   (BOOL) TRUE if succesful, FALSE otherwise.
     */
    BOOL ImgLoad( std::string &FileName )
    {
      HBITMAP hBmFile;
      BITMAP bm;
      BITMAPINFOHEADER bmih = {0};
      HDC hMemDC1, hMemDC2;
      HDC hDC = GetDC(NULL);

      if ((hBmFile = (HBITMAP)LoadImage(NULL, FileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)) == NULL)
        return FALSE;

      GetObject(hBmFile, sizeof(BITMAP), &bm);

      bmih.biSize = sizeof(BITMAPINFOHEADER);
      bmih.biPlanes = 1;
      bmih.biCompression = BI_RGB;
      bmih.biBitCount = 32;
      bmih.biWidth = W = bm.bmWidth;
      bmih.biHeight = H = bm.bmHeight;
      bmih.biSizeImage = W * H * 4;
      
      hBm = (HBITMAP *)CreateDIBSection(NULL, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, (VOID **)&Bits, NULL, 0);
      hMemDC1 = CreateCompatibleDC(hDC);
      SelectObject(hMemDC1, hBmFile);
      
      hMemDC2 = CreateCompatibleDC(hDC);
      SelectObject(hMemDC2, hBmFile);
      BitBlt(hMemDC2, 0, 0, W, H, hMemDC1, 0, 0, SRCCOPY);

      DeleteDC(hMemDC1);
      DeleteDC(hMemDC2);
      DeleteObject(hBmFile);

      // Fill alpha channel
      for (INT i = 0; i < W * H; i++)
        Bits[i] |= 0xFF000000;
      return TRUE;
    }

    // Class destructor
    ~image( VOID )
    {
      DeleteObject(hBm);
      memset(this, 0, sizeof(image));
    }


    /* Upload image to OpenGL texture memory function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID ImgToTex( VOID )
    {
      gluBuild2DMipmaps(GL_TEXTURE_2D, 4, W, H,
          GL_BGRA_EXT, GL_UNSIGNED_BYTE, Bits);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    } /* End of 'ImgToTex' function */
    
    /* Obtain image pixel color function.
     * ARGUMENTS: 
     *   - pixel coordinates:
     *       INT X, Y;
     * RETURNS: None.
     */
    DWORD ImgGet( INT X, INT Y )
    {
      X = (X + W) % W;
      Y = (Y + H) % H;
      return Bits[Y * W + X];
    } /* End of 'ImgGet' function */
  };
}

#endif /* __IMAGE_H_ */
