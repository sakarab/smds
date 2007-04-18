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

#include "dsBuffer.h"
#include "dsExceptions.h"
#include "dsIndex.h"
#include "dsCompareControlers.h"
//---------------------------------------------------------------------------
namespace smds
{

//***********************************************************************
//******    cRawBuffer
//***********************************************************************
void FASTCALL cRawBuffer::SetNull( const cFieldDef& field_def, bool value )
{
    SetBit( field_def.Index(), value );
}

void FASTCALL cRawBuffer::SetNull( const cFieldDef_& field_def, bool value )
{
    SetBit( field_def.mIndex, value );
}

bool FASTCALL cRawBuffer::IsNull( const cFieldDef& field_def ) const
{
    return ( TestBit( field_def.Index() ) );
}

bool FASTCALL cRawBuffer::IsNull( const cFieldDef_& field_def ) const
{
    return ( TestBit( field_def.mIndex ) );
}

void FASTCALL cRawBuffer::Nullify( const cFieldDef& field_def )
{
    SetBit( field_def.Index(), true );
}

Variant FASTCALL cRawBuffer::ReadVariant( const cFieldDef& field_def ) const
{
    if ( IsNull( field_def ) )
        return ( Variant() );
    else switch ( field_def.DataType() )
    {
        case ftBool     : return ( Variant( ReadBoolNN( field_def ) ) );
        case ftChar     : return ( Variant( ReadCharNN( field_def ) ) );
        case ftWChar    : return ( Variant( ReadWCharNN( field_def ) ) );
        case ftShort    : return ( Variant( ReadShortNN( field_def ) ) );
        case ftInteger  : return ( Variant( ReadIntegerNN( field_def ) ) );
        case ftLong     : return ( Variant( ReadLongNN( field_def ) ) );
        case ftDouble   : return ( Variant( ReadFloatNN( field_def ) ) );
        case ftDateTime : return ( Variant( ReadDateNN( field_def ) ) );
        case ftString   : return ( Variant( ReadStringNN( field_def ) ) );
        //case ftWString  : return ( Variant( ReadWStringNN( field_def ) ) );
        //case ftBlob     : return ( Variant( ReadBlobNN( field_def ) ) );
        default         : throw eVariantConversion();
    }
}

void FASTCALL cRawBuffer::WriteVariant( const cFieldDef& field_def, const Variant& value )
{
    if ( value.IsNull() )
        return ( Nullify( field_def ) );
    else switch ( field_def.DataType() )
    {
        case ftBool     : WriteBool( field_def, value.AsBool() );               break;
        case ftChar     : WriteChar( field_def, value.AsChar() );               break;
        case ftWChar    : WriteWChar( field_def, value.AsWChar() );             break;
        case ftShort    : WriteShort( field_def, value.AsShort() );             break;
        case ftInteger  : WriteInteger( field_def, value.AsInt() );             break;
        case ftLong     : WriteLong( field_def, value.AsLong() );               break;
        case ftDouble   : WriteFloat( field_def, value.AsDouble() );            break;
        case ftDateTime : WriteDate( field_def, value.AsDateTime() );           break;
        case ftString   : WriteString( field_def, value.AsString() );           break;
        //case ftWString  : WriteString( *mFieldDef, value.AsWString() );        break;
        default         : throw eVariantConversion();
    }
}

#ifdef SM_DS_STRING_AS_STRING
ds_string& FASTCALL cRawBuffer::empty_string()
{
    static  ds_string   empty;

    return ( empty );
}
#endif

//***********************************************************************
//******    cDoubleBuffer
//***********************************************************************
CDFASTCALL cDoubleBuffer::cDoubleBuffer( cFieldDefs *field_defs, bool unmodified )
    : mOriginalData( field_defs, unmodified ),
      mModifiedData( field_defs, ! unmodified ),
      mUpdateStatus( unmodified ? usUnmodified : usInserted ), mFieldDefs(field_defs)
{
}

CDFASTCALL cDoubleBuffer::~cDoubleBuffer()
{
}

void FASTCALL cDoubleBuffer::CommitUpdates()
{
    if ( mUpdateStatus != usUnmodified )
    {
        mModifiedData.swap( mOriginalData );
        mModifiedData.destroy( mFieldDefs );
        mUpdateStatus = usUnmodified;
    }
}

//***********************************************************************
//******    cData
//***********************************************************************
CDFASTCALL cData::cData()
: mData(), mFieldDefs( new cFieldDefs() )
{
}

CDFASTCALL cData::cData( const cFieldDefs_& field_defs )
    : mData(), mFieldDefs( new cFieldDefs( field_defs ) )
{
}

CDFASTCALL cData::cData( const cFieldDefs_ptr& field_defs )
    : mData(), mFieldDefs( field_defs )
{
}

CDFASTCALL cData::~cData()
{
}

void FASTCALL cData::Clear()
{
    mData = container();
}

void FASTCALL cData::CommitUpdates()
{
    for ( iterator n = mData.begin(), eend = mData.end() ; n != eend ; ++n )
        (*n)->CommitUpdates();
}

// returns a ref counted double buffer, in usUnmodified state, **not** inserted in the container
cData::value_type FASTCALL cData::NewBuffer_usUnmodified()
{
    return ( cData::value_type( new cDoubleBuffer( mFieldDefs.get(), true ) ) );
}

// returns a ref counted double buffer, in usInserted state, **not** inserted in the container
cData::value_type FASTCALL cData::NewBuffer_usInserted()
{
    return ( cData::value_type( new cDoubleBuffer( mFieldDefs.get(), false ) ) );
}

int FASTCALL cData::AddBuffer_ptr( const value_type& value )
{
    mData.push_back( value );
    return ( size() - 1 );
}

void FASTCALL cData::AddField( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned short size )
{
    mFieldDefs->AddField( name, kind, data_type, size );
}

cData_ptr FASTCALL cData::Clone_All()
{
    cData_ptr   result( new cData( GetFieldDefs() ) );

    std::copy( mData.begin(), mData.end(), std::back_inserter( result->mData ) );
    return result;
}

void FASTCALL cData::Sort( const detail::SortControler& cmp )
{
    std::sort( mData.begin(), mData.end(), cmp );
}

void FASTCALL cData::Locate( const OpenValues& values, const OpenFindFields& fields,
                             iterator begin, iterator end, locate_result& result )
{
    cData::value_type   tmp_rec = NewBuffer_usInserted();
    cRawBuffer&         raw_buffer = tmp_rec->GetActiveData();

    for ( int n = 0 ; n < values.GetCount() ; ++n )
        raw_buffer.WriteVariant( mFieldDefs->FieldByName( (fields.GetArray()[n])->GetFieldName() ),
                                 *(values.GetArray()[n]) );

    cSortCompareBase_ptr    cmp_func( new cFindCompareStd( fields ) );

    cmp_func->Initialize( mFieldDefs );

    cData::iterator     rslt = std::find_if( begin, end, detail::FindControler( cmp_func, tmp_rec->GetActiveData() ) );

    result.first = rslt != mData.end();
    if ( result.first )
        result.second = std::distance( mData.begin(), rslt );
    else
        result.second = mData.size();
}

void FASTCALL cData::Locate( const OpenValues& values, const OpenFindFields& fields, locate_result& result )
{
    Locate( values, fields, mData.begin(), mData.end(), result );
}

void FASTCALL cData::Locate( const OpenValues& values, const OpenFindFields& fields,
                             size_type start, size_type end, locate_result& result )
{
    Locate( values, fields, mData.begin() + start, mData.begin() + end, result );
}

void FASTCALL cData::Find_0( const cData::value_type& double_buffer, cSortCompareBase_ptr& compare,
                             iterator begin, iterator end, locate_result& result )
{
    detail::SortControler   cc = detail::SortControler( compare );
    cData::iterator         rslt = std::lower_bound( begin, end, double_buffer, cc );

    result.first = ( rslt != mData.end() && !cc( *rslt, double_buffer ) && !cc( double_buffer, *rslt ) );
    if ( result.first )
        result.second = std::distance( mData.begin(), rslt );
    else
        result.second = mData.size();
}

void FASTCALL cData::Find( const OpenValues& values, cSortCompareBase_ptr& compare,
                           iterator begin, iterator end, locate_result& result )
{
    // the comparizon function must be cIndexSortCompareStd. There is no other way to do a Find
    if ( dynamic_cast<cIndexSortCompareStd *>(compare.get()) == 0 )
    {
        result.first = false;
        result.second = mData.size();
    }
    else
    {
        cIndexSortCompareStd                *cmp = static_cast<cIndexSortCompareStd *>(compare.get());
        const std::vector<cIndexField>&     index_fields = cmp->GetIndexFields();
        int                                 trip_count = std::min<int>( values.GetCount(), index_fields.size() );
        cData::value_type                   tmp_rec = NewBuffer_usInserted();
        cRawBuffer&                         raw_buffer = tmp_rec->GetActiveData();

        for ( int n = 0 ; n < trip_count ; ++n )
            raw_buffer.WriteVariant( mFieldDefs->FieldByName( index_fields[n].GetFieldName() ), *(values.GetArray()[n]) );

        cIndexSortCompareStd::CompareFieldCountGuard    count_guard( *cmp, trip_count );

        Find_0( tmp_rec, compare, begin, end, result );
    }
}

void FASTCALL cData::Find( const OpenValues& values, cSortCompareBase_ptr& compare, locate_result& result )
{
    Find( values, compare, mData.begin(), mData.end(), result );
}

void FASTCALL cData::Find( const OpenValues& values, cSortCompareBase_ptr& compare,
                           size_type start, size_type end, locate_result& result )
{
    Find( values, compare, mData.begin() + start, mData.begin() + end, result );
}

void FASTCALL cData::GetRange( const OpenRangeValues& values, cSortCompareBase_ptr& compare, range_result& result )
{
    // the comparizon function must be cIndexSortCompareStd. There is no other way to do a Find
    if ( dynamic_cast<cIndexSortCompareStd *>(compare.get()) == 0 )
    {
        result.first = false;
        result.second.first = mData.size();
        result.second.second = result.second.first;
    }
    else
    {
        cIndexSortCompareStd                *cmp = static_cast<cIndexSortCompareStd *>(compare.get());
        const std::vector<cIndexField>&     index_fields = cmp->GetIndexFields();
        int                                 trip_count = std::min<int>( values.GetCount(), index_fields.size() );
        cData::value_type                   tmp_rec = NewBuffer_usInserted();
        cRawBuffer&                         raw_buffer = tmp_rec->GetActiveData();

        for ( int n = 0 ; n < trip_count ; ++n )
            raw_buffer.WriteVariant( mFieldDefs->FieldByName( index_fields[n].GetFieldName() ), (values.GetArray()[n])->First() );

        cIndexSortCompareStd::CompareFieldCountGuard    count_guard( *cmp, trip_count );

        locate_result   loc_1;

        Find_0( tmp_rec, compare, mData.begin(), mData.end(), loc_1 );
        if ( ! loc_1.first )
        {
            result.first = false;
            result.second.first = loc_1.second;
            result.second.second = loc_1.second;
        }
        else
        {
            for ( int n = 0 ; n < trip_count ; ++n )
                raw_buffer.WriteVariant( mFieldDefs->FieldByName( index_fields[n].GetFieldName() ), (values.GetArray()[n])->Second() );

            locate_result   loc_2;

            Find_0( tmp_rec, compare, mData.begin(), mData.end(), loc_2 );
            if ( ! loc_2.first )
            {
                result.first = false;
                result.second.first = loc_2.second;
                result.second.second = loc_2.second;
            }
            else
            {
                result.first = true;
                result.second.first = loc_1.second;
                result.second.second = loc_2.second;
            }
        }
    }
}

};
//---------------------------------------------------------------------------

