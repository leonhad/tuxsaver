#include <qgl.h>
#include <kconfig.h>
#include <kaudioplayer.h>
#include <math.h>
#include <kstddirs.h>
#include <klocale.h>
#include <qdatetime.h>
#include <qmessagebox.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>

#include "tuxsaver.hpp"

EventServer *myEventServer; // Master Event object
KConfig *tuxSaverConf; // global configuration object

TuxSaver :: TuxSaver( QWidget *parent, const char *name )
  : QGLWidget( parent, name )
{
#ifdef DEBUG
  cout << "constructing tuxsaver..." << endl;
#endif

  tex=new TextureLoader();

  //  start timers
  t.start();
  totalTime.start();  
  startTimer( 10 );

  //create global configuration object
  tuxSaverConf = new KConfig("tuxsaverrc",false,true,"config");

  //load some config options
  tuxSaverConf->setGroup("tuxsaver");
  if (tuxSaverConf->readEntry("blankScreen","no")=="yes") blankScreen=true; else blankScreen=false;
  blankScreenTime = (tuxSaverConf->readEntry("blankScreenTime","30").toFloat())*60000;

  //create other evenserver and other objects
  myEventServer = new EventServer(tex);
  myCamera = new Camera();
  myWorld = new World(tex);
  myIsland = new Island(tex);
  myWorld->setIsland(myIsland);
  myFishingLine = new FishingLine(tex);
  myPenguin = new penguin(tex);
  myHat = new Hat(tex);
  mySunglasses = new Sunglasses(tex);

#ifdef DEBUG
  cout << "adding clients..." << endl;
#endif
  myEventServer->addClient(myCamera);
  myEventServer->addClient(myWorld);
  
  myEventServer->addClient(myIsland);
  myEventServer->addClient(myPenguin);
  myEventServer->addClient(myHat);
  myEventServer->addClient(myFishingLine);
  myEventServer->addClient(mySunglasses);


#ifdef DEBUG
  cout << "ended constructing tuxsaver" << endl;
#endif
}

TuxSaver::~TuxSaver()
{
  delete myEventServer;
  delete myCamera;
  delete myHat;
  delete myFishingLine;
  delete myPenguin;
}

void TuxSaver :: initializeGL()
{
#ifdef DEBUG
  cout << "initialize OpenGL" << endl;
#endif

  glShadeModel( GL_SMOOTH );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
  glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glEnable( GL_TEXTURE_2D );
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //  glBlendFunc(GL_SRC_ALPHA, GL_ONE);        
  glColor4f(1.0f,1.0f,1.0f,0.5f);
  glDisable(GL_BLEND);
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);                       // type of depth test to do.
  glEnable(GL_DEPTH_TEST);                    // enables depth testing.


  glClearColor(1, 1, 1, 1);                      
  
  float ambience[4] = {0.2f, 0.2f, 0.2f, 1.0};   
  float diffuse[4] = {1.0f, 1.0f, 1.0f, 1.0};    
  float g_LightPosition[4] = {25, 20, 10, 1};
  
  glLightfv( GL_LIGHT0, GL_AMBIENT,  ambience );       // Set our ambience values (Default color without direct light)
  glLightfv( GL_LIGHT0, GL_DIFFUSE,  diffuse );        // Set our diffuse color (The light color)
  
  glLightfv( GL_LIGHT0, GL_POSITION, g_LightPosition );    // This Sets our light position
  
  glEnable(  GL_LIGHT0   );                                // Turn this light on
  
  glEnable(  GL_LIGHTING );                                // This turns on lighting
  
  glEnable(GL_COLOR_MATERIAL);                             // Allow color to show during lighting

  //generate display lists
  //apperently this has to be done during initializeGL
  tex->generateTextures();

  cout << "making all subclients" << endl;
  myEventServer->makeAllSubClients();
  cout << "finished making all subclients" << endl;

  tex->loadTextureList();

  myEventServer->loadStoryList("storylist");
  myEventServer->loadNewStory();
}


void TuxSaver :: resizeGL( int width, int height )
{
#ifdef DEBUG
  cout << "resize GL" << endl;
#endif
  GLfloat w = (float) width / (float) height;
  GLfloat h = 1.0;
  
  glViewport( 0, 0, width, height );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum( -w, w, -h, h, 5.0, 150.0 );
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void TuxSaver::timerEvent(QTimerEvent*)
{
  updateGL();
}

void TuxSaver::paintGL()
{
  if (blankScreen && totalTime.elapsed()>blankScreenTime)
    {
      //here we just paint a black surface
      glClearColor(0,0,0,1);                      
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
  else
    {
      //if somebody reseted the worldtime, make sure that we reset the timer too
      if (worldtime==0) {
	t.restart();
	worldtime=0.02; //to make sure that it doesn't keep resetting it
	prevworldtime=0;
      } else {
	prevworldtime=worldtime;
	worldtime=float(t.elapsed())/1000;
#ifdef DEBUG
	cout << "framerate:" << 1/(worldtime-prevworldtime) << endl;
#endif
      }
#ifdef DEBUG
      cout <<"worldtime: " << worldtime << endl;
#endif
      myEventServer->execute();
      draw();
    }
}

void TuxSaver::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(0,9,-38, 0,0,0, 0,0,1);

  myCamera->draw();

  myWorld->draw();
}
