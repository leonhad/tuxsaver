#include "loadableobject.hpp"
#include "ac3dloader.h"

#include <qdir.h>
#include <qstrlist.h>
#include <kstddirs.h>

#include <stdlib.h>

LoadableObject::LoadableObject(string name,TextureLoader *tex): Object(name) {
#ifdef DEBUG
  cout << "constructing loadableObject ... " << endl;
#endif
  setLoadable(true);
  objectdsplist=0;
  texture=tex;
#ifdef DEBUG
  cout << "loadableObject constructed"<< endl;
#endif
}

LoadableObject::~LoadableObject()
{
  //delete displaylist
  if (objectdsplist!=0)
    glDeleteLists(objectdsplist,1);
}


void LoadableObject::setObjectFilename(string filename)
{
  objectfilename=filename;
}

void LoadableObject::make()
{
  cout << "making display list for loadable object..." << endl;
  AC3DLoader loader(texture);
  if (!loader.load(objectfilename)) {
    printf("Can't load loadable object\n");
    //return -1;
  } else {
    cout << "rendering loadable object to make display list..." << endl;
    objectdsplist = loader.getListValue();
  }
  cout << "finished making display list for loadable object" << endl;
}

void LoadableObject::draw() {

  int state = visible->state;

  if (state!=1) {
    updateMainCo();
    glPushMatrix();
 
    glTranslatef(x,y,z);
    
    glRotatef(az,0,0,1.0f);
    glRotatef(ax,1.0f,0,0);
    glRotatef(ay,0,1.0f,0);

     glPushMatrix();
     followobject->drawFollowObjects();
     glPopMatrix();
        
     glPushMatrix();
     //call display list    
     glCallList(objectdsplist);
     glPopMatrix();

    glPopMatrix();
  }
}
