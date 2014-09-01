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
#ifndef SM_DS_TYPEDDATA_H
#define SM_DS_TYPEDDATA_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include "dsIndex.h"
//---------------------------------------------------------------------------

namespace smds
{

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
        typedef detail::cOldValuesProxy<typename RECORD::raw>   OldValuesProxy;

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
        return index_ptr( new index( GetData(), cmp_func ) );
    }

    index_ptr FASTCALL NewIndex( const spFieldSortCompare& cmp_func )
    {
        return index_ptr( new index( GetData(), cmp_func ) );
    }

    index_ptr FASTCALL NewIndex( const cIndexField& index_field )
    {
        return index_ptr( new index( GetData(), CreateCmp( index_field ) ) );
    }

    index_ptr FASTCALL NewIndex( const OpenIndexFields& index_fields )
    {
        return index_ptr( new index( GetData(), CreateCmp( index_fields ) ) );
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
        typedef detail::cOldValuesProxy<typename RECORD::raw>   OldValuesProxy;
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
        typedef detail::cOldValuesProxy<typename RECORD::raw>   OldValuesProxy;
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
    CDFASTCALL cuIndex( const detail::spData& data, const spSortCompare& cmp_func )
        : Index( data, cmp_func )
    {
    }
public:
    virtual CDFASTCALL ~cuIndex()                                           {} // empty

/*
    shared_ptr< cuTable<RECORD> > FASTCALL AsTable()
    {
        return shared_ptr< cuTable<RECORD> >( new cuTable<RECORD>( GetData() ) );
    }

    operator shared_ptr< cuTable<RECORD> >()
    {
        return shared_ptr< cuTable<RECORD> >( new cuTable<RECORD>( GetData() ) );
    }
*/

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
