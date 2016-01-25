#include "tuxsaverkss.hpp"
#include "tuxsaver.hpp"

TuxSaverKSS::TuxSaverKSS(WId id) : KScreenSaver( id )
{
  setBackgroundColor( black );
  erase();
  saver = new TuxSaver();
  embed(saver);
  saver->show();
}

TuxSaverKSS::~TuxSaverKSS()
{
  delete saver;
}

