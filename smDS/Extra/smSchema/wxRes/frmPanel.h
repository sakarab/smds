/////////////////////////////////////////////////////////////////////////////
// Name:        frmPanel.h
// Purpose:     
// Author:      Sam
// Modified by: 
// Created:     20/04/2008 12:56:16
// RCS-ID:      
// Copyright:   Sam's copyright
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FRMPANEL_H_
#define _FRMPANEL_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/xrc/xmlres.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_FRMPANEL 10001
#define SYMBOL_FRMPANEL_STYLE wxNO_BORDER|wxTAB_TRAVERSAL
#define SYMBOL_FRMPANEL_TITLE _("frmPanel")
#define SYMBOL_FRMPANEL_IDNAME ID_FRMPANEL
#define SYMBOL_FRMPANEL_SIZE wxSize(300, 200)
#define SYMBOL_FRMPANEL_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * frmPanel class declaration
 */

class frmPanel: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( frmPanel )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    frmPanel();
    frmPanel( wxWindow* parent, wxWindowID id = SYMBOL_FRMPANEL_IDNAME, const wxPoint& pos = SYMBOL_FRMPANEL_POSITION, const wxSize& size = SYMBOL_FRMPANEL_SIZE, long style = SYMBOL_FRMPANEL_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_FRMPANEL_IDNAME, const wxPoint& pos = SYMBOL_FRMPANEL_POSITION, const wxSize& size = SYMBOL_FRMPANEL_SIZE, long style = SYMBOL_FRMPANEL_STYLE );

    /// Destructor
    ~frmPanel();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin frmPanel event handler declarations

////@end frmPanel event handler declarations

////@begin frmPanel member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end frmPanel member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin frmPanel member variables
    wxButton* button1;
    wxButton* button2;
    wxButton* button3;
    wxButton* button4;
////@end frmPanel member variables
};

#endif
    // _FRMPANEL_H_
