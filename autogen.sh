#!/bin/sh

libtoolize
aclocal
autoconf
autoheader

ln -sf README.md README
ln -sf README.md NEWS
ln -sf README.md AUTHORS
ln -sf LICENSE COPYING

automake -a -c

if [ -f "configure" ]; then
	./configure --prefix=/opt/caprice32 \
	--with-wx-config="wx-config --version=2.8"
#	--with-lib765 \
#   	--with-stsound \
#   	--with-aylet \
#  	--with-ayemu \
#    	--with-wxwidget \
#    	--with-cli \
#    	--with-socket \
#    	--with-debugger \
#    	--with-ide \
#    	--with-asm \
#    	--disable-debug \
#    	--enable-filedrop \
#    	--disable-opengl

fi;

# Clean generated files:
# make distclean

# rm -rf ltmain.sh m4 missing install-sh config.sub config.guess compile INSTALL depcomp README NEWS COPYING AUTHORS aclocal.m4 autom4te.cache Makefile.in configure src/Makefile.in config.h.in~ config.log config.h stamp-h1 libtool config.lt Doxyfile config.status
# find . -iname Makefile.in -exec rm -v {} \;
