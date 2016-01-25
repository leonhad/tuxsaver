
#ifndef _ISLAND_HPP
#define _ISLAND_HPP

#include <kconfig.h>

#include "object.hpp"
#include "textureloader.hpp"

extern KConfig *tuxSaverConf;

class Island : public Object
{
public:
  Island(TextureLoader *t);
  ~Island();
  void draw();
  void make();

  TextureLoader *tex;

  GLUquadricObj *pObj;

  GLuint islanddsplist;
  string islandname;

  //island
  void drawIsland();
  bool waveIceberg;
  float islandheight; //this is the extra height caused by the waves of the sea.
} ;

#endif //_ISLAND_HPP
