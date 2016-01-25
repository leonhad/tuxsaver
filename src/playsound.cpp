#include "playsound.hpp"

#include <sstream>

#include <kstddirs.h>

//TODO has to go to utils.hpp
float string2float(string inputstring)
{
  float outputfloat;
  istringstream ist(inputstring);
  ist >> outputfloat;
  return outputfloat;
}

PlaySound::PlaySound()
{
  wavNr=0;
  //load configuration
  tuxSaverConf->setGroup("sound");
  if (tuxSaverConf->readEntry("sound","yes")=="yes") soundEnabled=true; else soundEnabled=false;
  if (tuxSaverConf->readEntry("oceanSounds","yes")=="yes") oceanSoundsEnabled=true; else oceanSoundsEnabled=false;
}

PlaySound::~PlaySound()
{
}

void PlaySound::execute(parameters params)
{
  if (soundEnabled)
    {
      unsigned int n=uint(params[2]);
      QString wavfilename = "tuxsaver/sounds/"+QString(wavFileList[n].c_str());
      QString fullwavfilename=locate("data",wavfilename);
#ifdef DEBUG
      cout << "wavefile " << wavfilename << endl;
      cout << "playing wavfile " << fullwavfilename << endl;
#endif
      KAudioPlayer::play(fullwavfilename);
    }
}

//we make a seperate interpretSt0ring function for playsound because we need a string as a parameter in stead of a float.
void PlaySound::interpretString(string parameterstring)
{
#ifdef DEBUG
  cout <<"interpreting soundstring:" <<parameterstring << endl;
#endif
  int pos=0;
  parameters param;
  //interpret first parameter which is the starttime
  pos = parameterstring.find(' ');
  param.push_back(string2float(parameterstring.substr(0,pos)));
  parameterstring=parameterstring.substr(pos+1,parameterstring.length()-pos-1);

  //interpret second parameter which is the endtim
  pos = parameterstring.find(' ');
  param.push_back(string2float(parameterstring.substr(0,pos)));
  parameterstring=parameterstring.substr(pos+1,parameterstring.length()-pos-1);
  
  //we add the name of the wav file to the wavefilelist, and store its number in the parameterlist, so we can retrieve it later by using the number.
  param.push_back(wavNr);
  wavNr++;
  wavFileList.push_back(parameterstring);
  //add begintime,eindtime and objectnumber to parameterlist of follow
  addParameters(param);  
}

//we reimplement this function to clear the wavefilelist
void PlaySound::clearParameterList()
{
  parameterlist.clear();
  wavFileList.clear();
  wavNr=0;
  if (oceanSoundsEnabled)  addOceanSounds();
}

//add the oceansoundsample a few times to the list of sounds, so it gets played continously
void PlaySound::addOceanSounds()
{
  float n;
  parameters param;
  wavFileList.push_back("Ocean.wav");
  for (int i=0;i<20;i++)
    {
      n=float(i*16); //16 is ne length of the oceansample in seconds
      param.clear();
      param.push_back(n);
      param.push_back(n);
      param.push_back(float(wavNr));
      addParameters(param);
    }
  wavNr++;
}
