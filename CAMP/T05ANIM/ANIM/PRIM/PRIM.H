/* FILE NAME: prim.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#ifndef __PRIM_H_
#define __PRIM_H_

#include "../RND/RES/MATERIALS.H"
#include "../TIMER/TIMER.H"

namespace degl
{
  class VERTEX
  {
  public:
    degl::vec P;
    degl::vec N;
    degl::vec2 T;
    degl::vec4 C;

    VERTEX( degl::vec Pos ) : P(Pos)
    {

    }

    VERTEX( VOID )
    {
    
    }
  };

  class prim : public material_manager, public VERTEX
  {
  public:
    friend class render;
    enum prim_type
    {
      POINT, LINE, LINESTRIP, MESH, STRIP
    } Type;

    degl::matr Trans;
    //stock<VERTEX> vertex;
   material Mtl;

    UINT VA, VBuf, IBuf, VertexCount, MtlNo, ICount;
    
    //prim( topology &Topo );
    VOID create( const prim_type &T, const std::vector<VERTEX> &V, const std::vector<INT> &I );

    BOOL Load( const CHAR *FileName );

    prim( const prim_type &T, const std::vector<VERTEX> &V, const std::vector<INT> &I );

    prim( VOID ) : VA(0), VBuf(0), IBuf(0)  
    {
    
    }

    ~prim( VOID );


  };

 /* class shader
  {
  public:
    INT ProgId;
  };

  class texture
  {
  public:
    INT TexNo;
  };

  class material
  {
  public:
    INT MtlNo;
    vec Ka, Kd, Ks;
    FLT Ph, Trans;
    shader *Shd;
    texture *Tex[8];
  }; */

}

#endif
