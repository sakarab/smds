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
namespace ds
{

//***********************************************************************
//******    Variant
//***********************************************************************
CDFASTCALL Variant::Variant( const cDateTime& value )
    : mVariantType(vtDateTime), mData(value)
{
}

CDFASTCALL Variant::Variant( const ds_string& value )
    : mVariantType(vtString), mData(value)
{
}

CDFASTCALL Variant::Variant( const ds_wstring& value )
    : mVariantType(vtWString), mData(value)
{
}

CDFASTCALL Variant::Variant( const Variant& src )
    : mVariantType(src.mVariantType)
{
    ConstructByType( src );
}

Variant& FASTCALL Variant::operator = ( const Variant& src )
{
    if ( this != &src )
    {
        DestructByType();
        ConstructByType( src );
        mVariantType = src.mVariantType;
    }
    return ( *this );
}

CDFASTCALL Variant::~Variant()
{
    DestructByType();
}

void FASTCALL Variant::ConstructByType( const Variant& src )             // the source type
{
    switch ( src.mVariantType )
    {
        case vtNull     :                                                       break;
        case vtBool     : mData.mBool = src.mData.mBool;                        break;
        case vtChar     : mData.mChar = src.mData.mChar;                        break;
        case vtWChar    : mData.mWChar = src.mData.mWChar;                      break;
        case vtShort    : mData.mShort = src.mData.mShort;                      break;
        case vtInteger  : mData.mInt = src.mData.mInt;                          break;
        case vtLong     : mData.mLong = src.mData.mLong;                        break;
        case vtDouble   : mData.mDouble = src.mData.mDouble;                    break;
        case vtDateTime : mData.ConstructDateTime( src.mData.GetDateTime() );   break;
        case vtString   : mData.ConstructString( src.mData.GetString() );       break;
        case vtWString  : mData.ConstructWString( src.mData.GetWString() );     break;
        case vtBlob     : mData.ConstructBlob( src.mData.GetBlob() );           break;
        default         : throw eVariantConversion();
    }
}

void FASTCALL Variant::DestructByType()                                  // "this" type
{
    switch ( mVariantType )
    {
        case vtNull     :                               break;
        case vtBool     :                               break;
        case vtChar     :                               break;
        case vtWChar    :                               break;
        case vtShort    :                               break;
        case vtInteger  :                               break;
        case vtLong     :                               break;
        case vtDouble   :                               break;
        case vtDateTime : mData.DestructDateTime();     break;
        case vtString   : mData.DestructString();       break;
        case vtWString  : mData.DestructWString();      break;
        case vtBlob     : mData.DestructBlob();         break;
        default         : throw eVariantConversion();
    }
}

long FASTCALL Variant::ToLongType() const
{
    switch ( mVariantType )
    {
        //case vtNull     : throw eVariantConversion();
        case vtBool     : return ( mData.mBool );
        case vtChar     : return ( mData.mChar );
        case vtWChar    : return ( mData.mWChar );
        case vtShort    : return ( mData.mShort );
        case vtInteger  : return ( mData.mInt );
        case vtLong     : return ( mData.mLong );
        case vtDouble   : return ( static_cast<long>(mData.mDouble) );
        case vtDateTime : return ( static_cast<long>(mData.GetDateTime().AsDouble()) );
        case vtString   : return ( StringToLong( mData.GetString() ) );
        case vtWString  : return ( StringToLong( WStringToString( mData.GetWString() ) ) );
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

    return ( result );
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

    return ( result );
}

ds_wstring Variant::StringToWString( const ds_string& sstr ) const
{
    int                             sstr_len = sstr.size();
    boost::scoped_array<wchar_t>    buff( new wchar_t[sstr_len + 1] );
    wchar_t                         *dst = buff.get();
    const char                      *src = sstr.c_str();

    for ( int n = 0 ; n < sstr_len ; ++n )
        *dst++ = *src++;
    *dst = 0;

    return ( ds_wstring( buff.get() ) );
}

ds_string Variant::WStringToString( const ds_wstring& sstr ) const
{
    int                             sstr_len = sstr.size();
    boost::scoped_array<char>       buff( new char[sstr_len + 1] );
    char                            *dst = buff.get();
    const wchar_t                   *src = sstr.c_str();

    for ( int n = 0 ; n < sstr_len ; ++n )
        *dst++ = static_cast<char>(*src++);
    *dst = 0;

    return ( ds_string( buff.get() ) );
}

double FASTCALL Variant::AsDouble() const
{
    switch ( mVariantType )
    {
        case vtDouble   : return ( mData.mDouble );
        case vtDateTime : return ( mData.GetDateTime().AsDouble() );
        case vtString   : return ( StringToDouble( mData.GetString() ) );
        case vtWString  : return ( StringToDouble( WStringToString( mData.GetWString() ) ) );
        case vtBlob     : throw eVariantConversion();
        default         : return ( ToLongType() );
    }
}

cDateTime FASTCALL Variant::AsDateTime() const
{
    switch ( mVariantType )
    {
        case vtDouble   : return ( cDateTime( mData.mDouble ) );
        case vtDateTime : return ( mData.GetDateTime() );
        case vtString   : throw eVariantConversion();
        case vtWString  : throw eVariantConversion();
        case vtBlob     : throw eVariantConversion();
        default         : return ( cDateTime( ToLongType() ) );
    }
}

ds_string FASTCALL Variant::AsString() const
{
    switch ( mVariantType )
    {
        case vtString   : return ( mData.GetString() );
        default         : throw eVariantConversion();
    }
}

Variant FASTCALL Variant::VarBlobCreate()
{
    Variant     result;

    result.mData.ConstructBlob( std::vector<char>() );
    result.mVariantType = vtBlob;
    return ( result );
}

//***********************************************************************
//******    cVariantStreamBuffer
//***********************************************************************
CDFASTCALL cVariantStreamBuffer::cVariantStreamBuffer( Variant& variant )
    : cAttachedStreamBuffer()
{
    if ( variant.VarType() != vtBlob )
        throw eNotApplicableOperation();
    InitBuffer( &(variant.mData.GetBlob()) );
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

