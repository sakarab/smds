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
#ifndef __GNUG__
#pragma hdrstop
#endif

#include "dsFields.h"
#include "dsExceptions.h"
#include "dsSmartPtr.h"
#include "dsDateTime.h"
#include "dsGUID.h"
#include "dsVariant.h"
#include <boost/type_traits.hpp>
#include "dsString.h"

namespace smds
{

namespace
{

struct TypeSizeMap
{
    cFieldDataType  DataType;
    unsigned short  RawSize;
};

// cFieldDataType_sync
// sorted by TypeSizeMap.DataType
static const TypeSizeMap TypeSizeMaps[] =
{
    { ftBool, sizeof(bool) },
    { ftByte, sizeof(char) },
    { ftShort, sizeof(short) },
    { ftInteger, sizeof(int) },
    { ftLongLong, sizeof(long long) },
    { ftDouble, sizeof(double) },
    { ftDate, sizeof(detail::dbDate_Internal) },
    { ftTime, sizeof(detail::dbTime_Internal) },
    { ftDateTime, sizeof(detail::dbDateTime_Internal) },
    { ftGUID, sizeof(detail::dbGUID_Internal) },
    { ftString, sizeof(ds_string *) },
    { ftWString, sizeof(ds_wstring *) },
    { ftBlob, sizeof(var_blob_type *) }
};

unsigned short GetFieldRawSize( cFieldDataType data_type )
{
    return TypeSizeMaps[data_type].RawSize;
}

bool IsFixedSizeDataType( cFieldDataType data_type )
{
    return ( data_type != ftString && data_type != ftWString && data_type != ftBlob );
}

template <class T> int FASTCALL aligned_offset( std::size_t end_offset )
{
    std::size_t     modulo = end_offset % boost::alignment_of<T>::value;

    return ( modulo == 0 ? end_offset : end_offset + boost::alignment_of<T>::value - modulo );
}

}; // namespace

//***********************************************************************
//******    cFieldDef
//***********************************************************************
CDFASTCALL cFieldDef::cFieldDef( unsigned short idx, int offset, const ds_string& name,
                                 cFieldKind kind, cFieldDataType data_type, unsigned int size )
    : mIndex(idx), mOffset(offset), mName(name), mKind(kind), mDataType(data_type),
      mRawSize(GetFieldRawSize( data_type )),
      mDataSize(IsFixedSizeDataType( data_type ) ? mRawSize : size)
{
}

CDFASTCALL cFieldDef::~cFieldDef()
{
}

bool FASTCALL cFieldDef::operator == ( const cFieldDef& other ) const
{
    return
    (
        mIndex == other.mIndex
        && mOffset == other.mOffset
        && mName == other.mName
        && mKind == other.mKind
        && mDataType == other.mDataType
        && mRawSize == other.mRawSize
        && mDataSize == other.mDataSize
    );
}

cStream& FASTCALL operator << ( cStream& st, const cFieldDef a )
{
    st << a.mIndex << a.mOffset << a.mName << a.mKind << a.mDataType << a.mDataSize;
    return ( st );
}

cStream& FASTCALL operator >> ( cStream& st, cFieldDef& a )
{
    st >> a.mIndex >> a.mOffset >> a.mName >> a.mKind >> a.mDataType >> a.mDataSize;
    a.mRawSize = GetFieldRawSize( a.mDataType );
    return ( st );
}

//***********************************************************************
//******    cFieldDefs
//***********************************************************************
CDFASTCALL cFieldDefs::cFieldDefs()
    : mBufferSize(0), mFieldDefs(), mFieldDefSorted()
{
}

class cSortByFieldName : public std::binary_function< const detail::cFieldNameMap&, const detail::cFieldNameMap&, bool>
{
public:
    result_type operator() ( first_argument_type name1, second_argument_type name2 )
    {
        return ( StringCompare( name1.FieldName(), name2.FieldName() ) < 0 );
    }
};

CDFASTCALL cFieldDefs::cFieldDefs( const detail::cFieldDefs_& field_defs )
    : mBufferSize(0), mFieldDefs(), mFieldDefSorted()
{
    // mFieldDefs.reserve( field_defs.mCount );
    for ( int n = 0 ; n < field_defs.mCount ; ++n )
    {
        const detail::cFieldDef_&   field_def = field_defs.mFieldDefs[n];

        mFieldDefs.push_back( cFieldDef( field_def.mIndex, field_def.mOffset, field_def.mName,
                                         field_def.mKind, field_def.mDataType, field_def.mDataSize ) );
    }

    const cFieldDef&    field_def = mFieldDefs.back();

    mBufferSize = field_def.Offset() + field_def.RawSize();
    ConstructSorted();
}

CDFASTCALL cFieldDefs::cFieldDefs( const cFieldDefs& src )
    : mBufferSize(src.mBufferSize), mFieldDefs(src.mFieldDefs), mFieldDefSorted()
{
    ConstructSorted();
}

cFieldDefs& FASTCALL cFieldDefs::operator=( const cFieldDefs& src )
{
    cFieldDefs  tmp( src );

    swap( tmp );
    return ( *this );
}

CDFASTCALL cFieldDefs::~cFieldDefs()
{
}

void FASTCALL cFieldDefs::swap( cFieldDefs& src )
{
    std::swap( mBufferSize, src.mBufferSize );
    mFieldDefs.swap( src.mFieldDefs );
    mFieldDefSorted.swap( src.mFieldDefSorted );
}

//bool FASTCALL cFieldDefs::equal( const cFieldDefs& field_defs ) const
//{
//    bool    result = mFieldDefs.size() == field_defs.mFieldDefs.size();
//
//    if ( result )
//        result = std::equal( mFieldDefs.begin(), mFieldDefs.end(), field_defs.mFieldDefs.begin() );
//    return ( result );
//}

//const cFieldDef& FASTCALL cFieldDefs::Fields( int idx ) const
//{
//    cFieldDefContainer::const_iterator      iter = mFieldDefs.begin();
//
//    std::advance( iter, idx );
//    return ( *iter );
//}

void FASTCALL cFieldDefs::ConstructSorted()
{
    for ( cFieldDefs::iterator n = mFieldDefs.begin(), eend = mFieldDefs.end() ; n != eend ; ++n )
        mFieldDefSorted.push_back( detail::cFieldNameMap( n->Name(), *n ) );
    std::sort( mFieldDefSorted.begin(), mFieldDefSorted.end(), cSortByFieldName() );
}

const cFieldDef FASTCALL cFieldDefs::MakeFieldDef( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned int size )
{
    int     offset;

    if ( mFieldDefs.empty() )
        offset = 0;
    else
    {
        const cFieldDef&    last = mFieldDefs.back();

        offset = last.Offset() + last.RawSize();
    }
    switch ( data_type )
    {
        case ftBool     : offset = aligned_offset<bool>( offset );                          break;
        case ftByte     : offset = aligned_offset<char>( offset );                          break;
        case ftShort    : offset = aligned_offset<short>( offset );                         break;
        case ftInteger  : offset = aligned_offset<int>( offset );                           break;
        case ftLongLong : offset = aligned_offset<long long>( offset );                     break;
        case ftDouble   : offset = aligned_offset<double>( offset );                        break;
        case ftDate     : offset = aligned_offset<detail::dbDate_Internal>( offset );       break;
        case ftTime     : offset = aligned_offset<detail::dbTime_Internal>( offset );       break;
        case ftDateTime : offset = aligned_offset<detail::dbDateTime_Internal>( offset );   break;
        case ftGUID     : offset = aligned_offset<detail::dbGUID_Internal>( offset );       break;
        case ftString   : offset = aligned_offset<ds_string *>( offset );                   break;
        case ftWString  : offset = aligned_offset<ds_wstring *>( offset );                  break;
        case ftBlob     : offset = aligned_offset<var_blob_type *>( offset );               break;
        default : throw eUnknownFieldType();
    };
    return ( cFieldDef( static_cast<unsigned short>(mFieldDefs.size()), offset, name, kind, data_type, size ) );
}

//void FASTCALL cFieldDefs::clear()
//{
//    mFieldDefSorted.clear();
//    mFieldDefs.clear();
//    mBufferSize = 0;
//}

const cFieldDef& FASTCALL cFieldDefs::AddField( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned int size )
{
    cFieldDef   field = MakeFieldDef( name, kind, data_type, size );

    std::pair<cFieldDefSortedContainer::iterator, cFieldDefSortedContainer::iterator>     pos
        = std::equal_range( mFieldDefSorted.begin(), mFieldDefSorted.end(), detail::cFieldNameMap( name ), cSortByFieldName() );

    if ( pos.first != pos.second )
        throw eFieldExists();
    mFieldDefs.push_back( field );

    cFieldDef&      result = mFieldDefs.back();

    mBufferSize = result.Offset() + result.RawSize();
    mFieldDefSorted.insert( pos.first, detail::cFieldNameMap( result.Name(), result ) );

    return result;
}

const cFieldDef& FASTCALL cFieldDefs::FieldByName( const ds_string& field_name ) const
{
    const cFieldDef     *result = FindField( field_name );

    if ( result == 0 )
        throw eFieldNotFound();
    return *result;
}

const cFieldDef& FASTCALL cFieldDefs::FieldByName( const char *field_name ) const
{
    return FieldByName( ds_string( field_name ) );
}

const cFieldDef * FASTCALL cFieldDefs::FindField( const ds_string& field_name ) const
{
    const detail::cFieldNameMap     field_map( field_name );            // only "field_name" is relevant

    cFieldDefSortedContainer::const_iterator    pos = std::lower_bound( mFieldDefSorted.begin(), mFieldDefSorted.end(),
                                                                        field_map, cSortByFieldName() );

    if ( pos == mFieldDefSorted.end() || StringCompare( pos->FieldName(), field_name ) != 0  )
        return 0;
    return &pos->FieldDef();
}

const cFieldDef * FASTCALL cFieldDefs::FindField( const char *field_name ) const
{
    return FindField( ds_string( field_name ) );
}

//---------------------------------------------------------------------------
}; // namespace smds
//---------------------------------------------------------------------------


