# ifndef _EVENTCLIENT_H
# define _EVENTCLIENT_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef vector<float> parameters;

class commando
{
 public:
  commando();
  virtual ~commando();
  void setName(string commandoname);
  string getName();
  void addParameters(parameters);
  virtual void execute(parameters);
  void setParameterList(vector<parameters>);
  void printName();
  vector<parameters> searchParameterList(float,float);
  string name;
  vector<parameters> parameterlist;
  virtual void interpretString(string parameterstring);
  virtual void clearParameterList();
};

class EventClient
{
 public:
  EventClient(string eventname);
  virtual ~EventClient();
  void setName(string eventname);
  string getName();
  void addCommando(commando *com);
  void interpretString(string commandostring);
  void addParameters(string commandoname,parameters params);
  void printParameters();
  void execute();
  void addClient(EventClient *subclient);
  void removeSubClient(EventClient *subclient);
  void removeAllLoadableSubClients();
  void setMasterClient(EventClient &client);
  commando* returnCommando(string commandostring);
  EventClient* getMaster();
  vector<parameters> searchParameterList(string commando,float,float);
  void clearParameterLists();
  EventClient* searchEventClient(string evname);

  virtual void make();
  EventClient* getClient(unsigned int clientnr);
  void makeAllSubClients();
  bool isLoadable();
  void setLoadable(bool b);
 private:
  string name;
  vector<commando*> commandolist;
  vector<EventClient*> subclientlist;
  EventClient* master;
  bool loadable;

};
# endif // _EVENTCLIENT_H
