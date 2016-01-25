#include "ac3dtexture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <string>

using namespace std;

AC3DTexture::AC3DTexture() {
  this->num_texture = 1;
}

AC3DTexture::~AC3DTexture() {
}

ACImage *AC3DTexture::ac_get_texture(unsigned int ind) {
  if (ind > texture.size()) {
    return(NULL);
  } else return(texture[ind]);
}

int AC3DTexture::ac_load_texture(char *name) {
  int id = ac_load_rgb_image(name);
  
  if (id > -1) {
    ACImage *i = ac_get_texture(id);
    
    glBindTexture(GL_TEXTURE_2D, id);
    gluBuild2DMipmaps(GL_TEXTURE_2D, i->depth, i->width, i->height,
                     (i->depth==1)?GL_LUMINANCE: (i->depth==2)?GL_LUMINANCE_ALPHA:
                     (i->depth==3)?GL_RGB: GL_RGBA, GL_UNSIGNED_BYTE, i->data);
  }
  return(id);
}

int AC3DTexture::ac_load_rgb_image(char *fileName) {
  rawImageRec *raw;
  ACImage *final = NULL;
  
  unsigned int value = names[fileName];
  if (value != 0) {
#ifdef DEBUG
    printf("Texture %s already exists\n", fileName);
#endif
    return value;
  }  
  final = new ACImage();
  if (!final) {
    printf("Out of memmory\n");
  }

#ifdef DEBUG
  printf("Loading texture: %s\n", fileName);
#endif

  raw = RawImageOpen(fileName);
  if (raw == NULL) {
    fprintf(stderr, "error opening rgb file\n");
    return(-1);
  }
  
  final->width = raw->sizeX;
  final->height = raw->sizeY;
  final->depth = raw->sizeZ;
  
  RawImageGetData(raw, final);
  RawImageClose(raw);

#ifdef DEBUG  
  printf("loaded texture %dx%d (%d)\n", final->width, final->height, final->depth);
#endif
  
  texture[num_texture] = final;
  names[fileName] = num_texture;
  
  num_texture++;
  return(num_texture - 1);
}

rawImageRec *AC3DTexture::RawImageOpen(char *fileName) {
  union {
    int testWord;
    char testByte[4];
  } endianTest;
  
  rawImageRec *raw;
  int swapFlag;
  int x;
  
  endianTest.testWord = 1;
  if (endianTest.testByte[0] == 1) {
    swapFlag = GL_TRUE;
  } else {
    swapFlag = GL_FALSE;
  }
  
  raw = (rawImageRec *)malloc(sizeof(rawImageRec));
  if (raw == NULL) {
    fprintf(stderr, "Out of memory!\n");
    return(NULL);
  }
  
  if ((raw->file = fopen(fileName, "rb")) == NULL) {
    perror(fileName);
    return(NULL);
  }
  
  fread(raw, 1, 12, raw->file);
  
  if (swapFlag) {
    ConvertShort(&raw->imagic, 6);
  }
  
  raw->tmp = (unsigned char *)malloc(raw->sizeX*256);
  raw->tmpR = (unsigned char *)malloc(raw->sizeX*256);
  raw->tmpG = (unsigned char *)malloc(raw->sizeX*256);
  raw->tmpB = (unsigned char *)malloc(raw->sizeX*256);
  raw->tmpA = (unsigned char *)malloc(raw->sizeX*256);
  if (raw->tmp == NULL || raw->tmpR == NULL || raw->tmpG == NULL ||
    raw->tmpB == NULL) {
    fprintf(stderr, "Out of memory!\n");
    return(NULL);
  }
  
  if ((raw->type & 0xFF00) == 0x0100) {
    x = raw->sizeY * raw->sizeZ * sizeof(GLuint);
    raw->rowStart = (GLuint *)malloc(x);
    raw->rowSize = (GLint *)malloc(x);
    if (raw->rowStart == NULL || raw->rowSize == NULL) {
      fprintf(stderr, "Out of memory!\n");
      return(NULL);
    }
    raw->rleEnd = 512 + (2 * x);
    fseek(raw->file, 512, SEEK_SET);
    fread(raw->rowStart, 1, x, raw->file);
    fread(raw->rowSize, 1, x, raw->file);
    if (swapFlag) {
      ConvertLong(raw->rowStart, x/sizeof(GLuint));
      ConvertLong((GLuint *)raw->rowSize, x/sizeof(GLint));
    }
  }
  return raw;
}

void AC3DTexture::RawImageGetData(rawImageRec *raw, ACImage *final) {
  unsigned char *ptr;
  int i, j;
  
  final->data = (unsigned char *)malloc((raw->sizeX+1)*(raw->sizeY+1)*raw->sizeZ);
  if (final->data == NULL) {
    fprintf(stderr, "Out of memory!\n");
    return;
  }
  
  ptr = (unsigned char *)final->data;
  
  if (raw->sizeZ == 1) {
    for (i = 0; i < raw->sizeY; i++) {
      RawImageGetRow(raw, raw->tmpR, i, 0);
      //packing
      for (j = 0; j < raw->sizeX; j++) {
        *ptr++ = *(raw->tmpR + j);
        //*ptr++ = *(raw->tmpR + j);
        //*ptr++ = *(raw->tmpR + j);
        //*ptr++ = 255;
      }
    }
  }
  if (raw->sizeZ == 2) {
    for (i = 0; i < raw->sizeY; i++) {
      RawImageGetRow(raw, raw->tmpR, i, 0);
      RawImageGetRow(raw, raw->tmpA, i, 1);
      //packing
      for (j = 0; j < raw->sizeX; j++) {
        *ptr++ = *(raw->tmpR + j);
        //*ptr++ = *(raw->tmpR + j);
        //*ptr++ = *(raw->tmpR + j);
        *ptr++ = *(raw->tmpA + j);
        
        final->amask |= ((*(raw->tmpA + j) == 255) ? ALPHA_OPAQUE : 0);
        final->amask |= ((*(raw->tmpA + j) == 0) ? ALPHA_INVIS : 0);
        final->amask |= (((*(raw->tmpA + j)>0) && (*(raw->tmpA + j)<255)) ? ALPHA_TRANSP : 0);
      }
    }
  } else if (raw->sizeZ == 3) {
    for (i = 0; i < raw->sizeY; i++) {
      RawImageGetRow(raw, raw->tmpR, i, 0);
      RawImageGetRow(raw, raw->tmpG, i, 1);
      RawImageGetRow(raw, raw->tmpB, i, 2);
      //packing
      for (j = 0; j < raw->sizeX; j++) {
        *ptr++ = *(raw->tmpR + j);
        *ptr++ = *(raw->tmpG + j);
        *ptr++ = *(raw->tmpB + j);
        //*ptr++ = 255;
      }
    }
  } else if (raw->sizeZ == 4) {
    for (i = 0; i < raw->sizeY; i++) {
      RawImageGetRow(raw, raw->tmpR, i, 0);
      RawImageGetRow(raw, raw->tmpG, i, 1);
      RawImageGetRow(raw, raw->tmpB, i, 2);
      RawImageGetRow(raw, raw->tmpA, i, 3);
      //packing
      for (j = 0; j < raw->sizeX; j++) {
        *ptr++ = *(raw->tmpR + j);
        *ptr++ = *(raw->tmpG + j);
        *ptr++ = *(raw->tmpB + j);
        *ptr++ = *(raw->tmpA + j);
        
        final->amask |= ((*(raw->tmpA + j) == 255) ? ALPHA_OPAQUE : 0);
        final->amask |= ((*(raw->tmpA + j) == 0) ? ALPHA_INVIS : 0);
        final->amask |= (((*(raw->tmpA + j)>0) && (*(raw->tmpA + j)<255)) ? ALPHA_TRANSP : 0);
      }
    }
  }
}

void AC3DTexture::RawImageClose(rawImageRec *raw) {
  fclose(raw->file);
  free(raw->tmp);
  free(raw->tmpR);
  free(raw->tmpG);
  free(raw->tmpB);
  free(raw);
}

void AC3DTexture::ConvertShort(unsigned short *array, long length) {
  unsigned long b1, b2;
  unsigned char *ptr;
  
  ptr = (unsigned char *)array;
  while (length--) {
    b1 = *ptr++;
    b2 = *ptr++;
    *array++ = (unsigned short)((b1 << 8) | (b2));
  }
}

void AC3DTexture::ConvertLong(GLuint *array, long length) {
  unsigned long b1, b2, b3, b4;
  unsigned char *ptr;
  
  ptr = (unsigned char *)array;
  while (length--) {
    b1 = *ptr++;
    b2 = *ptr++;
    b3 = *ptr++;
    b4 = *ptr++;
    *array++ = (b1 << 24) | (b2 << 16) | (b3 << 8) | (b4);
  }
}

void AC3DTexture::RawImageGetRow(rawImageRec *raw, unsigned char *buf, int y, int z) {
  unsigned char *iPtr, *oPtr, pixel;
  int count;
  
  if ((raw->type & 0xFF00) == 0x0100) {
    fseek(raw->file, raw->rowStart[y+z*raw->sizeY], SEEK_SET);
    fread(raw->tmp, 1, (unsigned int)raw->rowSize[y+z*raw->sizeY],
    raw->file);
    
    iPtr = raw->tmp;
    oPtr = buf;
    while (1) {
      pixel = *iPtr++;
      count = (int)(pixel & 0x7F);
      if (!count) {
        return;
      }
      if (pixel & 0x80) {
        while (count--) {
          *oPtr++ = *iPtr++;
        }
      } else {
        pixel = *iPtr++;
        while (count--) {
          *oPtr++ = pixel;
        }
      }
    }
  } else {
    fseek(raw->file, 512+(y*raw->sizeX)+(z*raw->sizeX*raw->sizeY), SEEK_SET);
    fread(buf, 1, raw->sizeX, raw->file);
  }
}

