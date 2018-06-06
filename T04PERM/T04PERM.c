 /* FILE NAME: T04PERM
  * PROGRAMMER: AD6
  * DATE: 05.06.2018
  */

#include <stdio.h>

#include <windows.h>

/* Permutation array */
#define MAX 4
INT P[MAX], parity = 1;

/* Swap function */
VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;

  *A = *B;
  *B = tmp;
} /* End of 'Swap' function */

/* Store permutation to log file function */
VOID Store( VOID )
{
  INT i;
  FILE *F;

  F = fopen("PERM.txt", "a");
  if (F == NULL)
    return;
  
  for (i = 0; i < MAX; i++)
    fprintf(F, "%d", P[i]);
  fprintf(F, " %s permutation\n", parity == 1 ? "Even" : "Odd");
  fclose(F);
} /* End of 'Store' function */

VOID Go( INT Pos )
{
  INT i;
  if (Pos == MAX)
  {
    Store();
    return;
  }
  else 
  {
    for (i = Pos; i < MAX; i++)
    {
      Swap(&P[Pos], &P[i]);
      parity = Pos == 1 ? parity : 1 - parity;
      Go(Pos + 1);
      Swap(&P[Pos], &P[i]);
    }
  }
} /* End of 'Go' function */

/* Main program function */
VOID main( VOID )
{
  INT i;

  for (i = 0; i < MAX; i++)
    P[i] = i + 1;
  Go(0);
} /* End of main program function */

/* End of 'T04PERM.C' file */

