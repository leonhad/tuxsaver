#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file '/home/koen/tuxsaver/src/tuxsaverui.ui'
**
** Created: Tue Dec 23 14:22:50 2003
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.2.3   edited May 19 14:22 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "tuxsaverui.h"

#include <qvariant.h>
#include <kdialog.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a tuxsaverUI as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
tuxsaverUI::tuxsaverUI( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "tuxsavercfg" );

    QWidget* privateLayoutWidget = new QWidget( this, "Layout2" );
    privateLayoutWidget->setGeometry( QRect( 5, 0, 255, 57 ) );
    Layout2 = new QGridLayout( privateLayoutWidget, 1, 1, KDialog::marginHint(), KDialog::spacingHint(), "Layout2"); 

    CheckBox1 = new QCheckBox( privateLayoutWidget, "CheckBox1" );

    Layout2->addWidget( CheckBox1, 0, 0 );

    Layout1 = new QHBoxLayout( 0, 0, KDialog::spacingHint(), "Layout1"); 

    OkayPushButton = new QPushButton( privateLayoutWidget, "OkayPushButton" );
    Layout1->addWidget( OkayPushButton );

    CancelPushButton = new QPushButton( privateLayoutWidget, "CancelPushButton" );
    Layout1->addWidget( CancelPushButton );

    Layout2->addLayout( Layout1, 1, 0 );
    languageChange();
    resize( QSize(257, 58).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
tuxsaverUI::~tuxsaverUI()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void tuxsaverUI::languageChange()
{
    setCaption( tr2i18n( "Screen Saver Config" ) );
    CheckBox1->setText( tr2i18n( "Set some setting" ) );
    OkayPushButton->setText( tr2i18n( "&OK" ) );
    CancelPushButton->setText( tr2i18n( "&Cancel" ) );
}

#include "tuxsaverui.moc"
