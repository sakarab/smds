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
#include "pre_smDS.h"
#include "dsBuffer.h"
#include "dsExceptions.h"
#include "dsCompare.h"
#include "dsCompareControlers.h"
//---------------------------------------------------------------------------
namespace smds
{

namespace detail
{

//***********************************************************************
//******    cRawBuffer
//***********************************************************************
void cRawBuffer::SetNull( const cFieldDef& field_def, bool value )
{
    NullBits::SetBit( mNullBits, field_def.Index(), value );
}

void cRawBuffer::SetNull( const cFieldDef_& field_def, bool value )
{
    NullBits::SetBit( mNullBits, field_def.mIndex, value );
}

bool cRawBuffer::IsNull( const cFieldDef& field_def ) const
{
    return (mData.get() == 0) || NullBits::TestBit( mNullBits, field_def.Index() );
}

bool cRawBuffer::IsNull( const cFieldDef_& field_def ) const
{
    return (mData.get() == 0) || NullBits::TestBit( mNullBits, field_def.mIndex );
}

void cRawBuffer::Nullify( const cFieldDef& field_def )
{
    if ( field_def.DataType() == ftString )
    {
        if ( ds_string **data = string_ptr_ptr( field_def.Offset() ) )
        {
            delete *data;
            *data = 0;
        }
    }
    else if ( field_def.DataType() == ftWString )
    {
        if ( ds_wstring **data = wstring_ptr_ptr( field_def.Offset() ) )
        {
            delete *data;
            *data = 0;
        }
    }
    else if ( field_def.DataType() == ftBlob )
    {
        if ( var_blob_type **data = blob_ptr_ptr( field_def.Offset() ) )
        {
            delete *data;
            *data = 0;
        }
    }
    NullBits::SetBit( mNullBits, field_def.Index(), true );
}

Variant cRawBuffer::ReadVariant( const cFieldDef& field_def ) const
{
    if ( IsNull( field_def ) )
        return Variant();
    else switch ( field_def.DataType() )
    {
        case ftBool     : return Variant( ReadBoolNN( field_def ) );
        case ftByte     : return Variant( ReadByteNN( field_def ) );
        case ftShort    : return Variant( ReadShortNN( field_def ) );
        case ftInteger  : return Variant( ReadIntegerNN( field_def ) );
        case ftLongLong : return Variant( ReadLongLongNN( field_def ) );
        case ftDouble   : return Variant( ReadFloatNN( field_def ) );
        case ftDate     : return Variant( ReadDateNN( field_def ) );
        case ftTime     : return Variant( ReadTimeNN( field_def ) );
        case ftDateTime : return Variant( ReadDateTimeNN( field_def ) );
        case ftGUID     : return Variant( ReadGUIDNN( field_def ) );
        case ftString   : return Variant( ReadStringNN( field_def ) );
        //case ftWString  : return Variant( ReadWStringNN( field_def ) );
        //case ftBlob     : return Variant( ReadBlobNN( field_def ) );
        default         : throw eVariantConversion();
    }
}

void cRawBuffer::WriteVariant( const cFieldDef& field_def, const Variant& value )
{
    if ( value.IsNull() )
        Nullify( field_def );
    else switch ( field_def.DataType() )
    {
        case ftBool     : WriteBool( field_def, value.AsBool() );               break;
        case ftByte     : WriteByte( field_def, value.AsByte() );               break;
        case ftShort    : WriteShort( field_def, value.AsShort() );             break;
        case ftInteger  : WriteInteger( field_def, value.AsInt() );             break;
        case ftLongLong : WriteLongLong( field_def, value.AsLongLong() );       break;
        case ftDouble   : WriteFloat( field_def, value.AsDouble() );            break;
        case ftDate     : WriteDate( field_def, value.AsDate() );               break;
        case ftTime     : WriteTime( field_def, value.AsTime() );               break;
        case ftDateTime : WriteDateTime( field_def, value.AsDateTime() );       break;
        case ftGUID     : WriteGUID( field_def, value.AsGUID() );               break;
        case ftString   : WriteString( field_def, value.AsString() );           break;
        //case ftWString  : WriteString( *mFieldDef, value.AsWString() );        break;
        //case ftBlog     : WriteString( *mFieldDef, value.AsWString() );        break;
        default         : throw eVariantConversion();
    }
}

ds_string& cRawBuffer::empty_string()
{
    static  ds_string   empty;

    return empty;
}

//***********************************************************************
//******    DoubleBuffer
//***********************************************************************
DoubleBuffer::DoubleBuffer( cFieldDefs *field_defs, bool unmodified )
    : mOriginalData( field_defs, unmodified ),
      mModifiedData( field_defs, ! unmodified ),
      mUpdateStatus( unmodified ? usUnmodified : usInserted ), mFieldDefs(field_defs)
{
}

DoubleBuffer::~DoubleBuffer()
{
}

void DoubleBuffer::CommitUpdates()
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
Data::Data( IDataNotify *i_notify )
    : mData(), mFieldDefs( new cFieldDefs() ), mDeleted( new container ),
      mLockCount( new int(0) ), mRelatedData(this), mTableNotify(i_notify)
{
}

Data::Data( const cFieldDefs_& field_defs, IDataNotify *i_notify )
    : mData(), mFieldDefs( new cFieldDefs( field_defs ) ), mDeleted( new container ),
      mLockCount( new int(0) ), mRelatedData(this), mTableNotify(i_notify)
{
}

Data::Data( const spFieldDefs& field_defs, const deleted_container& deleted,
                       lock_counter lock_count, IDataNotify *i_notify )
    : mData(), mFieldDefs( field_defs ), mDeleted(deleted),
      mLockCount(lock_count), mRelatedData(this), mTableNotify(i_notify)
{
}

#else
Data::Data()
    : mData(), mFieldDefs( new cFieldDefs() ), mDeleted( new container )
{
}

Data::Data( const cFieldDefs_& field_defs )
    : mData(), mFieldDefs( new cFieldDefs( field_defs ) ), mDeleted( new container )
{
}

Data::Data( const spFieldDefs& field_defs, const deleted_container& deleted )
    : mData(), mFieldDefs( field_defs ), mDeleted(deleted)
{
}
#endif

Data::~Data()
{
#if defined(SM_DS_ENABLE_NOTIFY)
    RemoveRelation( this );
#endif
}

#if defined(SM_DS_ENABLE_NOTIFY)
void Data::NotifyRecordAdded( const value_type& value )
{
    Data    *relation = mRelatedData;
    bool    lock = *mLockCount != 0;

    while ( relation != this )
    {
        mRelatedData->mTableNotify->RecordAdded( value, lock );
        relation = relation->mRelatedData;
    }
}

void Data::NotifyRecordDeleted( const value_type& value )
{
    Data    *relation = mRelatedData;

    while ( relation != this )
    {
        relation->mTableNotify->RecordDeleted( value );
        relation = relation->mRelatedData;
    }
}

void Data::NotifyOpened()
{
    std::vector<IDataNotify *>  notifies;

    GetNotifies( notifies );
    for ( std::vector<IDataNotify *>::iterator it = notifies.begin(), eend = notifies.end() ; it != eend ; ++it )
        (*it)->DataOpened( *this );
}

void Data::NotifyClosed()
{
    std::vector<IDataNotify *>  notifies;

    GetNotifies( notifies );
    for ( std::vector<IDataNotify *>::iterator it = notifies.begin(), eend = notifies.end() ; it != eend ; ++it )
        (*it)->DataClosed();
}

void Data::NotifyUpdateLockReleased()
{
    Data    *relation = mRelatedData;

    while ( relation != this )
    {
        relation->mTableNotify->UpdateLockReleased();
        relation = relation->mRelatedData;
    }
}

void Data::GetNotifies( std::vector<IDataNotify *>& notifies )
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
void Data::LockUpdates()
{
    ++(*mLockCount);
}

void Data::UnlockUpdates()
{
    int     *count = mLockCount.get();

    if ( *count )
        if ( --(*count) == 0 )
            NotifyUpdateLockReleased();
}
#endif

void Data::Clear()
{
    mData = container();
}

void Data::CommitUpdates()
{
    for ( iterator n = mData.begin(), eend = mData.end() ; n != eend ; ++n )
        (*n)->CommitUpdates();
}

// returns a ref counted double buffer, in usUnmodified state, **not** inserted in the container
Data::value_type Data::NewBuffer_usUnmodified()
{
    return Data::value_type( new DoubleBuffer( mFieldDefs.get(), true ) );
}

// returns a ref counted double buffer, in usInserted state, **not** inserted in the container
Data::value_type Data::NewBuffer_usInserted()
{
    return Data::value_type( new DoubleBuffer( mFieldDefs.get(), false ) );
}

int Data::AddBuffer_ptr( const value_type& value )
{
    mData.push_back( value );
    return ( size() - 1 );
}

int Data::AddBuffer( const value_type& value )
{
    mData.push_back( value );
#if defined(SM_DS_ENABLE_NOTIFY)
    NotifyRecordAdded( value );
#endif
    return ( size() - 1 );
}

// assume a sorted container and insert it in the right position
void Data::InsertBuffer_ptr( const value_type& value, spSortCompare& compare )
{
    SortControler       cc = SortControler( compare );
    Data::iterator      rslt = std::lower_bound( mData.begin(), mData.end(), value, cc );

    mData.insert( rslt, value );
}

void Data::DeleteBuffer_ptr( const value_type& value )
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

void Data::Delete( int idx )
{
    iterator        tmp( mData.begin() + idx );

    if ( (*tmp)->GetUpdateStatus() != usInserted )
        mDeleted->push_back( *tmp );
#if defined(SM_DS_ENABLE_NOTIFY)
    NotifyRecordDeleted( *tmp );
#endif
    mData.erase( tmp );
}

void Data::AddField( const std_string& name, cFieldKind kind, cFieldDataType data_type, unsigned int size )
{
    mFieldDefs->AddField( name, kind, data_type, size );
}

#if defined(SM_DS_ENABLE_NOTIFY)
spData Data::Clone_All( IDataNotify *i_notify )
#else
spData Data::Clone_All()
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

void Data::Sort( const SortControler& cmp )
{
    std::sort( mData.begin(), mData.end(), cmp );
}

void Data::Locate( const OpenValues& values, const OpenFindFields& fields,
                             iterator begin, iterator end, locate_result& result )
{
    Data::value_type    tmp_rec = NewBuffer_usInserted();
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

void Data::Locate( const OpenValues& values, const OpenFindFields& fields, locate_result& result )
{
    Locate( values, fields, mData.begin(), mData.end(), result );
}

void Data::Locate( const OpenValues& values, const OpenFindFields& fields,
                             size_type start, size_type end, locate_result& result )
{
    Locate( values, fields, mData.begin() + start, mData.begin() + end, result );
}

void Data::Find_0( const Data::value_type& double_buffer, spSortCompare& compare,
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

void Data::Find( const OpenValues& values, spSortCompare& compare,
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

void Data::Find( const OpenValues& values, spSortCompare& compare, locate_result& result )
{
    Find( values, compare, mData.begin(), mData.end(), result );
}

void Data::Find( const OpenValues& values, spSortCompare& compare,
                           size_type start, size_type end, locate_result& result )
{
    Find( values, compare, mData.begin() + start, mData.begin() + end, result );
}

void Data::GetRange( const OpenRangeValues& values, spSortCompare& compare, range_result& result )
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

