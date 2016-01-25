#ifndef _MOVE_HPP
#define _MOVE_HPP

#include <qgl.h>

#include "EventClient.hpp"
#include "init.hpp"

class Move : public commando
{
public:
  Move();
  virtual ~Move();
  void execute(parameters);
  void execute(GLfloat,GLfloat,GLfloat);
  void execute(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
  GLfloat posx,posy,posz,ofsx,ofsy,ofsz,resulx,resuly,resulz;
};

#endif //_MOVE_HPP
