/* FILE NAME: unitcow.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#include "U_FLY.H"

degl::unit_cow::unit_cow( anim *Ani )
{
  /*Cow->Load("cow.object");*/


  E45->Load("BIN/MODELS/E_45.g3dm", matr::Scale(vec(1)));
  Pos = vec(0);
  Ani->Cam.CamSet(Loc, vec(0), vec(0, 1, 0));
}
degl::unit_cow::~unit_cow( VOID )
{
  delete E45;
}

VOID degl::unit_cow::Render( anim *Ani )
{
  if (IsW)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  else
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  static CHAR Buf[100];
  glLoadIdentity();
  glColor3d(1, 1, 1);
  glRasterPos2d(-0.9, -0.85);
  glListBase(102);

  INT len =  IsFreeCam ? sprintf(Buf, "Free cam") : sprintf(Buf, "3rd person cam");
  glCallLists(len, GL_UNSIGNED_BYTE, Buf);

 /* Btr->Primitives[7]->Trans = Btr->Primitives[9]->Trans = 
      matr::Translate(vec(0.05, 0, 1.22)) *
      matr::RotateY(500 * Ani->Time) *
      matr::Translate(vec(-0.05, 0, -1.22));*/


  //Ani->PrimDraw(Cow, matr::Identity());
  glLoadMatrixf((Ani->Cam.GetProj()).A[0]);
  glBegin(GL_POLYGON);
  glColor3f(1, 0, 0);
  glVertex3f(100, 1, -100);
  glColor3f(0, 1, 0);
  glVertex3f(100, 1, 100);
  glColor3f(0, 0, 1);
  glVertex3f(-100, 1, 100);
  glColor3f(1, 1, 1);
  glVertex3f(-100, 1, -100);
  glEnd();
  Ani->PrsDraw(E45, M * T * (matr &)matr::Translate(Pos));

}
VOID degl::unit_cow::Response( anim *Ani )
{
  static FLT RotD = 0;
  static vec CameraLoc = vec(0, 47, 68);
  static vec U1(0, 1, 0);
  static vec Velocity = vec(0, 0, 0);
  if (IsFreeCam)
  {
  //Ani->Cam.CamRotY(Ani->Keys[VK_LEFT] * Ani->Time * 100);
  static FLT RotU = 0; 
  static FLT RotX = 0;
  static FLT speed = 0;
  static FLT speedR = 0;
  speed = (Ani->GlobalDeltaTime * 6 * (Ani->Keys['W'] - Ani->Keys['S'])); 
  speedR = (Ani->GlobalDeltaTime * -30 * (Ani->Keys['A'] - Ani->Keys['D'])); 
  RotX =  (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]) * Ani->GlobalDeltaTime * 60;      
  RotU =  (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT]) * Ani->GlobalDeltaTime * -60;
  //Loc += Dir * speed;
  vec Right = vec::Normalizing(Dir % vec(0, 1, 0));
  Dir = -(-Dir * matr::RotateY(RotU));
  Dir = -(-Dir * matr::Rotate(RotX, Right));
  CameraLoc += Dir * speed + Right * speedR;

  vec Pos(Dir + CameraLoc);
  Ani->Cam.CamSet(CameraLoc, Pos, vec(0, 1, 0));
  RotD += Ani->DeltaTime * -2 * RotD;
  }
  else
  { 
    static vec Poi(0, 47, 68);
    Dir = Pos - Poi;
    //Poi = Pos - Dir;
    CameraLoc = Poi;
    static FLT RotU = 0; 
    static FLT RotX = 0; 
    RotX =  Ani->JY *  60;
    RotU =  Ani->JX * -60;
    vec Right = vec::Normalizing(Dir % U1);
    static vec Acceleration = vec(Dir.Normalize()[0], 0, Dir.Normalize()[2]);

    RotD += fabs(Ani->JX) < 0.3 ? Ani->DeltaTime * -2 * RotD  : -60 * Ani->JX * Ani->DeltaTime;

    if (!Ani->IsPause && fabs(RotD) > fabs(45 * Ani->JX) && fabs(Ani->JX) > 0.1)
      RotD = -45 * Ani->JX;

    Pos += vec(0, 50 * Ani->DeltaTime * (Ani->JBut[1] - Ani->JBut[2]), 0);
    //Acceleration = Acceleration * matr::Rotate(RotX, Right);
    //Velocity = Velocity.VecTrans(matr::RotateY(RotD * Ani->DeltaTime));
    Dir = Dir.VecTrans(matr::RotateY(-RotD * Ani->DeltaTime ));
    //Acceleration = vec(Dir[0], 0, Dir[2]);
    Acceleration = Acceleration.VecTrans(matr::RotateY(RotD * Ani->DeltaTime));
    Velocity += Ani->JBut[0] == 1 || Ani->JBut[3] == 1 ? Acceleration * Ani->DeltaTime * 2 * (Ani->JBut[0] - Ani->JBut[3]) :
      Velocity.Length2() < 1 ? vec(0) : -Acceleration * Ani->DeltaTime;
    Velocity[1] = 0;
    Pos += Velocity * Ani->DeltaTime + (Acceleration * Ani->DeltaTime * Ani->DeltaTime) / 2;
    //U1 = U1.VecTrans(matr::Rotate(-RotX, Right));
    Poi = Pos - Dir;
    Acceleration = vec(Dir[0], 0, Dir[2]);
    Ani->Cam.CamSet(Poi, Pos, U1);
    CameraLoc = Poi;
    T = T * matr::RotateY(RotD * Ani->DeltaTime);
  }
  M = matr::RotateZ(RotD/*, vec(Dir.Normalize()[0], 2, Dir.Normalize()[0])*/);
  if (Ani->KeysClick[VK_F4])
    IsW = 1 - IsW;
  else if (Ani->KeysClick[VK_F1])
    IsFreeCam = 1;
  else if (Ani->KeysClick[VK_F2])
    IsFreeCam = 0;
  else if (Ani->KeysClick[VK_SPACE] || Ani->JButClick[5])
    Ani->IsPause = 1 - Ani->IsPause;

}