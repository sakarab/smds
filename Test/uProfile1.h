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
#ifndef uProfile1H
#define uProfile1H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include "uTables.h"
//---------------------------------------------------------------------------

namespace profile
{

//******************************************************
// fill table
//******************************************************
void FASTCALL FillTable( smds::Database& database, tblFiles_ptr& ds );

//******************************************************
// create index on integer field
//******************************************************
tblFiles::index_ptr FASTCALL CreateIndex_OneInt( tblFiles_ptr& ds );

//******************************************************
// create index on two integer fields
//******************************************************
tblFiles::index_ptr FASTCALL CreateIndex_TwoInts( tblFiles_ptr& ds );
tblFiles::index_ptr FASTCALL CreateIndex_TwoInts_Other( tblFiles_ptr& ds );

//******************************************************
// create index on integer field with a custom sort function
//******************************************************
tblFiles::index_ptr FASTCALL CreateIndex_OneIntCustom( tblFiles_ptr& ds );

//******************************************************
// modify dataset. two integer fields, one string field
//******************************************************
void FASTCALL ModifyDataset( tblFiles::iterator ds_it, const ds_string& descr );

//******************************************************
// add 20000 new records. set three integer fields and one string field. no live indexes
//******************************************************
void FASTCALL AddRecords_NoIndex( tblFiles_ptr& ds, const ds_string& descr );

//******************************************************
// add 20000 new records. set three integer fields and one string field. one live index on two integer fields
//******************************************************
void FASTCALL AddRecords_OneIndex( tblFiles_ptr& ds, const ds_string& descr );

//******************************************************
// locate with two fields
//******************************************************
bool FASTCALL LocateRecord_Two( tblFiles_ptr& ds );

//******************************************************
// find with two fields
//******************************************************
void FASTCALL FindRecord_Two( tblFiles::index_ptr& idx );

}; // namespace profile

//---------------------------------------------------------------------------
#endif

