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
#include "dsIndex.h"
#include "dsRecord.h"
#include "dsFields.h"
#include <boost/shared_array.hpp>

namespace smds
{

//***********************************************************************
//******    Tablebase
//***********************************************************************
class Tablebase
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
{
public:
    typedef detail::cRecordIterator     iterator;
private:
    friend class cTableWriter;

    detail::cData_ptr       mData;
    // noncopyable
    CDFASTCALL Tablebase( const Tablebase& src );
    Tablebase& FASTCALL operator=( const Tablebase& src );
protected:
    detail::cData_ptr& FASTCALL GetData()                                       { return mData; }
    void FASTCALL SetData( const detail::cData_ptr& data )                      { mData = data; }
    detail::cDoubleBuffer * FASTCALL GetDoubleBuffer( const cRecord& record )   { return record.GetDoubleBuffer(); }
    int FASTCALL AddBuffer_ptr( const cRecord& record )                         { return mData->AddBuffer_ptr( record.mRecord ); }

    CDFASTCALL Tablebase();
    CDFASTCALL Tablebase( const detail::cFieldDefs_& field_defs );
public:
    virtual CDFASTCALL ~Tablebase();
    const cFieldDefs_ptr& FASTCALL GetFieldDefs() const                         { return mData->GetFieldDefs(); }
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
//******    Index
//***********************************************************************
class Index : public Tablebase
{
public:
    typedef detail::cRangeIterator      range_iterator;
private:
    typedef detail::cData_ptr       container;
    friend class Table;            // next to eliminate

    cSortCompareBase_ptr    mCompare;
    cFilterCompareBase_ptr  mFilter;
    // noncopyable
    CDFASTCALL Index( const Index& src );
    Index& FASTCALL operator=( const Index& src );
protected:
    // CDFASTCALL Index();
    CDFASTCALL Index( const cSortCompareBase_ptr& cmp_func, const detail::cData_ptr& data );
public:
    virtual CDFASTCALL ~Index();
    iterator FASTCALL Find( const Variant& value );
    iterator FASTCALL Find( const OpenValues& values );
    bool FASTCALL Find( const Variant& value, iterator& iter );
    bool FASTCALL Find( const OpenValues& values, iterator& iter );
    bool FASTCALL Find( const Variant& value, range_iterator& iter );
    bool FASTCALL Find( const OpenValues& values, range_iterator& iter );
    // iterator FASTCALL GetIterator()                                         { return Tablebase::GetIterator(); }
    // Index FASTCALL GetRange( const cRangeValues& values );
    // Index FASTCALL GetRange( const OpenRangeValues& values );
};

typedef shared_ptr<Index>      cIndex_ptr;

//***********************************************************************
//******    Table
//***********************************************************************
typedef shared_ptr<detail::cIndexSortCompareStd>        cIndexSortCompareStd_ptr;

class Table : public Tablebase
{
private:
    ds_string               mSql;
    ds_string               mTableName;
    // methods
    ds_string FASTCALL ConstructSelectFromFields( const char *where_clause );
    ds_string FASTCALL ConstructSelectFromSql( const char *where_clause );
    ds_string FASTCALL ConstructSelect( const char *where_clause );
    detail::cData::value_type FASTCALL NewBuffer_usUnmodified();
    // noncopyable
    CDFASTCALL Table( const Table& src );
    Table& FASTCALL operator=( const Table& src );
protected:
    detail::cData::value_type FASTCALL NewBuffer_usInserted();

    cIndexSortCompareStd_ptr FASTCALL CreateCmp( const cIndexField& index_field );
    cIndexSortCompareStd_ptr FASTCALL CreateCmp( const OpenIndexFields& index_fields );

    CDFASTCALL Table( const detail::cFieldDefs_& field_defs );
public:
    CDFASTCALL Table();
    CDFASTCALL Table( const ds_string& table_name );
    CDFASTCALL Table( const char * table_name );
    virtual CDFASTCALL ~Table();

    const ds_string& GetTableName()                     { return ( mTableName ); }

    void FASTCALL AddField( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned short size );
    void FASTCALL AddField( const char *name, cFieldKind kind, cFieldDataType data_type, unsigned short size );
    void FASTCALL Open( const cDatabase& database, const char *where_clause );
    void FASTCALL Close();

    // sort only
    cIndex_ptr FASTCALL NewIndex( const cIndexField& index_field );
    cIndex_ptr FASTCALL NewIndex( const OpenIndexFields& index_fields );
    cIndex_ptr FASTCALL NewIndex( const cIndexSortCompareStd_ptr& cmp_func );
};

typedef shared_ptr< Table >    cTable_ptr;

//***********************************************************************
//******    cuIndex<>
//***********************************************************************
template <class RECORD> class cuIndex : public Index
{
public:
    typedef detail::cuRecordIterator<RECORD>    iterator;
private:
    friend class cuTable<RECORD>;
    // noncopyable
    CDFASTCALL cuIndex( const cuIndex& src );
    cuIndex& FASTCALL operator=( const cuIndex& src );
protected:
    CDFASTCALL cuIndex()
        : Index()
    {
    }
    CDFASTCALL cuIndex( const cSortCompareBase_ptr& cmp_func, const detail::cData_ptr& data )
        : Index( cmp_func, data )
    {
    }
public:
    virtual CDFASTCALL ~cuIndex()                                           {} // empty
    iterator FASTCALL GetIterator()                                         { return iterator( Index::GetIterator() ); }
    iterator FASTCALL Locate( const Variant& value, const cFindField& field )
    {
        return ( iterator( Index::Locate( value, field ) ) );
    }
    iterator FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields )
    {
        return ( iterator( Index::Locate( values, fields ) ) );
    }
    iterator FASTCALL Find( const Variant& value )                              { return ( iterator( Index::Find( value ) ) ); }
    iterator FASTCALL Find( const OpenValues& values )                          { return ( iterator( Index::Find( values ) ) ); }
    bool FASTCALL Find( const Variant& value, iterator& iter )                  { return ( Index::Find( value, iter ) ); }
    bool FASTCALL Find( const OpenValues& values, iterator& iter )              { return ( Index::Find( values, iter ) ); }
};

//***********************************************************************
//******    cuTable<>
//***********************************************************************
template <class RECORD> class cuTable : public Table
{
public:
    typedef detail::cuRecordIterator<RECORD>    iterator;
private:
    typedef RECORD                      record_type;

    template <class RECORD_> class cIndexSortCompare : public detail::cSortCompareBase
    {
    private:
        virtual bool FASTCALL do_compare_1( detail::cRawBuffer *item1, detail::cRawBuffer *item2 )
        {
#ifdef __BORLANDC__
            return ( do_compare_2( RECORD_::raw( *item1 ), RECORD_::raw( *item2 ) ) );
#else
            return ( do_compare_2( typename RECORD_::raw( *item1 ), typename RECORD_::raw( *item2 ) ) );
#endif
        }
    protected:
        virtual bool FASTCALL do_compare_2( const typename RECORD_::raw& item1, const typename RECORD_::raw& item2 ) = 0;
    };

    template <class RECORD_> class cFilterCompare : public detail::cFilterCompareBase
    {
    private:
        virtual bool FASTCALL do_compare_1( detail::cRawBuffer *item1 )
        {
            return ( do_compare_2( typename RECORD_::raw( *item1 ) ) );
        }
    protected:
        virtual bool FASTCALL do_compare_2( const typename RECORD_::raw& item1 ) = 0;
    };
public:
#ifndef __BORLANDC__
    using Table::Locate;
#endif
    typedef cuRecord<RECORD>                    record;
    typedef cuIndex<RECORD>                     index;
    typedef shared_ptr< cuIndex<RECORD> >       index_ptr;
    typedef cIndexSortCompare<RECORD>           sort_compare;
    typedef cFilterCompare<RECORD>              filter_compare;
    typedef typename RECORD::raw                raw;
private:
    // noncopyable
    CDFASTCALL cuTable( const cuTable& src );
    cuTable& FASTCALL operator=( const cuTable& src );
public:
    CDFASTCALL cuTable() : Table( RECORD::GetFieldDefs() )                      {} // empty
    virtual CDFASTCALL ~cuTable()                                               {} // empty

    index_ptr FASTCALL NewIndex( const cSortCompareBase_ptr& cmp_func )
    {
        return index_ptr( new index( cmp_func, GetData() ) );
    }

    index_ptr FASTCALL NewIndex( const cIndexSortCompareStd_ptr& cmp_func )
    {
        return index_ptr( new index( cmp_func, GetData() ) );
    }

    index_ptr FASTCALL NewIndex( const cIndexField& index_field )
    {
        return index_ptr( new index( CreateCmp( index_field ), GetData() ) );
    }

    index_ptr FASTCALL NewIndex( const OpenIndexFields& index_fields )
    {
        return index_ptr( new index( CreateCmp( index_fields ), GetData() ) );
    }

    iterator FASTCALL GetIterator()                                             { return Table::GetIterator(); }
    record FASTCALL NewRecord()                                                 { return record( NewBuffer_usInserted(), GetFieldDefs() ); }
    iterator FASTCALL AddRecord( const record& rec )                            { return iterator( GetData(), AddBuffer_ptr( rec ) ); }
    iterator FASTCALL Locate( const Variant& value, const cFindField& field )
    {
        return ( iterator( Table::Locate( value, field ) ) );
    }
    iterator FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields )
    {
        return ( iterator( Table::Locate( values, fields ) ) );
    }
#ifdef __BORLANDC__
    bool FASTCALL Locate( const Variant& value, const cFindField& field, iterator& iter )
    {
        return ( Table::Locate( value, field, iter ) );
    }
    bool FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields, iterator& iter )
    {
        return ( Table::Locate( values, fields, iter ) );
    }
#endif
};

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
    /* TODO -oSam : parameter must be const */
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
    static cTable_ptr FASTCALL CreateTemporaryTable();
public:
    static void FASTCALL SetTableData( Table& table, Variant& variant );
    template <class T> static void FASTCALL SetTableData( shared_ptr<T>& table, Variant& variant )
    {
        cTable_ptr      tmp( new T() );

        ReadTheRest( *tmp, *table, variant, true );
    }
};

}; // namespace smds
//---------------------------------------------------------------------------
#endif

