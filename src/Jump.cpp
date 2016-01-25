#include "Jump.hpp"
#include "math.h"

Jump::Jump(Move *trans,Move *rf,Move *lf,Move *ra,Move *la)
{
  translate=trans;
  state=false;
  rightf=rf;
  leftf=lf;
  righta=ra;
  lefta=la;
  posx=0;
  posy=0;
  posz=0;
  sty=0;
  wing=0;
}

Jump::~Jump()
{
}

void Jump::execute(parameters params)
{
  if ((params.size()!=7) || !(params[5]>0))
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
      float desthight = params[5];
      // unused
      //float destwing=params[6];
      
      
      if (worldtime>endtime)
	{
	  translate->posx=destx;
	  translate->posy=desty;
	  translate->posz=destz;
	  lefta->posy=0;
	  righta->posy=0;
	  state=false;
	  lefta->posy=0;
	  righta->posy=0;
	  sty=0;
	}
      else
	{
	  //	  cout << "we're jumping" << endl;
	  if (state==false) {
	    sty=translate->posy;
	    state=true;
	  }
	 //  if (worldtime<endtime+0.1) {
// 	    float factor2=(endtime-worldtime)/(endtime-prevworldtime);
// 	    wing=destwing-factor2*(destwing-wing);
// 	    lefta->posy=wing;
// 	    righta->posy=wing;
// 	  }

   


	  float factor=(endtime-worldtime)/(endtime-prevworldtime);
	  float t2 = endtime-begintime;
	  float y2=desty-sty;
	  float t=worldtime-begintime;
	  desthight=desthight+y2;
	  
	  float b=2*desthight*(1+sqrt(1-y2/desthight))/t2;
	  float a=-b*b/(4*desthight);
	  float h=a*t*t+b*t;

	  posx=destx-factor*(destx-posx);
	  posy=sty+h;
	  posz=destz-factor*(destz-posz);

	  translate->posx=posx;
	  translate->posy=posy;
	  translate->posz=posz;

// 	  cout << endl;
// 	  cout << "jumping with: "  << t2 << " " << y2 << " " << t << " " << h << " " << desthight << " " << b << " " << a << " " << posy << endl;
// 	  cout << worldtime << endl;
// 	  cout << "jumping to:   " << destx << " " << desty << " " << destz << " " << desthight << endl;
// 	  cout << endl;
	}
    }
}


