# In this directory we build the executable with wxWidgets gui
cmake_minimum_required(VERSION 2.8)
project(Caprice32WXGUI)

# wxWidgets
set(wxWidgets_CONFIGURATION 'wxmsw')
find_package(wxWidgets COMPONENTS aui adv core base REQUIRED)
include( "${wxWidgets_USE_FILE}" )

include_directories(..)

add_executable(caprice32wx
	CapriceAboutImpl.cpp
	CapriceApp.cpp
	CapriceInputSettingsImpl.cpp
	CapriceRegistersDialogImpl.cpp
	CapriceUI.cpp
	CapriceWindowImpl.cpp
	MemoryImpl.cpp
	../aop/portAudioAudioPlugin.cpp
#	../aop/alsaAudioPlugin.cpp
	WXEmulator.cpp
	../misc/Desass.cpp
)

add_dependencies(caprice32wx Caprice32Core)
target_link_libraries(caprice32wx Caprice32Core)

target_link_libraries(caprice32wx ${wxWidgets_LIBRARIES})

target_link_libraries(caprice32wx ${CMAKE_THREAD_LIB_INIT})

target_link_libraries(caprice32wx portaudio)
