/* FILE NAME: T04PERM
  * PROGRAMMER: AD6
  * DATE: 05.06.2018
  */

#include <stdio.h>

#include <windows.h>

typedef DOUBLE DBL;
#define MAX 5
DBL A[MAX][MAX], det = 0.0;
INT P[MAX], parity = 1, N = 0;

/* Swap function */
VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;

  *A = *B;
  *B = tmp;
} /* End of 'Swap' function */

BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;

  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;
  fscanf(F, "%d", &N);
  if (N < 0)
    N = 0;
  else if (N > MAX)
    N = MAX;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);
  fclose(F);
  return TRUE;
}
/* Store permutation to log file function */
VOID Store( VOID )
{
  INT i, j;
  FILE *F;

  F = fopen("PERM.txt", "a");
  if (F == NULL)
    return;
  
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
      fprintf(F, "%lf ", A[i][j]);
    fprintf(F, "\n");
  }
  fprintf(F, "%lf\n", det);
  fclose(F);
} /* End of 'Store' function */


VOID Go( INT Pos )
{
  INT i;
  if (Pos == N)
  {
    DBL prod = 1;
    for (i = 0; i < N; i++)
      prod *= A[i][P[i]];
    det += (parity * 2 - 1) * prod;
    return;
  }
  else 
  {
    for (i = Pos; i < N; i++)
    {
      Swap(&P[Pos], &P[i]);
      parity = 1 - parity;
      Go(Pos + 1);
      Swap(&P[Pos], &P[i]);
      parity = 1 - parity;
    }
  }
} /* End of 'Go' function */

/* Main program function */
VOID main( VOID )
{
  INT i;

  LoadMatrix("IN1.TXT");

  for (i = 0; i < N; i++)
    P[i] = i;
  parity = 1;
  Go(0);
  Store();
} /* End of main program function */

/* End of 'T04PERM.C' file */
