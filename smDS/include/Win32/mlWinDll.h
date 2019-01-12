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
#include "dsExceptions.h"
#include <cpp_string.h>
//---------------------------------------------------------------------------

namespace smds
{
    //=======================================================================
    //======    LoadLibraryImpl (for windows)
    //=======================================================================
    class SharedLibraryImpl
    {
    private:
        typedef void ( * procedure )();
    private:
        HMODULE                 mDLL;
        // noncpyable
        SharedLibraryImpl( const SharedLibraryImpl& src ) CC_EQ_DELETE;
        SharedLibraryImpl& operator = ( const SharedLibraryImpl& src ) CC_EQ_DELETE;
        procedure GetProcAddressImpl( const char * proc_name )
        {
            procedure   result = reinterpret_cast<procedure>(GetProcAddress( mDLL, proc_name ));

            if ( ! result )
                throw eDllLoadError();
            return result;
        }
    public:
        SharedLibraryImpl( const std_char *dll_name )
            : mDLL(LoadLibrary( dll_name ))
        {
            if ( mDLL == 0 )
                throw eDllLoadError();
        }
        
        ~SharedLibraryImpl()
        {
            if ( mDLL != 0 )
                FreeLibrary( mDLL );
        }

        template <class T> T GetProcAddressT( const char * proc_name )
        {
            return reinterpret_cast<T>(GetProcAddressImpl( proc_name ));
        }

    };

    typedef std::shared_ptr<SharedLibraryImpl>      spSharedLibrary;

    inline spSharedLibrary LoadDll( const std_char *dll_name )
    {
        return std::make_shared<SharedLibraryImpl>( dll_name );
    }

    //=======================================================================
    //======    WinDllML (for windows)
    //=======================================================================
    //class WinDllML : public IModuleLoader
    //{
    //private:
    //    spSharedLibrary         mDll_Guard;
    //    Database_Ctor           mDatabase_Ctor;
    //    Database_Dtor           mDatabase_Dtor;

    //    virtual Database_Ctor GetCreateDataConnection();
    //    virtual Database_Dtor GetDeleteDataConnection();

    //    // noncpyable
    //    WinDllML( const WinDllML& src ) CC_EQ_DELETE;
    //    WinDllML& operator = ( const WinDllML& src ) CC_EQ_DELETE;
    //public:
    //    WinDllML( const spSharedLibrary& dll );
    //};

}; // namespace smds
//---------------------------------------------------------------------------
#endif
