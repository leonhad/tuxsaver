
#ifndef _WORLD_HPP
#define _WORLD_HPP

#include <kconfig.h>

#include "object.hpp"
#include "textureloader.hpp"
#include "island.hpp"

extern KConfig *tuxSaverConf;

class World : public Object
{
public:
  World(TextureLoader *t);
  ~World();
  void draw();
  void make();

  TextureLoader *tex;

  GLUquadricObj *pObj;

  GLuint skydsplist;
  GLuint staticseadsplist; //display list for the non-moving sea

  bool waveIceberg;
  float islandheight; //this is the extra height caused by the waves of the sea.

  //island
  void setIsland(Island* the_island);
  void drawIsland();
  Island* island;
  //sky
  void drawSky();
  //sea
  void drawSea(float waveheight,float wavetime);
  bool waveSea;
  bool seaTransparancy;
  int seaTransparancyLevel;  //number between 0 and 99 which specifies the transparancy of the sea. O is no transparancy.
  float points[45][45][3];   // the array for the points on the grid of our "wave"
  float latestwavetime; //time when the latest wave passed by
  float waveHeight; //height of the waves
};

#endif //_WORLD_HPP
