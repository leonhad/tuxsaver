#include "ac3dloader.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>

#include <kstandarddirs.h>
#include <string>

#include "ac3d.h"
#include "textureloader.hpp"

AC3DLoader::AC3DLoader(TextureLoader *tex) {
  this->ob = NULL;
  this->num_palette = 0;
  this->startmatindex = 0;
  this->line = 0;
  this->tokc = 0;
  
  texture = tex;
}

AC3DLoader::~AC3DLoader() {
}

bool AC3DLoader::load(string filename) {
  cout << "loading file:" << filename << endl;
  string fullname="tuxsaver/objects/"+filename;
  fullname=locate("data",fullname.c_str()).latin1();
  //#ifdef DEBUG
  cout << "loading " << fullname << endl;
  //#endif
  ob =  ac_load_ac3d(fullname);
  cout << "ac3d file loaded" << endl;
  texture->updateTextureList();
  cout << "textures for ac3d object loaded" << endl;
  if (ob) {
    listValue = ac_display_list_render_object(ob);
    cout << "object rendered" << endl;
    return true;
  }
  return false;
}

void AC3DLoader::ac_prepare_render() {

  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  glDisable( GL_COLOR_MATERIAL ); 

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

ACObject *AC3DLoader::ac_load_ac3d(string fname) {
  string fln=fname;
  FILE *f = fopen(fln.c_str(), "r");
  ACObject *ret = NULL;

  if (f == NULL) {
    //    printf("can't open file: %s\n", fname);
    cout << "can't open file:" << fname << endl; 
    return(NULL);
  }

  read_line(f);
    
  if (strncmp(buff, "AC3D", 4)) {
    //    printf("ac_load_ac '%s' is not a valid AC3D file.", fname);
    cout << "can't open file:" << fname << endl; 
    fclose(f);
    return(0);
  }

  startmatindex = num_palette;
  ret = ac_load_object(f, NULL);
  fclose(f);
  ac_calc_vertex_normals(ret);

  return(ret);
}

bool AC3DLoader::read_line(FILE *f) {
  fgets(buff, 255, f); line++;
  return(true);
}

ACObject *AC3DLoader::ac_load_object(FILE *f, ACObject *parent) {
  char t[20];
  ACObject *ob = NULL;

  while (!feof(f)) {
    read_line(f);
    sscanf(buff, "%s", t);

    if (streq(t, "MATERIAL")) {
      float shi, tran;
      ACMaterial m;

      if (get_tokens(buff, &tokc, tokv) != 22) {
        printf("expected 21 params after \"MATERIAL\" - line %d\n", line);
      } else {
        m.name = STRING(tokv[1]);
        m.rgb.r = (float)atof(tokv[3]);
        m.rgb.g = (float)atof(tokv[4]);
        m.rgb.b = (float)atof(tokv[5]);
        
        m.ambient.r = (float)atof(tokv[7]);
        m.ambient.g = (float)atof(tokv[8]);
        m.ambient.b = (float)atof(tokv[9]);
        m.emissive.r = (float)atof(tokv[11]);
        m.emissive.g = (float)atof(tokv[12]);
        m.emissive.b = (float)atof(tokv[13]);
        
        m.specular.r = (float)atof(tokv[15]);
        m.specular.g = (float)atof(tokv[16]);
        m.specular.b = (float)atof(tokv[17]);
        
        m.shininess = (float)atof(tokv[19]);
        m.transparency = (float)atof(tokv[21]);
        
        shi = (float)atof(tokv[6]);
        tran = (float)atof(tokv[7]);
        
        palette[num_palette++] = m;
      }
    } else if (streq(t, "OBJECT")) {
      char type[20];      
      char str[20];
      ob = new_object();
      
      sscanf(buff, "%s %s", str, type);

      ob->type = string_to_objecttype(type);
    } else if (streq(t, "data")) {
      if (get_tokens(buff, &tokc, tokv) != 2) {

        printf("expected 'data <number>' at line %d\n", line);
      } else {
        char *str;
        int len;
  
        len = atoi(tokv[1]);
        if (len > 0) {
          str = (char *)malloc(len+1);
          fread(str, len, 1, f);
          str[len] = 0;
          fscanf(f, "\n"); line++;
          ob->data = STRING(str);
          free(str);
        }
      }
    } else if (streq(t, "name")) {
      int numtok = get_tokens(buff, &tokc, tokv);
      if (numtok != 2) {
        printf("expected quoted name at line %d (got %d tokens)\n", line, numtok);
      } else ob->name = STRING(tokv[1]);
    } else if (streq(t, "texture")) {
      if (get_tokens(buff, &tokc, tokv) != 2) {
        printf("expected quoted texture name at line %d\n", line);
      } else {

        ob->texture = true;
	string n = STRING(tokv[1]);
	unsigned int i = n.rfind('/',n.size());
	n = n.replace(0,i+1,"");
	ob->texture_name=STRING(n.c_str());
	texture->addTexture(ob->texture_name);
      }
    } else if (streq(t, "texrep")) {
      if (get_tokens(buff, &tokc, tokv) != 3) {
        printf("expected 'texrep <float> <float>' at line %d\n", line);
      } else {
        ob->texture_repeat_x = (float)atof(tokv[1]);
        ob->texture_repeat_y = (float)atof(tokv[2]);
      }
    } else if (streq(t, "texoff")) {
      if (get_tokens(buff, &tokc, tokv) != 3) {
        printf("expected 'texoff <float> <float>' at line %d\n", line);
      } else {
        ob->texture_offset_x = (float)atof(tokv[1]);
        ob->texture_offset_y = (float)atof(tokv[2]);
      }
    } else if (streq(t, "rot")) {
      float r[9];
      char str2[5];
      int n;

      sscanf(buff, "%s %f %f %f %f %f %f %f %f %f", str2, 
             &r[0], &r[1], &r[2], &r[3], &r[4], &r[5], &r[6], &r[7], &r[8] );

      for (n = 0; n < 9; n++)
        ob->matrix[n] = r[n];
    } else if (streq(t, "loc")) {
      char str[5];
      sscanf(buff, "%s %f %f %f", str,
             &ob->loc.x, &ob->loc.y, &ob->loc.z);      
    } else if (streq(t, "url")) {
      if (get_tokens(buff, &tokc, tokv) != 2) {
        printf("expected one arg to url at line %d (got %s)\n", line, tokv[0]);
      } else ob->url = STRING(tokv[1]);
    } else if (streq(t, "numvert")) {
      int num, n;
      char str[10];

      sscanf(buff, "%s %d", str, &num);

      if (num > 0) {
        ob->num_vert = num;
        ob->vertices = (ACVertex *)malloc(sizeof(ACVertex)*num);

        for (n = 0; n < num; n++) {
          ACVertex p;
          fscanf(f, "%f %f %f\n", &p.x, &p.y, &p.z); line++;
          ob->vertices[n] = p;
        }
      }
    } else if (streq(t, "numsurf")) {
      int num, n;
      char str[10];

      sscanf(buff, "%s %d", str, &num);
      if (num > 0) {
        ob->num_surf = num;
        ob->surfaces = (ACSurface *)malloc(sizeof(ACSurface) * num);

        for (n = 0; n < num; n++) {
          ACSurface *news = read_surface(f, &ob->surfaces[n], ob);
          if (news == NULL) {
            printf("error whilst reading surface at line: %d\n", line);
            return(NULL);
          }
        }
      }
    /** 'kids' is the last token in an object **/
    } else if (streq(t, "kids")) {
      int num, n;

      sscanf(buff, "%s %d", t, &num);

      if (num != 0) {
        ob->kids = (ACObject **)malloc(num * sizeof(ACObject *) );
        ob->num_kids = num;

        for (n = 0; n < num; n++) {
          ACObject *k = ac_load_object(f, ob);

          if (k == NULL) {
            printf("error reading expected child object %d of %d at line: %d\n",
                   n+1, num, line);
            return(ob);
          } else ob->kids[n] = k;
        }
      }
      return(ob);
    }
  }
  return(ob);
}

void AC3DLoader::tri_calc_normal(ACPoint *v1, ACPoint *v2, ACPoint *v3, ACPoint *n) {
  double len;

  n->x = (v2->y-v1->y)*(v3->z-v1->z)-(v3->y-v1->y)*(v2->z-v1->z);
  n->y = (v2->z-v1->z)*(v3->x-v1->x)-(v3->z-v1->z)*(v2->x-v1->x);
  n->z = (v2->x-v1->x)*(v3->y-v1->y)-(v3->x-v1->x)*(v2->y-v1->y);
  len = sqrt(n->x*n->x + n->y*n->y + n->z*n->z);

  if (len > 0) {
    n->x /= (float)len;
    n->y /= (float)len;
    n->z /= (float)len;  
  }
}

void AC3DLoader::ac_calc_vertex_normals(ACObject *ob) {
  int n;
  
  ac_object_calc_vertex_normals(ob);
  if (ob->num_kids)
    for (n = 0; n < ob->num_kids; n++)
       ac_calc_vertex_normals(ob->kids[n]);
}

int AC3DLoader::get_tokens(char *s, int *argc, char *argv[]) {
  char *p = s;
  char *st;
  char c;
  int tc;

  tc = 0;
  while ((c=*p) != 0) {
    if ((c != ' ') && (c != '\t') && (c != '\n') && ( c != 13)) {
      if (c == '"') {
        c = *p++;
        st = p;
        while ((c = *p) && ((c != '"')&&(c != '\n')&& ( c != 13)) ) {
          if (c == '\\') {
            strcpy(p, p+1);
          }
          p++;
        }
        *p=0;
        argv[tc++] = st;
      } else {
        st = p;
        while ((c = *p) && ((c != ' ') && (c != '\t') && (c != '\n') && (c != 13))) {
          p++;
        }
        *p=0;
        argv[tc++] = st;
      }
    }
    p++;
  }
  
  *argc = tc;
  return(tc);
}

int AC3DLoader::string_to_objecttype(char *s) {
  if (streq("world", s))
    return(OBJECT_WORLD);
  if (streq("poly", s))
    return(OBJECT_NORMAL);
  if (streq("group", s))
    return(OBJECT_GROUP);
  if (streq("light", s))
    return(OBJECT_LIGHT);
  return(OBJECT_NORMAL);
}

ACObject *AC3DLoader::new_object() {
  ACObject *ob = (ACObject *)malloc(sizeof(ACObject));
  
  ob->loc.x = ob->loc.y = ob->loc.z = 0.0;
  ob->name = ob->url = NULL;
  ob->data = NULL;
  ob->vertices = NULL;
  ob->num_vert = 0;
  ob->surfaces = NULL;
  ob->num_surf = 0;
  ob->texture = false;
  ob->texture_name = NULL;
  ob->texture_repeat_x = ob->texture_repeat_y = 1.0;
  ob->texture_offset_x = ob->texture_offset_y = 0.0;
  ob->kids = NULL;
  ob->num_kids = 0;
  ob->matrix[0] = 1;
  ob->matrix[1] = 0;
  ob->matrix[2] = 0;
  ob->matrix[3] = 0;
  ob->matrix[4] = 1;
  ob->matrix[5] = 0;

  ob->matrix[6] = 0;
  ob->matrix[7] = 0;
  ob->matrix[8] = 1;
  return(ob);
}

void AC3DLoader::ac_object_calc_vertex_normals(ACObject *ob) {
  int s, v, vr;
  
  // for each vertex in this object
  for (v = 0; v < ob->num_vert; v++) {
    ACNormal n = {0, 0, 0};
    int found = 0;
    
    // go through each surface
    for (s = 0; s < ob->num_surf; s++) {
      ACSurface *surf = &ob->surfaces[s];
      
      // check if this vertex is used in this surface
      // if it is, use it to create an average normal
      for (vr = 0; vr < surf->num_vertref; vr++)
        if (surf->vertref[vr] == v) {
          n.x+=surf->normal.x;

          n.y+=surf->normal.y;
          n.z+=surf->normal.z;
          found++;
        }
    }
    if (found > 0) {
      n.x /= found;
      n.y /= found;
      n.z /= found;
    }
    ob->vertices[v].normal = n;
  }
}

ACSurface *AC3DLoader::read_surface(FILE *f, ACSurface *s, ACObject *ob) {
  char t[20];
  
  init_surface(s);
  
  while (!feof(f)) {
    read_line(f);
    sscanf(buff, "%s", t);
    
    if (streq(t, "SURF")) {
      int flgs;
      
      if (get_tokens(buff, &tokc, tokv) != 2) {
        printf("SURF should be followed by one flags argument\n");
      } else {
        flgs = strtol(tokv[1], NULL, 0);
        s->flags = flgs;
      }
    } else if (streq(t, "mat")) {
      int mindx;
      
      sscanf(buff, "%s %d", t, &mindx);
      s->mat = mindx+startmatindex;
    } else if (streq(t, "refs")) {
      int num, n;
      int ind;
      float tx, ty;
      
      sscanf(buff, "%s %d", t, &num);        
      
      s->num_vertref = num;
      s->vertref = (int *)malloc( num * sizeof(int));
      s->uvs = (ACUV *)malloc( num * sizeof(ACUV));
      
      for (n = 0; n < num; n++) {
        fscanf(f, "%d %f %f\n", &ind, &tx, &ty); line++;
        s->vertref[n] = ind;
        s->uvs[n].u = tx;
        s->uvs[n].v = ty;
      }
      
      // calc surface normal
      if (s->num_vertref >= 3) {
        tri_calc_normal((ACPoint *)&ob->vertices[s->vertref[0]], 
                        (ACPoint *)&ob->vertices[s->vertref[1]], 
                        (ACPoint *)&ob->vertices[s->vertref[2]], (ACPoint *)&s->normal);
      }
      return(s);
    } else printf("ignoring %s\n", t);
  }
  return(NULL);
}

void AC3DLoader::init_surface(ACSurface *s) {
  s->vertref = NULL;
  s->uvs = NULL;
  s->num_vertref = 0;
  s->flags = 0;
  s->mat = 0;
  s->normal.x = 0.0; s->normal.z = 0.0; s->normal.z = 0.0; 
}

int AC3DLoader::ac_display_list_render_object(ACObject *ob) {
  GLuint  list;
  
  list = glGenLists(1);
  glNewList(list, GL_COMPILE);
#ifdef DEBUG
  printf("genlist = %d\n", list);
#endif
  
  render(ob);
  glEndList();
  return(list);
}

void AC3DLoader::render(ACObject *ob) {

// #ifdef DEBUG
//   printf("rendering...\n");
// #endif

  int n, s, sr;
  int st;
  
  glPushMatrix();
  glTranslated(ob->loc.x, ob->loc.y, ob->loc.z);

  //disabling textures by default

  //if a object wants a texture it will be enabled below
  glDisable(GL_TEXTURE_2D);

  // if exist an texture
  if (ob->texture) {
    //static int lasttextureset = -1;
    //texture->ac_get_texture(ob->texture);
    
    glEnable(GL_TEXTURE_2D);
    // bind the texture by name
    cout << "binding texture:" << ob->texture_name << "!" << endl;
    texture->bindTexture(ob->texture_name);
    
    
  }


  for (s = 0; s < ob->num_surf; s++) {

    ACSurface *surf = &ob->surfaces[s];
    
    glNormal3fv((GLfloat *)&surf->normal);
    
    //if (surf->flags & SURFACE_TWOSIDED) glDisable(GL_CULL_FACE);
    //else glEnable(GL_CULL_FACE);
    
    st = surf->flags & 0xf;
    if (st == SURFACE_TYPE_CLOSEDLINE) {
      //glDisable(GL_LIGHTING);
      
      glBegin(GL_LINE_LOOP);
      col_set_simple(surf->mat);
    } else if (st == SURFACE_TYPE_LINE) {
      //glDisable(GL_LIGHTING);
      
      glBegin(GL_LINE_STRIP);
      col_set_simple(surf->mat);
    } else {
      //glEnable(GL_LIGHTING);
      col_set(surf->mat);
      if (surf->num_vertref == 3) glBegin(GL_TRIANGLE_STRIP);
      else glBegin(GL_POLYGON);
    }
    
    for (sr = 0; sr < surf->num_vertref; sr++) {
      ACVertex *v = &ob->vertices[surf->vertref[sr]];

      if (ob->texture) {
        float tu = surf->uvs[sr].u;
        float tv = surf->uvs[sr].v;
        
        float tx = ob->texture_offset_x + tu * ob->texture_repeat_x;
        float ty = ob->texture_offset_y + tv * ob->texture_repeat_y;
        
	glTexCoord2f(tx, ty);
      }

      if (surf->flags & SURFACE_SHADED) glNormal3fv((GLfloat *)&v->normal);
      
      glVertex3fv((GLfloat *)v);
  }
    glEnd();
   }

  if (ob->num_kids)
    for (n = 0; n < ob->num_kids; n++)
      render(ob->kids[n]); 
  
  glPopMatrix();
  
  //since in the rest of the program,  textures are enable by default, we enable it again
  glEnable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glColor4f(1.0,1.0,1.0,0);
}

void AC3DLoader::col_set_simple(long matno) {
  ACMaterial *m = ac_palette_get_material(matno);
  
  glColor3fv((float *)&m->rgb);
}

void AC3DLoader::col_set(long matno) {
  ACMaterial *m = ac_palette_get_material(matno);
  ACCol rgba;
  //  static int lastcolset = -1;
  

  //if this is enabled, some objects get displayed white, when they should be colored,   koen
  //   if (lastcolset == matno) {
  //     return;
  //   } else {
  //     lastcolset = matno;
  //   }
  
  rgba = m->rgb;
  rgba.a = 1.0-m->transparency;
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (float*)&rgba);
  
  rgba = m->ambient;
  rgba.a = 1.0-m->transparency;
  
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (float *)&rgba);
  
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, (float *)&m->emissive);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (float *)&m->specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, (float *)&m->shininess);
  
  if (rgba.a < 1.0) {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
  } else glDisable(GL_BLEND);
  
  glColor4f(m->rgb.r,m->rgb.g,m->rgb.b,rgba.a);
}

ACMaterial *AC3DLoader::ac_palette_get_material(int id) {
  return(&palette[id]);
}

