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

#include "pre_smDS.h"
#include "dsConn.h"
//---------------------------------------------------------------------------
namespace smds
{

//***********************************************************************
//******    DbEngine
//***********************************************************************
CDFASTCALL DbEngine::DbEngine( shared_ptr<IModuleLoader> module_loader )
    : mData(module_loader)
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

