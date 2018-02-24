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
#ifndef uTestH
#define uTestH
//---------------------------------------------------------------------------
#include <dsData.h>
#include "uTables.h"
#include <boost/predef.h>
//---------------------------------------------------------------------------
#if (BOOST_OS_WINDOWS == BOOST_VERSION_NUMBER_AVAILABLE)

    #if defined(__BORLANDC__)
        #define SM_DS_TEST_BACKEND      "SmDS_ODBCConn_b6.dll"
    #elif ( _MSC_VER == 1310 )
        #define SM_DS_TEST_BACKEND      "SmDS_ODBCConn_v7.dll"
    #elif ( _MSC_VER == 1400 )
        #define SM_DS_TEST_BACKEND      "SmDS_ODBCConn_v8.dll"
    #elif ( _MSC_VER == 1500 )
        #define SM_DS_TEST_BACKEND      "SmDS_ODBCConn_v9.dll"
    #elif ( _MSC_VER == 1600 )
        #define SM_DS_TEST_BACKEND      "SmDS_ODBCConn_v10.dll"
    #elif ( _MSC_VER == 1800 )
        #define SM_DS_TEST_BACKEND      "SmDS_ODBCConn.dll"
    #elif ( _MSC_VER == 1900 )
        #define SM_DS_TEST_BACKEND      "SmDS_ODBCConn.dll"
    #elif ( _MSC_VER > 1900 )
        #define SM_DS_TEST_BACKEND      CCTEXT("SmDS_ODBCConn.dll")
#endif

#elif (BOOST_OS_LINUX == BOOST_VERSION_NUMBER_AVAILABLE)
    #define SM_DS_TEST_BACKEND          "./libODBC_Conn.so"
    //#define SM_DS_TEST_BACKEND      "smDS_ODBCConn_cbx.dll"
#endif

typedef void (FASTCALL *ErrorReporter)( void *user_data, const char *error );

tblFiles_ptr GetTblFiles( smds::Database& database );
void Test( tblFiles_ptr ds, ErrorReporter error_reporter, void *user_data );
void TestAlign();
//---------------------------------------------------------------------------
#endif
