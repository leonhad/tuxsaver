#ifndef _VISIBLE_HPP
#define _VISIBLE_HPP

#include <qgl.h>

#include "EventClient.hpp"
#include "init.hpp"

// state=0 visible, state=1 invisible
class Visible : public commando
{
public:
  Visible();
  virtual ~Visible();
  void  execute(parameters);
  int state;
};

#endif //_VISIBLE_HPP
