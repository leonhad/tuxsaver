#ifndef _ARM_HPP
#define _ARM_HPP

#include "textureloader.hpp"

class arm {
public:
  int right;  //0=right 1=left arm
  arm(TextureLoader *t,int side=0);
  ~arm();
  void draw();
  void move(GLfloat x, GLfloat y, GLfloat z);
  void rotate(GLfloat anglex, GLfloat angley, GLfloat anglez);
  void move_tip(GLfloat tipx, GLfloat tipy, GLfloat tipz);
  GLfloat posx,posy,posz,tipx,tipy,tipz; //position
  GLfloat ax,ay,az; //angle

  TextureLoader *tex;

};

#endif //_ARM_HPP
