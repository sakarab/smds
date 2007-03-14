//---------------------------------------------------------------------------
#ifndef SM_DS_RECORD_H
#define SM_DS_RECORD_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include "dsBuffer.h"
#include "dsVariant.h"
//---------------------------------------------------------------------------
namespace ds
{

//***********************************************************************
//******    cRawRecordPtr
//***********************************************************************
class cRawRecordPtr
{
private:
    cRawBuffer  *mRawBuffer;
protected:
    cRawBuffer * FASTCALL GetRawBuffer() const                      { return ( mRawBuffer ); }  // nice access to descenants.

    void FASTCALL Nullify( const cFieldDef& field_def )             { mRawBuffer->Nullify( field_def ); }

    bool FASTCALL ReadBool( const cFieldDef& field_def ) const;
    char FASTCALL ReadChar( const cFieldDef& field_def ) const;
    wchar_t FASTCALL ReadWChar( const cFieldDef& field_def ) const;
    short FASTCALL ReadShort( const cFieldDef& field_def ) const;
    int FASTCALL ReadInteger( const cFieldDef& field_def ) const;
    long FASTCALL ReadLong( const cFieldDef& field_def ) const;
    double FASTCALL ReadFloat( const cFieldDef& field_def ) const;
    cDateTime FASTCALL ReadDate( const cFieldDef& field_def ) const;
    ds_string FASTCALL ReadString( const cFieldDef& field_def ) const;
    Variant FASTCALL ReadVariant( const cFieldDef& field_def ) const                    { return ( mRawBuffer->ReadVariant( field_def ) ); }

    void FASTCALL WriteBool( const cFieldDef& field_def, bool value );
    void FASTCALL WriteChar( const cFieldDef& field_def, char value );
    void FASTCALL WriteWChar( const cFieldDef& field_def, wchar_t value );
    void FASTCALL WriteShort( const cFieldDef& field_def, short value );
    void FASTCALL WriteInteger( const cFieldDef& field_def, int value );
    void FASTCALL WriteLong( const cFieldDef& field_def, long value );
    void FASTCALL WriteFloat( const cFieldDef& field_def, double value );
    void FASTCALL WriteDate( const cFieldDef& field_def, const cDateTime& value );
    void FASTCALL WriteString( const cFieldDef& field_def, const ds_string& value );
    void FASTCALL WriteString( const cFieldDef& field_def, const char *value );
    void FASTCALL WriteVariant( const cFieldDef& field_def, const Variant& value )      { mRawBuffer->WriteVariant( field_def, value ); }

    bool FASTCALL ReadBool( const cFieldDef_& field_def ) const;
    char FASTCALL ReadChar( const cFieldDef_& field_def ) const;
    wchar_t FASTCALL ReadWChar( const cFieldDef_& field_def ) const;
    short FASTCALL ReadShort( const cFieldDef_& field_def ) const;
    int FASTCALL ReadInteger( const cFieldDef_& field_def ) const;
    long FASTCALL ReadLong( const cFieldDef_& field_def ) const;
    double FASTCALL ReadFloat( const cFieldDef_& field_def ) const;
    cDateTime FASTCALL ReadDate( const cFieldDef_& field_def ) const;
    ds_string FASTCALL ReadString( const cFieldDef_& field_def ) const;

    void FASTCALL WriteBool( const cFieldDef_& field_def, bool value );
    void FASTCALL WriteChar( const cFieldDef_& field_def, char value );
    void FASTCALL WriteWChar( const cFieldDef_& field_def, wchar_t value );
    void FASTCALL WriteShort( const cFieldDef_& field_def, short value );
    void FASTCALL WriteInteger( const cFieldDef_& field_def, int value );
    void FASTCALL WriteLong( const cFieldDef_& field_def, long value );
    void FASTCALL WriteFloat( const cFieldDef_& field_def, double value );
    void FASTCALL WriteDate( const cFieldDef_& field_def, const cDateTime& value );
    void FASTCALL WriteString( const cFieldDef_& field_def, const ds_string& value );
    void FASTCALL WriteString( const cFieldDef_& field_def, const char *value );
public:
    CDFASTCALL cRawRecordPtr( cRawBuffer& raw_buffer )
        : mRawBuffer(&raw_buffer)
    {
    }
    cRawRecordPtr * FASTCALL operator->()                           { return ( this ); }
    const cRawRecordPtr * FASTCALL operator->() const               { return ( this ); }

    bool FASTCALL IsNull( const cFieldDef& field_def ) const        { return ( mRawBuffer->IsNull( field_def ) ); }
    bool FASTCALL IsNull( const cFieldDef_& field_def ) const       { return ( mRawBuffer->IsNull( field_def ) ); }
};

//***********************************************************************
//******    cRecordPtr
//***********************************************************************
class cRecordPtr
{
private:
    cDoubleBuffer       *mBuffer;
protected:
    bool FASTCALL IsNull( const cFieldDef& field_def ) const;
    bool FASTCALL IsNull( const cFieldDef_& field_def ) const;
    void FASTCALL Nullify( const cFieldDef& field_def );

    bool FASTCALL ReadBool( const cFieldDef& field_def ) const;
    char FASTCALL ReadChar( const cFieldDef& field_def ) const;
    wchar_t FASTCALL ReadWChar( const cFieldDef& field_def ) const;
    short FASTCALL ReadShort( const cFieldDef& field_def ) const;
    int FASTCALL ReadInteger( const cFieldDef& field_def ) const;
    long FASTCALL ReadLong( const cFieldDef& field_def ) const;
    double FASTCALL ReadFloat( const cFieldDef& field_def ) const;
    cDateTime FASTCALL ReadDate( const cFieldDef& field_def ) const;
    ds_string FASTCALL ReadString( const cFieldDef& field_def ) const;

    void FASTCALL WriteBool( const cFieldDef& field_def, bool value );
    void FASTCALL WriteChar( const cFieldDef& field_def, char value );
    void FASTCALL WriteWChar( const cFieldDef& field_def, wchar_t value );
    void FASTCALL WriteShort( const cFieldDef& field_def, short value );
    void FASTCALL WriteInteger( const cFieldDef& field_def, int value );
    void FASTCALL WriteLong( const cFieldDef& field_def, long value );
    void FASTCALL WriteFloat( const cFieldDef& field_def, double value );
    void FASTCALL WriteDate( const cFieldDef& field_def, const cDateTime& value );
    void FASTCALL WriteString( const cFieldDef& field_def, const ds_string& value );
    void FASTCALL WriteString( const cFieldDef& field_def, const char *value );

    bool FASTCALL ReadBool( const cFieldDef_& field_def ) const;
    char FASTCALL ReadChar( const cFieldDef_& field_def ) const;
    wchar_t FASTCALL ReadWChar( const cFieldDef_& field_def ) const;
    short FASTCALL ReadShort( const cFieldDef_& field_def ) const;
    int FASTCALL ReadInteger( const cFieldDef_& field_def ) const;
    long FASTCALL ReadLong( const cFieldDef_& field_def ) const;
    double FASTCALL ReadFloat( const cFieldDef_& field_def ) const;
    cDateTime FASTCALL ReadDate( const cFieldDef_& field_def ) const;
    ds_string FASTCALL ReadString( const cFieldDef_& field_def ) const;

    void FASTCALL WriteBool( const cFieldDef_& field_def, bool value );
    void FASTCALL WriteChar( const cFieldDef_& field_def, char value );
    void FASTCALL WriteWChar( const cFieldDef_& field_def, wchar_t value );
    void FASTCALL WriteShort( const cFieldDef_& field_def, short value );
    void FASTCALL WriteInteger( const cFieldDef_& field_def, int value );
    void FASTCALL WriteLong( const cFieldDef_& field_def, long value );
    void FASTCALL WriteFloat( const cFieldDef_& field_def, double value );
    void FASTCALL WriteDate( const cFieldDef_& field_def, const cDateTime& value );
    void FASTCALL WriteString( const cFieldDef_& field_def, const ds_string& value );
    void FASTCALL WriteString( const cFieldDef_& field_def, const char *value );
public:
    CDFASTCALL cRecordPtr( cDoubleBuffer& buffer )
        : mBuffer(&buffer)
    {
    }
};

namespace detail
{

//***********************************************************************
//******    cFieldProxyRecordHelper
//***********************************************************************
class cFieldProxyRecordHelper : public cRawRecordPtr
{
private:
    const cFieldDef           *mFieldDef;
public:
    CDFASTCALL cFieldProxyRecordHelper( cRawBuffer& raw_buffer, const cFieldDef& field_def )
        : cRawRecordPtr(raw_buffer), mFieldDef(&field_def)
    {} // empty

    bool FASTCALL AsBoolean() const;
    void FASTCALL AsBoolean( bool value );
    char FASTCALL AsChar() const;
    void FASTCALL AsChar( char value );
    int  FASTCALL AsInteger() const;
    void FASTCALL AsInteger( int value );
    double  FASTCALL AsDouble() const;
    void FASTCALL AsDouble( double value );
    cDateTime FASTCALL AsDateTime() const;
    void FASTCALL AsDateTime( const cDateTime& value );
    ds_string FASTCALL AsString() const;
    void FASTCALL AsString( const ds_string& value );
    Variant FASTCALL AsVariant() const                      { return ( ReadVariant( *mFieldDef ) ); }
    void FASTCALL AsVariant( const Variant& value )         { WriteVariant( *mFieldDef, value ); }
};

//***********************************************************************
//******    cFieldProxy
//***********************************************************************
class cFieldProxy
{
private:
    cFieldProxyRecordHelper     mHelper;
public:
    CDFASTCALL cFieldProxy( cRawBuffer& raw_buffer, const cFieldDef& field_def )
        : mHelper(raw_buffer, field_def)                            {} // empty
    cFieldProxyRecordHelper * FASTCALL operator->()                 { return ( &mHelper ); }
    const cFieldProxyRecordHelper * FASTCALL operator->() const     { return ( &mHelper ); }
};

//***********************************************************************
//******    cRawRecordProxy
//***********************************************************************
template <typename RESULT_TYPE> class cRawRecordProxy
{
private:
    cRawBuffer          *mRawBuffer;
    const cFieldDefs    *mFieldDefs;
public:
    CDFASTCALL cRawRecordProxy( cRawBuffer& raw_buffer, const cFieldDefs& field_defs  )
        : mRawBuffer(&raw_buffer), mFieldDefs(&field_defs)      {} // empty
    const RESULT_TYPE FASTCALL operator*() const                { return ( RESULT_TYPE( *mRawBuffer ) ); }
    const RESULT_TYPE FASTCALL operator->() const               { return ( RESULT_TYPE( *mRawBuffer ) ); }

    cFieldProxy FieldByName( const ds_string& field_name )
    {
        return ( cFieldProxy( *mRawBuffer, mFieldDefs->FieldByName( field_name ) ) );
    }
    cFieldProxy FieldByName( const char *field_name )
    {
        return ( cFieldProxy( *mRawBuffer, mFieldDefs->FieldByName( field_name ) ) );
    }
    const cFieldProxy FieldByName( const ds_string& field_name ) const
    {
        return ( cFieldProxy( *mRawBuffer, mFieldDefs->FieldByName( field_name ) ) );
    }
    const cFieldProxy FieldByName( const char *field_name ) const
    {
        return ( cFieldProxy( *mRawBuffer, mFieldDefs->FieldByName( field_name ) ) );
    }
/*
    cFieldProxy operator[]( int idx )
    {
        return ( cFieldProxy( *mRawBuffer, mFieldDefs[idx] ) );
    }
    const cFieldProxy operator[]( int idx ) const
    {
        return ( cFieldProxy( *mRawBuffer, mFieldDefs->GetIndexed( idx ) ) );
    }
    cFieldProxy Value( const cFieldDef& field_def )
    {
        return ( cFieldProxy( *mRawBuffer, field_def ) );
    }
    const cFieldProxy Value( const cFieldDef& field_def ) const
    {
        return ( cFieldProxy( *mRawBuffer, field_def ) );
    }
*/
};

};  // namespace detail

//***********************************************************************
//******    cRecord
//***********************************************************************
class cRecord
{
private:
    friend class cTablebase;
    friend class cTableWriter;

    cData::value_type   mRecord;
    cFieldDefs_ptr      mFieldDefs;
protected:
    cDoubleBuffer * FASTCALL GetDoubleBuffer() const            { return ( mRecord.get() ); }
public:
    CDFASTCALL cRecord( const cData::value_type& container, const cFieldDefs_ptr& field_defs );
    CDFASTCALL ~cRecord();
    void FASTCALL CommitUpdates()                               { mRecord->CommitUpdates(); }
    detail::cFieldProxy FieldByName( const ds_string& field_name );
    detail::cFieldProxy FieldByName( const char *field_name );
};

//***********************************************************************
//******    cuRecord
//***********************************************************************
template <class RECORD> class cuRecord : public cRecord
{
private:
    RECORD FASTCALL operator*(); //                     { return ( RECORD( *GetDoubleBuffer() ) ); }
protected:
public:
    CDFASTCALL cuRecord( const cData::value_type& container, const cFieldDefs_ptr& field_defs )
        : cRecord( container, field_defs )
    {} // empty
    RECORD FASTCALL operator->()                    { return ( RECORD( *GetDoubleBuffer() ) ); }
};


//***********************************************************************
//******    cRecordIterator
//***********************************************************************
class cRecordIterator
{
private:
    friend class cIndex;
    friend class cTablebase;
    friend class cTableReader;

    cData::size_type    mIdx;
    cData_ptr           mContainer;
protected:
    typedef detail::cRawRecordProxy<cRawRecordPtr>      cOldValues;

    cDoubleBuffer * FASTCALL GetDoubleBuffer() const;
    const cData_ptr& FASTCALL GetData() const                   { return ( mContainer ); }
    cData::size_type FASTCALL GetIndex() const                  { return ( mIdx ); }
    void FASTCALL SetIndex( cData::size_type idx )              { mIdx = idx; }
    CDFASTCALL cRecordIterator( cData_ptr& container );
    CDFASTCALL cRecordIterator( cData_ptr& container, cData::size_type idx );
public:
    CDFASTCALL cRecordIterator( const cRecordIterator& src );
    CDFASTCALL ~cRecordIterator();
    cRecordIterator& FASTCALL operator = ( const cRecordIterator& src );
    cRecordIterator& FASTCALL operator++()
    {
        ++mIdx;
        return ( *this );
    }
    cRecordIterator& FASTCALL operator--()
    {
        --mIdx;
        return ( *this );
    }
    void FASTCALL Next()
    {
        if ( ! eof() )
            ++mIdx;
    }
    void FASTCALL Prev()
    {
        if ( mIdx > 0 )
            --mIdx;
    }
    bool FASTCALL eof() const                           { return ( mIdx >= mContainer->size() ); }
    bool FASTCALL bof() const                           { return ( mIdx == 0 ); }
    void FASTCALL First()                               { mIdx = 0; }
    void FASTCALL Last()                                { mIdx = mContainer->size() - 1; }
    int FASTCALL RecordCount() const                    { return ( mContainer->size() ); }
    void * FASTCALL GetMark() const                     { return ( reinterpret_cast<void *>(mIdx) ); }
    void FASTCALL GotoMark( void *mark )                { mIdx = reinterpret_cast<cData::size_type>(mark); }
    cUpdateStatus FASTCALL GetUpdateStatus() const      { return ( GetDoubleBuffer()->GetUpdateStatus() ); }

    const cOldValues FASTCALL OldValues()
    {
        return ( cOldValues( GetDoubleBuffer()->GetOriginalData(), *mContainer->GetFieldDefs().get() ) );
    }
    detail::cFieldProxy FASTCALL FieldByName( const ds_string& field_name );
    detail::cFieldProxy FASTCALL FieldByName( const char *field_name );
};

//***********************************************************************
//******    cuRecordIterator
//***********************************************************************
template <class RECORD> class cuRecordIterator : public cRecordIterator
{
private:
    typedef detail::cRawRecordProxy<typename RECORD::raw>      cOldValues;
    RECORD FASTCALL operator*(); //                     { return ( RECORD( *GetDoubleBuffer() ) ); }

    template <class RECORD> friend class cuTable;
    template <class RECORD> friend class cuIndex;

	CDFASTCALL cuRecordIterator( cData_ptr& container )
        : cRecordIterator(container)                                                {} // empty
    CDFASTCALL cuRecordIterator( cData_ptr& container, cData::size_type idx )
        : cRecordIterator(container, idx)                                           {} // empty
    CDFASTCALL cuRecordIterator( const cRecordIterator& iter )
        : cRecordIterator(iter)                                                     {} // empty
public:
    const cOldValues FASTCALL OldValues() const
    {
        return ( cOldValues( GetDoubleBuffer()->GetOriginalData(), *GetData()->GetFieldDefs().get() ) );
    }

    RECORD FASTCALL operator->()                    { return ( RECORD( *GetDoubleBuffer() ) ); }
    cuRecordIterator& FASTCALL operator++()
    {
        cRecordIterator::operator++();
        return ( *this );
    }
    cuRecordIterator& FASTCALL operator--()
    {
        cRecordIterator::operator--();
        return ( *this );
    }
};

//***********************************************************************
//******    cRangeIterator
//***********************************************************************
class cRangeIterator : private cRecordIterator
{
private:
    friend class cTable;
    friend class cIndex;
    friend class cTablebase;

    cData::size_type    mStart;
    cData::size_type    mEnd;
protected:
    CDFASTCALL cRangeIterator( cData_ptr& container, cData::size_type start, cData::size_type end );
public:
    CDFASTCALL cRangeIterator( const cRangeIterator& src );
    cRangeIterator& FASTCALL operator = ( const cRangeIterator& src );
    cRangeIterator& FASTCALL operator++()
    {
        cRecordIterator::operator++();
        return ( *this );
    }
    cRecordIterator& FASTCALL operator--()
    {
        cRecordIterator::operator--();
        return ( *this );
    }
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
    void * FASTCALL GetMark()               { return ( reinterpret_cast<void *>(GetIndex()) ); }
    void FASTCALL GotoMark( void *mark )    { SetIndex( reinterpret_cast<cData::size_type>(mark) ); }

    const cOldValues FASTCALL OldValues()                               { return ( cRecordIterator::OldValues() ); }
    detail::cFieldProxy FieldByName( const ds_string& field_name )      { return ( cRecordIterator::FieldByName( field_name ) ); }
    detail::cFieldProxy FieldByName( const char *field_name )           { return ( cRecordIterator::FieldByName( field_name ) ); }
};

//***********************************************************************
//******    cuRangeIterator
//***********************************************************************
template <class RECORD> class cuRangeIterator : public cRangeIterator
{
private:
    typedef detail::cRawRecordProxy<typename RECORD::raw>      cOldValues;
    RECORD FASTCALL operator*(); //                     { return ( RECORD( *GetDoubleBuffer() ) ); }

    template <class RECORD> friend class cuTable;
    template <class RECORD> friend class cuIndex;

    CDFASTCALL cuRangeIterator( const cRangeIterator& iter )
        : cRangeIterator(iter)                                                      {} // empty
public:
    const cOldValues FASTCALL OldValues() const
    {
        return ( cOldValues( GetDoubleBuffer()->GetOriginalData(), *GetData()->GetFieldDefs().get() ) );
    }

    RECORD FASTCALL operator->()                    { return ( RECORD( *GetDoubleBuffer() ) ); }
    cuRangeIterator& FASTCALL operator++()
    {
        cRangeIterator::operator++();
        return ( *this );
    }
    cuRangeIterator& FASTCALL operator--()
    {
        cRangeIterator::operator--();
        return ( *this );
    }
};

};
//---------------------------------------------------------------------------
#endif