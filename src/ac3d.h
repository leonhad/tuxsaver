#ifndef _ac3d_h
#define _ac3d_h

// if system is windows
#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

/** Define a 3D point */
typedef struct ACPoint_t {
  float x, y, z;
} ACPoint;

/** Define a normal point */
typedef struct ACNormal_t {
  float x, y, z;
} ACNormal;

/** Define a vertex point */
typedef struct ACVertex_t {
  float x, y, z;
  ACNormal normal;
} ACVertex;

/** The UV struct */
typedef struct ACUV_t {
  float u, v;
} ACUV;

/** The Surface of the polygon */
typedef struct ACSurface_t {
  int *vertref;
  ACUV *uvs;
  int num_vertref;
  ACNormal normal;
  int flags;
  int mat;
} ACSurface;

/** The AC3D Object struct */
typedef struct ACObject_t {
  ACPoint loc;
  char *name;
  char *data;
  char *url;
  ACVertex *vertices;
  int num_vert;

  ACSurface *surfaces;
  int num_surf;
  float texture_repeat_x, texture_repeat_y;
  float texture_offset_x, texture_offset_y;

  int num_kids;
  struct ACObject_t **kids;
  float matrix[9];
  int type;
  bool texture;
  char* texture_name;
} ACObject;

/** The RGBA color scheme */
typedef struct ACCol_t {
  float r, g, b, a;
} ACCol;

typedef struct Material_t {
  /** diffuse */
  ACCol rgb;
  ACCol ambient;
  ACCol specular;
  ACCol emissive;
  float shininess;
  float transparency;
  char *name;
} ACMaterial;

typedef struct ACImage_t {
  unsigned short width, height, depth;    
  void *data; 
  int index;
  char *name;
  int amask;
  /** do not set - set automatically in texture_read function **/
  char *origname;
} ACImage;

#define OBJECT_WORLD 999
#define OBJECT_NORMAL 0
#define OBJECT_GROUP 1
#define OBJECT_LIGHT 2

#define SURFACE_SHADED (1<<4)
#define SURFACE_TWOSIDED (1<<5)

#define SURFACE_TYPE_POLYGON (0)
#define SURFACE_TYPE_CLOSEDLINE (1)
#define SURFACE_TYPE_LINE (2)

#define STRING(s)  (char *)(strcpy((char *)malloc(strlen(s)+1), s))
#define streq(a,b)  (!strcmp(a,b))

#endif

