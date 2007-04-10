/****************************************************************************
  smds - the openSource Memory DataSet

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Please read the "Doc\License.txt" for more copyright and license
  information.
****************************************************************************/
//---------------------------------------------------------------------------
#ifndef __GNUG__
#pragma hdrstop
#endif

#include "uTables.h"
//---------------------------------------------------------------------------

//***********************************************************************
//******    tblLocation
//***********************************************************************
const ds::cFieldDef_     tblLocation_data::tblLocation_Fields[] =
{
    { 0, offsetof(tblLocation_map,LocationID_), "LocationID", ds::fkData, ds::ftInteger,  4 },
    { 1, offsetof(tblLocation_map,LocTypeID_),  "LocTypeID",  ds::fkData, ds::ftShort,    2 },
    { 2, offsetof(tblLocation_map,IsUser_),     "IsUser",     ds::fkData, ds::ftShort,    2 },
    { 3, offsetof(tblLocation_map,SerialNo_),   "SerialNo",   ds::fkData, ds::ftInteger,  4 },
    { 4, offsetof(tblLocation_map,Drive_),      "Drive",      ds::fkData, ds::ftString,   4 }
};

const ds::cFieldDefs_    tblLocation_data::tblLocation_FieldDef =
{
    sizeof(tblLocation_map),
    sizeof(tblLocation_Fields)/sizeof(tblLocation_Fields[0]),
    //"SELECT LocationID, LocTypeID, IsUser, SerialNo, Drive FROM %s %s",
    "LocationID, LocTypeID, IsUser, SerialNo, Drive",
    "tblLocation",
    tblLocation_Fields
};

const ds::cFieldDefs_& FASTCALL tblLocation_rec::GetFieldDefs()             { return ( tblLocation_FieldDef ); }

//***********************************************************************
//******    tblFiles
//***********************************************************************
const ds::cFieldDef_     tblFiles_data::tblFiles_Fields[] =
{
    { 0, offsetof(tblFiles_map,FileID_),       "FileID",       ds::fkData, ds::ftInteger,    4 },
    { 1, offsetof(tblFiles_map,PathID_),       "PathID",       ds::fkData, ds::ftInteger,    4 },
    { 2, offsetof(tblFiles_map,LongFileName_), "LongFileName", ds::fkData, ds::ftString,   255 },
    { 3, offsetof(tblFiles_map,fSize_),        "fSize",        ds::fkData, ds::ftInteger,    4 },
    { 4, offsetof(tblFiles_map,fDate_),        "fDate",        ds::fkData, ds::ftDateTime,   8 },
    { 5, offsetof(tblFiles_map,Description_),  "Description",  ds::fkData, ds::ftString,   255 },
    { 6, offsetof(tblFiles_map,zipID_),        "zipID",        ds::fkData, ds::ftInteger,    4 },
};

const ds::cFieldDefs_    tblFiles_data::tblFiles_FieldDef =
{
    sizeof(tblFiles_map),
    sizeof(tblFiles_Fields)/sizeof(tblFiles_Fields[0]),
    //"SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM tblFiles",
    "tblFiles",
    tblFiles_Fields
};

const ds::cFieldDefs_& FASTCALL tblFiles_rec::GetFieldDefs()                { return ( tblFiles_FieldDef ); }

/*
int FASTCALL tblFiles_rec::GetFileID() const                                { return ( ReadInteger( tblFiles_Fields[0] ) ); }
void FASTCALL tblFiles_rec::SetFileID( int value )                          { WriteInteger( tblFiles_Fields[0], value ); }
int FASTCALL tblFiles_rec::GetPathID() const                                { return ( ReadInteger( tblFiles_Fields[1] ) ); }
void FASTCALL tblFiles_rec::SetPathID( int value )                          { WriteInteger( tblFiles_Fields[1], value ); }
ds_string FASTCALL tblFiles_rec::GetLongFileName() const                    { return ( ReadString( tblFiles_Fields[2] ) ); }
void FASTCALL tblFiles_rec::SetLongFileName( const ds_string& value )       { WriteString( tblFiles_Fields[2], value ); }
void FASTCALL tblFiles_rec::SetLongFileName( const char *value )            { WriteString( tblFiles_Fields[2], value ); }
int  FASTCALL tblFiles_rec::GetfSize() const                                { return ( ReadInteger( tblFiles_Fields[3] ) ); }
void FASTCALL tblFiles_rec::SetfSize( int value )                           { WriteInteger( tblFiles_Fields[3], value ); }
ds::cDateTime FASTCALL tblFiles_rec::GetfDate() const                       { return ( ReadDate( tblFiles_Fields[4] ) ); }
void FASTCALL tblFiles_rec::SetfDate( const ds::cDateTime& value )          { WriteDate( tblFiles_Fields[4], value ); }
ds_string FASTCALL tblFiles_rec::GetDescription() const                     { return ( ReadString( tblFiles_Fields[5] ) ); }
void FASTCALL tblFiles_rec::SetDescription( const ds_string& value )        { WriteString( tblFiles_Fields[5], value ); }
void FASTCALL tblFiles_rec::SetDescription( const char *value )             { WriteString( tblFiles_Fields[5], value ); }
int  FASTCALL tblFiles_rec::GetzipID() const                                { return ( ReadInteger( tblFiles_Fields[6] ) ); }
void FASTCALL tblFiles_rec::SetzipID( int value )                           { WriteInteger( tblFiles_Fields[6], value ); }
*/
//---------------------------------------------------------------------------

