/////////////////////////////////////////////////////////////////////////////
// Name:        frmMain.cpp
// Purpose:     
// Author:      Sam
// Modified by: 
// Created:     20/04/2008 11:29:41
// RCS-ID:      
// Copyright:   Sam's copyright
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "frmMain.h"
#include "frmPanel.h"
#include "wxUtils.h"

////@begin XPM images
////@end XPM images


/*!
 * frmMain type definition
 */

IMPLEMENT_CLASS( frmMain, wxFrame )


/*!
 * frmMain event table definition
 */

BEGIN_EVENT_TABLE( frmMain, wxFrame )

////@begin frmMain event table entries
    EVT_MENU( XRCID("ID_MSOPEN"), frmMain::OnMSOPENClick )

    EVT_MENU( XRCID("ID_MSQUIT"), frmMain::OnMSQUITClick )

////@end frmMain event table entries

END_EVENT_TABLE()


/*!
 * frmMain constructors
 */

frmMain::frmMain()
{
    Init();
}

frmMain::frmMain( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*!
 * frmMain creator
 */

bool frmMain::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin frmMain creation
    SetParent(parent);
    CreateControls();
    Centre();
////@end frmMain creation
    return true;
}


/*!
 * frmMain destructor
 */

frmMain::~frmMain()
{
////@begin frmMain destruction
////@end frmMain destruction
}


/*!
 * Member initialisation
 */

void frmMain::Init()
{
////@begin frmMain member initialisation
    mMenuLine = NULL;
    mPanel1 = NULL;
////@end frmMain member initialisation
}


/*!
 * Control creation for frmMain
 */

void frmMain::CreateControls()
{    
////@begin frmMain content construction
    if (!wxXmlResource::Get()->LoadFrame(this, GetParent(), wxT("ID_FRMMAIN")))
        wxLogError(wxT("Missing wxXmlResource::Get()->Load() in OnInit()?"));
    mMenuLine = XRCCTRL(*this, "wxID_STATIC", wxStaticLine);
    mPanel1 = XRCCTRL(*this, "ID_PANEL1", wxPanel);
////@end frmMain content construction

    // Create custom windows not generated automatically here.
////@begin frmMain content initialisation
////@end frmMain content initialisation
}


/*!
 * Should we show tooltips?
 */

bool frmMain::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap frmMain::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin frmMain bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end frmMain bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon frmMain::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin frmMain icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end frmMain icon retrieval
}


/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MSQUIT
 */

void frmMain::OnMSQUITClick( wxCommandEvent& event )
{
    Close();
    event.Skip();
}


/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MSOPEN
 */

void frmMain::OnMSOPENClick( wxCommandEvent& event )
{
    //mPanel1->Destroy();
    //mPanel1 = 0;

    //frmPanel    *frm = wx::CreateForm<frmPanel>( this ); //->Show( true );
    //wxSizer     *sizer = GetSizer();

    //sizer->Add( frm, 1, wxGROW | wxALL, 0 );
    //sizer->RecalcSizes();
    //mPanel1 = frm;

    wx::DestroyForm( mPanel1 );
    mPanel1 = wx::CreateAttachedPanel<frmPanel>( this );
    event.Skip();
}
