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

#include "dsConn.h"
#include "dsExceptions.h"
//---------------------------------------------------------------------------
namespace smds
{

namespace
{

// Use this define until how dlltool woks is found.

#if defined (__GNUG__ )
    #define CREATE_DATA_CONNECTION      "CreateDataConnection"
    #define DELETE_DATA_CONNECTION      "DeleteDataConnection"
#else
    #define CREATE_DATA_CONNECTION      "_CreateDataConnection"
    #define DELETE_DATA_CONNECTION      "_DeleteDataConnection"
#endif


// Connection name to DLL map
struct ConnMapElement
{
    const char  *name;
    const char  *dll_name;
};

ConnMapElement  ConnMapArray[] =
{
    { "ADO",  "smDS_ADOConn_b6.dll" },
    { "DAO",  "smDS_DAOConn_b6.dll" },
    { "BDE",  "smDS_BDEConn_b6.dll" },
    { "SAS",  "SmDS_SASConn_d7.dll" },
#if defined(__BORLANDC__)
    { "ODBC", "SmDS_ODBCConn_b6.dll" },
#elif ( _MSC_VER == 1310 )
    { "ODBC", "SmDS_ODBCConn_v7.dll" },
#elif ( _MSC_VER == 1400 )
    { "ODBC", "SmDS_ODBCConn_v8.dll" },
#elif defined (__GNUG__ )
//    { "ODBC", "ODBC_Conn_gcc.dll" },
    { "ODBC", "smDS_ODBCConn_cbx.dll" },
#endif
    { 0, 0 }
};

};

//---------------------------------------------------------------------------

DbEngine FASTCALL SelectDbEngine( const char *name )
{
    for ( int n = 0 ; ConnMapArray[n].name != 0 ; ++n )
        if ( std::strcmp( ConnMapArray[n].name, name ) == 0 )
            return ( DbEngine( ConnMapArray[n].dll_name ) );
    throw eDllLoadError();
}

//***********************************************************************
//******    DbEngine
//***********************************************************************
CDFASTCALL DbEngine::DbEngine( const char *dll_name )
    : mData(new cDbEngine_impl())
{
    mData->mDLL = ::LoadLibrary( dll_name );
    if ( mData->mDLL == 0 )
        throw eDllLoadError();
    mData->mDatabase_Ctor = reinterpret_cast<Database_Ctor>(::GetProcAddress( mData->mDLL, CREATE_DATA_CONNECTION ));
    mData->mDatabase_Dtor = reinterpret_cast<Database_Dtor>(::GetProcAddress( mData->mDLL, DELETE_DATA_CONNECTION ));
    if ( mData->mDatabase_Ctor == 0 || mData->mDatabase_Dtor == 0 )
        throw eDllLoadError();
}

CDFASTCALL DbEngine::~DbEngine()
{
}

Database FASTCALL DbEngine::NewConnection( const ds_string& connection_string )
{
    return ( Database( *this, connection_string ) );
}

//***********************************************************************
//******    Database
//***********************************************************************
CDFASTCALL Database::Database( const DbEngine& transport_code, const ds_string& connection_string )
    : mData( new cDatabase_impl( transport_code, connection_string ) )
{
    mData->mDatabase = transport_code.Database_Constructor()( connection_string.c_str() );
}

CDFASTCALL Database::~Database()
{
}

DataTransfer FASTCALL Database::NewTransfer() const
{
    return ( DataTransfer( *this ) );
}

//***********************************************************************
//******    DataTransfer
//***********************************************************************
CDFASTCALL DataTransfer::DataTransfer( const Database& conn )
    : mData( new cDataTransferData( conn ) )
{
}

CDFASTCALL DataTransfer::~DataTransfer()
{
}

//---------------------------------------------------------------------------
};

