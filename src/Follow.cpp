#include "Follow.hpp"

#include <sstream>

extern EventClient* myEventServer;

float string2f(string inputstring)
{
  float outputfloat;
  istringstream ist(inputstring);
  ist >> outputfloat;
  return outputfloat;
}

Follow::Follow(Object *parent)
{
  parentObject=parent;
  objectnumber=0;
}

Follow::~Follow()
{
}

void Follow::execute(parameters params)
{
  //parameter nr2 contains a nr in the objectlist, we can use this number
  //to find out which object we have to follow during this periode in time.
  unsigned int obnr= uint(params[2]);
  float endtime=params[1];
      
  if (worldtime>endtime) {
#ifdef DEBUG
    cout << "-------------------> end of follow" << endl;
    cout << "me "<< parentObject->move->resulx <<"|" << parentObject->move->resulz << endl;
    cout << "my boss " << objectlist[obnr]->move->resulx << "|" <<objectlist[obnr]->move->resulz <<endl;
#endif
    //we execute this follow for the last time, so we put the object in his absolute coordinates,so it won't move back.
    parentObject->move->resulx += objectlist[obnr]->move->resulx;
    parentObject->move->resuly += objectlist[obnr]->move->resuly;
    parentObject->move->resulz += objectlist[obnr]->move->resulz;
#ifdef DEBUG
    cout << "my x cor"<< parentObject->move->resulx << endl;
    cout << "my z cor"<< parentObject->move->resulz << endl;
#endif
  } else {
    //add my object to the list of the object I have to follow, so when that object gets drawn, I get drawned too
    objectlist[obnr]->followobject->addObjectToFollowList(parentObject);
  }
}

//we make a seperate interpretSt0ring function for Follow because we need a string as a parameter in stead of a float.
void Follow::interpretString(string parameterstring)
{
#ifdef DEBUG
  cout <<"interpreting FollowString:" <<parameterstring << endl;
#endif
  Object *ob;
  int pos=0;
  parameters param;
  //interpret first parameter which is the starttime
  pos = parameterstring.find(' ');
  param.push_back(string2f(parameterstring.substr(0,pos)));
  parameterstring=parameterstring.substr(pos+1,parameterstring.length()-pos-1);

  //interpret second parameter which is the endtim
  pos = parameterstring.find(' ');
  param.push_back(string2f(parameterstring.substr(0,pos)));
  parameterstring=parameterstring.substr(pos+1,parameterstring.length()-pos-1);

  //add objectname to follow to object follow list
  //we add a number to the parameterlist, this number is the number of the objectname in the objectlist.
  //that we we can find the objectname when we do an execute.
 
  //maybe someday we change the param in a template, that would solve this problem better.
  
  param.push_back(objectnumber);
  //search the object and add it to the objectlist
  ob=static_cast<Object*>(myEventServer->searchEventClient(parameterstring));
  objectlist.push_back(ob);
  objectnumber++;

  //add begintime,eindtime and objectnumber to parameterlist of follow
  addParameters(param);  
}

//we reimplement this function to clear the objectlist
void Follow::clearParameterList()
{
  parameterlist.clear();
  objectlist.clear();
  objectnumber=0;
}

void Follow::addObjectToFollowList(Object*ob)
{
  objectsThatFollowMe.push_back(ob);
}

void Follow::drawFollowObjects()
{
  //draw al the object that follow me and clear list
  vector<Object*>::iterator i;
  for (i=objectsThatFollowMe.begin();i!=objectsThatFollowMe.end();i++) {
    (*i)->draw();
  }
  objectsThatFollowMe.clear();
}
