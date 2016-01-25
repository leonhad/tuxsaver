# This spec file was generated using Kpp
# If you find any problems with this spec file please report
# the error to ian geiser <geiseri@msoe.edu>
Summary:   TuxSaver
Name:      tuxsaver
Version:   1.0
Release:   1mdk
Copyright: GPL
Vendor:    koen muylkens <koen.muylkens@NOSPAMesat.kuleuven.ac.be>
Url:       http://www.esat.kuleuven.ac.be/~kmuylken

Packager:  koen muylkens <koen.muylkens@NOSPAMesat.kuleuven.ac.be>
Group:     ScreenSavers
Source:    tuxsaver-1.0.tar.gz
BuildRoot: %{_tmppath}/%{name}-buildroot 

%description
TuxSaver is a 3D screensaver for KDE 3.x
It show the life of tux living on an iceberg on the southpole.
It is possible to develop your own stories and objects. Please read the howto in the setupdialogbox for instructions.
%prep
%setup
CFLAGS="$RPM_OPT_FLAGS" CXXFLAGS="$RPM_OPT_FLAGS" ./configure \
		--prefix=/usr \
		--disable-debug \
                $LOCALFLAGS
%build
# Setup for parallel builds
numprocs=`egrep -c ^cpu[0-9]+ /proc/stat || :`
if [ "$numprocs" = "0" ]; then
  numprocs=1
fi

make -j$numprocs

%install
make install-strip DESTDIR=$RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/lib/menu
cat << EOF > $RPM_BUILD_ROOT/usr/lib/menu/tuxsaver.menu
?package(tuxsaver): needs="x11" kde_filename="tuxsaverscreensaver" section=".hidden/ScreenSavers" title="TuxSaver (GL)" icon="kscreensaver.png" command="tuxsaver.kss" kde_opt="\\\nActions=Setup;InWindow;Root\\\n[Desktop Action Setup]\\\nExec=tuxsaver.kss -setup\\\nName=Setup...\\\nIcon=kscreensaver\\\n[Desktop Action InWindow]\\\nExec=tuxsaver.kss -window-id %w\\\nName=Display in specified window\\\nNoDisplay=true\\\n[Desktop Action Root]\\\nExec=tuxsaver.kss -root\\\nName=Display in root window\\\nNoDisplay=true"
EOF

cd $RPM_BUILD_ROOT
find . -type d | sed '1,2d;s,^\.,\%attr(-\,root\,root) \%dir ,' > $RPM_BUILD_DIR/file.list.tuxsaver
find . -type f | sed 's,^\.,\%attr(-\,root\,root) ,' >> $RPM_BUILD_DIR/file.list.tuxsaver
find . -type l | sed 's,^\.,\%attr(-\,root\,root) ,' >> $RPM_BUILD_DIR/file.list.tuxsaver

%post
%{update_menus}

%postun
%{clean_menus}

%clean
rm -rf $RPM_BUILD_ROOT/*
rm -rf $RPM_BUILD_DIR/tuxsaver
rm -rf ../file.list.tuxsaver


%files -f ../file.list.tuxsaver
