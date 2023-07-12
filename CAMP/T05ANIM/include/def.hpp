/* FILE NAME: def.h
* PROGRAMMER: AD6
* LAST UPDATE: 11.07.2018
* PURPOSE
*/


#ifndef __DEF_H_
#define __DEF_H_

#include "MTH/MTH.H"

#define GLEW_STATIC

#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>


#pragma comment(lib, "glew32s")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

namespace degl
{
  template<class T>
    class mth::vec; 
  typedef mth::vec<FLT> vec;

  template<class T>
    class mth::vec2; 
  typedef mth::vec2<FLT> vec2;

  template<class T>
    class mth::vec4; 
  typedef mth::vec4<FLT> vec4;

  template<class T>
    class mth::matr; 
  typedef mth::matr<FLT> matr;

  template<class T>
    class mth::camera; 
  typedef mth::camera<FLT> camera;


  class win;

  class anim;

  class unit;

  class input;


  template<class T>
    class stock;

  class timer;

  class render;

  class prim;

  class prims;

  class shader_manager;

  class material;

  class material_manager;

  class image;

  class texture;

  class texture_manager;

  class unit_cow;
}

#pragma warning(disable: 4305 4244 4996 4101)

/* Debug memory allocation support */ 
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h> 
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy 
{ 
public: 
  /* Class constructor */
  __Dummy( VOID ) 
  { 
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __ooppss;

#endif /* _DEBUG */ 

#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

#endif

/* End of 'def.h' file */