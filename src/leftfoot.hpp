#ifndef _LEFTFOOT_HPP
#define _LEFTFOOT_HPP

#include "textureloader.hpp"
#include "object.hpp"

class Leftfoot: public Object {
public:
  Leftfoot(TextureLoader *t);
  ~Leftfoot();
  void draw();
  void make();


  TextureLoader *tex;
  Move *walk;

  GLuint leftfootdsplist; //the display list for leftfoot
  GLUquadricObj *pObj;
};

#endif //_LEFTFOOT_HPP
