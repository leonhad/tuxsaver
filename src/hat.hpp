#ifndef _HAT_HPP
#define _HAT_HPP

#include <kconfig.h>

#include <string>

#include "object.hpp"
#include "textureloader.hpp"

extern KConfig *tuxSaverConf;

class Hat: public Object {
public:
  Hat(TextureLoader *tex);
  ~Hat();
  void draw();
  void make();
private:

  string hatname;
  
  string chooseRandomHat(); //set hatname on a random hat
  bool randomHat;

  GLuint hatdsplist; //the display list for hat
  TextureLoader *texture;
};

#endif //_HAT_HPP
