#include "Visible.hpp"

Visible::Visible()
{
  state=1;
}

Visible::~Visible()
{
}

void Visible::execute(parameters params)
{
  if (params.size()!=2)
    {
      cout << "wrong number of parameters for visible" << endl;
    }
  else
    {
      //float begintime = params[0];
      float endtime = params[1];    
      if (worldtime>endtime)  state =1;
      else state=0;
    }
}
