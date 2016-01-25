
#ifndef _OPENMOUTH_HPP
#define _OPENMOUTH_HPP

#include <qgl.h>

#include "EventClient.hpp"
#include "init.hpp"
#include "Move.hpp"

class Openmouth: public commando
{
public:
  Openmouth();
  ~Openmouth(); 
  void execute(parameters);
  float open;
};
#endif //_OPENMOUTH_HPP
