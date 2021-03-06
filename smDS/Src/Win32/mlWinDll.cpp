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

#include "pre_smDS.h"
#include "Win32/mlWinDll.h"
//---------------------------------------------------------------------------
namespace smds
{

//***********************************************************************
//******    WinDllML
//***********************************************************************
CDFASTCALL WinDllML::WinDllML( const wchar_t *dll_name )
    : mDll_Guard(dll_name)
{
    mDatabase_Ctor = reinterpret_cast<Database_Ctor>(mDll_Guard.GetProcAddress( "_CreateDataConnection" ));
    mDatabase_Dtor = reinterpret_cast<Database_Dtor>(mDll_Guard.GetProcAddress( "_DeleteDataConnection" ));
    if ( mDatabase_Ctor == 0 || mDatabase_Dtor == 0 )
        throw eDllLoadError();
}

Database_Ctor FASTCALL WinDllML::GetCreateDataConnection()
{
    return mDatabase_Ctor;
}

Database_Dtor FASTCALL WinDllML::GetDeleteDataConnection()
{
    return mDatabase_Dtor;
}

} // namespace smds
//---------------------------------------------------------------------------

