#include <kstddirs.h>

#include "tuxsaversetup.hpp"

TuxSaverSetup::TuxSaverSetup( QWidget* parent, const char* name, bool modal, WFlags fl )
{
#ifdef HAVE_CONFIG_H
  QString titleText=QString("TuxSaver ")+QString(VERSION);
  titleLabel->setText(titleText.ascii());
#endif

  loadHatDir();
  loadIslandDir();

  tuxSaverConf = new KConfig("tuxsaverrc",false,true,"config");
  loadConfiguration();  
}

TuxSaverSetup::~TuxSaverSetup()
{
  delete tuxSaverConf;
}

void TuxSaverSetup::loadHatDir()
{
  QDir objectDir;
  objectDir.setPath(locate("data","tuxsaver/objects/hats/"));
  hatListBox->insertStringList(objectDir.entryList(QDir::Files));
}

void TuxSaverSetup::loadIslandDir()
{
  QDir objectDir;
  objectDir.setPath(locate("data","tuxsaver/objects/islands/"));
  islandListBox->insertStringList(objectDir.entryList(QDir::Files));
}

void TuxSaverSetup::okButtonClicked()
{
  saveConfiguration();
  this->accept();
}

void TuxSaverSetup::cancelButtonClicked()
{
  this->reject();
}

void TuxSaverSetup::saveConfiguration()
{
  tuxSaverConf->setGroup("tuxsaver");
  if (blankScreenCheckBox->isChecked()) tuxSaverConf->writeEntry("blankScreen","yes"); else tuxSaverConf->writeEntry("blankScreen","no"); 
  tuxSaverConf->writeEntry("blankScreenTime",blankScreenTimeSlider->value());

  tuxSaverConf->setGroup("sea");
  if (waveSeaCheckBox->isChecked()) tuxSaverConf->writeEntry("waveSea","yes"); else tuxSaverConf->writeEntry("waveSea","no"); 
  tuxSaverConf->writeEntry("waveHeight",waveHeightSlider->value());

  if (seaTransparancyCheckBox->isChecked()) tuxSaverConf->writeEntry("seaTransparancy","yes"); else tuxSaverConf->writeEntry("seaTransparancy","no");
  tuxSaverConf->writeEntry("seaTransparancyLevel",seaTransparancySlider->value());

  tuxSaverConf->setGroup("sound");
  if (soundCheckBox->isChecked()) tuxSaverConf->writeEntry("sound","yes"); else tuxSaverConf->writeEntry("sound","no"); 
  if (oceanSoundsCheckBox->isChecked()) tuxSaverConf->writeEntry("oceanSounds","yes"); else tuxSaverConf->writeEntry("oceanSounds","no");

  tuxSaverConf->setGroup("hat");
  QString hatname= hatListBox->currentText();
  if (!hatname.isEmpty())
  {
    tuxSaverConf->writeEntry("hatName",hatname);
  }
  if (randomHatCheckBox->isChecked()) tuxSaverConf->writeEntry("randomHat","yes"); else tuxSaverConf->writeEntry("randomHat","no"); 

  tuxSaverConf->setGroup("island");
  QString islandname= islandListBox->currentText();
  if (!islandname.isEmpty())
  {
    tuxSaverConf->writeEntry("islandName",islandname);
  }
  if (waveIcebergCheckBox->isChecked()) tuxSaverConf->writeEntry("waveIceberg","yes"); else tuxSaverConf->writeEntry("waveIceberg","no");
}

void TuxSaverSetup::loadConfiguration()
{
  tuxSaverConf->setGroup("tuxsaver");
  if (tuxSaverConf->readEntry("blankScreen","no")=="yes") blankScreenCheckBox->setChecked(true); else blankScreenCheckBox->setChecked(false);  
  blankScreenTimeSlider->setValue(tuxSaverConf->readEntry("blankScreenTime","30").toInt());

  tuxSaverConf->setGroup("sea");
  if (tuxSaverConf->readEntry("waveSea","yes")=="yes") waveSeaCheckBox->setChecked(true); else waveSeaCheckBox->setChecked(false);

  waveHeightSlider->setValue(tuxSaverConf->readEntry("waveHeight","30").toInt());

  if (tuxSaverConf->readEntry("seaTransparancy","yes")=="yes") seaTransparancyCheckBox->setChecked(true); else seaTransparancyCheckBox->setChecked(false);
  seaTransparancySlider->setValue(tuxSaverConf->readEntry("seaTransparancyLevel","50").toInt());

  tuxSaverConf->setGroup("sound");
  if (tuxSaverConf->readEntry("sound","yes")=="yes") soundCheckBox->setChecked(true); else soundCheckBox->setChecked(false);
  if (tuxSaverConf->readEntry("oceanSounds","yes")=="yes") oceanSoundsCheckBox->setChecked(true); else oceanSoundsCheckBox->setChecked(false);

  tuxSaverConf->setGroup("hat");
  hatListBox->setSelected(hatListBox->findItem(tuxSaverConf->readEntry("hatName","christmashat.ac")),true);
  if (tuxSaverConf->readEntry("randomHat","yes")=="yes") randomHatCheckBox->setChecked(true); else randomHatCheckBox->setChecked(false);

  tuxSaverConf->setGroup("island");
  islandListBox->setSelected(islandListBox->findItem(tuxSaverConf->readEntry("islandName","iceberg_with_iglo.ac")),true);
  if (tuxSaverConf->readEntry("waveIceberg","yes")=="yes") waveIcebergCheckBox->setChecked(true); else waveIcebergCheckBox->setChecked(false);  

}

void TuxSaverSetup::openHowtoButtonClicked()
{
  KProcess *proc = new KProcess;
  *proc << "konqueror";
  *proc << locate("html","en/tuxsaver/storyhowto.html");
  proc->start();
}

void TuxSaverSetup::openHomePage(const QString &urlname)
{
  cout << "opening url: " << urlname << endl;
  KProcess *proc = new KProcess;
  *proc << "konqueror";
  *proc << urlname;
  proc->start();
}

//#include "tuxsaversetup.moc"