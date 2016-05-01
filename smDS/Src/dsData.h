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
#if ! defined (SM_DS_DATA_H)
#define SM_DS_DATA_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include "dsBuffer.h"
#include "dsConn.h"
#include "dsCompare.h"
#include "dsRecord.h"
#include "dsFields.h"
#include <boost/shared_array.hpp>

namespace smds
{

class UpdateLocker;
class Index;
typedef shared_ptr<Index>   cIndex_ptr;

//***********************************************************************
//******    Tablebase
//***********************************************************************
class Tablebase
#if defined(SM_DS_ENABLE_NOTIFY)
    : public detail::IDataNotify
#endif
#ifdef SM_DS_USE_SMALL_SHARED_PTR
#if defined(SM_DS_ENABLE_NOTIFY)
    ,
#else
    :
#endif
    public boost::shared_in_base<long>
#endif
{
public:
    typedef detail::cRecordIterator     iterator;
private:
    friend class cTableWriter;
    friend class UpdateLocker;

    detail::spData          mData;
#if defined(SM_DS_ENABLE_NOTIFY)
    // IDataNotify
    virtual void RecordAdded( const detail::Data::value_type& value, bool locked );
    virtual void RecordDeleted( const detail::Data::value_type& value );
    virtual void DataOpened( detail::Data& data );
    virtual void DataClosed();
    virtual void UpdateLockReleased();
#endif
    // noncopyable
    CDFASTCALL Tablebase( const Tablebase& src );
    Tablebase& FASTCALL operator=( const Tablebase& src );
protected:
    detail::spData& FASTCALL GetData()                                          { return mData; }
    void FASTCALL SetData( const detail::spData& data )                         { mData = data; }
    detail::DoubleBuffer * FASTCALL GetDoubleBuffer( const cRecord& record )    { return record.GetDoubleBuffer(); }
    int FASTCALL AddBuffer( const cRecord& record )                             { return mData->AddBuffer( record.mRecord ); }

    detail::Data::locate_result::second_type FASTCALL LocateImpl( const OpenValues& values, const OpenFindFields& fields );

    CDFASTCALL Tablebase();
    CDFASTCALL Tablebase( const detail::cFieldDefs_& field_defs );
public:
    virtual CDFASTCALL ~Tablebase();
    const spFieldDefs& FASTCALL GetFieldDefs() const                            { return mData->GetFieldDefs(); }
    bool FASTCALL IsEmpty()                                                     { return mData->is_empty(); }
    int FASTCALL RecordCount()                                                  { return mData->size(); }
    iterator FASTCALL GetIterator()                                             { return iterator( mData ); }

    void FASTCALL Clear()                                                       { mData->Clear(); }
    void FASTCALL CommitUpdates()                                               { mData->CommitUpdates(); }
    cRecord FASTCALL NewRecord();
    iterator FASTCALL AddRecord( const cRecord& record );
    iterator FASTCALL Locate( const Variant& value, const cFindField& field );
    iterator FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields );
};

typedef Tablebase::iterator    record_iterator;

//***********************************************************************
//******    UpdateLocker
//***********************************************************************
#if defined(SM_DS_ENABLE_NOTIFY)
class UpdateLocker
{
private:
    Tablebase&          mTablebase;

    CDFASTCALL UpdateLocker();
    // noncopyable
    CDFASTCALL UpdateLocker( const UpdateLocker& src );
    UpdateLocker& FASTCALL operator=( const UpdateLocker& src );
public:
    template <class T> CDFASTCALL UpdateLocker( shared_ptr<T>& src )
        : mTablebase( *src.get() )
    {
        mTablebase.mData->LockUpdates();
    }
    CDFASTCALL ~UpdateLocker()                                                  { mTablebase.mData->UnlockUpdates(); }
};
#else
class UpdateLocker
{
private:
    CDFASTCALL UpdateLocker();
    // noncopyable
    CDFASTCALL UpdateLocker( const UpdateLocker& src );
    UpdateLocker& FASTCALL operator=( const UpdateLocker& src );
public:
    template <class T> CDFASTCALL UpdateLocker( shared_ptr<T>& src )            {} // empty
};
#endif

//***********************************************************************
//******    Table
//***********************************************************************
typedef shared_ptr<FieldSortCompare>        spFieldSortCompare;

class Table : public Tablebase
{
private:
    ds_string               mSql;
    ds_string               mTableName;
    // methods
    ds_string FASTCALL ConstructSelectFromFields( const char *where_clause );
    ds_string FASTCALL ConstructSelectFromSql( const char *where_clause );
    ds_string FASTCALL ConstructSelect( const char *where_clause );
    detail::Data::value_type FASTCALL NewBuffer_usUnmodified();
    // noncopyable
    CDFASTCALL Table( const Table& src );
    Table& FASTCALL operator=( const Table& src );
protected:
    detail::Data::value_type FASTCALL NewBuffer_usInserted();

    spFieldSortCompare FASTCALL CreateCmp( const cIndexField& index_field );
    spFieldSortCompare FASTCALL CreateCmp( const OpenIndexFields& index_fields );

    CDFASTCALL Table( const detail::cFieldDefs_& field_defs );
public:
    CDFASTCALL Table();
    CDFASTCALL Table( const ds_string& table_name );
    CDFASTCALL Table( const char * table_name );
    virtual CDFASTCALL ~Table();

    const ds_string& GetTableName()                     { return ( mTableName ); }

    void FASTCALL AddField( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned int size );
    void FASTCALL AddField( const char *name, cFieldKind kind, cFieldDataType data_type, unsigned int size );
    void FASTCALL Open( const Database& database, const char *where_clause );
    void FASTCALL Close();

    // sort only
    cIndex_ptr FASTCALL NewIndex( const cIndexField& index_field );
    cIndex_ptr FASTCALL NewIndex( const OpenIndexFields& index_fields );
    cIndex_ptr FASTCALL NewIndex( const spFieldSortCompare& cmp_func );
};

typedef shared_ptr<Table>       spTable;

inline bool FASTCALL LocateSucceeded( const record_iterator& iter )
{
    return ( ! iter.eof() );
}

inline bool FASTCALL FindSucceeded( const record_iterator& iter )
{
    return ( ! iter.eof() );
}

//***********************************************************************
//******    cTableSerializingData
//***********************************************************************
class cTableSerializingData
{
protected:
    static const char  PacketMagic[];
    static const int   PacketVersion;
};

//***********************************************************************
//******    cTableReader
//***********************************************************************
class cTableReader : private cTableSerializingData
{
private:
    static void FASTCALL ReadFieldValue( cStream& st, const detail::cRawBuffer& rb, const cFieldDef& field );
public:
    /* TODO -osakarab : parameter must be const */
    static Variant FASTCALL GetTablePacket( Table& table );
    template <class T> static Variant FASTCALL GetTablePacket( shared_ptr<T>& table )
    {
        return ( GetTablePacket( *table.get() ) );
    }
};

//***********************************************************************
//******    cTableWriter
//***********************************************************************
class cTableWriter : private cTableSerializingData
{
private:
    static void FASTCALL CheckMagic( cStream& st );
    static void FASTCALL CheckVersion( cStream& st );
    static void FASTCALL Check( cStream& st );
    //static void FASTCALL CheckFieldDefsEqual( Table& tmp, Table& table );
    static void FASTCALL ReadFieldDefs( cStream& st, Table& tmp, bool is_typed );
    static void FASTCALL ReadData( cStream& st, Table& tmp );
    static void FASTCALL ReadDataAssign( cStream& st, Table& tmp, Table& table );
    static void FASTCALL ReadFieldValue( cStream& st, detail::cRawBuffer& rb, const cFieldDef& field );
    static void FASTCALL ReadTheRest( Table& tmp, Table& table, Variant& variant, bool is_typed );
    static spTable FASTCALL CreateTemporaryTable();
public:
    static void FASTCALL SetTableData( Table& table, Variant& variant );
    template <class T> static void FASTCALL SetTableData( shared_ptr<T>& table, Variant& variant )
    {
        spTable     tmp( new T() );

        ReadTheRest( *tmp, *table, variant, true );
    }
};

}; // namespace smds
//---------------------------------------------------------------------------
#endif

