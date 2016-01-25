#ifndef _BODY_HPP
#define _BODY_HPP

#include "textureloader.hpp"

class body {
public:
  body(TextureLoader *t);
  ~body();
  void draw();
  void drawMouth();
  void move(GLfloat,GLfloat,GLfloat);
  void rotate(GLfloat,GLfloat,GLfloat);
  void open_mouth(GLfloat); //dist= opening of the bek
  void move_mouth(GLfloat,GLfloat,GLfloat);
  void rotate_kop(GLfloat,GLfloat,GLfloat);

  GLfloat posx,posy,posz,open,mouthx,mouthy,mouthz; //position
  GLfloat ax,ay,az,kopx,kopz,kopy; //angle
  GLUquadricObj *pObj;
  TextureLoader *tex;

  void make();
  GLuint bodydsplist; //the display list for body
};

#endif //_BODY_HPP
