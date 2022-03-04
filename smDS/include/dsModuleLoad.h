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
#ifndef SM_DS_MODULE_LOAD_H
#define SM_DS_MODULE_LOAD_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include "dsSmartPtr.h"
#include "dsConn_Intf.h"
#include <cpp_string.h>
#include <predef_cc.h>

//---------------------------------------------------------------------------
namespace smds
{
    //***********************************************************************
    //******    IModuleLoader
    //***********************************************************************
    class IModuleLoader
    #ifdef SM_DS_USE_SMALL_SHARED_PTR
        : public boost::shared_in_base<long>
    #endif
    {
    public:
        virtual Database_Ctor GetCreateDataConnection() = 0;
        virtual Database_Dtor GetDeleteDataConnection() = 0;

        virtual ~IModuleLoader()                                 {} // empty
    };
}

#if defined( BOOST_OS_WINDOWS )
    #include "Win32/mlWinDll.h"
#elif defined (LINUX)
    #include "Linux/mlLinuxSo.h"
#else
    #error "No platform specified"
#endif

namespace smds
{
    //=======================================================================
    //======    DbDriver
    //=======================================================================
    class DbDriver
    {
    private:
        spSharedLibrary         mDll_Guard;
        Database_Ctor           mCreateDataConnection;
        Database_Dtor           mDeleteDataConnection;
        // noncpyable
        DbDriver( const DbDriver& src ) CC_EQ_DELETE;
        DbDriver& operator = ( const DbDriver& src ) CC_EQ_DELETE;
    public:
        explicit DbDriver( const spSharedLibrary& dll );
        explicit DbDriver( const std_char *dll_name );

        IDatabase *CreateDataConnection( const std_char *connection_string )        { return mCreateDataConnection( connection_string ); }
        void DeleteDataConnection( IDatabase *db_engine )                           { mDeleteDataConnection( db_engine ); }
    };

    typedef shared_ptr<DbDriver>    spDbDriver;

    //=======================================================================
    //======    DbConnection
    //=======================================================================
    class DbConnection
    {
    private:
        spDbDriver      mDriver;
        IDatabase       *mDatabase;
        // noncpyable
        DbConnection( const DbConnection& src ) CC_EQ_DELETE;
        DbConnection& operator = ( const DbConnection& src ) CC_EQ_DELETE;
    public:
        DbConnection( const spDbDriver& driver, const std_char *connection_string );
        DbConnection( const spSharedLibrary& dll, const std_char *connection_string );
        DbConnection( const std_char *dll_name, const std_char *connection_string );
        ~DbConnection();
    };

    class ModuleLoader : public IModuleLoader
    {
    private:
        spSharedLibrary         mDll_Guard;
        Database_Ctor           mDatabase_Ctor;
        Database_Dtor           mDatabase_Dtor;

        virtual Database_Ctor GetCreateDataConnection();
        virtual Database_Dtor GetDeleteDataConnection();

        // noncpyable
        ModuleLoader( const ModuleLoader& src ) CC_EQ_DELETE;
        ModuleLoader& operator = ( const ModuleLoader& src ) CC_EQ_DELETE;
    public:
        ModuleLoader( const spSharedLibrary& dll );
    };

    typedef shared_ptr<ModuleLoader>      spModuleLoader;
    spModuleLoader GetOsModuleLoader( const std_char *dll_name );

} // namespace smds

//---------------------------------------------------------------------------
#endif

