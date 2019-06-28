#ifndef _ac3dtexture_h
#define _ac3dtexture_h

// if system is a windows
#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <map>
#include <string>
#include "ac3d.h"

#ifndef SEEK_SET
#define SEEK_SET 0
#endif

/** no alpha info */
#define ALPHA_NONE   (0x0000)
/** alpha = 1 */
#define ALPHA_OPAQUE (0x0001<<0)
/** alpha = 0 */
#define ALPHA_INVIS  (0x0001<<1)
/** 0 < alpha < 1 */
#define ALPHA_TRANSP (0x0004<<2)

using namespace std;

typedef struct _rawImageRec {
  unsigned short imagic;
  unsigned short type;
  unsigned short dim;
  unsigned short sizeX, sizeY, sizeZ;
  unsigned long min, max;
  unsigned long wasteBytes;
  char name[80];
  unsigned long colorMap;
  FILE *file;
  unsigned char *tmp, *tmpR, *tmpG, *tmpB, *tmpA;
  unsigned long rleEnd;
  GLuint *rowStart;
  GLint *rowSize;
} rawImageRec;

typedef map<unsigned int, ACImage*> textureType;
typedef map<string, unsigned int> namesType;

/*A Texture manipulation
 *@author Leonardo Alves da Costa <leonardoac@brturbo.com>
 */
class AC3DTexture {
protected:
  textureType texture;
  namesType names;
  int num_texture;

public:
  AC3DTexture();
  ~AC3DTexture();

  /** Load a texture and return your code in class */
  int ac_load_texture(char *name);
  /** Get a image by a int value */
  ACImage *ac_get_texture(unsigned int ind);
  
protected:
  /** Returns a rawImageRec form a file */ 
  rawImageRec *RawImageOpen(char *fileName);
  /** Load the data from a raw image */
  void RawImageGetData(rawImageRec *raw, ACImage *final);
  /** Close a raw image */
  void RawImageClose(rawImageRec *raw);
  /** Convert a array of bytes to unsigned shot numbers */
  void ConvertShort(unsigned short *array, long length);
  /** Convert a array of bytes to GLuint numbers */
  void ConvertLong(GLuint *array, long length);
  /** Get a row from a raw image */
  void RawImageGetRow(rawImageRec *raw, unsigned char *buf, int y, int z);
  /** Load a rgb image by name */
  int ac_load_rgb_image(char *fileName);
};

#endif

