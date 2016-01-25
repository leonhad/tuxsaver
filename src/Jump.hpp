#ifndef _JUMP_HPP
#define _JUMP_HPP

#include <qgl.h>

#include "EventClient.hpp"
#include "init.hpp"
#include "Move.hpp"

class Jump: public commando
{
public:
  Jump(Move *trans,Move *rfoot,Move *lfoot,Move *rarm,Move *larm);
  ~Jump(); 
  void execute(parameters);
  Move *translate;
  Move *rightf,*righta,*leftf,*lefta;
  float posx,posy,posz,sty,a,b,wing;
  bool state;
};
#endif //_JUMP_HPP
