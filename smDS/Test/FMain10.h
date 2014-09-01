//---------------------------------------------------------------------------
#ifndef FMain10H
#define FMain10H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBClient.hpp>
#include <DBCtrls.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Provider.hpp>
//---------------------------------------------------------------------------
#include "uTables.h"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TButton *Button1;
    TButton *Button2;
    TDBNavigator *DBNavigator1;
    TDBEdit *DBEdit1;
    TDBEdit *DBEdit2;
    TListView *lvList;
    TADOConnection *ADOConnection;
    TADOQuery *ADOQuery;
    TClientDataSet *ClientDataSet;
    TDataSetProvider *DataSetProvider;
    TDatabase *Database;
    TQuery *Query;
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall lvListData(TObject *Sender, TListItem *Item);
private:	// User declarations
    tblFiles_ptr    mFiles;
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
