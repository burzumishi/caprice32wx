/**
 *   $Id: CapriceApp.h 60 2008-11-25 17:08:52Z giot.romain $
 *   CapriceReloded an Amstrad CPC emulator
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


#ifndef INCLUDED_CAPRICEAPP_H
#define INCLUDED_CAPRICEAPP_H

#include <wx/wxprec.h>
#include <wx/cmdline.h>
#ifdef WINDOWS
  #define IPC
  #include <wx/ipc.h>
#endif
#ifndef WX_PRECOMP
       #include <wx/wx.h>
#endif

#include "CapriceWindowImpl.h"
#include "CapriceRegistersDialogImpl.h"
#include "WXEmulator.h"
#include "core/snapshot.h"

#if defined(IPC)
//We have compilation problems under Linux. Need to check
class wxSingleInstanceChecker;


class ipcCnx: public wxConnection
{
	public:
		bool OnPoke(const wxString& topic, const wxString& item, wxChar *data, int size, wxIPCFormat format)
		{
			switch (item[0]) {
        		case 'A': 
				{
					wxString s("Insert ");
				   	s << data << " into drive " << item;
					Emulator::getInstance()->logMessage(s.mb_str());
					Emulator::getInstance()->GetFDC()->insertA( (const char *) data); break;
				}
				case 'B': Emulator::getInstance()->GetFDC()->insertB( (const char *) data); break;

				case 'S': snapshot_load(*(Emulator::getInstance()), (const char *)data) ; break;
			}
    		return wxConnection::OnPoke(topic, item, data, size, format);
		}
};


class ipcServer: public wxServer
{
	public:
		wxConnectionBase* OnAcceptConnection(const wxString& topic) {
			return new ipcCnx();	
		}
};
#endif


class CapriceApp : public wxApp
{
public:
    virtual bool OnInit();
    virtual int  OnRun();
    virtual int  OnExit();
    virtual void OnInitCmdLine(wxCmdLineParser& parser);
    virtual bool OnCmdLineParsed(wxCmdLineParser& parser);


    CapriceWindowImpl   *frame ;

private:
    WXEmulator          *emulator ;

    //params
    bool        fullscreen ;
    bool        greenscreen ;
    bool        remanency ;
    long        intensity;
  bool    cli;

    wxString    drivea ;
    wxString    driveb ;
    wxString    tape ;
    wxString    snapshot ;  

#if defined(IPC)
	wxSingleInstanceChecker* wsic;
	ipcServer* commServer;
#endif
};
 
DECLARE_APP(CapriceApp);

static const wxCmdLineEntryDesc g_cmdLineDesc [] =
{

    { wxCMD_LINE_SWITCH, "h", "help", "displays help on the command line parameters", wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },

#if CLI
    { wxCMD_LINE_SWITCH, "c", "cli", "cli interface" },
#endif

    { wxCMD_LINE_SWITCH, "f", "fullscreen", "display Reloaded in full screen" },
    { wxCMD_LINE_SWITCH, "g", "greenscreen", "display Reloaded with a green screen" },
    { wxCMD_LINE_SWITCH, "r", "remanancy", "use remanancy" },
    { wxCMD_LINE_OPTION, "i", "intensity", "set intensity screen", wxCMD_LINE_VAL_NUMBER, wxCMD_LINE_PARAM_OPTIONAL  },
    
    { wxCMD_LINE_OPTION, "a", "drivea", "specify disk image to insert into drive A", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
    { wxCMD_LINE_OPTION, "b", "driveb", "specify disk image to insert into drive B", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
     
    { wxCMD_LINE_OPTION, "t", "tape", "specify tape image ", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
    { wxCMD_LINE_OPTION, "s", "snapshot", "specify snapshot image ", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },

    { wxCMD_LINE_NONE }
};
 
#endif // INCLUDED_CAPRICEAPP_H 
