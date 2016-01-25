#include "camera.hpp"

Camera::Camera() : Object("camera")
{
  cout << "constructing camera..." << endl;
 
  //set default camera position
   move->posx = 0.0f;
   move->posy = 9.0f;
   move->posz = -38.0f;
}

Camera::~Camera()
{
}

void Camera::draw()
{
  float x=-move->posx;
  float y=-move->posy;
  float z=-move->posz;

  float ax=rotate->posx;
  float ay=rotate->posy;
  float az=rotate->posz;

  glTranslatef(0.0f,9.0f,-38.0f);

  glRotatef(ax,1.0f,0.0f,0.0f);
  glRotatef(ay,0.0f,1.0f,0.0f);
  glRotatef(az,0.0f,0.0f,1.0f);

  glTranslatef(x,y,z);
}
