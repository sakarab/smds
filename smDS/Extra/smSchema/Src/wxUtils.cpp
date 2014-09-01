/////////////////////////////////////////////////////////////////////////////
// Name:        wxUtils.cpp
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

#include <cstring>
#include "wxUtils.h"

namespace wx
{

//********************************************************
//******    LogException
//********************************************************
LogException::LogException( const wxChar *message )
    : mMessage( new wxChar[wxStrlen( message ) + 1] )
{
    wxStrcpy( mMessage.get(), message );
}

//********************************************************
//******    LogException
//********************************************************
void LogExceptioner::DoLog( wxLogLevel level, const wxChar *szString, time_t t )
{
    if ( level == wxLOG_FatalError || level == wxLOG_Error )
        throw LogException( szString );
    if ( mOldLog )
        static_cast<LogExceptioner *>(mOldLog)->DoLog( level, szString, t );
}

void LogExceptioner::DoLogString( const wxChar *, time_t )
{
}

//********************************************************
//******    Free Functions
//********************************************************

}; // namespace wx

