#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <qimage.h>
#include <qgl.h>

#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define NUMBEROFTEX 40

class TextureLoader
{
public:
  TextureLoader();
  ~TextureLoader();

  void bindTexture(string name);
  void bindTexture(unsigned int texnr);

  vector<string> texturelist;

  GLuint texturememory[NUMBEROFTEX];
 
  void addTexture(string filename);
  void loadTextureList();
  void updateTextureList();
  void removeTextures();
  void generateTextures();

 private:
  void loadTexture(string filename, int num);
  unsigned int fixedtextures;
};

#endif
