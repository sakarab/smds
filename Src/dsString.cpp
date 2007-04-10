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

#include "dsString.h"
#include <boost/scoped_array.hpp>
//---------------------------------------------------------------------------
namespace ds
{

//***********************************************************************
//******    string_tag
//***********************************************************************
const string_tag::size_type string_tag::npos = 0xFFFFFFFF;

CDFASTCALL string_tag::string_tag()
    : mStr()
{
}

CDFASTCALL string_tag::string_tag( const value_type *str )
    : mStr(str)
{
}

CDFASTCALL string_tag::string_tag( const value_type *str, const size_type count )
    : mStr(str, count)
{
}

CDFASTCALL string_tag::string_tag( const value_type *str, const size_type start_idx, const size_type count )
    : mStr(str, start_idx, count)
{
}

CDFASTCALL string_tag::string_tag( const size_type count, const value_type str )
    : mStr(count, str)
{
}

CDFASTCALL string_tag::string_tag( const string_tag& src )
    : mStr(src.mStr)
{
}

CDFASTCALL string_tag::~string_tag()
{
}

void FASTCALL string_tag::swap( string_tag& src )
{
    mStr.swap( src.mStr );
}

string_tag& FASTCALL string_tag::assign( const string_tag& s, size_type pos, size_type n )
{
    mStr.assign( s.mStr, pos, n );
    return ( *this );
}

string_tag& FASTCALL string_tag::assign( const value_type *s, size_type n )
{
    mStr.assign( s, n );
    return ( *this );
}

string_tag& FASTCALL string_tag::append( const value_type* src )
{
    mStr.append( src );
    return ( *this );
}

string_tag& FASTCALL string_tag::append( const value_type* src, size_type count )
{
    mStr.append( src, count );
    return ( *this );
}

string_tag& FASTCALL string_tag::append( const string_tag& src, size_type offset, size_type count )
{
    mStr.append( src.mStr, offset, count );
    return ( *this );
}

string_tag& FASTCALL string_tag::append( const string_tag& src )
{
    mStr.append( src.mStr );
    return ( *this );
}

string_tag& FASTCALL string_tag::append( size_type count, value_type ch )
{
    mStr.append( count, ch );
    return ( *this );
}

string_tag& FASTCALL string_tag::operator += ( const string_tag& src )
{
    mStr += src.mStr;
    return ( *this );
}

string_tag& FASTCALL string_tag::operator += ( const value_type *src )
{
    mStr += src;
    return ( *this );
}

string_tag& FASTCALL string_tag::operator += ( value_type src )
{
    mStr += src;
    return ( *this );
}

string_tag& FASTCALL string_tag::erase( size_type pos, size_type n )
{
    mStr.erase( pos, n );
    return ( *this );
}

string_tag::iterator FASTCALL string_tag::erase( iterator p )
{
    return ( mStr.erase( p ) );
}

string_tag::iterator FASTCALL string_tag::erase( iterator first, iterator last )
{
    return ( mStr.erase( first, last ) );
}

//---------------------------------------------------------------------------

string_tag FASTCALL operator + ( const string_tag& lhs, const string_tag& rhs )
{
    string_tag  str( lhs );

    str.mStr += rhs.mStr;
    return ( str );
}

string_tag FASTCALL operator + ( const string_tag::value_type *lhs, const string_tag& rhs )
{
    string_tag  str( lhs );

    str.mStr += rhs.mStr;
    return ( str );
}

string_tag FASTCALL operator + ( string_tag::value_type lhs, const string_tag& rhs )
{
    string_tag  str( 1, lhs );

    str.mStr += rhs.mStr;
    return ( str );
}

string_tag FASTCALL operator + ( const string_tag& lhs, const string_tag::value_type *rhs )
{
    string_tag  str( lhs );

    str.mStr += rhs;
    return ( str );
}

string_tag FASTCALL operator + ( const string_tag& lhs, string_tag::value_type rhs )
{
    string_tag  str( lhs );

    str.mStr += rhs;
    return ( str );
}

bool FASTCALL operator < ( const string_tag& lhs, const string_tag& rhs )
{
    return ( lhs.mStr < rhs.mStr );
}

bool FASTCALL operator < ( const string_tag& lhs, const string_tag::value_type *rhs )
{
    return ( lhs.mStr < rhs );
}

bool FASTCALL operator == ( const string_tag& lhs, const string_tag& rhs )
{
    return ( lhs.mStr == rhs.mStr );
}

bool FASTCALL operator != ( const string_tag& lhs, const string_tag& rhs )
{
    return ( lhs.mStr != rhs.mStr );
}

//-- IO --
cStream& FASTCALL operator << ( cStream& st, const string_tag& a )
{
    string_tag::size_type    size = a.size();

    st << size;
    if ( size != 0 )
        st.WriteBuffer( a.c_str(), size );
    return ( st );
}

cStream& FASTCALL operator >> ( cStream& st, string_tag& a )
{
    string_tag::size_type   size;

    st >> size;
    if ( size != 0 )
    {
        boost::scoped_array<char>   buffer( new char[size + 1] );

        st.ReadBuffer( buffer.get(), size );
        buffer[size] = 0;
        a = buffer.get();
    }
    return ( st );
}

//***********************************************************************
//******    wstring_tag
//***********************************************************************
CDFASTCALL wstring_tag::wstring_tag()
    : mStr()
{
}

CDFASTCALL wstring_tag::wstring_tag( const value_type *str )
    : mStr(str)
{
}

CDFASTCALL wstring_tag::wstring_tag( const wstring_tag& src )
    : mStr(src.mStr)
{
}

CDFASTCALL wstring_tag::~wstring_tag()
{
}

wstring_tag::value_type FASTCALL wstring_tag::operator []( size_type idx ) const
{
    return ( mStr[idx] );
}

//***********************************************************************
//******    StringBuilder
//***********************************************************************
//CDFASTCALL StringBuilder::StringBuilder()
//    : mStream()
//{
//}
//
//CDFASTCALL StringBuilder::StringBuilder( const string_tag& src )
//    : mStream( src.c_str() )
//{
//}
//
//CDFASTCALL StringBuilder::StringBuilder( const char *src )
//    : mStream( src )
//{
//}
//
//CDFASTCALL StringBuilder::~StringBuilder()
//{
//}
//
//string_tag FASTCALL StringBuilder::str()
//{
//    return ( mStream.str().c_str() );
//}
//
//StringBuilder& FASTCALL StringBuilder::operator << ( int value )
//{
//}
//
//StringBuilder& FASTCALL StringBuilder::operator << ( const string_tag& value )
//{
//}
//
//StringBuilder& FASTCALL StringBuilder::operator << ( const char *value )
//{
//}

};
//---------------------------------------------------------------------------

