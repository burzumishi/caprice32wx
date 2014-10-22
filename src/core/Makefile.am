noinst_LIBRARIES = libcaprice32wxcore.a

libcaprice32wxcore_a_CPPFLAGS = -O2 -funroll-loops -ffast-math -fomit-frame-pointer -fno-strength-reduce -finline-functions \
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
			  -ldl -lm -lz

libcaprice32wxcore_a_SOURCES = \
	config_manager.cpp \
	crtc.cpp \
	crtc1.cpp \
	dsk.cpp \
	emulator.cpp \
	fdc_old.cpp \
	gatearray.cpp \
	glfuncs.cpp \
	IMG_savepng.cpp \
	input.cpp \
	ioport.cpp \
	memory.cpp \
	ppi.cpp \
	psg.cpp \
	render.cpp \
	renderData.cpp \
	snapshot.cpp \
	tape.cpp \
	vdu.cpp \
	video.cpp \
	z80.cpp \
	audioPlugin.h \
	dsk.h \
	glfunclist.h \
	input.h \
	ppi.h \
	cap32.h \
	crtc1.h \
	fdc_old.h \
	snapshot.h \
	video.h \
	cap32type.h \
	emulator.h \
	glfuncs.h \
	ioport.h \
	psg.h \
	crtc.h \
	error.h \
	tape.h \
	z80daa.h \
	config_manager.h \
	debug.h \
	IMG_savepng.h \
	memory.h \
	z80.h \
	CPCKeyDefs.h \
	gatearray.h \
	render.h \
	vdu.h

