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
#ifndef SM_DS_ML_WINDLL_H
#define SM_DS_ML_WINDLL_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include <windows.h>
#include "dsModuleLoad.h"
#include "dsExceptions.h"
//---------------------------------------------------------------------------

namespace smds
{

//***********************************************************************
//******    WinDllML
//***********************************************************************
class WinDllML : public IModuleLoader
{
private:
    class Dll_Guard
    {
    private:
        HMODULE                 mDLL;
        // noncpyable
        Dll_Guard( const Dll_Guard& src );
        Dll_Guard& operator = ( const Dll_Guard& src );
    public:
        CDFASTCALL Dll_Guard( const char *dll_name )
            : mDLL(::LoadLibrary( dll_name ))
        {
            if ( mDLL == 0 )
                throw eDllLoadError();
        }
        CDFASTCALL ~Dll_Guard()
        {
            if ( mDLL != 0 )
                ::FreeLibrary( mDLL );
        }
        FARPROC FASTCALL GetProcAddress( const char * proc_name )
        {
            return ::GetProcAddress( mDLL, proc_name );
        }
    };

    Dll_Guard               mDll_Guard;
    Database_Ctor           mDatabase_Ctor;
    Database_Dtor           mDatabase_Dtor;

    virtual Database_Ctor FASTCALL GetCreateDataConnection();
    virtual Database_Dtor FASTCALL GetDeleteDataConnection();

    // noncpyable
    WinDllML( const WinDllML& src );
    WinDllML& operator = ( const WinDllML& src );
public:
    CDFASTCALL WinDllML( const char *dll_name );
};

}; // namespace smds
//---------------------------------------------------------------------------
#endif
