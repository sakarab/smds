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
#include "pre_test.h"
#include "uCompileTest.h"
#include <dsData.h>
#include <dsIndex.h>
#include "uTables.h"
#include "uTest.h"
//---------------------------------------------------------------------------

using namespace smds;

void ConvertTypedData( tblFiles::index_ptr& idx )
{
    // tblFiles_ptr    ds = *idx;
}

void Tutorial()
{
    // Select engine
    spModuleLoader          module_loader( new OsModuleLoader( SM_DS_TEST_BACKEND ) );
    DbEngine                engine( module_loader );

    // connect to database
    Database        database = engine.NewConnection( CCTEXT( "" ) );

    // Create and open the dataset
    tblFiles_ptr    ds( new tblFiles() );

    ds->Open( database, 0 );

    // serially locate a record with PathID == 27
    tblFiles::iterator      iter = ds->GetIterator();

    while ( ! iter.eof() )
    {
        if ( ! iter->PathID_IsNull() && iter->GetPathID() == 27 )
            break;
        ++iter;
    }
    if ( ! iter.eof() )
    {
        //  found. do something with it
    }
    else
    {
        // report the error
    }

    // Create an index on "PathID" and "fSize" fields
    tblFiles::index_ptr     idx = ds->NewIndex( OpenIndexFields( cIndexField( CCTEXT( "PathID" ) ), cIndexField( CCTEXT( "fSize" ) ) ) );

    // find - binary search - a record with PathID == 27 and fSize == 45000
    tblFiles::index::iterator   idx_it = idx->Find( OpenValues( 27, 45000 ) );

    if ( ! idx_it.eof() )
    {
        //  found. do something with it
    }
    else
    {
        // report the error
    }

    // change all

}
//---------------------------------------------------------------------------

