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
#ifndef ODBC_SubH
#define ODBC_SubH
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <vector>
#include <string>
//---------------------------------------------------------------------------

//***********************************************************************
//******    ODBC_Field
//***********************************************************************
class ODBC_Field
{
private:
    enum { BUFFER_SWITCH = 16 };

    SWORD               mDataType;
    UDWORD              mDataSize;
    SWORD               mDecimalDigits;
    SWORD               mNullable;
    SQLLEN              mIndicator;
    std::string         mName;
    std::vector<char>   mVecBuff;
    char                mCharBuff[BUFFER_SWITCH];
public:
    CDFASTCALL ODBC_Field( const std::string name, SWORD data_type, UDWORD data_size, SWORD decimal_digits, SWORD nullable );
    CDFASTCALL ~ODBC_Field();
    SWORD FASTCALL GetDataType() const                      { return mDataType; }
    SWORD FASTCALL GetCDataType() const;
    UDWORD FASTCALL GetSize() const                         { return mDataSize; }
    UDWORD FASTCALL GetDataSize() const                     { return mDataSize; }
    const std::string& GetName() const                      { return mName; }
    SQLPOINTER FASTCALL GetBuffer();
    SQLLEN FASTCALL GetBufferLength();
    SQLLEN * FASTCALL GetIndicatorAddress()                 { return &mIndicator; }
    bool FASTCALL IsNull() const                            { return mIndicator == SQL_NULL_DATA; }
};

//***********************************************************************
//******    ODBC_Env
//***********************************************************************
class ODBC_Env
{
private:
    SQLHANDLE       mEnvironment;
    // noncopyable
    ODBC_Env( const ODBC_Env& src );
    ODBC_Env& operator=( const ODBC_Env& src );
public:
    CDFASTCALL ODBC_Env();
    CDFASTCALL ~ODBC_Env();
    SQLHANDLE GetHandle() const                         { return mEnvironment; }

    void FASTCALL SetOdbcVersion( int version );                                // SQL_ATTR_ODBC_VERSION
};

//***********************************************************************
//******    ODBC_Connection
//***********************************************************************
class ODBC_Connection
{
private:
    SQLHANDLE       mConnection;
    bool            mConnected;
    // noncopyable
    ODBC_Connection( const ODBC_Connection& src );
    ODBC_Connection& operator=( const ODBC_Connection& src );
public:
    CDFASTCALL ODBC_Connection( ODBC_Env& env );
    CDFASTCALL ~ODBC_Connection();
    SQLHANDLE GetHandle() const                                     { return mConnection; }
    void FASTCALL Connect( const char *connection_string );
    void FASTCALL Disconnect();
};

//***********************************************************************
//******    ODBC_Statement
//***********************************************************************
class ODBC_Statement
{
private:
    SQLHANDLE                   mStatement;
    std::vector<ODBC_Field>     mFields;
    bool                        mIsEof;
    // noncopyable
    ODBC_Statement( const ODBC_Statement& src );
    ODBC_Statement& operator=( const ODBC_Statement& src );
public:
    CDFASTCALL ODBC_Statement( ODBC_Connection& connection );
    CDFASTCALL ~ODBC_Statement();

    void FASTCALL ExecSql( const char *sql );
    void FASTCALL CloseSql();
    void FASTCALL Next();
    bool FASTCALL Eof() const                                       { return mIsEof; }

    ODBC_Field * FASTCALL FieldByName( const char *field_name );
};

//---------------------------------------------------------------------------

SQLRETURN CheckReturn( SQLRETURN ret );

#if defined(__BORLANDC__)
int _stricmp( const char * str1, const char * str2 )
{
    return std::stricmp( str1, str2 );
}
#endif

//---------------------------------------------------------------------------
#endif
