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

#include "dsData.h"
#include "dsExceptions.h"
#include "dsIndex.h"
#include "dsCompareControlers.h"
#include <sstream>
#include <stdexcept>
#include "dsString.h"

namespace smds
{

//***********************************************************************
//******    Tablebase
//***********************************************************************
#if defined(SM_DS_ENABLE_NOTIFY)
CDFASTCALL Tablebase::Tablebase()
    : mData( new detail::Data( this ) )
{
}

CDFASTCALL Tablebase::Tablebase( const detail::cFieldDefs_& field_defs )
    : mData( new detail::Data( field_defs, this ) )
{
}
#else
CDFASTCALL Tablebase::Tablebase()
    : mData( new detail::Data() )
{
}

CDFASTCALL Tablebase::Tablebase( const detail::cFieldDefs_& field_defs )
    : mData( new detail::Data( field_defs ) )
{
}
#endif
/*
CDFASTCALL Tablebase::Tablebase( const Tablebase& src )
{
}

Tablebase& FASTCALL Tablebase::operator=( const Tablebase& src )
{
}
*/

CDFASTCALL Tablebase::~Tablebase()
{
}

cRecord FASTCALL Tablebase::NewRecord()
{
    return ( cRecord( mData->NewBuffer_usInserted(), mData->GetFieldDefs() ) );
}

Tablebase::iterator FASTCALL Tablebase::AddRecord( const cRecord& record )
{
    return ( iterator( mData, AddBuffer( record ) ) );
}

detail::Data::locate_result::second_type FASTCALL Tablebase::LocateImpl( const OpenValues& values, const OpenFindFields& fields )
{
    detail::Data::locate_result    result;

    mData->Locate( values, fields, result );
    return result.second;
}

Tablebase::iterator FASTCALL Tablebase::Locate( const OpenValues& values, const OpenFindFields& fields )
{
    return iterator( mData, LocateImpl( values, fields ) );
}

Tablebase::iterator FASTCALL Tablebase::Locate( const Variant& value, const cFindField& field )
{
    return Locate( OpenValues( value ), OpenFindFields( field ) );
}

#if defined(SM_DS_ENABLE_NOTIFY)
void FASTCALL Tablebase::RecordAdded( const detail::Data::value_type& value, bool )
{
    mData->AddBuffer_ptr( value );
}

void FASTCALL Tablebase::RecordDeleted( const detail::Data::value_type& value )
{
    mData->DeleteBuffer_ptr( value );
}

void FASTCALL Tablebase::DataOpened( detail::Data& )
{
    // do nothing. Normally we will never come here as "Open" and "Close" can
    // be done only from "Table"
}

void FASTCALL Tablebase::DataClosed()
{
    // do nothing. Normally we will never come here as "Open" and "Close" can
    // be done only from "Table"
}

void FASTCALL Tablebase::UpdateLockReleased()
{
}
#endif

//***********************************************************************
//******    Table
//***********************************************************************
CDFASTCALL Table::Table( const detail::cFieldDefs_& field_defs )
    : Tablebase( field_defs ), mSql(field_defs.mSql), mTableName(field_defs.mTableName)
{
}

CDFASTCALL Table::Table()
    : Tablebase(), mSql(), mTableName()
{
}

CDFASTCALL Table::Table( const ds_string& table_name )
    : Tablebase(), mSql(), mTableName(table_name)
{
}

CDFASTCALL Table::Table( const char * table_name )
    : Tablebase(), mSql(), mTableName(table_name)
{
}

CDFASTCALL Table::~Table()
{
}

ds_string FASTCALL Table::ConstructSelectFromFields( const char *where_clause )
{
    std::ostringstream      qstr;
    const spFieldDefs&      field_defs = GetData()->GetFieldDefs();
    bool                    first_field = true;

    qstr << "SELECT ";
    for ( cFieldDefs::const_iterator n = field_defs->begin(), eend = field_defs->end() ; n != eend ; ++n )
    {
        if ( n->Kind() == fkData )
        {
            if ( ! first_field )
                qstr << ", ";
            else
                first_field = false;
            qstr << n->Name().c_str();
        }
    }
    qstr << " FROM " << mTableName.c_str();
    if ( where_clause )
        qstr << " WHERE " << where_clause;

    return ( ds_string( qstr.str().c_str() ) );
}

ds_string FASTCALL Table::ConstructSelectFromSql( const char *where_clause )
{
    std::ostringstream      qstr;

    // qstr << "SELECT " << mSql.c_str() << " FROM " << mTableName.c_str();
    qstr << mSql.c_str();
    if ( where_clause )
        qstr << " WHERE " << where_clause;
    return ( ds_string( qstr.str().c_str() ) );
}

ds_string FASTCALL Table::ConstructSelect( const char *where_clause )
{
    if ( mSql.empty() )
        return ( ConstructSelectFromFields( where_clause ) );
    else
        return ( ConstructSelectFromSql( where_clause ) );
}

detail::Data::value_type FASTCALL Table::NewBuffer_usUnmodified()
{
    return ( GetData()->NewBuffer_usUnmodified() );
}

detail::Data::value_type FASTCALL Table::NewBuffer_usInserted()
{
    return ( GetData()->NewBuffer_usInserted() );
}

spFieldSortCompare FASTCALL Table::CreateCmp( const cIndexField& index_field )
{
    return spFieldSortCompare( new FieldSortCompare( index_field ) );
}

spFieldSortCompare FASTCALL Table::CreateCmp( const OpenIndexFields& index_fields )
{
    return spFieldSortCompare( new FieldSortCompare( index_fields ) );
}

cIndex_ptr FASTCALL Table::NewIndex( const cIndexField& index_field )
{
    return cIndex_ptr( new Index( GetData(), CreateCmp( index_field ) ) );
}

cIndex_ptr FASTCALL Table::NewIndex( const OpenIndexFields& index_fields )
{
    return cIndex_ptr( new Index( GetData(), CreateCmp( index_fields ) ) );
}

cIndex_ptr FASTCALL Table::NewIndex( const spFieldSortCompare& cmp_func )
{
    return cIndex_ptr( new Index( GetData(), cmp_func ) );
}

void FASTCALL Table::AddField( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned int size )
{
    GetData()->AddField( name, kind, data_type, size );
}

void FASTCALL Table::AddField( const char *name, cFieldKind kind, cFieldDataType data_type, unsigned int size )
{
    AddField( ds_string( name ), kind, data_type, size );
}

namespace
{

class cFieldValuesAcceptor : public IFieldValuesAcceptor
{
private:
    detail::cRawBuffer&                 mRawBuffer;
    std::vector<const cFieldDef *>&     mLocalMap;
    // non copyable
    CDFASTCALL cFieldValuesAcceptor( const cFieldValuesAcceptor& src );
    cFieldValuesAcceptor& FASTCALL operator = ( const cFieldValuesAcceptor& src );
public:
    CDFASTCALL cFieldValuesAcceptor( detail::cRawBuffer& raw_buffer, std::vector<const cFieldDef *>& local_map )
        : mRawBuffer(raw_buffer), mLocalMap(local_map)
    {
    }
    virtual ~cFieldValuesAcceptor()
    {
    }
#if defined ( SM_USE_COM_DELPHI_INTERFACE )
    // IUnknown
    virtual HRESULT STDCALL QueryInterface( REFIID /*riid*/, void ** /*ppvObject*/ )  { return E_NOINTERFACE; }
    virtual ULONG STDCALL AddRef()                                                    { return 0xFFFFFFFFU; }
    virtual ULONG STDCALL Release()                                                   { return 0xFFFFFFFFU; }
#endif
    // IFieldValuesAcceptor
    virtual bool STDCALL FieldValue( int field_idx, void *buff, unsigned int field_data_size )
    {
        const cFieldDef     *field_def = mLocalMap[field_idx];

        if ( field_def == 0 )
            return true;

        if ( buff == 0 )
            mRawBuffer.Nullify( *field_def );
        else switch ( field_def->DataType() )
        {
            case cFieldDataType_ftBool     :
            {
                bool    value = *reinterpret_cast<char *>(buff) != 0;

                mRawBuffer.WriteBool( *field_def, value );
                break;
            }
            case cFieldDataType_ftByte     :
                mRawBuffer.WriteByte( *field_def, *reinterpret_cast<char *>(buff) );
                break;
            case cFieldDataType_ftShort    :
                mRawBuffer.WriteShort( *field_def, *reinterpret_cast<short *>(buff) );
                break;
            case cFieldDataType_ftInteger  :
                mRawBuffer.WriteInteger( *field_def, *reinterpret_cast<int *>(buff) );
                break;
            case cFieldDataType_ftLongLong     :
                mRawBuffer.WriteLongLong( *field_def, *reinterpret_cast<long long *>(buff) );
                break;
            case cFieldDataType_ftDouble   :
                mRawBuffer.WriteFloat( *field_def, *reinterpret_cast<double *>(buff) );
                break;
/////////////////////////////////////////////////////////////////
            // all of the folowing need fixing
            case cFieldDataType_ftDate :
                mRawBuffer.WriteDate( *field_def, LongEncodeDate( *reinterpret_cast<DATE_STRUCT *>(buff) ) );
                break;
            case cFieldDataType_ftTime :
                mRawBuffer.WriteTime( *field_def, LongEncodeTime( *reinterpret_cast<TIME_STRUCT *>(buff) ) );
                break;
            case cFieldDataType_ftDateTime :
                mRawBuffer.WriteDateTime( *field_def, LongEncodeDateTime( *reinterpret_cast<TIMESTAMP_STRUCT *>(buff) ) );
                break;
            case cFieldDataType_ftGUID     :
                mRawBuffer.WriteGUID( *field_def, *reinterpret_cast<SQLGUID *>(buff) );
                break;
            case cFieldDataType_ftString   :
                mRawBuffer.WriteString( *field_def, reinterpret_cast<char *>(buff) );
                break;
            case cFieldDataType_ftWString  :
                // mRawBuffer.WriteWString( field_def, reinterpret_cast<wchar_t *>(buff) );
                break;
            case cFieldDataType_ftBlob     :
                // mRawBuffer.WriteBlob( field_def, reinterpret_cast<wchar_t *>(buff) );
                break;
/////////////////////////////////////////////////////////////////
            default                        : return false;
        }
        return true;
    }
};

struct DriverField
{
    int             idx;
    std::string     name;
    unsigned long   data_size;
    int             data_type;
    unsigned short  scale;
};

}; // namespace

void FASTCALL Table::Open( const Database& database, const char *where_clause )
{
    ds_string   sql( ConstructSelect( where_clause ) );

    if ( sql[0] == 0 )
        return;

    DataTransfer    transfer = database.NewTransfer();
    IDataProvider   *provider = transfer.GetDataTransfer();

    provider->OpenSql( sql.c_str() );

    const spFieldDefs               sp_field_defs = GetData()->GetFieldDefs();
    bool                            have_fields = sp_field_defs->Count() != 0;
    int                             provider_field_count = provider->GetFieldCount();

    unsigned int                    name_buffer_length = 100;
    boost::scoped_array<char>       name_buffer( new char[name_buffer_length] );
    std::size_t                     name_buffer_required_length;
    unsigned int                    field_data_size;
    int                             field_data_type;
    const cFieldDef                 *ds_field;
    std::vector<const cFieldDef *>  local_map;

    for ( int n = 0 ; n < provider_field_count ; ++n )
    {
        provider->GetFieldAttributes( n, name_buffer.get(), name_buffer_length, name_buffer_required_length,
                                      field_data_size, field_data_type );
        if ( name_buffer_required_length > name_buffer_length )
        {
            name_buffer_length = name_buffer_required_length + name_buffer_required_length / 2;
            name_buffer.reset( new char[name_buffer_length] );
            provider->GetFieldAttributes( n, name_buffer.get(), name_buffer_length, name_buffer_required_length,
                                          field_data_size, field_data_type );
        }
        name_buffer[name_buffer_required_length - 1] = 0;
        if ( ! have_fields )
        {
            ds_field = &sp_field_defs->AddField( ds_string( name_buffer.get() ), fkData,
                                                 static_cast<cFieldDataType>(field_data_type), field_data_size );
        }
        else
        {
            ds_field = sp_field_defs->FindField( name_buffer.get() );

            if ( ds_field != 0 )
            {
                cFieldDataType      data_type = ds_field->DataType();

                if ( data_type != static_cast<cFieldDataType>(field_data_type) )
                    throw std::runtime_error( "Field type or size mismatch!!!!" );
                if ( data_type != ftDate && data_type != ftTime && data_type != ftDateTime && ds_field->DataSize() != field_data_size )
                    throw std::runtime_error( "Field type or size mismatch!!!!" );
            }
        }
        local_map.push_back( ds_field );
    }

    while ( ! provider->Eof() )
    {
        // insert a buffer
        detail::Data::value_type        rec = NewBuffer_usUnmodified();
        detail::cRawBuffer&             raw = rec->GetOriginalData();
        cFieldValuesAcceptor            acceptor( raw, local_map );

        if ( ! provider->GetFieldValues( &acceptor ) )
            break;

        GetData()->AddBuffer_ptr( rec );
        provider->Next();
    }
    provider->CloseSql();
#if defined(SM_DS_ENABLE_NOTIFY)
    GetData()->NotifyOpened();
#endif
}

void FASTCALL Table::Close()
{
#if defined(SM_DS_ENABLE_NOTIFY)
    GetData()->NotifyClosed();
    SetData( detail::spData( new detail::Data( this ) ) );
#else
    SetData( detail::spData( new detail::Data() ) );
#endif
}

//***********************************************************************
//******    cTableSerializingData
//***********************************************************************
const char  cTableSerializingData::PacketMagic[] = "DataPacket";
const int   cTableSerializingData::PacketVersion = 0;

//***********************************************************************
//******    cTableReader
//***********************************************************************
void FASTCALL cTableReader::ReadFieldValue( cStream& st, const detail::cRawBuffer& rb, const cFieldDef& field )
{
    if ( rb.IsNull( field ) )
        st << false;
    else
    {
        st << true;
        switch ( field.DataType() )
        {
            case ftBool     : st.WriteBuffer( rb.buffer_field_cast<bool *>(field.Offset()), sizeof(bool) );                         break;
            // case ftChar     : st.WriteBuffer( rb.buffer_field_cast<char *>(field.Offset()), sizeof(char) );                         break;
            // case ftWChar    : st.WriteBuffer( rb.buffer_field_cast<wchar_t *>(field.Offset()), sizeof(wchar_t) );                   break;
            case ftShort    : st.WriteBuffer( rb.buffer_field_cast<short *>(field.Offset()), sizeof(short) );                       break;
            case ftInteger  : st.WriteBuffer( rb.buffer_field_cast<int *>(field.Offset()), sizeof(int) );                           break;
            case ftLongLong : st.WriteBuffer( rb.buffer_field_cast<long long *>(field.Offset()), sizeof(long long) );               break;
            case ftDouble   : st.WriteBuffer( rb.buffer_field_cast<double *>(field.Offset()), sizeof(double) );                     break;
            case ftDateTime : st.WriteBuffer( rb.buffer_field_cast<detail::dbDateTime_Internal *>(field.Offset()), sizeof(detail::dbDateTime_Internal) ); break;
            case ftString   :
            {
                const ds_string&    str( **rb.string_ptr_ptr( field.Offset() ) );

                st << str;
                // st.WriteBuffer( str.c_str(), std::min<ds_string::size_type>( str.size(), field.DataSize_() ) );
                break;
            }
            //case ftWString  : st.WriteBuffer( rb.buffer_field_cast<char *>(field.Offset()), static_cast<unsigned short>(size * sizeof(wchar_t));                break;
            //case ftBlob     : st.WriteBuffer( rb.buffer_field_cast<char *>(field.Offset()), sizeof(shared_ptr< std::vector<char> >);                break;
            default         : throw eUnknownFieldType();
        }
    }
}

Variant FASTCALL cTableReader::GetTablePacket( Table& table )
{
    Variant         result( Variant::VarBlobCreate() );
    cVariantStream  st( result );

    st << PacketMagic << PacketVersion;

    spFieldDefs     field_defs( table.GetFieldDefs() );

    st << field_defs->Count();
    for ( cFieldDefs::iterator n = field_defs->begin(), eend = field_defs->end() ; n != eend ; ++n )
        st << n->Index() << n->Offset() << n->Name() << n->Kind() << n->DataType() << n->DataSize();

    record_iterator     rec = table.GetIterator();

    st << table.RecordCount();
    st.SetSize( st.GetSize() + table.RecordCount() * field_defs->BufferSize() );
    while ( ! rec.eof() )
    {
        cUpdateStatus   update_status = rec.GetUpdateStatus();

        st << update_status;
        if ( update_status == usUnmodified || update_status == usModified || update_status == usDeleted )
            for ( cFieldDefs::iterator n = field_defs->begin(), eend = field_defs->end() ; n != eend ; ++n )
                ReadFieldValue( st, rec.GetDoubleBuffer()->GetOriginalData(), *n );
        if ( update_status == usModified || update_status == usInserted )
            for ( cFieldDefs::iterator n = field_defs->begin(), eend = field_defs->end() ; n != eend ; ++n )
                ReadFieldValue( st, rec.GetDoubleBuffer()->GetActiveData(), *n );
        ++rec;
    }
    st.SetSize( st.GetPosition() );

    return ( result );
}

//***********************************************************************
//******    cTableWriter
//***********************************************************************
void FASTCALL cTableWriter::CheckMagic( cStream& st )
{
    ds_string   magic;

    st >> magic;
}

void FASTCALL cTableWriter::CheckVersion( cStream& st )
{
    int     version;

    st >> version;
}

void FASTCALL cTableWriter::Check( cStream& st )
{
    CheckMagic( st );
    CheckVersion( st );
}

void FASTCALL cTableWriter::ReadFieldDefs( cStream& st, Table& table, bool is_typed )
{
    Check( st );

    int             field_count, field_count_start = 0;
    cFieldDef       field_def;

    st >> field_count;
    if ( is_typed )
    {
        int                         n;
        cFieldDefs::const_iterator  field_def_start = table.GetFieldDefs()->begin();
        cFieldDefs::const_iterator  field_def_end = table.GetFieldDefs()->end();

        field_count_start = table.GetFieldDefs()->Count();

        for ( n = 0 ; n < field_count_start && field_def_start != field_def_end ; ++n, ++field_def_start )
        {
            st >> field_def;
            if ( field_def != *field_def_start )
                throw ePacketError();
        }
        if ( n != field_count_start )
            throw ePacketError();
    }
    for ( int n = field_count_start ; n < field_count ; ++n )
    {
        st >> field_def;
        table.AddField( field_def.Name(), field_def.Kind(), field_def.DataType(), field_def.DataSize() );
    }
}

spTable FASTCALL cTableWriter::CreateTemporaryTable()
{
    return spTable( new Table( "__TMP__" ) );
}

void FASTCALL cTableWriter::ReadFieldValue( cStream& st, detail::cRawBuffer& rb, const cFieldDef& field )
{
    bool    not_null;

    st >> not_null;
    if ( not_null )
    {
        switch ( field.DataType() )
        {
            case ftBool     :
            {
                bool    v;

                st >> v;
                rb.WriteBool( field, v );
                break;
            }
            case ftByte     :
            {
                char    v;

                st >> v;
                rb.WriteByte( field, v );
                break;
            }
/*
            case ftWChar    :
            {
                wchar_t     v;

                st >> v;
                rb.WriteWChar( field, v );
                break;
            }
*/
            case ftShort    :
            {
                short   v;

                st >> v;
                rb.WriteShort( field, v );
                break;
            }
            case ftInteger  :
            {
                int     v;

                st >> v;
                rb.WriteInteger( field, v );
                break;
            }
            case ftLongLong :
            {
                long long   v;

                st >> v;
                rb.WriteLongLong( field, v );
                break;
            }
            case ftDouble   :
            {
                double  v;

                st >> v;
                rb.WriteFloat( field, v );
                break;
            }
            case ftDateTime :
            {
                dbDateTime      v;

                st >> v;
                rb.WriteDateTime( field, v );
                break;
            }
            case ftString   :
            {
                ds_string   v;

                st >> v;
                rb.WriteString( field, v );
                break;
            }
            //case ftWString  : st.WriteBuffer( rb.buffer_field_cast<char *>(field.Offset()), static_cast<unsigned short>(size * sizeof(wchar_t));                break;
            //case ftBlob     : st.WriteBuffer( rb.buffer_field_cast<char *>(field.Offset()), sizeof(shared_ptr< std::vector<char> >);                break;
            default         : throw eUnknownFieldType();
        }
    }
}

void FASTCALL cTableWriter::ReadData( cStream& st, Table& tmp )
{
    spFieldDefs         field_defs( tmp.GetFieldDefs() );
    int                 record_count;

    st >> record_count;
    for ( int n = 0 ; n < record_count ; ++n )
    {
        cUpdateStatus   update_status;

        st >> update_status;

        cRecord         new_rec = tmp.NewRecord();

        if ( update_status == usUnmodified || update_status == usModified || update_status == usDeleted )
        {
            for ( cFieldDefs::iterator n = field_defs->begin(), eend = field_defs->end() ; n != eend ; ++n )
                ReadFieldValue( st, new_rec.GetDoubleBuffer()->GetActiveData(), *n );
            new_rec.CommitUpdates();
        }
        if ( update_status == usModified || update_status == usInserted )
            for ( cFieldDefs::iterator n = field_defs->begin(), eend = field_defs->end() ; n != eend ; ++n )
                ReadFieldValue( st, new_rec.GetDoubleBuffer()->GetActiveData(), *n );
        tmp.AddRecord( new_rec );
    }
}

void FASTCALL cTableWriter::ReadDataAssign( cStream& st, Table& tmp, Table& table )
{
    ReadData( st, tmp );
    table.SetData( tmp.GetData() );
}

//void FASTCALL cTableWriter::CheckFieldDefsEqual( Table& tmp, Table& table )
//{
//    if ( ! tmp.GetFieldDefs()->equal( *table.GetFieldDefs() ) )
//        throw ePacketError();
//}

void FASTCALL cTableWriter::ReadTheRest( Table& tmp, Table& table, Variant& variant, bool is_typed )
{
    cVariantStream  st( variant );

    ReadFieldDefs( st, tmp, is_typed );
    ReadDataAssign( st, tmp, table );
}

void FASTCALL cTableWriter::SetTableData( Table& table, Variant& variant )
{
    spTable     tmp = CreateTemporaryTable();

    ReadTheRest( *tmp, table, variant, false );
}

}; // namespace smds

