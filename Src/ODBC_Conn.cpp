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
#include <windows.h>
#ifndef __GNUG__
#pragma hdrstop
#endif

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <boost/smart_ptr.hpp>
#include "dsConn_Intf.h"
#include "ODBC_Sub.h"
//---------------------------------------------------------------------------

using namespace smds;

namespace
{

class DbEngine;

std::auto_ptr<ODBC_Env>     Engine;

//***********************************************************************
//******    cDataConnection
//***********************************************************************
class cDataConnection : public IDatabase
{
private:
    ODBC_Connection     mConnection;
    // noncopyable
    cDataConnection( const cDataConnection& src );
    cDataConnection& operator=( const cDataConnection& src );
protected:
#if defined ( SM_USE_COM_DELPHI_INTERFACE )
    // IUnknown
    virtual HRESULT __stdcall QueryInterface( REFIID riid, void **ppvObject );
    virtual ULONG __stdcall AddRef();
    virtual ULONG __stdcall Release();
#endif
    // IDatabase
    virtual IDataProvider *     __stdcall CreateDataProvider();
    virtual void                __stdcall DestroyDataProvider( IDataProvider *connection );
public:
    cDataConnection( ODBC_Env& env, const char *connection_string );
    ~cDataConnection();
    ODBC_Connection& GetConnection()                  { return mConnection; }
};

//***********************************************************************
//******    cDataProvider
//***********************************************************************
class cDataProvider : public IDataProvider
{
private:
    typedef ODBC_Field      native_field_type;

    cDataConnection         *mDataConnection;
    ODBC_Statement          mStatement;
    // noncopyable
    cDataProvider( const cDataProvider& src );
    cDataProvider& operator=( const cDataProvider& src );
protected:
#if defined ( SM_USE_COM_DELPHI_INTERFACE )
    // IUnknown
    virtual HRESULT __stdcall QueryInterface( REFIID riid, void **ppvObject );
    virtual ULONG __stdcall AddRef();
    virtual ULONG __stdcall Release();
#endif
    // IDataTransfer
    virtual void __stdcall OpenSql( const char *sql );
    virtual void __stdcall CloseSql();
    virtual bool __stdcall Eof();
    virtual void __stdcall Next();

    virtual std::size_t __stdcall GetFieldCount();
    virtual void __stdcall GetFieldAttributes( int idx, char *name, unsigned int name_buffer_length,
                                               std::size_t& name_buffer_required_length,
                                               unsigned int& field_data_size, int& field_data_type );

    virtual bool __stdcall GetFieldValues( IFieldValuesAcceptor *values_acceptor );

    virtual void __stdcall StartTransaction();
    virtual void __stdcall Commit();
    virtual void __stdcall RollBack();
    virtual void __stdcall ExecSql( const char *sql );
public:
    cDataProvider( cDataConnection *conn );
    ~cDataProvider();
};

//***********************************************************************
//******    cDataConnection
//***********************************************************************
cDataConnection::cDataConnection( ODBC_Env& env, const char *connection_string )
    : mConnection( env )
{
    mConnection.Connect( connection_string );
}

cDataConnection::~cDataConnection()
{
    mConnection.Disconnect();
}

#if defined ( SM_USE_COM_DELPHI_INTERFACE )
HRESULT __stdcall cDataConnection::QueryInterface( REFIID riid, void **ppvObject )
{
    return E_NOINTERFACE;
}

ULONG __stdcall cDataConnection::AddRef()
{
    return -1;
}

ULONG __stdcall cDataConnection::Release()
{
    return -1;
}
#endif

IDataProvider * __stdcall cDataConnection::CreateDataProvider()
{
    return ( new cDataProvider( this ) );
}

void __stdcall cDataConnection::DestroyDataProvider( IDataProvider *connection )
{
    delete connection;
}

//***********************************************************************
//******    cDataProvider
//***********************************************************************
cDataProvider::cDataProvider( cDataConnection *connection )
    : mDataConnection(connection), mStatement( connection->GetConnection() )
{
}

cDataProvider::~cDataProvider()
{
}

#if defined ( SM_USE_COM_DELPHI_INTERFACE )
HRESULT __stdcall cDataProvider::QueryInterface( REFIID riid, void **ppvObject )
{
    return E_NOINTERFACE;
}

ULONG __stdcall cDataProvider::AddRef()
{
    return -1;
}

ULONG __stdcall cDataProvider::Release()
{
    return -1;
}
#endif

void __stdcall cDataProvider::OpenSql( const char *sql )
{
    mStatement.ExecSql( sql );
}

bool __stdcall cDataProvider::Eof()
{
    return mStatement.Eof();
}

void __stdcall cDataProvider::Next()
{
    mStatement.Next();
}

void __stdcall cDataProvider::CloseSql()
{
    mStatement.CloseSql();
}

unsigned int __stdcall cDataProvider::GetFieldCount()
{
    return mStatement.GetFieldCount();
}

void __stdcall cDataProvider::GetFieldAttributes( int idx, char *name, unsigned int name_buffer_length,
                                                  std::size_t& name_buffer_required_length,
                                                  unsigned int& field_data_size, int& field_data_type )
{
    mStatement.GetFieldAttributes( idx, name, name_buffer_length, name_buffer_required_length, field_data_size, field_data_type );
}

bool __stdcall cDataProvider::GetFieldValues( IFieldValuesAcceptor *values_acceptor )
{
    bool        result = false;

    for ( unsigned int n = 0 ; n < mStatement.GetFieldCount() ; ++n )
    {
        native_field_type   *field = mStatement.FieldByIndex( n );

        if ( field->IsNull() )
            result = values_acceptor->FieldValue( n, 0, field->GetDataSize() );
        else
            result = values_acceptor->FieldValue( n, field->GetBuffer(), field->GetDataSize() );
    }

    return result;
}

void __stdcall cDataProvider::StartTransaction()
{
}

void __stdcall cDataProvider::Commit()
{
}

void __stdcall cDataProvider::RollBack()
{
}

void __stdcall cDataProvider::ExecSql( const char *sql )
{
}

}; // end namespace

extern "C"
{

IDatabase * CreateDataConnection( const char *connection_string )
{
    if ( Engine.get() == 0 )
    {
        Engine.reset( new ODBC_Env() );
        Engine->SetOdbcVersion( SQL_OV_ODBC3 );
    }
    return ( new cDataConnection( *Engine.get(), connection_string ) );
}

void DeleteDataConnection( IDatabase *connection )
{
    delete connection;
}

}; // extern "C"

int WINAPI DllEntryPoint( HINSTANCE /*hinst*/, unsigned long /*reason*/, void* /*lpReserved*/ )
{
    return 1;
}
//---------------------------------------------------------------------------

