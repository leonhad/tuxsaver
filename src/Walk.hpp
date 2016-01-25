#ifndef _WALK_HPP
#define _WALK_HPP

#include <qgl.h>

#include "EventClient.hpp"
#include "init.hpp"
#include "Move.hpp"

class Walk: public commando
{
public:
  Walk(Move *trans,Move *rot,Move *lfoot,Move *rfoot);
  ~Walk();
  void execute(parameters);
  GLfloat leftfootangle;
  GLfloat rightfootangle;
  GLfloat lang;
  GLfloat rang;
  GLfloat bodyangle;
  GLfloat bang;

  bool isWalking;
  GLfloat beginposx,beginax,multix;
  GLfloat beginposy,beginay,multiy;
  GLfloat beginposz,beginaz,multiz;

  Move *translate;
  Move *rotate;
  Move *leftfoot;
  Move *rightfoot;
};
#endif //_WALK_HPP
