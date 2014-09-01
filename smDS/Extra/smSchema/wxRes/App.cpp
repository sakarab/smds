/////////////////////////////////////////////////////////////////////////////
// Name:        App.cpp
// Purpose:     
// Author:      Sam
// Modified by: 
// Created:     20/04/2008 04:44:55
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
#include "wx/fs_zip.h"
////@end includes

#include "App.h"
#include "wxUtils.h"
#include "frmMain.h"

////@begin XPM images
////@end XPM images


/*!
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( App )
////@end implement app


/*!
 * App type definition
 */

IMPLEMENT_CLASS( App, wxApp )


/*!
 * App event table definition
 */

BEGIN_EVENT_TABLE( App, wxApp )

////@begin App event table entries
////@end App event table entries

END_EVENT_TABLE()


/*!
 * Constructor for App
 */

App::App()
{
    Init();
}


/*!
 * Member initialisation
 */

void App::Init()
{
////@begin App member initialisation
////@end App member initialisation
}

/*!
 * Initialisation for App
 */

bool App::OnInit()
{    
    bool    result;

    try
    {
////@begin App initialisation
	// Remove the comment markers above and below this block
	// to make permanent changes to the code.

	wxXmlResource::Get()->InitAllHandlers();
	wxFileSystem::AddHandler(new wxZipFSHandler);
	wxString archive = _T("smSchema.zip");
	wxString url = wxFileSystem::FileNameToURL(archive);
	wxXmlResource::Get()->Load(url);

#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif
	frmMain* mainWindow = new frmMain( NULL );
	mainWindow->Show(true);
////@end App initialisation

        // wx::CreateForm<frmMain>( 0 )->Show( true );
        result = true;
    }
    catch ( const wx::ExceptionBase& e )
    {
        ::wxMessageBox( e.wwhat(), wxT("Error") );
        result = false;
    }
    catch ( const std::exception& e )
    {
        ::wxMessageBox( boost::lexical_cast<std::wstring>(e.what()).c_str(), wxT("Error") );
        result = false;
    }
    catch ( ... )
    {
        ::wxMessageBox( wxT("Unknown Error"), wxT("Error") );
        result = false;
    }
    return result;
}

void App::HandleEvent( wxEvtHandler *handler, wxEventFunction func, wxEvent& event ) const
{
    try
    {
        wxApp::HandleEvent( handler, func, event );
    }
    catch ( const wx::ExceptionBase& e )
    {
        ::wxMessageBox( e.wwhat(), wxT("Error") );
        throw;
    }
    catch ( const std::exception& e )
    {
        ::wxMessageBox( boost::lexical_cast<std::wstring>(e.what()).c_str(), wxT("Error") );
        throw;
    }
    catch ( ... )
    {
        ::wxMessageBox( wxT("Unknown Error"), wxT("Error") );
        throw;
    }
}

int App::OnRun()
{
    int     result;

    try
    {
        result = wxApp::OnRun();
    }
    catch ( ... )
    {
        result = 1;
    }
    return result;
}


/*!
 * Cleanup for App
 */

int App::OnExit()
{    
////@begin App cleanup
	return wxApp::OnExit();
////@end App cleanup
}
