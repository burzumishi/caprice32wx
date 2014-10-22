noinst_LIBRARIES = libcaprice32wxmisc.a

libcaprice32wxmisc_a_CPPFLAGS = -I@top_srcdir@/src $(SDL_CFLAGS) $(WX_CFLAGS)

libcaprice32wxmisc_a_SOURCES = \
	file/c_inifile.cpp  file/filetools.cpp \
	clock_gettime_stub.cpp  Desass.cpp  log.cpp  synchro.cpp  zip.cpp \
	file/c_bool.h  file/c_inifile.h  file/filetools.h \
	clock_gettime_stub.h  Desass.h  log.h  synchro.h  timer.h  zip.h

libcaprice32wxmisc_a_CPPFLAGS += -O2 -funroll-loops -ffast-math -fomit-frame-pointer -fno-strength-reduce -finline-functions -s  
