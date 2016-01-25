#include "textureloader.hpp"

#include <kstddirs.h>

TextureLoader::TextureLoader()
{
 
}

void TextureLoader::generateTextures()
{
  glGenTextures(NUMBEROFTEX, &texturememory[0]);
}

TextureLoader::~TextureLoader()
{
  glDeleteTextures (NUMBEROFTEX, &texturememory[0]);
}

void TextureLoader::loadTexture(string filename, int num)
{
  string fullfilename;
  fullfilename = "tuxsaver/pics/"+filename;

  cout << "loading " << fullfilename << endl;
  QImage texture;
  QImage buf;
  if (!buf.load(locate("data",fullfilename.c_str())))
    {
      cout << "Could not read image file, using single-color instead." << endl;
      QImage dummy(0,0,0);
      dummy.fill( Qt::white.rgb() );
      buf = dummy;
    }

  texture = QGLWidget::convertToGLFormat(buf);
  cout << "binding texture to load file:" << fullfilename << ":" << texturememory[num] << endl;
  glBindTexture(GL_TEXTURE_2D, texturememory[num]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);   
  glTexImage2D( GL_TEXTURE_2D, 0, 3, texture.width(), texture.height(), 0,GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );
  cout << "loading of " << filename << " finished" << endl;
}

void TextureLoader::bindTexture(string name)
{
  int n=0;
  vector<string>::iterator i;
  for (i=texturelist.begin();i<texturelist.end();i++)
    {
      if (name==(*i)) 
	{
	  bindTexture(n);
	  return;
	}
      n++;
    }
}

void TextureLoader::bindTexture(unsigned int nr)
{
  glBindTexture(GL_TEXTURE_2D, texturememory[nr]); 
}

//TODO check if texture is already in the list, maybe change vector to set or...
void TextureLoader::addTexture(string filename)
{
  vector<string>::iterator i;
  for (i=texturelist.begin(); i != texturelist.end(); i++)
    {
      if ( (*i)==filename) return ;
    }
  cout << "adding " << filename << " to texturelist..." << endl;	
  texturelist.push_back(filename);
  cout << "added to texturelist" << endl;	
}

void TextureLoader::loadTextureList()
{
  fixedtextures=texturelist.size();
  int n=0;
  vector<string>::iterator i;
  for (i=texturelist.begin(); i != texturelist.end(); i++)
    {
      loadTexture((*i),n);
      n++;
    }
}

void TextureLoader::updateTextureList()
{
  cout << "updating textures.." << endl; 
    
  int n=0;
  vector<string>::iterator i;
  //  for (i=texturelist.begin()+fixedtextures; i != texturelist.end(); i++)
  for (i=texturelist.begin(); i != texturelist.end(); i++) 
  {
      cout << "loading texture:" << endl;
      if ( (*i)!="")
	{
	  cout << "now" << endl;
	  if (n>=fixedtextures) 
	    {
	      cout << (*i) << endl;
	      loadTexture((*i),n);
	    }
	  n++;
	}
      else cout << "something wrong with the textures !!!" << endl;
    }
} 

void TextureLoader::removeTextures()
{
  cout << "removing textures..." << endl;
  texturelist.erase(texturelist.begin()+fixedtextures,texturelist.end());
}
