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
#ifndef SM_DS_CONN_H
#define SM_DS_CONN_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include "dsConn_Intf.h"
#include "dsTypes.h"
#include "dsModuleLoad.h"
//---------------------------------------------------------------------------
namespace smds
{

class Database;
class DataTransfer;

//***********************************************************************
//******    DbEngine
//***********************************************************************
class DbEngine
{
private:
    shared_ptr<IModuleLoader>   mData;
public:
    CDFASTCALL DbEngine( shared_ptr<IModuleLoader> module_loader );

    Database_Ctor FASTCALL Database_Constructor() const     { return ( mData->GetCreateDataConnection() ); }
    Database_Dtor FASTCALL Database_Destructor() const      { return ( mData->GetDeleteDataConnection() ); }

    Database FASTCALL NewConnection( const std_string& connection_string );
};

//***********************************************************************
//******    Database
//***********************************************************************
class Database
{
private:
    class cDatabase_impl
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
    {
    private:
        // noncpyable
        cDatabase_impl( const cDatabase_impl& src );
        cDatabase_impl& operator = ( const cDatabase_impl& src );
    public:
        IDatabase           *mDatabase;
        DbEngine            mDbEngine;
        std_string          mConnectionString;

        CDFASTCALL cDatabase_impl( const DbEngine& transport_code, const std_string& connection_string )
            : mDatabase(0), mDbEngine(transport_code), mConnectionString(connection_string)
        {
        }
        CDFASTCALL ~cDatabase_impl()
        {
            mDbEngine.Database_Destructor()( mDatabase );
        }
    };

    shared_ptr<cDatabase_impl>       mData;
public:
    CDFASTCALL Database( const DbEngine& transport_code, const std_string& connection_string );
    CDFASTCALL ~Database();

    IDatabase * FASTCALL GetDatabase() const           { return ( mData->mDatabase ); }

    DataTransfer FASTCALL NewTransfer() const;
};

//***********************************************************************
//******    DataTransfer
//***********************************************************************
class DataTransfer
{
private:
    class cDataTransferData
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
    {
    private:
        // noncpyable
        cDataTransferData( const cDataTransferData& src );
        cDataTransferData& operator = ( const cDataTransferData& src );
    public:
        IDataProvider       *mTransfer;
        Database           mDatabase;

        CDFASTCALL cDataTransferData( const Database& database )
            : mTransfer(database.GetDatabase()->CreateDataProvider()), mDatabase(database)
        {
        }
        CDFASTCALL ~cDataTransferData()
        {
            mDatabase.GetDatabase()->DestroyDataProvider( mTransfer );
        }
    };

    shared_ptr<cDataTransferData>  mData;
public:
    CDFASTCALL DataTransfer( const Database& conn );
    CDFASTCALL ~DataTransfer();

    IDataProvider * FASTCALL GetDataTransfer() const           { return ( mData->mTransfer ); }
};

};
//---------------------------------------------------------------------------
#endif

