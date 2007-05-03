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

#include "uCompileTest.h"
#include <dsData.h>
#include "uTables.h"
//---------------------------------------------------------------------------
using namespace smds;
using namespace smds::detail;

void Tutorial()
{
    // Select engine
    cDbEngine       engine = SelectDbEngine( "ADO" );

    // connect to database
    cDatabase       database = engine.NewConnection( "" );

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
    tblFiles::index_ptr     idx = ds->NewIndex( OpenIndexFields( cIndexField( "PathID" ), cIndexField( "fSize" ) ) );

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

