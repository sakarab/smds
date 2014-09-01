//---------------------------------------------------------------------------
#ifndef FMainH
#define FMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <Db.hpp>
#include <DBClient.hpp>
#include <Provider.hpp>
#include <ComCtrls.hpp>
#include <dsFields.h>
#include <DBTables.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
#include "uTest.h"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TButton *Button1;
    TADOConnection *ADOConnection;
    TADOQuery *ADOQuery;
    TClientDataSet *ClientDataSet;
    TDataSetProvider *DataSetProvider;
    TButton *Button2;
    TDatabase *Database;
    TQuery *Query;
    TDBNavigator *DBNavigator1;
    TDBEdit *DBEdit1;
    TDBEdit *DBEdit2;
    TListView *lvList;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall lvListData(TObject *Sender, TListItem *Item);
private:	// User declarations
    tblFiles_ptr    mFiles;
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
    virtual __fastcall ~TfrmMain();
};
//---------------------------------------------------------------------------
extern TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
