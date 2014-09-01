/////////////////////////////////////////////////////////////////////////////
// Name:        
// Purpose:     
// Author:      Sam
// Modified by: 
// Created:     20/04/2008 04:45:43
// RCS-ID:      
// Copyright:   Sam's copyright
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _APP_RESOURCES_H_
#define _APP_RESOURCES_H_

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

class AppResources
{
public:
    AppResources() {}

/*!
 * Resource functions
 */

////@begin AppResources resource functions
    /// Menu creation function for ID_MENU
    static wxMenu* CreateMenuMENU();

    /// Retrieves bitmap resources
    static wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    static wxIcon GetIconResource( const wxString& name );
////@end AppResources resource functions

};

#endif
    // _APP_RESOURCES_H_
