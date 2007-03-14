#pragma hdrstop

#include <dsData.h>
#include "dsExceptions.h"
#include "dsCompareControlers.h"
#include <sstream>

namespace ds
{
//***********************************************************************
//******    cTablebase
//***********************************************************************
CDFASTCALL cTablebase::cTablebase()
    : mData( new cData() )
{
}

CDFASTCALL cTablebase::cTablebase( const cFieldDefs_& field_defs )
    : mData( new cData( field_defs ) )
{
}

CDFASTCALL cTablebase::~cTablebase()
{
}

cRecord FASTCALL cTablebase::NewRecord()
{
    return ( cRecord( mData->NewBuffer_usInserted(), mData->GetFieldDefs() ) );
}

cRecordIterator FASTCALL cTablebase::AddRecord( const cRecord& record )
{
    return ( iterator( mData, AddBuffer_ptr( record ) ) );
}

cTablebase::iterator FASTCALL cTablebase::Locate( const OpenValues& values, const OpenFindFields& fields )
{
    cData::locate_result    result;

    mData->Locate( values, fields, result );
    return ( iterator( mData, result.second ) );
}

cTablebase::iterator FASTCALL cTablebase::Locate( const Variant& value, const cFindField& field )
{
    return ( Locate( ds::OpenValues( value ), ds::OpenFindFields( field ) ) );
}

bool FASTCALL cTablebase::Locate( const Variant& value, const cFindField& field, iterator& iter )
{
    return ( Locate( ds::OpenValues( value ), ds::OpenFindFields( field ), iter ) );
}

bool FASTCALL cTablebase::Locate( const OpenValues& values, const OpenFindFields& fields, iterator& iter )
{
#ifdef SM_DS_DEBUG
    if ( mData != iter.mContainer )
        throw eDebug( "Error in Locate" );
#endif
    cData::locate_result    result;

    iter.mContainer->Locate( values, fields, result );
    if ( result.first )
        iter.mIdx = result.second;
    return ( result.first );
}

bool FASTCALL cTablebase::Locate( const Variant& value, const cFindField& field, range_iterator& iter )
{
    return ( Locate( ds::OpenValues( value ), ds::OpenFindFields( field ), iter ) );
}

bool FASTCALL cTablebase::Locate( const OpenValues& values, const OpenFindFields& fields, range_iterator& iter )
{
#ifdef SM_DS_DEBUG
    if ( mData != iter.mContainer )
        throw eDebug( "Error in Locate" );
#endif
    cData::locate_result    result;

    iter.mContainer->Locate( values, fields, iter.mStart, iter.mEnd, result );
    if ( result.first )
        iter.mIdx = result.second;
    return ( result.first );
}

//***********************************************************************
//******    cTable
//***********************************************************************
CDFASTCALL cTable::cTable( const cFieldDefs_& field_defs )
    : cTablebase( field_defs ), mSql(field_defs.mSql), mTableName(field_defs.mTableName)
{
}

CDFASTCALL cTable::cTable()
    : cTablebase(), mSql(), mTableName()
{
}

CDFASTCALL cTable::cTable( const ds_string& table_name )
    : cTablebase(), mSql(), mTableName(table_name)
{
}

CDFASTCALL cTable::cTable( const char * table_name )
    : cTablebase(), mSql(), mTableName(table_name)
{
}

CDFASTCALL cTable::~cTable()
{
}

ds_string FASTCALL cTable::ConstructSelectFromFields( const char *where_clause )
{
    std::ostringstream      qstr;
    const cFieldDefs_ptr&   field_defs = GetData()->GetFieldDefs();
    bool                    first_field = true;

    qstr << "SELECT ";
    for ( cFieldDefs::const_iterator n = field_defs->begin(), eend = field_defs->end() ; n != eend ; ++n )
    {
        if ( n->Kind() == ds::fkData )
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

ds_string FASTCALL cTable::ConstructSelectFromSql( const char *where_clause )
{
    std::ostringstream      qstr;

    // qstr << "SELECT " << mSql.c_str() << " FROM " << mTableName.c_str();
    qstr << mSql.c_str();
    if ( where_clause )
        qstr << " WHERE " << where_clause;
    return ( ds_string( qstr.str().c_str() ) );
}

ds_string FASTCALL cTable::ConstructSelect( const char *where_clause )
{
    if ( mSql.empty() )
        return ( ConstructSelectFromFields( where_clause ) );
    else
        return ( ConstructSelectFromSql( where_clause ) );
}

cData::value_type FASTCALL cTable::NewBuffer_usUnmodified()
{
    return ( GetData()->NewBuffer_usUnmodified() );
}

cData::value_type FASTCALL cTable::NewBuffer_usInserted()
{
    return ( GetData()->NewBuffer_usInserted() );
}

cIndex * FASTCALL cTable::ConstructIndex( cIndex *index, const cSortCompareBase_ptr& cmp_func )
{
    std::auto_ptr<cIndex>   idx( index );

    index->Construct( cmp_func, GetData() );
    return ( idx.release() );
}

cIndex * FASTCALL cTable::ConstructIndex( cIndex *index, const cIndexField& index_field )
{
    std::auto_ptr<cIndex>   idx( index );

    index->Construct( ds::cIndexSortCompareStd_ptr( new ds::cIndexSortCompareStd( index_field ) ), GetData() );
    return ( idx.release() );
}

cIndex * FASTCALL cTable::ConstructIndex( cIndex *index, const OpenIndexFields& index_fields )
{
    std::auto_ptr<cIndex>   idx( index );

    index->Construct( ds::cIndexSortCompareStd_ptr( new ds::cIndexSortCompareStd( index_fields ) ), GetData() );
    return ( idx.release() );
}

cIndex_ptr FASTCALL cTable::NewIndex( const cIndexField& index_field )
{
    return ( cIndex_ptr( ConstructIndex( new cIndex(), index_field ) ) );
}

cIndex_ptr FASTCALL cTable::NewIndex( const OpenIndexFields& index_fields )
{
    return ( cIndex_ptr( ConstructIndex( new cIndex(), index_fields ) ) );
}

cIndex_ptr FASTCALL cTable::NewIndex( const cIndexSortCompareStd_ptr& cmp_func )
{
    return ( cIndex_ptr( ConstructIndex( new cIndex(), cmp_func ) ) );
}

void FASTCALL cTable::AddField( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned short size )
{
    GetData()->AddField( name, kind, data_type, size );
}

void FASTCALL cTable::AddField( const char *name, cFieldKind kind, cFieldDataType data_type, unsigned short size )
{
    AddField( ds_string( name ), kind, data_type, size );
}

class cFieldValuesAcceptor : public IFieldValuesAcceptor
{
private:
    cRawBuffer&         mRawBuffer;
    const cFieldDefs&   mFieldDefs;
    // non copyable
    CDFASTCALL cFieldValuesAcceptor( const cFieldValuesAcceptor& src );
    cFieldValuesAcceptor& FASTCALL operator = ( const cFieldValuesAcceptor& src );
public:
    CDFASTCALL cFieldValuesAcceptor( cRawBuffer& raw_buffer, const cFieldDefs& field_defs )
        : mRawBuffer(raw_buffer), mFieldDefs(field_defs)
    {
    }
    virtual ~cFieldValuesAcceptor()
    {
    }
#if defined ( SM_USE_COM_DELPHI_INTERFACE )
    // IUnknown
    virtual HRESULT __stdcall QueryInterface( REFIID /*riid*/, void ** /*ppvObject*/ )  { return E_NOINTERFACE; }
    virtual ULONG __stdcall AddRef()                                                    { return 0xFFFFFFFFU; }
    virtual ULONG __stdcall Release()                                                   { return 0xFFFFFFFFU; }
#endif
    // IFieldValuesAcceptor
    virtual bool __stdcall FieldValue( const char *field_name, int field_data_type, const void *data, void *buff, int field_data_size )
    {
        const cFieldDef&    field_def = data == 0 ? mFieldDefs.FieldByName( field_name ) : *static_cast<const cFieldDef *>(data);

        if ( buff == 0 )
            mRawBuffer.Nullify( field_def );
        else switch ( field_data_type )
        {
            case cFieldDataType_ftBool     :
                mRawBuffer.WriteBool( field_def, *reinterpret_cast<bool *>(buff) );
                break;
            case cFieldDataType_ftChar     :
                mRawBuffer.WriteChar( field_def, *reinterpret_cast<char *>(buff) );
                break;
            case cFieldDataType_ftWChar    :
                mRawBuffer.WriteWChar( field_def, *reinterpret_cast<wchar_t *>(buff) );
                break;
            case cFieldDataType_ftShort    :
                mRawBuffer.WriteShort( field_def, *reinterpret_cast<short *>(buff) );
                break;
            case cFieldDataType_ftInteger  :
                mRawBuffer.WriteInteger( field_def, *reinterpret_cast<int *>(buff) );
                break;
            case cFieldDataType_ftLong     :
                mRawBuffer.WriteLong( field_def, *reinterpret_cast<long *>(buff) );
                break;
            case cFieldDataType_ftDouble   :
                mRawBuffer.WriteFloat( field_def, *reinterpret_cast<double *>(buff) );
                break;
            case cFieldDataType_ftDateTime :
                mRawBuffer.WriteDate( field_def, cDateTime( *reinterpret_cast<double *>(buff) ) );
                break;
            case cFieldDataType_ftString   :
                mRawBuffer.WriteString( field_def, reinterpret_cast<char *>(buff) );
                break;
            //case cFieldDataType_ftWString  :
            //    mRawBuffer.WriteWString( field_def, reinterpret_cast<wchar_t *>(buff) );
            //    break;
            //case cFieldDataType_ftBlob     :
            //    mRawBuffer.WriteBlob( field_def, reinterpret_cast<wchar_t *>(buff) );
            //    break;
            default                        : return ( false );
        }
        return ( true );
    }
};

void FASTCALL cTable::Open( const cDatabase& database, const char *where_clause )
{
    ds_string   sql( ConstructSelect( where_clause ) );

    if ( sql[0] == 0 )
        return;

    cDataTransfer   transfer = database.NewTransfer();
    IDataProvider   *provider = transfer.DataTransfer();

    provider->OpenSql( sql.c_str() );

    provider->InitDataTransfer();

    const cFieldDefs&   field_defs = *GetData()->GetFieldDefs().get();

    for ( cFieldDefs::const_iterator n = field_defs.begin(), eend = field_defs.end() ; n != eend ; ++n )
        if ( n->Kind() == fkData )
#ifdef SM_DS_STRING_AS_STRING
            provider->StepInitDataTransfer( n->Name().c_str(), n->DataSize_(), n->DataType(), &(*n) );
#else
            provider->StepInitDataTransfer( n->Name().c_str(), n->Size_(), n->DataType(), &(*n) );
#endif
    provider->EndInitDataTransfer();

    while ( ! provider->Eof() )
    {
        // insert a buffer
        cData::value_type       rec = NewBuffer_usUnmodified();
        cRawBuffer&             raw = rec->GetOriginalData();
        cFieldValuesAcceptor    acceptor( raw, field_defs );

        if ( ! provider->GetFieldValues( &acceptor ) )
            break;
        GetData()->AddBuffer_ptr( rec );
        provider->Next();
    }
    provider->EndDataTransfer();
    provider->CloseSql();
}

void FASTCALL cTable::Close()
{
    cData_ptr   tmp( new cData() );

    GetData() = tmp;
}

//***********************************************************************
//******    cIndex
//***********************************************************************
CDFASTCALL cIndex::cIndex()
    : cTablebase(), mCompare()
{
}

CDFASTCALL cIndex::~cIndex()
{
}

void FASTCALL cIndex::Construct( const cSortCompareBase_ptr& cmp_func, const cData_ptr& data )
{
    mCompare = cmp_func;
    SetData( data->Clone_All() );
    mCompare->Initialize( GetData()->GetFieldDefs() );
    GetData()->Sort( detail::SortControler( mCompare ) );
/*
    SetData( cData_ptr( new cData( data->GetFieldDefs() ) ) );
    mCompare = cmp_func;

    GetData()->CopyData( *data );
    mCompare->Initialize( GetData()->GetFieldDefs() );
    GetData()->Sort( detail::SortControler( mCompare ) );
*/
}

cIndex::iterator FASTCALL cIndex::Find( const OpenValues& values )
{
    cData::locate_result    result;

    GetData()->Find( values, mCompare, result );
    return ( iterator( GetData(), result.second ) );
}

cIndex::iterator FASTCALL cIndex::Find( const Variant& value )
{
    return( Find( ds::OpenValues( value ) ) );
}

bool FASTCALL cIndex::Find( const Variant& value, iterator& iter )
{
    return ( Find( OpenValues( value ), iter ) );
}

bool FASTCALL cIndex::Find( const OpenValues& values, iterator& iter )
{
#ifdef SM_DS_DEBUG
    if ( mData != iter.mContainer )
        throw eDebug( "Error in Find" );
#endif
    cData::locate_result    result;

    iter.mContainer->Find( values, mCompare, result );
    if ( result.first )
        iter.mIdx = result.second;
    return ( result.first );
}

bool FASTCALL cIndex::Find( const Variant& value, range_iterator& iter )
{
    return ( Find( OpenValues( value ), iter ) );
}

bool FASTCALL cIndex::Find( const OpenValues& values, range_iterator& iter )
{
#ifdef SM_DS_DEBUG
    if ( mData != iter.mContainer )
        throw eDebug( "Error in Find" );
#endif
    cData::locate_result    result;

    iter.mContainer->Find( values, mCompare, iter.mStart, iter.mEnd, result );
    if ( result.first )
        iter.mIdx = result.second;
    return ( result.first );
}

cIndex::range_iterator FASTCALL cIndex::GetRangeIterator( const cRangeValues& values )
{
    return ( GetRangeIterator( OpenRangeValues( values ) ) );
}

cIndex::range_iterator FASTCALL cIndex::GetRangeIterator( const OpenRangeValues& values )
{
    cData::range_result     result;

    GetData()->GetRange( values, mCompare, result );
    return ( cRangeIterator( GetData(), result.second.first, result.second.second ) );
}

//***********************************************************************
//******    cTableSerializingData
//***********************************************************************
const char  cTableSerializingData::PacketMagic[] = "DataPacket";
const int   cTableSerializingData::PacketVersion = 0;

//***********************************************************************
//******    cTableReader
//***********************************************************************
void FASTCALL cTableReader::ReadFieldValue( cStream& st, const cRawBuffer& rb, const cFieldDef& field )
{
    if ( rb.IsNull( field ) )
        st << false;
    else
    {
        st << true;
        switch ( field.DataType() )
        {
            case ftBool     : st.WriteBuffer( rb.buffer_field_cast<bool *>(field.Offset()), sizeof(bool) );             break;
            case ftChar     : st.WriteBuffer( rb.buffer_field_cast<char *>(field.Offset()), sizeof(char) );             break;
            case ftWChar    : st.WriteBuffer( rb.buffer_field_cast<wchar_t *>(field.Offset()), sizeof(wchar_t) );       break;
            case ftShort    : st.WriteBuffer( rb.buffer_field_cast<short *>(field.Offset()), sizeof(short) );           break;
            case ftInteger  : st.WriteBuffer( rb.buffer_field_cast<int *>(field.Offset()), sizeof(int) );               break;
            case ftLong     : st.WriteBuffer( rb.buffer_field_cast<long *>(field.Offset()), sizeof(long) );             break;
            case ftDouble   : st.WriteBuffer( rb.buffer_field_cast<double *>(field.Offset()), sizeof(double) );         break;
            case ftDateTime : st.WriteBuffer( rb.buffer_field_cast<cDateTime *>(field.Offset()), sizeof(cDateTime) );   break;
#ifdef SM_DS_STRING_AS_STRING
            case ftString   :
            {
                const ds_string&    str( *(rb.buffer_field_cast<ds_string *>(field.Offset())) );

                st << str;
                // st.WriteBuffer( str.c_str(), std::min<ds_string::size_type>( str.size(), field.DataSize_() ) );
                break;
            }
#else
            case ftString   :
            {
                const char  *str = rb.buffer_field_cast<char *>(field.Offset());

                st << str;
                //st.WriteBuffer( str, rb.BufferStringLen( str, field.Size_() ) );
                break;
            }
#endif
            //case ftWString  : st.WriteBuffer( rb.buffer_field_cast<char *>(field.Offset()), static_cast<unsigned short>(size * sizeof(wchar_t));                break;
            //case ftBlob     : st.WriteBuffer( rb.buffer_field_cast<char *>(field.Offset()), sizeof(shared_ptr< std::vector<char> >);                break;
            default         : throw eUnknownFieldType();
        }
    }
}

Variant FASTCALL cTableReader::GetTablePacket( cTable& table )
{
    Variant         result( Variant::VarBlobCreate() );
    cVariantStream  st( result );

    st << PacketMagic << PacketVersion;

    cFieldDefs_ptr  field_defs( table.GetFieldDefs() );

    st << field_defs->Count();
    for ( cFieldDefs::iterator n = field_defs->begin(), eend = field_defs->end() ; n != eend ; ++n )
        st << n->Index() << n->Offset() << n->Name() << n->Kind() << n->DataType()
#ifdef SM_DS_STRING_AS_STRING
           << n->DataSize_();
#else
           << n->Size_();
#endif

    cTablebase::iterator    rec = table.GetIterator();

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

void FASTCALL cTableWriter::ReadFieldDefs( cStream& st, cTable& table, bool is_typed )
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
        table.AddField( field_def.Name(), field_def.Kind(), field_def.DataType(),
#ifdef SM_DS_STRING_AS_STRING
                        field_def.DataSize_() );
#else
                        field_def.Size_() );
#endif
    }
}

cTable_ptr FASTCALL cTableWriter::CreateTemporaryTable()
{
    return ( cTable_ptr( new cTable( "__TMP__" ) ) );
}

void FASTCALL cTableWriter::ReadFieldValue( cStream& st, cRawBuffer& rb, const cFieldDef& field )
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
            case ftChar     :
            {
                char    v;

                st >> v;
                rb.WriteChar( field, v );
                break;
            }
            case ftWChar    :
            {
                wchar_t     v;

                st >> v;
                rb.WriteWChar( field, v );
                break;
            }
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
            case ftLong     :
            {
                long    v;

                st >> v;
                rb.WriteLong( field, v );
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
                cDateTime   v;

                st >> v;
                rb.WriteDate( field, v );
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

void FASTCALL cTableWriter::ReadData( cStream& st, cTable& tmp )
{
    cFieldDefs_ptr      field_defs( tmp.GetFieldDefs() );
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

void FASTCALL cTableWriter::ReadDataAssign( cStream& st, cTable& tmp, cTable& table )
{
    ReadData( st, tmp );
    table.SetData( tmp.GetData() );
}

//void FASTCALL cTableWriter::CheckFieldDefsEqual( cTable& tmp, cTable& table )
//{
//    if ( ! tmp.GetFieldDefs()->equal( *table.GetFieldDefs() ) )
//        throw ePacketError();
//}

void FASTCALL cTableWriter::ReadTheRest( cTable& tmp, cTable& table, Variant& variant, bool is_typed )
{
    cVariantStream  st( variant );

    ReadFieldDefs( st, tmp, is_typed );
    ReadDataAssign( st, tmp, table );
}

void FASTCALL cTableWriter::SetTableData( cTable& table, Variant& variant )
{
    cTable_ptr      tmp = CreateTemporaryTable();

    ReadTheRest( *tmp, table, variant, false );
}

};
