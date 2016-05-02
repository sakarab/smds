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

#include "pre_smDS.h"
#include "dsRecord.h"
#include "dsExceptions.h"
//---------------------------------------------------------------------------
namespace smds
{

namespace detail
{

//***********************************************************************
//******    cRawRecordPtr
//***********************************************************************
bool FASTCALL cRawRecordPtr::ReadBool( const cFieldDef_& field_def ) const              { return mRawBuffer->ReadBool( field_def ); }
char FASTCALL cRawRecordPtr::ReadByte( const cFieldDef_& field_def ) const              { return mRawBuffer->ReadByte( field_def ); }
short FASTCALL cRawRecordPtr::ReadShort( const cFieldDef_& field_def ) const            { return mRawBuffer->ReadShort( field_def ); }
int FASTCALL cRawRecordPtr::ReadInteger( const cFieldDef_& field_def ) const            { return mRawBuffer->ReadInteger( field_def ); }
long long FASTCALL cRawRecordPtr::ReadLongLong( const cFieldDef_& field_def ) const     { return mRawBuffer->ReadLongLong( field_def ); }
double FASTCALL cRawRecordPtr::ReadFloat( const cFieldDef_& field_def ) const           { return mRawBuffer->ReadFloat( field_def ); }
dbDate FASTCALL cRawRecordPtr::ReadDate( const cFieldDef_& field_def ) const            { return mRawBuffer->ReadDate( field_def ); }
dbTime FASTCALL cRawRecordPtr::ReadTime( const cFieldDef_& field_def ) const            { return mRawBuffer->ReadTime( field_def ); }
dbDateTime FASTCALL cRawRecordPtr::ReadDateTime( const cFieldDef_& field_def ) const    { return mRawBuffer->ReadDateTime( field_def ); }
ds_string FASTCALL cRawRecordPtr::ReadString( const cFieldDef_& field_def ) const       { return mRawBuffer->ReadString( field_def ); }

void FASTCALL cRawRecordPtr::WriteBool( const cFieldDef_& field_def, bool value )                   { mRawBuffer->WriteBool( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteByte( const cFieldDef_& field_def, char value )                   { mRawBuffer->WriteByte( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteShort( const cFieldDef_& field_def, short value )                 { mRawBuffer->WriteShort( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteInteger( const cFieldDef_& field_def, int value )                 { mRawBuffer->WriteInteger( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteLongLong( const cFieldDef_& field_def, long long value )          { mRawBuffer->WriteLongLong( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteFloat( const cFieldDef_& field_def, double value )                { mRawBuffer->WriteFloat( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteDate( const cFieldDef_& field_def, const dbDate& value )          { mRawBuffer->WriteDate( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteTime( const cFieldDef_& field_def, const dbTime& value )          { mRawBuffer->WriteTime( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteDateTime( const cFieldDef_& field_def, const dbDateTime& value )  { mRawBuffer->WriteDateTime( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteString( const cFieldDef_& field_def, const ds_string& value )     { mRawBuffer->WriteString( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteString( const cFieldDef_& field_def, const char *value )          { mRawBuffer->WriteString( field_def, value ); }

bool FASTCALL cRawRecordPtr::ReadBool( const cFieldDef& field_def ) const               { return mRawBuffer->ReadBool( field_def ); }
char FASTCALL cRawRecordPtr::ReadByte( const cFieldDef& field_def ) const               { return mRawBuffer->ReadByte( field_def ); }
short FASTCALL cRawRecordPtr::ReadShort( const cFieldDef& field_def ) const             { return mRawBuffer->ReadShort( field_def ); }
int FASTCALL cRawRecordPtr::ReadInteger( const cFieldDef& field_def ) const             { return mRawBuffer->ReadInteger( field_def ); }
long long FASTCALL cRawRecordPtr::ReadLongLong( const cFieldDef& field_def ) const      { return mRawBuffer->ReadLongLong( field_def ); }
double FASTCALL cRawRecordPtr::ReadFloat( const cFieldDef& field_def ) const            { return mRawBuffer->ReadFloat( field_def ); }
dbDate FASTCALL cRawRecordPtr::ReadDate( const cFieldDef& field_def ) const             { return mRawBuffer->ReadDate( field_def ); }
dbTime FASTCALL cRawRecordPtr::ReadTime( const cFieldDef& field_def ) const             { return mRawBuffer->ReadTime( field_def ); }
dbDateTime FASTCALL cRawRecordPtr::ReadDateTime( const cFieldDef& field_def ) const     { return mRawBuffer->ReadDateTime( field_def ); }
ds_string FASTCALL cRawRecordPtr::ReadString( const cFieldDef& field_def ) const        { return mRawBuffer->ReadString( field_def ); }

void FASTCALL cRawRecordPtr::WriteBool( const cFieldDef& field_def, bool value )                    { mRawBuffer->WriteBool( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteByte( const cFieldDef& field_def, char value )                    { mRawBuffer->WriteByte( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteShort( const cFieldDef& field_def, short value )                  { mRawBuffer->WriteShort( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteInteger( const cFieldDef& field_def, int value )                  { mRawBuffer->WriteInteger( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteLongLong( const cFieldDef& field_def, long long value )           { mRawBuffer->WriteLongLong( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteFloat( const cFieldDef& field_def, double value )                 { mRawBuffer->WriteFloat( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteDate( const cFieldDef& field_def, const dbDate& value )           { mRawBuffer->WriteDate( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteTime( const cFieldDef& field_def, const dbTime& value )           { mRawBuffer->WriteTime( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteDateTime( const cFieldDef& field_def, const dbDateTime& value )   { mRawBuffer->WriteDateTime( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteString( const cFieldDef& field_def, const ds_string& value )      { mRawBuffer->WriteString( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteString( const cFieldDef& field_def, const char *value )           { mRawBuffer->WriteString( field_def, value ); }

//***********************************************************************
//******    cRecordPtr
//***********************************************************************
bool FASTCALL cRecordPtr::IsNull( const cFieldDef& field_def ) const                { return mBuffer->IsNull( field_def ); }
bool FASTCALL cRecordPtr::IsNull( const cFieldDef_& field_def ) const               { return mBuffer->IsNull( field_def ); }
void FASTCALL cRecordPtr::Nullify( const cFieldDef& field_def )                     { mBuffer->Nullify( field_def ); }

bool FASTCALL cRecordPtr::ReadBool( const cFieldDef_& field_def ) const             { return mBuffer->ReadBool( field_def ); }
char FASTCALL cRecordPtr::ReadByte( const cFieldDef_& field_def ) const             { return mBuffer->ReadByte( field_def ); }
short FASTCALL cRecordPtr::ReadShort( const cFieldDef_& field_def ) const           { return mBuffer->ReadShort( field_def ); }
int FASTCALL cRecordPtr::ReadInteger( const cFieldDef_& field_def ) const           { return mBuffer->ReadInteger( field_def ); }
long long FASTCALL cRecordPtr::ReadLongLong( const cFieldDef_& field_def ) const    { return mBuffer->ReadLongLong( field_def ); }
double FASTCALL cRecordPtr::ReadFloat( const cFieldDef_& field_def ) const          { return mBuffer->ReadFloat( field_def ); }
dbDate FASTCALL cRecordPtr::ReadDate( const cFieldDef_& field_def ) const           { return mBuffer->ReadDate( field_def ); }
dbTime FASTCALL cRecordPtr::ReadTime( const cFieldDef_& field_def ) const           { return mBuffer->ReadTime( field_def ); }
dbDateTime FASTCALL cRecordPtr::ReadDateTime( const cFieldDef_& field_def ) const   { return mBuffer->ReadDateTime( field_def ); }
ds_string FASTCALL cRecordPtr::ReadString( const cFieldDef_& field_def ) const      { return mBuffer->ReadString( field_def ); }

void FASTCALL cRecordPtr::WriteBool( const cFieldDef_& field_def, bool value )                  { mBuffer->WriteBool( field_def, value ); }
void FASTCALL cRecordPtr::WriteByte( const cFieldDef_& field_def, char value )                  { mBuffer->WriteByte( field_def, value ); }
void FASTCALL cRecordPtr::WriteShort( const cFieldDef_& field_def, short value )                { mBuffer->WriteShort( field_def, value ); }
void FASTCALL cRecordPtr::WriteInteger( const cFieldDef_& field_def, int value )                { mBuffer->WriteInteger( field_def, value ); }
void FASTCALL cRecordPtr::WriteLongLong( const cFieldDef_& field_def, long long value )         { mBuffer->WriteLongLong( field_def, value ); }
void FASTCALL cRecordPtr::WriteFloat( const cFieldDef_& field_def, double value )               { mBuffer->WriteFloat( field_def, value ); }
void FASTCALL cRecordPtr::WriteDate( const cFieldDef_& field_def, const dbDate& value )         { mBuffer->WriteDate( field_def, value ); }
void FASTCALL cRecordPtr::WriteTime( const cFieldDef_& field_def, const dbTime& value )         { mBuffer->WriteTime( field_def, value ); }
void FASTCALL cRecordPtr::WriteDateTime( const cFieldDef_& field_def, const dbDateTime& value ) { mBuffer->WriteDateTime( field_def, value ); }
void FASTCALL cRecordPtr::WriteString( const cFieldDef_& field_def, const ds_string& value )    { mBuffer->WriteString( field_def, value ); }
void FASTCALL cRecordPtr::WriteString( const cFieldDef_& field_def, const char *value )         { mBuffer->WriteString( field_def, value ); }

bool FASTCALL cRecordPtr::ReadBool( const cFieldDef& field_def ) const             { return mBuffer->ReadBool( field_def ); }
char FASTCALL cRecordPtr::ReadByte( const cFieldDef& field_def ) const             { return mBuffer->ReadByte( field_def ); }
short FASTCALL cRecordPtr::ReadShort( const cFieldDef& field_def ) const           { return mBuffer->ReadShort( field_def ); }
int FASTCALL cRecordPtr::ReadInteger( const cFieldDef& field_def ) const           { return mBuffer->ReadInteger( field_def ); }
long long FASTCALL cRecordPtr::ReadLongLong( const cFieldDef& field_def ) const    { return mBuffer->ReadLongLong( field_def ); }
double FASTCALL cRecordPtr::ReadFloat( const cFieldDef& field_def ) const          { return mBuffer->ReadFloat( field_def ); }
dbDate FASTCALL cRecordPtr::ReadDate( const cFieldDef& field_def ) const           { return mBuffer->ReadDate( field_def ); }
dbTime FASTCALL cRecordPtr::ReadTime( const cFieldDef& field_def ) const           { return mBuffer->ReadTime( field_def ); }
dbDateTime FASTCALL cRecordPtr::ReadDateTime( const cFieldDef& field_def ) const   { return mBuffer->ReadDateTime( field_def ); }
ds_string FASTCALL cRecordPtr::ReadString( const cFieldDef& field_def ) const      { return mBuffer->ReadString( field_def ); }
Variant FASTCALL cRecordPtr::ReadVariant( const cFieldDef& field_def ) const       { return mBuffer->ReadVariant( field_def ); }

void FASTCALL cRecordPtr::WriteBool( const cFieldDef& field_def, bool value )                  { mBuffer->WriteBool( field_def, value ); }
void FASTCALL cRecordPtr::WriteByte( const cFieldDef& field_def, char value )                  { mBuffer->WriteByte( field_def, value ); }
void FASTCALL cRecordPtr::WriteShort( const cFieldDef& field_def, short value )                { mBuffer->WriteShort( field_def, value ); }
void FASTCALL cRecordPtr::WriteInteger( const cFieldDef& field_def, int value )                { mBuffer->WriteInteger( field_def, value ); }
void FASTCALL cRecordPtr::WriteLongLong( const cFieldDef& field_def, long long value )         { mBuffer->WriteLongLong( field_def, value ); }
void FASTCALL cRecordPtr::WriteFloat( const cFieldDef& field_def, double value )               { mBuffer->WriteFloat( field_def, value ); }
void FASTCALL cRecordPtr::WriteDate( const cFieldDef& field_def, const dbDate& value )         { mBuffer->WriteDate( field_def, value ); }
void FASTCALL cRecordPtr::WriteTime( const cFieldDef& field_def, const dbTime& value )         { mBuffer->WriteTime( field_def, value ); }
void FASTCALL cRecordPtr::WriteDateTime( const cFieldDef& field_def, const dbDateTime& value ) { mBuffer->WriteDateTime( field_def, value ); }
void FASTCALL cRecordPtr::WriteString( const cFieldDef& field_def, const ds_string& value )    { mBuffer->WriteString( field_def, value ); }
void FASTCALL cRecordPtr::WriteString( const cFieldDef& field_def, const char *value )         { mBuffer->WriteString( field_def, value ); }
void FASTCALL cRecordPtr::WriteVariant( const cFieldDef& field_def, const Variant& value )     { mBuffer->WriteVariant( field_def, value ); }

//***********************************************************************
//******    cRecordIterator
//***********************************************************************
CDFASTCALL cRecordIterator::cRecordIterator( spData& container )
    : mIdx(0),
#if ! defined( SM_DS_FAST_ITERATORS_INTERNAL )
      mContainer(container)
#else
      mContainer(container.get())
#endif
{
}

CDFASTCALL cRecordIterator::cRecordIterator( spData& container, detail::Data::size_type idx )
    : mIdx(idx),
#if ! defined( SM_DS_FAST_ITERATORS_INTERNAL )
      mContainer(container)
#else
      mContainer(container.get())
#endif
{
}

CDFASTCALL cRecordIterator::cRecordIterator( const cRecordIterator& src )
    : mIdx(src.mIdx), mContainer(src.mContainer)
{
}

CDFASTCALL cRecordIterator::~cRecordIterator()
{
}

cRecordIterator& FASTCALL cRecordIterator::operator = ( const cRecordIterator& src )
{
    if ( &src != this )
    {
        mIdx = src.mIdx;
        mContainer = src.mContainer;
    }
    return ( *this );
}

detail::DoubleBuffer * FASTCALL cRecordIterator::GetDoubleBuffer() const
{
    return ( (*mContainer)[mIdx].get() );
}

const cRecordIterator FASTCALL cRecordIterator::operator++( int )
{
    cRecordIterator     tmp( *this );

    ++(*this);
    return tmp;
}

const cRecordIterator FASTCALL cRecordIterator::operator--( int )
{
    cRecordIterator     tmp( *this );

    --(*this);
    return tmp;
}

cRecordIterator FASTCALL cRecordIterator::operator+( int num )
{
    cRecordIterator     tmp( *this );

    tmp += num;
    return tmp;
}

cRecordIterator FASTCALL cRecordIterator::operator-( int num )
{
    cRecordIterator     tmp( *this );

    tmp -= num;
    return tmp;
}

cRecordIterator::cFieldProxy FASTCALL cRecordIterator::FieldByName( const ds_string& field_name )
{
    return cFieldProxy( *GetDoubleBuffer(), mContainer->FieldByName( field_name ) );
}

cRecordIterator::cFieldProxy FASTCALL cRecordIterator::FieldByName( const char *field_name )
{
    return FieldByName( ds_string( field_name ) );
}

bool FASTCALL cRecordIterator::Locate( const Variant& value, const cFindField& field )
{
    return Locate( OpenValues( value ), OpenFindFields( field ) );
}

bool FASTCALL cRecordIterator::Locate( const OpenValues& values, const OpenFindFields& fields )
{
    Data::locate_result     result;

    mContainer->Locate( values, fields, result );
    if ( result.first )
        mIdx = result.second;
    return result.first;
}

Variant FASTCALL cRecordIterator::Value( const cFieldDef& field_def ) const
{
    return cFieldProxy( *GetDoubleBuffer(), field_def )->AsVariant();
}

void FASTCALL cRecordIterator::Value( const cFieldDef& field_def, const Variant val )
{
    cFieldProxy( *GetDoubleBuffer(), field_def )->AsVariant( val );
}

//***********************************************************************
//******    cRangeIterator
//***********************************************************************
/*
CDFASTCALL cRangeIterator::cRangeIterator( cData_ptr& container, Data::size_type start, Data::size_type end )
    : cRecordIterator(container,start), mStart(start), mEnd(end)
{
}

CDFASTCALL cRangeIterator::cRangeIterator( cData_ptr& container, Data::size_type start, Data::size_type end, Data::size_type idx )
    : cRecordIterator(container,idx), mStart(start), mEnd(end)
{
}

CDFASTCALL cRangeIterator::cRangeIterator( const cRangeIterator& src )
    : cRecordIterator(src), mStart(src.mStart), mEnd(src.mEnd)
{
}

cRangeIterator& FASTCALL cRangeIterator::operator = ( const cRangeIterator& src )
{
    if ( &src != this )
    {
        cRecordIterator::operator=( src );
        mStart = src.mStart;
        mEnd = src.mEnd;
    }
    return *this;
};
*/

}; // namespace detail

//***********************************************************************
//******    cRecord
//***********************************************************************
CDFASTCALL cRecord::cRecord( const detail::Data::value_type& container, const spFieldDefs& field_defs )
    : mRecord(container), mFieldDefs(field_defs)
{
}

CDFASTCALL cRecord::~cRecord()
{
}

cRecord::cFieldProxy cRecord::FieldByName( const ds_string& field_name )
{
    return cFieldProxy( *mRecord, mFieldDefs->FieldByName( field_name ) );
}

cRecord::cFieldProxy cRecord::FieldByName( const char *field_name )
{
    return FieldByName( ds_string( field_name ) );
}

namespace detail
{

//***********************************************************************
//******    cFieldProxy
//***********************************************************************

//***********************************************************************
//******    cRawFieldProxyHelper
//***********************************************************************
bool FASTCALL cRawFieldProxyHelper::AsBoolean() const
{
    if ( mFieldDef->DataType() == ftBool )
        return ReadBool( *mFieldDef );
    return AsVariant().AsBool();
}

char FASTCALL cRawFieldProxyHelper::AsByte() const
{
    if ( mFieldDef->DataType() == ftByte )
        return ReadByte( *mFieldDef );
    return AsVariant().AsByte();
}

int  FASTCALL cRawFieldProxyHelper::AsInteger() const
{
    if ( mFieldDef->DataType() == ftInteger )
        return ReadInteger( *mFieldDef );
    return AsVariant().AsInt();
}

double FASTCALL cRawFieldProxyHelper::AsDouble() const
{
    if ( mFieldDef->DataType() == ftDouble )
        return ReadFloat( *mFieldDef );
    return AsVariant().AsDouble();
}

dbDateTime FASTCALL cRawFieldProxyHelper::AsDateTime() const
{
    if ( mFieldDef->DataType() == ftDateTime )
        return ReadDateTime( *mFieldDef );
    return AsVariant().AsDateTime();
}

ds_string FASTCALL cRawFieldProxyHelper::AsString() const
{
    if ( mFieldDef->DataType() == ftString )
        return ReadString( *mFieldDef );
    return AsVariant().AsString();
}

void FASTCALL cRawFieldProxyHelper::AsBoolean( bool value )
{
    if ( mFieldDef->DataType() == ftBool )
        WriteBool( *mFieldDef, value );
    else
        AsVariant( Variant( value ) );
}

void FASTCALL cRawFieldProxyHelper::AsByte( char value )
{
    if ( mFieldDef->DataType() == ftByte )
        WriteByte( *mFieldDef, value );
    else
        AsVariant( Variant( value ) );
}

void FASTCALL cRawFieldProxyHelper::AsInteger( int value )
{
    if ( mFieldDef->DataType() == ftInteger )
        WriteInteger( *mFieldDef, value );
    else
        AsVariant( Variant( value ) );
}

void FASTCALL cRawFieldProxyHelper::AsDouble( double value )
{
    if ( mFieldDef->DataType() == ftDouble )
        WriteFloat( *mFieldDef, value );
    else
        AsVariant( Variant( value ) );
}

void FASTCALL cRawFieldProxyHelper::AsDateTime( const dbDateTime& value )
{
    if ( mFieldDef->DataType() == ftDateTime )
        WriteDateTime( *mFieldDef, value );
    else
        AsVariant( Variant( value ) );
}

void FASTCALL cRawFieldProxyHelper::AsString( const ds_string& value )
{
    if ( mFieldDef->DataType() == ftString )
        WriteString( *mFieldDef, value );
    else
        AsVariant( Variant( value ) );
}

//***********************************************************************
//******    cDoubleFieldProxyHelper
//***********************************************************************
bool FASTCALL cDoubleFieldProxyHelper::AsBoolean() const
{
    if ( mFieldDef->DataType() == ftBool )
        return ReadBool( *mFieldDef );
    return AsVariant().AsBool();
}

char FASTCALL cDoubleFieldProxyHelper::AsByte() const
{
    if ( mFieldDef->DataType() == ftByte )
        return ReadByte( *mFieldDef );
    return AsVariant().AsByte();
}

int  FASTCALL cDoubleFieldProxyHelper::AsInteger() const
{
    if ( mFieldDef->DataType() == ftInteger )
        return ReadInteger( *mFieldDef );
    return AsVariant().AsInt();
}

double FASTCALL cDoubleFieldProxyHelper::AsDouble() const
{
    if ( mFieldDef->DataType() == ftDouble )
        return ReadFloat( *mFieldDef );
    return AsVariant().AsDouble();
}

dbDateTime FASTCALL cDoubleFieldProxyHelper::AsDateTime() const
{
    if ( mFieldDef->DataType() == ftDateTime )
        return ReadDateTime( *mFieldDef );
    return AsVariant().AsDateTime();
}

ds_string FASTCALL cDoubleFieldProxyHelper::AsString() const
{
    if ( mFieldDef->DataType() == ftString )
        return ReadString( *mFieldDef );
    return AsVariant().AsString();
}

void FASTCALL cDoubleFieldProxyHelper::AsBoolean( bool value )
{
    if ( mFieldDef->DataType() == ftBool )
        WriteBool( *mFieldDef, value );
    else
        AsVariant( Variant( value ) );
}

void FASTCALL cDoubleFieldProxyHelper::AsByte( char value )
{
    if ( mFieldDef->DataType() == ftByte )
        WriteByte( *mFieldDef, value );
    else
        AsVariant( Variant( value ) );
}

void FASTCALL cDoubleFieldProxyHelper::AsInteger( int value )
{
    if ( mFieldDef->DataType() == ftInteger )
        WriteInteger( *mFieldDef, value );
    else
        AsVariant( Variant( value ) );
}

void FASTCALL cDoubleFieldProxyHelper::AsDouble( double value )
{
    if ( mFieldDef->DataType() == ftDouble )
        WriteFloat( *mFieldDef, value );
    else
        AsVariant( Variant( value ) );
}

void FASTCALL cDoubleFieldProxyHelper::AsDateTime( const dbDateTime& value )
{
    if ( mFieldDef->DataType() == ftDateTime )
        WriteDateTime( *mFieldDef, value );
    else
        AsVariant( Variant( value ) );
}

void FASTCALL cDoubleFieldProxyHelper::AsString( const ds_string& value )
{
    if ( mFieldDef->DataType() == ftString )
        WriteString( *mFieldDef, value );
    else
        AsVariant( Variant( value ) );
}

}; // namespace detail

}; // namespace smds
//---------------------------------------------------------------------------

