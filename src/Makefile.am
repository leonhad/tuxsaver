# Makefile.am for tuxsaver.
#

AM_CPPFLAGS = -UQT_NO_ASCII_CAST
METASOURCES = AUTO

INCLUDES = $(all_includes)
LDFLAGS = $(all_libraries) $(KDE_RPATH)
LDADD = $(LIB_KDEUI) -lkscreensaver -lm
bin_PROGRAMS = tuxsaver.kss

tuxsaver_kss_SOURCES = tuxsaverui.ui tuxsaver.cpp ac3d.h ac3dloader.cpp ac3dloader.h ac3dtexture.cpp ac3dtexture.h arm.cpp arm.hpp body.cpp body.hpp camera.cpp camera.hpp EventClient.cpp EventClient.hpp EventServer.cpp EventServer.hpp fishingline.cpp fishingline.hpp Follow.cpp Follow.hpp hat.cpp hat.hpp init.cpp init.hpp island.cpp island.hpp Jump.cpp Jump.hpp leftfoot.cpp leftfoot.hpp loadableobject.cpp loadableobject.hpp main.cpp Move.cpp Move.hpp object.cpp object.hpp objectloader.cpp Openmouth.cpp Openmouth.hpp penguin.cpp penguin.hpp playsound.cpp playsound.hpp rightfoot.cpp rightfoot.hpp setupdialog.h setupdialog.ui sunglasses.cpp sunglasses.hpp textureloader.cpp textureloader.hpp tuxsaver.hpp tuxsaverkss.cpp tuxsaverkss.hpp tuxsaversetup.cpp tuxsaversetup.h tuxsaversetup.hpp utils.cpp utils.hpp Visible.cpp Visible.hpp Walk.cpp Walk.hpp world.cpp world.hpp objectloader.h
tuxsaver_kss_LDADD = -lGLU -lGL -lkscreensaver $(LIB_QT) $(LIB_KDECORE) $(LDADD) $(LIB_KSYCOCA)

datadir = $(kde_datadir)/tuxsaver

desktop_DATA = tuxsaver.desktop
desktopdir = $(kde_appsdir)/System/ScreenSavers

EXTRA_DIST = $(desktop_DATA)

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/tuxsaver.pot

SUBDIRS = pics stories objects soundfiles
