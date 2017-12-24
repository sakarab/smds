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

#include "uProfile.h"
#include <dsTypedData.h>
#include <boost/timer.hpp>
#include <iostream>
#include "uConnectionStrings.h"
#include "uProfile1.h"
//---------------------------------------------------------------------------

using namespace profile;

namespace
{

//******************************************************
// fill table
//******************************************************
tblFiles_ptr FASTCALL run_FillTable( smds::Database& database )
{
    tblFiles_ptr    result( new tblFiles() );
    boost::timer    clock;

    FillTable( database, result );

    double      elapsed = clock.elapsed();

    std::cout << "fill table (" << result->RecordCount() << " records) " << elapsed << " secs\n";
    return result;
}

//******************************************************
// create index on integer field
//******************************************************
void FASTCALL run_CreateIndex_OneInt( tblFiles_ptr& ds )
{
    boost::timer    clock;

    CreateIndex_OneInt( ds );

    double      elapsed = clock.elapsed();

    std::cout << "create index on integer field (" << ds->RecordCount() << " records) " << elapsed << " secs\n";
}

//******************************************************
// create index on two integer fields
//******************************************************
void FASTCALL run_CreateIndex_TwoInts( tblFiles_ptr& ds )
{
    boost::timer    clock;

    CreateIndex_TwoInts( ds );

    double      elapsed = clock.elapsed();

    std::cout << "create index on two integer fields (" << ds->RecordCount() << " records) " << elapsed << " secs\n";
}

//******************************************************
// create index on integer field with a custom sort function
//******************************************************
void FASTCALL run_CreateIndex_OneIntCustom( tblFiles_ptr& ds )
{
    boost::timer    clock;

    CreateIndex_OneIntCustom( ds );

    double      elapsed = clock.elapsed();

    std::cout << "create index on integer field. custom sort (" << ds->RecordCount() << " records) " << elapsed << " secs\n";
}

//******************************************************
// modify dataset. two integer fields, one string field
//******************************************************
void FASTCALL run_ModifyDataset( tblFiles_ptr& ds )
{
    ds_string       sstr( 200, 'h' );
    boost::timer    clock;

#ifndef __GNUG__
    ModifyDataset( ds->GetIterator(), sstr );
#else
    std::cout << "ModifyDataset() not called. gcc bug\n";
#endif

    double      elapsed = clock.elapsed();

    std::cout << "modify dataset (" << ds->RecordCount() << " records) " << elapsed << " secs\n";
}

//******************************************************
// add 20000 new records. set three integer fields and one string field. no live indexes
//******************************************************
void FASTCALL run_AddRecords_NoIndex( tblFiles_ptr& ds )
{
    boost::timer            clock;

    AddRecords_NoIndex( ds, ds_string( "record description" ) );

    double      elapsed = clock.elapsed();

    std::cout << "add records. no live index (" << ds->RecordCount() << " records) " << elapsed << " secs\n";
}

//******************************************************
// add 20000 new records. set three integer fields and one string field. one live index on two integer fields
//******************************************************
void FASTCALL run_AddRecords_OneIndex( tblFiles_ptr& ds )
{
    tblFiles::index_ptr     idx = CreateIndex_TwoInts_Other( ds );
    boost::timer            clock;

    AddRecords_OneIndex( ds, ds_string( "record description" ) );

    double      elapsed = clock.elapsed();

    std::cout << "add records. one live index (" << ds->RecordCount() << " records) " << elapsed << " secs\n";
}

//******************************************************
// locate with two fields
//******************************************************
void FASTCALL run_LocateRecord_Two( tblFiles_ptr& ds )
{
    boost::timer            clock;

    LocateRecord_Two( ds );

    double      elapsed = clock.elapsed();

    std::cout << "locate with two fields (" << ds->RecordCount() << " records) " << elapsed << " secs\n";
}

//******************************************************
// find with two fields
//******************************************************
void FASTCALL run_FindRecord_Two( tblFiles_ptr& ds )
{
    tblFiles::index_ptr     idx = CreateIndex_TwoInts_Other( ds );
    boost::timer            clock;

    FindRecord_Two( idx );

    double      elapsed = clock.elapsed();

    std::cout << "find with two fields x 1000 x 2 (" << ds->RecordCount() << " records) " << elapsed << " secs\n";
}

}; // namespace

void FASTCALL RunProfile( smds::Database& database )
{
    std::cout << "\n\n";

    tblFiles_ptr    ds = run_FillTable( database );

    run_CreateIndex_OneInt( ds );
    run_CreateIndex_TwoInts( ds );
    run_CreateIndex_OneIntCustom( ds );

    run_AddRecords_OneIndex( ds );
    run_AddRecords_NoIndex( ds );

    run_ModifyDataset( ds );
    run_LocateRecord_Two( ds );
    run_FindRecord_Two( ds );
}
//---------------------------------------------------------------------------

