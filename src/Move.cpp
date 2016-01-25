#include "Move.hpp"

Move::Move()
{
  posx=0;
  posy=0;
  posz=0;
  resulx=0;
  resuly=0;
  resulz=0;
}

Move::~Move()
{
}

void Move::execute(GLfloat p1,GLfloat p2,GLfloat p3,GLfloat p4,GLfloat p5)
{
  //float begintime = p1;
  float endtime = p2;
  float destx = p3;
  float desty = p4;
  float destz = p5;
      
  if (worldtime>endtime)
    {
      posx=destx;
      posy=desty;
      posz=destz;
      execute(0,0,0);
    }
  else
    {
      float factor=(endtime-worldtime)/(endtime-prevworldtime);
      posx=destx-factor*(destx-posx);
      posy=desty-factor*(desty-posy);
      posz=destz-factor*(destz-posz);
      execute(0,0,0);
    }
}


void Move::execute(GLfloat ofsx,GLfloat ofsy,GLfloat ofsz) {
  resulx=posx+ofsx;
  resuly=posy+ofsy;
  resulz=posz+ofsz;
}

void Move::execute(parameters params) {

  if (params.size()!=5)
    {
      cout << "wrong number of parameters for move" << endl;
    }
  else
    {
      float begintime = params[0];
      float endtime = params[1];
      float destx = params[2];
      float desty = params[3];
      float destz = params[4];
      execute(begintime,endtime,destx,desty,destz);
    }
}
