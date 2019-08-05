/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : PRIM.H
* PURPOSE     : Ray tracing.
*               Shapes.
*               Primitive.
* PROGRAMMER  : AD6.
* LAST UPDATE : 23.08.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __PRIM_H_
#define __PRIM_H_

#include "TRIAN.H"
#include "BOX.H"

namespace dert
{
  class prim : public shape
  {
  private:
    box BoundBox;
  public:  
    std::vector<triangle *> Tr; 

    // Default constructor
    prim( VOID )
    {
    }
  
    /* Primitive constructor function.
     * ARGUMENTS:
     *   - filename to load from:
     *       std::string &FileName;
     *   - reference to material type:
     *       material &Mt;
     *   - reference to environment type:
     *       environment &Env;
     * RETURNS: None.
     */
    prim( const std::string &FileName, const material &Mt, const environment &Env );


    /* Load primitive from "*.OBJ" file function.
     * ARGUMENTS:
     *   - filename to load from:
     *       std::string &FileName;
     * RETURNS:
     *  (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL LoadObj( const std::string &FileName );

    /* Find intersection with primitive function.
     * ARGUMENTS: 
     *   - reference to ray to find intersection with:
     *        ray &R;
     *   - pointer to intersection type:
     *        intr *Intr;
     * RETURNS:
     *       (BOOL) TRUE if there is a intersection, FALSE otherwise.
     */
    BOOL Intersect( const ray &R, intr *Intr ) override;

    /* Find all intersections with primitive function.
     * ARGUMENTS: 
     *   - reference to ray to find intersections with:
     *        ray &R;
     *   - pointer to intersections type:
     *        intr_list *IList;
     * RETURNS:
     *       (INT) Amount of intersections.
     */
    INT AllIntersect( const ray &R, intr_list *IList ) override;

    /* Normal evaluation function
     * ARGUMENTS:
     *   - pointer to intersection type:
     *        intr *Intr;
     * RETURNS: None.
     */
    VOID EvalNormal( intr *Intr ) override;

    ~prim( VOID );
  };
} /* End of 'dert' namespace */
#endif /* __PRIM_H_ */

/* End of 'PRIM.H' file */