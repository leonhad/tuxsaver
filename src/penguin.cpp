#include <iostream>

#include "penguin.hpp"

penguin::penguin(TextureLoader *t) : Object("penguin") 
{
  myBody = new body(t);
  myleftFoot = new Leftfoot(t);
  myrightFoot = new Rightfoot(t);
  myleftArm = new arm(t,1);
  myrightArm = new arm(t,0);
  pObj = gluNewQuadric();

  rotatekop = new Move();
  rotatekop->setName("rkop");
  addCommando(rotatekop);

  rotaterightfoot = myrightFoot->rotate;
  rotaterightfoot->setName("rightfoot");
  addCommando(rotaterightfoot);

  rotateleftfoot = myleftFoot->rotate;
  rotateleftfoot->setName("leftfoot");
  addCommando(rotateleftfoot);

  moveleftarm = new Move();
  moveleftarm->setName("leftarm");
  addCommando(moveleftarm);

  moverightarm  = new Move();
  moverightarm->setName("rightarm");
  addCommando(moverightarm);

  movemouth  = new Move();
  movemouth->setName("movemouth");
  addCommando(movemouth);

  openmouth = new Openmouth();
  openmouth->setName("openmouth");
  addCommando(openmouth);
  
  walkpenguin = new Walk(move,rotate,rotateleftfoot,rotaterightfoot);
  walkpenguin->setName("walk");
  addCommando(walkpenguin);

  jumpit = new Jump(move,rotaterightfoot,rotateleftfoot,moverightarm,moveleftarm);
  jumpit->setName("jump");
  addCommando(jumpit);

  //cout << "constructing penguin finished" << endl;
}
penguin::~penguin()
{
  delete myBody;
  delete myleftFoot;
  delete myrightFoot;
  delete myleftArm;
  delete myrightArm;

  delete rotaterightfoot;
  delete rotateleftfoot;
  delete moveleftarm;
  delete moverightarm;
  delete movemouth;
  delete walkpenguin;
  delete openmouth;

  gluDeleteQuadric(pObj);                                // Free the Quadric
}

void penguin::move_wings(GLfloat tx,GLfloat ty,GLfloat tz) {
  myleftArm->move_tip(tx,ty,-tz+4.6);
  myrightArm->move_tip(tx,ty,-tz+4.6);
}


void penguin::open_mouth(GLfloat dist) {
  myBody->open_mouth(dist);
}

void penguin::move_mouth(GLfloat x,GLfloat y,GLfloat z){
  myBody->move_mouth(x,y,z);
}

void penguin::draw()
{ 
    updateMainCo();
    // Not used
    //GLfloat kopx = rotatekop->resulx;
    //GLfloat kopy = rotatekop->resuly;
    //GLfloat kopz = rotatekop->resulz;

    GLfloat rightarmx = moverightarm->resulx;
    GLfloat rightarmy = moverightarm->resuly;
    GLfloat rightarmz = moverightarm->resulz;

    GLfloat leftarmx = moveleftarm->resulx;
    GLfloat leftarmy = moveleftarm->resuly;
    GLfloat leftarmz = moveleftarm->resulz;

    //TODO: this is wrong
    // Not used
    //GLfloat mouthx = moveleftarm->resulx;
    //GLfloat mouthy = moveleftarm->resuly;
    //GLfloat mouthz = moveleftarm->resulz;

    //TODO: clean this up, the drawfunction should use the openmouth variable
    // openmouth should be a part of body
    // clean up how hierarchy of penguin !!!
    myBody->open=openmouth->open;

    int state = visible->state;
    if (state!=1){

      myleftArm->move_tip(leftarmx,leftarmy,leftarmz);
      myrightArm->move_tip(rightarmx,rightarmy,rightarmz);

//       myleftFoot->rotatewalk(leftfax,leftfay,leftfaz);
//       myrightFoot->rotatewalk(rightfax,rightfaz,rightfay);

      
      glPushMatrix();
      glTranslatef(x,y,z);

      glRotatef(az,0,0,1.0f);
      glRotatef(ax,1.0f,0,0);
      glRotatef(ay,0,1.0f,0);

      glPushMatrix();
      glCallList(myBody->bodydsplist);
      glPopMatrix();

           //TODO: move this code to body to clean up hierachy
           glPushMatrix();
	   myBody->drawMouth();
	   glPopMatrix();
           
           glPushMatrix();
	   myleftFoot->draw();
	   glPopMatrix();

           glPushMatrix();
	   myrightFoot->draw();
	   glPopMatrix();

	   glPushMatrix();
	   myleftArm->draw();
	   glPopMatrix();

	   glPushMatrix();
	   myrightArm->draw();
	   glPopMatrix();

      followobject->drawFollowObjects();

      glPopMatrix();


      //Other
      //myBody->open_bek(openbek);
    }
}

void penguin::make()
{
  myBody->make();
  myleftFoot->make();
  myrightFoot->make();
}
