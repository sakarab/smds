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
//******    cTablebase
//***********************************************************************
class cTablebase
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
{
public:
    typedef cRecordIterator             iterator;
    // typedef detail::cRangeIterator      range_iterator;
private:
    friend class cTableWriter;

    detail::cData_ptr       mData;
    // noncopyable
    CDFASTCALL cTablebase( const cTablebase& src );
    cTablebase& FASTCALL operator=( const cTablebase& src );
protected:
    detail::cData_ptr& FASTCALL GetData()                                               { return ( mData ); }
    void FASTCALL SetData( const detail::cData_ptr& data )                              { mData = data; }
    detail::cDoubleBuffer * FASTCALL GetDoubleBuffer( const cRecord& record )           { return ( record.GetDoubleBuffer() ); }
    int FASTCALL AddBuffer_ptr( const cRecord& record )                         { return ( mData->AddBuffer_ptr( record.mRecord ) ); }

    void FASTCALL ConstructIndex( cSortCompareBase_ptr& cmp_func, const detail::cData_ptr& data );
    CDFASTCALL cTablebase();
    CDFASTCALL cTablebase( const detail::cFieldDefs_& field_defs );
public:
    virtual CDFASTCALL ~cTablebase();
    const cFieldDefs_ptr& FASTCALL GetFieldDefs() const                         { return ( mData->GetFieldDefs() ); }
    int FASTCALL RecordCount()                                                  { return ( mData->size() ); }
    cRecordIterator FASTCALL GetIterator()                                      { return ( cRecordIterator( mData ) ); }

    void FASTCALL Clear()                                                       { mData->Clear(); }
    void FASTCALL CommitUpdates()                                               { mData->CommitUpdates(); }
    cRecord FASTCALL NewRecord();
    iterator FASTCALL AddRecord( const cRecord& record );
    iterator FASTCALL Locate( const Variant& value, const cFindField& field );
    iterator FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields );
    bool FASTCALL Locate( const Variant& value, const cFindField& field, iterator& iter );
    bool FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields, iterator& iter );
};

//***********************************************************************
//******    cIndex
//***********************************************************************
class cIndex : public cTablebase
{
public:
    class iterator : public cTablebase::iterator
    {
    private:
        friend class cIndex;
    protected:
        CDFASTCALL iterator( detail::cData_ptr& container )
            : cTablebase::iterator( container )                                            {} // empty
        CDFASTCALL iterator( detail::cData_ptr& container, detail::cData::size_type idx )
            : cTablebase::iterator( container, idx )                                       {} // empty
    public:
        CDFASTCALL iterator( const cTablebase::iterator& src )
            : cTablebase::iterator(src)                                                    {} // empty
        CDFASTCALL iterator( const iterator& src ) : cTablebase::iterator(src)             {} // empty
        CDFASTCALL ~iterator()                                                  {} // empty
        iterator& FASTCALL operator = ( const iterator& src )
        {
            cTablebase::iterator::operator=( src );
            return *this;
        }
        iterator& FASTCALL operator++()
        {
            cTablebase::iterator::operator++();
            return ( *this );
        }
        iterator& FASTCALL operator--()
        {
            cTablebase::iterator::operator--();
            return ( *this );
        }
    };
private:
    typedef detail::cData_ptr       container;
    friend class cTable;            // next to eliminate

    cSortCompareBase_ptr    mCompare;
    cFilterCompareBase_ptr  mFilter;
    // noncopyable
    CDFASTCALL cIndex( const cIndex& src );
    cIndex& FASTCALL operator=( const cIndex& src );
protected:
    void FASTCALL Construct( const cSortCompareBase_ptr& cmp_func, const detail::cData_ptr& data );
    CDFASTCALL cIndex();
public:
    virtual CDFASTCALL ~cIndex();
    iterator FASTCALL Find( const Variant& value );
    iterator FASTCALL Find( const OpenValues& values );
    bool FASTCALL Find( const Variant& value, iterator& iter );
    bool FASTCALL Find( const OpenValues& values, iterator& iter );
    // bool FASTCALL Find( const Variant& value, range_iterator& iter );
    // bool FASTCALL Find( const OpenValues& values, range_iterator& iter );
    iterator FASTCALL GetIterator()                                         { return cTablebase::GetIterator(); }
    cIndex FASTCALL GetRange( const cRangeValues& values );
    cIndex FASTCALL GetRange( const OpenRangeValues& values );
};

typedef shared_ptr<cIndex>      cIndex_ptr;

//***********************************************************************
//******    cTable
//***********************************************************************
typedef shared_ptr<detail::cIndexSortCompareStd>        cIndexSortCompareStd_ptr;

class cTable : public cTablebase
{
public:
    class iterator : public cTablebase::iterator
    {
    private:
        friend class cTable;
    protected:
        CDFASTCALL iterator( detail::cData_ptr& container )
            : cTablebase::iterator( container )                                            {} // empty
        CDFASTCALL iterator( detail::cData_ptr& container, detail::cData::size_type idx )
            : cTablebase::iterator( container, idx )                                       {} // empty
        CDFASTCALL iterator( const cTablebase::iterator& src )
            : cTablebase::iterator(src)                                                    {} // empty
    public:
        CDFASTCALL iterator( const iterator& src ) : cTablebase::iterator(src)             {} // empty
        CDFASTCALL ~iterator()                                                  {} // empty
        iterator& FASTCALL operator = ( const iterator& src )
        {
            cTablebase::iterator::operator=( src );
            return *this;
        }
        iterator& FASTCALL operator++()
        {
            cTablebase::iterator::operator++();
            return ( *this );
        }
        iterator& FASTCALL operator--()
        {
            cTablebase::iterator::operator--();
            return ( *this );
        }
    };
private:
    ds_string               mSql;
    ds_string               mTableName;
    // methods
    ds_string FASTCALL ConstructSelectFromFields( const char *where_clause );
    ds_string FASTCALL ConstructSelectFromSql( const char *where_clause );
    ds_string FASTCALL ConstructSelect( const char *where_clause );
    detail::cData::value_type FASTCALL NewBuffer_usUnmodified();
    // noncopyable
    CDFASTCALL cTable( const cTable& src );
    cTable& FASTCALL operator=( const cTable& src );
protected:
    detail::cData::value_type FASTCALL NewBuffer_usInserted();

    cIndex * FASTCALL ConstructIndex( cIndex *index, const cSortCompareBase_ptr& cmp_func );
    cIndex * FASTCALL ConstructIndex( cIndex *index, const cIndexField& index_field );
    cIndex * FASTCALL ConstructIndex( cIndex *index, const OpenIndexFields& index_fields );

    CDFASTCALL cTable( const detail::cFieldDefs_& field_defs );
public:
    CDFASTCALL cTable();
    CDFASTCALL cTable( const ds_string& table_name );
    CDFASTCALL cTable( const char * table_name );
    virtual CDFASTCALL ~cTable();

    const ds_string& GetTableName()                     { return ( mTableName ); }
    iterator FASTCALL GetIterator()                     { return cTablebase::GetIterator(); }

    iterator FASTCALL Locate( const Variant& value, const cFindField& field )
    {
        return iterator ( cTablebase::Locate( value, field ) );
    }
    iterator FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields )
    {
        return iterator ( cTablebase::Locate( values, fields ) );
    }

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
//******    cuIndex<>
//***********************************************************************
template <class RECORD> class cuIndex : public cIndex
{
public:
/*
    class iterator : public cuRecordIterator<RECORD, cIndex::iterator>
    {
    private:
        typedef cIndex::iterator    BASE;
    protected:
	    CDFASTCALL iterator( detail::cData_ptr& container )
            : BASE(container)                                                {} // empty
        CDFASTCALL iterator( detail::cData_ptr& container, detail::cData::size_type idx )
            : BASE(container, idx)                                           {} // empty
        CDFASTCALL iterator( const BASE& iter )
            : BASE(iter)                                                     {} // empty
    public:
        RECORD FASTCALL operator->()                    { return ( RECORD( *GetDoubleBuffer() ) ); }
        iterator& FASTCALL operator++()
        {
            BASE::operator++();
            return ( *this );
        }
        iterator& FASTCALL operator--()
        {
            BASE::operator--();
            return ( *this );
        }
    };
    // typedef detail::cuRangeIterator<RECORD>     range_iterator;
*/
    template <class RECORD> class cuRecordIterator : public cIndex::iterator
    {
    private:
        typedef detail::cRawRecordProxy<typename RECORD::raw>      OldValuesProxy;

        template <class RECORD_> friend class cuIndex;

        CDFASTCALL cuRecordIterator( detail::cData_ptr& container )
            : cIndex::iterator(container)                                                {} // empty
        CDFASTCALL cuRecordIterator( detail::cData_ptr& container, detail::cData::size_type idx )
            : cIndex::iterator(container, idx)                                           {} // empty
        CDFASTCALL cuRecordIterator( const cIndex::iterator& iter )
            : cIndex::iterator(iter)                                                     {} // empty
    public:
        const OldValuesProxy FASTCALL OldValues() const
        {
            return ( OldValuesProxy( GetDoubleBuffer()->GetOriginalData(), *GetData()->GetFieldDefs().get() ) );
        }

        RECORD FASTCALL operator->()                    { return ( RECORD( *GetDoubleBuffer() ) ); }
        iterator& FASTCALL operator++()
        {
            cIndex::iterator::operator++();
            return ( *this );
        }
        iterator& FASTCALL operator--()
        {
            cIndex::iterator::operator--();
            return ( *this );
        }
    };
    typedef cuRecordIterator<RECORD>    iterator;
private:
    template <class RECORD_> friend class cuTable;
    // noncopyable
    CDFASTCALL cuIndex( const cuIndex& src );
    cuIndex& FASTCALL operator=( const cuIndex& src );
protected:
    CDFASTCALL cuIndex() : cIndex()                                         {} // empty
public:
    virtual CDFASTCALL ~cuIndex()                                           {} // empty
    iterator FASTCALL GetIterator()                                         { return iterator( cIndex::GetIterator() ); }
    iterator FASTCALL Locate( const Variant& value, const cFindField& field )
    {
        return ( iterator( cIndex::Locate( value, field ) ) );
    }
    iterator FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields )
    {
        return ( iterator( cIndex::Locate( values, fields ) ) );
    }
    iterator FASTCALL Find( const Variant& value )                              { return ( iterator( cIndex::Find( value ) ) ); }
    iterator FASTCALL Find( const OpenValues& values )                          { return ( iterator( cIndex::Find( values ) ) ); }
    bool FASTCALL Find( const Variant& value, iterator& iter )                  { return ( cIndex::Find( value, iter ) ); }
    bool FASTCALL Find( const OpenValues& values, iterator& iter )              { return ( cIndex::Find( values, iter ) ); }
};

//***********************************************************************
//******    cuTable<>
//***********************************************************************
template <class RECORD> class cuTable : public cTable
{
public:
    template <class REC> class cuRecordIterator : public cTable::iterator
    {
    private:
        typedef detail::cRawRecordProxy<typename RECORD::raw>      OldValuesProxy;

        template <class RECORD> friend class cuTable;

        CDFASTCALL cuRecordIterator( detail::cData_ptr& container )
            : cTable::iterator(container)                                                {} // empty
        CDFASTCALL cuRecordIterator( detail::cData_ptr& container, detail::cData::size_type idx )
            : cTable::iterator(container, idx)                                           {} // empty
        CDFASTCALL cuRecordIterator( const cTable::iterator& iter )
            : cTable::iterator(iter)                                                     {} // empty
    public:
        const OldValuesProxy FASTCALL OldValues() const
        {
            return ( OldValuesProxy( GetDoubleBuffer()->GetOriginalData(), *GetData()->GetFieldDefs().get() ) );
        }

        REC FASTCALL operator->()                    { return ( REC( *GetDoubleBuffer() ) ); }
        iterator& FASTCALL operator++()
        {
            cTable::iterator::operator++();
            return ( *this );
        }
        iterator& FASTCALL operator--()
        {
            cTable::iterator::operator--();
            return ( *this );
        }
    };
    typedef cuRecordIterator<RECORD>    iterator;
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
    using cTable::Locate;
#endif
    typedef cuRecord<RECORD>                    record;
    typedef cuIndex<RECORD>                     index;
    typedef shared_ptr< cuIndex<RECORD> >       index_ptr;
    typedef cIndexSortCompare<RECORD>           sort_compare;
    typedef cFilterCompare<RECORD>              filter_compare;
    typedef typename RECORD::raw                raw;
private:
    index * FASTCALL ConstructIndex( index *index, const cSortCompareBase_ptr& cmp_func )
    {
        cTable::ConstructIndex( index, cmp_func );
        return ( index );
    }
    index * FASTCALL ConstructIndex( index *index, const cIndexField& index_field )
    {
        cTable::ConstructIndex( index, index_field );
        return ( index );
    }
    index * FASTCALL ConstructIndex( index *index, const OpenIndexFields& index_fields )
    {
        cTable::ConstructIndex( index, index_fields );
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

    iterator FASTCALL GetIterator()                                             { return cTable::GetIterator(); }
    record FASTCALL NewRecord()                                                 { return record( NewBuffer_usInserted(), GetFieldDefs() ); }
    iterator FASTCALL AddRecord( const record& rec )                            { return iterator( GetData(), AddBuffer_ptr( rec ) ); }
    iterator FASTCALL Locate( const Variant& value, const cFindField& field )
    {
        return ( iterator( cTable::Locate( value, field ) ) );
    }
    iterator FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields )
    {
        return ( iterator( cTable::Locate( values, fields ) ) );
    }
#ifdef __BORLANDC__
    bool FASTCALL Locate( const Variant& value, const cFindField& field, iterator& iter )
    {
        return ( cTable::Locate( value, field, iter ) );
    }
    bool FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields, iterator& iter )
    {
        return ( cTable::Locate( values, fields, iter ) );
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
    static void FASTCALL ReadFieldValue( cStream& st, const detail::cRawBuffer& rb, const cFieldDef& field );
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
    static void FASTCALL ReadFieldValue( cStream& st, detail::cRawBuffer& rb, const cFieldDef& field );
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

}; // namespace smds
//---------------------------------------------------------------------------
#endif

