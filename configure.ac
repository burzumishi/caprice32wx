#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

PACKAGE=caprice32wx

CAPRICE_MAJOR_VERSION=5
CAPRICE_MINOR_VERSION=0

VERSION=$CAPRICE_MAJOR_VERSION.$CAPRICE_MINOR_VERSION

AC_INIT([Caprice32WX], [5.0],
	[<antoniocao000@gmail.com>],
	[caprice32wx])

LT_INIT
LT_LANG([C++])

AC_CONFIG_SRCDIR([src/gui/CapriceUI.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_HOST
AC_CANONICAL_BUILD

AM_INIT_AUTOMAKE([-Wno-all -Wno-cast-align -Wno-unused-result -Wno-write-strings])

AC_DEFINE_UNQUOTED([PREFIX], ["/opt/caprice32wx/"], [Define to the root directory.])
AC_DEFINE_UNQUOTED([BINDIR], ["${prefix}/bin/"], [Define Executable Directory.])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LEX
AC_PROG_YACC

AC_CHECK_PROGS([DOXYGEN], [doxygen])
AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "${DOXYGEN}"])

AC_PROG_LIBTOOL
AC_PROG_AWK
AC_LANG([C++])
AC_LANG_PUSH([C++])
AC_SUBST(LIBTOOL_DEPS)
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Checks for libraries.
AC_CHECK_LIB([dl], [main])
AC_CHECK_LIB([z], [main])
AC_CHECK_LIB([SDL], [main])

# Checks for header files.
AC_CHECK_HEADERS([SDL/SDL.h stdint.h stdlib.h string.h unistd.h])

AM_OPTIONS_WXCONFIG
reqwx=2.8.0
WX_CONFIG_CHECK($reqwx, wxWin=1)
if test "$wxWin" != 1; then
	AC_MSG_ERROR([
		wxWidgets must be installed on your system.
 
		Please check that wx-config is in path, the directory
		where wxWidgets libraries are installed (returned by
		'wx-config --libs' or 'wx-config --static --libs' command)
		is in LD_LIBRARY_PATH or equivalent variable and
		wxWidgets version is $reqwx or above.
		])
fi

#
# Check for portaudio path
#
AC_ARG_WITH([pa-include],
AC_HELP_STRING([--with-pa-include],
[specify path to portaudio v2.0 include directory]),
[with_portaudio=$withval],
[with_portaudio=""])

PKG_CHECK_MODULES(PORTAUDIO, portaudio-2.0 >= 19)

#
#
#
if test -n "$with_portaudio"; then
PORTAUDIO_CFLAGS="-I$withval"
fi

#
# Check which APIs are available
#

have_oss=no
AC_CHECK_HEADERS([sys/soundcard.h linux/soundcard.h machine/soundcard.h], have_oss=yes)
if [[ $have_oss = "yes" ]] ; then
AC_CHECK_HEADER(pa_unix_oss.h, ,have_oss=no, [#include "portaudio.h"])
if [[ $have_oss = "yes" ]] ; then
AC_EGREP_HEADER([PaOSS_GetStreamInputDevice], [pa_unix_oss.h], , [have_oss=no])
if [[ $have_oss = "no" ]] ; then
AC_MSG_WARN([Missing PaOSS_GetStreamInputDevice support in pa_unix_oss.h]);
fi
fi
fi

AC_CHECK_HEADER(alsa/asoundlib.h, have_alsa=yes, have_alsa=no)
if [[ $have_alsa = "yes" ]] ; then
AC_CHECK_HEADER(pa_linux_alsa.h, ,have_alsa=no)
if [[ $have_alsa = "yes" ]] ; then
AC_EGREP_HEADER([PaAlsa_GetStreamInputCard], [pa_linux_alsa.h], , [have_alsa=no])
if [[ $have_alsa = "no" ]] ; then
AC_MSG_WARN([Missing PaAlsa_GetStreamInputCard support in pa_linux_alsa.h]);
fi
fi
fi

AC_CHECK_HEADER(CoreAudio/CoreAudio.h, have_coreaudio=yes, have_coreaudio=no)
if [[ $have_coreaudio = "yes" ]] ; then
AC_CHECK_HEADER(pa_mac_core.h, ,have_coreaudio=no, [#include "portaudio.h"])
if [[ $have_alsa = "yes" ]] ; then
AC_EGREP_HEADER([PaMacCore_GetStreamInputDevice], [pa_mac_core.h], , [have_support=no])
if [[ $have_support = "no" ]] ; then
AC_MSG_WARN([Missing support in pa_mac_core.h]);
fi
fi
fi

AC_CHECK_HEADER(portaudio.h, have_portaudio=yes, have_portaudio=no)
if [[ $have_portaudio = "yes" ]] ; then
AC_EGREP_HEADER([Pa_GetStreamHostApiType], [portaudio.h], , [have_portaudio=no])
if [[ $have_portaudio = "no" ]] ; then
AC_MSG_ERROR([Your version of portaudio does not include required Pa_GetStreamHostApiType function]);
fi
fi

#
# Set up to use the identified ones
#
have_support=no
AC_MSG_NOTICE([---------------------------------------])
AM_CONDITIONAL([USE_UNIX_OSS], [test "$have_oss" = yes])
if [[ $have_oss = "yes" ]] ; then
AC_MSG_NOTICE([Including support for OSS]);
#AC_DEFINE(PX_USE_UNIX_OSS)
have_support=yes
fi

AM_CONDITIONAL([USE_LINUX_ALSA], [test "$have_alsa" = yes])
if [[ $have_alsa = "yes" ]] ; then
AC_MSG_NOTICE([Including support for ALSA])
#AC_DEFINE(PX_USE_LINUX_ALSA)
have_support=yes
fi

AM_CONDITIONAL([USE_MAC_COREAUDIO], [test "$have_coreaudio" = yes])
if [[ $have_coreaudio = "yes" ]] ; then
AC_MSG_NOTICE([Including support for Coreaudio])
#AC_DEFINE(PX_USE_MAC_COREAUDIO)
have_support=yes
fi

if [[ $have_support = "no" ]] ; then
AC_MSG_ERROR([No supported mixer interfaces detected])
fi
AC_MSG_NOTICE([---------------------------------------])

#
# Enable PTHREADS
#

AC_ARG_ENABLE([pthreads],
AC_HELP_STRING([--enable-pthreads],
[Enable use of PThreads]),
[enable_pthreads=$enableval],
[enable_pthreads=""])

if test -n "$enable_pthreads"; then
PTHREADS_LDFLAGS="-lpthread"
AC_DEFINE([USE_PTHREADS], [--enable-pthreads], [Enable use SNA Media Player])
fi

#
# Enable SNAMP
#

AC_ARG_ENABLE([snamp],
AC_HELP_STRING([--enable-SNAMP],
[Enable use SNA Media Player]),
[with_enable=$enableval],
[with_enable=""])

if test -n "$enable_snamp"; then
AC_DEFINE([USE_SNAMP], [--enable-snamp], [Enable use SNA Media Player])
fi

#
# Enable STSOUND
#

AC_ARG_WITH([stsound],
AC_HELP_STRING([--with-stsound],
[With ST Sound Library]),
[with_stsound=$withval],
[with_stsound=""])

if test -n "$with_stsound"; then
AC_DEFINE([USE_STSOUND], [--with-stsound], [With ST Sound Library])
fi

#
# Enable DEBUG
#

AC_ARG_ENABLE([debug],
AC_HELP_STRING([--enable-debug],
[Enable Debugging]),
[enable_debug=$enableval],
[enable_debug=""])

if test -n "$enable_debug"; then
AC_DEFINE([USE_DEBUG], [--enable-debug], [Enable Debugging])
fi

#
# Enable IDE
#

AC_ARG_ENABLE([ide],
AC_HELP_STRING([--enable-ide],
[Enable GUI IDE]),
[enable_ide=$enableval],
[enable_ide=""])

AM_CONDITIONAL([USE_IDE], [test -n "$enable_ide"])

if test -n "$enable_ide"; then
AC_DEFINE([USE_IDE], [--enable-ide], [Enable GUI IDE])
fi

#
# Enable ASM
#

AC_ARG_WITH([asm],
AC_HELP_STRING([--with-asm],
[include Z80 ASM]),
[with_asm=$withval],
[with_asm=""])

AM_CONDITIONAL([WITH_ASM], [test -n "$with_asm"])

if test -n "$with_asm"; then
AC_DEFINE([WITH_ASM], [--with-asm], [include Z80 ASM])
fi

#
# Enable CLI
#

AC_ARG_WITH([cli],
AC_HELP_STRING([--with-cli],
[Enable CLI]),
[with_cli=$withval],
[with_cli=""])

AM_CONDITIONAL([CLI], [test -n "$with_cli"])

if test -n "$with_cli"; then
AC_DEFINE([CLI], [--with-cli], [Enable CLI])
fi


#
# CFLAGS CXXFLAGS CPPFLAGS LIBS
#

CPPFLAGS="$CPPFLAGS $WX_CPPFLAGS $PORTAUDIO_CFLAGS"
CXXFLAGS="$CXXFLAGS $WX_CXXFLAGS_ONLY $PORTAUDIO_CFLAGS -std=gnu++11"
CFLAGS="$CFLAGS $WX_CFLAGS_ONLY $PORTAUDIO_CFLAGS"
LIBS="$LIBS $WX_LIBS $PORTAUDIO_LIBS"

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UID_T
AC_TYPE_INT64_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_STRUCT_TIMEZONE

AX_CXX_COMPILE_STDCXX_11

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([atexit getcwd memset pow rint strcasecmp strcspn strncasecmp strrchr strtol strtoul])

AC_CONFIG_FILES([Makefile 
		 src/Makefile
		 src/aop/Makefile
		 src/asm/Makefile
		 src/cli/Makefile
		 src/core/Makefile
		 src/misc/Makefile
		 src/gui/IDE/Makefile
		 src/gui/Makefile
		 Doxyfile])

LT_OUTPUT
AC_OUTPUT

