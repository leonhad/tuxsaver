#ifndef _FOLLOW_HPP
#define _FOLLOW_HPP

#include <qgl.h>

#include "object.hpp"
#include "init.hpp"
#include "Move.hpp"
#include "utils.hpp"

class Object;

class Follow : public commando
{
public:
  Follow(Object *parent);
  virtual ~Follow();
  void execute(parameters);

  Object *parentObject;
  void interpretString(string parameterstring);
  vector<Object*> objectlist;

  vector<Object*> objectsThatFollowMe;
  void addObjectToFollowList(Object*);
  void drawFollowObjects();

  //TODO remove objectnumber and use vectorsize
  unsigned int objectnumber;
  void clearParameterList();  
};

#endif //_FOLLOW_HPP
