#ifndef _PENGUIN_HPP
#define _PENGUIN_HPP

/*
hpp voor tux
*/

#include "body.hpp"
#include "arm.hpp"
#include "rightfoot.hpp"
#include "leftfoot.hpp"
#include "Walk.hpp"
#include "Jump.hpp"
#include "Openmouth.hpp"

#include "object.hpp"

class penguin: public Object {
public:
  penguin(TextureLoader *t);
  ~penguin();
  void draw();

  void move_wings(GLfloat tx,GLfloat ty,GLfloat tz);
  void open_mouth(GLfloat dist);
  void move_mouth(GLfloat,GLfloat,GLfloat);
  void rot_leftf(GLfloat,GLfloat,GLfloat);

  body *myBody;
  Leftfoot *myleftFoot;
  Rightfoot *myrightFoot;
  arm *myleftArm;
  arm *myrightArm;
  GLUquadricObj *pObj;

  Move *rotatekop;
  Move *rotateleftfoot;
  Move *rotaterightfoot;
  Move *moveleftarm;
  Move *moverightarm;
  Move *movemouth;
  Jump *jumpit;
  Openmouth *openmouth;
  
  GLuint bodydsplist; //the display list for body

  Walk *walkpenguin;

  void make();
};

#endif //_PENGUIN_HPP
