/* Derzhavin Andrey, 11-6, 08.07.2018 */

struct A
{
  static A hi;
protected:
  A( void )
  {
  
  }
};

#include "WND/Win.h"
int main( void )
{

  win MyWindow;
 // A  t;

  MyWindow.Run();
  return 30;
}

/* End of 'MAIN.C' file */