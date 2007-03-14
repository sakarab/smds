//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FMain.h"
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
__fastcall TfrmMain::~TfrmMain()
{
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
void __fastcall TfrmMain::Button2Click(TObject *Sender)
{
    DoFetch( ADOQuery, DataSetProvider, ClientDataSet );
    ShowMessage( "Done" );
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
    Item->SubItems->Add( "" );
    Item->SubItems->Add( ds->GetDescription().c_str() );
    Item->SubItems->Add( IntToStr( ds->GetzipID() ) );
}
//---------------------------------------------------------------------------

