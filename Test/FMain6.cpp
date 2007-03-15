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

  Please read the "readme" file in the root directory of this
  package for more copyright and license information.
****************************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FMain6.h"
#include "bcbTest.h"
#include "uTest.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmMain *frmMain;
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
    Test( mFiles );
    FillList( lvList, tblFiles_rec::GetFieldDefs(), mFiles );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::lvListData(TObject *Sender, TListItem *Item)
{
    tblFiles::iterator      ds = mFiles->GetIterator();

    ds.GotoMark( reinterpret_cast<void *>(Item->Index) );

    Item->Caption = IntToStr( ds->GetFileID() );
    Item->SubItems->Add( IntToStr( ds->GetPathID() ) );
    Item->SubItems->Add( ds->GetLongFileName().c_str() );
    Item->SubItems->Add( IntToStr( ds->GetfSize() ) );
    Item->SubItems->Add( DateTimeToStr( ds->GetfDate().AsDouble() ) );
    Item->SubItems->Add( ds->GetDescription().c_str() );
    Item->SubItems->Add( IntToStr( ds->GetzipID() ) );
}
//---------------------------------------------------------------------------

