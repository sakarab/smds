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
        // noncpyable
        So_Guard( const So_Guard& src );
        So_Guard& operator = ( const So_Guard& src );
    public:
        CDFASTCALL So_Guard( const char *so_name )
        {
        }
        CDFASTCALL ~So_Guard()
        {
        }
        void * FASTCALL GetProcAddress( const char * proc_name )
        {
            return 0;
        }
    };

    So_Guard                mSo_Guard;
    Database_Ctor           mDatabase_Ctor;
    Database_Dtor           mDatabase_Dtor;

    virtual Database_Ctor FASTCALL GetCreateDataConnection();
    virtual Database_Dtor FASTCALL GetDeleteDataConnection();

    // noncpyable
    LinuxSoML( const LinuxSoML& src );
    LinuxSoML& operator = ( const LinuxSoML& src );
public:
    CDFASTCALL LinuxSoML( const char *so_name );
};

}; // namespace smds
//---------------------------------------------------------------------------
#endif
