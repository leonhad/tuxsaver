#ifndef _FISHINGLINE_HPP
#define _FISHINGLINE_HPP

#include "textureloader.hpp"
#include "object.hpp"

class FishingLine: public Object {
public:
  FishingLine(TextureLoader *t);
  ~FishingLine();
  void draw();
  void make();

  GLUquadricObj *pObj;

  TextureLoader *tex;
};

#endif //_FISHINGLINE_HPP
