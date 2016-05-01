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
#ifndef __GNUG__
#pragma hdrstop
#endif

#include "dsIndex.h"
#include "dsExceptions.h"
#include "dsCompareControlers.h"
#include <set>
//---------------------------------------------------------------------------
namespace smds
{

//***********************************************************************
//******    Index::iterator
//***********************************************************************
CDFASTCALL Index::iterator::iterator( detail::spData& container, const spSortCompare& cmp )
    : inherited(container), mCompare(cmp)
{
}

CDFASTCALL Index::iterator::iterator( detail::spData& container, detail::Data::size_type idx, const spSortCompare& cmp )
    : inherited(container,idx), mCompare(cmp)
{
}

CDFASTCALL Index::iterator::iterator( const Index::iterator& src )
    : inherited(src), mCompare(src.mCompare)
{
}

CDFASTCALL Index::iterator::~iterator()
{
}

Index::iterator& FASTCALL Index::iterator::operator = ( const Index::iterator& src )
{
    if ( &src != this )
    {
        inherited::operator= ( src );
        mCompare = src.mCompare;
    }
    return *this;
}

const Index::iterator FASTCALL Index::iterator::operator++( int )
{
    iterator    tmp( *this );

    ++(*this);
    return tmp;
}

const Index::iterator FASTCALL Index::iterator::operator--( int )
{
    iterator    tmp( *this );

    --(*this);
    return tmp;
}

Index::iterator FASTCALL Index::iterator::operator+( int num )
{
    iterator    tmp( *this );

    tmp += num;
    return tmp;
}

Index::iterator FASTCALL Index::iterator::operator-( int num )
{
    iterator    tmp( *this );

    tmp -= num;
    return tmp;
}

bool FASTCALL Index::iterator::Find( const Variant& value )
{
    return Find( OpenValues( value ) );
}

bool FASTCALL Index::iterator::Find( const OpenValues& values )
{
    detail::Data::locate_result     result;

    GetData()->Find( values, mCompare, result );
    if ( result.first )
        SetIndex( result.second );
    return result.first;
}

//***********************************************************************
//******    Index::range_iterator
//***********************************************************************
CDFASTCALL Index::range_iterator::range_iterator( detail::spData& container, detail::Data::size_type start,
                                                  detail::Data::size_type end, const spSortCompare& cmp )
    : Index::iterator( container, cmp ), mStart(start), mEnd(end)
{
}

CDFASTCALL Index::range_iterator::range_iterator( detail::spData& container, detail::Data::size_type start,
                                                  detail::Data::size_type end, detail::Data::size_type idx,
                                                  const spSortCompare& cmp )
    : Index::iterator( container, idx, cmp ), mStart(start), mEnd(end)
{
}

CDFASTCALL Index::range_iterator::range_iterator( const range_iterator& src )
    : Index::iterator( src ), mStart(src.mStart), mEnd(src.mEnd)
{
}

CDFASTCALL Index::range_iterator::~range_iterator()
{
}

Index::range_iterator& FASTCALL Index::range_iterator::operator = ( const range_iterator& src )
{
    if ( &src != this )
    {
        Index::iterator::operator= ( src );
        mStart = src.mStart;
        mEnd = src.mEnd;
    }
    return *this;
}

const Index::range_iterator FASTCALL Index::range_iterator::operator++( int )
{
    range_iterator      tmp( *this );

    ++(*this);
    return tmp;
}

const Index::range_iterator FASTCALL Index::range_iterator::operator--( int )
{
    range_iterator      tmp( *this );

    --(*this);
    return tmp;
}

Index::range_iterator FASTCALL Index::range_iterator::operator+( int num )
{
    range_iterator      tmp( *this );

    tmp += num;
    return tmp;
}

Index::range_iterator FASTCALL Index::range_iterator::operator-( int num )
{
    range_iterator      tmp( *this );

    tmp -= num;
    return tmp;
}

bool FASTCALL Index::range_iterator::Find( const Variant& value )
{
    return Find( OpenValues( value ) );
}

bool FASTCALL Index::range_iterator::Find( const OpenValues& values )
{
    detail::Data::locate_result     result;

    GetData()->Find( values, GetCompare(), mStart, mEnd, result );
    if ( result.first )
        SetIndex( result.second );
    return result.first;
}

//***********************************************************************
//******    Index
//***********************************************************************
CDFASTCALL Index::Index( const detail::spData& data, const spSortCompare& cmp_func )
    : Tablebase(), mCompare(cmp_func)
{
    UpdateIndex( *data );
}

CDFASTCALL Index::~Index()
{
}

void FASTCALL Index::UpdateIndex( detail::Data& data )
{
#if defined(SM_DS_ENABLE_NOTIFY)
    SetData( data.Clone_All( this ) );
#else
    SetData( data.Clone_All() );
#endif
    mCompare->Initialize( GetData()->GetFieldDefs() );
    GetData()->Sort( detail::SortControler( mCompare ) );
}

Index::iterator FASTCALL Index::Find( const OpenValues& values )
{
    detail::Data::locate_result     result;

    GetData()->Find( values, mCompare, result );
    return iterator( GetData(), result.second, mCompare );
}

Index::iterator FASTCALL Index::Find( const Variant& value )
{
    return( Find( OpenValues( value ) ) );
}

Index::range_iterator FASTCALL Index::GetRangeIterator( const cRangeValues& values )
{
    return GetRangeIterator( OpenRangeValues( values ) );
}

Index::range_iterator FASTCALL Index::GetRangeIterator( const OpenRangeValues& values )
{
    detail::Data::range_result      result;

    GetData()->GetRange( values, mCompare, result );
    return range_iterator( GetData(), result.second.first, result.second.second, mCompare );
}

#if defined(SM_DS_ENABLE_NOTIFY)
void Index::RecordAdded( const detail::Data::value_type& value, bool locked )
{
    if ( locked )
        GetData()->AddBuffer_ptr( value );
    else
        GetData()->InsertBuffer_ptr( value, mCompare );
}

void Index::RecordDeleted( const detail::Data::value_type& value )
{
    GetData()->DeleteBuffer_ptr( value );
}

void Index::DataOpened( detail::Data& data )
{
    UpdateIndex( data );
}

void Index::DataClosed()
{
    SetData( detail::spData() );
}

void Index::UpdateLockReleased()
{
    GetData()->Sort( detail::SortControler( mCompare ) );
}
#endif

}; // namespace smds
//---------------------------------------------------------------------------

