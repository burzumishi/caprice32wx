noinst_LIBRARIES = libcapricesnamp.a

libcapricesnamp_a_CPPFLAGS = -I/usr/include -I@top_srcdir@/src $(SDL_CFLAGS) $(WX_CFLAGS) $(PORTAUDIO_CFLAGS)

libcapricesnamp_a_LDFLAGS = $(SDL_LDFLAGS) $(WX_LDFLAGS) $(PORTAUDIO_LDFLAGS) -ldl -lpthread -lportaudio

libcapricesnamp_a_SOURCES = \
	main.cpp

libcapricesnamp_a_CPPFLAGS += -O2 -funroll-loops -ffast-math -fomit-frame-pointer -fno-strength-reduce -finline-functions -s  
