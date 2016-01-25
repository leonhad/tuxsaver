#include <fstream>
#include <string>

#include "EventClient.hpp"
#include "playsound.hpp"
#include "loadableobject.hpp"
#include "textureloader.hpp"

class EventServer;

class EndStory : public commando
{
public:
  EndStory();
  ~EndStory();
  void execute(parameters);
  void setEventServer(EventServer*);
  EventServer *es;
};

class Story
{
public:
  Story();
  ~Story();
  unsigned int getChance();
  void setChance(unsigned int);
  string getFilename();
  void setFilename(string);
private:
  unsigned int chance;
  string filename;
};

class LoadObject : public commando
{
public:
  LoadObject(TextureLoader *tex);
  ~LoadObject();
  void execute(parameters);
  void setEventServer(EventServer*);
  EventServer *es;
  void interpretString(string parameterstring);
  vector<LoadableObject*> loadableObjectList;
  unsigned int loadableobjectnr;
  void clearParameterList(); 
  TextureLoader *texture;
};

class EventServer : public EventClient
{
public:
  EventServer(TextureLoader *tex);
  ~EventServer();
  void loadStoryList(string filename);
  ifstream storylistfile;

  void openStoryFile(string filename);
  
  unsigned int chooseStory();
  void loadNewStory();
  unsigned int currentstory;
  vector<Story> storylist;

  //we need this to findout next random story, we store this after loading the file
  unsigned totalchance;

  EndStory *endstory;
  PlaySound *playSound;
  LoadObject *loadObject;
  TextureLoader *texture;
};
