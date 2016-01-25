#ifndef _OBJECT_HPP
#define _OBJECT_HPP

#include "Move.hpp"
#include "Follow.hpp"
#include "Visible.hpp"
#include "EventClient.hpp"

class Follow;
// thing which are common to all object
// move, rotate, follow, visible,...
class Object : public EventClient {
public:
  Object(string objectname);
  virtual ~Object();
  void updateMainCo();

  Move *move;
  Move *rotate;
  Follow *followobject;

  Visible *visible;

  GLfloat x,y,z,ax,ay,az;
  int state;

  virtual void draw();
};

#endif //_OBJECT_HPP
