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
#include "dsVariant.h"

namespace smds
{

// cFieldDataType_sync
unsigned short GetFieldDataSize( cFieldDataType data_type, unsigned short size )
{
    unsigned short  result;

    switch ( data_type )
    {
        case ftBool :
            result = sizeof(bool);
            break;
        case ftChar :
            result = sizeof(char);
            break;
        case ftWChar :
            result = sizeof(wchar_t);
            break;
        case ftShort :
            result = sizeof(short);
            break;
        case ftInteger :
            result = sizeof(int);
            break;
        case ftLong :
            result = sizeof(long);
            break;
        case ftDouble :
            result = sizeof(double);
            break;
        case ftDateTime :
            result = sizeof(cDateTime);
            break;
        case ftString :
#ifdef SM_DS_STRING_AS_STRING
            result = sizeof(ds_string);
#else
            result = size;
#endif
            break;
        //case ftWString :
        //    result = static_cast<unsigned short>(size * sizeof(wchar_t));
        //    break;
        case ftBlob :
            result = sizeof(var_blob_type);
            break;
        default :
            throw eUnknownFieldType();
    }
    return ( result );
}

//***********************************************************************
//******    cFieldDef
//***********************************************************************
CDFASTCALL cFieldDef::cFieldDef( unsigned short idx, int offset, const ds_string& name,
                                 cFieldKind kind, cFieldDataType data_type, unsigned short size )
    : mIndex(idx), mOffset(offset), mName(name), mKind(kind), mDataType(data_type),
#ifdef SM_DS_STRING_AS_STRING
      mSize_(GetFieldDataSize( data_type, size )), mDataSize_(size)
#else
      mSize_(size)
#endif
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
        && mSize_ == other.mSize_
#ifdef SM_DS_STRING_AS_STRING
        && mDataSize_ == other.mDataSize_
#endif
    );
}

cStream& FASTCALL operator << ( cStream& st, const cFieldDef a )
{
    st << a.mIndex << a.mOffset << a.mName << a.mKind << a.mDataType
#ifdef SM_DS_STRING_AS_STRING
       << a.mDataSize_;
#else
       << a.mSize_;
#endif
    return ( st );
}

cStream& FASTCALL operator >> ( cStream& st, cFieldDef& a )
{
    st >> a.mIndex >> a.mOffset >> a.mName >> a.mKind >> a.mDataType
#ifdef SM_DS_STRING_AS_STRING
       >> a.mDataSize_;
       a.mSize_ = GetFieldDataSize( a.mDataType, 0 );
#else
       >> a.mSize_;
#endif
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

CDFASTCALL cFieldDefs::cFieldDefs( const cFieldDefs_& field_defs )
    : mBufferSize(0), mFieldDefs(), mFieldDefSorted()
{
    // mFieldDefs.reserve( field_defs.mCount );
    for ( int n = 0 ; n < field_defs.mCount ; ++n )
    {
        const cFieldDef_&   field_def = field_defs.mFieldDefs[n];

        mFieldDefs.push_back( cFieldDef( field_def.mIndex, field_def.mOffset, field_def.mName,
                                         field_def.mKind, field_def.mDataType, field_def.mSize ) );
    }

    const cFieldDef&    field_def = mFieldDefs.back();

    mBufferSize = field_def.Offset() + field_def.Size_();
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

const cFieldDef FASTCALL cFieldDefs::MakeFieldDef( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned short size )
{
    int     offset;

    if ( mFieldDefs.empty() )
        offset = 0;
    else
    {
        const cFieldDef&    last = mFieldDefs.back();

        offset = last.Offset() + last.Size_();
    }
    return ( cFieldDef( static_cast<unsigned short>(mFieldDefs.size()), offset, name,
                        kind, data_type, GetFieldDataSize( data_type, size ) ) );
}

//void FASTCALL cFieldDefs::clear()
//{
//    mFieldDefSorted.clear();
//    mFieldDefs.clear();
//    mBufferSize = 0;
//}

const cFieldDef& FASTCALL cFieldDefs::AddField( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned short size )
{
    cFieldDef   field = MakeFieldDef( name, kind, data_type, size );

    std::pair<cFieldDefSortedContainer::iterator, cFieldDefSortedContainer::iterator>     pos
        = std::equal_range( mFieldDefSorted.begin(), mFieldDefSorted.end(), detail::cFieldNameMap( name ), cSortByFieldName() );

    if ( pos.first != pos.second )
        throw eFieldExists();
    mFieldDefs.push_back( field );

    cFieldDef&      result = mFieldDefs.back();

    mBufferSize += result.Size_();
    mFieldDefSorted.insert( pos.first, detail::cFieldNameMap( result.Name(), result ) );

    return ( result );
}

const cFieldDef& FASTCALL cFieldDefs::FieldByName( const ds_string& field_name ) const
{
    const detail::cFieldNameMap     field_map( field_name );            // only "field_name" is relevant

    cFieldDefSortedContainer::const_iterator    pos = std::lower_bound( mFieldDefSorted.begin(), mFieldDefSorted.end(),
                                                                        field_map, cSortByFieldName() );

    if ( pos == mFieldDefSorted.end() || StringCompare( pos->FieldName(), field_name ) != 0  )
        throw eFieldNotFound();
    return ( pos->FieldDef() );
}

const cFieldDef& FASTCALL cFieldDefs::FieldByName( const char *field_name ) const
{
    return ( FieldByName( ds_string( field_name ) ) );
}

/*
const cFieldDef& FASTCALL cFieldDefs::AddField( const cFieldDef& field )
{
    mFieldDefs.push_back( field );
    mBufferSize += mFieldDefs.back().Size();
    return ( mFieldDefs.back() );
}
*/

//---------------------------------------------------------------------------
};
//---------------------------------------------------------------------------


