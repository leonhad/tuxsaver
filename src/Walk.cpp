#include "Walk.hpp"
#include "math.h"

float distance(float bx,float by,float bz, float ex, float ey, float ez)
{
  float dist;
  dist=sqrt( pow(ex-bx,2)+pow(ey-by,2)+pow(ez-bz,2));
  return dist;
}

Walk::Walk(Move *trans,Move *rot, Move *lfoot, Move *rfoot)
{
  translate=trans;
  rotate=rot;
  leftfoot=lfoot;
  rightfoot=rfoot;
  
  leftfootangle=0;
  rightfootangle=0;
  lang=12;
  rang=0;
  bodyangle=0;
  bang=-1.25;
  isWalking=0;
}

Walk::~Walk()
{
}

void Walk::execute(parameters params)
{
  translate->execute(params); 

  float endtime=params[1];

  if (!isWalking) 
    {
      //we start walking
      float pi = 3.14159265;
      isWalking=true;
      beginposx=translate->posx;
      beginposy=translate->posy;
      beginposz=translate->posz;
      beginax=rotate->posx;
      beginay=rotate->posy;
      beginaz=rotate->posz;
      //multipliers of the angles if the penguin is rotated around y-axis
      //==>TODO ?? other rotations could be useful but are they a must?? 
      multix=sin(beginay*pi/180);
      multiy=0;
      multiz=cos(beginay*pi/180);
    }

  if (worldtime>endtime)
    {
      isWalking=false;
    }
  
  float current=distance(translate->posx,translate->posy,translate->posz,beginposx,beginposy,beginposz);

  //do a translation and keep 0.1 sec to put feet back to normal position
  if (worldtime<=params[1]-0.1)
    {
      //destination for tux to move both feet ones.
      float dest=2;
      
      while (current>dest)
	{
	  current=current-dest;
	}

      float fourth=dest/4;
      float half=fourth*2;
      float treefourth=fourth*3;
      //float fac=0;

      if (current < fourth)
	{
	  float fac=45*(current/fourth);
	  leftfoot->execute(worldtime,worldtime,fac,0,0);
	  rightfoot->execute(worldtime,worldtime,0,0,0);
	  rotate->execute(worldtime,worldtime,beginax+multix*fac/4.5,beginay,beginaz+multiz*fac/4.5);
	}
      if ((current > fourth) && (current < half))
	{
	  float fac=45*((current-fourth)/fourth);
	  fac=45-fac;
	  leftfoot->execute(worldtime,worldtime,fac,0,0);
	  rightfoot->execute(worldtime,worldtime,0,0,0);
	  rotate->execute(worldtime,worldtime,beginax+multix*fac/4.5,beginay,beginaz+multiz*fac/4.5);
	}
      if ((current > half) && (current < treefourth))
	{
	  float fac=45*((current-half)/fourth);
	  rightfoot->execute(worldtime,worldtime,fac,0,0);
	  leftfoot->execute(worldtime,worldtime,0,0,0);
	  rotate->execute(worldtime,worldtime,beginax-multix*fac/4.5,beginay,beginaz-multiz*fac/4.5);
	}
      if (current > treefourth)
	{
	  float fac=45*((current-treefourth)/fourth);
	  fac=45-fac;
	  rightfoot->execute(worldtime,worldtime,fac,0,0);
	  leftfoot->execute(worldtime,worldtime,0,0,0);
	  rotate->execute(worldtime,worldtime,beginax-multix*fac/4.5,beginay,beginaz-multiz*fac/4.5);
	}
    }
  else
    {
      //we are in the right place but our feet are not right yet.
      leftfoot->execute(params[1]-0.1,params[1],0,0,0);
      rightfoot->execute(params[1]-0.1,params[1],0,0,0);
      
      //move closer to 0
      //TODO: this is not very good:
      if (rotate->posz!=0) rotate->posz=rotate->posz+((0-rotate->posz)/4);
      if (worldtime>endtime) rotate->posz=0;
    }
}

