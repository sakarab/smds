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

#include "dsVariant.h"
#include "dsExceptions.h"
//---------------------------------------------------------------------------
namespace smds
{

//***********************************************************************
//******    Variant
//***********************************************************************
Variant::Variant( const dbDate& value ) : mVariantType(vtDate), mData(value)                     {}
Variant::Variant( const dbTime& value ) : mVariantType(vtTime), mData(value)                     {}
Variant::Variant( const dbDateTime& value ) : mVariantType(vtDateTime), mData(value)             {}
Variant::Variant( const dbGUID& value ) : mVariantType(vtGUID), mData(value)                     {}
Variant::Variant( const char *value ) : mVariantType(vtString), mData(ds_string( value ))        {}
Variant::Variant( const ds_string& value ) : mVariantType(vtString), mData(value)                {}
Variant::Variant( const wchar_t *value ) : mVariantType(vtWString), mData(ds_wstring( value ))   {}
Variant::Variant( const ds_wstring& value ) : mVariantType(vtWString), mData(value)              {}
Variant::Variant( const var_blob_type& value ) : mVariantType(vtBlob), mData(value)              {}

Variant::Variant( const Variant& src )
    : mVariantType(src.mVariantType), mData(src.mData)
{
}

Variant& Variant::operator = ( const Variant& src )
{
    if ( this != &src )
    {
        mVariantType = src.mVariantType;
        mData = src.mData;
    }
    return *this;
}

Variant::~Variant()
{
}

bool Variant::AsBool() const                          { return strict_get<bool, vtBool>(); }
char Variant::AsByte() const                          { return strict_get<char, vtByte>(); }
short Variant::AsShort() const                        { return strict_get<short, vtShort>(); }
int Variant::AsInt() const                            { return strict_get<int, vtInteger>(); }
long Variant::AsLong() const                          { return strict_get<long, vtLong>(); }
long long Variant::AsLongLong() const                 { return strict_get<long long, vtLongLong>(); }
double Variant::AsDouble() const                      { return strict_get<double, vtDouble>(); }
dbDate Variant::AsDate() const                        { return strict_get<dbDate, vtDate>(); }
dbTime Variant::AsTime() const                        { return strict_get<dbTime, vtTime>(); }
dbDateTime Variant::AsDateTime() const                { return strict_get<dbDateTime, vtDateTime>(); }
dbGUID Variant::AsGUID() const                        { return strict_get<dbGUID, vtGUID>(); }
ds_string Variant::AsString() const                   { return strict_get<ds_string, vtString>(); }

Variant Variant::VarBlobCreate()
{
    Variant     result;

    result.mData = var_blob_type();
    result.mVariantType = vtBlob;
    return result;
}

//***********************************************************************
//******    cVariantStreamBuffer
//***********************************************************************
CDFASTCALL cVariantStreamBuffer::cVariantStreamBuffer( Variant& variant )
    : cAttachedStreamBuffer()
{
    if ( variant.VarType() != vtBlob )
        throw eNotApplicableOperation();
    InitBuffer( &(boost::get<var_blob_type>(variant.mData)) );
}

CDFASTCALL cVariantStreamBuffer::~cVariantStreamBuffer()
{
    DoneBuffer();
}

//***********************************************************************
//******    cVariantStream
//***********************************************************************
CDFASTCALL cVariantStream::cVariantStream( Variant& variant )
    : cStream( shared_ptr<cStreamBuff>( new cVariantStreamBuffer( variant ) ) )
{
}

CDFASTCALL cVariantStream::~cVariantStream()
{
}

};
//---------------------------------------------------------------------------

