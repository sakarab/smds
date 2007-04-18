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
#ifndef SM_DS_STRING_H
#define SM_DS_STRING_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include <string>
#include "dsStream.h"
//---------------------------------------------------------------------------

namespace smds
{

//***********************************************************************
//******    string_tag
//***********************************************************************
class string_tag
{
public:
    typedef std::string                 string_type;
    typedef string_type::value_type     value_type;
    typedef string_type::size_type      size_type;
    typedef string_type::iterator       iterator;
private:
    friend string_tag FASTCALL operator + ( const string_tag& lhs, const string_tag& rhs );
    friend string_tag FASTCALL operator + ( const string_tag::value_type *lhs, const string_tag& rhs );
    friend string_tag FASTCALL operator + ( string_tag::value_type lhs, const string_tag& rhs );
    friend string_tag FASTCALL operator + ( const string_tag& lhs, const string_tag::value_type *rhs );
    friend string_tag FASTCALL operator + ( const string_tag& lhs, string_tag::value_type rhs );
    friend bool       FASTCALL operator < ( const string_tag& lhs, const string_tag& rhs );
    friend bool       FASTCALL operator < ( const string_tag& lhs, const string_tag::value_type *rhs );
    friend bool       FASTCALL operator == ( const string_tag& lhs, const string_tag& rhs );
    friend bool       FASTCALL operator != ( const string_tag& lhs, const string_tag& rhs );
    std::string     mStr;
public:
    CDFASTCALL string_tag();
    CDFASTCALL string_tag( const value_type *str );
    CDFASTCALL string_tag( const value_type *str, const size_type count );
    CDFASTCALL string_tag( const value_type *str, const size_type start_idx, const size_type count );
    CDFASTCALL string_tag( const size_type count, const value_type str );
    CDFASTCALL string_tag( const string_tag& src );
    CDFASTCALL ~string_tag();
    void FASTCALL swap( string_tag& src );

    string_tag& FASTCALL assign( const string_tag& s, size_type pos, size_type n );
    string_tag& FASTCALL assign( const value_type *s, size_type n );

    string_tag& FASTCALL operator += ( const string_tag& src );
    string_tag& FASTCALL operator += ( const value_type *src );
    string_tag& FASTCALL operator += ( value_type src );

    value_type FASTCALL operator []( size_type idx ) const          { return ( mStr[idx] ); }

    string_tag& FASTCALL append( const value_type* src );
    string_tag& FASTCALL append( const value_type* src, size_type count );
    string_tag& FASTCALL append( const string_tag& src, size_type offset, size_type count );
    string_tag& FASTCALL append( const string_tag& src );
    string_tag& FASTCALL append( size_type count, value_type ch );

    string_tag& FASTCALL erase( size_type pos = 0, size_type n = npos );
    iterator FASTCALL erase( iterator p );
    iterator FASTCALL erase( iterator first, iterator last );

    //basic_string& insert( size_type _P0, const value_type* _Ptr );
    //basic_string& insert( size_type _P0, const value_type* _Ptr, size_type _Count );
    //basic_string& insert( size_type _P0, const basic_string& _Str );
    //basic_string& insert( size_type _P0, const basic_string& _Str, size_type _Off, size_type _Count );
    //basic_string& insert( size_type _P0, size_type _Count, value_type _Ch );
    //iterator insert( iterator _It, value_type _Ch = value_type( ) );

    bool FASTCALL empty() const                                     { return ( mStr.empty() ); }
    size_type FASTCALL size() const                                 { return ( mStr.size() ); }
    const value_type * FASTCALL c_str() const                       { return ( mStr.c_str() ); }

    static const size_type npos;
};

string_tag FASTCALL operator + ( const string_tag& lhs, const string_tag& rhs );
string_tag FASTCALL operator + ( const string_tag::value_type *lhs, const string_tag& rhs );
string_tag FASTCALL operator + ( string_tag::value_type lhs, const string_tag& rhs );
string_tag FASTCALL operator + ( const string_tag& lhs, const string_tag::value_type *rhs );
string_tag FASTCALL operator + ( const string_tag& lhs, string_tag::value_type rhs );

bool FASTCALL operator < ( const string_tag& lhs, const string_tag& rhs );
bool FASTCALL operator < ( const string_tag::value_type *, const string_tag& );
bool FASTCALL operator < ( const string_tag& lhs, const string_tag::value_type *rhs );

bool FASTCALL operator == ( const string_tag& lhs, const string_tag& rhs );
bool FASTCALL operator == ( const string_tag::value_type *, const string_tag& );
bool FASTCALL operator == ( const string_tag&, const string_tag::value_type * );

bool FASTCALL operator != ( const string_tag& lhs, const string_tag& rhs );
bool FASTCALL operator != ( const string_tag::value_type *, const string_tag& );
bool FASTCALL operator != ( const string_tag&, const string_tag::value_type * );

//-- IO --
cStream& FASTCALL operator << ( cStream& st, const string_tag& a );
cStream& FASTCALL operator >> ( cStream& st, string_tag& a );
//***********************************************************************
//******    wstring_tag
//***********************************************************************
class wstring_tag
{
public:
    typedef std::wstring                string_type;
    typedef string_type::value_type     value_type;
    typedef string_type::size_type      size_type;
    typedef string_type::iterator       iterator;
private:
    friend wstring_tag FASTCALL operator + ( const wstring_tag& lhs, const wstring_tag& rhs );
    friend wstring_tag FASTCALL operator + ( const wstring_tag::value_type *lhs, const wstring_tag& rhs );
    friend wstring_tag FASTCALL operator + ( wstring_tag::value_type lhs, const wstring_tag& rhs );
    friend wstring_tag FASTCALL operator + ( const wstring_tag& lhs, const wstring_tag::value_type *rhs );
    friend wstring_tag FASTCALL operator + ( const wstring_tag& lhs, wstring_tag::value_type rhs );
    friend bool        FASTCALL operator < ( const wstring_tag& lhs, const wstring_tag& rhs );
    friend bool        FASTCALL operator < ( const wstring_tag& lhs, const wstring_tag::value_type *rhs );
    friend bool        FASTCALL operator == ( const wstring_tag& lhs, const wstring_tag& rhs );
    string_type     mStr;
public:
    CDFASTCALL wstring_tag();
    CDFASTCALL wstring_tag( const value_type *str );
    CDFASTCALL wstring_tag( const value_type *str, const size_type count );
    CDFASTCALL wstring_tag( const size_type count, const value_type str );
    CDFASTCALL wstring_tag( const wstring_tag& src );
    CDFASTCALL ~wstring_tag();
    wstring_tag& FASTCALL operator += ( const wstring_tag& src );
    wstring_tag& FASTCALL operator += ( const value_type *src );
    wstring_tag& FASTCALL operator += ( value_type src );

    value_type FASTCALL operator []( size_type idx ) const;                     /* TODO -oSam : Check this out */

    wstring_tag& FASTCALL erase( size_type pos = 0, size_type n = npos );
    iterator FASTCALL erase( iterator p );
    iterator FASTCALL erase( iterator first, iterator last );

    bool FASTCALL empty() const                                     { return ( mStr.empty() ); }
    size_type FASTCALL size() const                                 { return ( mStr.size() ); }
    const value_type * FASTCALL c_str() const                       { return ( mStr.c_str() ); }

    static const size_type npos;
};

wstring_tag FASTCALL operator + ( const wstring_tag& lhs, const wstring_tag& rhs );
wstring_tag FASTCALL operator + ( const wstring_tag::value_type *lhs, const wstring_tag& rhs );
wstring_tag FASTCALL operator + ( wstring_tag::value_type lhs, const wstring_tag& rhs );
wstring_tag FASTCALL operator + ( const wstring_tag& lhs, const wstring_tag::value_type *rhs );
wstring_tag FASTCALL operator + ( const wstring_tag& lhs, wstring_tag::value_type rhs );

bool FASTCALL operator < ( const wstring_tag& lhs, const wstring_tag& rhs );
bool FASTCALL operator < ( const wstring_tag::value_type *, const wstring_tag& );
bool FASTCALL operator < ( const wstring_tag& lhs, const wstring_tag::value_type *rhs );

bool FASTCALL operator == ( const wstring_tag& lhs, const wstring_tag& rhs );
bool FASTCALL operator == ( const wstring_tag::value_type *, const wstring_tag& );
bool FASTCALL operator == ( const wstring_tag&, const wstring_tag::value_type * );

#if defined ( __BORLANDC__ )

inline int FASTCALL StringCompare( const char *str1, const char *str2 )
{
    return ( stricmp( str1, str2 ) );
}

#endif

#if defined ( _MSC_VER )

inline int FASTCALL StringCompare( const char *str1, const char *str2 )
{
    return ( _stricmp( str1, str2 ) );
}

#endif

inline int FASTCALL StringCompare( const string_tag& str1, const string_tag& str2 )
{
    return ( StringCompare( str1.c_str(), str2.c_str() ) );
}

//***********************************************************************
//******    StringBuilder
//***********************************************************************
//class StringBuilder
//{
//private:
//    std::ostringstream  mStream;
//    // non copyable
//    CDFASTCALL StringBuilder( const StringBuilder& src );
//    StringBuilder& FASTCALL operator=( const StringBuilder& src );
//public:
//    CDFASTCALL StringBuilder();
//    CDFASTCALL StringBuilder( const string_tag& src );
//    CDFASTCALL StringBuilder( const char *src );
//    CDFASTCALL ~StringBuilder();
//    string_tag FASTCALL str();
//    StringBuilder& FASTCALL operator << ( int value );
//    StringBuilder& FASTCALL operator << ( const string_tag& value );
//    StringBuilder& FASTCALL operator << ( const char *value );
//};

};

//---------------------------------------------------------------------------
#endif
