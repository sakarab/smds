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

#include "dsRecord.h"
#include "dsExceptions.h"
//---------------------------------------------------------------------------
namespace ds
{

//***********************************************************************
//******    cRawRecordPtr
//***********************************************************************
bool FASTCALL cRawRecordPtr::ReadBool( const cFieldDef& field_def ) const               { return ( mRawBuffer->ReadBool( field_def ) ); }
char FASTCALL cRawRecordPtr::ReadChar( const cFieldDef& field_def ) const               { return ( mRawBuffer->ReadChar( field_def ) ); }
wchar_t FASTCALL cRawRecordPtr::ReadWChar( const cFieldDef& field_def ) const           { return ( mRawBuffer->ReadWChar( field_def ) ); }
short FASTCALL cRawRecordPtr::ReadShort( const cFieldDef& field_def ) const             { return ( mRawBuffer->ReadShort( field_def ) ); }
int FASTCALL cRawRecordPtr::ReadInteger( const cFieldDef& field_def ) const             { return ( mRawBuffer->ReadInteger( field_def ) ); }
long FASTCALL cRawRecordPtr::ReadLong( const cFieldDef& field_def ) const               { return ( mRawBuffer->ReadLong( field_def ) ); }
double FASTCALL cRawRecordPtr::ReadFloat( const cFieldDef& field_def ) const            { return ( mRawBuffer->ReadFloat( field_def ) ); }
cDateTime FASTCALL cRawRecordPtr::ReadDate( const cFieldDef& field_def ) const          { return ( mRawBuffer->ReadDate( field_def ) ); }
ds_string FASTCALL cRawRecordPtr::ReadString( const cFieldDef& field_def ) const        { return ( mRawBuffer->ReadString( field_def ) ); }

void FASTCALL cRawRecordPtr::WriteBool( const cFieldDef& field_def, bool value )                { mRawBuffer->WriteBool( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteChar( const cFieldDef& field_def, char value )                { mRawBuffer->WriteChar( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteWChar( const cFieldDef& field_def, wchar_t value )            { mRawBuffer->WriteWChar( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteShort( const cFieldDef& field_def, short value )              { mRawBuffer->WriteShort( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteInteger( const cFieldDef& field_def, int value )              { mRawBuffer->WriteInteger( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteLong( const cFieldDef& field_def, long value )                { mRawBuffer->WriteLong( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteFloat( const cFieldDef& field_def, double value )             { mRawBuffer->WriteFloat( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteDate( const cFieldDef& field_def, const cDateTime& value )    { mRawBuffer->WriteDate( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteString( const cFieldDef& field_def, const ds_string& value )  { mRawBuffer->WriteString( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteString( const cFieldDef& field_def, const char *value )       { mRawBuffer->WriteString( field_def, value ); }

bool FASTCALL cRawRecordPtr::ReadBool( const cFieldDef_& field_def ) const               { return ( mRawBuffer->ReadBool( field_def ) ); }
char FASTCALL cRawRecordPtr::ReadChar( const cFieldDef_& field_def ) const               { return ( mRawBuffer->ReadChar( field_def ) ); }
wchar_t FASTCALL cRawRecordPtr::ReadWChar( const cFieldDef_& field_def ) const           { return ( mRawBuffer->ReadWChar( field_def ) ); }
short FASTCALL cRawRecordPtr::ReadShort( const cFieldDef_& field_def ) const             { return ( mRawBuffer->ReadShort( field_def ) ); }
int FASTCALL cRawRecordPtr::ReadInteger( const cFieldDef_& field_def ) const             { return ( mRawBuffer->ReadInteger( field_def ) ); }
long FASTCALL cRawRecordPtr::ReadLong( const cFieldDef_& field_def ) const               { return ( mRawBuffer->ReadLong( field_def ) ); }
double FASTCALL cRawRecordPtr::ReadFloat( const cFieldDef_& field_def ) const            { return ( mRawBuffer->ReadFloat( field_def ) ); }
cDateTime FASTCALL cRawRecordPtr::ReadDate( const cFieldDef_& field_def ) const          { return ( mRawBuffer->ReadDate( field_def ) ); }
ds_string FASTCALL cRawRecordPtr::ReadString( const cFieldDef_& field_def ) const        { return ( mRawBuffer->ReadString( field_def ) ); }

void FASTCALL cRawRecordPtr::WriteBool( const cFieldDef_& field_def, bool value )                { mRawBuffer->WriteBool( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteChar( const cFieldDef_& field_def, char value )                { mRawBuffer->WriteChar( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteWChar( const cFieldDef_& field_def, wchar_t value )            { mRawBuffer->WriteWChar( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteShort( const cFieldDef_& field_def, short value )              { mRawBuffer->WriteShort( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteInteger( const cFieldDef_& field_def, int value )              { mRawBuffer->WriteInteger( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteLong( const cFieldDef_& field_def, long value )                { mRawBuffer->WriteLong( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteFloat( const cFieldDef_& field_def, double value )             { mRawBuffer->WriteFloat( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteDate( const cFieldDef_& field_def, const cDateTime& value )    { mRawBuffer->WriteDate( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteString( const cFieldDef_& field_def, const ds_string& value )  { mRawBuffer->WriteString( field_def, value ); }
void FASTCALL cRawRecordPtr::WriteString( const cFieldDef_& field_def, const char *value )       { mRawBuffer->WriteString( field_def, value ); }

//***********************************************************************
//******    cRecordPtr
//***********************************************************************
bool FASTCALL cRecordPtr::IsNull( const cFieldDef& field_def ) const            { return ( mBuffer->IsNull( field_def ) ); }
bool FASTCALL cRecordPtr::IsNull( const cFieldDef_& field_def ) const           { return ( mBuffer->IsNull( field_def ) ); }
void FASTCALL cRecordPtr::Nullify( const cFieldDef& field_def )                 { mBuffer->Nullify( field_def ); }

bool FASTCALL cRecordPtr::ReadBool( const cFieldDef& field_def ) const          { return ( mBuffer->ReadBool( field_def ) ); }
char FASTCALL cRecordPtr::ReadChar( const cFieldDef& field_def ) const          { return ( mBuffer->ReadChar( field_def ) ); }
wchar_t FASTCALL cRecordPtr::ReadWChar( const cFieldDef& field_def ) const      { return ( mBuffer->ReadWChar( field_def ) ); }
short FASTCALL cRecordPtr::ReadShort( const cFieldDef& field_def ) const        { return ( mBuffer->ReadShort( field_def ) ); }
int FASTCALL cRecordPtr::ReadInteger( const cFieldDef& field_def ) const        { return ( mBuffer->ReadInteger( field_def ) ); }
long FASTCALL cRecordPtr::ReadLong( const cFieldDef& field_def ) const          { return ( mBuffer->ReadLong( field_def ) ); }
double FASTCALL cRecordPtr::ReadFloat( const cFieldDef& field_def ) const       { return ( mBuffer->ReadFloat( field_def ) ); }
cDateTime FASTCALL cRecordPtr::ReadDate( const cFieldDef& field_def ) const     { return ( mBuffer->ReadDate( field_def ) ); }
ds_string FASTCALL cRecordPtr::ReadString( const cFieldDef& field_def ) const   { return ( mBuffer->ReadString( field_def ) ); }

void FASTCALL cRecordPtr::WriteBool( const cFieldDef& field_def, bool value )               { mBuffer->WriteBool( field_def, value ); }
void FASTCALL cRecordPtr::WriteChar( const cFieldDef& field_def, char value )               { mBuffer->WriteChar( field_def, value ); }
void FASTCALL cRecordPtr::WriteWChar( const cFieldDef& field_def, wchar_t value )           { mBuffer->WriteWChar( field_def, value ); }
void FASTCALL cRecordPtr::WriteShort( const cFieldDef& field_def, short value )             { mBuffer->WriteShort( field_def, value ); }
void FASTCALL cRecordPtr::WriteInteger( const cFieldDef& field_def, int value )             { mBuffer->WriteInteger( field_def, value ); }
void FASTCALL cRecordPtr::WriteLong( const cFieldDef& field_def, long value )               { mBuffer->WriteLong( field_def, value ); }
void FASTCALL cRecordPtr::WriteFloat( const cFieldDef& field_def, double value )            { mBuffer->WriteFloat( field_def, value ); }
void FASTCALL cRecordPtr::WriteDate( const cFieldDef& field_def, const cDateTime& value )   { mBuffer->WriteDate( field_def, value ); }
void FASTCALL cRecordPtr::WriteString( const cFieldDef& field_def, const ds_string& value ) { mBuffer->WriteString( field_def, value ); }
void FASTCALL cRecordPtr::WriteString( const cFieldDef& field_def, const char *value )      { mBuffer->WriteString( field_def, value ); }

bool FASTCALL cRecordPtr::ReadBool( const cFieldDef_& field_def ) const          { return ( mBuffer->ReadBool( field_def ) ); }
char FASTCALL cRecordPtr::ReadChar( const cFieldDef_& field_def ) const          { return ( mBuffer->ReadChar( field_def ) ); }
wchar_t FASTCALL cRecordPtr::ReadWChar( const cFieldDef_& field_def ) const      { return ( mBuffer->ReadWChar( field_def ) ); }
short FASTCALL cRecordPtr::ReadShort( const cFieldDef_& field_def ) const        { return ( mBuffer->ReadShort( field_def ) ); }
int FASTCALL cRecordPtr::ReadInteger( const cFieldDef_& field_def ) const        { return ( mBuffer->ReadInteger( field_def ) ); }
long FASTCALL cRecordPtr::ReadLong( const cFieldDef_& field_def ) const          { return ( mBuffer->ReadLong( field_def ) ); }
double FASTCALL cRecordPtr::ReadFloat( const cFieldDef_& field_def ) const       { return ( mBuffer->ReadFloat( field_def ) ); }
cDateTime FASTCALL cRecordPtr::ReadDate( const cFieldDef_& field_def ) const     { return ( mBuffer->ReadDate( field_def ) ); }
ds_string FASTCALL cRecordPtr::ReadString( const cFieldDef_& field_def ) const   { return ( mBuffer->ReadString( field_def ) ); }

void FASTCALL cRecordPtr::WriteBool( const cFieldDef_& field_def, bool value )               { mBuffer->WriteBool( field_def, value ); }
void FASTCALL cRecordPtr::WriteChar( const cFieldDef_& field_def, char value )               { mBuffer->WriteChar( field_def, value ); }
void FASTCALL cRecordPtr::WriteWChar( const cFieldDef_& field_def, wchar_t value )           { mBuffer->WriteWChar( field_def, value ); }
void FASTCALL cRecordPtr::WriteShort( const cFieldDef_& field_def, short value )             { mBuffer->WriteShort( field_def, value ); }
void FASTCALL cRecordPtr::WriteInteger( const cFieldDef_& field_def, int value )             { mBuffer->WriteInteger( field_def, value ); }
void FASTCALL cRecordPtr::WriteLong( const cFieldDef_& field_def, long value )               { mBuffer->WriteLong( field_def, value ); }
void FASTCALL cRecordPtr::WriteFloat( const cFieldDef_& field_def, double value )            { mBuffer->WriteFloat( field_def, value ); }
void FASTCALL cRecordPtr::WriteDate( const cFieldDef_& field_def, const cDateTime& value )   { mBuffer->WriteDate( field_def, value ); }
void FASTCALL cRecordPtr::WriteString( const cFieldDef_& field_def, const ds_string& value ) { mBuffer->WriteString( field_def, value ); }
void FASTCALL cRecordPtr::WriteString( const cFieldDef_& field_def, const char *value )      { mBuffer->WriteString( field_def, value ); }

//***********************************************************************
//******    cRecordIterator
//***********************************************************************
CDFASTCALL cRecordIterator::cRecordIterator( cData_ptr& container )
    : mIdx(0), mContainer(container)
{
}

CDFASTCALL cRecordIterator::cRecordIterator( cData_ptr& container, cData::size_type idx )
    : mIdx(idx), mContainer(container)
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

cDoubleBuffer * FASTCALL cRecordIterator::GetDoubleBuffer() const
{
    return ( (*mContainer)[mIdx].get() );
}

detail::cFieldProxy FASTCALL cRecordIterator::FieldByName( const ds_string& field_name )
{
    return ( detail::cFieldProxy( GetDoubleBuffer()->GetActiveData(), mContainer->FieldByName( field_name ) ) );
}

detail::cFieldProxy FASTCALL cRecordIterator::FieldByName( const char *field_name )
{
    return ( FieldByName( ds_string( field_name ) ) );
}

//***********************************************************************
//******    cRangeIterator
//***********************************************************************
CDFASTCALL cRangeIterator::cRangeIterator( cData_ptr& container, cData::size_type start, cData::size_type end )
    : cRecordIterator(container,start), mStart(start), mEnd(end)
{
}

CDFASTCALL cRangeIterator::cRangeIterator( const cRangeIterator& src )
    : cRecordIterator(src), mStart(src.mStart), mEnd(src.mEnd)
{
}

//***********************************************************************
//******    cRecord
//***********************************************************************
CDFASTCALL cRecord::cRecord( const cData::value_type& container, const cFieldDefs_ptr& field_defs )
    : mRecord(container), mFieldDefs(field_defs)
{
}

CDFASTCALL cRecord::~cRecord()
{
}

detail::cFieldProxy cRecord::FieldByName( const ds_string& field_name )
{
    return ( detail::cFieldProxy( mRecord->GetActiveData(), mFieldDefs->FieldByName( field_name ) ) );
}

detail::cFieldProxy cRecord::FieldByName( const char *field_name )
{
    return ( FieldByName( ds_string( field_name ) ) );
}

namespace detail
{

//***********************************************************************
//******    cFieldProxy
//***********************************************************************

//***********************************************************************
//******    cFieldProxyRecordHelper
//***********************************************************************
bool FASTCALL cFieldProxyRecordHelper::AsBoolean() const
{
    return ( AsVariant().AsBool() );
}

void FASTCALL cFieldProxyRecordHelper::AsBoolean( bool value )
{
    AsVariant( Variant( value ) );
}

char FASTCALL cFieldProxyRecordHelper::AsChar() const
{
    return ( AsVariant().AsChar() );
}

void FASTCALL cFieldProxyRecordHelper::AsChar( char value )
{
    AsVariant( Variant( value ) );
}

int  FASTCALL cFieldProxyRecordHelper::AsInteger() const
{
    return ( AsVariant().AsInt() );
}

void FASTCALL cFieldProxyRecordHelper::AsInteger( int value )
{
    AsVariant( Variant( value ) );
}

double  FASTCALL cFieldProxyRecordHelper::AsDouble() const
{
    return ( AsVariant().AsDouble() );
}

void FASTCALL cFieldProxyRecordHelper::AsDouble( double value )
{
    AsVariant( Variant( value ) );
}

cDateTime FASTCALL cFieldProxyRecordHelper::AsDateTime() const
{
    return ( AsVariant().AsDateTime() );
}

void FASTCALL cFieldProxyRecordHelper::AsDateTime( const cDateTime& value )
{
    AsVariant( Variant( value ) );
}

ds_string FASTCALL cFieldProxyRecordHelper::AsString() const
{
    return ( AsVariant().AsString() );
}

void FASTCALL cFieldProxyRecordHelper::AsString( const ds_string& value )
{
    AsVariant( Variant( value ) );
}

};

};
//---------------------------------------------------------------------------

