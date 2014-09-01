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

#if defined (WIN32) || defined (__WIN32__) || defined (_WIN32)
    #include <windows.h>
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
    virtual HRESULT STDCALL QueryInterface( REFIID riid, void **ppvObject );
    virtual ULONG STDCALL AddRef();
    virtual ULONG STDCALL Release();
#endif
    // IDatabase
    virtual IDataProvider *     STDCALL CreateDataProvider();
    virtual void                STDCALL DestroyDataProvider( IDataProvider *connection );
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
    virtual HRESULT STDCALL QueryInterface( REFIID riid, void **ppvObject );
    virtual ULONG STDCALL AddRef();
    virtual ULONG STDCALL Release();
#endif
    // IDataTransfer
    virtual void STDCALL OpenSql( const char *sql );
    virtual void STDCALL CloseSql();
    virtual bool STDCALL Eof();
    virtual void STDCALL Next();

    virtual std::size_t STDCALL GetFieldCount() override;
    virtual void STDCALL GetFieldAttributes( int idx, char *name, unsigned int name_buffer_length,
                                             std::size_t& name_buffer_required_length,
                                             unsigned int& field_data_size, int& field_data_type ) override;

    virtual bool STDCALL GetFieldValues( IFieldValuesAcceptor *values_acceptor );

    virtual void STDCALL StartTransaction();
    virtual void STDCALL Commit();
    virtual void STDCALL RollBack();
    virtual void STDCALL ExecSql( const char *sql );
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
HRESULT STDCALL cDataConnection::QueryInterface( REFIID riid, void **ppvObject )
{
    return E_NOINTERFACE;
}

ULONG STDCALL cDataConnection::AddRef()
{
    return -1;
}

ULONG STDCALL cDataConnection::Release()
{
    return -1;
}
#endif

IDataProvider * STDCALL cDataConnection::CreateDataProvider()
{
    return ( new cDataProvider( this ) );
}

void STDCALL cDataConnection::DestroyDataProvider( IDataProvider *connection )
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
HRESULT STDCALL cDataProvider::QueryInterface( REFIID riid, void **ppvObject )
{
    return E_NOINTERFACE;
}

ULONG STDCALL cDataProvider::AddRef()
{
    return -1;
}

ULONG STDCALL cDataProvider::Release()
{
    return -1;
}
#endif

void STDCALL cDataProvider::OpenSql( const char *sql )
{
    mStatement.ExecSql( sql );
}

bool STDCALL cDataProvider::Eof()
{
    return mStatement.Eof();
}

void STDCALL cDataProvider::Next()
{
    mStatement.Next();
}

void STDCALL cDataProvider::CloseSql()
{
    mStatement.CloseSql();
}

std::size_t STDCALL cDataProvider::GetFieldCount()
{
    return mStatement.GetFieldCount();
}

void STDCALL cDataProvider::GetFieldAttributes( int idx, char *name, unsigned int name_buffer_length,
                                                std::size_t& name_buffer_required_length,
                                                unsigned int& field_data_size, int& field_data_type )
{
    mStatement.GetFieldAttributes( idx, name, name_buffer_length, name_buffer_required_length, field_data_size, field_data_type );
}

bool STDCALL cDataProvider::GetFieldValues( IFieldValuesAcceptor *values_acceptor )
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

void STDCALL cDataProvider::StartTransaction()
{
}

void STDCALL cDataProvider::Commit()
{
}

void STDCALL cDataProvider::RollBack()
{
}

void STDCALL cDataProvider::ExecSql( const char *sql )
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

#if defined (WIN32) || defined (__WIN32__) || defined (_WIN32)
int WINAPI DllEntryPoint( HINSTANCE /*hinst*/, unsigned long /*reason*/, void* /*lpReserved*/ )
{
    return 1;
}
#endif
//---------------------------------------------------------------------------

