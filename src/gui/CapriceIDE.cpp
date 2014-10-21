/**
 *   $Id$
 *	 CapriceReloded an Amstrad CPC emulator
 *   Copyright (C) 2009  cpcsdk crew
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


#include "CapriceIDE.h"
#include "CapASM.h"
#include <iostream>

/**
 * Create the window designed by wxformbuilder,
 * then add specific code editor, htanks to wxstedit
 */
CapriceIDEImpl::CapriceIDEImpl(wxWindow* parent, WXEmulator* emulator) : 
  IDE(parent),
  emulator(emulator)
{

  
   m_mainSplitter = new wxSplitterWindow((wxWindow*)this, ID_STF_MAIN_SPLITTER);
   
   wxSTEditorOptions steOptions(STE_DEFAULT_OPTIONS);
   steOptions.GetMenuManager()->SetMenuOptionType(STE_MENU_NOTEBOOK, true);
   wxSTEditorOptions::SetGlobalDefaultFileName("newfile.asm");
   wxSTEditorOptions::SetGlobalDefaultFileExtensions("Z80 file (*.asm)|*.asm");

   m_mainSplitter->SetMinimumPaneSize(10);

   m_steNotebook = new wxSTEditorNotebook(
       m_mainSplitter, 
       wxID_ANY, 
       wxDefaultPosition, 
       wxDefaultSize,
       wxCLIP_CHILDREN);
   m_steNotebook->CreateOptions(steOptions);
  (void)m_steNotebook->InsertEditorSplitter(-1, wxID_ANY, _T("demo.asm"), true);
  
  m_steNotebook->UpdateAllItems();
  m_mainSplitter->Initialize(m_steNotebook);

}

/**
 * Destroy editor
 */
CapriceIDEImpl::~CapriceIDEImpl()
{
	delete m_steNotebook;
	m_steNotebook = NULL;
	delete m_mainSplitter;
	m_mainSplitter = NULL;
}



// Menu 
void CapriceIDEImpl::OnNew( wxCommandEvent& event )
{
  GetNotebook()->NewPage();
}

void CapriceIDEImpl::onOpen( wxCommandEvent& event )
{
  GetNotebook()->LoadFile(wxFileName(), _T(""));
}

void CapriceIDEImpl::onSave( wxCommandEvent& event )
{
  GetNotebook()->GetEditor()->SaveFile(false);
}

void CapriceIDEImpl::onSaveAs( wxCommandEvent& event )
{
  GetNotebook()->GetEditor()->SaveFile(true);

}

void CapriceIDEImpl::onClose( wxCommandEvent& event )
{
}

void CapriceIDEImpl::onExit( wxCommandEvent& event )
{
	this->Close();
}

/**
 * Launch the compilation of the selected source file.
 * The compilation is done with the file on disc.
 */
void CapriceIDEImpl::OnAssemble( wxCommandEvent& event)
{
  CapASM capAsm(emulator);
  std::string filename =  std::string(GetNotebook()->GetEditor()->GetFileName().GetFullName().mb_str());
  capAsm.Compile( filename.c_str());

}

