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
#ifndef SM_DS_INDEX_H
#define SM_DS_INDEX_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include <vector>
#include "dsTypes.h"
#include "dsUtils.h"
#include "dsData.h"
#include "dsFields.h"
//---------------------------------------------------------------------------

namespace smds
{

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

}; // namespace smds
//---------------------------------------------------------------------------
#endif
