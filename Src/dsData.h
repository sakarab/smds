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

namespace ds
{

//***********************************************************************
//******    cTablebase
//***********************************************************************
class cTablebase
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
{
public:
    typedef cRecordIterator         iterator;
    typedef cRangeIterator          range_iterator;
private:
    friend class cTableWriter;

    cData_ptr       mData;
    // noncopyable
    CDFASTCALL cTablebase( const cTablebase& src );
    cTablebase& FASTCALL operator=( const cTablebase& src );
protected:
    cData_ptr& FASTCALL GetData()                                               { return ( mData ); }
    void FASTCALL SetData( const cData_ptr& data )                              { mData = data; }
    cDoubleBuffer * FASTCALL GetDoubleBuffer( const cRecord& record )           { return ( record.GetDoubleBuffer() ); }
    int FASTCALL AddBuffer_ptr( const cRecord& record )                         { return ( mData->AddBuffer_ptr( record.mRecord ) ); }
    CDFASTCALL cTablebase();
    CDFASTCALL cTablebase( const cFieldDefs_& field_defs );
public:
    virtual CDFASTCALL ~cTablebase();
    const cFieldDefs_ptr& FASTCALL GetFieldDefs() const                         { return ( mData->GetFieldDefs() ); }
    int FASTCALL RecordCount()                                                  { return ( mData->size() ); }
    iterator FASTCALL GetIterator()                                             { return ( iterator( mData ) ); }

    void FASTCALL Clear()                                                       { mData->Clear(); }
    void FASTCALL CommitUpdates()                                               { mData->CommitUpdates(); }
    cRecord FASTCALL NewRecord();
    iterator FASTCALL AddRecord( const cRecord& record );
    iterator FASTCALL Locate( const Variant& value, const cFindField& field );
    iterator FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields );
    bool FASTCALL Locate( const Variant& value, const cFindField& field, iterator& iter );
    bool FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields, iterator& iter );
    bool FASTCALL Locate( const Variant& value, const cFindField& field, range_iterator& iter );
    bool FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields, range_iterator& iter );
};

//***********************************************************************
//******    cIndex
//***********************************************************************
class cIndex : public cTablebase
{
private:
    typedef cData_ptr               container;
    friend class cTable;            // next to eliminate

    cSortCompareBase_ptr    mCompare;
    cFilterCompareBase_ptr  mFilter;
    // noncopyable
    CDFASTCALL cIndex( const cIndex& src );
    cIndex& FASTCALL operator=( const cIndex& src );
protected:
    void FASTCALL Construct( const cSortCompareBase_ptr& cmp_func, const cData_ptr& data );
    CDFASTCALL cIndex();
public:
    virtual CDFASTCALL ~cIndex();
    iterator FASTCALL Find( const Variant& value );
    iterator FASTCALL Find( const OpenValues& values );
    bool FASTCALL Find( const Variant& value, iterator& iter );
    bool FASTCALL Find( const OpenValues& values, iterator& iter );
    bool FASTCALL Find( const Variant& value, range_iterator& iter );
    bool FASTCALL Find( const OpenValues& values, range_iterator& iter );
    iterator FASTCALL GetIterator()                                         { return ( iterator( GetData() ) ); }
    range_iterator FASTCALL GetRangeIterator( const cRangeValues& values );
    range_iterator FASTCALL GetRangeIterator( const OpenRangeValues& values );
};

typedef shared_ptr<cIndex>      cIndex_ptr;

//***********************************************************************
//******    cuIndex<>
//***********************************************************************
template <class RECORD> class cuIndex : public cIndex
{
public:
    typedef RECORD                          record_type;
    typedef cuRecordIterator<RECORD>        iterator;
    typedef cuRangeIterator<RECORD>         range_iterator;
private:
    typedef cIndex                          inherited;
    template <class RECORD> friend class cuTable;
    // noncopyable
    CDFASTCALL cuIndex( const cuIndex& src );
    cuIndex& FASTCALL operator=( const cuIndex& src );
protected:
    CDFASTCALL cuIndex() : cIndex()                                         {} // empty
public:
    virtual CDFASTCALL ~cuIndex()                                           {} // empty
    iterator FASTCALL GetIterator()                                         { return ( iterator( GetData() ) ); }
    range_iterator FASTCALL GetRangeIterator( const cRangeValues& values )
    {
        return ( range_iterator( inherited::GetRangeIterator( values ) ) );
    }
    range_iterator FASTCALL GetRangeIterator( const OpenRangeValues& values )
    {
        return ( range_iterator( inherited::GetRangeIterator( values ) ) );
    }
    iterator FASTCALL Locate( const Variant& value, const cFindField& field )
    {
        return ( iterator( inherited::Locate( values, field ) ) );
    }
    iterator FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields )
    {
        return ( iterator( inherited::Locate( values, fields ) ) );
    }
    iterator FASTCALL Find( const Variant& value )                              { return ( iterator( inherited::Find( value ) ) ); }
    iterator FASTCALL Find( const OpenValues& values )                          { return ( iterator( inherited::Find( values ) ) ); }
    bool FASTCALL Find( const Variant& value, iterator& iter )                  { return ( inherited::Find( value, iter ) ); }
    bool FASTCALL Find( const OpenValues& values, iterator& iter )              { return ( inherited::Find( values, iter ) ); }
    bool FASTCALL Find( const Variant& value, range_iterator& iter )            { return ( inherited::Find( value, iter ) ); }
    bool FASTCALL Find( const OpenValues& values, range_iterator& iter )        { return ( inherited::Find( values, iter ) ); }
};

//***********************************************************************
//******    cTable
//***********************************************************************
typedef shared_ptr<cIndexSortCompareStd>        cIndexSortCompareStd_ptr;

class cTable : public cTablebase
{
private:
    ds_string               mSql;
    ds_string               mTableName;
    // methods
    ds_string FASTCALL ConstructSelectFromFields( const char *where_clause );
    ds_string FASTCALL ConstructSelectFromSql( const char *where_clause );
    ds_string FASTCALL ConstructSelect( const char *where_clause );
    cData::value_type FASTCALL NewBuffer_usUnmodified();
    // noncopyable
    CDFASTCALL cTable( const cTable& src );
    cTable& FASTCALL operator=( const cTable& src );
protected:
    cData::value_type FASTCALL NewBuffer_usInserted();

    cIndex * FASTCALL ConstructIndex( cIndex *index, const cSortCompareBase_ptr& cmp_func );
    cIndex * FASTCALL ConstructIndex( cIndex *index, const cIndexField& index_field );
    cIndex * FASTCALL ConstructIndex( cIndex *index, const OpenIndexFields& index_fields );

    CDFASTCALL cTable( const cFieldDefs_& field_defs );
public:
    CDFASTCALL cTable();
    CDFASTCALL cTable( const ds_string& table_name );
    CDFASTCALL cTable( const char * table_name );
    virtual CDFASTCALL ~cTable();

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

typedef shared_ptr< cTable >    cTable_ptr;

//***********************************************************************
//******    cuTable<>
//***********************************************************************
template <class RECORD> class cuTable : public cTable
{
private:
    typedef cTable                      inherited;
    typedef RECORD                      record_type;

    template <class RECORD> class cIndexSortCompare : public cSortCompareBase
    {
    protected:
        virtual bool FASTCALL do_compare_2( const typename RECORD::raw& item1, const typename RECORD::raw& item2 ) = 0;
        virtual bool FASTCALL do_compare_1( cRawBuffer *item1, cRawBuffer *item2 )
        {
            return ( do_compare_2( RECORD::raw( *item1 ), RECORD::raw( *item2 ) ) );
        }
    };

    template <class RECORD> class cFilterCompare : public cFilterCompareBase
    {
    protected:
        virtual bool FASTCALL do_compare_2( const typename RECORD::raw& item1 ) = 0;
        virtual bool FASTCALL do_compare_1( cRawBuffer *item1 )
        {
            return ( do_compare_2( RECORD::raw( *item1 ) ) );
        }
    };

public:
#ifndef __BORLANDC__
    using cTable::Locate;
#endif
    typedef cuRecordIterator<RECORD>            iterator;
    typedef cuRecord<RECORD>                    record;
    typedef cuIndex<RECORD>                     index;
    typedef shared_ptr< cuIndex<RECORD> >       index_ptr;
    typedef cIndexSortCompare<RECORD>           sort_compare;
    typedef cFilterCompare<RECORD>              filter_compare;
    typedef typename RECORD::raw                raw;
private:
    index * FASTCALL ConstructIndex( index *index, const cSortCompareBase_ptr& cmp_func )
    {
        inherited::ConstructIndex( index, cmp_func );
        return ( index );
    }
    index * FASTCALL ConstructIndex( index *index, const cIndexField& index_field )
    {
        inherited::ConstructIndex( index, index_field );
        return ( index );
    }
    index * FASTCALL ConstructIndex( index *index, const OpenIndexFields& index_fields )
    {
        inherited::ConstructIndex( index, index_fields );
        return ( index );
    }
    // noncopyable
    CDFASTCALL cuTable( const cuTable& src );
    cuTable& FASTCALL operator=( const cuTable& src );
public:
    CDFASTCALL cuTable() : cTable( RECORD::GetFieldDefs() )                     {} // empty
    virtual CDFASTCALL ~cuTable()                                               {} // empty

    index_ptr FASTCALL NewIndex( const cSortCompareBase_ptr& cmp_func )
    {
        return ( index_ptr( ConstructIndex( new index(), cmp_func ) ) );
    }

    index_ptr FASTCALL NewIndex( const cIndexSortCompareStd_ptr& cmp_func )
    {
        return ( index_ptr( ConstructIndex( new index(), cmp_func ) ) );
    }

    index_ptr FASTCALL NewIndex( const cIndexField& index_field )
    {
        return ( index_ptr( ConstructIndex( new index(), index_field ) ) );
    }

    index_ptr FASTCALL NewIndex( const OpenIndexFields& index_fields )
    {
        return ( index_ptr( ConstructIndex( new index(), index_fields ) ) );
    }

    iterator FASTCALL GetIterator()                                             { return ( iterator( GetData() ) ); }
    record FASTCALL NewRecord()                                                 { return ( record( NewBuffer_usInserted(), GetFieldDefs() ) ); }
    iterator FASTCALL AddRecord( const record& rec )                            { return ( iterator( GetData(), AddBuffer_ptr( rec ) ) ); }
    iterator FASTCALL Locate( const Variant& value, const cFindField& field )
    {
        return ( iterator( inherited::Locate( value, field ) ) );
    }
    iterator FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields )
    {
        return ( iterator( inherited::Locate( values, fields ) ) );
    }
#ifdef __BORLANDC__
    bool FASTCALL Locate( const Variant& value, const cFindField& field, iterator& iter )
    {
        return ( inherited::Locate( value, field, iter ) );
    }
    bool FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields, iterator& iter )
    {
        return ( inherited::Locate( values, fields, iter ) );
    }
    bool FASTCALL Locate( const Variant& value, const cFindField& field, range_iterator& iter )
    {
        return ( inherited::Locate( value, field, iter ) );
    }
    bool FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields, range_iterator& iter )
    {
        return ( inherited::Locate( values, fields, iter ) );
    }
#endif
};

inline bool FASTCALL LocateSucceeded( const cRecordIterator& iter )
{
    return ( ! iter.eof() );
}

inline bool FASTCALL FindSucceeded( const cRecordIterator& iter )
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
    static void FASTCALL ReadFieldValue( cStream& st, const cRawBuffer& rb, const cFieldDef& field );
public:
    /* TODO -oSam : parameter must be const */
    static Variant FASTCALL GetTablePacket( cTable& table );
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
    //static void FASTCALL CheckFieldDefsEqual( cTable& tmp, cTable& table );
    static void FASTCALL ReadFieldDefs( cStream& st, cTable& tmp, bool is_typed );
    static void FASTCALL ReadData( cStream& st, cTable& tmp );
    static void FASTCALL ReadDataAssign( cStream& st, cTable& tmp, cTable& table );
    static void FASTCALL ReadFieldValue( cStream& st, cRawBuffer& rb, const cFieldDef& field );
    static void FASTCALL ReadTheRest( cTable& tmp, cTable& table, Variant& variant, bool is_typed );
    static cTable_ptr FASTCALL CreateTemporaryTable();
public:
    static void FASTCALL SetTableData( cTable& table, Variant& variant );
    template <class T> static void FASTCALL SetTableData( shared_ptr<T>& table, Variant& variant )
    {
        cTable_ptr      tmp( new T() );

        ReadTheRest( *tmp, *table, variant, true );
    }
};

};
//---------------------------------------------------------------------------
#endif

