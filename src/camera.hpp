#ifndef _CAMERA_HPP
#define _CAMERA_HPP

#include "object.hpp"

class Camera : public Object
{
public:
  Camera();
  ~Camera();
  void draw();

  GLUquadricObj *pObj;
};

#endif //_CAMERA_HPP
