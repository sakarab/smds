//---------------------------------------------------------------------------
#ifndef FMain6H
#define FMain6H
//---------------------------------------------------------------------------
#include "uTables.h"
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *msLoadData;
    TMenuItem *N1;
    TMenuItem *msQuit;
    TBevel *Bevel1;
    TActionList *ActionList;
    TAction *actLoadData;
    TMenuItem *N2;
    TMenuItem *msRunSelected;
    TMenuItem *msRunAll;
    TAction *actRunSelected;
    TAction *actRunAll;
    TStatusBar *StatusBar1;
    TLabel *Label1;
    TPanel *Panel1;
    TListBox *lbStats;
    TSplitter *Splitter1;
    TMemo *mmHelp;
    TSplitter *Splitter2;
    TStringGrid *sgGrid;
    TMenuItem *msClearReport;
    void __fastcall msQuitClick(TObject *Sender);
    void __fastcall actLoadDataExecute(TObject *Sender);
    void __fastcall actRunSelectedExecute(TObject *Sender);
    void __fastcall actRunAllExecute(TObject *Sender);
    void __fastcall lbStatsClick(TObject *Sender);
    void __fastcall sgGridDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
    void __fastcall msClearReportClick(TObject *Sender);
    void __fastcall lbStatsDblClick(TObject *Sender);
private:	// User declarations
    spDRAWS     mDraws;
    void LoadData();
    void RunOne( int idx );
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
