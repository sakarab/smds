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

    // table->Open( database, 0 );
}
//---------------------------------------------------------------------------

