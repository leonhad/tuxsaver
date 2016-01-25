#include "arm.hpp"

arm::arm(TextureLoader *t, int side) {
  cout << "constructing arm ..." << endl;
  tex = t;
  tex->addTexture("arm.png");
  posx=0;
  posy=0;
  posz=0;
  tipx=0;
  tipy=0;
  tipz=0;
  ax=0;
  ay=0;
  az=0;
  right=side;
  cout << "constructing arm finished" << endl;
}

arm::~arm()
{
  delete tex;
}

void arm::move(GLfloat x, GLfloat y, GLfloat z) {
  posx=x;
  posy=y;
  posz=z;
}

void arm::rotate(GLfloat x, GLfloat y, GLfloat z) {
  ax=x;
  ay=y;
  az=z;
}

void arm::move_tip(GLfloat tx, GLfloat ty, GLfloat tz) {
  tipx=tx;
  tipy=ty;
  tipz=tz;
}
void arm::draw() {
  
  tex->bindTexture("arm.png");

  glTranslatef(0,3.8,0);
  glRotatef(90, 1.0f, 0.0f, 0.0f);

  if (right==0) {
    glBegin(GL_TRIANGLES);
    glVertex3f(0.79,0,1);
    glVertex3f(0.96,0,2.2);
    glVertex3f(1.5+tipx,0.2-tipz,3-tipy);
    glEnd();
  }
  else {
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.79,0,1);
    glVertex3f(-0.96,0,2.2);
    glVertex3f(-1.5-tipx,-tipz+0.2,3-tipy);
    glEnd();
  } 
}

