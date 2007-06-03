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
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>
#include <boost/smart_ptr.hpp>
#include "dsConn_Intf.h"
#include <sql.h>
#include <sqlext.h>
//---------------------------------------------------------------------------

using namespace smds;

namespace
{

SQLRETURN CheckReturn( SQLRETURN ret )
{
    if ( ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO )
        throw std::runtime_error( "ODBC Error." );
    return ret;
}

//***********************************************************************
//******    SqlCall
//***********************************************************************
/*
class SqlCall
{
private:
    class SqlCallImpl
    {
    public:
        SQLRETURN SQLAllocHandle_( SQLSMALLINT HandleType, SQLHANDLE InputHandle, SQLHANDLE *OutputHandle)
        {
            return SQLAllocHandle( HandleType, InputHandle, OutputHandle );
        }
    };
    SqlCallImpl     mImpl;
public:
    SqlCallImpl operator ->()       { return mImpl };
};
*/

class DbEngine;

std::auto_ptr<DbEngine>  Engine;

//***********************************************************************
//******    DbEngine
//***********************************************************************
class DbEngine
{
private:
    // noncopyable
    DbEngine( const DbEngine& src );
    DbEngine& operator=( const DbEngine& src );
public:
    DbEngine();
    ~DbEngine();
};
//---------------------------------------------------------------------------
DbEngine::DbEngine()
{
}

DbEngine::~DbEngine()
{
}

//***********************************************************************
//******    cDataConnection
//***********************************************************************
class cDataConnection : public IDatabase
{
private:
    SQLHANDLE       mEnvironment;
    SQLHANDLE       mConnection;
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
    cDataConnection( const char *connection_string );
    ~cDataConnection();
    SQLHANDLE GetConnectionHandle() const           { return mConnection; }
};

//***********************************************************************
//******    cDataProvider
//***********************************************************************
class cDataProvider : public IDataProvider
{
private:
/*
    typedef TField      native_field_type;

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
            return ( std::stricmp( item1.mFieldName.c_str(), item2.mFieldName.c_str() ) < 0 );
        }
    };
*/
    cDataConnection                 *mDataConnection;
    // std::vector<FieldFieldPair>     mFieldPairMap;
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
cDataConnection::cDataConnection( const char *connection_string )
    : mEnvironment(SQL_NULL_HANDLE), mConnection(SQL_NULL_HANDLE)
{
    CheckReturn( SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &mEnvironment ) );

    if ( CheckReturn( SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &mEnvironment ) ) == SQL_SUCCESS )
        if ( CheckReturn( SQLSetEnvAttr( mEnvironment, SQL_ATTR_ODBC_VERSION, reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3), 0 ) ) )
            if ( CheckReturn( SQLAllocHandle( SQL_HANDLE_DBC, mEnvironment, &mConnection ) ) == SQL_SUCCESS )
            {
                short   len = static_cast<short>(strlen(connection_string));
                short   new_len;
                boost::scoped_ptr<unsigned char>    tmp_conn_str( new unsigned char[len + 1] );
                unsigned char                       conn_str_out[1024];

                std::strcpy( reinterpret_cast<char *>(tmp_conn_str.get()), connection_string );
                CheckReturn( SQLDriverConnect( mConnection, 0, tmp_conn_str.get(), len,
                             conn_str_out,  sizeof(conn_str_out)-1, &new_len, SQL_DRIVER_NOPROMPT ) );
            }
}

cDataConnection::~cDataConnection()
{
    SQLFreeHandle( SQL_HANDLE_DBC, mConnection );
    SQLFreeHandle( SQL_HANDLE_ENV, mEnvironment );
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
    : mDataConnection(connection) //, mQuery()
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
    boost::scoped_array<unsigned char>  tmp_sql( new unsigned char[strlen(sql) + 1] );

    std::strcpy( reinterpret_cast<char *>(tmp_sql.get()), sql );

    SQLHSTMT    hstmt;

    CheckReturn( SQLAllocHandle( SQL_HANDLE_STMT, mDataConnection->GetConnectionHandle(), &hstmt ) );
    CheckReturn( SQLExecDirect( hstmt, tmp_sql.get(), SQL_NTS ) );

    SWORD    nCols;                      // # of result columns

    CheckReturn( SQLNumResultCols( hstmt, &nCols ) );
}

bool __stdcall cDataProvider::Eof()
{
//    return( mQuery->Eof );
    return true;
}

void __stdcall cDataProvider::Next()
{
//    mQuery->Next();
}

void __stdcall cDataProvider::CloseSql()
{
//    mQuery.reset( 0 );
}

void __stdcall cDataProvider::InitDataTransfer()
{
//    mFieldPairMap.clear();
}

void __stdcall cDataProvider::StepInitDataTransfer( const char *field_name, int field_data_size, int field_data_type, const void *data )
{
/*
    mFieldPairMap.push_back( FieldFieldPair( mQuery->FieldByName( field_name ), field_name, field_data_size, field_data_type, data ) );

    std::vector<FieldFieldPair>::value_type&    pair_ptr = mFieldPairMap.back();

    if ( pair_ptr.mNativeField->Size > field_data_size )
        throw Exception( "DataSize mismatch!!!!" );
*/
}

void __stdcall cDataProvider::EndInitDataTransfer()
{
//    std::sort( mFieldPairMap.begin(), mFieldPairMap.end(), SortCmpByFieldDef() );
}

bool __stdcall cDataProvider::GetFieldValues( IFieldValuesAcceptor *values_acceptor )
{
/*
    bool        result = false;
    Variant     v;

    for ( std::vector<FieldFieldPair>::iterator n = mFieldPairMap.begin(), eend = mFieldPairMap.end() ; n != eend ; ++n )
    {
        v = n->mNativeField->Value;

        if ( VarIsNull( v ) )
            values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, 0, n->mFieldDataSize );
        else switch ( n->mFieldDataType )
        {
            case cFieldDataType_ftBool :
                {
                    bool    a = v;

                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, &a, n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftChar :
                {
                    char    a = v;

                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, &a, n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftWChar :
                break;
            case cFieldDataType_ftShort :
                {
                    short    a = v;

                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, &a, n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftInteger :
                {
                    int    a = v;

                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, &a, n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftLong :
                {
                    long    a = v;

                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, &a, n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftDouble :
                {
                    double    a = v;

                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, &a, n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftDateTime :
                {
                    double    a = v;

                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, &a, n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftString :
                {
                    AnsiString    a = v;

                    result = values_acceptor->FieldValue( n->mFieldName.c_str(), n->mFieldDataType, n->mData, a.c_str(), n->mFieldDataSize );
                }
                break;
            case cFieldDataType_ftWString :
                break;
            case cFieldDataType_ftBlob :
                break;
        }
    }
    return ( result );
*/
    return true;
}

void __stdcall cDataProvider::EndDataTransfer()
{
//    mFieldPairMap.clear();
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
    return ( new cDataConnection( connection_string ) );
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
