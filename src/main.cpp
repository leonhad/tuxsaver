
#include <kapplication.h>
#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>
#include <kglobal.h>
#include <qmessagebox.h>
#include <qgl.h>
#include <kapplication.h>

#include "tuxsaverkss.hpp"
#include "tuxsaversetup.hpp"

extern "C"
{
  const char *kss_applicationName = "tuxsaver.kss";
  const char *kss_description = I18N_NOOP( "tuxsaver" );
  const char *kss_version = "2.2.0";
  
  KScreenSaver *kss_create(WId id)
  {
    KGlobal::locale()->insertCatalogue("tuxsaver");
    return new TuxSaverKSS(id);
  }
  
  QDialog *kss_setup()
  {
    KGlobal::locale()->insertCatalogue("tuxsaver");
    return new TuxSaverSetup();
  }
}
