# Caprice32wx - Amstrad CPC Emulator

```
(c) Copyright 1997-2004 Ulrich Doewich (Caprice32)
(c) Copyright 2008-2013 CPCSDK: CloudStrife, Krusty, PulkoMandy (Reloaded)
(c) Copyright 2014 Antonio Cao (Caprice32wx)
```

## WHAT IS IT?

**Caprice32wx** is a software emulator of the **Amstrad CPC 8bit** home computer series. The emulator faithfully imitates the **CPC464**, **CPC664**, and **CPC6128** models. By recreating the operations of all hardware components at a low level, the emulator achieves a high degree of compatibility with original CPC software. These programs or games can be run unmodified at real-time or higher speeds, depending on the emulator host environment.

**Reloaded** is based on a fork of **Caprice32**, but nearly every part was rewritten from scratch.

**Caprice32wx** is based on a fork of **Reloaded** by CPCSDK Team.


## REQUIREMENTS

You will need the following to successfully compile an executable:

 - [**Alsa**] (http://www.alsa-project.org) -> Advanced Linux Sound Arquitecture
 - [**Portaudio**] (http://portaudio.com) -> Audio I/O library
 - [**libstsound**] (http://cpcsdk.googlecode.com/svn/trunk/libstsound/) -> Audio Library emulating an AY-3-8912 Chipset
 - [**SDL**] (https://www.libsdl.org) -> Simple Direct Layer
 - [**wxWidgets**] (http://www.wxwidgets.org) -> Cross Platform GUI Library
 - [**CMake**] (http://www.cmake.org) -> CMake Build System
 - [**libpng**] (http://www.libpng.org) -> Graphics Library for taking screenshots (Optional)
 - **Python Audio Bindings**: python3-portaudio, python-portaudio python-alsa (can be installed from your distro's package manager)


### BUILD

Compilation for Linux and probably other Unix:

```	mkdir build
	cd build
	cmake .. -DCMAKE_BUILD_TYPE=Release
	make ; make install```


### USING THE SOURCE

The source for **Caprice32wx** is distributed under the terms of the **GNU General Public License (GNU GPL)**, which is included in this archive as **"LICENSE"**. Please make sure that you understand the terms and conditions of the license before using the source.

I encourage you to get involved in the project - please see the **Caprice32wx** pages on **GitHub** for contact details.


## COMMENTS OR READY TO CONTRIBUTE?

If you have suggestions, a bug report or even want to join the development team, please feel free to use one of the many contact methods presented on the **Caprice32wx** project page on **GitHub** - see the URL at the top.

Development is done at your request, if we don't know about bugs, we can't fix them! (and if we know, we may be too lazy to do it before someone asks).
