libcaprice32wxaop_a_CPPFLAGS = -O2 -funroll-loops -ffast-math -fomit-frame-pointer -fno-strength-reduce -finline-functions -s  

noinst_LIBRARIES = libcaprice32wxaop.a

libcaprice32wxaop_a_CPPFLAGS = -I@top_srcdir@/src $(SDL_CFLAGS) $(WX_CFLAGS)

libcaprice32wxaop_a_SOURCES = \
portAudioAudioPlugin.cpp  portAudioAudioPlugin.h

if USE_LINUX_ALSA
libcaprice32wxaop_a_SOURCES += \
alsaAudioPlugin.cpp  alsaAudioPlugin.h 
endif
