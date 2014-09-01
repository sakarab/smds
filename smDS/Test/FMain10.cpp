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
#include <vcl.h>
#pragma hdrstop

#include "FMain10.h"
#include "bcbTest.h"
#include "uTest.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmMain *frmMain;

namespace
{

void FASTCALL ErrorReporter_( void *user_data, const char *error )
{
}

};

//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Button2Click(TObject *Sender)
{
    DoFetch( ADOQuery, DataSetProvider, ClientDataSet );
    ShowMessage( "Done" );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Button1Click(TObject *Sender)
{
    lvList->Items->Count = 0;
    mFiles = GetTblFiles();
    Test( mFiles, ErrorReporter_, this );
    FillList( lvList, tblFiles_rec::GetFieldDefs(), mFiles );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::lvListData(TObject *Sender, TListItem *Item)
{
    tblFiles::iterator      ds = mFiles->GetIterator();

    ds.GotoMark( reinterpret_cast<void *>(Item->Index) );

    if ( ds->FileID_IsNull() )
        Item->Caption = "";
    else
        Item->Caption = IntToStr( ds->GetFileID() );

    if ( ds->PathID_IsNull() )
        Item->SubItems->Add( "" );
    else
        Item->SubItems->Add( IntToStr( ds->GetPathID() ) );

    if ( ds->LongFileName_IsNull() )
        Item->SubItems->Add( "" );
    else
        Item->SubItems->Add( ds->GetLongFileName().c_str() );

    if ( ds->fSize_IsNull() )
        Item->SubItems->Add( "" );
    else
        Item->SubItems->Add( IntToStr( ds->GetfSize() ) );

    if ( ds->fDate_IsNull() )
        Item->SubItems->Add( "" );
    else
        Item->SubItems->Add( DateTimeToStr( ds->GetfDate().AsDouble() ) );

    if ( ds->Description_IsNull() )
        Item->SubItems->Add( "" );
    else
        Item->SubItems->Add( ds->GetDescription().c_str() );

    if ( ds->zipID_IsNull() )
        Item->SubItems->Add( "" );
    else
        Item->SubItems->Add( IntToStr( ds->GetzipID() ) );
}
//---------------------------------------------------------------------------

