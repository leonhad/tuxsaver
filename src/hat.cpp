#include "hat.hpp"
#include "ac3dloader.h"
#include "config.h"

#include <qdir.h>
#include <qstrlist.h>
#include <kstddirs.h>

#include <time.h>
#include <stdlib.h>


Hat::Hat(TextureLoader *tex): Object("hat") {
#ifdef DEBUG
  cout << "constructing hat ... " << endl;
#endif

  //load configuration
  tuxSaverConf->setGroup("hat");
  if (tuxSaverConf->readEntry("randomHat","yes")=="yes") randomHat=true; else randomHat=false;
  hatname = tuxSaverConf->readEntry("hatName","christmashat.ac").latin1();
  
  // if randomHat is enabled we overwrite the hatname;
  if (randomHat) hatname=chooseRandomHat();

  texture=tex;
#ifdef DEBUG
  cout << "hat constructed"<< endl;
#endif
}

Hat::~Hat()
{
}

void Hat::make()
{
  /*
  cout << "making display list for hat..." << endl;
  hatdsplist=glGenLists(1);
  glNewList(hatdsplist,GL_COMPILE);

  tex->bindTexture("redhat.png");      
  glTranslatef(0,0.15,0);
  glRotatef(90,1.0,0,0);
  gluDisk(pObj,0.7,1.5,30,30);
  gluCylinder(pObj,1.5,1.5,0.15,30,30);;
  glTranslatef(0,0,0.15);
  gluDisk(pObj,0,1.5,30,30);
  glTranslatef(0,0,-0.5);
  gluDisk(pObj,0,0.7,30,30);
  tex->bindTexture("redyellowhat.png");
  gluCylinder(pObj,0.7,0.7,0.5,30,30);

  glEndList();
  */
  AC3DLoader loader(texture);
  string fullhatname = "hats/"+hatname;
  if (!loader.load(fullhatname)) {
    printf("Can't load hat\n");
    //return -1;
  } else {
     hatdsplist = loader.getListValue();
  }
}

void Hat::draw() {

  int state = visible->state;

  if (state!=1) {
    updateMainCo();
    glPushMatrix();
 
    glTranslatef(x,y,z);
    
    glRotatef(az,0,0,1.0f);
    glRotatef(ax,1.0f,0,0);
    glRotatef(ay,0,1.0f,0);
        
    glPushMatrix();
    //call display list    
    glCallList(hatdsplist);
    
    glPopMatrix();
    glPopMatrix();
  }
}

string Hat::chooseRandomHat()
{
  QDir hatdir;
  hatdir.setPath(locate("data","tuxsaver/objects/hats/"));
  QStringList hatlist=hatdir.entryList(QDir::Files);
  
  srand( (unsigned int) time( NULL ));

  float ranf= (float(rand()))/(float(RAND_MAX));
  ranf = ranf*(hatlist.count());  
  int ran= int(ranf);
  cout << "hat choosen randomly: " << ran << " " << *hatlist.at(ran) << endl; 
  return (*hatlist.at(ran)).latin1();
}
