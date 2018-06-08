 /* FILE NAME: T08ANIM
  * PROGRAMMER: AD6
  * DATE: 07.06.2018
  */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define PI       3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian (a) D2R(a)

typedef double DBL;

typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

typedef struct tagMATR
{
  DBL M[4][4];
} MATR;

static MATR UnitMatrix = 
{
  {
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0}
  }
};

/* Vector set function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       DBL X, Y, Z;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v = {X, Y, Z};
  return v;
} /* End of 'VecSet' function */

/* Vector addition function.
 * ARGUMENTS:
 *   - vectors :
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* Vector substraction function.
 * ARGUMENTS:
 *   - vectors :
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* End of 'VecSubVec' function */

/* Vector multiplication number function.
 * ARGUMENTS:
 *   - vector :
 *       VEC V1;
 *   - number:
         DBL N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulNum( VEC V1, DBL N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
} /* End of 'VecMulNum' function */

/* Vector division number function.
 * ARGUMENTS:
 *   - vector :
 *       VEC V1;
 *   - number:
         DBL N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecDivNum( VEC V1, DBL N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
} /* End of 'VecMulNum' function */

/* Vector negation function.
 * ARGUMENTS:
 *   - vector :
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
} /* End of 'VecNeg' function */

/* Vectors dot production function.
 * ARGUMENTS:
 *   - vectors :
 *       VEC V1, V2;
 * RETURNS:
 *   (DBL) dot production.
 */
__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} /* End of 'VecDotVec' function */

/* Vectors cross production function.
 * ARGUMENTS:
 *   - vectors :
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X- V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
} /* End of 'VecDotVec' function */

/* Vector square length function.
 * ARGUMENTS:
 *   - vector :
 *       VEC V;
 * RETURNS:
 *   (DBL) length.
 */
__inline DBL VecLen2( VEC V )
{
  return VecDotVec(V, V); 
} /* End of 'VecLen2' function */

/* Vector length function.
 * ARGUMENTS:
 *   - vector :
 *       VEC V;
 * RETURNS:
 *   (DBL) length.
 */
__inline DBL VecLen( VEC V )
{
  return sqrt(VecLen2(V));
} /* End of 'VecLen' function */

/* Vector normalize function.
 * ARGUMENTS:
 *   - vector :
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNormalize( VEC V )
{
  DBL len = VecDotVec(V, V);

  if (len == 0 || len == 1)
    return V;
  return VecDivNum(V, sqrt(len));
} /* End of 'VecNormalize' function */

/* Point transform function.
 * ARGUMENTS:
 *   - vector :
 *       VEC V;
 *   - transform matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(M.M[0][0] * V.X + M.M[0][1] * V.Y + M.M[0][2] * V.Z + M.M[0][3], 
                M.M[1][0] * V.X + M.M[1][1] * V.Y + M.M[1][2] * V.Z + M.M[1][3],
                M.M[2][0] * V.X + M.M[2][1] * V.Y + M.M[2][2] * V.Z + M.M[2][3]);
} /* End of 'PointTransform' function */

/* Vector transform function.
 * ARGUMENTS:
 *   - vector :
 *       VEC V;
 *   - transform matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(M.M[0][0] * V.X + M.M[0][1] * V.Y + M.M[0][2] * V.Z, 
                M.M[1][0] * V.X + M.M[1][1] * V.Y + M.M[1][2] * V.Z,
                M.M[2][0] * V.X + M.M[2][1] * V.Y + M.M[2][2] * V.Z);
} /* End of 'VectorTransform' function */

/* Matrix identity function.
 * ARGUMENTS: NONE
 * RETURNS:
 *   (VEC) Unit matrix.
 */
__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
} /* End of 'MatrIdentity' function */

/* Make translate matrix function.
 * ARGUMENTS:
 *   - vector :
 *       VEC V;
 *   - transform matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;

  m.M[3][0] = T.X;
  m.M[3][1] = T.Y;
  m.M[3][2] = T.Z;
  return m;
}

__inline MATR MatrScale( VEC S )
{
  MATR m = UnitMatrix;

  m.M[0][0] = S.X;
  m.M[1][1] = S.Y;
  m.M[2][2] = S.Z;
  return m;
}

__inline MATR MatrRotateX( DBL AngleInDegree )
{
  DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  
  MATR M =
  {
    {
      {1, 0, 0, 0},
      {0, co, si, 0},
      {0, -si, co, 0},
      {0, 0, 0, 1}
    }
  };

  return M;
}

__inline MATR MatrRotateY( DBL AngleInDegree )
{
  DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  
  MATR M =
  {
    {
      {co, 0, -si, 0},
      {0, 1, 0, 0},
      {si, 0, co, 0},
      {0, 0, 0, 1}
    }
  };

  return M;
}

__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  
  MATR M =
  {
    {
      {co, si, 0, 0},
      {-si, co, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    }
  };

  return M;
}

__inline MATR MatrRotate( DBL AngleInDegree, VEC R )
{
  DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  VEC V = VecNormalize(R);

  MATR M =
  {
    {
      {co + V.X * V.X * (1 - co), V.X * V.Y * (1 - co) + V.Z * si, V.X * V.Z * (1 - co) - V.Y * si, 0},
      {V.Y * V.X * (1 - co) - V.Z * si, co + V.Y * V.Y * (1 - co), V.Y * V.Z * (1 - co) + V.X * si, 0},
      {V.Z * V.X * (1 - co) + V.Y * si, V.Z * V.Y * (1 - co) - V.X * si, co + V.Z * V.Z * (1 - co), 0},
      {0, 0, 0, 1}
    }
  };

  return M;
}

__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r;
  INT i, j, k;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.M[i][j] = 0, k = 0; k < 4; k++)
        r.M[i][j] += M1.M[i][k] * M2.M[k][j];
  return r;
}

__inline MATR MatrTranspose( MATR M )
{
  INT i, j;
  MATR M1;

  for(i = 0; i < 4; i++)
    for(j = 0; j < 4;j++)
      M1.M[j][i] = M.M[i][j];
  return M1;
}

__inline DBL MatrDeterm3x3( DBL M11, DBL M12, DBL M13,
                   DBL M21, DBL M22, DBL M23,
                   DBL M31, DBL M32, DBL M33 )
{
  return M11 * M22 * M33 - M11 * M23 * M32 - M12 * M21 * M33 + 
         M12 * M23 * M31 + M13 * M21 * M32 - M13 * M22 * M31;
}

__inline DBL MatrDeterm( MATR M )
{
  return
    M.M[0][0] * MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                              M.M[2][1], M.M[2][2], M.M[2][3],
                              M.M[3][1], M.M[3][2], M.M[3][3]) -
    M.M[0][1] * MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                              M.M[2][0], M.M[2][2], M.M[2][3],
                              M.M[3][0], M.M[3][2], M.M[3][3]) +
    M.M[0][2] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                              M.M[2][0], M.M[2][1], M.M[2][3],
                              M.M[3][0], M.M[3][1], M.M[3][3]) -
    M.M[0][3] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                              M.M[2][0], M.M[2][1], M.M[2][2],
                              M.M[3][0], M.M[3][1], M.M[3][2]);
}
__inline MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);
  
  if (det == 0)
    return UnitMatrix; 

  r.M[0][0] =
    MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[2][1], M.M[2][2], M.M[2][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[2][0], M.M[2][2], M.M[2][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][0] =
    MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[2][0], M.M[2][1], M.M[2][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[2][0], M.M[2][1], M.M[2][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]);
  r.M[0][1] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                   M.M[2][1], M.M[2][2], M.M[2][3],
                   M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][1] =
    MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                  M.M[2][0], M.M[2][2], M.M[2][3],
                  M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][1] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                   M.M[2][0], M.M[2][1], M.M[2][3],
                   M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][1] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                  M.M[2][0], M.M[2][1], M.M[2][2],
                  M.M[3][0], M.M[3][1], M.M[3][2]);
  r.M[0][2] =
    MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][2] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                  M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]);
  r.M[0][3] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                   M.M[1][1], M.M[1][2], M.M[1][3],
                   M.M[2][1], M.M[2][2], M.M[2][3]); 
  r.M[1][3] =
    MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                  M.M[1][0], M.M[1][2], M.M[1][3],
                  M.M[2][0], M.M[2][2], M.M[2][3]);
  r.M[2][3] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                   M.M[1][0], M.M[1][1], M.M[1][3],
                   M.M[2][0], M.M[2][1], M.M[2][3]);
  r.M[3][3] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                  M.M[1][0], M.M[1][1], M.M[1][2],
                  M.M[2][0], M.M[2][1], M.M[2][2]);

  r.M[0][0] /= det;
  r.M[1][0] /= det;
  r.M[2][0] /= det;
  r.M[3][0] /= det;
  r.M[0][1] /= det;
  r.M[1][1] /= det;
  r.M[2][1] /= det;
  r.M[3][1] /= det;
  r.M[0][2] /= det;
  r.M[1][2] /= det;
  r.M[2][2] /= det;
  r.M[3][2] /= det;
  r.M[0][3] /= det;
  r.M[1][3] /= det;
  r.M[2][3] /= det;
  r.M[3][3] /= det;

  return r;
}

__inline MATR MatrView( VEC At, VEC Loc, VEC Up1 )
{
  VEC 
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));

  MATR m = 
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), -VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
}

__inline MATR MatrViewFrustum( DBL r, DBL l, DBL t, DBL b, DBL f, DBL n )
{
  MATR m = 
  {
    {
      {2 * n / (r - l), 0, 0, 0},
      {0, 2 * n / (t - b), 0, 0},
      {(r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1},
      {0, 0, -2 * n * f / (f - n), 0}
    }
  };

  return m;
}

__inline VEC VecMulMatr4x4( VEC V, MATR M )
{
   DBL w = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3];

   return VecSet((M.M[0][0] * V.X + M.M[0][1] * V.Y + M.M[0][2] * V.Z) / w, 
                (M.M[1][0] * V.X + M.M[1][1] * V.Y + M.M[1][2] * V.Z) / w,
                (M.M[2][0] * V.X + M.M[2][1] * V.Y + M.M[2][2] * V.Z) / w);
}

__inline MATR MatrResult( MATR T, MATR V, MATR VFM )
{ 
  return MatrMulMatr(MatrMulMatr(T, V), VFM);
}
