/////////////////////////////////////////////////////////////////////////////
// Name:        frmPanel.cpp
// Purpose:     
// Author:      Sam
// Modified by: 
// Created:     20/04/2008 12:56:16
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

#include "frmPanel.h"

////@begin XPM images
////@end XPM images


/*!
 * frmPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( frmPanel, wxPanel )


/*!
 * frmPanel event table definition
 */

BEGIN_EVENT_TABLE( frmPanel, wxPanel )

////@begin frmPanel event table entries
////@end frmPanel event table entries

END_EVENT_TABLE()


/*!
 * frmPanel constructors
 */

frmPanel::frmPanel()
{
    Init();
}

frmPanel::frmPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, pos, size, style);
}


/*!
 * frmPanel creator
 */

bool frmPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
////@begin frmPanel creation
    SetParent(parent);
    CreateControls();
////@end frmPanel creation
    return true;
}


/*!
 * frmPanel destructor
 */

frmPanel::~frmPanel()
{
////@begin frmPanel destruction
////@end frmPanel destruction
}


/*!
 * Member initialisation
 */

void frmPanel::Init()
{
////@begin frmPanel member initialisation
    button1 = NULL;
    button2 = NULL;
    button3 = NULL;
    button4 = NULL;
////@end frmPanel member initialisation
}


/*!
 * Control creation for frmPanel
 */

void frmPanel::CreateControls()
{    
////@begin frmPanel content construction
    if (!wxXmlResource::Get()->LoadPanel(this, GetParent(), _T("ID_FRMPANEL")))
        wxLogError(wxT("Missing wxXmlResource::Get()->Load() in OnInit()?"));
    button1 = XRCCTRL(*this, "ID_BUTTON1", wxButton);
    button2 = XRCCTRL(*this, "ID_BUTTON2", wxButton);
    button3 = XRCCTRL(*this, "ID_BUTTON3", wxButton);
    button4 = XRCCTRL(*this, "ID_BUTTON4", wxButton);
////@end frmPanel content construction

    // Create custom windows not generated automatically here.
////@begin frmPanel content initialisation
////@end frmPanel content initialisation
}


/*!
 * Should we show tooltips?
 */

bool frmPanel::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap frmPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin frmPanel bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end frmPanel bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon frmPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin frmPanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end frmPanel icon retrieval
}
