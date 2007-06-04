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
    SWORD           mDataType;
    UDWORD          mDataSize;
    SWORD           mDecimalDigits;
    SWORD           mNullable;
    std::string     mName;
    union
    {
        char    char_buff[16];
        char    vec_buff[sizeof(std::vector<char>)];
    } Data;
public:
    CDFASTCALL ODBC_Field( const std::string name, SWORD data_type, UDWORD data_size, SWORD decimal_digits, SWORD nullable );
    CDFASTCALL ~ODBC_Field();
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
    SQLHANDLE       mStatement;
    // noncopyable
    ODBC_Statement( const ODBC_Statement& src );
    ODBC_Statement& operator=( const ODBC_Statement& src );
public:
    CDFASTCALL ODBC_Statement( ODBC_Connection& connection );
    CDFASTCALL ~ODBC_Statement();

    void FASTCALL ExecSql( const char *sql );
};

//---------------------------------------------------------------------------

SQLRETURN CheckReturn( SQLRETURN ret );

//---------------------------------------------------------------------------
#endif
