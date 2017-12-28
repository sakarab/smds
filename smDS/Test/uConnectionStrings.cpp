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
#include "pre_test.h"
#include "uConnectionStrings.h"
//---------------------------------------------------------------------------

const std_char *BDE_DirData_Conn =  CCLIB_STRING( "DirData"                                "\r\n" )
                                    CCLIB_STRING( "DATABASE NAME=G:\\Data\\Dirdata82.mdb"  "\r\n" )
                                    CCLIB_STRING( "USER NAME=Admin"                        "\r\n" )
                                    CCLIB_STRING( "OPEN MODE=READ/WRITE"                   "\r\n" )
                                    CCLIB_STRING( "LANGDRIVER="                            "\r\n" )
                                    CCLIB_STRING( "SYSTEM DATABASE="                       "\r\n" )
                                    CCLIB_STRING( "PASSWORD=" );

const std_char *ODBC_Access_DirData_Conn =  CCLIB_STRING( "DBQ=G:\\Data\\Dirdata82.mdb;" )
                                            CCLIB_STRING( "DefaultDir=G:\\Data;" )
                                            CCLIB_STRING( "Driver={Microsoft Access Driver (*.mdb)};" )
                                            CCLIB_STRING( "DriverId=281;" )
                                            CCLIB_STRING( "FIL=MS Access;" )
                                            CCLIB_STRING( "MaxBufferSize=2048;" )
                                            CCLIB_STRING( "MaxScanRows=8;" )
                                            CCLIB_STRING( "PageTimeout=5;" )
                                            CCLIB_STRING( "SafeTransactions=0;" )
                                            CCLIB_STRING( "Threads=3;" )
                                            CCLIB_STRING( "UID=admin;" )
                                            CCLIB_STRING( "UserCommitSync=Yes;" );

const std_char *ODBC_MsSql_DirData_Conn =   CCLIB_STRING( "DRIVER=SQL Native Client;" )
                                            CCLIB_STRING( "UID=sa;" )
                                            CCLIB_STRING( "PWD=123456;" )
                                            CCLIB_STRING( "DATABASE=DirData;" )
                                            CCLIB_STRING( "WSID=SAM2KFAST;" )
                                            CCLIB_STRING( "APP=Microsoft® Windows® Operating System;" )
                                            CCLIB_STRING( "SERVER=Web2kS;" )
                                            CCLIB_STRING( "Description=Dir-Data;" );

const std_char *ODBC_SEn_Conn = CCLIB_STRING( "DRIVER={Microsoft ODBC for Oracle};" )
                                CCLIB_STRING( "UID=s01999;" )
                                CCLIB_STRING( "PWD=s01999;" )
                                CCLIB_STRING( "SERVER=sen9i.world;"; )

const std_char *ODBC_Marine_Conn = CCLIB_STRING( "DSN=Marine;" )
                                   CCLIB_STRING( "UID=dba;" )
                                   CCLIB_STRING( "PWD=sql;" )
                                   CCLIB_STRING( "Start=C:\\SqlAny50\\Win32\\DbEng50;" )
                                   CCLIB_STRING( "DatabaseFile=G:\\Data\\Marine;" )
                                   CCLIB_STRING( "DatabaseName=Marine;" )
                                   CCLIB_STRING( "EngineName=DbLocal;" )
                                   CCLIB_STRING( "AutoStop=yes;" )
                                   CCLIB_STRING( "KeysInSQLStatistics=1;" )
                                   CCLIB_STRING( "PreventNotCapable=0;" )
                                   CCLIB_STRING( "Driver={Sybase SQL Anywhere 5.0};" )
                                   CCLIB_STRING( "LazyAutocommit=0;" )
                                   CCLIB_STRING( "Delphi=0"; )

const std_char *BDE_SENDATA_Conn = CCLIB_STRING( "SENDATA"                            "\r\n" )
                                   CCLIB_STRING( "SERVER NAME=SEN9I.WORLD"            "\r\n" )
                                   CCLIB_STRING( "USER NAME=s01000"                   "\r\n" )
                                   CCLIB_STRING( "NET PROTOCOL=TNS"                   "\r\n" )
                                   CCLIB_STRING( "OPEN MODE=READ/WRITE"               "\r\n" )
                                   CCLIB_STRING( "SCHEMA CACHE SIZE=8"                "\r\n" )
                                   CCLIB_STRING( "LANGDRIVER="                        "\r\n" )
                                   CCLIB_STRING( "SQLQRYMODE="                        "\r\n" )
                                   CCLIB_STRING( "SQLPASSTHRU MODE=SHARED AUTOCOMMIT" "\r\n" )
                                   CCLIB_STRING( "SCHEMA CACHE TIME=-1"               "\r\n" )
                                   CCLIB_STRING( "MAX ROWS=-1"                        "\r\n" )
                                   CCLIB_STRING( "BATCH COUNT=200"                    "\r\n" )
                                   CCLIB_STRING( "ENABLE SCHEMA CACHE=FALSE"          "\r\n" )
                                   CCLIB_STRING( "SCHEMA CACHE DIR="                  "\r\n" )
                                   CCLIB_STRING( "ENABLE BCD=FALSE"                   "\r\n" )
                                   CCLIB_STRING( "ENABLE INTEGERS=TRUE"               "\r\n" )
                                   CCLIB_STRING( "LIST SYNONYMS=NONE"                 "\r\n" )
                                   CCLIB_STRING( "ROWSET SIZE=20"                     "\r\n" )
                                   CCLIB_STRING( "BLOBS TO CACHE=64"                  "\r\n" )
                                   CCLIB_STRING( "BLOB SIZE=32"                       "\r\n" )
                                   CCLIB_STRING( "OBJECT MODE=TRUE"                   "\r\n" )
                                   CCLIB_STRING( "PASSWORD=s01000" );

const std_char *ADO_Dirdata_Conn =  CCLIB_STRING( "Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;" )
                                    CCLIB_STRING( "Data Source=G:\\Data\\Dirdata82.mdb;Mode=Share Deny None;" )
                                    CCLIB_STRING( "Extended Properties="""";Persist Security Info=False;" )
                                    CCLIB_STRING( "Jet OLEDB:System database="""";Jet OLEDB:Registry Path="""";" )
                                    CCLIB_STRING( "Jet OLEDB:Database Password="""";Jet OLEDB:Engine Type=5;" )
                                    CCLIB_STRING( "Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;" )
                                    CCLIB_STRING( "Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password="""";" )
                                    CCLIB_STRING( "Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;" )
                                    CCLIB_STRING( "Jet OLEDB:Don't Copy Locale on Compact=False;" )
                                    CCLIB_STRING( "Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False" );

const std_char *DAO_Dirdata_Conn =  CCLIB_STRING( "G:\\Data\\DirData82.mdb" );

//---------------------------------------------------------------------------
