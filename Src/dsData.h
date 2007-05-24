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

class UpdateLocker;

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
    virtual void FASTCALL RecordAdded( const detail::Data::value_type& value, bool locked );
    virtual void FASTCALL RecordDeleted( const detail::Data::value_type& value );
    virtual void FASTCALL DataOpened( detail::Data& data );
    virtual void FASTCALL DataClosed();
    virtual void FASTCALL UpdateLockReleased();
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
    // noncopyable
    CDFASTCALL UpdateLocker( const UpdateLocker& src );
    UpdateLocker& FASTCALL operator=( const UpdateLocker& src );
public:
    CDFASTCALL UpdateLocker( Tablebase& tablebase ) : mTablebase(tablebase)     { tablebase.mData->LockUpdates(); }
    CDFASTCALL ~UpdateLocker()                                                  { mTablebase.mData->UnlockUpdates(); }
};
#else
class UpdateLocker
{
private:
    // noncopyable
    CDFASTCALL UpdateLocker( const UpdateLocker& src );
    UpdateLocker& FASTCALL operator=( const UpdateLocker& src );
public:
    CDFASTCALL UpdateLocker( Tablebase& )                                       {} // empty
};
#endif

//***********************************************************************
//******    Index
//***********************************************************************
class Index : public Tablebase
{
public:
    class iterator : public Tablebase::iterator
    {
    private:
        typedef Tablebase::iterator     inherited;
        friend class Index;
        spSortCompare       mCompare;
    protected:
        spSortCompare& GetCompare()                         { return mCompare; }
        CDFASTCALL iterator( detail::spData& container, const spSortCompare& cmp );
        CDFASTCALL iterator( detail::spData& container, detail::Data::size_type idx, const spSortCompare& cmp );
    public:
        CDFASTCALL iterator( const iterator& src );
        CDFASTCALL ~iterator();
        iterator& FASTCALL operator = ( const iterator& src );

        iterator& FASTCALL operator++()                 { inherited::operator++();      return *this; }
        iterator& FASTCALL operator--()                 { inherited::operator--();      return *this; }
        iterator& FASTCALL operator+=( int num )        { inherited::operator+=( num ); return *this; }
        iterator& FASTCALL operator-=( int num )        { inherited::operator-=( num ); return *this; }

        const iterator FASTCALL operator++( int );
        const iterator FASTCALL operator--( int );
        iterator FASTCALL operator+( int num );
        iterator FASTCALL operator-( int num );

        bool FASTCALL Find( const Variant& value );
        bool FASTCALL Find( const OpenValues& values );
    };

    class range_iterator : private iterator
    {
    private:
        typedef iterator            inherited;
        friend class Index;

        detail::Data::size_type     mStart;
        detail::Data::size_type     mEnd;
    protected:
        CDFASTCALL range_iterator( detail::spData& container, detail::Data::size_type start,
                                   detail::Data::size_type end, const spSortCompare& cmp );
        CDFASTCALL range_iterator( detail::spData& container, detail::Data::size_type start,
                                   detail::Data::size_type end, detail::Data::size_type idx,
                                   const spSortCompare& cmp );
    public:
        CDFASTCALL range_iterator( const range_iterator& src );
        CDFASTCALL ~range_iterator();
        range_iterator& FASTCALL operator = ( const range_iterator& src );

        range_iterator& FASTCALL operator++()               { inherited::operator++();      return *this; }
        range_iterator& FASTCALL operator--()               { inherited::operator--();      return *this; }
        range_iterator& FASTCALL operator+=( int num )      { inherited::operator+=( num ); return *this; }
        range_iterator& FASTCALL operator-=( int num )      { inherited::operator-=( num ); return *this; }

        const range_iterator FASTCALL operator++( int );
        const range_iterator FASTCALL operator--( int );
        range_iterator FASTCALL operator+( int num );
        range_iterator FASTCALL operator-( int num );

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
        void * FASTCALL GetMark()               { return reinterpret_cast<void *>(GetIndex()); }
        void FASTCALL GotoMark( void *mark )    { SetIndex( reinterpret_cast<detail::Data::size_type>(mark) ); }

        const OldValuesProxy FASTCALL OldValues()                           { return iterator::OldValues(); }
        detail::cFieldProxy FieldByName( const ds_string& field_name )      { return iterator::FieldByName( field_name ); }
        detail::cFieldProxy FieldByName( const char *field_name )           { return iterator::FieldByName( field_name ); }
        bool FASTCALL Find( const Variant& value );
        bool FASTCALL Find( const OpenValues& values );
    };

private:
    typedef detail::spData          container;
    friend class Table;            // needed only for constructor

    spSortCompare           mCompare;
    cFilterCompareBase_ptr  mFilter;
    void FASTCALL UpdateIndex( detail::Data& data );
#if defined(SM_DS_ENABLE_NOTIFY)
    // IDataNotify
    virtual void FASTCALL RecordAdded( const detail::Data::value_type& value, bool locked );
    virtual void FASTCALL RecordDeleted( const detail::Data::value_type& value );
    virtual void FASTCALL DataOpened( detail::Data& data );
    virtual void FASTCALL DataClosed();
    virtual void FASTCALL UpdateLockReleased();
#endif
    // noncopyable
    CDFASTCALL Index( const Index& src );
    Index& FASTCALL operator=( const Index& src );
protected:
    const spSortCompare& GetCompare() const                     { return mCompare; }
    CDFASTCALL Index( const spSortCompare& cmp_func, const detail::spData& data );
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

    void FASTCALL AddField( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned short size );
    void FASTCALL AddField( const char *name, cFieldKind kind, cFieldDataType data_type, unsigned short size );
    void FASTCALL Open( const Database& database, const char *where_clause );
    void FASTCALL Close();

    // sort only
    cIndex_ptr FASTCALL NewIndex( const cIndexField& index_field );
    cIndex_ptr FASTCALL NewIndex( const OpenIndexFields& index_fields );
    cIndex_ptr FASTCALL NewIndex( const spFieldSortCompare& cmp_func );
};

typedef shared_ptr<Table>       spTable;

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
        typedef Index::iterator                                 inherited;
        friend class cuIndex<RECORD>;
        typedef detail::cRawRecordProxy<typename RECORD::raw>   OldValuesProxy;
    protected:
        CDFASTCALL iterator( detail::spData& container, const spSortCompare& cmp )
            : inherited(container,cmp)                                                {} // empty
        CDFASTCALL iterator( detail::spData& container, detail::Data::size_type idx, const spSortCompare& cmp )
            : inherited(container, idx)                                           {} // empty
        CDFASTCALL iterator( const Index::iterator& iter )
            : inherited(iter)                                                     {} // empty
    public:
        RECORD FASTCALL operator->()                    { return ( RECORD( *GetDoubleBuffer() ) ); }

        iterator& FASTCALL operator++()                 { inherited::operator++();      return *this; }
        iterator& FASTCALL operator--()                 { inherited::operator--();      return *this; }
        iterator& FASTCALL operator+=( int num )        { inherited::operator+=( num ); return *this; }
        iterator& FASTCALL operator-=( int num )        { inherited::operator-=( num ); return *this; }

        const iterator FASTCALL operator++( int )
        {
            iterator    tmp( *this );

            ++(*this);
            return tmp;
        }
        const iterator FASTCALL operator--( int )
        {
            iterator    tmp( *this );

            --(*this);
            return tmp;
        }
        iterator FASTCALL operator+( int num )
        {
            iterator    tmp( *this );

            tmp += num;
            return tmp;
        }
        iterator FASTCALL operator-( int num )
        {
            iterator    tmp( *this );

            tmp -= num;
            return tmp;
        }

        const OldValuesProxy FASTCALL OldValues() const
        {
            return OldValuesProxy( GetDoubleBuffer()->GetOriginalData(), *GetData()->GetFieldDefs().get() );
        }
    };

    class range_iterator : public Index::range_iterator
    {
    private:
        typedef Index::range_iterator                           inherited;
        friend class cuIndex<RECORD>;
        typedef detail::cRawRecordProxy<typename RECORD::raw>   OldValuesProxy;
    protected:
        CDFASTCALL range_iterator( detail::spData& container, detail::Data::size_type start,
                                   detail::Data::size_type end, const spSortCompare& cmp );
        CDFASTCALL range_iterator( detail::spData& container, detail::Data::size_type start,
                                   detail::Data::size_type end, detail::Data::size_type idx,
                                   const spSortCompare& cmp );
        CDFASTCALL range_iterator( const Index::range_iterator& iter )
            : inherited(iter)                                               {} // empty
    public:
        CDFASTCALL ~range_iterator()                                        {} // empty

        range_iterator& FASTCALL operator++()           { inherited::operator++();      return *this; }
        range_iterator& FASTCALL operator--()           { inherited::operator--();      return *this; }
        range_iterator& FASTCALL operator+=( int num )  { inherited::operator+=( num ); return *this; }
        range_iterator& FASTCALL operator-=( int num )  { inherited::operator-=( num ); return *this; }

        const range_iterator FASTCALL operator++( int )
        {
            range_iterator    tmp( *this );

            ++(*this);
            return tmp;
        }
        const range_iterator FASTCALL operator--( int )
        {
            range_iterator    tmp( *this );

            --(*this);
            return tmp;
        }
        range_iterator FASTCALL operator+( int num )
        {
            range_iterator    tmp( *this );

            tmp += num;
            return tmp;
        }
        range_iterator FASTCALL operator-( int num )
        {
            range_iterator    tmp( *this );

            tmp -= num;
            return tmp;
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
    CDFASTCALL cuIndex( const spSortCompare& cmp_func, const detail::spData& data )
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
    class iterator : public Table::iterator
    {
    private:
        typedef Table::iterator                                 inherited;
        typedef detail::cRawRecordProxy<typename RECORD::raw>   OldValuesProxy;

        friend class cuTable<RECORD>;
    protected:
        CDFASTCALL iterator( detail::spData& container )
            : inherited(container)                                                {} // empty
        CDFASTCALL iterator( detail::spData& container, detail::Data::size_type idx )
            : inherited(container, idx)                                           {} // empty
        //CDFASTCALL iterator( const inherited& iter )
        //    : inherited(iter)                                                     {} // empty
    public:
        RECORD FASTCALL operator->()                    { return ( RECORD( *GetDoubleBuffer() ) ); }

        iterator& FASTCALL operator++()                 { inherited::operator++();      return *this; }
        iterator& FASTCALL operator--()                 { inherited::operator--();      return *this; }
        iterator& FASTCALL operator+=( int num )        { inherited::operator+=( num ); return *this; }
        iterator& FASTCALL operator-=( int num )        { inherited::operator-=( num ); return *this; }

        const iterator FASTCALL operator++( int )
        {
            iterator    tmp( *this );

            ++(*this);
            return tmp;
        }
        const iterator FASTCALL operator--( int )
        {
            iterator    tmp( *this );

            --(*this);
            return tmp;
        }
        iterator FASTCALL operator+( int num )
        {
            iterator    tmp( *this );

            tmp += num;
            return tmp;
        }
        iterator FASTCALL operator-( int num )
        {
            iterator    tmp( *this );

            tmp -= num;
            return tmp;
        }

        const OldValuesProxy FASTCALL OldValues() const
        {
            return OldValuesProxy( GetDoubleBuffer()->GetOriginalData(), *GetData()->GetFieldDefs().get() );
        }
    };
private:
    typedef RECORD                      record_type;

    class cIndexSortCompare : public detail::SortCompare
    {
    private:
        virtual bool FASTCALL compare( detail::cRawBuffer *item1, detail::cRawBuffer *item2 )
        {
#ifdef __BORLANDC__
            return typed_compare( RECORD::raw( *item1 ), RECORD::raw( *item2 ) );
#else
            return typed_compare( typename RECORD::raw( *item1 ), typename RECORD::raw( *item2 ) );
#endif
        }
    protected:
        virtual bool FASTCALL typed_compare( const typename RECORD::raw& item1, const typename RECORD::raw& item2 ) = 0;
    };

    class cFilterCompare : public detail::cFilterCompareBase
    {
    private:
        virtual bool FASTCALL compare( detail::cRawBuffer *item1 )
        {
            return typed_compare( typename RECORD::raw( *item1 ) );
        }
    protected:
        virtual bool FASTCALL typed_compare( const typename RECORD::raw& item1 ) = 0;
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

    index_ptr FASTCALL NewIndex( const spSortCompare& cmp_func )
    {
        return index_ptr( new index( cmp_func, GetData() ) );
    }

    index_ptr FASTCALL NewIndex( const spFieldSortCompare& cmp_func )
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
    iterator FASTCALL AddRecord( const record& rec )                            { return iterator( GetData(), AddBuffer( rec ) ); }
    iterator FASTCALL Locate( const Variant& value, const cFindField& field )
    {
        return iterator( Table::Locate( value, field ) );
    }
    iterator FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields )
    {
        return iterator( GetData(), Table::LocateImpl( values, fields ) );
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

