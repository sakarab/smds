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
#ifndef SM_DS_GUID_H
#define SM_DS_GUID_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include "dsODBCtypes.h"

namespace smds
{

class dbGUID;

namespace detail
{

typedef SQLGUID     dbGUID_Internal;

dbGUID CreateDbGUID( const dbGUID_Internal& guid );

} // detail

//***********************************************************************
//******    dbGUID
//***********************************************************************
class dbGUID
{
private:
    //friend cStream& operator << ( cStream& st, const dbGUID a );
    //friend cStream& operator >> ( cStream& st, dbGUID& a );
    friend dbGUID detail::CreateDbGUID( const detail::dbGUID_Internal& guid );

    detail::dbGUID_Internal     mValue;

    explicit dbGUID( const detail::dbGUID_Internal& guid );
public:
    dbGUID();
    const detail::dbGUID_Internal& AsInternal() const                   { return mValue; }
};

namespace detail
{

inline dbGUID CreateDbGUID( const dbGUID_Internal& guid )
{
    return dbGUID( guid );
}

} // detail

} // smds
//---------------------------------------------------------------------------
#endif

