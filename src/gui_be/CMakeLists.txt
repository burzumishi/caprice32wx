# In this directory we build the Haiku GUI

# TODO we replicate a lot of the src/gui dir in here. Cleanup !
include_directories(..)
include_directories(keymap)

add_executable(caprice32wx
	RWin.cpp
	REmulator.cpp
	RApp.cpp
	keymap/KeyboardLayout.cpp
	keymap/KeyboardLayoutView.cpp
	keymap/KeymapWindow.cpp
	keymap/Keymap.cpp
	keymap/Keymap2.cpp
)

add_dependencies(caprice32wx Caprice32Core)
target_link_libraries(caprice32wx Caprice32Core)

target_link_libraries(caprice32wx stsound be game tracker)
