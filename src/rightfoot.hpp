#ifndef _RIGHTFOOT_HPP
#define _RIGHTFOOT_HPP

#include "textureloader.hpp"
#include "object.hpp"

class Rightfoot: public Object {
public:
  Rightfoot(TextureLoader *t);
  ~Rightfoot();
  void draw();
  void make();

  TextureLoader *tex;
  Move *Walk;

  GLuint rightfootdsplist; //the display list for rightfoot
  GLUquadricObj *pObj;
};

#endif //_RIGHTFOOT_HPP
