#ifndef _SUNGLASSES_HPP
#define _SUNGLASSES_HPP

#include "textureloader.hpp"
#include "object.hpp"

class Sunglasses: public Object {
public:
  Sunglasses(TextureLoader *t);
  ~Sunglasses();
  void draw();
  void make();

  TextureLoader *tex;

  GLuint sunglassesdsplist; //the display list for hat
  GLUquadricObj *pObj;
};

#endif //_SUNGLASSES_HPP
