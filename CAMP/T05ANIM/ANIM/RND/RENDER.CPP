/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME   : MATR.H
* PURPOSE     : WinAPI animation system.
*               Rendering.
* PROGRAMMER  : AD6.
* LAST UPDATE : 12.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#include "RENDER.H"

degl::render::render( HWND hWorkWnd, INT WRef = 0, INT HRef = 0 ) : hWndWork(hWorkWnd), W(WRef), H(HRef)
{
  PIXELFORMATDESCRIPTOR pfd = {0};
  INT i;
  RECT RC;
  HFONT hFnt, hOldFnt;
  
  hDC = GetDC(hWndWork);

  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(hDC, &pfd);
  DescribePixelFormat(hDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(hDC, i, &pfd);

  hGLRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hGLRC);

  if (glewInit() != GLEW_OK)
    exit(0);
  if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
    exit(0);

  glClearColor(0.3, 0.5, 0.7, 1);
  glEnable(GL_DEPTH_TEST);

  hFnt = CreateFont(47, 0, 0, 0, FW_BOLD, FALSE, FALSE,
    FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_SCRIPT, "Courier New");
  hOldFnt = (HFONT)SelectObject(hDC, hFnt);
  wglUseFontBitmaps(hDC, 0, 256, 102);
  hOldFnt = (HFONT)SelectObject(hDC, hOldFnt);
  DeleteObject(hFnt);



  GetWindowRect(hWndWork, &RC);
  MtlInit();
  ShdInit();


  W = RC.right;
  H = RC.bottom; 

 // Pr = new prim;

  Cam.ProjSet(W, H);
  //Cam.CamSet(vec(260, 500, 1032), vec(0), vec(0, 1, 0));
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

degl::render::~render( VOID )
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hGLRC);
  ReleaseDC(hWndWork, hDC);
//  delete Pr;
}

VOID degl::render::FrameStart( VOID )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


VOID degl::render::FrameEnd( VOID )
{
  glEnd();
  glFinish();
}

VOID degl::render::FrameCopy( VOID )
{
  HDC hDc;
  PAINTSTRUCT ps;

  hDc = BeginPaint(hWndWork, &ps);
  SwapBuffers(hDc);
  EndPaint(hWndWork, &ps);
  ReleaseDC(hWndWork, hDc);
}

VOID degl::render::RndResize( INT Wh, INT Hh )
{
  glViewport(0, 0, Wh, Hh);
  W = Wh;
  H = Hh;
  Cam.ProjSet(W, H);
}





VOID degl::render::PrimDraw( prims::prim *P, matr World , INT Count)
{
  INT gl_prim_type, loc, ProgId = shaders["BIN/SHADERS/DEFAULT"];
  matr WVP = P->Trans * World * Cam.GetProj(), N;
  N.Transpose((P->Trans * World).Inverse());

  ProgId = P->Mtl.MtlApply();
  glUseProgram(ProgId);


  if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, WVP.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrN")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, N.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "CamLoc")) != -1)
    glUniform3fv(loc, 1, &(Cam.GetLoc())[0]);
  if ((loc = glGetUniformLocation(ProgId, "Time")) != -1)
    glUniform1f(loc, GlobalTime);
  if ((loc = glGetUniformLocation(ProgId, "Number")) != -1)
    glUniform1i(loc, Count);
   

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);
  
  gl_prim_type = P->Type == P->MESH ? GL_TRIANGLES : GL_TRIANGLE_STRIP;

  glBindVertexArray(P->VA);
  /*if (P->IBuf == 0)
    glDrawArrays(gl_prim_type, 0, P->I.size());
  else
  { */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, P->IBuf);
    glDrawElements(gl_prim_type, P->ICount, GL_UNSIGNED_INT, NULL);
 // }
  glBindVertexArray(0);
  glUseProgram(0);
   
} /* End of 'PrimDraw' function */

VOID degl::render::PrsDraw( prims *Pr, const matr &World)
{
  INT i;
  matr M;

  M = Pr->Trans * World;
  for ( i = 0; i < Pr->Primitives.size(); i++)
  {
    PrimDraw(Pr->Primitives[i], World, i);
  }
}


 




/* End of 'render.cpp' file */