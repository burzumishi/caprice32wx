/**
 *   $Id: CapriceApp.cpp 60 2008-11-25 17:08:52Z giot.romain $
 *	 Reloded an Amstrad CPC emulator
 *   Copyright (C) 2008  cpcsdk crew
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */  

/* #include "config.h" */

#include <memory>
#include <iostream>

#include <wx/splash.h>
#include <wx/snglinst.h>
#include <wx/utils.h>

#include "CapriceApp.h"
#include "CapriceWindowImpl.h"
#include "CapriceInputSettingsImpl.h"


#include "core/cap32.h"
#include "core/debug.h"
#include "core/fdc.h"
#include "core/dsk.h"
#include "core/snapshot.h"
#include "core/tape.h"
#include "misc/file/filetools.h"

using std::shared_ptr;
using std::make_shared;

#if CLI
extern "C" {
#include "cparser.h"
#include "cparser_priv.h"
#include "cparser_token.h"
#include "cparser_tree.h"
  }

  cparser_t parser;
  extern cparser_node_t cparser_root;
  wxFrame *frameClone;
  Emulator *emulatorClone;
#endif

#if WITH_ASM
#include "asm/CapASM.h"
CapASM *capAsm ;
#endif

#include "WXVideo.cpp"


#ifdef __WXMAC__
#include <ApplicationServices/ApplicationServices.h>
#endif

#include "WXLog.h"

#if SOUND_OUTPUT == SOUND_OUTPUT_PortAudio
#include "aop/portAudioAudioPlugin.h"
#elif SOUND_OUTPUT == SOUND_OUTPUT_Alsa
#include "aop/alsaAudioPlugin.h"
#endif

//TODO destroy emulator when finishing

IMPLEMENT_APP(CapriceApp)

	wxSplashScreen* splash ;

// This is executed upon startup, like 'main()' in non-wxWidgets programs.
bool CapriceApp::OnInit()
{
    // call default behaviour (mandatory)
    if (!wxApp::OnInit())
        return false;

    WXLog::init();

    SetAppName("reloaded");

#if defined(IPC)
	// Check if another instance is running
	const wxString name = wxString::Format("reloaded-%s", wxGetUserId().mb_str());
	wsic = new wxSingleInstanceChecker(name);
	if ( wsic->IsAnotherRunning() )
	{
		// Another instance is running - parse CLI and send to it.
		wxClient wc;
		ipcCnx* CNX = (ipcCnx*)wc.MakeConnection("localhost","~/.reloadedcommand","loadthings");
		if(CNX == NULL) {
			wxLogError("Unable to connect to running instance !");
			return false;
		}

		// We have a connexion, send our params
		if(!drivea.IsEmpty())
			CNX->Poke("A",(char*)drivea.mb_str());
		if(!driveb.IsEmpty())
			CNX->Poke("B",(char*)driveb.mb_str());

		// Exit now.
		return false;
	}
#endif

	wxImage::AddHandler(new wxPNGHandler);

	//Splash screen managment
	wxBitmap bitmap;
	if (bitmap.LoadFile( "./logo.png", wxBITMAP_TYPE_PNG))
    {
		splash = new wxSplashScreen(bitmap,
		                wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
		                6000, NULL, -1, wxDefaultPosition, wxDefaultSize,
		                wxSIMPLE_BORDER|wxSTAY_ON_TOP);
    }
	wxYield();

#if defined(IPC)
	commServer = new ipcServer();
	commServer->Create("~/.reloadedcommand");
#endif

#if SOUND_OUTPUT == SOUND_OUTPUT_PortAudio
    auto audio = shared_ptr<AudioPlugin>(new PortAudioAudioPlugin());
#elif SOUND_OUTPUT == SOUND_OUTPUT_Alsa
    auto audio = shared_ptr<AudioPlugin>(new AlsaAudioPlugin());
#elif SOUND_OUTPUT == SOUND_OUTPUT_Null
    auto audio = shared_ptr<AudioPlugin>(new NullAudioPlugin());
#endif

	auto video = make_shared<WXDoubleLinePlugin>();

	//Create emulator and IHM
	WXEmulator::createInstance(video, audio);
	emulator = WXEmulator::getInstance();
	
	#if WITH_ASM
	capAsm = new CapASM(emulator);
	#endif

#ifndef NDEBUG
	InfoLogMessage("Compile in Debug mode");
#endif
	InfoLogMessage("Initialization done\n");
	return true ; 
}


int CapriceApp::OnExit()
{
#if defined(IPC)
	delete commServer;
	commServer = NULL;
	delete wsic;
	wsic = NULL;
#endif

	delete emulator;
	emulator = NULL;

	// The only way to exit the emulator is to delete the window.
	// So when we get here, the window is already gone.
#ifdef __WXMSW__
	delete frame;
	frame = NULL;
#endif
#if CLI
  	if (cli)
  	{
		cout << "Quit parser" << endl ;
		cparser_quit(&parser) ;
  	}
#endif
	return 0;
}


int CapriceApp::OnRun()
{
	// Creating the frame must be done here and not in OnInit, or else wxWidgets will not close the app 
	// with the window. See http://docs.wxwidgets.org/2.8/wx_wxappoverview.html#wxappshutdownoverview
	frame = new CapriceWindowImpl(emulator);
	frame->Show(true);
	frame->Raise();

  #if CLI
    frameClone = frame ;
  #endif

#ifdef __WXMAC__ 
	ProcessSerialNumber PSN;
	GetCurrentProcess(&PSN);
	TransformProcessType(&PSN,kProcessTransformToForegroundApplication);
#endif

    //Set command line options
    if (greenscreen) emulator->GetConfig()->scr_tube = Renderer::GreenMode;
    if (intensity!=-1) emulator->GetConfig()->scr_intensity = intensity;
    if (remanency) emulator->GetConfig()->scr_remanency = true;

    if(emulator->Init())
    {
        #ifdef USE_DEBUGGER
        InitDebug();
        #endif

        //do the initialisations
        if (!drivea.IsEmpty()) emulator->GetFDC()->insertA( (const char *) drivea.mb_str());
        if (!driveb.IsEmpty()) emulator->GetFDC()->insertB( (const char *) driveb.mb_str());

        if (!snapshot.IsEmpty()) snapshot_load( *emulator,  (const char *)snapshot.c_str()) ;

        if (!tape.IsEmpty()) emulator->GetTape()->tape_insert((const char *)tape.c_str()) ; 

        if (fullscreen) emulator->GetRenderer().ToggleFullScreen();		

		// Initializing the keymap is done in the input settings window...
		CapriceInputSettingsImpl* InputSettingsWindow = new CapriceInputSettingsImpl(frame);
		InputSettingsWindow -> applySettings();
		delete InputSettingsWindow;
    }

    delete splash;

    SetTopWindow(frame);

    // generate an initial idle event to start things
    wxIdleEvent event;
    //event.SetEventObject(&frame->getPanel());
    //frame->getPanel().AddPendingEvent(event);

    // start the main loop
    return wxApp::OnRun();
}






void CapriceApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    parser.SetDesc (g_cmdLineDesc);
    // must refuse '/' as parameter starter or cannot use "/path" style paths
    parser.SetSwitchChars ("-");
}

#if CLI
 /**
 * CLI in a thread
 * @todo use locks and co
 */
void* cliRout(void* args)
{ 

    parser.cfg.root = &cparser_root;
    parser.cfg.ch_complete = '\t' ;
    parser.cfg.ch_erase ='\b' ;
    parser.cfg.ch_del = 127 ;
    parser.cfg.ch_help = '?' ;
    parser.cfg.flags =  0 ;
    strcpy(parser.cfg.prompt, "caprice>> ");
    //parser.cfg.fd = STDOUT_FILENO ;
    cparser_io_config(&parser);

    //Load cli interface
    if (CPARSER_OK != cparser_init(&parser.cfg, &parser))
    {
      std::cout << "Fail to initialize parser." << endl;
      return false;
    }
    cparser_run(&parser) ;

    //TODO quit application
    frameClone->Close();

	return args;
}
#endif


bool CapriceApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
	intensity = -1 ;
	greenscreen = false ;
	remanency = false ;
  cli = false;

    fullscreen = parser.Found("f");
	greenscreen = parser.Found("g");
	remanency = parser.Found("r");
	parser.Found("i", &intensity);

	parser.Found("a", &drivea);
	parser.Found("b", &driveb);
	parser.Found("t", &tape);
	parser.Found("s", &snapshot);

#if CLI
  if (parser.Found("c"))
  {
    cli = true ;
    pthread_t threadcli;
    if (pthread_create (&threadcli, NULL, cliRout, NULL) < 0)
    {
      std::cout << "Fail to create cli thread." << endl ;
      return false ;
    }
  }

#endif

    return true;
}


