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
#include <boost/smart_ptr.hpp>
#include <cmath>
//---------------------------------------------------------------------------
namespace smds
{

//***********************************************************************
//******    Variant
//***********************************************************************
CDFASTCALL Variant::Variant( const dbDate& value ) : mVariantType(vtDate), mData(value)                     {}
CDFASTCALL Variant::Variant( const dbTime& value ) : mVariantType(vtTime), mData(value)                     {}
CDFASTCALL Variant::Variant( const dbDateTime& value ) : mVariantType(vtDateTime), mData(value)             {}
CDFASTCALL Variant::Variant( const dbGUID& value ) : mVariantType(vtGUID), mData(value)                     {}
CDFASTCALL Variant::Variant( const char *value ) : mVariantType(vtString), mData(ds_string( value ))        {}
CDFASTCALL Variant::Variant( const ds_string& value ) : mVariantType(vtString), mData(value)                {}
CDFASTCALL Variant::Variant( const wchar_t *value ) : mVariantType(vtWString), mData(ds_wstring( value ))   {}
CDFASTCALL Variant::Variant( const ds_wstring& value ) : mVariantType(vtWString), mData(value)              {}
CDFASTCALL Variant::Variant( const var_blob_type& value ) : mVariantType(vtBlob), mData(value)              {}

CDFASTCALL Variant::Variant( const Variant& src )
    : mVariantType(src.mVariantType), mData(src.mData)
{
}

Variant& FASTCALL Variant::operator = ( const Variant& src )
{
    if ( this != &src )
    {
        mVariantType = src.mVariantType;
        mData = src.mData;
    }
    return *this;
}

CDFASTCALL Variant::~Variant()
{
}

long FASTCALL Variant::ToLongType() const
{
    switch ( mVariantType )
    {
        //case vtNull     : throw eVariantConversion();
        case vtBool     : return boost::get<bool>( mData );
        case vtByte     : return boost::get<char>( mData );
        case vtShort    : return boost::get<short>( mData );
        case vtInteger  : return boost::get<int>( mData );
        case vtLong     : return boost::get<long>( mData );
        case vtLongLong : return boost::get<long long>( mData );
        case vtDouble   : return boost::get<double>( mData );
        case vtDate     : return boost::get<dbDate>( mData ).AsInternal();
        case vtTime     : return boost::get<dbTime>( mData ).AsInternal();
        //case vtDateTime : return boost::get<dbDateTime>( mData ).AsInternal();
        //case vtGUID     : throw eVariantConversion();
        case vtString   : return StringToLong( boost::get<ds_string>( mData ) );
        //case vtWString  : return StringToLong( WStringToString( mData.GetWString() ) );
        //case vtBlob     : throw eVariantConversion();
        default         : throw eVariantConversion();
    }
}

long long FASTCALL Variant::ToLongLongType() const
{
    switch ( mVariantType )
    {
        //case vtNull     : throw eVariantConversion();
        case vtBool     : return boost::get<bool>( mData );
        case vtByte     : return boost::get<char>( mData );
        case vtShort    : return boost::get<short>( mData );
        case vtInteger  : return boost::get<int>( mData );
        case vtLong     : return boost::get<long>( mData );
        case vtLongLong : return boost::get<long long>( mData );
        case vtDouble   : return boost::get<double>( mData );
        case vtDate     : return boost::get<dbDate>( mData ).AsInternal();
        case vtTime     : return boost::get<dbTime>( mData ).AsInternal();
        case vtDateTime : return static_cast<long long>(boost::get<dbDateTime>( mData ).AsDouble());
        //case vtGUID     : throw eVariantConversion();
        //case vtString   : return StringToLong( mData.GetString() );
        //case vtWString  : return StringToLong( WStringToString( mData.GetWString() ) );
        //case vtBlob     : throw eVariantConversion();
        default         : throw eVariantConversion();
    }
}

long FASTCALL Variant::StringToLong( const ds_string& sstr ) const
{
    if ( sstr.empty() )
        throw eVariantConversion();

    int                         sstr_len = sstr.size();
    boost::scoped_array<char>   str( new char[sstr_len + 1] );

    std::strcpy( str.get(), sstr.c_str() );

    char                        *end_ptr = str.get();
    long                        result = std::strtol( str.get(), &end_ptr, 10 );

    if ( end_ptr != (str.get() + sstr_len ) )
        throw eVariantConversion();

    return result;
}

double FASTCALL Variant::StringToDouble( const ds_string& sstr ) const
{
    if ( sstr.empty() )
        throw eVariantConversion();

    int                         sstr_len = sstr.size();
    boost::scoped_array<char>   str( new char[sstr_len + 1] );

    std::strcpy( str.get(), sstr.c_str() );

    char                        *end_ptr = str.get();
    double                      result = std::strtod( str.get(), &end_ptr );

#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0570 )
    if ( end_ptr != (str.get() + sstr_len ) || result == +std::HUGE_VAL || result == -std::HUGE_VAL )
#else
    if ( end_ptr != (str.get() + sstr_len ) || result == +HUGE_VAL || result == -HUGE_VAL )
#endif
        throw eVariantConversion();

    return result;
}

//ds_wstring Variant::StringToWString( const ds_string& sstr ) const
//{
//    int                             sstr_len = sstr.size();
//    boost::scoped_array<wchar_t>    buff( new wchar_t[sstr_len + 1] );
//    wchar_t                         *dst = buff.get();
//    const char                      *src = sstr.c_str();
//
//    for ( int n = 0 ; n < sstr_len ; ++n )
//        *dst++ = *src++;
//    *dst = 0;
//
//    return ds_wstring( buff.get() );
//}

//ds_string Variant::WStringToString( const ds_wstring& sstr ) const
//{
//    int                             sstr_len = sstr.size();
//    boost::scoped_array<char>       buff( new char[sstr_len + 1] );
//    char                            *dst = buff.get();
//    const wchar_t                   *src = sstr.c_str();
//
//    for ( int n = 0 ; n < sstr_len ; ++n )
//        *dst++ = static_cast<char>(*src++);
//    *dst = 0;
//
//    return ds_string( buff.get() );
//}

double FASTCALL Variant::AsDouble() const
{
    switch ( mVariantType )
    {
        //case vtNull     : throw eVariantConversion();
        case vtBool     : return boost::get<bool>( mData );
        case vtByte     : return boost::get<char>( mData );
        case vtShort    : return boost::get<short>( mData );
        case vtInteger  : return boost::get<int>( mData );
        case vtLong     : return boost::get<long>( mData );
        case vtLongLong : return boost::get<long long>( mData );
        case vtDouble   : return boost::get<double>( mData );
        case vtDate     : return boost::get<dbDate>( mData ).AsInternal();
        case vtTime     : return boost::get<dbTime>( mData ).AsInternal();
        case vtDateTime : return boost::get<dbDateTime>( mData ).AsDouble();
        //case vtGUID     : throw eVariantConversion();
        case vtString   : return StringToDouble( boost::get<ds_string>( mData ) );
        // case vtWString  : return StringToDouble( WStringToString( mData.GetWString() ) );
        // case vtBlob     : throw eVariantConversion();
        default         : throw eVariantConversion();
    }
}

dbDate FASTCALL Variant::AsDate() const
{
    switch ( mVariantType )
    {
        case vtDate     : return boost::get<dbDate>( mData );
        default         : throw eVariantConversion();
    }
}

dbTime FASTCALL Variant::AsTime() const
{
    switch ( mVariantType )
    {
        case vtTime     : return boost::get<dbTime>( mData );
        default         : throw eVariantConversion();
    }
}

dbDateTime FASTCALL Variant::AsDateTime() const
{
    switch ( mVariantType )
    {
        case vtDateTime : return boost::get<dbDateTime>( mData );
        default         : throw eVariantConversion();
    }
}

dbGUID FASTCALL Variant::AsGUID() const
{
    switch ( mVariantType )
    {
        case vtGUID     : return boost::get<dbGUID>( mData );
        default         : throw eVariantConversion();
    }
}

ds_string FASTCALL Variant::AsString() const
{
    switch ( mVariantType )
    {
        case vtString   : return boost::get<ds_string>( mData );
        default         : throw eVariantConversion();
    }
}

Variant FASTCALL Variant::VarBlobCreate()
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

