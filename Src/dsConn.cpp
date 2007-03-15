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

  Please read the "readme" file in the root directory of this
  package for more copyright and license information.
****************************************************************************/
//---------------------------------------------------------------------------
#pragma hdrstop

#include "dsConn.h"
#include "dsExceptions.h"
//---------------------------------------------------------------------------
namespace ds
{

namespace
{

// Connection name to DLL map
struct ConnMapElement
{
    const char  *name;
    const char  *dll_name;
};

ConnMapElement  ConnMapArray[] =
{
    { "ADO", "smDS_ADOConn_b6.dll" },
    { "DAO", "smDS_DAOConn_b6.dll" },
    { "BDE", "smDS_BDEConn_b6.dll" },
    { "SAS", "SmDS_SASConn_d7.dll" },
    { 0, 0 }
};

};

//---------------------------------------------------------------------------

cDbEngine FASTCALL SelectDbEngine( const char *name )
{
    for ( int n = 0 ; ConnMapArray[n].name != 0 ; ++n )
        if ( std::strcmp( ConnMapArray[n].name, name ) == 0 )
            return ( cDbEngine( ConnMapArray[n].dll_name ) );
    throw eDllLoadError();
}

//***********************************************************************
//******    cDbEngine
//***********************************************************************
CDFASTCALL cDbEngine::cDbEngine( const char *dll_name )
    : mData(new cDbEngine_impl())
{
    mData->mDLL = ::LoadLibrary( dll_name );
    if ( mData->mDLL == 0 )
        throw eDllLoadError();
    mData->mDatabase_Ctor = reinterpret_cast<Database_Ctor>(::GetProcAddress( mData->mDLL, "_CreateDataConnection" ));
    mData->mDatabase_Dtor = reinterpret_cast<Database_Dtor>(::GetProcAddress( mData->mDLL, "_DeleteDataConnection" ));
    if ( mData->mDatabase_Ctor == 0 || mData->mDatabase_Dtor == 0 )
        throw eDllLoadError();
}

CDFASTCALL cDbEngine::~cDbEngine()
{
}

cDatabase FASTCALL cDbEngine::NewConnection( const ds_string& connection_string )
{
    return ( cDatabase( *this, connection_string ) );
}

//***********************************************************************
//******    cDatabase
//***********************************************************************
CDFASTCALL cDatabase::cDatabase( const cDbEngine& transport_code, const ds_string& connection_string )
    : mData( new cDatabase_impl( transport_code, connection_string ) )
{
    mData->mDatabase = transport_code.Database_Constructor()( connection_string.c_str() );
}

CDFASTCALL cDatabase::~cDatabase()
{
}

cDataTransfer FASTCALL cDatabase::NewTransfer() const
{
    return ( cDataTransfer( *this ) );
}

//***********************************************************************
//******    cDataTransfer
//***********************************************************************
CDFASTCALL cDataTransfer::cDataTransfer( const cDatabase& conn )
    : mData( new cDataTransferData( conn ) )
{
}

CDFASTCALL cDataTransfer::~cDataTransfer()
{
}

//---------------------------------------------------------------------------
};

