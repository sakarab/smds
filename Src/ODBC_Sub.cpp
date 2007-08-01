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
#include "ODBC_Sub.h"
#include <stdexcept>
#include <boost/smart_ptr.hpp>
#include "dsConn_Intf.h"
//---------------------------------------------------------------------------

using namespace smds;

SQLRETURN CheckReturn( SQLRETURN ret )
{
    if ( ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO )
        return ret;
    throw std::runtime_error( "ODBC Error." );
}

/*
static SQLRETURN    LastError;

SQLRETURN CheckReturn_( SQLRETURN ret )
{
    LastError = ret;
    return ret;
}

void DescribeError( short handle_type, void *handle )
{
    if ( LastError == SQL_SUCCESS || LastError == SQL_SUCCESS_WITH_INFO )
        return;

    unsigned char   sql_state[10];
    SQLINTEGER      native_error;
    SQLCHAR         message[1024];
    SQLSMALLINT     message_len_is;
    SQLSMALLINT     rec_no = 1;
    SQLRETURN       ret;

    do
    {
        ret = SQLGetDiagRec( handle_type, handle, rec_no, sql_state, &native_error, message, sizeof(message), &message_len_is );
        if ( ret == SQL_INVALID_HANDLE || ret == SQL_ERROR )
            break;
        ++rec_no;
    }
    while ( ret != SQL_NO_DATA );
    throw std::runtime_error( "ODBC Error." );
}
*/

TypeRaw     DataTypeMap[23] =
{
    { SQL_CHAR                      , SQL_C_CHAR            , cFieldDataType_ftString    , 0                            },  // CHAR(n) Character string of fixed string length n.
    { SQL_VARCHAR                   , SQL_C_CHAR            , cFieldDataType_ftString    , 0                            },  // VARCHAR(n) Variable-length character string with a maximum string length n.
    { SQL_LONGVARCHAR               , SQL_C_CHAR            , cFieldDataType_ftString    , 0                            },  // LONG VARCHAR Variable length character data. Maximum length is data source–dependent.[9]
    { SQL_WCHAR                     , SQL_C_CHAR            , cFieldDataType_ftString    , 0                            },  // WCHAR(n) Unicode character string of fixed string length n
    { SQL_WVARCHAR                  , SQL_C_CHAR            , cFieldDataType_ftString    , 0                            },  // VARWCHAR(n) Unicode variable-length character string with a maximum string length n
    { SQL_WLONGVARCHAR              , SQL_C_CHAR            , cFieldDataType_ftString    , 0                            },  // LONGWVARCHAR Unicode variable-length character data. Maximum length is data source–dependent
    { SQL_DECIMAL                   , SQL_C_DOUBLE          , cFieldDataType_ftDouble    , sizeof(double)               },  // DECIMAL(p,s) Signed, exact, numeric value with a precision of at least p and scale s. (The maximum precision is driver-defined.)(1 <= p <= 15; s <= p).[4]
    { SQL_NUMERIC                   , SQL_C_DOUBLE          , cFieldDataType_ftDouble    , sizeof(double)               },  // NUMERIC(p,s) Signed, exact, numeric value with a precision p and scale s (1 <= p <= 15; s <= p).[4]
    { SQL_SMALLINT                  , SQL_C_SSHORT          , cFieldDataType_ftShort     , sizeof(short)                },  // SMALLINT Exact numeric value with precision 5 and scale 0(signed:–32,768 <= n <= 32,767, unsigned:0 <= n <= 65,535)[3].
    { SQL_INTEGER                   , SQL_C_SLONG           , cFieldDataType_ftInteger   , sizeof(int)                  },  // INTEGER Exact numeric value with precision 10 and scale 0(signed:–2[31] <= n <= 2[31] – 1, unsigned:0 <= n <= 2[32] – 1)[3].
    { SQL_REAL                      , SQL_C_DOUBLE          , cFieldDataType_ftDouble    , sizeof(double)               },  // REAL Signed, approximate, numeric value with a binary precision 24 (zero or absolute value 10[–38] to 10[38]).
    { SQL_FLOAT                     , SQL_C_DOUBLE          , cFieldDataType_ftDouble    , sizeof(double)               },  // FLOAT(p) Signed, approximate, numeric value with a binary precision of at least p. (The maximum precision is driver-defined.)[5]
    { SQL_DOUBLE                    , SQL_C_DOUBLE          , cFieldDataType_ftDouble    , sizeof(double)               },  // DOUBLE PRECISION Signed, approximate, numeric value with a binary precision 53 (zero or absolute value 10[–308] to 10[308]).
    { SQL_BIT                       , SQL_C_BIT             , cFieldDataType_ftBool      , sizeof(char)                 },  // BIT Single bit binary data.[8]
    { SQL_TINYINT                   , SQL_C_STINYINT        , cFieldDataType_ftByte      , sizeof(char)                 },  // TINYINT Exact numeric value with precision 3 and scale 0(signed:–128 <= n <= 127,unsigned:0 <= n <= 255)[3].
    { SQL_BIGINT                    , SQL_C_SBIGINT         , cFieldDataType_ftLongLong  , sizeof(long long)            },  // BIGINT Exact numeric value with precision 19 (if signed) or 20 (if unsigned) and scale 0(signed:–2[63] <= n <= 2[63] – 1,unsigned:0 <= n <= 2[64] – 1)[3],[9].
    { SQL_BINARY                    , SQL_C_BINARY          , cFieldDataType_ftBlob      , 0                            },  // BINARY(n) Binary data of fixed length n.[9]
    { SQL_VARBINARY                 , SQL_C_BINARY          , cFieldDataType_ftBlob      , 0                            },  // VARBINARY(n) Variable length binary data of maximum length n. The maximum is set by the user.[9]
    { SQL_LONGVARBINARY             , SQL_C_BINARY          , cFieldDataType_ftBlob      , 0                            },  // LONG VARBINARY Variable length binary data. Maximum length is data source–dependent.[9]
    { SQL_TYPE_DATE                 , SQL_C_TYPE_DATE       , cFieldDataType_ftDate      , sizeof(SQL_DATE_STRUCT)      },  // [6] DATE Year, month, and day fields, conforming to the rules of the Gregorian calendar. (See "Constraints of the Gregorian Calendar," later in this appendix.)
    { SQL_TYPE_TIME                 , SQL_C_TYPE_TIME       , cFieldDataType_ftTime      , sizeof(SQL_TIME_STRUCT)      },  // [6] TIME(p) Hour, minute, and second fields, with valid values for hours of 00 to 23, valid values for minutes of 00 to 59, and valid values for seconds of 00 to 61. Precision p indicates the seconds precision.
    { SQL_TYPE_TIMESTAMP            , SQL_C_TYPE_TIMESTAMP  , cFieldDataType_ftDateTime  , sizeof(SQL_TIMESTAMP_STRUCT) },  // [6] TIMESTAMP(p) Year, month, day, hour, minute, and second fields, with valid values as defined for the DATE and TIME data types.
//  { SQL_TYPE_UTCDATETIME          , 0                     , 0                          , 0                            },  // UTCDATETIME Year, month, day, hour, minute, second, utchour, and utcminute fields. The utchour and utcminute fields have 1/10th microsecond precision.
//  { SQL_TYPE_UTCTIME              , 0                     , 0                          , 0                            },  // UTCTIME Hour, minute, second, utchour, and utcminute fields. The utchour and utcminute fields have 1/10th microsecond precision..
//  { SQL_INTERVAL_MONTH            , 0                     , 0                          , 0                            },  // [7] INTERVAL MONTH(p) Number of months between two dates; p is the interval leading precision.
//  { SQL_INTERVAL_YEAR             , 0                     , 0                          , 0                            },  // [7] INTERVAL YEAR(p) Number of years between two dates; p is the interval leading precision.
//  { SQL_INTERVAL_YEAR_TO_MONTH    , 0                     , 0                          , 0                            },  // [7] INTERVAL YEAR(p) TO MONTH Number of years and months between two dates; p is the interval leading precision.
//  { SQL_INTERVAL_DAY              , 0                     , 0                          , 0                            },  // [7] INTERVAL DAY(p) Number of days between two dates; p is the interval leading precision.
//  { SQL_INTERVAL_HOUR             , 0                     , 0                          , 0                            },  // [7] INTERVAL HOUR(p) Number of hours between two date/times; p is the interval leading precision.
//  { SQL_INTERVAL_MINUTE           , 0                     , 0                          , 0                            },  // [7] INTERVAL MINUTE(p) Number of minutes between two date/times; p is the interval leading precision.
//  { SQL_INTERVAL_SECOND           , 0                     , 0                          , 0                            },  // [7] INTERVAL SECOND(p,q) Number of seconds between two date/times; p is the interval leading precision and q is the interval seconds precision.
//  { SQL_INTERVAL_DAY_TO_HOUR      , 0                     , 0                          , 0                            },  // [7] INTERVAL DAY(p) TO HOUR Number of days/hours between two date/times; p is the interval leading precision.
//  { SQL_INTERVAL_DAY_TO_MINUTE    , 0                     , 0                          , 0                            },  // [7] INTERVAL DAY(p) TO MINUTE Number of days/hours/minutes between two date/times; p is the interval leading precision.
//  { SQL_INTERVAL_DAY_TO_SECOND    , 0                     , 0                          , 0                            },  // [7] INTERVAL DAY(p) TO SECOND(q) Number of days/hours/minutes/seconds between two date/times; p is the interval leading precision and q is the interval seconds precision.
//  { SQL_INTERVAL_HOUR_TO_MINUTE   , 0                     , 0                          , 0                            },  // [7] INTERVAL HOUR(p) TO MINUTE Number of hours/minutes between two date/times; p is the interval leading precision.
//  { SQL_INTERVAL_HOUR_TO_SECOND   , 0                     , 0                          , 0                            },  // [7] INTERVAL HOUR(p) TO SECOND(q) Number of hours/minutes/seconds between two date/times; p is the interval leading precision and q is the interval seconds precision.
//  { SQL_INTERVAL_MINUTE_TO_SECOND , 0                     , 0                          , 0                            },  // [7] INTERVAL MINUTE(p) TO SECOND(q) Number of minutes/seconds between two date/times; p is the interval leading precision and q is the interval seconds precision.
    { SQL_GUID                      , SQL_C_GUID            , cFieldDataType_ftGUID      , sizeof(SQLGUID)              }   // GUID Fixed length Globally Unique Identifier.
};

/*
SWORD FASTCALL ODBCtoCtype( SWORD odbc_data_type )
{
    for ( int n = 0 ; n < sizeof(DataTypeMap)/sizeof(DataTypeMap[0]) ; ++n )
        if ( DataTypeMap[n].OdbcType == odbc_data_type )
            return DataTypeMap[n].DriverCType;
    throw std::runtime_error( "ODBC: Unsupported database type." );
}
*/

const TypeRaw * FASTCALL TypeRawFromODBCtype( SWORD odbc_data_type )
{
    TypeRaw     *result = &DataTypeMap[0];

    for ( unsigned int n = 0 ; n < sizeof(DataTypeMap)/sizeof(DataTypeMap[0]) ; ++n, ++result )
        if ( result->OdbcType == odbc_data_type )
            return result;
    throw std::runtime_error( "ODBC: Unsupported database type." );
}

//***********************************************************************
//******    ODBC_Field
//***********************************************************************
CDFASTCALL ODBC_Field::ODBC_Field( const std::string name, const TypeRaw *data_type, UDWORD precision, SWORD scale, SWORD nullable )
    : m_ODBC_type(data_type->OdbcType), mPrecision(precision), mScale(scale), mNullable(nullable), mIndicator(0),
      mName(name), mVecBuff() // mVecBuff( precision <= BUFFER_SWITCH ? 0 : data_size )
{
    // SQL type transilation. Better to provide an interface to handle it.
    if ( (m_ODBC_type == SQL_DECIMAL || m_ODBC_type == SQL_NUMERIC) && mScale == 0 && mPrecision <= 19 )
    {
        if ( mPrecision <= 3 )
            data_type = TypeRawFromODBCtype( SQL_TINYINT );
        else if ( mPrecision <= 5 )
            data_type = TypeRawFromODBCtype( SQL_SMALLINT );
        else if ( mPrecision <= 10 )
            data_type = TypeRawFromODBCtype( SQL_INTEGER );
        else // if ( mPrecision <= 19 )
            data_type = TypeRawFromODBCtype( SQL_BIGINT );
    }
    m_C_type = data_type->OdbcCType;
    m_DS_type = data_type->DatasetType;

    if ( data_type->BinarySize != 0 )
        mDataSize = data_type->BinarySize;
    else
        mDataSize = precision;
    if ( mDataSize > BUFFER_SWITCH )
        mVecBuff.resize( mDataSize <= LONG_DATA ? mDataSize : LONG_DATA_BUFFER );
}

CDFASTCALL ODBC_Field::~ODBC_Field()
{
}

SQLPOINTER FASTCALL ODBC_Field::GetBuffer()
{
    if ( mDataSize <= BUFFER_SWITCH )
        return mCharBuff;
    return &mVecBuff.front();
}

SQLLEN FASTCALL ODBC_Field::GetBufferLength()
{
    if ( mDataSize <= BUFFER_SWITCH )
        return BUFFER_SWITCH;
    return mVecBuff.size();
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

void FASTCALL ODBC_Env::SetOdbcVersion( unsigned long version )
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
    : mStatement(SQL_NULL_HANDLE), mFields(), mIsEof(false)
{
    CheckReturn( SQLAllocHandle( SQL_HANDLE_STMT, connection.GetHandle(), &mStatement ) );
}

CDFASTCALL ODBC_Statement::~ODBC_Statement()
{
    SQLFreeHandle( SQL_HANDLE_STMT, mStatement );
}

void FASTCALL ODBC_Statement::GetFieldAttributes( int idx, char *name, unsigned int name_buffer_length,
                                                  std::size_t& name_buffer_required_length,
                                                  unsigned int& field_data_size, int& field_data_type )
{
    ODBC_Field&     field = mFields[idx];
    std::size_t     copy_len;

    if ( name_buffer_length > field.GetName().length() )
        copy_len = field.GetName().length();
    else
        copy_len = name_buffer_length - 1;

    std::strncpy( name, field.GetName().c_str(), copy_len );
    name[name_buffer_length - 1] = '\0';
    name_buffer_required_length = field.GetName().length() + 1;
    field_data_size = field.GetDataSize();
    field_data_type = field.DS_Type();
}

void FASTCALL ODBC_Statement::ExecSql( const char *sql )
{
    mIsEof = false;

    boost::scoped_array<unsigned char>  tmp_sql( new unsigned char[strlen(sql) + 1] );

    std::strcpy( reinterpret_cast<char *>(tmp_sql.get()), sql );

    CheckReturn( SQLExecDirect( mStatement, tmp_sql.get(), SQL_NTS ) );

    SWORD    nCols;                      // # of result columns

    CheckReturn( SQLNumResultCols( mStatement, &nCols ) );

    std::vector<char>   field_name( 50 );
    SWORD               field_name_size = static_cast<SWORD>(field_name.size());

    for ( SWORD n = 1 ; n <= nCols ; ++n )
    {
        SWORD   data_type;                  // column data type
        UDWORD  precision;                  // precision on the column
        SWORD   scale;                      // column scale
        SWORD   nullable;                   // nullable column ?
        SWORD   name_length;                // column data length

        SQLRETURN   ret = CheckReturn( SQLDescribeCol( mStatement, n, reinterpret_cast<unsigned char *>(&field_name.front()),
                                                       field_name_size, &name_length, &data_type, &precision, &scale,
                                                       &nullable ) );
        if ( ret == SQL_SUCCESS_WITH_INFO )
        {
            field_name.resize( name_length + 1 + (name_length + 1) / 2 );
            field_name_size = static_cast<SWORD>(field_name.size());
            CheckReturn( SQLDescribeCol( mStatement, n, reinterpret_cast<unsigned char *>(&field_name.front()), field_name_size,
                                         &name_length, &data_type, &precision, &scale, &nullable ) );
        }
        mFields.push_back( ODBC_Field( &field_name.front(), TypeRawFromODBCtype( data_type ), precision, scale, nullable ) );
    }
    for ( SWORD n = 1 ; n <= nCols ; ++n )
    {
        ODBC_Field&     field = mFields[n-1];

        if ( ! field.IsLongData() )
            CheckReturn( SQLBindCol( mStatement, n, field.C_Type(), field.GetBuffer(),
                                     field.GetBufferLength(), field.GetIndicatorAddress() ) );
    }
    Next();
}

void FASTCALL ODBC_Statement::CloseSql()
{
    CheckReturn( SQLFreeStmt( mStatement, SQL_CLOSE ) );
    mIsEof = false;
}

void FASTCALL ODBC_Statement::Next()
{
    SQLRETURN   nReturn = SQLFetch( mStatement );

    if ( nReturn != SQL_NO_DATA )
        CheckReturn( nReturn );
    mIsEof = nReturn != SQL_SUCCESS;
}

ODBC_Field * FASTCALL ODBC_Statement::FieldByName( const char *field_name )
{
    for ( std::vector<ODBC_Field>::iterator it = mFields.begin(), eend = mFields.end() ; it != eend ; ++it )
        if ( _stricmp( it->GetName().c_str(), field_name ) == 0 )
            return &(*it);
    throw std::runtime_error( "ODBC FieldByName error." );
}

//---------------------------------------------------------------------------

