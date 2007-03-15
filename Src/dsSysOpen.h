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

  Please read the "readme" file in the root directory of this
  package for more copyright and license information.
****************************************************************************/
//---------------------------------------------------------------------------
#ifndef SM_DS_SYSOPN_H
#define SM_DS_SYSOPN_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include <boost/scoped_array.hpp>
#include <ssport.h>

namespace ds
{

namespace detail
{

/*
template <class T, int n> class OArr
{
private:
    const T *mArray[n];
    // noncopyable
    CDFASTCALL OArr( const OArr& src );
    OArr& FASTCALL operator =( const OArr& rhs );
public:
    CDFASTCALL OArr( const T& arg0 )
    {
        SetElement( 0, &arg0 );
    }
    CDFASTCALL OArr( const T& arg0, const T& arg1 )
    {
        SetElement( 0, &arg0 );
        SetElement( 1, &arg1 );
    }
    T * FASTCALL GetElement( int idx )                      { return ( mArray[idx] ); }
    void FASTCALL SetElement( int idx, const T *element )   { mArray[idx] = element; }
    int FASTCALL GetCount()                                 { return ( n ); }
};

//partial specialization class templates

template <> class OArr <int, 1>
{
    CDFASTCALL OArr( const T& arg0 )
    {
        SetElement( 0, &arg0 );
    }
    CDFASTCALL OArr( const T& arg0, const T& arg1 )
    {
        SetElement( 0, &arg0 );
        SetElement( 1, &arg1 );
    }
};

template <> class OArr <char, 2>
{
    CDFASTCALL OArr( const T& arg0 )
    {
        SetElement( 0, &arg0 );
    }
    CDFASTCALL OArr( const T& arg0, const T& arg1 )
    {
        SetElement( 0, &arg0 );
        SetElement( 1, &arg1 );
    }
};
*/

template<class T> class OpenArray
{
private:
    boost::scoped_array<const T*>    Array;
    long Count;
    // noncopyable
    CDFASTCALL OpenArray( const OpenArray& src );
    OpenArray& FASTCALL operator =( const OpenArray& rhs );
public:
    CDFASTCALL OpenArray( const T& arg0 )
        : Array(new const T*[Count = 1])
    {
        Array[0] = &arg0;
    }
    CDFASTCALL OpenArray( const T& arg0, const T& arg1 )
        : Array(new const T*[Count = 2])
    {
        Array[0] = &arg0;
        Array[1] = &arg1;
    }
    CDFASTCALL OpenArray( const T& arg0, const T& arg1, const T& arg2 )
        : Array(new const T*[Count = 3])
    {
        Array[0] = &arg0;
        Array[1] = &arg1;
        Array[2] = &arg2;
    }
    CDFASTCALL OpenArray( const T& arg0, const T& arg1, const T& arg2, const T& arg3 )
        : Array(new const T*[Count = 4])
    {
        Array[0] = &arg0;
        Array[1] = &arg1;
        Array[2] = &arg2;
        Array[3] = &arg3;
    }
    CDFASTCALL OpenArray( const T& arg0, const T& arg1, const T& arg2, const T& arg3, const T& arg4 )
        : Array(new const T*[Count = 5])
    {
        Array[0] = &arg0;
        Array[1] = &arg1;
        Array[2] = &arg2;
        Array[3] = &arg3;
        Array[4] = &arg4;
    }
    CDFASTCALL OpenArray( const T& arg0, const T& arg1, const T& arg2, const T& arg3, const T& arg4, const T& arg5 )
        : Array(new const T*[Count = 6])
    {
        Array[0] = &arg0;
        Array[1] = &arg1;
        Array[2] = &arg2;
        Array[3] = &arg3;
        Array[4] = &arg4;
        Array[5] = &arg5;
    }
    CDFASTCALL OpenArray( const T& arg0, const T& arg1, const T& arg2, const T& arg3, const T& arg4, const T& arg5, const T& arg6 )
        : Array(new const T*[Count = 7])
    {
        Array[0] = &arg0;
        Array[1] = &arg1;
        Array[2] = &arg2;
        Array[3] = &arg3;
        Array[4] = &arg4;
        Array[5] = &arg5;
        Array[6] = &arg6;
    }
    CDFASTCALL OpenArray( const T& arg0, const T& arg1, const T& arg2, const T& arg3, const T& arg4, const T& arg5, const T& arg6,
                        const T& arg7 )
        : Array(new const T*[Count = 8])
    {
        Array[0] = &arg0;
        Array[1] = &arg1;
        Array[2] = &arg2;
        Array[3] = &arg3;
        Array[4] = &arg4;
        Array[5] = &arg5;
        Array[6] = &arg6;
        Array[7] = &arg7;
    }
    CDFASTCALL OpenArray( const T& arg0, const T& arg1, const T& arg2, const T& arg3, const T& arg4, const T& arg5, const T& arg6,
                        const T& arg7, const T& arg8 )
        : Array(new const T*[Count = 9])
    {
        Array[0] = &arg0;
        Array[1] = &arg1;
        Array[2] = &arg2;
        Array[3] = &arg3;
        Array[4] = &arg4;
        Array[5] = &arg5;
        Array[6] = &arg6;
        Array[7] = &arg7;
        Array[8] = &arg8;
    }
    CDFASTCALL OpenArray( const T& arg0, const T& arg1, const T& arg2, const T& arg3, const T& arg4, const T& arg5, const T& arg6,
                        const T& arg7, const T& arg8, const T& arg9 )
        : Array(new const T*[Count = 10])
    {
        Array[0] = &arg0;
        Array[1] = &arg1;
        Array[2] = &arg2;
        Array[3] = &arg3;
        Array[4] = &arg4;
        Array[5] = &arg5;
        Array[6] = &arg6;
        Array[7] = &arg7;
        Array[8] = &arg8;
        Array[9] = &arg9;
    }
/*
    CDFASTCALL OpenArray( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6,
                        T arg7, T arg8, T arg9, T arg10 )
        : Array(new T[Count = 11])
    {
        Array[0] = arg0;
        Array[1] = arg1;
        Array[2] = arg2;
        Array[3] = arg3;
        Array[4] = arg4;
        Array[5] = arg5;
        Array[6] = arg6;
        Array[7] = arg7;
        Array[8] = arg8;
        Array[9] = arg9;
        Array[10] = arg10;
    }
    CDFASTCALL OpenArray( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6,
                        T arg7, T arg8, T arg9, T arg10, T arg11 )
        : Array(new T[Count = 12])
    {
        Array[0] = arg0;
        Array[1] = arg1;
        Array[2] = arg2;
        Array[3] = arg3;
        Array[4] = arg4;
        Array[5] = arg5;
        Array[6] = arg6;
        Array[7] = arg7;
        Array[8] = arg8;
        Array[9] = arg9;
        Array[10] = arg10;
        Array[11] = arg11;
    }
    CDFASTCALL OpenArray( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6,
                        T arg7, T arg8, T arg9, T arg10, T arg11, T arg12 )
        : Array(new T[Count = 13])
    {
        Array[0] = arg0;
        Array[1] = arg1;
        Array[2] = arg2;
        Array[3] = arg3;
        Array[4] = arg4;
        Array[5] = arg5;
        Array[6] = arg6;
        Array[7] = arg7;
        Array[8] = arg8;
        Array[9] = arg9;
        Array[10] = arg10;
        Array[11] = arg11;
        Array[12] = arg12;
    }
    CDFASTCALL OpenArray( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6,
                        T arg7, T arg8, T arg9, T arg10, T arg11, T arg12,
                        T arg13 )
        : Array(new T[Count = 14])
    {
        Array[0] = arg0;
        Array[1] = arg1;
        Array[2] = arg2;
        Array[3] = arg3;
        Array[4] = arg4;
        Array[5] = arg5;
        Array[6] = arg6;
        Array[7] = arg7;
        Array[8] = arg8;
        Array[9] = arg9;
        Array[10] = arg10;
        Array[11] = arg11;
        Array[12] = arg12;
        Array[13] = arg13;
    }
    CDFASTCALL OpenArray( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6,
                        T arg7, T arg8, T arg9, T arg10, T arg11, T arg12,
                        T arg13, T arg14 )
        : Array(new T[Count = 15])
    {
        Array[0] = arg0;
        Array[1] = arg1;
        Array[2] = arg2;
        Array[3] = arg3;
        Array[4] = arg4;
        Array[5] = arg5;
        Array[6] = arg6;
        Array[7] = arg7;
        Array[8] = arg8;
        Array[9] = arg9;
        Array[10] = arg10;
        Array[11] = arg11;
        Array[12] = arg12;
        Array[13] = arg13;
        Array[14] = arg14;
    }
    CDFASTCALL OpenArray( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6,
                        T arg7, T arg8, T arg9, T arg10, T arg11, T arg12,
                        T arg13, T arg14, T arg15 )
        : Array(new T[Count = 16])
    {
        Array[0] = arg0;
        Array[1] = arg1;
        Array[2] = arg2;
        Array[3] = arg3;
        Array[4] = arg4;
        Array[5] = arg5;
        Array[6] = arg6;
        Array[7] = arg7;
        Array[8] = arg8;
        Array[9] = arg9;
        Array[10] = arg10;
        Array[11] = arg11;
        Array[12] = arg12;
        Array[13] = arg13;
        Array[14] = arg14;
        Array[15] = arg15;
    }
    CDFASTCALL OpenArray( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6,
                        T arg7, T arg8, T arg9, T arg10, T arg11, T arg12,
                        T arg13, T arg14, T arg15, T arg16 )
        : Array(new T[Count = 17])
    {
        Array[0] = arg0;
        Array[1] = arg1;
        Array[2] = arg2;
        Array[3] = arg3;
        Array[4] = arg4;
        Array[5] = arg5;
        Array[6] = arg6;
        Array[7] = arg7;
        Array[8] = arg8;
        Array[9] = arg9;
        Array[10] = arg10;
        Array[11] = arg11;
        Array[12] = arg12;
        Array[13] = arg13;
        Array[14] = arg14;
        Array[15] = arg15;
        Array[16] = arg16;
    }
    CDFASTCALL OpenArray( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6,
                        T arg7, T arg8, T arg9, T arg10, T arg11, T arg12,
                        T arg13, T arg14, T arg15, T arg16, T arg17 )
        : Array(new T[Count = 18])
    {
        Array[0] = arg0;
        Array[1] = arg1;
        Array[2] = arg2;
        Array[3] = arg3;
        Array[4] = arg4;
        Array[5] = arg5;
        Array[6] = arg6;
        Array[7] = arg7;
        Array[8] = arg8;
        Array[9] = arg9;
        Array[10] = arg10;
        Array[11] = arg11;
        Array[12] = arg12;
        Array[13] = arg13;
        Array[14] = arg14;
        Array[15] = arg15;
        Array[16] = arg16;
        Array[17] = arg17;
    }
    CDFASTCALL OpenArray( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6,
                        T arg7, T arg8, T arg9, T arg10, T arg11, T arg12,
                        T arg13, T arg14, T arg15, T arg16, T arg17, T arg18 )
        : Array(new T[Count = 19])
    {
        Array[0] = arg0;
        Array[1] = arg1;
        Array[2] = arg2;
        Array[3] = arg3;
        Array[4] = arg4;
        Array[5] = arg5;
        Array[6] = arg6;
        Array[7] = arg7;
        Array[8] = arg8;
        Array[9] = arg9;
        Array[10] = arg10;
        Array[11] = arg11;
        Array[12] = arg12;
        Array[13] = arg13;
        Array[14] = arg14;
        Array[15] = arg15;
        Array[16] = arg16;
        Array[17] = arg17;
        Array[18] = arg18;
    }
*/
    CDFASTCALL ~OpenArray()                                         {}
    const T** FASTCALL GetArray() const                             { return Array.get(); }
    int FASTCALL GetCount() const                                   { return Count; }
};

}; // namespace detail

}; // namespace ds
//---------------------------------------------------------------------------
#endif
