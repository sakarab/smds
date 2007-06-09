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
#ifndef SM_DS_DATETIME_H
#define SM_DS_DATETIME_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include "dsStream.h"
#include <ctime>

namespace smds
{

#if defined(SM_DS_DATE_IS_DOUBLE)

class cDate
{
private:
    friend cStream& FASTCALL operator << ( cStream& st, const cDate a );
    friend cStream& FASTCALL operator >> ( cStream& st, cDate& a );
    double  mValue;
public:
    CDFASTCALL cDate() : mValue(0)                                      {} // empty
    explicit CDFASTCALL cDate( const double& value ) : mValue(value)    {} // empty
    double FASTCALL AsDouble() const                                    { return ( mValue ); }
    bool operator <= ( const cDate& right )                             { return ( mValue <= right.mValue ); }
    bool operator < ( const cDate& right )                              { return ( mValue < right.mValue ); }
};

class cTime
{
private:
    friend cStream& FASTCALL operator << ( cStream& st, const cTime a );
    friend cStream& FASTCALL operator >> ( cStream& st, cTime& a );
    double  mValue;
public:
    CDFASTCALL cTime() : mValue(0)                                      {} // empty
    explicit CDFASTCALL cTime( const double& value ) : mValue(value)    {} // empty
    double FASTCALL AsDouble() const                                    { return ( mValue ); }
    bool operator <= ( const cTime& right )                             { return ( mValue <= right.mValue ); }
    bool operator < ( const cTime& right )                              { return ( mValue < right.mValue ); }
};

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
    CDFASTCALL cDateTime() : mValue(0)                                      {} // empty
    explicit CDFASTCALL cDateTime( const double& value ) : mValue(value)    {} // empty
    double FASTCALL AsDouble() const                                        { return ( mValue ); }
    double FASTCALL Date() const                                            { return ( static_cast<double>(static_cast<int>(mValue)) ); }
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

#else

//***********************************************************************
//******    dbDate
//***********************************************************************
// exactly like tagDATE_STRUCT
struct dbDate_tag
{
    short           year;
    unsigned short  month;
    unsigned short  day;
};

class dbDate
{
private:
    dbDate_tag      mData;
public:
    explicit CDFASTCALL dbDate( const dbDate_tag& date );
    explicit CDFASTCALL dbDate( const std::tm& date );
    explicit CDFASTCALL dbDate( const double& date );
    CDFASTCALL dbDate( short year, unsigned short month, unsigned short day );

    bool operator < ( const dbDate& right );

    short FASTCALL GetYear() const                  { return mData.year; }
    unsigned short FASTCALL GetMonth() const        { return mData.month; }
    unsigned short FASTCALL GetDay() const          { return mData.day; }
};

//***********************************************************************
//******    dbTime
//***********************************************************************
// exactly like tagTIME_STRUCT
struct dbTime_tag
{
    unsigned short  hour;
    unsigned short  minute;
    unsigned short  second;
};

//***********************************************************************
//******    dbDateTime
//***********************************************************************
// exactly like tagTIMESTAMP_STRUCT
struct dbDateTime_tag
{
    short           year;
    unsigned short  month;
    unsigned short  day;
    unsigned short  hour;
    unsigned short  minute;
    unsigned short  second;
    unsigned long   fraction;
};

class dbDateTime
{
private:
    dbDateTime_tag  mData;
public:
    explicit CDFASTCALL dbDateTime( const dbDate_tag& date );
    explicit CDFASTCALL dbDateTime( const std::tm& date );
    explicit CDFASTCALL dbDateTime( const double& date );
    CDFASTCALL dbDateTime( short year, unsigned short month, unsigned short day );

    bool operator < ( const dbDateTime& right );
};

#endif

}; // smds
//---------------------------------------------------------------------------
#endif
