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
#ifndef SM_DS_CONN_INTF_H
#define SM_DS_CONN_INTF_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
//---------------------------------------------------------------------------
namespace smds
{

// these must be in sync with "cFieldDataType" enum in "dsFields.h"
const int cFieldDataType_ftBool     = 0;
const int cFieldDataType_ftChar     = 1;
const int cFieldDataType_ftWChar    = 2;
const int cFieldDataType_ftShort    = 3;
const int cFieldDataType_ftInteger  = 4;
const int cFieldDataType_ftLong     = 5;
const int cFieldDataType_ftDouble   = 6;
const int cFieldDataType_ftDateTime = 7;
const int cFieldDataType_ftString   = 8;
const int cFieldDataType_ftWString  = 9;
const int cFieldDataType_ftBlob     = 10;

/*
const int FieldDataType_ftBool      = 0;            // one byte
const int FieldDataType_ftByte      = 1;            // one byte
const int FieldDataType_ftShort     = 2;            // two bytes
const int FieldDataType_ftInteger   = 3;            // four bytes
const int FieldDataType_ftLong      = 4;            // eight bytes
const int FieldDataType_ftDouble    = 5;
const int FieldDataType_ftDate      = 6;
const int FieldDataType_ftTime      = 7;
const int FieldDataType_ftDateTime  = 8;
const int FieldDataType_ftGUID      = 9;
const int FieldDataType_ftChar      = 10;           // CHAR(n)
const int FieldDataType_ftString    = 11;           // VARCHAR
const int FieldDataType_ftWChar     = 12;           // WCHAR(n)
const int FieldDataType_ftWString   = 13;           // VARWCHAR
const int FieldDataType_ftBlobn     = 14;           // fixed length blob
const int FieldDataType_ftBlob      = 15;           // variable length blob
*/

class IDataConnection;
class IDataProvider;

//***********************************************************************
//******    IDatabase
//***********************************************************************
class IDatabase
#if defined ( SM_USE_COM_DELPHI_INTERFACE )
    : public IUnknown
#endif
{
public:
    virtual IDataProvider * __stdcall CreateDataProvider() = 0;
    virtual void            __stdcall DestroyDataProvider( IDataProvider * conn ) = 0;
    virtual ~IDatabase()                                                                        {} // empty;
};

//***********************************************************************
//******    IFieldValuesAcceptor
//***********************************************************************
class IFieldValuesAcceptor
#if defined ( SM_USE_COM_DELPHI_INTERFACE )
    : public IUnknown
#endif
{
public:
    virtual bool __stdcall FieldValue( const char *field_name, int field_data_type, const void *data, void *buff, int field_data_size ) = 0;
    virtual ~IFieldValuesAcceptor()                                                             {} // empty;
};

//***********************************************************************
//******    IDataProvider
//***********************************************************************
class IDataProvider
#if defined ( SM_USE_COM_DELPHI_INTERFACE )
    : public IUnknown
#endif
{
public:
    virtual void __stdcall OpenSql( const char *sql ) = 0;
    virtual bool __stdcall Eof() = 0;
    virtual void __stdcall Next() = 0;
    virtual void __stdcall CloseSql() = 0;

    virtual void __stdcall InitDataTransfer() = 0;
    virtual void __stdcall StepInitDataTransfer( const char *field_name, int field_data_size, int field_data_type, const void *data ) = 0;
    virtual void __stdcall EndInitDataTransfer() = 0;

    virtual bool __stdcall GetFieldValues( IFieldValuesAcceptor *values_acceptor ) = 0;
    virtual void __stdcall EndDataTransfer() = 0;

    virtual void __stdcall StartTransaction() = 0;
    virtual void __stdcall Commit() = 0;
    virtual void __stdcall RollBack() = 0;
    virtual void __stdcall ExecSql( const char *sql ) = 0;

    virtual ~IDataProvider()                                                                    {} // empty;
};

typedef IDatabase * (*Database_Ctor)( const char *connection_string );
typedef void        (*Database_Dtor)( IDatabase *db_engine );
//---------------------------------------------------------------------------
};

#endif

