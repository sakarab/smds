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
#ifndef SM_DS_ML_LINUXSO_H
#define SM_DS_ML_LINUXSO_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include "dsModuleLoad.h"
#include "dsExceptions.h"
#include <dlfcn.h>
//---------------------------------------------------------------------------

namespace smds
{

//***********************************************************************
//******    LinuxSoML
//***********************************************************************
class LinuxSoML : public IModuleLoader
{
private:
    class So_Guard
    {
    private:
        void    *mHandle;
        // noncpyable
        So_Guard( const So_Guard& src );
        So_Guard& operator = ( const So_Guard& src );
    public:
        So_Guard( const char *so_name )
            : mHandle(dlopen( so_name, RTLD_NOW ))
        {
            if ( mHandle == 0 )
            {
                const char  *aa = dlerror();

                if ( aa == 0 )
                    throw eDllLoadError( "Unable to load ODBC_Conn" );
                else
                    throw eDllLoadError( aa );
            }
        }
        ~So_Guard()
        {
            dlclose( mHandle );
        }
        void * GetProcAddress( const char *proc_name )
        {
            void    *result = dlsym( mHandle, proc_name );

            if ( result == 0 )
                throw eDllLoadError( "function not found in ODBC_Conn" );
            return result;
        }
    };

    So_Guard                mSo_Guard;
    Database_Ctor           mDatabase_Ctor;
    Database_Dtor           mDatabase_Dtor;

    virtual Database_Ctor GetCreateDataConnection();
    virtual Database_Dtor GetDeleteDataConnection();

    // noncpyable
    LinuxSoML( const LinuxSoML& src );
    LinuxSoML& operator = ( const LinuxSoML& src );
public:
    LinuxSoML( const char *so_name );
};

} // namespace smds
//---------------------------------------------------------------------------
#endif
