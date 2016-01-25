#ifndef _PLAYSOUND_HPP
#define _PLAYSOUND_HPP

#include "EventClient.hpp"

#include <kaudioplayer.h>
#include <kconfig.h>

extern KConfig *tuxSaverConf;

class PlaySound : public commando
{
public:
  PlaySound();
  ~PlaySound();
  void execute(parameters);
  void interpretString(string);
  unsigned int wavNr;
  vector<string> wavFileList;
  void clearParameterList();

  KAudioPlayer *audioplayer;
  bool soundEnabled;
  bool oceanSoundsEnabled;
  void addOceanSounds();
};

#endif //_PLAYSOUND_HPP
