//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FMain6.h"
#include "uStats.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmMain *frmMain;
using namespace smds;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner), mDraws(new tDRAWS())
{
    AvailableStats      stats;

    for ( int n = 0 ; n < stats.Count() ; ++n )
        lbStats->Items->Add( stats.GetStat( n ).ShortDescr );
}
//---------------------------------------------------------------------------
void TfrmMain::LoadData()
{
    if ( mDraws->IsEmpty() )
    {
        DbEngine    engine = SelectDbEngine( "DAO" );
        Database    database = engine.NewConnection( "G:\\Data\\Lotto.mdb" );

        mDraws->Open( database, 0 );
    }
}
//---------------------------------------------------------------------------
void TfrmMain::RunOne( int idx )
{
    AvailableStats().GetStat( idx ).Execute( mDraws, sgGrid );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::msQuitClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actLoadDataExecute(TObject *Sender)
{
    LoadData();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actRunSelectedExecute(TObject *Sender)
{
    LoadData();

    int     idx = lbStats->ItemIndex;

    if ( idx >= 0 )
    {
        RunOne( idx );
        sgGrid->Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actRunAllExecute(TObject *Sender)
{
    LoadData();

    AvailableStats      stats;

    for ( int n = 0 ; n < stats.Count() ; ++n )
        RunOne( n );
    sgGrid->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::lbStatsClick(TObject *Sender)
{
    int     idx = lbStats->ItemIndex;

    if ( idx >= 0 )
        mmHelp->Lines->Text = AvailableStats().GetStat( idx ).LongDescr;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::sgGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
    sgGrid->Canvas->TextOutA( Rect.Left+2, Rect.Top+2, sgGrid->Cells[ACol][ARow] );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::msClearReportClick(TObject *Sender)
{
    sgGrid->RowCount = 1;
    for ( int n = 0 ; n < sgGrid->ColCount ; ++n )
        sgGrid->Cells[n][0] = "";
    sgGrid->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::lbStatsDblClick(TObject *Sender)
{
    LoadData();
    actRunSelected->Execute();
}
//---------------------------------------------------------------------------

