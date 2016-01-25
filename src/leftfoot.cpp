#include "leftfoot.hpp"

Leftfoot::Leftfoot(TextureLoader *t): Object("leftfoot") {

  cout << "constructing leftfoot ... " << endl;
  tex = t;
  tex->addTexture("yellow.png");

  pObj = gluNewQuadric();
  gluQuadricTexture(pObj,true);

  make();
  cout << "leftfoot constructed"<< endl;
}

Leftfoot::~Leftfoot()
{
  delete tex;
  gluDeleteQuadric(pObj);                                // Free the Quadric
}

void Leftfoot::make()
{
    cout << "making display list for leftfoot..." << endl;
 
  leftfootdsplist=glGenLists(1);
  glNewList(leftfootdsplist,GL_COMPILE);

    //Leg 
    glTranslatef(-0.3f,1.0f,0.0f);
    glRotatef(90,1.0f,0,0);
    glTranslatef(0,0,0.2);
    tex->bindTexture("yellow.png");
    gluQuadricTexture(pObj,true);
    gluCylinder(pObj, 0.1,0.1,0.65,20,20);

    //voet omhoog
    glTranslatef(0,0,-0.5);

    //Foot

    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,-1);
    glVertex3f(0.2,0.2,1.2);
    glVertex3f(-0.2,0.2,1.2);
    glVertex3f(0.2,-0.8,1.2);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,-1);
    glVertex3f(0.2,-0.8,1.2);
    glVertex3f(-0.2,-0.8,1.2);
    glVertex3f(-0.2,0.2,1.2);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,-1);
    glVertex3f(0.2,0.2,1.05);
    glVertex3f(-0.2,0.2,1.05);
    glVertex3f(0.2,-0.8,1.05);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,-1);
    glVertex3f(0.2,-0.8,1.05);
    glVertex3f(-0.2,-0.8,1.05);
    glVertex3f(-0.2,0.2,1.05);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(1,0,0);
    glVertex3f(0.2,0.2,1.05);
    glVertex3f(0.2,0.2,1.2);
    glVertex3f(0.2,-0.8,1.2);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(1,0,0);
    glVertex3f(0.2,-0.8,1.2);
    glVertex3f(0.2,-0.8,1.05);
    glVertex3f(0.2,0.2,1.05);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(1,0,0);
    glVertex3f(-0.2,0.2,1.05);
    glVertex3f(-0.2,0.2,1.2);
    glVertex3f(-0.2,-0.8,1.2);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(1,0,0);
    glVertex3f(-0.2,-0.8,1.2);
    glVertex3f(-0.2,-0.8,1.05);
    glVertex3f(-0.2,0.2,1.05);
    glEnd();

    glTranslatef(0.0,0.2,1.05);

    //Heel
    
    gluCylinder(pObj, 0.2, 0.2, 0.15, 10, 10);
    gluQuadricOrientation(pObj,GLU_INSIDE);
    gluDisk(pObj,0,0.2,10,10);
    glTranslatef(0,0,0.15);
    gluDisk(pObj,0,0.2,10,10);
    gluQuadricOrientation(pObj,GLU_OUTSIDE);
    glTranslatef(0,0,-0.15);

    //Tones

    glTranslatef(0,-1.0,0.0);
    gluCylinder(pObj,0.1,0.1,0.15,10,10);
    gluQuadricOrientation(pObj,GLU_INSIDE);
    gluDisk(pObj,0,0.1,10,10);
    glTranslatef(0,0,0.15);
    gluDisk(pObj,0,0.1,10,10);
    gluQuadricOrientation(pObj,GLU_OUTSIDE);
    glTranslatef(0,0,-0.15);

    glTranslatef(0.1,0,0);
    gluCylinder(pObj,0.1,0.1,0.15,10,10);
    gluQuadricOrientation(pObj,GLU_INSIDE);
    gluDisk(pObj,0,0.1,10,10);
    glTranslatef(0,0,0.15);
    gluDisk(pObj,0,0.1,10,10);
    gluQuadricOrientation(pObj,GLU_OUTSIDE);
    glTranslatef(0,0,-0.15);

    glTranslatef(-0.2,0,0);
    gluCylinder(pObj,0.1,0.1,0.15,10,10);
    gluQuadricOrientation(pObj,GLU_INSIDE);
    gluDisk(pObj,0,0.1,10,10);
    glTranslatef(0,0,0.15);
    gluDisk(pObj,0,0.1,10,10);
    gluQuadricOrientation(pObj,GLU_OUTSIDE);

  glEndList();    
}  

void Leftfoot::draw() {

    glPushMatrix();
    updateMainCo();
    glTranslatef(0,0.55,0);
    glRotatef(az,0,0,1.0f);
    glRotatef(ax,1.0f,0,0);
    glRotatef(ay,0,1.0f,0);
    glTranslatef(0,-0.55,0);
    //call display list    
    glCallList(leftfootdsplist);
    
    glPopMatrix();
}

