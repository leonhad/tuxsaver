#ifndef TUXSAVERSETUP_H
#define TUXSAVERSETUP_H

#include <kconfig.h>
#include <qlistbox.h>
#include <qstring.h>
#include <qdir.h>
#include <kprocess.h>

#include <iostream>

#include "setupdialog.h"

#include <qcheckbox.h>
#include <qstring.h>
#include <qlabel.h>
#include <qslider.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace std;

class TuxSaverSetup: public SetupDialog
{
public:
    TuxSaverSetup( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
  ~TuxSaverSetup();

  KConfig *tuxSaverConf;  
  void okButtonClicked();
  void cancelButtonClicked();
  void openHowtoButtonClicked();
  void openHomePage(const QString &);

  void saveConfiguration();
  void loadConfiguration();
  void loadHatDir();
  void loadIslandDir();
};

#endif
