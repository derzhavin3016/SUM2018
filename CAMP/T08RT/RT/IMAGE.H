/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : IMAGE.H
* PURPOSE     : Ray tracing.
*               Image creating class.
* PROGRAMMER  : AD6.
* LAST UPDATE : 25.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include "../DEF.H"

namespace dert
{
  class image
  {
  private:
    INT W, H;     // Image size
    DWORD *Bits;
    BITMAPINFOHEADER bmih;
    HBITMAP hBm;
    HDC hMemDC;
  public:

   /* Converting color from 3 components to DWORD
    * ARGUMENTS: 
    *   - 3 components (0-255)(Red, Green, Blue):
    *        BYTE R, G, B;
    * RETURNS: 
    *        (DWORD) Color.
    */
    static DWORD Rgb( BYTE R, BYTE G, BYTE B );

   /* Converting color from DWORD to 3 components
    * ARGUMENTS: 
    *   - Red, Green, Blue in hexadecimal:
    *        DWORD Color;
    * RETURNS: 
    *        (vec) result color.
    */
    static vec ToRgb( DWORD Color );

   /* Converting color from 3 float components to DWORD
    * ARGUMENTS: 
    *   - 3 components (0-1)(Red, Green, Blue):
    *        T R, G, B;
    * RETURNS: 
    *        (DWORD) Color.
    */
    static DWORD ToDWORD( FLT R, FLT G, FLT B );

   /* Converting color from 3 float components to DWORD
    * ARGUMENTS:
    *   - referernce 3 components vector (0-1)(Red, Green, Blue):
    *        vec &rgb;
    * RETURNS:
    *        (DWORD) Color.
    */
    static DWORD ToDWORD( const vec &rgb );

   /* Image resize function
    * ARGUMENTS: 
    *   - new width and height:
    *        INT newW, newH;
    * RETURNS: None.
    */
    VOID Resize( INT newW, INT newH );

   /* Load image from .bmp file function
    * ARGUMENTS:
    *   - name of .bmp file to load:
    *        std::string &FileName;
    * RETURNS:
    *   (BOOL) TRUE if success, FALSE otherwise.
    */
    BOOL Load( const std::string &FileName );
   
    /* Image save to *.bmp file function
    * ARGUMENTS: None.
    * RETURNS:
    *     (BOOL) TRUE if success, FALSE otherwise.
    */
    BOOL SaveBMP( VOID );

   /* Image draw function
    * ARGUMENTS:
    *   - device context:
    *        HDC hDC;
    *   - draw position ((0, 0) default):
    *        INT Dx, Dy;
    * RETURNS: None.
    */
    VOID Draw( HDC hDC, INT Dx = 0, INT Dy = 0 );

   /* Put pixel to image function
    * ARGUMENTS: 
    *   - screen coordinates:
    *        INT X, Y;
    *   - color to put:
    *        DWORD Color;
    * RETURNS: None.
    */
    VOID PutPixel( INT X, INT Y, DWORD Color );

   /* Get pixel from image function
    * ARGUMENTS: 
    *   - screen coordinates:
    *        INT X, Y;
    * RETURNS:
    *        (DWORD) pixel color;
    */
    DWORD GetPixel( INT X, INT Y );

    /* Get image width function
     * ARGUMENTS: None.
     * RETURNS:
     *        (INT) image width;
     */
    INT GetWidth( VOID );

    /* Get image height function
     * ARGUMENTS: None.
     * RETURNS:
     *        (INT) image height;
     */
    INT GetHeight( VOID );

    // Default constructor
    image( VOID );

    // Desrtuctor
    ~image( VOID );
  };
} /* End of 'dert' namespace */

#endif /* __IMAGE_H_ */

/* End of 'IMAGE.H' file */