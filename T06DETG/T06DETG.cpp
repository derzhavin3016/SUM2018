/* FILE NAME: T04PERM
  * PROGRAMMER: AD6
  * DATE: 05.06.2018
  */

#include <stdio.h>
#include <math.h>
#include <windows.h>

typedef DOUBLE DBL;
#define MAX 5
DBL A[MAX][MAX], det = 1.0;
INT P[MAX], parity = 1, N = 0;

/* Swap function */
VOID Swap( DBL *A, DBL *B )
{
  DBL tmp = *A;

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

DBL Detg1( VOID )
{
  INT i, j, z, x, y, p, t;
  DBL koef, det = 1.0, k;
  for (i = 0; i < N; i++)
    for (j = i + 1; j < N; j++)
      for (z = i; z < N; z++)
      {
        if (A[i][i] == 0)
        {
          k = 0;
          for (x = 0; x < N; x++)
            for (y = 0; y < N; y++)
            {
              if (fabs(k) < fabs(A[x][y]))
              {
                k = A[x][y];
                p = x;
                t = y;
              }
            }

              if (k == 0)
                return 0;


              if (p != i)
              {
                for (x = 0; x < N; x++)
                    Swap(&A[p][x], &A[i][x]);
                det = -det;
              }

              if (t != i)
              {
                for (x = 0; x < N; x++)
                    Swap(&A[x][t], &A[x][i]);
                det = -det;
              }
        }
        koef = A[j][i] / A[i][i];
        A[j][z] -= A[i][z] * koef;
      }
  for (x = 0; x < N; x++)
    det *= A[x][x];
  return det;
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
  fprintf(F, "%lf\n", Detg1());
  fclose(F);
} /* End of 'Store' function */

INT Detg( VOID )
{
  INT i, j, z;
  DBL k;
  for (i = 0; i < N; i++)
    for (j = i + 1; j < N; j++)
      for (z = i; z < N; z++)
      {
        if (A[i][i] == 0)
          return 0;
        else
        k = A[j][i] / A[i][i];
        A[j][z] -= A[i][z] * k;
      }
  return 1;
}

/* Main program function */
VOID main( VOID )
{
  LoadMatrix("IN1.TXT");
  Store();
} /* End of main program function */

/* End of 'T04PERM.C' file */
