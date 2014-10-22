# In this directory we build the executable without gui (SNAMP)
cmake_minimum_required(VERSION 2.8)
project(SNAMP)

include_directories(..)

if(HAIKU)
	set (AudioPlugin ../gui_be/RAudio.h)
else(HAIKU)
	set (AudioPlugin ../aop/portAudioAudioPlugin.cpp)
endif(HAIKU)

add_executable(snamp WIN32 
	main.cpp
	${AudioPlugin}
)

add_dependencies(snamp Caprice32Core)
target_link_libraries(snamp Caprice32Core)

target_link_libraries(snamp ${CMAKE_THREAD_LIB_INIT})

if (NOT HAIKU)
	target_link_libraries(snamp portaudio)
endif (NOT HAIKU)
