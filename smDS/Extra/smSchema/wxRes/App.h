/////////////////////////////////////////////////////////////////////////////
// Name:        App.h
// Purpose:     
// Author:      Sam
// Modified by: 
// Created:     20/04/2008 04:44:55
// RCS-ID:      
// Copyright:   Sam's copyright
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _APP_H_
#define _APP_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/xrc/xmlres.h"
#include "wx/image.h"
#include "frmMain.h"
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
////@end control identifiers

/*!
 * App class declaration
 */

class App: public wxApp
{    
    DECLARE_CLASS( App )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    App();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

    virtual int OnRun();
    virtual void HandleEvent( wxEvtHandler *handler, wxEventFunction func, wxEvent& event ) const;

////@begin App event handler declarations

////@end App event handler declarations

////@begin App member function declarations

////@end App member function declarations

////@begin App member variables
////@end App member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(App)
////@end declare app

#endif
    // _APP_H_
