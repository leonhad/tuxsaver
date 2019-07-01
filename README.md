# Tux Saver

For more info see the howto in the setup dialog box of tuxsaver.

## Instalation

To install tuxsaver, make sure you have kde 3.x and have OpenGL configured.
Including the development libraries.

- for Mandrake, Redhat:

tar -xzvf tuxsaver-x.tar.gz
cd tuxsaver-x
./configure --prefix=/usr      (change /usr to the location of your
kde installation)
make
make install

- for Suse:

tar -xzvf tuxsaver-x.tar.gz
cd tuxsaver-x
./configure --prefix=/opt/kde3     (change /usr to the location of your
kde installation)
make
make install

## How to make your own story

See the storyhowto.html file included in tuxsaver. There's a link in
the setupdialog.

## How to make you own hat

Use ac3d to draw new objects like hats.
Put the .ac-file in '/usr/share/apps/tuxsaver/objects/hats' and they
will be added to the list of hats.

## How to make you own island

Use ac3d to draw new objects like islands.
Put the .ac-file in '/usr/share/apps/tuxsaver/objects/islands' and they
will be added to the list of islands.

## Licensing

This software is released under the GNU Lesser General Public License v3.0 (LGPLv3).
Additionally, Autoconf includes a licensing exception in some of its
source files.

For more licensing information, see
<http://www.gnu.org/licenses/gpl-faq.html>.
