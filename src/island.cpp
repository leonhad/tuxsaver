#include "island.hpp"
#include "ac3dloader.h"
#include <math.h>

Island::Island(TextureLoader *t) : Object("island")
{
#ifdef DEBUG
  cout << "constructing island..." << endl;
#endif
  //load textures
  tex = t;
//   tex->addTexture("snow.png");
//   tex->addTexture("snowice.png");
//   tex->addTexture("ice.png");

  pObj = gluNewQuadric();
  gluQuadricTexture(pObj,true);

  //the island is standard visible
  visible->state=0;

  //load configuration
  tuxSaverConf->setGroup("island");
  islandname = tuxSaverConf->readEntry("islandName","iceberg_with_iglo.ac").latin1();
#ifdef DEBUG
  cout << "constructing island finished" << endl;
#endif
}

Island::~Island()
{
  delete tex;
  gluDeleteQuadric(pObj);   // Free the Quadric
}

void Island::draw()
{ 
   glPushMatrix();
   if (visible->state!=1) drawIsland();
    glPushMatrix();
    followobject->drawFollowObjects();
    glPopMatrix();
   glPopMatrix();
} 

void Island::make()
{
#ifdef DEBUG
  cout << "making display list for island..." << endl;
#endif

  AC3DLoader loader(tex);
  string fullname = "islands/" + islandname;
  if (!loader.load(fullname)) {
    printf("Can't load hat\n");
    //return -1;
  } else {
     islanddsplist = loader.getListValue();
  }



//   islanddsplist=glGenLists(1);
//   glNewList(islanddsplist,GL_COMPILE);

//   //berg2
//   glPushMatrix();
//   glColor4f(1.0,1.0,1.0,0);
//   tex->bindTexture("snowice.png");
//   glTranslatef(-6.0f,5.0f,5.0f);
//   glRotatef(90, 1.0f, 0.1f, 0.0f);                // Rotate the cylinder around 90 degrees
//   gluCylinder(pObj,1.5,3,8,25,25);
//   tex->bindTexture("snow.png");
//   // gluQuadricOrientation(pObj,GLU_INSIDE);
//   glRotatef(180, 1.0f, 0.0f, 0.0f);
//   gluDisk(pObj,0,1.5,25,25);
//   // gluQuadricOrientation(pObj,GLU_OUTSIDE);
//   glPopMatrix();

//   //vlak
//   glPushMatrix();
//   glTranslatef(0,-1,0);
//   tex->bindTexture("snowice.png");
//   glTranslatef(0.0f,1.0f,0.0f);
//   glRotatef(90, 1.0f, 0.0f, 0.0f);                // Rotate the cylinder around 90 degrees
//   gluCylinder(pObj,10,10,3,40,40);
//   //gluQuadricOrientation(pObj,GLU_INSIDE);
//   glRotatef(180, 1.0f, 0.0f, 0.0f);                // Rotate the cylinder around 90 degrees
//   tex->bindTexture("snow.png");
//   gluDisk(pObj,0,10,40,40);
//   glTranslatef(0,0,-3);
//   gluDisk(pObj,0,10,40,40);
//   glPopMatrix();


//   //boebel
//   glPushMatrix();
//   tex->bindTexture("snow.png");
//   glTranslatef(3.0f,-1.0f,-6.0f);
//   gluSphere(pObj,2,18,18);
//   glPopMatrix();
  
  
//   glColor4f(1.0f,1.0f,1.0f,0.0f);
 
//   //berg
//   glPushMatrix();
//   tex->bindTexture("snowice.png");
//   glTranslatef(-4.0f,3.0f,5.0f);
//   glRotatef(110, 1.0f, 0.1f, 0.0f);                // Rotate the cylinder around 90 degrees
//   gluCylinder(pObj,1.5,3,5,22,22);
//   tex->bindTexture("snow.png");
//   // gluQuadricOrientation(pObj,GLU_INSIDE);
//   glRotatef(180, 1.0f, 0.0f, 0.0f);
//   gluDisk(pObj,0,1.5,22,22);
//   // gluQuadricOrientation(pObj,GLU_OUTSIDE);
//   glPopMatrix();

//   glEndList();   
 
}

void Island::drawIsland()
{
  int state = visible->state;

  if (state!=1) {
    updateMainCo();
    glTranslatef(x,y-0.2,z);

    glRotatef(az,0,0,1.0f);
    glRotatef(ax,1.0f,0,0);
    glRotatef(ay,0,1.0f,0);

    //call display list    
    glPushMatrix();
    glCallList(islanddsplist);
    glPopMatrix();
  }
}
