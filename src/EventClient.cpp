
#include "EventClient.hpp"

#include "init.hpp" 
//#include "utils.hpp"
#include <sstream>
#include "config.h"


//has to go to utils.hpp
float string2fl(string inputstring)
{
  float outputfloat;
  istringstream ist(inputstring);
  ist >> outputfloat;
  return outputfloat;
}

//COMMANDO
commando::commando()
{
}

commando::~commando()
{
}

string commando::getName()
{
  return name;
}

void commando::setName(string comname)
{
  name=comname;
}

void commando::printName()
{
  cout << "my name is " << name << endl;
}

void commando::addParameters(parameters params)
{
  parameterlist.push_back(params);
}

//virtual function, must be implemented in the command object
void commando::execute(parameters)
{
}

vector<parameters> commando::searchParameterList(float startt,float endt) {
  vector<parameters> temp;
  vector<parameters>::iterator j;
  for(j=parameterlist.begin();j!=parameterlist.end();j++) {
    vector<float> temp2 = *j;
    float stt = temp2[0];
    float ett = temp2[1];
    if (ett<=endt || stt>=startt) temp.push_back(temp2);
  }
  return temp;
}

void commando::setParameterList(vector<parameters> newlist) {
  parameterlist=newlist;
}

void commando::interpretString(string parameterstring)
{
  parameters param;
  int pos=0;
  string firststring;
  string reststring;
  pos = parameterstring.find(' ');
  while(pos!=-1) {
    firststring=parameterstring.substr(0,pos);
    reststring=parameterstring.substr(pos+1,parameterstring.length()-pos-1);
    param.push_back(string2fl(firststring));
    parameterstring=reststring;
    //find next ' '
    pos = parameterstring.find(' ');
  }
  param.push_back(string2fl(parameterstring));
  //add parameters to parameterlist
  addParameters(param);
}

void commando::clearParameterList()
{
  parameterlist.clear();
}

//EVENTCLIENT
EventClient::EventClient(string eventname)
{
  name=eventname;
  setLoadable(false);
}

EventClient::~EventClient()
{
}

void EventClient::setName(string eventname)
{
  name=eventname;
}

string EventClient::getName()
{
  return name;
}

void EventClient::addCommando(commando *com)
{
#ifdef DEBUG
  cout << "commando  : " << com->getName() << endl;
#endif
  commandolist.push_back(com);
}


//execute all commandos in commandolist
//and start executing the subeventclients
void EventClient::execute()
{
  //this is true if we executed a command in the past, so we remember that we have to remove it.
  bool past=false;
  vector<parameters>::iterator p;
  //execute all commandos
  vector<commando*>::iterator i;
  vector<parameters>::iterator j;
  // unused
  //vector<float>::iterator k;
  for (i=commandolist.begin();i!=commandolist.end();i++) {
    //      cout << "execute" << getName()<< ":" << (*i)->getName() <<endl;
    if ( (*i)->parameterlist.size() > 0) {
      past=false;
      for (j=(*i)->parameterlist.begin();j!=(*i)->parameterlist.end();j++) {
        //if time is between begin and end time excute the command
        if ( (worldtime>=(*j)[0]) && (worldtime<(*j)[1]) ) {
          //cout << getName() << ":" << (*i)->getName() << " between: " << (*j)[0] << " " << (*j)[1] << endl;
          (*i)->execute((*j));
        }
        //if end time is in the past, execute it and erase
        if ( worldtime>(*j)[1]) {
          //cout << getName() << ":" << (*i)->getName() << " between: " << (*j)[0] << " " << (*j)[1] << endl;
          (*i)->execute((*j));
          past=true;
          p=j;
        }
      }
      //if we executed a command in the past, we must
      // remove the parameters from the list after execution
      //only remove the parameters if not worldtime=0, cause if
      //not we delete the endstory command ,which we just executed
      //and started a new story with a new endstory command
      if (past&&(worldtime!=0)) (*i)->parameterlist.erase(p);
    }
  }
  //execute all subEventclients
  vector<EventClient*>::iterator c;
  for (c=subclientlist.begin();c!=subclientlist.end();c++) {
    (*c)->execute();
  }
}

void EventClient::addParameters(string commandoname,parameters params)
{
  vector<commando*>::iterator i;
  for (i=commandolist.begin();i!=commandolist.end();i++) {
    if ((*i)->getName()==commandoname) {
      (*i)->addParameters(params);
      break;
    }
  }
}

void EventClient::printParameters()
{
  vector<commando*>::iterator i;
  vector<parameters>::iterator j;
  vector<float>::iterator k;
  for (i=commandolist.begin();i!=commandolist.end();i++) {
    cout << "--- parmeterlist for " << (*i)->getName() << " ---" << endl;
    for (j=(*i)->parameterlist.begin();j!=(*i)->parameterlist.end();j++) {
      for (k=j->begin();k!=j->end();k++) {
        cout << "|" << *k ;
      }
      cout << endl;
    }
  }
}

void EventClient::interpretString(string inputstring)
{
  bool done=false;
  string commandostring;
  string parameterstring;
  int pos =inputstring.find(' ');
  commandostring=inputstring.substr(0,pos);
  parameterstring=inputstring.substr(pos+1,inputstring.length()-pos-1);
#ifdef DEBUG
  cout << commandostring << ":" << parameterstring << "." << endl;
#endif

  // we search the commandostring in the subclientlist
  vector<EventClient*>::iterator i;
  for (i=subclientlist.begin();i!=subclientlist.end();i++) {
    if ((*i)->getName()==commandostring) {
#ifdef DEBUG
      cout << "commandostring: " << commandostring << " found, it's an object" << endl;
#endif
      //parameterstring doorgeven aan object (*i)
      (*i)->interpretString(parameterstring);
      done=true;
      break;
    }
  }

  // we didn't find the commandostring in the object list, we search for
  // it in the commandolist
  if (done==false) {
    vector<commando*>::iterator j;
    for (j=commandolist.begin();j!=commandolist.end();j++) {
      if ((*j)->getName()==commandostring) {
#ifdef DEBUG
        cout << "commandostring: " << commandostring << " found, it's a command" << endl;
#endif
        //parameterstring doorgeven aan object (*i)
        (*j)->interpretString(parameterstring);
        done=true;
        break;
      }
    }
  }
#ifdef DEBUG
  printParameters();
#endif
}

void EventClient::addClient(EventClient *client)
{
  subclientlist.push_back(client);
  client->setMasterClient(*this);
}

void EventClient::removeSubClient(EventClient *client)
{
#ifdef DEBUG
  cout << "removing " << client <<  client->getName() << endl;
#endif

  //remove all subclients
  vector<EventClient*>::iterator i;
  for(i=client->subclientlist.begin();i!=client->subclientlist.end();i++)
    {
      client->removeSubClient(*i);   
    }
  //remove client from list
  //  i = find(subclientlist.begin(), subclientlist.end(), client);
  for(i=subclientlist.begin();i!=subclientlist.end();i++)
    {
      if ( (*i)==client ) break;  
    }
  subclientlist.erase(i);
  //delete object
  delete client;
  if (client) cout << "could not delete client" << endl;
 
#ifdef DEBUG
  cout << "removed" << endl;
#endif 
}

void EventClient::removeAllLoadableSubClients()
{
#ifdef DEBUG
  cout << "removing all loadable subclients " << endl;
#endif
  vector<EventClient*>::iterator i;

  i=subclientlist.begin();
  unsigned int n=0;
  while(n<subclientlist.size())
    { 
#ifdef DEBUG   
      cout << "going to see if this is a loadable sublcient " << (*i) << endl;
#endif
      if ((*i)->isLoadable())
	{
#ifdef DEBUG
	  cout << "removing loadable subclient "<< (*i)->getName() << endl;
#endif
	  removeSubClient(*i);
	}
      i++;
      n++;
    }
}

bool EventClient::isLoadable()
{
  return loadable;
}

void EventClient::setLoadable(bool b)
{
  loadable=b;
}

void EventClient::setMasterClient(EventClient &client)
{
  master = &client;
}

EventClient* EventClient::getMaster() {
  return master;
}

vector<parameters> EventClient::searchParameterList(string commandostring,float startt,float endt) {
  vector<commando*>::iterator j;
  vector<parameters> temp;
  bool done = true;
  j = commandolist.begin();
  while(j!=commandolist.end() && done) {
    if ((*j)->getName()==commandostring) done=false;
    else j++;
  }
  temp=(*j)->searchParameterList(startt,endt);
  return temp;
}

//clear the parameterlist of all commando's and alle subclients
void EventClient::clearParameterLists()
{
  //clear all subEventclients
  vector<EventClient*>::iterator c;
  for (c=subclientlist.begin();c!=subclientlist.end();c++) {
    (*c)->clearParameterLists();
  }
  vector<commando*>::iterator i;
  for (i=commandolist.begin();i!=commandolist.end();i++) {
#ifdef DEBUG
    cout << "clearing parameter list of " << (*i)->getName() << " in  " << getName() << endl;
#endif
    (*i)->clearParameterList();
  }
}

commando* EventClient::returnCommando(string commandostring) {
  vector<commando*>::iterator j;
  bool done = true;
  j = commandolist.begin();
  while(j!=commandolist.end() && done) {
    if ((*j)->getName()==commandostring) done=false;
    else j++;
  }
  return (*j);
}

EventClient* EventClient::searchEventClient(string evname)
{
  EventClient *outputev;
  if (name==evname) return this;
  else {
    int pos = evname.find(' ');
    evname=evname.substr(pos+1,evname.length()-pos-1);

    vector<EventClient*>::iterator c;
    for (c=subclientlist.begin();c!=subclientlist.end();c++) {
      outputev=(*c)->searchEventClient(evname);
      if (outputev!=NULL) return outputev;
    }
    return NULL;
  }
}

EventClient* EventClient::getClient(unsigned int clientnr)
{
  if (clientnr<subclientlist.size()) return subclientlist[clientnr]; else return NULL;
}

void EventClient::makeAllSubClients()
{
  cout << "making sublclient:" << getName() << endl;
  vector<EventClient*>::iterator i;
  for (i=subclientlist.begin();i!=subclientlist.end();i++)
    {
      (*i)->make();
      (*i)->makeAllSubClients();
    }
}

void EventClient::make()
{
}
