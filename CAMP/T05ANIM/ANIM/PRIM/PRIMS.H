/* FILE NAME: prims.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#ifndef __PRIMS_H_
#define __PRIMS_H_

#include "PRIM.H"



namespace degl
{
  class prims : public prim
  {
  public:
    std::vector<prim *> Primitives;  // Primitives array
    matr Trans;                     // Allprimitives transformation matrix
    
    ~prims( VOID );

    prims( VOID );

    /* Load primitives from 'G3DM' file function.
    * ARGUMENTS:
    *   - file name:
    *       const std::string &FileName;
    *   - transformation matrix:
    *       const matr &Transform;
    * RETURNS:
    *   (BOOL) TRUE if success, FALSE otherwise.
    */
    BOOL Load( const std::string &FileName, const matr &Transform );
  };
}

#endif /* __PRIMS_H_ */