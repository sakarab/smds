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

#include "pre_test.h"
#include "uConnectionStrings.h"
//---------------------------------------------------------------------------

const char *BDE_DirData_Conn = "DirData"                                "\r\n"
                               "DATABASE NAME=G:\\Data\\Dirdata82.mdb"  "\r\n"
                               "USER NAME=Admin"                        "\r\n"
                               "OPEN MODE=READ/WRITE"                   "\r\n"
                               "LANGDRIVER="                            "\r\n"
                               "SYSTEM DATABASE="                       "\r\n"
                               "PASSWORD=";

const char *ODBC_Access_DirData_Conn =  "DBQ=G:\\Data\\Dirdata82.mdb;"
                                        "DefaultDir=G:\\Data;"
                                        "Driver={Microsoft Access Driver (*.mdb)};"
                                        "DriverId=281;"
                                        "FIL=MS Access;"
                                        "MaxBufferSize=2048;"
                                        "MaxScanRows=8;"
                                        "PageTimeout=5;"
                                        "SafeTransactions=0;"
                                        "Threads=3;"
                                        "UID=admin;"
                                        "UserCommitSync=Yes;";

const char *ODBC_MsSql_DirData_Conn =   "DRIVER=SQL Native Client;"
                                        "UID=sa;"
                                        "PWD=123456;"
                                        "DATABASE=DirData;"
                                        "WSID=SAM2KFAST;"
                                        "APP=Microsoft® Windows® Operating System;"
                                        "SERVER=Web2kS;"
                                        "Description=Dir-Data;";

const char *ODBC_SEn_Conn = "DRIVER={Microsoft ODBC for Oracle};"
                            "UID=s01999;"
                            "PWD=s01999;"
                            "SERVER=sen9i.world;";

const char *ODBC_Marine_Conn = "DSN=Marine;"
                               "UID=dba;"
                               "PWD=sql;"
                               "Start=C:\\SqlAny50\\Win32\\DbEng50;"
                               "DatabaseFile=G:\\Data\\Marine;"
                               "DatabaseName=Marine;"
                               "EngineName=DbLocal;"
                               "AutoStop=yes;"
                               "KeysInSQLStatistics=1;"
                               "PreventNotCapable=0;"
                               "Driver={Sybase SQL Anywhere 5.0};"
                               "LazyAutocommit=0;"
                               "Delphi=0";


const char *BDE_SENDATA_Conn = "SENDATA"                            "\r\n"
                               "SERVER NAME=SEN9I.WORLD"            "\r\n"
                               "USER NAME=s01000"                   "\r\n"
                               "NET PROTOCOL=TNS"                   "\r\n"
                               "OPEN MODE=READ/WRITE"               "\r\n"
                               "SCHEMA CACHE SIZE=8"                "\r\n"
                               "LANGDRIVER="                        "\r\n"
                               "SQLQRYMODE="                        "\r\n"
                               "SQLPASSTHRU MODE=SHARED AUTOCOMMIT" "\r\n"
                               "SCHEMA CACHE TIME=-1"               "\r\n"
                               "MAX ROWS=-1"                        "\r\n"
                               "BATCH COUNT=200"                    "\r\n"
                               "ENABLE SCHEMA CACHE=FALSE"          "\r\n"
                               "SCHEMA CACHE DIR="                  "\r\n"
                               "ENABLE BCD=FALSE"                   "\r\n"
                               "ENABLE INTEGERS=TRUE"               "\r\n"
                               "LIST SYNONYMS=NONE"                 "\r\n"
                               "ROWSET SIZE=20"                     "\r\n"
                               "BLOBS TO CACHE=64"                  "\r\n"
                               "BLOB SIZE=32"                       "\r\n"
                               "OBJECT MODE=TRUE"                   "\r\n"
                               "PASSWORD=s01000";

const char *ADO_Dirdata_Conn =  "Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;"
                                "Data Source=G:\\Data\\Dirdata82.mdb;Mode=Share Deny None;"
                                "Extended Properties="""";Persist Security Info=False;"
                                "Jet OLEDB:System database="""";Jet OLEDB:Registry Path="""";"
                                "Jet OLEDB:Database Password="""";Jet OLEDB:Engine Type=5;"
                                "Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;"
                                "Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password="""";"
                                "Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;"
                                "Jet OLEDB:Don't Copy Locale on Compact=False;"
                                "Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False";

const char *DAO_Dirdata_Conn =  "G:\\Data\\DirData82.mdb";

//---------------------------------------------------------------------------
