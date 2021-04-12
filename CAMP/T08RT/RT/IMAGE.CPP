/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : IMAGE.CPP
* PURPOSE     : Ray tracing.
*               Image creating class.
*               Functions realization.
* PROGRAMMER  : AD6.
* LAST UPDATE : 25.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "IMAGE.H"

/* Converting color from 3 components to DWORD
 * ARGUMENTS:
 *   - 3 components (0-255)(Red, Green, Blue):
 *        BYTE R, G, B;
 * RETURNS:
 *        (DWORD) Color.
 */
DWORD dert::image::Rgb( BYTE R, BYTE G, BYTE B )
{
  return ((DWORD)R << 16) | ((DWORD)G << 8) | (DWORD)B;
} /* End of 'Rgb' function */

/* Converting color from DWORD to 3 components
 * ARGUMENTS: 
 *   - Red, Green, Blue in hexadecimal:
 *        DWORD Color;
 * RETURNS: 
 *        (vec) result color.
 */
dert::vec dert::image::ToRgb( DWORD Color )
{
  return vec((Color >> 16) & 0xFF, (Color >> 8) & 0xFF,
             Color & 0xFF) / 255;
}

/* Converting color from 3 float components to DWORD
 * ARGUMENTS:
 *   - 3 components (0-1)(Red, Green, Blue):
 *        T R, G, B;
 * RETURNS:
 *        (DWORD) Color.
 */
DWORD dert::image::ToDWORD( FLT R, FLT G, FLT B )
{
  return Rgb(R * 255, G * 255, B * 255);
} /* End of 'ToDWORD' function */

/* Converting color from 3 float components to DWORD
 * ARGUMENTS:
 *   - referernce 3 components vector (0-1)(Red, Green, Blue):
 *        vec &rgb;
 * RETURNS:
 *        (DWORD) Color.
 */
DWORD dert::image::ToDWORD( const vec &rgb )
{
  return Rgb(rgb[0] * 255, rgb[1] * 255, rgb[2] * 255);
} /* End of 'ToDWORD' function */

/* Image resize function
 * ARGUMENTS:
 *   - new width and height:
 *        INT newW, newH;
 * RETURNS: None.
 */
VOID dert::image::Resize( INT newW, INT newH )
{
  W = newW;
  H = newH;
  bmih.biSize = sizeof(BITMAPINFOHEADER);
  bmih.biBitCount = 32;
  bmih.biPlanes = 1;
  bmih.biCompression = BI_RGB;
  bmih.biWidth = W;
  bmih.biHeight = -H;
  bmih.biSizeImage = W * H * 4;
  bmih.biClrUsed = 0;
  bmih.biClrImportant = 0;
  bmih.biXPelsPerMeter = bmih.biYPelsPerMeter = 0;

  hBm = CreateDIBSection(NULL, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, (VOID **)&Bits, NULL, 0);
  ///hBm = (HBITMAP)LoadImage(NULL, "BIN/TEXTURES/sky.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
} /* End of 'Resize' function */

/* Load image from .bmp file function
 * ARGUMENTS:
 *   - name of .bmp file to load:
 *        std::string &FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL dert::image::Load( const std::string &FileName )
{
  INT i;
  HBITMAP hBmFile;
  BITMAP bm;
  bmih = {0};
  // Addon handle
  HDC hMemDC1;

  if ((hBmFile = (HBITMAP)LoadImage(NULL, FileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)) == NULL)
    return FALSE;

  GetObject(hBmFile, sizeof(BITMAP), &bm);

  bmih.biSize = sizeof(BITMAPINFOHEADER);
  bmih.biPlanes = 1;
  bmih.biCompression = BI_RGB; /* No compression */
  bmih.biBitCount = 32;
  bmih.biWidth = W = bm.bmWidth;
  bmih.biHeight = H = bm.bmHeight; /* if negative - up-bottom order */
  bmih.biSizeImage = W * H * 4;
  bmih.biClrUsed = 0;
  bmih.biClrImportant = 0;
  bmih.biXPelsPerMeter = bmih.biYPelsPerMeter = 0;


  hBm = CreateDIBSection(NULL, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, (VOID **)&Bits, NULL, 0);

  hMemDC1 = CreateCompatibleDC(GetDC(NULL));
  SelectObject(hMemDC1, hBmFile);
  hMemDC = CreateCompatibleDC(GetDC(NULL));
  SelectObject(hMemDC, hBm);
  BitBlt(hMemDC, 0, 0, W, H, hMemDC1, 0, 0, SRCCOPY);
  

  DeleteDC(hMemDC1);
  DeleteObject(hBmFile);

  return TRUE;
} /* End of 'Load' function */

/* Image save to *.bmp file function
 * ARGUMENTS: None.
 * RETURNS:
 *     (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL dert::image::SaveBMP( VOID )
{
  BITMAPFILEHEADER bfh;
  UINT bpl = (W * 3 + 3) / 4 * 4;
  FILE *F;
  SYSTEMTIME st;

  bfh.bfType = 'B' | ('M' << 8);
  bfh.bfSize = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + bpl * H;
  bfh.bfReserved1 = 0;
  bfh.bfReserved2 = 0;
  bfh.bfOffBits = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

  bmih.biSize = sizeof(BITMAPINFOHEADER);
  bmih.biBitCount = 24;
  bmih.biPlanes = 1;
  bmih.biCompression = BI_RGB;
  bmih.biWidth = W;
  bmih.biHeight = H;
  bmih.biSizeImage = bpl * H;
  bmih.biClrUsed = 0;
  bmih.biClrImportant = 0;
  bmih.biXPelsPerMeter = bmih.biYPelsPerMeter = 0;

  GetLocalTime(&st);

  static CHAR Buf[1000];

  sprintf(Buf, "BIN/IMAGES/BMP/RT-%d_%02d_%02d~~%02d_%02d_%02d.bmp", st.wYear, st.wMonth,
           st.wDay, st.wHour, st.wMinute, st.wSecond);

  if ((F = fopen(Buf, "wb")) == NULL)
    return FALSE;


  fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, F);
  fwrite(&bmih, sizeof(BITMAPINFOHEADER), 1, F);

  BYTE *row = new BYTE[bpl];

  for (INT y = H - 1; y >= 0; y--)
  {
    for (INT x = 0; x < W; x++)
    {
      row[x * 3 + 0] = Bits[y * W + x] & 0xFF;
      row[x * 3 + 1] = (Bits[y * W + x] >> 8) & 0xFF;
      row[x * 3 + 2] = (Bits[y * W + x] >> 16) & 0xFF;
    }
    fwrite(row, 1, bpl, F);
  }
  delete[] row;
  fclose(F);
  return TRUE;
} /* End of 'SaveBMP' function */

/* Image draw function
 * ARGUMENTS:
 *   - device context:
 *        HDC hDC;
 *   - draw position ((0, 0) default):
 *        INT Dx, Dy;
 * RETURNS: None.
 */
VOID dert::image::Draw( HDC hDC, INT Dx, INT Dy )
{
  hMemDC = CreateCompatibleDC(hDC);
  SelectObject(hMemDC, hBm);
  BitBlt(hDC, 0, 0, W, H, hMemDC, Dx, Dy, SRCCOPY);
  //StretchBlt(hDC, 0, 0, W, H, hMemDC, Dx, Dy, W, H, SRCCOPY);
}

/* Put pixel to image function
 * ARGUMENTS:
 *   - screen coordinates:
 *        INT X, Y;
 *   - color to put:
 *        DWORD Color;
 * RETURNS: None.
 */
VOID dert::image::PutPixel( INT X, INT Y, DWORD Color )
{
  Bits[Y * W + X] = Color;
} /* End of 'PutPixel' function */

/* Get pixel from image function
 * ARGUMENTS:
 *   - screen coordinates:
 *        INT X, Y;
 * RETURNS:
 *        (DWORD) pixel color;
 */
DWORD dert::image::GetPixel( INT X, INT Y )
{
  X = (X + W) % W;
  Y = (Y + H) % H;
  X = X >= 0 ? X : -X;
  Y = Y >= 0 ? Y : -Y;
  return Bits[Y * W + X];
} /* End of 'GetPixel' function */

/* Get image width function
 * ARGUMENTS: None.
 * RETURNS:
 *        (INT) image width;
 */
INT dert::image::GetWidth( VOID )
{
  return W;
} /* End of 'GetWidth' function */

/* Get image height function
 * ARGUMENTS: None.
 * RETURNS:
 *        (INT) image height;
 */
INT dert::image::GetHeight( VOID )
{
  return H;
} /* End of 'GetHeight' function */

// Default constructor
dert::image::image( VOID )
{
  memset(&bmih, 0, sizeof(bmih));
  memset(this, 0, sizeof(image));
}

// Desrtuctor
dert::image::~image( VOID )
{
  // Delete objects
  DeleteObject(hBm);
  DeleteDC(hMemDC);
}

/* End of 'IMAGE.CPP' file */