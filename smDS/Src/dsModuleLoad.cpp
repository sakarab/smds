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
#include "pre_smDS.h"
#include "dsModuleLoad.h"
//---------------------------------------------------------------------------
namespace smds
{
    //***********************************************************************
    //******    ModuleLoader
    //***********************************************************************
    ModuleLoader::ModuleLoader( const spSharedLibrary& dll )
        : mDll_Guard(dll)
    {
        mDatabase_Ctor = mDll_Guard->GetProcAddressT<Database_Ctor>( "_CreateDataConnection" );
        mDatabase_Dtor = mDll_Guard->GetProcAddressT<Database_Dtor>( "_DeleteDataConnection" );
    }

    Database_Ctor ModuleLoader::GetCreateDataConnection()
    {
        return mDatabase_Ctor;
    }

    Database_Dtor ModuleLoader::GetDeleteDataConnection()
    {
        return mDatabase_Dtor;
    }

    spModuleLoader GetOsModuleLoader( const std_char *dll_name )
    {
        return spModuleLoader( new ModuleLoader( LoadDll( dll_name ) ) );
    }

    //=======================================================================
    //======    DbDriver
    //=======================================================================
    DbDriver::DbDriver( const spSharedLibrary& dll )
        : mDll_Guard( dll )
    {
        mCreateDataConnection = dll->GetProcAddressT<Database_Ctor>( "_CreateDataConnection" );
        mDeleteDataConnection = dll->GetProcAddressT<Database_Dtor>( "_DeleteDataConnection" );
    }

    DbDriver::DbDriver( const std_char *dll_name )
        : DbDriver( LoadDll( dll_name ) )
    {
    }

    //=======================================================================
    //======    DbConnection
    //=======================================================================
    DbConnection::DbConnection( const spDbDriver& driver, const std_char* connection_string )
        : mDriver( driver ), mDatabase( driver->CreateDataConnection( connection_string ) )
    {
    }

    DbConnection::DbConnection( const spSharedLibrary& dll, const std_char* connection_string )
        : DbConnection( std::make_shared<DbDriver>( dll ), connection_string )
    {
    }

    DbConnection::DbConnection( const std_char* dll_name, const std_char* connection_string )
        : DbConnection( LoadDll( dll_name ), connection_string )
    {
    }

    DbConnection::~DbConnection()
    {
        mDriver->DeleteDataConnection( mDatabase );
    }

} // namespace smds
