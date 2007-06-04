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

#include "ODBC_Sub.h"
#include <stdexcept>
#include <boost/smart_ptr.hpp>
//---------------------------------------------------------------------------

SQLRETURN CheckReturn( SQLRETURN ret )
{
    if ( ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO )
        throw std::runtime_error( "ODBC Error." );
    return ret;
}

//***********************************************************************
//******    ODBC_Field
//***********************************************************************
CDFASTCALL ODBC_Field::ODBC_Field( const std::string name, SWORD data_type, UDWORD data_size, SWORD decimal_digits, SWORD nullable )
{
}

CDFASTCALL ODBC_Field::~ODBC_Field()
{
}

//***********************************************************************
//******    ODBC_Env
//***********************************************************************
CDFASTCALL ODBC_Env::ODBC_Env()
    : mEnvironment(SQL_NULL_HANDLE)
{
    CheckReturn( SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &mEnvironment ) );
}

CDFASTCALL ODBC_Env::~ODBC_Env()
{
    SQLFreeHandle( SQL_HANDLE_ENV, mEnvironment );
}

void FASTCALL ODBC_Env::SetOdbcVersion( int version )
{
    CheckReturn( SQLSetEnvAttr( mEnvironment, SQL_ATTR_ODBC_VERSION, reinterpret_cast<SQLPOINTER>(version), 0 ) );
}

//***********************************************************************
//******    ODBC_Connection
//***********************************************************************
CDFASTCALL ODBC_Connection::ODBC_Connection( ODBC_Env& env )
    : mConnection(SQL_NULL_HANDLE), mConnected(false)
{
    CheckReturn( SQLAllocHandle( SQL_HANDLE_DBC, env.GetHandle(), &mConnection ) );
}

CDFASTCALL ODBC_Connection::~ODBC_Connection()
{
    SQLFreeHandle( SQL_HANDLE_DBC, mConnection );
}

void FASTCALL ODBC_Connection::Connect( const char *connection_string )
{
    short                               len = static_cast<short>(strlen(connection_string));
    short                               new_len;
    boost::scoped_ptr<unsigned char>    tmp_conn_str( new unsigned char[len + 1] );
    unsigned char                       conn_str_out[1024];

    std::strcpy( reinterpret_cast<char *>(tmp_conn_str.get()), connection_string );
    CheckReturn( SQLDriverConnect( mConnection, 0, tmp_conn_str.get(), len,
                 conn_str_out,  sizeof(conn_str_out)-1, &new_len, SQL_DRIVER_NOPROMPT ) );
    mConnected = true;
}

void FASTCALL ODBC_Connection::Disconnect()
{
    if ( mConnected )
    {
        CheckReturn( SQLDisconnect( mConnection ) );
        mConnected = false;
    }
}

//***********************************************************************
//******    ODBC_Statement
//***********************************************************************
CDFASTCALL ODBC_Statement::ODBC_Statement( ODBC_Connection& connection )
    : mStatement(SQL_NULL_HANDLE)
{
    CheckReturn( SQLAllocHandle( SQL_HANDLE_STMT, connection.GetHandle(), &mStatement ) );
}

CDFASTCALL ODBC_Statement::~ODBC_Statement()
{
    SQLFreeHandle( SQL_HANDLE_STMT, mStatement );
}

void FASTCALL ODBC_Statement::ExecSql( const char *sql )
{
    boost::scoped_array<unsigned char>  tmp_sql( new unsigned char[strlen(sql) + 1] );

    std::strcpy( reinterpret_cast<char *>(tmp_sql.get()), sql );

    CheckReturn( SQLExecDirect( mStatement, tmp_sql.get(), SQL_NTS ) );

    SWORD    nCols;                      // # of result columns

    CheckReturn( SQLNumResultCols( mStatement, &nCols ) );

    std::vector<unsigned char>      field_name( 50 );
    SWORD                           field_name_size = static_cast<SWORD>(field_name.size() - 1);

    for ( SWORD n = 1 ; n <= nCols ; ++n )
    {
        SWORD   data_type;                  // column data type
        SWORD   decimal_digits;             // column scale
        SWORD   nullable;                   // nullable column ?
        SWORD   name_length;                // column data length
        UDWORD  data_size;                  // precision on the column

        SQLRETURN   ret = CheckReturn( SQLDescribeCol( mStatement, n, &field_name.front(), field_name_size,
                                                       &name_length, &data_type, &data_size, &decimal_digits, &nullable ) );
        if ( ret == SQL_SUCCESS_WITH_INFO )
        {
            field_name.resize( name_length + 1 );
            field_name_size = static_cast<SWORD>(field_name.size() - 1);
            CheckReturn( SQLDescribeCol( mStatement, n, &field_name.front(), field_name_size,
                                         &name_length, &data_type, &data_size, &decimal_digits, &nullable ) );
        }
    }
}

//---------------------------------------------------------------------------

