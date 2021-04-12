/* FILE NAME: unit_cow.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/



#include "../ANIM/ANIM.H"

class unit_cow : public degl::unit
{
public:
  degl::vec Pos;
  degl::prim *Pr;

  unit_cow( VOID );
  ~unit_cow( VOID );

  VOID Render( degl::anim *Ani );
  VOID Response( degl::anim *Ani );
};



/* End of 'unit_cow.h' file */