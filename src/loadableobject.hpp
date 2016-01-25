#ifndef _LOADABLEOBJECT_HPP
#define _LOADABLEOBJECT_HPP

#include <kconfig.h>

#include <string>

#include "object.hpp"

#include "textureloader.hpp"

extern KConfig *tuxSaverConf;

class LoadableObject: public Object {
public:
  LoadableObject(string name,TextureLoader *tex);
  ~LoadableObject();
  void draw();
  void make();
  void setObjectFilename(string filename);
private:
  string objectfilename;
 
  GLuint objectdsplist; //the display list for object
  TextureLoader *texture;
};

#endif //_LOADABLEOBJECT_HPP
