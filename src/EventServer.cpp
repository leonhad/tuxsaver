#include "EventServer.hpp"

#include <kstddirs.h>
#include <qstring.h>
#include <sstream>
#include <fstream>

#include <time.h>
#include <stdlib.h>

#include "init.hpp"
#include "config.h"

unsigned int string2unsignedint(string inputstring)
{
  unsigned int outputint;
  istringstream ist(inputstring);
  ist >> outputint;
  return outputint;
}

float str2f(string inputstring)
{
  float outputfloat;
  istringstream ist(inputstring);
  ist >> outputfloat;
  return outputfloat;
}

Story::Story()
{
}

Story::~Story()
{
}

string Story::getFilename()
{
  return filename;
}

void Story::setFilename(string fn)
{
  filename=fn;
}

unsigned int  Story::getChance()
{
  return chance;
}

void Story::setChance(unsigned int c)
{
  if (c>100) c=100;
  chance=c;
}

EndStory::EndStory()
{
}

EndStory::~EndStory()
{
}

void EndStory::setEventServer(EventServer *events)
{
  es=events; 
}


void EndStory::execute(parameters)
{
#ifdef DEBUG
  cout << "Starting story nr "<< es->currentstory << endl;
#endif
  es->loadNewStory();
}

LoadObject::LoadObject(TextureLoader *tex)
{
  loadableobjectnr=0;
  texture=tex;
}

LoadObject::~LoadObject()
{
}

void LoadObject::setEventServer(EventServer *events)
{
  es=events; 
}

void LoadObject::execute(parameters)
{
}

void LoadObject::interpretString(string parameterstring)
{
#ifdef DEBUG
  cout <<"interpreting String for loadobject:" <<parameterstring << endl;
#endif
  int pos=0;
  parameters param;
  //interpret first parameter which is the objectname
  pos = parameterstring.find(' ');
  string objectname=parameterstring.substr(0,pos);
  parameterstring=parameterstring.substr(pos+1,parameterstring.length()-pos-1);

  //interpret second parameter which is the objectfilename
  pos = parameterstring.find(' ');
  string objectfilename=parameterstring.substr(0,pos);
  parameterstring=parameterstring.substr(pos+1,parameterstring.length()-pos-1);

  //TODO: someday we change the param in a template, that would solve this problem better.
  
  //TODO somewhere this object should be deleted at the end of the story !!!!

  LoadableObject *loadableOb;
  loadableOb = new LoadableObject(objectname,texture);
  loadableOb->setObjectFilename(objectfilename);
  cout << "making " << objectname << "..." <<endl;
  loadableOb->make();
#ifdef DEBUG
  cout << "adding " << objectname << "to eventserver" << endl;
#endif
  es->addClient(loadableOb);
}

void LoadObject::clearParameterList()
{
#ifdef DEBUG
  cout << "clearing parmeterlist for loadobject " << endl;
#endif
  parameterlist.clear();
  es->removeAllLoadableSubClients();
#ifdef DEBUG
  cout << "Cleared parameterlist for loadobject" << endl;
#endif
}

EventServer::EventServer(TextureLoader *tex):EventClient("server")
{
  texture=tex;
  currentstory=0;
  endstory = new EndStory();
  endstory->setEventServer(this);
  endstory->setName("endstory");
  addCommando(endstory);

  playSound =  new PlaySound();
  playSound->setName("playsound");
  addCommando(playSound);

  loadObject = new LoadObject(texture);
  loadObject->setEventServer(this);
  loadObject->setName("loadobject");
  addCommando(loadObject);
}

EventServer::~EventServer()
{
  delete endstory;
  delete playSound;
  delete loadObject;
}

void EventServer::openStoryFile(string filename)
{
#ifdef DEBUG
  cout << "search file to open..." << endl;
#endif
  filename="tuxsaver/stories/"+filename;
  filename=locate("data",filename.c_str()).latin1();

  //  filename=string(locate("data",filename.c_str()));
  string commandostring;
  string parameterstring;
  char line[255];
#ifdef DEBUG
  cout << "opening story file:" << filename.c_str() << "..." << endl;
#endif
  ifstream eventfile;
  eventfile.open(filename.c_str(),ios::in);
  while (! eventfile.eof() )
  {
    eventfile.getline(line,200);
    if (line!="") interpretString(line);
  }
#ifdef DEBUG
  cout << "closing story file" << endl;
#endif
  eventfile.close();
}

void EventServer::loadStoryList(string filename)
{
  char line[255];
  unsigned int c;
  Story st;
  totalchance=0;
#ifdef DEBUG
  cout << "search file to open..." << endl;
#endif
  filename="tuxsaver/stories/"+filename;
  filename=locate("data",filename.c_str()).ascii();
#ifdef DEBUG
  cout << "opening " << filename << "..." << endl;
#endif
  storylistfile.open(filename.c_str());
  while (! storylistfile.eof() )
  {
    storylistfile.getline(line,200,' ');
    st.setFilename(line);
    storylistfile.getline(line,200);
    c = string2unsignedint(line);
    st.setChance(c);
    totalchance=totalchance+c;
    storylist.push_back(st);
  }
  storylistfile.close();
}


void EventServer::loadNewStory()
{
#ifdef DEBUG
  cout << "loadNewStory"  << endl;
#endif
  worldtime=0;
  //make sure all lists are empty
  clearParameterLists();
#ifdef DEBUG
  cout << "lists cleared" << endl;
#endif
  
  //remove all texture which are loaded by the stories
  texture->removeTextures();

  //open next story list and fill the parameterlist
  unsigned int choose= chooseStory();
#ifdef DEBUG
  cout << "your next story will be" << choose << endl;
#endif
  openStoryFile(storylist[choose].getFilename());
}

//sequential
//   if (currentstory==storylist.size()) currentstory=0;
//   //make sure all lists are empty
//   clearParameterLists();
//   cout << "lists cleared" << endl;
//   //open next story list and fill the parameterlist
//   openStoryFile(storylist[currentstory].getFilename());
//   currentstory++;
//}

unsigned int EventServer::chooseStory()
{
  unsigned int storynr=0;
  unsigned int chancesum=0;

  srand( (unsigned int) time( NULL ));
  float ranf= (float(rand()))/(float(RAND_MAX));
  //ran is a number between 0 and totalchance
  ranf = ranf*totalchance;
  unsigned int ran = uint(ranf);
  vector<Story>::iterator i;
  for (i=storylist.begin();i!=storylist.end();i++) {
    chancesum=chancesum + i->getChance();
    if (chancesum>ran) {
      return storynr;
    }
    storynr++;
  }
  // only for compiler time warning
  return storynr;
}
