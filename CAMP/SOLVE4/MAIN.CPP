#include <iostream>
#include <conio.h>
#include "SOLVE4.H"

using namespace std;

int main( void )
{
  double
    A, B, C, D, E, Roots[4];

  cout << "Input a coefficients:\n";
  cin >> A >> B >> C >> D >> E;

  int num = Solve4(Roots, A, B, C, D, E);

  for (int i = 0; i < num; i++)
    cout << "x" << i << " = " << Roots[i] << endl;

  cout << "Num:" << num;
  _getch();
  return 30;
}

/* End of 'MAIN.CPP' file */