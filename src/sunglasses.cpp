#include "sunglasses.hpp"
#include "config.h"

Sunglasses::Sunglasses(TextureLoader *t): Object("sunglasses") {
#ifdef DEBUG
  cout << "constructing sunglasses ... " << endl;
#endif
  tex = t;
  tex->addTexture("redhat.png");

  pObj = gluNewQuadric();
  gluQuadricTexture(pObj,true);

  make();
#ifdef DEBUG
  cout << "sunglasses constructed"<< endl;
#endif
}

Sunglasses::~Sunglasses()
{
  delete tex;

  gluDeleteQuadric(pObj);                                // Free the Quadric
}

void Sunglasses::make()
{
#ifdef DEBUG
  cout << "making display list for sunglasses..." << endl;
#endif
  sunglassesdsplist=glGenLists(1);
  glNewList(sunglassesdsplist,GL_COMPILE);

  tex->bindTexture("redhat.png");      
  glColor4f(0.0f,0.0f,0.8f,0.9f);
  glDisable(GL_LIGHTING);
  glEnable(GL_BLEND);
  //leftsideglass
  glTranslatef(-0.2,0,0);
  gluDisk(pObj,0,0.16,20,20);
  gluDisk(pObj,0.15,0.17,20,20);
  //rightsideglass
  glTranslatef(0.4,0,0);
  gluDisk(pObj,0,0.16,20,20);
  gluDisk(pObj,0.15,0.17,20,20);
  glDisable(GL_BLEND);
  glEnable(GL_LIGHTING);
  //middle
  glTranslatef(-0.2,0.02,0);
  glBegin(GL_QUADS);
  glVertex3f(-0.05,0.05,0);
  glVertex3f(-0.05,0,0);
  glVertex3f(0.05,0.05,0);
  glVertex3f(0.05,0,0);
  glEnd();
  glTranslatef(0.2,0,0);
  //leftside
  glTranslatef(0.2,0,0);
  glBegin(GL_QUADS);
  glVertex3f(0,0.05,-0.02);
  glVertex3f(0,0.0,-0.02);
  glVertex3f(0.4,0.05,0.5);
  glVertex3f(0.4,0.0,0.5);
  glEnd();
  //rightside
  glTranslatef(-0.8,0,0);
  glBegin(GL_QUADS);
  glVertex3f(0,-0.05,-0.02);
  glVertex3f(0,0.0,-0.02);
  glVertex3f(-0.4,0.05,0.5);
  glVertex3f(-0.4,0.0,0.5);
  glEnd();

  glColor4f(1.0f,1.0f,1.0f,0.5f);
  glEndList();    
  
}

void Sunglasses::draw() {

  int state = visible->state;

  if (state!=1) {
    updateMainCo();
    glPushMatrix();
    glTranslatef(x,y,z);
 
    glRotatef(az,0,0,1.0f);
    glRotatef(ax,1.0f,0,0);
    glRotatef(ay,0,1.0f,0);
     
    //call display list    
    glCallList(sunglassesdsplist);
    
    glPopMatrix();
  }
}

