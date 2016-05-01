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

#include "uUntypedTest.h"
//---------------------------------------------------------------------------

using namespace smds;

namespace untyped
{

//***********************************************************************
//******    WhileLoop
//***********************************************************************
void FASTCALL WhileLoop( record_iterator ptr )
{
    while ( ! ptr.eof() )
        ++ptr;
}
//***********************************************************************
//******    ForLoop
//***********************************************************************
void FASTCALL ForLoop( record_iterator ptr )
{
    for ( int n = 0, end = ptr.RecordCount() ; n < end ; ++n )
        ++ptr;
}
//***********************************************************************
//******    CheckNull
//***********************************************************************
int FASTCALL CountNulls_1( record_iterator ptr )
{
    int                 result = 0;
    const cFieldDef&    zipID_field = ptr.GetFieldDefs()->FieldByName( "zipID" );

    ptr.First();
    for ( int n = 0, end = ptr.RecordCount() ; n < end ; ++n, ++ptr )
        if ( ptr.Value( zipID_field ).IsNull() )
            ++result;
    return result;
}

//***********************************************************************
//******    CheckNull
//***********************************************************************
int FASTCALL CountNulls_2( record_iterator ptr )
{
    int                 result = 0;

    ptr.First();
    for ( int n = 0, end = ptr.RecordCount() ; n < end ; ++n, ++ptr )
        if ( ptr.FieldByName( "zipID" )->IsNull() )
            ++result;
    return result;
}

//***********************************************************************
//******    dsDatasetModify
//***********************************************************************
void FASTCALL dsDatasetModify_1( record_iterator ds, const ds_string& descr )
{
    const cFieldDef&    FileID_field = ds.GetFieldDefs()->FieldByName( "FileID" );
    const cFieldDef&    fSize_field = ds.GetFieldDefs()->FieldByName( "fSize" );
    const cFieldDef&    Description_field = ds.GetFieldDefs()->FieldByName( "Description" );
    const Variant       vdescr( descr );

    ds.First();
    for ( int n = 0, end = ds.RecordCount() ; n < end ; ++n, ++ds )
    {
        ds.Value( FileID_field, n );
        ds.Value( fSize_field, n );
        ds.Value( Description_field, vdescr );
    }
}

void FASTCALL dsDatasetModify( record_iterator ds )
{
    ds_string   sstr( 200, 'h' );

    dsDatasetModify_1( ds, sstr );
}

}; // namespace untyped

using namespace untyped;

void FASTCALL UntypedTest( Database& database )
{
    spTable     table( new Table( "tblFiles" ) );

    table->AddField( "FileID",       fkData, ftInteger,  4 );
    table->AddField( "PathID",       fkData, ftInteger,  4 );
    table->AddField( "LongFileName", fkData, ftString,   255 );
    table->AddField( "fSize",        fkData, ftInteger,  4 );
    table->AddField( "fDate",        fkData, ftDateTime, 8 );
    table->AddField( "Description",  fkData, ftString,   255 );
    table->AddField( "zipID",        fkData, ftInteger,  4 );

    table->Open( database, 0 );

    WhileLoop( table->GetIterator() );
    ForLoop( table->GetIterator() );
    CountNulls_1( table->GetIterator() );
    CountNulls_2( table->GetIterator() );
}
//---------------------------------------------------------------------------