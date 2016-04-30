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
#include "dsODBCtypes.h"
#include <ctime>

namespace smds
{

class dbDate;
class dbTime;
class dbDateTime;

namespace detail
{

typedef long    dbDate_Internal;
typedef long    dbTime_Internal;

struct dbDateTime_Internal
{
    dbDate_Internal     date;
    dbTime_Internal     time;
};

dbDate FASTCALL CreateDbDate( const dbDate_Internal& date );
dbTime FASTCALL CreateDbTime( const dbTime_Internal& time );
dbDateTime FASTCALL CreateDbDateTime( const dbDateTime_Internal& date_time );

};

//***********************************************************************
//******    dbDate
//***********************************************************************
class dbDate
{
private:
    friend cStream& FASTCALL operator << ( cStream& st, const dbDate a );
    friend cStream& FASTCALL operator >> ( cStream& st, dbDate& a );
    friend dbDate FASTCALL detail::CreateDbDate( const detail::dbDate_Internal& date );

    detail::dbDate_Internal     mValue;

    explicit CDFASTCALL dbDate( const detail::dbDate_Internal& date ) : mValue(date)        {} // empty
public:
    CDFASTCALL dbDate() : mValue()                                                          {} // empty
    CDFASTCALL dbDate( const dbDate& date ) : mValue(date.mValue)                           {} // empty
    explicit CDFASTCALL dbDate( const std::tm& date );
    explicit CDFASTCALL dbDate( const double& value );
    detail::dbDate_Internal FASTCALL AsInternal() const                                     { return mValue; }
    double FASTCALL AsDouble() const;
};

//***********************************************************************
//******    dbTime
//***********************************************************************
class dbTime
{
private:
    friend cStream& FASTCALL operator << ( cStream& st, const dbTime a );
    friend cStream& FASTCALL operator >> ( cStream& st, dbTime& a );
    friend dbTime FASTCALL detail::CreateDbTime( const detail::dbTime_Internal& time );

    detail::dbTime_Internal     mValue;

    explicit CDFASTCALL dbTime( const detail::dbTime_Internal& time ) : mValue(time)        {} // empty
public:
    CDFASTCALL dbTime() : mValue()                                                          {} // empty
    explicit CDFASTCALL dbTime( const std::tm& date );
    explicit CDFASTCALL dbTime( const double& value );
    detail::dbTime_Internal FASTCALL AsInternal() const                                     { return mValue; }
    double FASTCALL AsDouble() const;
};

//***********************************************************************
//******    dbDateTime
//***********************************************************************
class dbDateTime
{
public:
private:
    friend cStream& FASTCALL operator << ( cStream& st, const dbDateTime a );
    friend cStream& FASTCALL operator >> ( cStream& st, dbDateTime& a );
    friend dbDateTime FASTCALL detail::CreateDbDateTime( const detail::dbDateTime_Internal& date_time );

    detail::dbDateTime_Internal     mValue;

    explicit CDFASTCALL dbDateTime( const detail::dbDateTime_Internal& date_time ) : mValue(date_time)     {} // empty
public:
    CDFASTCALL dbDateTime();
    explicit CDFASTCALL dbDateTime( const std::tm& date_time );
    explicit CDFASTCALL dbDateTime( const double& date_time );

    const detail::dbDateTime_Internal& FASTCALL AsInternal() const                          { return mValue; }
    double FASTCALL AsDouble() const;
    std::tm FASTCALL AsTM() const;
};

cStream& FASTCALL operator << ( cStream& st, const dbDateTime a );
cStream& FASTCALL operator >> ( cStream& st, dbDateTime& a );

namespace detail
{

inline dbDate FASTCALL CreateDbDate( const detail::dbDate_Internal& date )
{
    return dbDate( date );
}

inline dbTime FASTCALL CreateDbTime( const detail::dbTime_Internal& time )
{
    return dbTime( time );
}

inline dbDateTime FASTCALL CreateDbDateTime( const detail::dbDateTime_Internal& date_time )
{
    return dbDateTime( date_time );
}

bool operator < ( const detail::dbDateTime_Internal& left, const detail::dbDateTime_Internal& right );
bool operator > ( const detail::dbDateTime_Internal& left, const detail::dbDateTime_Internal& right );

};

//***********************************************************************
//******    free functions
//***********************************************************************
detail::dbDate_Internal LongEncodeDate( const DATE_STRUCT& date );
detail::dbTime_Internal LongEncodeTime( const TIME_STRUCT& time );
detail::dbDateTime_Internal LongEncodeDateTime( const TIMESTAMP_STRUCT& date_time );

}; // smds
//---------------------------------------------------------------------------
#endif

