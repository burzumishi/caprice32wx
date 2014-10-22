#The editor code is based on wxstedit

noinst_LIBRARIES = libcaprice32wxide.a 

AM_CXXFLAGS = -I@top_srcdir@/src -I@top_srcdir@/src/gui/IDE/include $(WX_CFLAGS) $(SDL_CFLAGS) $(PORTAUDIO_CFLAGS)

libcaprice32wxide_a_CPPFLAGS = -I@top_srcdir@/src -I@top_srcdir@/src/gui/IDE/include $(WX_CFLAGS) $(SDL_CFLAGS) $(PORTAUDIO_CFLAGS)

libcaprice32wxide_a_SOURCES = \
                            stedit/precomp.cpp \
                            stedit/steart.cpp \
                            stedit/stedit.cpp \
                            stedit/stedlgs.cpp \
                            stedit/steexprt.cpp   \
                            stedit/stefindr.cpp  \
                            stedit/steframe.cpp \
                            stedit/stelangs.cpp  \
                            stedit/stemenum.cpp  \
                            stedit/stenoteb.cpp  \
                            stedit/steopts.cpp \
                            stedit/steprefs.cpp  \
                            stedit/steprint.cpp  \
                            stedit/steshell.cpp \
                            stedit/stesplit.cpp  \
                            stedit/stestyls.cpp \
                            stedit/stedlgs.wdr      \
                            stedit/stedlgs_wdr.cpp \
			stedit/wxext.cpp

