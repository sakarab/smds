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
//---------------------------------------------------------------------------

using namespace smds;

namespace
{

//******************************************************
// fill table
//******************************************************
void FASTCALL FillTable( Database& database, tblFiles_ptr& ds )
{
    ds->Open( database, 0 );
}

tblFiles_ptr FASTCALL run_FillTable( Database& database )
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
tblFiles::index_ptr FASTCALL CreateIndex_OneInt( tblFiles_ptr& ds )
{
    return ds->NewIndex( cIndexField( "PathID", cIndexField::Descending ) );
}

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
tblFiles::index_ptr FASTCALL CreateIndex_TwoInts( tblFiles_ptr& ds )
{
    return ds->NewIndex( OpenIndexFields( cIndexField( "fSize" ), cIndexField( "PathID", cIndexField::Descending ) ) );
}

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
class idx_ByPathID : public tblFiles::sort_compare
{
private:
    // non copyable
    CDFASTCALL idx_ByPathID( const idx_ByPathID& src );
    idx_ByPathID& FASTCALL operator=( const idx_ByPathID& src );
protected:
    virtual bool FASTCALL typed_compare( const tblFiles::raw& item1, const tblFiles::raw& item2 )
    {
        return ( item1.GetPathID() > item2.GetPathID() );
    }
public:
    CDFASTCALL idx_ByPathID() : tblFiles::sort_compare()        {} // empty
};

tblFiles::index_ptr FASTCALL CreateIndex_OneIntCustom( tblFiles_ptr& ds )
{
    return ds->NewIndex( spSortCompare( new idx_ByPathID() ) );
}

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
void FASTCALL ModifyDataset( tblFiles::iterator ds_it, const ds_string& descr )
{
    ds_it.First();
    for ( int n = 0, end = ds_it.RecordCount() ; n < end ; ++n, ++ds_it )
    {
        ds_it->SetFileID( n );
        ds_it->SetfSize( n );
        ds_it->SetDescription( descr );
    }
}

void FASTCALL run_ModifyDataset( tblFiles_ptr& ds )
{
    ds_string       sstr( 200, 'h' );
    boost::timer    clock;

    ModifyDataset( ds->GetIterator(), sstr );

    double      elapsed = clock.elapsed();

    std::cout << "modify dataset (" << ds->RecordCount() << " records) " << elapsed << " secs\n";
}

//******************************************************
// add 20000 new records. set three integer fields and one string field. no live indexes
//******************************************************
void FASTCALL AddRecords_NoIndex( tblFiles_ptr& ds, const ds_string& descr )
{
    UpdateLocker    lock( ds );

    for ( int n = 0 ; n < 20000 ; ++n )
    {
        tblFiles::record    new_record = ds->NewRecord();

        new_record->SetFileID( n );
        new_record->SetPathID( n );
        new_record->SetfSize( n );
        new_record->SetDescription( descr );
        ds->AddRecord( new_record );
    }
}

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
void FASTCALL AddRecords_OneIndex( tblFiles_ptr& ds, const ds_string& descr )
{
    UpdateLocker    lock( ds );

    for ( int n = 0 ; n < 20000 ; ++n )
    {
        tblFiles::record    new_record = ds->NewRecord();

        new_record->SetFileID( n );
        new_record->SetPathID( n );
        new_record->SetfSize( n );
        new_record->SetDescription( descr );
        ds->AddRecord( new_record );
    }
}

void FASTCALL run_AddRecords_OneIndex( tblFiles_ptr& ds )
{
    tblFiles::index_ptr     idx = CreateIndex_TwoInts( ds );
    boost::timer            clock;

    AddRecords_OneIndex( ds, ds_string( "record description" ) );

    double      elapsed = clock.elapsed();

    std::cout << "add records. one live index (" << ds->RecordCount() << " records) " << elapsed << " secs\n";
}

//******************************************************
// locate with two fields
//******************************************************
bool FASTCALL LocateRecord_Two( tblFiles_ptr& ds )
{
    tblFiles::iterator  iter = ds->Locate( OpenValues( 19999, 19998 ),
                                           OpenFindFields( "FileID", "PathID" ) );
    return ! iter.eof();
}

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
bool FASTCALL FindRecord_Two( tblFiles::index_ptr& idx )
{
    tblFiles::index::iterator   it = idx->Find( OpenValues( 18999, 18999 ) );

    return ! it.eof();
}

void FASTCALL run_FindRecord_Two( tblFiles_ptr& ds )
{
    tblFiles::index_ptr     idx = CreateIndex_TwoInts( ds );
    boost::timer            clock;

    for ( int n = 0 ; n < 1000 ; ++n )
        FindRecord_Two( idx );

    double      elapsed = clock.elapsed();

    std::cout << "find with two fields x 1000 (" << ds->RecordCount() << " records) " << elapsed << " secs\n";
}

}; // namespace

void FASTCALL RunProfile()
{
    std::cout << "\n\n";

    // DbEngine        engine = SelectDbEngine( "ODBC" );
    // Database        database = engine.NewConnection( ODBC_DirData_Conn );

    DbEngine        engine = SelectDbEngine( "DAO" );
    Database        database = engine.NewConnection( DAO_Dirdata_Conn );

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

