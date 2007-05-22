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

namespace detail
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
//******    DoubleBuffer
//***********************************************************************
CDFASTCALL DoubleBuffer::DoubleBuffer( cFieldDefs *field_defs, bool unmodified )
    : mOriginalData( field_defs, unmodified ),
      mModifiedData( field_defs, ! unmodified ),
      mUpdateStatus( unmodified ? usUnmodified : usInserted ), mFieldDefs(field_defs)
{
}

CDFASTCALL DoubleBuffer::~DoubleBuffer()
{
}

void FASTCALL DoubleBuffer::CommitUpdates()
{
    if ( mUpdateStatus != usUnmodified )
    {
        mModifiedData.swap( mOriginalData );
        mModifiedData.destroy( mFieldDefs );
        mUpdateStatus = usUnmodified;
    }
}

//***********************************************************************
//******    Data
//***********************************************************************
#if defined(SM_DS_ENABLE_NOTIFY)
CDFASTCALL Data::Data( IDataNotify *i_notify )
    : mData(), mFieldDefs( new cFieldDefs() ), mDeleted( new container ),
      mLockCount( new int(0) ), mRelatedData(this), mTableNotify(i_notify)
{
}

CDFASTCALL Data::Data( const cFieldDefs_& field_defs, IDataNotify *i_notify )
    : mData(), mFieldDefs( new cFieldDefs( field_defs ) ), mDeleted( new container ),
      mLockCount( new int(0) ), mRelatedData(this), mTableNotify(i_notify)
{
}

CDFASTCALL Data::Data( const spFieldDefs& field_defs, const deleted_container& deleted,
                       lock_counter lock_count, IDataNotify *i_notify )
    : mData(), mFieldDefs( field_defs ), mDeleted(deleted),
      mLockCount(lock_count), mRelatedData(this), mTableNotify(i_notify)
{
}

#else
CDFASTCALL Data::Data()
    : mData(), mFieldDefs( new cFieldDefs() ), mDeleted( new container )
{
}

CDFASTCALL Data::Data( const cFieldDefs_& field_defs )
    : mData(), mFieldDefs( new cFieldDefs( field_defs ) ), mDeleted( new container )
{
}

CDFASTCALL Data::Data( const spFieldDefs& field_defs, const deleted_container& deleted )
    : mData(), mFieldDefs( field_defs ), mDeleted(deleted)
{
}
#endif

CDFASTCALL Data::~Data()
{
#if defined(SM_DS_ENABLE_NOTIFY)
    RemoveRelation( this );
#endif
}

#if defined(SM_DS_ENABLE_NOTIFY)
void FASTCALL Data::NotifyRecordAdded( const value_type& value )
{
    Data    *relation = mRelatedData;
    bool    lock = *mLockCount != 0;

    while ( relation != this )
    {
        mRelatedData->mTableNotify->RecordAdded( value, lock );
        relation = relation->mRelatedData;
    }
}

void FASTCALL Data::NotifyRecordDeleted( const value_type& value )
{
    Data    *relation = mRelatedData;

    while ( relation != this )
    {
        relation->mTableNotify->RecordDeleted( value );
        relation = relation->mRelatedData;
    }
}

void FASTCALL Data::NotifyOpened()
{
    std::vector<IDataNotify *>  notifies;

    GetNotifies( notifies );
    for ( std::vector<IDataNotify *>::iterator it = notifies.begin(), eend = notifies.end() ; it != eend ; ++it )
        (*it)->DataOpened( *this );
}

void FASTCALL Data::NotifyClosed()
{
    std::vector<IDataNotify *>  notifies;

    GetNotifies( notifies );
    for ( std::vector<IDataNotify *>::iterator it = notifies.begin(), eend = notifies.end() ; it != eend ; ++it )
        (*it)->DataClosed();
}

void FASTCALL Data::NotifyUpdateLockReleased()
{
    Data    *relation = mRelatedData;

    while ( relation != this )
    {
        relation->mTableNotify->UpdateLockReleased();
        relation = relation->mRelatedData;
    }
}

void FASTCALL Data::GetNotifies( std::vector<IDataNotify *>& notifies )
{
    Data                        *relation = mRelatedData;

    while ( relation != this )
    {
        notifies.push_back( relation->mTableNotify );
        relation = relation->mRelatedData;
    }
}

#endif

#if defined(SM_DS_ENABLE_NOTIFY)
void FASTCALL Data::LockUpdates()
{
    ++(*mLockCount);
}

void FASTCALL Data::UnlockUpdates()
{
    int     *count = mLockCount.get();

    if ( *count )
        if ( --(*count) == 0 )
            NotifyUpdateLockReleased();
}
#endif

void FASTCALL Data::Clear()
{
    mData = container();
}

void FASTCALL Data::CommitUpdates()
{
    for ( iterator n = mData.begin(), eend = mData.end() ; n != eend ; ++n )
        (*n)->CommitUpdates();
}

// returns a ref counted double buffer, in usUnmodified state, **not** inserted in the container
Data::value_type FASTCALL Data::NewBuffer_usUnmodified()
{
    return Data::value_type( new DoubleBuffer( mFieldDefs.get(), true ) );
}

// returns a ref counted double buffer, in usInserted state, **not** inserted in the container
Data::value_type FASTCALL Data::NewBuffer_usInserted()
{
    return Data::value_type( new DoubleBuffer( mFieldDefs.get(), false ) );
}

int FASTCALL Data::AddBuffer_ptr( const value_type& value )
{
    mData.push_back( value );
    return ( size() - 1 );
}

int FASTCALL Data::AddBuffer( const value_type& value )
{
    mData.push_back( value );
#if defined(SM_DS_ENABLE_NOTIFY)
    NotifyRecordAdded( value );
#endif
    return ( size() - 1 );
}

// assume a sorted container and insert it in the right position
void FASTCALL Data::InsertBuffer_ptr( const value_type& value, spSortCompare& compare )
{
    SortControler       cc = SortControler( compare );
    Data::iterator      rslt = std::lower_bound( mData.begin(), mData.end(), value, cc );

    mData.insert( rslt, value );
}

void FASTCALL Data::DeleteBuffer_ptr( const value_type& value )
{
    DoubleBuffer    *tmp = value.get();

    for ( iterator it = mData.begin(), eend = mData.end() ; it != eend ; ++it )
    {
        if ( it->get() == tmp )
        {
            mData.erase( it );
            break;
        }
    }
}

void FASTCALL Data::Delete( int idx )
{
    iterator        tmp( mData.begin() + idx );

    if ( (*tmp)->GetUpdateStatus() != usInserted )
        mDeleted->push_back( *tmp );
#if defined(SM_DS_ENABLE_NOTIFY)
    NotifyRecordDeleted( *tmp );
#endif
    mData.erase( tmp );
}

void FASTCALL Data::AddField( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned short size )
{
    mFieldDefs->AddField( name, kind, data_type, size );
}

#if defined(SM_DS_ENABLE_NOTIFY)
spData FASTCALL Data::Clone_All( IDataNotify *i_notify )
#else
spData FASTCALL Data::Clone_All()
#endif
{
#if defined(SM_DS_ENABLE_NOTIFY)
    spData      result( new Data( GetFieldDefs(), mDeleted, mLockCount, i_notify ) );
#else
    spData      result( new Data( GetFieldDefs(), mDeleted ) );
#endif

    std::copy( mData.begin(), mData.end(), std::back_inserter( result->mData ) );
#if defined(SM_DS_ENABLE_NOTIFY)
    AddRelation( result.get() );
#endif
    return result;
}

void FASTCALL Data::Sort( const SortControler& cmp )
{
    std::sort( mData.begin(), mData.end(), cmp );
}

void FASTCALL Data::Locate( const OpenValues& values, const OpenFindFields& fields,
                             iterator begin, iterator end, locate_result& result )
{
    Data::value_type   tmp_rec = NewBuffer_usInserted();
    cRawBuffer&         raw_buffer = tmp_rec->GetActiveData();

    for ( int n = 0 ; n < values.GetCount() ; ++n )
        raw_buffer.WriteVariant( mFieldDefs->FieldByName( (fields.GetArray()[n])->GetFieldName() ),
                                 *(values.GetArray()[n]) );

    spSortCompare       cmp_func( new cFindCompareStd( fields ) );

    cmp_func->Initialize( mFieldDefs );

    Data::iterator     rslt = std::find_if( begin, end, FindControler( cmp_func, tmp_rec->GetActiveData() ) );

    result.first = rslt != mData.end();
    if ( result.first )
        result.second = std::distance( mData.begin(), rslt );
    else
        result.second = mData.size();
}

void FASTCALL Data::Locate( const OpenValues& values, const OpenFindFields& fields, locate_result& result )
{
    Locate( values, fields, mData.begin(), mData.end(), result );
}

void FASTCALL Data::Locate( const OpenValues& values, const OpenFindFields& fields,
                             size_type start, size_type end, locate_result& result )
{
    Locate( values, fields, mData.begin() + start, mData.begin() + end, result );
}

void FASTCALL Data::Find_0( const Data::value_type& double_buffer, spSortCompare& compare,
                             iterator begin, iterator end, locate_result& result )
{
    SortControler       cc = SortControler( compare );
    Data::iterator      rslt = std::lower_bound( begin, end, double_buffer, cc );

    result.first = ( rslt != mData.end() && !cc( *rslt, double_buffer ) && !cc( double_buffer, *rslt ) );
    if ( result.first )
        result.second = std::distance( mData.begin(), rslt );
    else
        result.second = mData.size();
}

void FASTCALL Data::Find( const OpenValues& values, spSortCompare& compare,
                           iterator begin, iterator end, locate_result& result )
{
    // the comparizon function must be FieldSortCompare. There is no other way to do a Find
    if ( dynamic_cast<FieldSortCompare *>(compare.get()) == 0 )
    {
        result.first = false;
        result.second = mData.size();
    }
    else
    {
        FieldSortCompare                    *cmp = static_cast<FieldSortCompare *>(compare.get());
        const std::vector<cIndexField>&     index_fields = cmp->GetIndexFields();
        int                                 trip_count = std::min<int>( values.GetCount(), index_fields.size() );
        Data::value_type                    tmp_rec = NewBuffer_usInserted();
        cRawBuffer&                         raw_buffer = tmp_rec->GetActiveData();

        for ( int n = 0 ; n < trip_count ; ++n )
            raw_buffer.WriteVariant( mFieldDefs->FieldByName( index_fields[n].GetFieldName() ), *(values.GetArray()[n]) );

        FieldSortCompare::CompareFieldCountGuard    count_guard( *cmp, trip_count );

        Find_0( tmp_rec, compare, begin, end, result );
    }
}

void FASTCALL Data::Find( const OpenValues& values, spSortCompare& compare, locate_result& result )
{
    Find( values, compare, mData.begin(), mData.end(), result );
}

void FASTCALL Data::Find( const OpenValues& values, spSortCompare& compare,
                           size_type start, size_type end, locate_result& result )
{
    Find( values, compare, mData.begin() + start, mData.begin() + end, result );
}

void FASTCALL Data::GetRange( const OpenRangeValues& values, spSortCompare& compare, range_result& result )
{
    // the comparizon function must be FieldSortCompare. There is no other way to do a Find
    if ( dynamic_cast<FieldSortCompare *>(compare.get()) == 0 )
    {
        result.first = false;
        result.second.first = mData.size();
        result.second.second = result.second.first;
    }
    else
    {
        FieldSortCompare                    *cmp = static_cast<FieldSortCompare *>(compare.get());
        const std::vector<cIndexField>&     index_fields = cmp->GetIndexFields();
        int                                 trip_count = std::min<int>( values.GetCount(), index_fields.size() );
        Data::value_type                    tmp_rec = NewBuffer_usInserted();
        cRawBuffer&                         raw_buffer = tmp_rec->GetActiveData();

        for ( int n = 0 ; n < trip_count ; ++n )
            raw_buffer.WriteVariant( mFieldDefs->FieldByName( index_fields[n].GetFieldName() ), (values.GetArray()[n])->First() );

        FieldSortCompare::CompareFieldCountGuard    count_guard( *cmp, trip_count );

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

}; // namespace detail

}; // namespace smds
//---------------------------------------------------------------------------

