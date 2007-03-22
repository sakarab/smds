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
#include <ssport.h>
#include <windows.h>
#include "dsConn_Intf.h"
#include <dsTypes.h>
#include "dsSmartPtr.h"
//---------------------------------------------------------------------------
namespace ds
{

class cDatabase;
class cDataTransfer;

//***********************************************************************
//******    cDbEngine
//***********************************************************************
class cDbEngine
{
private:
    class cDbEngine_impl
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
    {
    private:
        NO_COPY_CTOR(cDbEngine_impl);
        NO_COPY_OPER(cDbEngine_impl);
    public:
        HMODULE                 mDLL;
        Database_Ctor           mDatabase_Ctor;
        Database_Dtor           mDatabase_Dtor;

        CDFASTCALL cDbEngine_impl()
            : mDLL(0),
              mDatabase_Ctor(0), mDatabase_Dtor(0)
        {
        }
        CDFASTCALL ~cDbEngine_impl()
        {
            if ( mDLL != 0 )
                ::FreeLibrary( mDLL );
        }
    };
    shared_ptr<cDbEngine_impl>           mData;
public:
    CDFASTCALL cDbEngine( const char *dll_name );
    CDFASTCALL cDbEngine( const cDbEngine& src )
        : mData(src.mData)
    {
    }
    CDFASTCALL ~cDbEngine();

    Database_Ctor FASTCALL Database_Constructor() const     { return ( mData->mDatabase_Ctor ); }
    Database_Dtor FASTCALL Database_Destructor() const      { return ( mData->mDatabase_Dtor ); }

    cDatabase FASTCALL NewConnection( const ds_string& connection_string );
};

//***********************************************************************
//******    cDatabase
//***********************************************************************
class cDatabase
{
private:
    class cDatabase_impl
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
    {
    private:
        NO_COPY_CTOR(cDatabase_impl);
        NO_COPY_OPER(cDatabase_impl);
    public:
        IDatabase           *mDatabase;
        cDbEngine           mDbEngine;
        ds_string           mConnectionString;

        CDFASTCALL cDatabase_impl( const cDbEngine& transport_code, const ds_string& connection_string )
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
    CDFASTCALL cDatabase( const cDbEngine& transport_code, const ds_string& connection_string );
    CDFASTCALL ~cDatabase();

    IDatabase * FASTCALL Database() const           { return ( mData->mDatabase ); }

    cDataTransfer FASTCALL NewTransfer() const;
};

//***********************************************************************
//******    cDataTransfer
//***********************************************************************
class cDataTransfer
{
private:
    class cDataTransferData
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
    {
    private:
        NO_COPY_CTOR(cDataTransferData);
        NO_COPY_OPER(cDataTransferData);
    public:
        IDataProvider       *mTransfer;
        cDatabase           mDatabase;

        CDFASTCALL cDataTransferData( const cDatabase& database )
            : mTransfer(database.Database()->CreateDataProvider()), mDatabase(database)
        {
        }
        CDFASTCALL ~cDataTransferData()
        {
            mDatabase.Database()->DestroyDataProvider( mTransfer );
        }
    };

    shared_ptr<cDataTransferData>  mData;
public:
    CDFASTCALL cDataTransfer( const cDatabase& conn );
    CDFASTCALL ~cDataTransfer();

    IDataProvider * FASTCALL DataTransfer() const           { return ( mData->mTransfer ); }
};

cDbEngine FASTCALL SelectDbEngine( const char *name );

};
//---------------------------------------------------------------------------
#endif
