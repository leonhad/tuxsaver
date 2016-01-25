#include "fishingline.hpp"
#include "config.h"

FishingLine::FishingLine(TextureLoader *t) : Object("fishingline") {

  cout << "constructing FishingLine ..." << endl;
  tex = t;
  tex->addTexture("redhat.png");

  pObj = gluNewQuadric();
  cout << "constructing FishingLine finished" << endl;
}

FishingLine::~FishingLine()
{
  delete tex;
  gluDeleteQuadric(pObj);                                // Free the Quadric
}

void FishingLine::draw() {

    if (state!=1){
      tex->bindTexture("redhat.png");
      gluQuadricTexture(pObj,true);
      glTranslatef(x,y,z);
      glRotatef(90,1.0,0,0);
    
      glRotatef(az,0,0,1.0f);
      glRotatef(ax,1.0f,0,0);
      glRotatef(ay,0,1.0f,0);

      glTranslatef(0,-5,-9);
      glRotatef(-30,1,0,0);
      gluCylinder(pObj,0.04,0.15,7,10,10);
      glRotatef(30,1,0,0);


      glRotatef(-ay,0,1.0f,0);
      glRotatef(-ax,1.0,0,0);
      glRotatef(-az,0,0,1.0f);
      gluCylinder(pObj,0.04,0.04,7,10,10);
      glTranslatef(0,0,7);
      gluSphere(pObj,0.3,10,10);
    }
}

void FishingLine::make() {
}
