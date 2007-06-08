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
#include <dsIndex.h>
//---------------------------------------------------------------------------

using namespace smds;

namespace
{

//******************************************************
// fill table
//******************************************************
void FillTable( Database& database, tblFiles_ptr& ds )
{
    ds->Open( database, 0 );
}

tblFiles_ptr run_FillTable( Database& database )
{
    tblFiles_ptr    result( new tblFiles() );

    FillTable( database, result );
    return result;
}

//******************************************************
// create index on integer field
//******************************************************
tblFiles::index CreateIndex_OneInt( tblFiles_ptr& ds )
{
    // return ds->NewIndex( cIndexField( "PathID", cIndexField::Descending ) );
}

void run_CreateIndex_OneInt( tblFiles_ptr& ds )
{
    CreateIndex_OneInt( ds );
}

//******************************************************
// create index on two integer fields
//******************************************************
tblFiles::index CreateIndex_TwoInts( tblFiles_ptr& ds )
{
    // return ds->NewIndex( OpenIndexFields( cIndexField( "fSize" ), cIndexField( "PathID", cIndexField::Descending ) ) );
}

void run_CreateIndex_TwoInts( tblFiles_ptr& ds )
{
    CreateIndex_TwoInts( ds );
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

tblFiles::index CreateIndex_OneIntCustom( tblFiles_ptr& ds )
{
    // return ds->NewIndex( spSortCompare( new idx_ByPathID() ) );
}

void run_CreateIndex_OneIntCustom( tblFiles_ptr& ds )
{
    CreateIndex_OneIntCustom( ds );
}

//******************************************************
// modify dataset. two integer fields, one string field
//******************************************************

//******************************************************
// add 20000 new records. set three integer fields and one string field. no live indexes
//******************************************************

//******************************************************
// add 20000 new records. set three integer fields and one string field. one live index on two integer fields
//******************************************************

//******************************************************
// locate with two fields
//******************************************************

//******************************************************
// find with two fields
//******************************************************

}; // namespace

void FASTCALL RunProfile()
{
    // DbEngine        engine = SelectDbEngine( "ODBC" );
    // Database        database = engine.NewConnection( ODBC_DirData_Conn );

}
//---------------------------------------------------------------------------

