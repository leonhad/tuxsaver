/****************************************************************************
** Form interface generated from reading ui file '/home/koen/tuxsaver/src/setupdialog.ui'
**
** Created: Tue Dec 23 14:22:54 2003
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.2.3   edited May 19 14:22 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QTabWidget;
class QWidget;
class QGroupBox;
class QLabel;
class QCheckBox;
class QSlider;
class QPushButton;
class QButtonGroup;
class QListBox;
class QListBoxItem;
class KURLLabel;

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    SetupDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~SetupDialog();

    QTabWidget* tab;
    QWidget* tuxSaverTab;
    QGroupBox* groupBox2_2;
    QLabel* textLabel1;
    QCheckBox* blankScreenCheckBox;
    QSlider* blankScreenTimeSlider;
    QGroupBox* groupBox3;
    QPushButton* openStoryHowtoButton;
    QWidget* soundTab;
    QCheckBox* soundCheckBox;
    QCheckBox* oceanSoundsCheckBox;
    QWidget* seaTab;
    QGroupBox* groupBox2;
    QCheckBox* waveSeaCheckBox;
    QSlider* waveHeightSlider;
    QLabel* wavelevel;
    QButtonGroup* buttonGroup1;
    QCheckBox* seaTransparancyCheckBox;
    QLabel* translevel;
    QSlider* seaTransparancySlider;
    QWidget* tab_2;
    QListBox* islandListBox;
    QCheckBox* waveIcebergCheckBox;
    QWidget* hatTab;
    QCheckBox* randomHatCheckBox;
    QListBox* hatListBox;
    QWidget* aboutTab;
    QLabel* aboutLabel;
    QLabel* titleLabel;
    QLabel* picturelabel;
    KURLLabel* homepageurl;
    QPushButton* okbutton;
    QPushButton* cancelbutton;

public slots:
    virtual void okButtonClicked();
    virtual void cancelButtonClicked();
    virtual void openHowtoButtonClicked();
    virtual void openHomePage(const QString&);

protected:
    QGridLayout* SetupDialogLayout;
    QGridLayout* tuxSaverTabLayout;
    QVBoxLayout* layout20;
    QGridLayout* soundTabLayout;
    QVBoxLayout* layout22;
    QGridLayout* seaTabLayout;
    QVBoxLayout* layout21;
    QGridLayout* tabLayout;
    QGridLayout* hatTabLayout;
    QGridLayout* aboutTabLayout;
    QVBoxLayout* layout27;
    QHBoxLayout* layout6;
    QHBoxLayout* layout8;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;

};

#endif // SETUPDIALOG_H
