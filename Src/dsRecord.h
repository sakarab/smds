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
#ifndef SM_DS_RECORD_H
#define SM_DS_RECORD_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include "dsBuffer.h"
#include "dsVariant.h"
//---------------------------------------------------------------------------
namespace smds
{

class Tablebase;
class Table;
class Index;
class cTableReader;
template <class RECORD> class cuTable;
template <class RECORD> class cuIndex;

namespace detail
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
    char FASTCALL ReadByte( const cFieldDef& field_def ) const;
    short FASTCALL ReadShort( const cFieldDef& field_def ) const;
    int FASTCALL ReadInteger( const cFieldDef& field_def ) const;
    long long FASTCALL ReadLongLong( const cFieldDef& field_def ) const;
    double FASTCALL ReadFloat( const cFieldDef& field_def ) const;
    dbDate FASTCALL ReadDate( const cFieldDef& field_def ) const;
    dbTime FASTCALL ReadTime( const cFieldDef& field_def ) const;
    dbDateTime FASTCALL ReadDateTime( const cFieldDef& field_def ) const;
    ds_string FASTCALL ReadString( const cFieldDef& field_def ) const;
    Variant FASTCALL ReadVariant( const cFieldDef& field_def ) const                    { return mRawBuffer->ReadVariant( field_def ); }

    void FASTCALL WriteBool( const cFieldDef& field_def, bool value );
    void FASTCALL WriteByte( const cFieldDef& field_def, char value );
    void FASTCALL WriteShort( const cFieldDef& field_def, short value );
    void FASTCALL WriteInteger( const cFieldDef& field_def, int value );
    void FASTCALL WriteLongLong( const cFieldDef& field_def, long long value );
    void FASTCALL WriteFloat( const cFieldDef& field_def, double value );
    void FASTCALL WriteDate( const cFieldDef& field_def, const dbDate& value );
    void FASTCALL WriteTime( const cFieldDef& field_def, const dbTime& value );
    void FASTCALL WriteDateTime( const cFieldDef& field_def, const dbDateTime& value );
    void FASTCALL WriteString( const cFieldDef& field_def, const ds_string& value );
    void FASTCALL WriteString( const cFieldDef& field_def, const char *value );
    void FASTCALL WriteVariant( const cFieldDef& field_def, const Variant& value )      { mRawBuffer->WriteVariant( field_def, value ); }

    bool FASTCALL ReadBool( const cFieldDef_& field_def ) const;
    char FASTCALL ReadByte( const cFieldDef_& field_def ) const;
    short FASTCALL ReadShort( const cFieldDef_& field_def ) const;
    int FASTCALL ReadInteger( const cFieldDef_& field_def ) const;
    long long FASTCALL ReadLongLong( const cFieldDef_& field_def ) const;
    double FASTCALL ReadFloat( const cFieldDef_& field_def ) const;
    dbDate FASTCALL ReadDate( const cFieldDef_& field_def ) const;
    dbTime FASTCALL ReadTime( const cFieldDef_& field_def ) const;
    dbDateTime FASTCALL ReadDateTime( const cFieldDef_& field_def ) const;
    ds_string FASTCALL ReadString( const cFieldDef_& field_def ) const;

    void FASTCALL WriteBool( const cFieldDef_& field_def, bool value );
    void FASTCALL WriteByte( const cFieldDef_& field_def, char value );
    void FASTCALL WriteShort( const cFieldDef_& field_def, short value );
    void FASTCALL WriteInteger( const cFieldDef_& field_def, int value );
    void FASTCALL WriteLongLong( const cFieldDef_& field_def, long long value );
    void FASTCALL WriteFloat( const cFieldDef_& field_def, double value );
    void FASTCALL WriteDate( const cFieldDef_& field_def, const dbDate& value );
    void FASTCALL WriteTime( const cFieldDef_& field_def, const dbTime& value );
    void FASTCALL WriteDateTime( const cFieldDef_& field_def, const dbDateTime& value );
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
    DoubleBuffer        *mBuffer;
protected:
    bool FASTCALL IsNull( const cFieldDef& field_def ) const;
    bool FASTCALL IsNull( const cFieldDef_& field_def ) const;
    void FASTCALL Nullify( const cFieldDef& field_def );

    bool FASTCALL ReadBool( const cFieldDef& field_def ) const;
    char FASTCALL ReadByte( const cFieldDef& field_def ) const;
    short FASTCALL ReadShort( const cFieldDef& field_def ) const;
    int FASTCALL ReadInteger( const cFieldDef& field_def ) const;
    long long FASTCALL ReadLongLong( const cFieldDef& field_def ) const;
    double FASTCALL ReadFloat( const cFieldDef& field_def ) const;
    dbDate FASTCALL ReadDate( const cFieldDef& field_def ) const;
    dbTime FASTCALL ReadTime( const cFieldDef& field_def ) const;
    dbDateTime FASTCALL ReadDateTime( const cFieldDef& field_def ) const;
    ds_string FASTCALL ReadString( const cFieldDef& field_def ) const;
    Variant FASTCALL ReadVariant( const cFieldDef& field_def ) const;

    void FASTCALL WriteBool( const cFieldDef& field_def, bool value );
    void FASTCALL WriteByte( const cFieldDef& field_def, char value );
    void FASTCALL WriteShort( const cFieldDef& field_def, short value );
    void FASTCALL WriteInteger( const cFieldDef& field_def, int value );
    void FASTCALL WriteLongLong( const cFieldDef& field_def, long long value );
    void FASTCALL WriteFloat( const cFieldDef& field_def, double value );
    void FASTCALL WriteDate( const cFieldDef& field_def, const dbDate& value );
    void FASTCALL WriteTime( const cFieldDef& field_def, const dbTime& value );
    void FASTCALL WriteDateTime( const cFieldDef& field_def, const dbDateTime& value );
    void FASTCALL WriteString( const cFieldDef& field_def, const ds_string& value );
    void FASTCALL WriteString( const cFieldDef& field_def, const char *value );
    void FASTCALL WriteVariant( const cFieldDef& field_def, const Variant& value );

    bool FASTCALL ReadBool( const cFieldDef_& field_def ) const;
    char FASTCALL ReadByte( const cFieldDef_& field_def ) const;
    short FASTCALL ReadShort( const cFieldDef_& field_def ) const;
    int FASTCALL ReadInteger( const cFieldDef_& field_def ) const;
    long long FASTCALL ReadLongLong( const cFieldDef_& field_def ) const;
    double FASTCALL ReadFloat( const cFieldDef_& field_def ) const;
    dbDate FASTCALL ReadDate( const cFieldDef_& field_def ) const;
    dbTime FASTCALL ReadTime( const cFieldDef_& field_def ) const;
    dbDateTime FASTCALL ReadDateTime( const cFieldDef_& field_def ) const;
    ds_string FASTCALL ReadString( const cFieldDef_& field_def ) const;

    void FASTCALL WriteBool( const cFieldDef_& field_def, bool value );
    void FASTCALL WriteByte( const cFieldDef_& field_def, char value );
    void FASTCALL WriteShort( const cFieldDef_& field_def, short value );
    void FASTCALL WriteInteger( const cFieldDef_& field_def, int value );
    void FASTCALL WriteLongLong( const cFieldDef_& field_def, long long value );
    void FASTCALL WriteFloat( const cFieldDef_& field_def, double value );
    void FASTCALL WriteDate( const cFieldDef_& field_def, const dbDate& value );
    void FASTCALL WriteTime( const cFieldDef_& field_def, const dbTime& value );
    void FASTCALL WriteDateTime( const cFieldDef_& field_def, const dbDateTime& value );
    void FASTCALL WriteString( const cFieldDef_& field_def, const ds_string& value );
    void FASTCALL WriteString( const cFieldDef_& field_def, const char *value );
public:
    CDFASTCALL cRecordPtr( DoubleBuffer& buffer )
        : mBuffer(&buffer)
    {
    }
};

//***********************************************************************
//******    cRawFieldProxyHelper
//***********************************************************************
class cRawFieldProxyHelper : private cRawRecordPtr
{
private:
    typedef cRawRecordPtr   inherited;
private:
    const cFieldDef         *mFieldDef;
public:
    CDFASTCALL cRawFieldProxyHelper( cRawBuffer& buffer, const cFieldDef& field_def )
        : inherited(buffer), mFieldDef(&field_def)
    {} // empty

    bool FASTCALL IsNull() const                            { return inherited::IsNull( *mFieldDef ); }

    bool FASTCALL AsBoolean() const;
    char FASTCALL AsByte() const;
    int  FASTCALL AsInteger() const;
    double FASTCALL AsDouble() const;
    dbDate FASTCALL AsDate() const;
    dbTime FASTCALL AsTime() const;
    dbDateTime FASTCALL AsDateTime() const;
    ds_string FASTCALL AsString() const;
    Variant FASTCALL AsVariant() const                      { return ReadVariant( *mFieldDef ); }

    void FASTCALL AsBoolean( bool value );
    void FASTCALL AsByte( char value );
    void FASTCALL AsInteger( int value );
    void FASTCALL AsDouble( double value );
    void FASTCALL AsDateTime( const dbDateTime& value );
    void FASTCALL AsString( const ds_string& value );
    void FASTCALL AsVariant( const Variant& value )         { WriteVariant( *mFieldDef, value ); }
};

//***********************************************************************
//******    cDoubleFieldProxyHelper
//***********************************************************************
class cDoubleFieldProxyHelper : private cRecordPtr
{
private:
    typedef cRecordPtr      inherited;
private:
    const cFieldDef         *mFieldDef;
public:
    CDFASTCALL cDoubleFieldProxyHelper( DoubleBuffer& buffer, const cFieldDef& field_def )
        : inherited(buffer), mFieldDef(&field_def)
    {} // empty

    bool FASTCALL IsNull() const                            { return inherited::IsNull( *mFieldDef ); }

    bool FASTCALL AsBoolean() const;
    char FASTCALL AsByte() const;
    int  FASTCALL AsInteger() const;
    double FASTCALL AsDouble() const;
    dbDate FASTCALL AsDate() const;
    dbTime FASTCALL AsTime() const;
    dbDateTime FASTCALL AsDateTime() const;
    ds_string FASTCALL AsString() const;
    Variant FASTCALL AsVariant() const                      { return inherited::ReadVariant( *mFieldDef ); }

    void FASTCALL AsBoolean( bool value );
    void FASTCALL AsByte( char value );
    void FASTCALL AsInteger( int value );
    void FASTCALL AsDouble( double value );
    void FASTCALL AsDate( const dbDate& value );
    void FASTCALL AsTime( const dbTime& value );
    void FASTCALL AsDateTime( const dbDateTime& value );
    void FASTCALL AsString( const ds_string& value );
    void FASTCALL AsVariant( const Variant& value )         { inherited::WriteVariant( *mFieldDef, value ); }
};

//***********************************************************************
//******    cRawFieldProxy
//***********************************************************************
class cRawFieldProxy
{
private:
    cRawFieldProxyHelper        mHelper;
public:
    CDFASTCALL cRawFieldProxy( cRawBuffer& buffer, const cFieldDef& field_def )
        : mHelper(buffer, field_def)                                {} // empty
    cRawFieldProxyHelper * FASTCALL operator->()                    { return ( &mHelper ); }
    const cRawFieldProxyHelper * FASTCALL operator->() const        { return ( &mHelper ); }
};

//***********************************************************************
//******    cDoubleFieldProxy
//***********************************************************************
class cDoubleFieldProxy
{
private:
    cDoubleFieldProxyHelper     mHelper;
public:
    CDFASTCALL cDoubleFieldProxy( DoubleBuffer& buffer, const cFieldDef& field_def )
        : mHelper(buffer, field_def)                                {} // empty
    cDoubleFieldProxyHelper * FASTCALL operator->()                 { return ( &mHelper ); }
    const cDoubleFieldProxyHelper * FASTCALL operator->() const     { return ( &mHelper ); }
};

//***********************************************************************
//******    cOldValuesProxy
//***********************************************************************
template <typename RESULT_TYPE> class cOldValuesProxy
{
private:
    cRawBuffer          *mRawBuffer;
    const cFieldDefs    *mFieldDefs;
public:
    CDFASTCALL cOldValuesProxy( cRawBuffer& raw_buffer, const cFieldDefs& field_defs  )
        : mRawBuffer(&raw_buffer), mFieldDefs(&field_defs)      {} // empty
    const RESULT_TYPE FASTCALL operator*() const                { return RESULT_TYPE( *mRawBuffer ); }
    const RESULT_TYPE FASTCALL operator->() const               { return RESULT_TYPE( *mRawBuffer ); }

    cRawFieldProxy FieldByName( const ds_string& field_name )
    {
        return cRawFieldProxy( *mRawBuffer, mFieldDefs->FieldByName( field_name ) );
    }
    cRawFieldProxy FieldByName( const char *field_name )
    {
        return cRawFieldProxy( *mRawBuffer, mFieldDefs->FieldByName( field_name ) );
    }
    const cRawFieldProxy FieldByName( const ds_string& field_name ) const
    {
        return cRawFieldProxy( *mRawBuffer, mFieldDefs->FieldByName( field_name ) );
    }
    const cRawFieldProxy FieldByName( const char *field_name ) const
    {
        return cRawFieldProxy( *mRawBuffer, mFieldDefs->FieldByName( field_name ) );
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

//***********************************************************************
//******    cRecordIterator
//***********************************************************************
class cRecordIterator
{
private:
    friend class smds::cTableReader;
    friend class smds::Tablebase;
    friend class Table;
    friend class Index;

#if ! defined( SM_DS_FAST_ITERATORS_INTERNAL )
    typedef spData          ContainerPointerType;
    typedef spData &        ContainerReferanceType;
    typedef const spData &  ConstContainerReferanceType;
#else
    typedef Data *          ContainerPointerType;
    typedef Data *          ContainerReferanceType;
    typedef Data *          ConstContainerReferanceType;
#endif

    Data::size_type         mIdx;
    ContainerPointerType    mContainer;
protected:
    typedef cOldValuesProxy<cRawRecordPtr>      OldValuesProxy;
    typedef cDoubleFieldProxy                   cFieldProxy;

    DoubleBuffer * FASTCALL GetDoubleBuffer() const;
    ConstContainerReferanceType FASTCALL GetData() const        { return mContainer; }
    Data::size_type FASTCALL GetIndex() const                   { return mIdx; }
    void FASTCALL SetIndex( Data::size_type idx )               { mIdx = idx; }

    CDFASTCALL cRecordIterator( spData& container );
    CDFASTCALL cRecordIterator( spData& container, Data::size_type idx );
public:
    CDFASTCALL cRecordIterator( const cRecordIterator& src );
    virtual CDFASTCALL ~cRecordIterator();
    cRecordIterator& FASTCALL operator = ( const cRecordIterator& src );

    cRecordIterator& FASTCALL operator++()              { ++mIdx;       return *this; }
    cRecordIterator& FASTCALL operator--()              { --mIdx;       return *this; }
    cRecordIterator& FASTCALL operator+=( int num )     { mIdx += num;  return *this; }
    cRecordIterator& FASTCALL operator-=( int num )     { mIdx -= num;  return *this; }

    const cRecordIterator FASTCALL operator++( int );
    const cRecordIterator FASTCALL operator--( int );

    cRecordIterator FASTCALL operator+( int num );
    cRecordIterator FASTCALL operator-( int num );

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
    bool FASTCALL eof() const                           { return mIdx >= mContainer->size(); }
    bool FASTCALL bof() const                           { return ( mIdx == 0 ); }
    void FASTCALL First()                               { mIdx = 0; }
    void FASTCALL Last()                                { mIdx = mContainer->size() - 1; }
    int FASTCALL RecordCount() const                    { return mContainer->size(); }
    void * FASTCALL GetMark() const                     { return reinterpret_cast<void *>(mIdx); }
    void FASTCALL GotoMark( void *mark )                { mIdx = reinterpret_cast<detail::Data::size_type>(mark); }
    cUpdateStatus FASTCALL GetUpdateStatus() const      { return GetDoubleBuffer()->GetUpdateStatus(); }

    Variant FASTCALL Value( const cFieldDef& field_def ) const;
    void FASTCALL Value( const cFieldDef& field_def, const Variant val );
    const OldValuesProxy FASTCALL OldValues()
    {
        return OldValuesProxy( GetDoubleBuffer()->GetOriginalData(), *mContainer->GetFieldDefs().get() );
    }

    cFieldProxy FASTCALL FieldByName( const ds_string& field_name );
    cFieldProxy FASTCALL FieldByName( const char *field_name );
    bool FASTCALL Locate( const Variant& value, const cFindField& field );
    bool FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields );

    void FASTCALL Delete()                                                      { mContainer->Delete( mIdx ); }
    const spFieldDefs& FASTCALL GetFieldDefs() const                            { return mContainer->GetFieldDefs(); }
};

//***********************************************************************
//******    cuRecordIterator
//***********************************************************************
/*
template <class RECORD> class cuRecordIterator : public cRecordIterator
{
private:
    typedef detail::cRawRecordProxy<typename RECORD::raw>   OldValuesProxy;

    friend class cuTable<RECORD>;
    friend class cuIndex<RECORD>;
protected:
	CDFASTCALL cuRecordIterator( detail::cData_ptr& container )
        : cRecordIterator(container)                                                {} // empty
    CDFASTCALL cuRecordIterator( detail::cData_ptr& container, detail::Data::size_type idx )
        : cRecordIterator(container, idx)                                           {} // empty
    CDFASTCALL cuRecordIterator( const cRecordIterator& iter )
        : cRecordIterator(iter)                                                     {} // empty
public:
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

    const OldValuesProxy FASTCALL OldValues() const
    {
        return ( OldValuesProxy( GetDoubleBuffer()->GetOriginalData(), *GetData()->GetFieldDefs().get() ) );
    }
};
*/

//***********************************************************************
//******    cRangeIterator
//***********************************************************************
/*
class cRangeIterator : private cRecordIterator
{
private:
    friend class Index;
    friend class Tablebase;

    Data::size_type    mStart;
    Data::size_type    mEnd;
protected:
    CDFASTCALL cRangeIterator( cData_ptr& container, Data::size_type start, Data::size_type end );
    CDFASTCALL cRangeIterator( cData_ptr& container, Data::size_type start, Data::size_type end, Data::size_type idx );
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
    void FASTCALL GotoMark( void *mark )    { SetIndex( reinterpret_cast<Data::size_type>(mark) ); }

    const OldValuesProxy FASTCALL OldValues()                   { return ( cRecordIterator::OldValues() ); }
    cFieldProxy FieldByName( const ds_string& field_name )      { return ( cRecordIterator::FieldByName( field_name ) ); }
    cFieldProxy FieldByName( const char *field_name )           { return ( cRecordIterator::FieldByName( field_name ) ); }
};
*/

//***********************************************************************
//******    cuRangeIterator
//***********************************************************************
/*
template <class RECORD> class cuRangeIterator : public cRangeIterator
{
private:
    typedef cRawRecordProxy<typename RECORD::raw>      OldValuesProxy;

    friend class cuTable<RECORD>;
    friend class cuIndex<RECORD>;

    CDFASTCALL cuRangeIterator( const cRangeIterator& iter )
        : cRangeIterator(iter)                                                      {} // empty
public:
    const OldValuesProxy FASTCALL OldValues() const
    {
        return ( OldValuesProxy( GetDoubleBuffer()->GetOriginalData(), *GetData()->GetFieldDefs().get() ) );
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
*/

}; // namespace detail

//***********************************************************************
//******    cRecord
//***********************************************************************
class cRecord
{
private:
    friend class Tablebase;
    friend class cTableWriter;
    typedef detail::cDoubleFieldProxy       cFieldProxy;

    detail::Data::value_type    mRecord;
    spFieldDefs                 mFieldDefs;
protected:
    detail::DoubleBuffer * FASTCALL GetDoubleBuffer() const             { return ( mRecord.get() ); }
public:
    CDFASTCALL cRecord( const detail::Data::value_type& container, const spFieldDefs& field_defs );
    CDFASTCALL ~cRecord();
    void FASTCALL CommitUpdates()                                       { mRecord->CommitUpdates(); }
    cFieldProxy FieldByName( const ds_string& field_name );
    cFieldProxy FieldByName( const char *field_name );
};

//***********************************************************************
//******    cuRecord
//***********************************************************************
template <class RECORD> class cuRecord : public cRecord
{
public:
    CDFASTCALL cuRecord( const detail::Data::value_type& container, const spFieldDefs& field_defs )
        : cRecord( container, field_defs )
    {} // empty
    RECORD FASTCALL operator->()                    { return ( RECORD( *GetDoubleBuffer() ) ); }
};

}; // namespace smds
//---------------------------------------------------------------------------
#endif

