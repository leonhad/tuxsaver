#include "object.hpp"

Object::Object(string objectname): EventClient(objectname)
{
  move = new Move();
  move->setName("move");
  addCommando(move);

  rotate = new Move();
  rotate->setName("rotate");
  addCommando(rotate);

  visible = new Visible();
  visible->setName("visible");
  addCommando(visible);

  followobject = new Follow(this);
  followobject->setName("follow");
  addCommando(followobject);
}

Object::~Object()
{
  delete move;
  delete rotate;
  delete visible;
  delete followobject;
}

void Object::draw()
{
}

void Object::updateMainCo() {
  x = move->resulx;
  y = move->resuly;
  z = move->resulz;
  ax = rotate->resulx;
  ay = rotate->resuly;
  az = rotate->resulz;
}
