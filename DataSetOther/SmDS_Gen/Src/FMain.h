//---------------------------------------------------------------------------
#ifndef FMainH
#define FMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <DBClient.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TButton *btnRunSql;
    TEdit *edtTableName;
    TLabel *Label1;
    TDatabase *Database;
    TQuery *Query;
    TEdit *edtPrefix;
    TLabel *Label2;
    TPageControl *PageControl1;
    TTabSheet *tsSql;
    TMemo *mmSql;
    TTabSheet *tsCustomFIelds;
    TTabSheet *tsResult;
    TMemo *Memo;
    TButton *btnRunCustom;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *msQuit;
    TMenuItem *msOpenSql;
    TMenuItem *msOpenCustom;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *msSaveSql;
    TMenuItem *msSaveCustom;
    TOpenDialog *OpenDlg;
    TSaveDialog *SaveDlg;
    TClientDataSet *dsCustom;
    TDataSource *srcCustom;
    TDBGrid *DBGrid1;
    TStringField *dsCustomName;
    TIntegerField *dsCustomType;
    TIntegerField *dsCustomDataType;
    TIntegerField *dsCustomSize;
    TIntegerField *dsCustomOrder;
    void __fastcall btnRunSqlClick(TObject *Sender);
    void __fastcall msOpenSqlClick(TObject *Sender);
    void __fastcall msOpenCustomClick(TObject *Sender);
    void __fastcall msSaveSqlClick(TObject *Sender);
    void __fastcall dsCustomTypeGetText(TField *Sender, AnsiString &Text,
          bool DisplayText);
    void __fastcall dsCustomTypeSetText(TField *Sender,
          const AnsiString Text);
    void __fastcall dsCustomDataTypeGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
    void __fastcall dsCustomDataTypeSetText(TField *Sender,
          const AnsiString Text);
    void __fastcall msSaveCustomClick(TObject *Sender);
    void __fastcall btnRunCustomClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
