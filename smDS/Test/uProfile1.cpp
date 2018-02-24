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
#include "uProfile1.h"
//---------------------------------------------------------------------------

using namespace smds;

namespace profile
{

//******************************************************
// fill table
//******************************************************
void FASTCALL FillTable( Database& database, tblFiles_ptr& ds )
{
    ds->Open( database, 0 );
}

//******************************************************
// create index on integer field
//******************************************************
tblFiles::index_ptr FASTCALL CreateIndex_OneInt( tblFiles_ptr& ds )
{
    return ds->NewIndex( cIndexField( CCTEXT( "PathID" ), cIndexField::Descending ) );
}

//******************************************************
// create index on two integer fields
//******************************************************
tblFiles::index_ptr FASTCALL CreateIndex_TwoInts( tblFiles_ptr& ds )
{
    return ds->NewIndex( OpenIndexFields( cIndexField( CCTEXT( "fSize" ) ), cIndexField( CCTEXT( "PathID" ), cIndexField::Descending ) ) );
}

tblFiles::index_ptr FASTCALL CreateIndex_TwoInts_Other( tblFiles_ptr& ds )
{
#if defined ( _MSC_VER )
    tblFiles::iterator  it = ds->GetIterator();
#endif
    return ds->NewIndex( OpenIndexFields( cIndexField( CCTEXT( "fSize" ) ), cIndexField( CCTEXT( "PathID" ), cIndexField::Descending ) ) );
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

//******************************************************
// modify dataset. two integer fields, one string field
//******************************************************
void FASTCALL ModifyDataset( tblFiles::iterator ds_it, const ds_string& descr )
{
    ds_it.First();
    for ( int n = 0, end = ds_it.RecordCount() ; n < end ; ++n, ++ds_it )
    {
        ds_it->SetFileID( n );
        ds_it->SetzipID( n );
        ds_it->SetDescription( descr );
    }
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

//******************************************************
// add 20000 new records. set three integer fields and one string field. one live index on two integer fields
//******************************************************
void FASTCALL AddRecords_OneIndex( tblFiles_ptr& ds, const ds_string& descr )
{
#if defined ( _MSC_VER )
    tblFiles::iterator  it = ds->GetIterator();
#endif

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

//******************************************************
// locate with two fields
//******************************************************
bool FASTCALL LocateRecord_Two( tblFiles_ptr& ds )
{
    tblFiles::iterator  iter = ds->Locate( OpenValues( 19998, 19998 ),
                                           OpenFindFields( CCTEXT( "FileID" ), CCTEXT( "PathID" ) ) );
    return ! iter.eof();
}

//******************************************************
// find with two fields
//******************************************************
namespace
{

bool FASTCALL FindRecord_Two_No( tblFiles::index_ptr& idx )
{
    tblFiles::index::iterator   it = idx->Find( OpenValues( 18888, 18999 ) );

    return ! it.eof();
}

bool FASTCALL FindRecord_Two_Yes( tblFiles::index_ptr& idx )
{
    tblFiles::index::iterator   it = idx->Find( OpenValues( 18999, 18999 ) );

    return ! it.eof();
}

}; // namespace

void FASTCALL FindRecord_Two( tblFiles::index_ptr& idx )
{
    for ( int n = 0 ; n < 1000 ; ++n )
        if ( ! FindRecord_Two_No( idx ) )
            FindRecord_Two_Yes( idx );
}

}; // namespace profile
//---------------------------------------------------------------------------
