
#ifndef TUXSAVER_H
#define TUXSAVER_H

#include <qgl.h>
#include <qptrlist.h>
#include <qimage.h>
#include <qstring.h>
#include <qevent.h>
#include <qdatetime.h>

#include <kconfig.h>

#include "init.hpp"
#include "world.hpp"
#include "island.hpp"
#include "fishingline.hpp"
#include "hat.hpp"
#include "camera.hpp"
#include "penguin.hpp"
#include "sunglasses.hpp"
#include "EventServer.hpp"
#include "textureloader.hpp"

using namespace std;

class TuxSaver : public QGLWidget
{
 public:
  TuxSaver( QWidget *parent=0, const char *name=0 );
  ~TuxSaver();
  void timerEvent( QTimerEvent * );
  QTime t; //how long this story is running
  QTime totalTime; //how long the screensaver is running
  
  World *myWorld;
  Island *myIsland;
  Camera *myCamera;
  Hat *myHat;
  FishingLine *myFishingLine;
  penguin *myPenguin;
  Sunglasses *mySunglasses;

  TextureLoader *tex;
  GLuint texturememory[40];

protected:
  void initializeGL();
  void resizeGL( int, int );
  void paintGL();
  void draw();

  bool blankScreen;
  float blankScreenTime; //time when to blank the screen in secondes
};

#endif
