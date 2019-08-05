/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME  : INTR.H
* PURPOSE     : Ray tracing.
*               Intersect info class.
* PROGRAMMER  : AD6.
* LAST UPDATE : 25.07.2018.
* NOTE        : None.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __INTR_H_
#define __INTR_H_

#include "../DEF.H"

namespace dert
{
  class intr
  {
  public:
    shape *Shp;     // Object pointer
    DBL T;          // Ray param
    BOOL IsEnter;   // Entering flag
    vec N;          // Normal
    BOOL IsN;       // Normal evaluation flag
    vec P;          // Position
    BOOL IsP;       // Position evaluation flag
    // Addon param  
    INT I[5];
    DBL D[5];
    vec V[5];

    // Default constructor
    intr( VOID );

    intr &operator=( const intr &Intr );

    // Copy constructor by reference
    intr( const intr &Intr );

    VOID SetIntr( const intr &Intr );

    // Copy constructor by pointer
    intr( intr *Intr );

    /* Constructor function.
     * ARGUMENTS: 
     *   - object pointer:
     *         shape *Shp;
     *   - Ray parameter:
     *          DBL T;
     *   - Is enter flag:
     *          BOOL IsEnter(TRUE default);
     * RETURNS: None.
     */
    intr( shape *Shp, DBL T, BOOL IsEnter = TRUE );

    /* Constructor function.
     * ARGUMENTS: 
     *   - object pointer:
     *         shape *Shp;
     *   - Ray parameter:
     *          DBL T;
     *   - Is enter flag:
     *          BOOL IsEnter;
     *   - reference to normal:
     *          vec &Norm;
     * RETURNS: None.
     */
    intr( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm );

    /* Constructor function.
     * ARGUMENTS: 
     *   - object pointer:
     *         shape *Shp;
     *   - Ray parameter:
     *          DBL T;
     *   - Is enter flag:
     *          BOOL IsEnter;
     *   - reference to normal:
     *          vec &Norm;
     *   - reference to position:
     *          vec &Pos;
     * RETURNS: None.
     */
    intr( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm, const vec &Pos );

    /* Intersect set function.
     * ARGUMENTS: 
     *   - object pointer:
     *         shape *Shp;
     *   - Ray parameter:
     *          DBL T;
     *   - Is enter flag:
     *          BOOL IsEnter(TRUE default);
     * RETURNS: None.
     */
    VOID SetIntr( shape *Shp, DBL T, BOOL IsEnter = TRUE );

    /* Intersect set function.
     * ARGUMENTS: 
     *   - object pointer:
     *         shape *Shp;
     *   - Ray parameter:
     *          DBL T;
     *   - Is enter flag:
     *          BOOL IsEnter;
     *   - reference to normal:
     *          vec &Norm;
     * RETURNS: None.
     */
    VOID SetIntr( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm );

    /* Intersect set function.
     * ARGUMENTS: 
     *   - object pointer:
     *         shape *Shp;
     *   - Ray parameter:
     *          DBL T;
     *   - Is enter flag:
     *          BOOL IsEnter;
     *   - reference to normal:
     *          vec &Norm;
     *   - reference to position:
     *          vec &Pos;
     * RETURNS: None.
     */
    VOID SetIntr( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm, const vec &Pos );
  };
} /* End of 'dert' namespace */



#endif /* __INTR_H_ */

/* End of 'INTR.H' file */
