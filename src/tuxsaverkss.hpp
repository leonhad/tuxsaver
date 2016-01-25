
#ifndef TUXSAVERKSS_H
#define TUXSAVERKSS_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kapp.h>
#include <qwidget.h>

#include <qpushbutton.h>

#include <kscreensaver.h>

using namespace std;

#include "init.hpp"

#include "tuxsaver.hpp"

class TuxSaverKSS : public KScreenSaver
{
 public:
  TuxSaverKSS( WId id );
  ~TuxSaverKSS();
  
 private:
  TuxSaver *saver;
};

#endif
