/////////////////////////////////////////////////////////////////////////////
// Name:        frmMain.h
// Purpose:     
// Author:      Sam
// Modified by: 
// Created:     20/04/2008 11:29:41
// RCS-ID:      
// Copyright:   Sam's copyright
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FRMMAIN_H_
#define _FRMMAIN_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/xrc/xmlres.h"
#include "wx/frame.h"
#include "wx/statline.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class wxStaticLine;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_FRMMAIN 10000
#define SYMBOL_FRMMAIN_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxMINIMIZE_BOX|wxMAXIMIZE_BOX|wxCLOSE_BOX
#define SYMBOL_FRMMAIN_TITLE _("frmMain")
#define SYMBOL_FRMMAIN_IDNAME ID_FRMMAIN
#define SYMBOL_FRMMAIN_SIZE wxSize(400, 300)
#define SYMBOL_FRMMAIN_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * frmMain class declaration
 */

class frmMain: public wxFrame
{    
    DECLARE_CLASS( frmMain )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    frmMain();
    frmMain( wxWindow* parent, wxWindowID id = SYMBOL_FRMMAIN_IDNAME, const wxString& caption = SYMBOL_FRMMAIN_TITLE, const wxPoint& pos = SYMBOL_FRMMAIN_POSITION, const wxSize& size = SYMBOL_FRMMAIN_SIZE, long style = SYMBOL_FRMMAIN_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_FRMMAIN_IDNAME, const wxString& caption = SYMBOL_FRMMAIN_TITLE, const wxPoint& pos = SYMBOL_FRMMAIN_POSITION, const wxSize& size = SYMBOL_FRMMAIN_SIZE, long style = SYMBOL_FRMMAIN_STYLE );

    /// Destructor
    ~frmMain();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin frmMain event handler declarations

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MSOPEN
    void OnMSOPENClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MSQUIT
    void OnMSQUITClick( wxCommandEvent& event );

////@end frmMain event handler declarations

////@begin frmMain member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end frmMain member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin frmMain member variables
    wxStaticLine* mMenuLine;
    wxPanel* mPanel1;
////@end frmMain member variables
};

#endif
    // _FRMMAIN_H_
