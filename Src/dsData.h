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
//******    Index
//***********************************************************************
class Index : public Tablebase
{
public:
    class iterator : public Tablebase::iterator
    {
    private:
        friend class Index;
        cSortCompareBase_ptr    mCompare;
    protected:
        cSortCompareBase_ptr& GetCompare()                      { return mCompare; }
        CDFASTCALL iterator( detail::cData_ptr& container, const cSortCompareBase_ptr& cmp );
        CDFASTCALL iterator( detail::cData_ptr& container, detail::cData::size_type idx, const cSortCompareBase_ptr& cmp );
    public:
        CDFASTCALL iterator( const iterator& src );
        CDFASTCALL ~iterator();
        iterator& FASTCALL operator = ( const iterator& src );
        bool FASTCALL Find( const Variant& value );
        bool FASTCALL Find( const OpenValues& values );
    };

    class range_iterator : private iterator
    {
    private:
        friend class Index;

        detail::cData::size_type    mStart;
        detail::cData::size_type    mEnd;
    protected:
        CDFASTCALL range_iterator( detail::cData_ptr& container, detail::cData::size_type start,
                                   detail::cData::size_type end, const cSortCompareBase_ptr& cmp );
        CDFASTCALL range_iterator( detail::cData_ptr& container, detail::cData::size_type start,
                                   detail::cData::size_type end, detail::cData::size_type idx,
                                   const cSortCompareBase_ptr& cmp );
    public:
        CDFASTCALL range_iterator( const range_iterator& src );
        CDFASTCALL ~range_iterator();
        range_iterator& FASTCALL operator = ( const range_iterator& src );
        range_iterator& FASTCALL operator++()
        {
            iterator::operator++();
            return *this;
        }
        range_iterator& FASTCALL operator--()
        {
            iterator::operator--();
            return *this;
        }
        void FASTCALL Next()
        {
            if ( ! eof() )
                ++(*this);
        }
        void FASTCALL Prev()
        {
            if ( GetIndex() > mStart )
                --(*this);
        }
        bool FASTCALL eof()                     { return ( GetIndex() >= mEnd ); }
        bool FASTCALL bof()                     { return ( GetIndex() == mStart ); }
        void FASTCALL First()                   { SetIndex( mStart ); }
        void FASTCALL Last()                    { SetIndex( mEnd - 1 ); }
        int FASTCALL RecordCount()              { return ( mEnd - mStart ); }
        void * FASTCALL GetMark()               { return ( reinterpret_cast<void *>(GetIndex()) ); }
        void FASTCALL GotoMark( void *mark )    { SetIndex( reinterpret_cast<detail::cData::size_type>(mark) ); }

        const OldValuesProxy FASTCALL OldValues()                           { return iterator::OldValues(); }
        detail::cFieldProxy FieldByName( const ds_string& field_name )      { return iterator::FieldByName( field_name ); }
        detail::cFieldProxy FieldByName( const char *field_name )           { return iterator::FieldByName( field_name ); }
        bool FASTCALL Find( const Variant& value );
        bool FASTCALL Find( const OpenValues& values );
    };

private:
    typedef detail::cData_ptr       container;
    friend class Table;            // needed only for constructor

    cSortCompareBase_ptr    mCompare;
    cFilterCompareBase_ptr  mFilter;
    // noncopyable
    CDFASTCALL Index( const Index& src );
    Index& FASTCALL operator=( const Index& src );
protected:
    const cSortCompareBase_ptr& GetCompare() const                  { return mCompare; }
    CDFASTCALL Index( const cSortCompareBase_ptr& cmp_func, const detail::cData_ptr& data );
public:
    virtual CDFASTCALL ~Index();
    iterator FASTCALL Find( const Variant& value );
    iterator FASTCALL Find( const OpenValues& values );
    iterator FASTCALL GetIterator()                                         { return iterator( GetData(), mCompare ); }
    range_iterator FASTCALL GetRangeIterator( const cRangeValues& values );
    range_iterator FASTCALL GetRangeIterator( const OpenRangeValues& values );
    // Range FASTCALL GetRange( const cRangeValues& values );
    // Range FASTCALL GetRange( const OpenRangeValues& values );
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
    void FASTCALL Open( const Database& database, const char *where_clause );
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
private:
    friend class cuTable<RECORD>;
public:
    class iterator : public Index::iterator
    {
    private:
        friend class cuIndex<RECORD>;
        typedef detail::cRawRecordProxy<typename RECORD::raw>   OldValuesProxy;
    protected:
        CDFASTCALL iterator( detail::cData_ptr& container, const cSortCompareBase_ptr& cmp )
            : Index::iterator(container,cmp)                                                {} // empty
        CDFASTCALL iterator( detail::cData_ptr& container, detail::cData::size_type idx, const cSortCompareBase_ptr& cmp )
            : Index::iterator(container, idx)                                           {} // empty
        CDFASTCALL iterator( const Index::iterator& iter )
            : Index::iterator(iter)                                                     {} // empty
    public:
        RECORD FASTCALL operator->()                    { return ( RECORD( *GetDoubleBuffer() ) ); }
        iterator& FASTCALL operator++()
        {
            Index::iterator::operator++();
            return *this;
        }
        iterator& FASTCALL operator--()
        {
            Index::iterator::operator--();
            return *this;
        }

        const OldValuesProxy FASTCALL OldValues() const
        {
            return OldValuesProxy( GetDoubleBuffer()->GetOriginalData(), *GetData()->GetFieldDefs().get() );
        }
    };

    class range_iterator : public Index::range_iterator
    {
    private:
        friend class cuIndex<RECORD>;
        typedef detail::cRawRecordProxy<typename RECORD::raw>   OldValuesProxy;
    protected:
        CDFASTCALL range_iterator( detail::cData_ptr& container, detail::cData::size_type start,
                                   detail::cData::size_type end, const cSortCompareBase_ptr& cmp );
        CDFASTCALL range_iterator( detail::cData_ptr& container, detail::cData::size_type start,
                                   detail::cData::size_type end, detail::cData::size_type idx,
                                   const cSortCompareBase_ptr& cmp );
        CDFASTCALL range_iterator( const Index::range_iterator& iter )
            : Index::range_iterator(iter)                                       {} // empty
    public:
        CDFASTCALL ~range_iterator()                                            {} // empty
        range_iterator& FASTCALL operator++()
        {
            Index::range_iterator::operator++();
            return *this;
        }
        range_iterator& FASTCALL operator--()
        {
            Index::range_iterator::operator--();
            return ( *this );
        }

        const OldValuesProxy FASTCALL OldValues() const
        {
            return OldValuesProxy( GetDoubleBuffer()->GetOriginalData(), *GetData()->GetFieldDefs().get() );
        }
    };
private:
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
    iterator FASTCALL GetIterator()                                         { return iterator( GetData(), GetCompare() ); }
    iterator FASTCALL Locate( const Variant& value, const cFindField& field )
    {
        return ( iterator( Index::Locate( value, field ) ) );
    }
    iterator FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields )
    {
        return ( iterator( Index::Locate( values, fields ) ) );
    }
    iterator FASTCALL Find( const Variant& value )                              { return iterator( Index::Find( value ) ); }
    iterator FASTCALL Find( const OpenValues& values )                          { return iterator( Index::Find( values ) ); }
    range_iterator FASTCALL GetRangeIterator( const cRangeValues& values )      { return range_iterator( Index::GetRangeIterator( values ) ); }
    range_iterator FASTCALL GetRangeIterator( const OpenRangeValues& values )   { return range_iterator( Index::GetRangeIterator( values ) ); }
};

//***********************************************************************
//******    cuTable<>
//***********************************************************************
template <class RECORD> class cuTable : public Table
{
public:
    class iterator : public Tablebase::iterator
    {
    private:
        typedef detail::cRawRecordProxy<typename RECORD::raw>   OldValuesProxy;

        friend class cuTable<RECORD>;
    protected:
        CDFASTCALL iterator( detail::cData_ptr& container )
            : Tablebase::iterator(container)                                                {} // empty
        CDFASTCALL iterator( detail::cData_ptr& container, detail::cData::size_type idx )
            : Tablebase::iterator(container, idx)                                           {} // empty
        CDFASTCALL iterator( const Tablebase::iterator& iter )
            : Tablebase::iterator(iter)                                                     {} // empty
    public:
        RECORD FASTCALL operator->()                    { return ( RECORD( *GetDoubleBuffer() ) ); }
        iterator& FASTCALL operator++()
        {
            Tablebase::iterator::operator++();
            return *this;
        }
        iterator& FASTCALL operator--()
        {
            Tablebase::iterator::operator--();
            return *this;
        }

        const OldValuesProxy FASTCALL OldValues() const
        {
            return OldValuesProxy( GetDoubleBuffer()->GetOriginalData(), *GetData()->GetFieldDefs().get() );
        }
    };
private:
    typedef RECORD                      record_type;

    class cIndexSortCompare : public detail::cSortCompareBase
    {
    private:
        virtual bool FASTCALL do_compare_1( detail::cRawBuffer *item1, detail::cRawBuffer *item2 )
        {
#ifdef __BORLANDC__
            return ( do_compare_2( RECORD::raw( *item1 ), RECORD::raw( *item2 ) ) );
#else
            return ( do_compare_2( typename RECORD::raw( *item1 ), typename RECORD::raw( *item2 ) ) );
#endif
        }
    protected:
        virtual bool FASTCALL do_compare_2( const typename RECORD::raw& item1, const typename RECORD::raw& item2 ) = 0;
    };

    class cFilterCompare : public detail::cFilterCompareBase
    {
    private:
        virtual bool FASTCALL do_compare_1( detail::cRawBuffer *item1 )
        {
            return ( do_compare_2( typename RECORD::raw( *item1 ) ) );
        }
    protected:
        virtual bool FASTCALL do_compare_2( const typename RECORD::raw& item1 ) = 0;
    };
public:
#ifndef __BORLANDC__
    using Table::Locate;
#endif
    typedef cuRecord<RECORD>                    record;
    typedef cuIndex<RECORD>                     index;
    typedef shared_ptr< cuIndex<RECORD> >       index_ptr;
    typedef cIndexSortCompare                   sort_compare;
    typedef cFilterCompare                      filter_compare;
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

    iterator FASTCALL GetIterator()                                             { return iterator( GetData() ); }
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

