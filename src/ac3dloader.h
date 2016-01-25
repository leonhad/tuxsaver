#ifndef AC3DLOADER_H
#define AC3DLOADER_H

#include <stdio.h>
#include <string>

#include "textureloader.hpp"
#include "objectloader.h"
#include "ac3d.h"

/*The AC3D file loader
 *@author Leonardo Alves da Costa <leonardoac@brturbo.com>
 */
class AC3DLoader : public ObjectLoader {
protected:
  ACObject *ob;
  int line;
  int num_palette;
  int startmatindex;
  
  int tokc;
  char *tokv[30];
  ACMaterial palette[255];
  char buff[255];

  // All textures for one object
  TextureLoader *texture;
  
public:
  AC3DLoader(TextureLoader *tex);
  virtual ~AC3DLoader();
  /** laod the object from a file
   * @param filename The object file name
   */
  virtual bool load(string filename);

protected:
  /** Prepate the OpenGL to rendering */
  void ac_prepare_render();
  /** Load the ac3d file
   * @param fname The object file name
   */
  ACObject *ac_load_ac3d(string fname);
  /** Load a object from a file */
  ACObject *ac_load_object(FILE *f, ACObject *parent);
  /** Calculate the normal of a triangle */
  void tri_calc_normal(ACPoint *v1, ACPoint *v2, ACPoint *v3, ACPoint *n);
  /** Calculate the normal of a vertex */
  void ac_calc_vertex_normals(ACObject *ob);
  /** Get token like int main(argc, argv) */
  int get_tokens(char *s, int *argc, char *argv[]);
  /** Read a line from file */
  bool read_line(FILE *f);
  /** Convert a string name to ObjectType */
  int string_to_objecttype(char *s);
  /** Create a new object */
  ACObject *new_object();
  /** Calculate the normal of a vertex by a object*/
  void ac_object_calc_vertex_normals(ACObject *ob);
  /** Read a surface from a file */
  ACSurface *read_surface(FILE *f, ACSurface *s, ACObject *ob);
  /** Initialize the surface */
  void init_surface(ACSurface *s);
  /** Render a ACObject in a OpenGL list */
  int ac_display_list_render_object(ACObject *ob);
  /** render the AC3D Object */
  void render(ACObject *ob);
  /** set a simple color */
  void col_set_simple(long matno);
  /** set color */
  void col_set(long matno);
  /** return the palette by number */
  ACMaterial *ac_palette_get_material(int id);
};

#endif // AC3DLOADER_H

