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
#ifndef SM_DS_DATETIME_H
#define SM_DS_DATETIME_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include <ssport.h>
#include "dsStream.h"

namespace ds
{

// Data types
#pragma pack( push, 1 )

/*
struct cDateTime
{
    unsigned int Date;
    unsigned int Time;
};
*/

class cDateTime
{
private:
    //friend double operator - ( const cDateTime& left, const cDateTime& right );
    //friend bool operator <= ( const cDateTime& left, const cDateTime& right );
    //friend bool operator < ( const cDateTime& left, const cDateTime& right );
    friend cStream& FASTCALL operator << ( cStream& st, const cDateTime a );
    friend cStream& FASTCALL operator >> ( cStream& st, cDateTime& a );
    double  mValue;
public:
    CDFASTCALL cDateTime() : mValue(0)                                  {} // empty
    CDFASTCALL cDateTime( const double& value ) : mValue(value)         {} // empty
    double FASTCALL AsDouble() const                                    { return ( mValue ); }
    double FASTCALL Date() const                                        { return ( static_cast<double>(static_cast<int>(mValue)) ); }
    cDateTime& FASTCALL operator += ( int days )
    {
        mValue += days;
        return ( *this );
    }
    cDateTime& FASTCALL operator -= ( int days )
    {
        mValue -= days;
        return ( *this );
    }
    cDateTime FASTCALL operator + ( int days )
    {
        cDateTime   tmp( *this );

        tmp += days;
        return ( tmp );
    }
    bool operator <= ( const cDateTime& right )                         { return ( mValue <= right.mValue ); }
    bool operator < ( const cDateTime& right )                          { return ( mValue < right.mValue ); }
};

//inline double operator - ( const cDateTime& left, const cDateTime& right )
//{
//    return ( left.mValue - right.mValue );
//}
//
//inline bool operator <= ( const cDateTime& left, const cDateTime& right )
//{
//    return ( left.mValue <= right.mValue );
//}
//
//inline bool operator < ( const cDateTime& left, const cDateTime& right )
//{
//    return ( left.mValue < right.mValue );
//}

cStream& FASTCALL operator << ( cStream& st, const cDateTime a );
cStream& FASTCALL operator >> ( cStream& st, cDateTime& a );

//typedef double  cDateTime;

#pragma pack( pop )

};
//---------------------------------------------------------------------------
#endif
