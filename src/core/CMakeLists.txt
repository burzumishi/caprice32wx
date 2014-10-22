# In this directory we build the static library of emulator core
cmake_minimum_required(VERSION 2.8)
project(Caprice32Core)

include_directories(..)

set(SOURCE_FILES
	# core
	config_manager.cpp
	crtc.cpp
	crtc1.cpp
	dsk.cpp
	emulator.cpp
	fdc_old.cpp
	gatearray.cpp
	input.cpp
	ioport.cpp
	memory.cpp
	ppi.cpp
	psg.cpp
	render.cpp
	renderData.cpp
	snapshot.cpp
	tape.cpp
	vdu.cpp
	video.cpp
	z80.cpp
	# We may further separate these into a toolkit lib...
	../misc/file/c_inifile.cpp
	../misc/file/filetools.cpp
	../misc/log.cpp
	../misc/synchro.cpp
)

add_library(Caprice32Core STATIC ${SOURCE_FILES})

target_link_libraries(Caprice32Core ${CMAKE_THREAD_LIB_INIT})

target_link_libraries(Caprice32Core stsound)
