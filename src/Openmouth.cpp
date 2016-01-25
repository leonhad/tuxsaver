#include "Openmouth.hpp"

Openmouth::Openmouth()
{
  open=0;
}

Openmouth::~Openmouth()
{
}

void Openmouth::execute(parameters params)
{
  if (params.size()!=3)
    {
      cout << "wrong number of parameters for openbek" << endl;
    }
  else
    {
      //float begintime = params[0];
      float endtime = params[1];
      float destbek = params[2];

      
      if (worldtime>endtime)
	{
	  open=destbek;
	}
      else
	{
	  float factor=(endtime-worldtime)/(endtime-prevworldtime);
	  open=destbek-factor*(destbek-open);
	}
    }
}
