caprice32wx_CFLAGS = -O2 -funroll-loops -ffast-math -fomit-frame-pointer -fno-strength-reduce -finline-functions \
			  -Wno-write-strings -Wno-unused-result \
			  $(WX_CFLAGS) \
			  $(SDL_CFLAGS) \
			  $(PORTAUDIO_CFLAGS) \
			  -I. \
			  -I@top_srcdir@ \
                          -I@top_srcdir@/src \
                          -I@top_srcdir@/src/core \
                          -I@top_srcdir@/src/asm \
                          -I@top_srcdir@/src/cli \
                          -I@top_srcdir@/src/misc \
                          -I@top_srcdir@/src/gui/IDE \
			  -ldl -lm -lz -s

caprice32wx_CXXFLAGS = $(caprice32wx_CFLAGS)
caprice32wx_CPPFLAGS = $(caprice32wx_CFLAGS)

caprice32wx_LDFLAGS = $(SDL_LDFLAGS) $(WX_LDFLAGS) $(PORTAUDIO_LDFLAGS) $(STSOUND_LDFLAGS) $(PTHREADS_LDFLAGS) -ldl -lm -lz

if USE_IDE
SUBDIRS = IDE
endif

bin_PROGRAMS = caprice32wx

caprice32wx_SOURCES = \
	CapriceAboutImpl.cpp \
	CapriceApp.cpp \
	CapriceInputSettingsImpl.cpp \
	CapriceRegistersDialogImpl.cpp \
	CapriceUI.cpp \
	CapriceWindowImpl.cpp \
	MemoryImpl.cpp \
	WXEmulator.cpp
	

include_HEADERS = \
CapriceAboutImpl.h  CapriceRegistersDialogImpl.h  CapriceWindowImpl.h  WXEmulator.h \
CapriceApp.h        CapriceInputSettingsImpl.h  CapriceUI.h                   MemoryImpl.h         WXLog.h

if USE_IDE
caprice32wx_SOURCES += CapriceIDE.cpp
include_HEADERS += CapriceIDE.h
endif

caprice32wx_LDADD = \
@top_srcdir@/src/aop/libcaprice32wxaop.a \
@top_srcdir@/src/misc/libcaprice32wxmisc.a \
$(NULL)

if WITH_ASM
caprice32wx_LDADD += \
@top_srcdir@/src/asm/libcaprice32wxasm.a \
$(NULL)
endif

if CLI
caprice32wx_LDADD += \
@top_srcdir@/src/cli/libcaprice32wxcli.a \
$(NULL)
endif

caprice32wx_LDADD += \
@top_srcdir@/src/core/libcaprice32wxcore.a \
$(NULL)

if USE_IDE
caprice32wx_LDADD += \
@top_srcdir@/src/gui/IDE/libcaprice32wxide.a \
$(NULL)
endif


