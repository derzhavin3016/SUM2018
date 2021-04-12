/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : DEF.H
* PURPOSE     : Ray tracing.
*               Definitions file.
* PROGRAMMER  : AD6.
* LAST UPDATE : 24.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/


#ifndef __DEF_H_
#define __DEF_H_

#include "MTH/MTH.H"


#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>


namespace dert
{
  template<class T>
    class mth::vec; 

  template<class T>
    class mth::vec2; 

  template<class T>
    class mth::vec4; 

  template<class T>
    class mth::matr; 

  template<class T>
    class mth::camera;

  template<class T>
    class mth::ray;

  typedef mth::vec<DBL> vec;
  typedef mth::vec2<DBL> vec2;
  typedef mth::vec4<DBL> vec4;
  typedef mth::matr<DBL> matr;
  typedef mth::camera<DBL> camera;
  typedef mth::ray<DBL> ray;

  class win;

  class frame;

  class shape;

  class sphere;

  class box;

  class triangle;

  class quad;

  class torus;

  class intr;

  typedef std::vector<intr> intr_list;

  class image;

  class shape_list;

  class shade_data;

  class material;

  class environment;

  class plane;

  class base_light;

  class spot_light;

  class base_mods;

  class sphere_tex_mods;

  class cylin_tex_mods;

  class point_mods;

  class prim;

  const DBL Threshold = 0.0001;
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

#endif /* __DEF_H_ */

/* End of 'def.h' file */