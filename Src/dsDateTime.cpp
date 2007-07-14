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

#include "dsDateTime.h"
#include <stdexcept>
//---------------------------------------------------------------------------

namespace smds
{

namespace
{

typedef SQLUSMALLINT        DayTable[13];

const unsigned int DaysOffset            = 693594U;
const unsigned int HoursPerDay           = 24U;
const unsigned int MinutesPerHour        = 60U;
const unsigned int SecondsPerMinute      = 60U;
const unsigned int MillisecondsPerSecond = 1000U;
const unsigned int MinutesPerDay         = HoursPerDay * MinutesPerHour;
const unsigned int SecondsPerDay         = MinutesPerDay * SecondsPerMinute;
const unsigned int MillisecondsPerDay    = SecondsPerDay * MillisecondsPerSecond;

DayTable MonthDays[2] =
{
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

bool IsLeapYear( SQLSMALLINT year )
{
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

detail::dbDate_Internal LongEncodeDatePart( SQLSMALLINT year, SQLUSMALLINT month, SQLUSMALLINT day )
{
    SQLUSMALLINT    *day_table = MonthDays[IsLeapYear( year )];

    if ( month < 1 || month > 12 || day < 1 || day > day_table[month] )
        throw std::runtime_error( "Date conversion error." );
    for ( int i = 1 ; i < month ; ++i )
        day += day_table[i];
    --year;
    return ( year * 365 + year / 4 - year / 100 + year / 400 + day );
}

detail::dbTime_Internal LongEncodeTimePart( SQLUSMALLINT hour, SQLUSMALLINT minute, SQLUSMALLINT second, SQLUINTEGER fraction )
{
    if ( hour >= HoursPerDay || minute >= MinutesPerHour || second >= SecondsPerMinute || fraction >= MillisecondsPerSecond )
        throw std::runtime_error( "Time conversion error." );
    return ( ( hour * (MinutesPerHour * SecondsPerMinute * MillisecondsPerSecond) +
               minute * (SecondsPerMinute * MillisecondsPerSecond) +
               second * MillisecondsPerSecond +
               fraction ) );
}

detail::dbDateTime_Internal LongEncodeDateTimePart( SQLSMALLINT year, SQLUSMALLINT month, SQLUSMALLINT day,
                                                    SQLUSMALLINT hour, SQLUSMALLINT minute, SQLUSMALLINT second, SQLUINTEGER fraction )
{
    detail::dbDateTime_Internal     result;

    result.date = LongEncodeDatePart( year, month, day );
    result.time = LongEncodeTimePart( hour, minute, second, fraction );
    return result;
}

/*
double EncodeDate( SQLSMALLINT year, SQLUSMALLINT month, SQLUSMALLINT day )
{
    if ( year < 1 || year > 9999 )
        throw std::runtime_error( "Date conversion error." );
    return ( LongEncodeDatePart( year, month, day ) - DaysOffset );
}

double EncodeTime( SQLUSMALLINT hour, SQLUSMALLINT minute, SQLUSMALLINT second, SQLUINTEGER fraction )
{
    return ( LongEncodeTimePart( hour, minute, second, fraction ) / static_cast<double>(MillisecondsPerDay) );
}

double EncodeDateTime( SQLSMALLINT year, SQLUSMALLINT month, SQLUSMALLINT day,
                       SQLUSMALLINT hour, SQLUSMALLINT minute, SQLUSMALLINT second, SQLUINTEGER fraction )
{
    return EncodeDate( year, month, day ) + EncodeTime( hour, minute, second, fraction );
}
*/

inline double InternalDateToDouble( detail::dbDate_Internal date )
{
    return ( date - DaysOffset );
}

inline double InternalTimeToDouble( detail::dbTime_Internal time )
{
    return ( time / static_cast<double>(MillisecondsPerDay) );
}

inline double InternalDateTimeToDouble( const detail::dbDateTime_Internal& date_time )
{
    return InternalDateToDouble( date_time.date ) + InternalTimeToDouble( date_time.time );
}

}; // namespace

detail::dbDate_Internal LongEncodeDate( const DATE_STRUCT& date )
{
    return LongEncodeDatePart( date.year, date.month, date.day );
}

detail::dbTime_Internal LongEncodeTime( const TIME_STRUCT& time )
{
    return LongEncodeTimePart( time.hour, time.minute, time.second, 0 );
}

detail::dbDateTime_Internal LongEncodeDateTime( const TIMESTAMP_STRUCT& date_time )
{
    return LongEncodeDateTimePart( date_time.year, date_time.month, date_time.day,
                                   date_time.hour, date_time.minute, date_time.second, date_time.fraction );
}

//***********************************************************************
//******    dbDate
//***********************************************************************
double FASTCALL dbDate::AsDouble() const
{
    return InternalDateToDouble( mValue );
}

//***********************************************************************
//******    dbTime
//***********************************************************************
double FASTCALL dbTime::AsDouble() const
{
    return InternalTimeToDouble( mValue );
}

//***********************************************************************
//******    dbDateTime
//***********************************************************************
CDFASTCALL dbDateTime::dbDateTime()
{
    mValue.date = 0;
    mValue.time = 0;
}

double FASTCALL dbDateTime::AsDouble() const
{
    return InternalDateTimeToDouble( mValue );
}

cStream& FASTCALL operator << ( cStream& st, const dbDateTime a )
{
    return st.WriteBuffer( &a.mValue, sizeof(a.mValue) );
}

cStream& FASTCALL operator >> ( cStream& st, dbDateTime& a )
{
	return st.ReadBuffer( &a.mValue, sizeof(a.mValue) );
}

namespace detail
{

bool operator < ( const detail::dbDateTime_Internal& left, const detail::dbDateTime_Internal& right )
{
    if ( left.date < right.date )
        return true;
    else if ( left.date == right.date && left.time < right.time )
        return true;
    return false;
}

bool operator > ( const detail::dbDateTime_Internal& left, const detail::dbDateTime_Internal& right )
{
    if ( left.date > right.date )
        return true;
    else if ( left.date == right.date && left.time > right.time )
        return true;
    return false;
}

}; // detail

}; // smds
//---------------------------------------------------------------------------

