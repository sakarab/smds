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
#pragma hdrstop

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>
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

    struct FieldFieldPair
    {
        native_field_type       *mNativeField;
        std::string             mFieldName;
        int                     mFieldDataSize;
        int                     mFieldDataType;
        const void              *mData;
        FieldFieldPair( native_field_type *native_field, const char *field_name, int data_size, int data_type, const void *data )
            : mNativeField(native_field), mFieldName(field_name), mFieldDataSize(data_size),
              mFieldDataType(data_type), mData(data)
        {
        }
    };

    struct SortCmpByFieldDef : public std::binary_function<FieldFieldPair, FieldFieldPair, bool>
    {
        bool operator() ( const FieldFieldPair& item1, const FieldFieldPair& item2 )
        {
            return ( _stricmp( item1.mFieldName.c_str(), item2.mFieldName.c_str() ) < 0 );
        }
    };
    cDataConnection                 *mDataConnection;
    std::vector<FieldFieldPair>     mFieldPairMap;
    ODBC_Statement                  mStatement;
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
    virtual bool __stdcall Eof();
    virtual void __stdcall Next();
    virtual void __stdcall CloseSql();

    virtual void __stdcall InitDataTransfer();
    virtual void __stdcall StepInitDataTransfer( const char *field_name, int field_data_size, int field_data_type, const void *data );
    virtual void __stdcall EndInitDataTransfer();

    virtual bool __stdcall GetFieldValues( IFieldValuesAcceptor *values_acceptor );
    virtual void __stdcall EndDataTransfer();

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

void __stdcall cDataProvider::InitDataTransfer()
{
    mFieldPairMap.clear();
}

void __stdcall cDataProvider::StepInitDataTransfer( const char *field_name, int field_data_size, int field_data_type, const void *data )
{
    mFieldPairMap.push_back( FieldFieldPair( mStatement.FieldByName( field_name ), field_name, field_data_size, field_data_type, data ) );

    std::vector<FieldFieldPair>::value_type&    pair_ptr = mFieldPairMap.back();

    if ( static_cast<long>(pair_ptr.mNativeField->GetSize()) > field_data_size )
        throw std::runtime_error( "DataSize mismatch!!!!" );
}

void __stdcall cDataProvider::EndInitDataTransfer()
{
    std::sort( mFieldPairMap.begin(), mFieldPairMap.end(), SortCmpByFieldDef() );
}

bool __stdcall cDataProvider::GetFieldValues( IFieldValuesAcceptor *values_acceptor )
{
    bool        result = false;

    for ( std::vector<FieldFieldPair>::iterator n = mFieldPairMap.begin(), eend = mFieldPairMap.end() ; n != eend ; ++n )
    {
        native_field_type   *field = n->mNativeField;

        if ( field->IsNull() )
            values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, 0, n->mFieldDataSize );
        else switch ( n->mFieldDataType )
        {
            case cFieldDataType_ftBool :
                {
                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, field->GetBuffer(), n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftChar :
                {
                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, field->GetBuffer(), n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftWChar :
                break;
            case cFieldDataType_ftShort :
                {
                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, field->GetBuffer(), n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftInteger :
                {
                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, field->GetBuffer(), n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftLong :
                {
                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, field->GetBuffer(), n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftDouble :
                {
                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, field->GetBuffer(), n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftDateTime :
                {
                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, field->GetBuffer(), n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftString :
                {
                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, field->GetBuffer(), n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftWString :
                break;
            case cFieldDataType_ftBlob :
                break;
        }
    }
    return ( result );
}

void __stdcall cDataProvider::EndDataTransfer()
{
    mFieldPairMap.clear();
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

__declspec(dllexport) IDatabase * CreateDataConnection( const char *connection_string )
{
    if ( Engine.get() == 0 )
    {
        Engine.reset( new ODBC_Env() );
        Engine->SetOdbcVersion( SQL_OV_ODBC3 );
    }
    return ( new cDataConnection( *Engine.get(), connection_string ) );
}

__declspec(dllexport) void DeleteDataConnection( IDatabase *connection )
{
    delete connection;
}

};

int WINAPI DllEntryPoint( HINSTANCE /*hinst*/, unsigned long /*reason*/, void* /*lpReserved*/ )
{
    return 1;
}
//---------------------------------------------------------------------------
