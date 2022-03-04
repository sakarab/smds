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

const std_char *BDE_DirData_Conn = CCTEXT( "DirData"                                "\r\n" )
                                   CCTEXT( "DATABASE NAME=G:\\Data\\Dirdata82.mdb"  "\r\n" )
                                   CCTEXT( "USER NAME=Admin"                        "\r\n" )
                                   CCTEXT( "OPEN MODE=READ/WRITE"                   "\r\n" )
                                   CCTEXT( "LANGDRIVER="                            "\r\n" )
                                   CCTEXT( "SYSTEM DATABASE="                       "\r\n" )
                                   CCTEXT( "PASSWORD=" );

const std_char *ODBC_Access_DirData_Conn = CCTEXT( "DBQ=G:\\Data\\Dirdata82.mdb;" )
                                           CCTEXT( "DefaultDir=G:\\Data;" )
                                           CCTEXT( "Driver={Microsoft Access Driver (*.mdb)};" )
                                           CCTEXT( "DriverId=281;" )
                                           CCTEXT( "FIL=MS Access;" )
                                           CCTEXT( "MaxBufferSize=2048;" )
                                           CCTEXT( "MaxScanRows=8;" )
                                           CCTEXT( "PageTimeout=5;" )
                                           CCTEXT( "SafeTransactions=0;" )
                                           CCTEXT( "Threads=3;" )
                                           CCTEXT( "UID=admin;" )
                                           CCTEXT( "UserCommitSync=Yes;" );

const std_char *ODBC_MsSql_DirData_Conn = CCTEXT( "DRIVER=SQL Native Client;" )
                                          CCTEXT( "UID=sa;" )
                                          CCTEXT( "PWD=123456;" )
                                          CCTEXT( "DATABASE=DirData;" )
                                          CCTEXT( "WSID=SAM2KFAST;" )
                                          CCTEXT( "APP=Microsoft® Windows® Operating System;" )
                                          CCTEXT( "SERVER=Web2kS;" )
                                          CCTEXT( "Description=Dir-Data;" );

const std_char *ODBC_SEn_Conn = CCTEXT( "DRIVER={Microsoft ODBC for Oracle};" )
                                CCTEXT( "UID=s01999;" )
                                CCTEXT( "PWD=s01999;" )
                                CCTEXT( "SERVER=sen9i.world;"; )

const std_char *ODBC_Marine_Conn = CCTEXT( "DSN=Marine;" )
                                   CCTEXT( "UID=dba;" )
                                   CCTEXT( "PWD=sql;" )
                                   CCTEXT( "Start=C:\\SqlAny50\\Win32\\DbEng50;" )
                                   CCTEXT( "DatabaseFile=G:\\Data\\Marine;" )
                                   CCTEXT( "DatabaseName=Marine;" )
                                   CCTEXT( "EngineName=DbLocal;" )
                                   CCTEXT( "AutoStop=yes;" )
                                   CCTEXT( "KeysInSQLStatistics=1;" )
                                   CCTEXT( "PreventNotCapable=0;" )
                                   CCTEXT( "Driver={Sybase SQL Anywhere 5.0};" )
                                   CCTEXT( "LazyAutocommit=0;" )
                                   CCTEXT( "Delphi=0"; )

const std_char *BDE_SENDATA_Conn = CCTEXT( "SENDATA"                            "\r\n" )
                                   CCTEXT( "SERVER NAME=SEN9I.WORLD"            "\r\n" )
                                   CCTEXT( "USER NAME=s01000"                   "\r\n" )
                                   CCTEXT( "NET PROTOCOL=TNS"                   "\r\n" )
                                   CCTEXT( "OPEN MODE=READ/WRITE"               "\r\n" )
                                   CCTEXT( "SCHEMA CACHE SIZE=8"                "\r\n" )
                                   CCTEXT( "LANGDRIVER="                        "\r\n" )
                                   CCTEXT( "SQLQRYMODE="                        "\r\n" )
                                   CCTEXT( "SQLPASSTHRU MODE=SHARED AUTOCOMMIT" "\r\n" )
                                   CCTEXT( "SCHEMA CACHE TIME=-1"               "\r\n" )
                                   CCTEXT( "MAX ROWS=-1"                        "\r\n" )
                                   CCTEXT( "BATCH COUNT=200"                    "\r\n" )
                                   CCTEXT( "ENABLE SCHEMA CACHE=FALSE"          "\r\n" )
                                   CCTEXT( "SCHEMA CACHE DIR="                  "\r\n" )
                                   CCTEXT( "ENABLE BCD=FALSE"                   "\r\n" )
                                   CCTEXT( "ENABLE INTEGERS=TRUE"               "\r\n" )
                                   CCTEXT( "LIST SYNONYMS=NONE"                 "\r\n" )
                                   CCTEXT( "ROWSET SIZE=20"                     "\r\n" )
                                   CCTEXT( "BLOBS TO CACHE=64"                  "\r\n" )
                                   CCTEXT( "BLOB SIZE=32"                       "\r\n" )
                                   CCTEXT( "OBJECT MODE=TRUE"                   "\r\n" )
                                   CCTEXT( "PASSWORD=s01000" );

const std_char *ADO_Dirdata_Conn = CCTEXT( "Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;" )
                                   CCTEXT( "Data Source=G:\\Data\\Dirdata82.mdb;Mode=Share Deny None;" )
                                   CCTEXT( "Extended Properties="""";Persist Security Info=False;" )
                                   CCTEXT( "Jet OLEDB:System database="""";Jet OLEDB:Registry Path="""";" )
                                   CCTEXT( "Jet OLEDB:Database Password="""";Jet OLEDB:Engine Type=5;" )
                                   CCTEXT( "Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;" )
                                   CCTEXT( "Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password="""";" )
                                   CCTEXT( "Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;" )
                                   CCTEXT( "Jet OLEDB:Don't Copy Locale on Compact=False;" )
                                   CCTEXT( "Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False" );

const std_char *DAO_Dirdata_Conn = CCTEXT( "G:\\Data\\DirData82.mdb" );

//---------------------------------------------------------------------------
