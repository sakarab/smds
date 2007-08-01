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
#include <cstddef>
//---------------------------------------------------------------------------
namespace smds
{

/* TODO -osakarab : Rename cFieldDataType_xxx to FieldDataType_xxx */
// these must be in sync with "cFieldDataType" enum in "dsFields.h"
const int cFieldDataType_ftBool      = 0;            // one byte
const int cFieldDataType_ftByte      = 1;            // one byte
const int cFieldDataType_ftShort     = 2;            // two bytes
const int cFieldDataType_ftInteger   = 3;            // four bytes
const int cFieldDataType_ftLongLong  = 4;            // eight bytes
const int cFieldDataType_ftDouble    = 5;
const int cFieldDataType_ftDate      = 6;
const int cFieldDataType_ftTime      = 7;
const int cFieldDataType_ftDateTime  = 8;
const int cFieldDataType_ftGUID      = 9;
const int cFieldDataType_ftString    = 10;           // VARCHAR
const int cFieldDataType_ftWString   = 11;           // VARWCHAR
const int cFieldDataType_ftBlob      = 12;           // variable length blob

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
    virtual IDataProvider * STDCALL CreateDataProvider() = 0;
    virtual void            STDCALL DestroyDataProvider( IDataProvider * conn ) = 0;
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
    virtual bool STDCALL FieldValue( int field_idx, void *buff, unsigned int field_data_size ) = 0;
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
    virtual void STDCALL OpenSql( const char *sql ) = 0;
    virtual void STDCALL CloseSql() = 0;

    virtual bool STDCALL Eof() = 0;
    virtual void STDCALL Next() = 0;

    virtual std::size_t STDCALL GetFieldCount() = 0;
    virtual void STDCALL GetFieldAttributes( int idx, char *name, unsigned int name_buffer_length,
                                               unsigned int& name_buffer_required_length,
                                               unsigned int& field_data_size, int& field_data_type ) = 0;

    virtual bool STDCALL GetFieldValues( IFieldValuesAcceptor *values_acceptor ) = 0;

    virtual void STDCALL StartTransaction() = 0;
    virtual void STDCALL Commit() = 0;
    virtual void STDCALL RollBack() = 0;
    virtual void STDCALL ExecSql( const char *sql ) = 0;

    virtual ~IDataProvider()                                                                    {} // empty;
};

typedef IDatabase * (*Database_Ctor)( const char *connection_string );
typedef void        (*Database_Dtor)( IDatabase *db_engine );
//---------------------------------------------------------------------------
};

#endif

