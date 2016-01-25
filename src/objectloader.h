#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

/*A Abstract Object Loader
 *@author Leonardo Alves da Costa <leonardoac@brturbo.com>
 */

#include <string>

using namespace std;

class ObjectLoader {
protected:
  /** Store the erros */
  bool error;
  /** Store the value of list in OpenGL */
  int listValue;
  
public:
  ObjectLoader();
  virtual ~ObjectLoader();
	
  /** It have a error? */
  bool isError();
  /** Load the object */
  virtual bool load(string filename) = 0;
  /** Return the OpenGL list value */
  int getListValue();
};

#endif

