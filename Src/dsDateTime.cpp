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
#pragma hdrstop

#include "dsDateTime.h"
//---------------------------------------------------------------------------

namespace ds
{

cStream& FASTCALL operator << ( cStream& st, const cDateTime a )
{
    return ( st.WriteBuffer( &a.mValue, sizeof(a.mValue) ) );
}

cStream& FASTCALL operator >> ( cStream& st, cDateTime& a )
{
	return ( st.ReadBuffer( &a.mValue, sizeof(a.mValue) ) );
}

};
//---------------------------------------------------------------------------

