

#include <iostream>
#include <conio.h>

int CountDig( int N )
{
  int i(0);
  while (N != 0)
  {
    N /= 10;
    i++;
  }

  return i;
}

int main( void )
{
  int N, maxspc;

  std::cout << "Input N:" << std::endl;
  std::cin >> N;

  maxspc = CountDig(N * N);

  for (int i = 1; i <= N; i++)
  {
    for (int j = 1; j <= N; j++)
    {
      std::cout.left;
      std::cout << i * j;
      for (int z = 0; z < maxspc - CountDig(i * j) + 1; z++)
        std::cout << " ";
    }
    std::cout << std::endl;
  }
  _getch();
}