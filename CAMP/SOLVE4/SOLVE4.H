#include <cmath>


typedef float FLT;
typedef double DBL;
typedef int INT;


/* Solve equation of the fourth degree function.
 * ARGUMENTS:
 *    - pointer to roots array:
 *        DBL *Roots;
 *    - Equation coefficients:
 *        DBL A, B, C, D, E;
 * RETURNS:
 *   (INT) amount of real roots.
 */
INT Solve4( DBL *Roots, DBL A, DBL B, DBL C, DBL D, DBL E );

/* Solve equation of the third degree function (static).
 * ARGUMENTS:
 *    - pointer to roots array:
 *        DBL *Roots;
 *    - Equation coefficients:
 *        DBL A, B, C, D;
 * RETURNS:
 *   (INT) amount of real roots.
 */
INT Solve3( DBL *Roots, DBL A, DBL B, DBL C, DBL D );

/* Solve equation of the second degree function (static).
 * ARGUMENTS:
 *    - pointer to roots array:
 *        DBL *Roots;
 *    - Equation coefficients:
 *        DBL A, B, C;
 * RETURNS:
 *   (INT) amount of real roots.
 */
INT Solve2( DBL *Roots, DBL A, DBL B, DBL C );

template <class T>
  T power(T A, INT n)
  {
    if (n == 0)
      return (T)1;
    return A * power(A, n - 1);
  }

template <class T>
  T operator$(T A, INT n)
  {
    return power(A, n);
  }

template<typename T>
  void Swap( T &A, T &B )
  {
    T tmp = A;
    A = B;
    B = tmp;
  }

const DBL PI = 3.14159265358979323846;


/* End of 'SOLVE4.H' file */