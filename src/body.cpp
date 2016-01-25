
/*
ccp-file for tux
*/

#include "body.hpp"

body::body(TextureLoader *t) {
  cout << "constructing body ... " << endl; 
  //load texture files
  tex = t;
  tex->addTexture("head.png");
  tex->addTexture("body.png");
  tex->addTexture("subbody.png");
  tex->addTexture("yellow.png");
  open=0;
  kopz=0;
  kopy=0;
  kopx=0;
  mouthx=0;
  mouthy=0;
  mouthz=0;
  pObj = gluNewQuadric();
  cout << "constructing body finished" << endl;
  }

body::~body()
{
  delete tex;
  gluDeleteQuadric(pObj);                                // Free the Quadric
}

void body::rotate_kop(GLfloat angx,GLfloat angy,GLfloat angz) {
  kopz=angz;
  kopy=angy;
  kopx=angx;
}

void body::open_mouth(GLfloat dist) {
  open=dist/2;
}

void body::move_mouth(GLfloat x,GLfloat y,GLfloat z){
  mouthx=x;
  mouthy=y;
  mouthz=z;
}

void body::draw() {
  //call display list
}

void body::drawMouth()
{
  //MOUTH UPPER
  tex->bindTexture("yellow.png");
  glTranslatef(0.0f,2.8f,0.0f);
  glRotatef(90,1.0f,0.0f,0.0f);

  glBegin (GL_TRIANGLES); 
  glNormal3f( 0.0f, 0.0f, -1.0f); 
  glVertex3f(-0.5, -0.7, 0.2);     
  glVertex3f(0.5, -0.7, 0.2);      
  glVertex3f(mouthx,mouthy-1.3,mouthz+0.2-open);   
  glEnd();
  
  glBegin (GL_TRIANGLES);
  glNormal3f( -0.4f, 0.0f, -1.0f); 
  glVertex3f(-0.5, -0.7, 0.2);    
  glVertex3f(0, -0.7, -0.3);        
  glVertex3f(mouthx,mouthy-1.3,mouthz+0.2-open);   
  glEnd();
  
  glBegin (GL_TRIANGLES);
  glNormal3f( 0.4f, 0.0f, -1.0f); 
  glVertex3f(0, -0.7, -0.3);
  glVertex3f(0.5, -0.7, 0.2);
  glVertex3f(mouthx,mouthy-1.3,mouthz+0.2-open);
  glEnd();

  //MOUTH LOWER
  glBegin (GL_TRIANGLES); 
  glNormal3f( 0.0f, 0.0f, -1.0f); 
  glVertex3f(-0.5, -0.7, 0.2);     
  glVertex3f(0.5, -0.7, 0.2);      
  glVertex3f(mouthx,mouthy-1.3,mouthz+0.2+open);   
  glEnd();
  
  glBegin (GL_TRIANGLES);
  glNormal3f( -1.0f, 0.0f, -1.0f); 
  glVertex3f(-0.5, -0.7, 0.2);    
  glVertex3f(0, -0.7, 0.5);                        
  glVertex3f(mouthx,mouthy-1.3,mouthz+0.2+open);   
  glEnd();
  
  glBegin (GL_TRIANGLES);
  glNormal3f( 1.0f, 0.5f, -1.0f); 
  glVertex3f(0,-0.7, 0.5);                         
  glVertex3f(0.5, -0.7, 0.2);                      
  glVertex3f(mouthx,mouthy-1.3,mouthz+0.2+open);   
  glEnd();  
}

void body::make()
{
  cout << "making display list for body..." << endl;

  bodydsplist=glGenLists(1);
  glNewList(bodydsplist,GL_COMPILE);

    gluQuadricTexture(pObj,true);

    glTranslatef(0,3.8f,0);

    glRotatef(90, 1.0f, 0.0f, 0.0f);
   
    //MOUTH UPPER
    glTranslatef(0.0f,0.0f,1.0f);

//     tex->bindTexture("yellow.png");


//     glBegin (GL_TRIANGLES); 
//     glNormal3f( 0.0f, 0.0f, -1.0f); 
//     glVertex3f(-0.5, -0.7, 0.2);     
//     glVertex3f(0.5, -0.7, 0.2);      
//     glVertex3f(mouthx,mouthy-1.3,mouthz+0.2-open);   
//     glEnd();

//     glBegin (GL_TRIANGLES);
//     glNormal3f( -0.4f, 0.0f, -1.0f); 
//     glVertex3f(-0.5, -0.7, 0.2);    
//     glVertex3f(0, -0.7, -0.3);        
//     glVertex3f(mouthx,mouthy-1.3,mouthz+0.2-open);   
//     glEnd();

//     glBegin (GL_TRIANGLES);
//     glNormal3f( 0.4f, 0.0f, -1.0f); 
//     glVertex3f(0, -0.7, -0.3);                          // Here is the top point of the triangle
//     glVertex3f(0.5, -0.7, 0.2);                      // Here is the left point of the triangle
//     glVertex3f(mouthx,mouthy-1.3,mouthz+0.2-open);                   // Here is the right point of the triangle
//     glEnd();
//     //MOUTH LOWER
//     glBegin (GL_TRIANGLES); 
//     glNormal3f( 0.0f, 0.0f, -1.0f); 
//     glVertex3f(-0.5, -0.7, 0.2);     
//     glVertex3f(0.5, -0.7, 0.2);      
//     glVertex3f(mouthx,mouthy-1.3,mouthz+0.2+open);   
//     glEnd();

//     glBegin (GL_TRIANGLES);
//     glNormal3f( 0.0f, 0.0f, -1.0f); 
//     glVertex3f(-0.5, -0.7, 0.2);    
//     glVertex3f(0, -0.7, 0.5);                          // Here is the left point of the triangle
//     glVertex3f(mouthx,mouthy-1.3,mouthz+0.2+open);                  // Here is the right point of the triangle
//     glEnd();

//     glBegin (GL_TRIANGLES);
//     glNormal3f( 0.0f, 0.0f, -1.0f); 
//     glVertex3f(0,-0.7, 0.5);                          // Here is the top point of the triangle
//     glVertex3f(0.5, -0.7, 0.2);                      // Here is the left point of the triangle
//     glVertex3f(mouthx,mouthy-1.3,mouthz+0.2+open);                   // Here is the right point of the triangle
//     glEnd();

   //UPSIDE 
    tex->bindTexture("head.png");
    gluSphere(pObj, 0.8f, 20, 20);

    //MIDDLE
    tex->bindTexture("body.png");
    gluQuadricDrawStyle(pObj, GL_FILL);     // Draw the cylinder in lines
    gluCylinder(pObj, 0.8, 0.97, 1.2, 50, 50);   // Draw our cylinder

    //DOWNSIDE
    glTranslatef(0,0,1.4);
    tex->bindTexture("subbody.png");    
    gluSphere(pObj, 1.0f, 50, 50);   
    glTranslatef(0,0,-2.4f);
     
     //arm
    tex->bindTexture("yellow.png");
    glBegin(GL_TRIANGLES);
    glVertex3f(0.79,0,1);
    glVertex3f(0.96,0,2.2);
    glVertex3f(-0.79,0,1);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(-0.79,0,1);
    glVertex3f(-0.96,0,2.2);
    glVertex3f(0.96,0,2.2);
    glEnd();
    
    //foot
    tex->bindTexture("yellow.png");        
    glBegin(GL_TRIANGLES);
    glVertex3f(0.3,0,2.7);
    glVertex3f(0.3,0,3);
    glVertex3f(-0.3,0,3);
    glEnd();
   
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.3,0,2.7);
    glVertex3f(-0.3,0,3);
    glVertex3f(0.3,0,3);
    glEnd();  

  glEndList();  
}
