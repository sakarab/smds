//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FMain.h"
#include "uSub.h"
#include <string>
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
    dsCustom->CreateDataSet();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRunSqlClick(TObject *Sender)
{
    if ( edtTableName->Text.IsEmpty() )
        return;

    OpenGuard<TDatabase>        db( Database );
    std::vector<AnsiString>     h;

    sub::RunQuery( Query, edtPrefix->Text, edtTableName->Text, mmSql->Lines->Text, h );
    Memo->Lines->BeginUpdate();
    Memo->Lines->Clear();
    for ( int n = 0, eend = h.size() ; n < eend ; ++n )
        Memo->Lines->Add( h[n] );
    Memo->Lines->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::msOpenSqlClick(TObject *Sender)
{
    OpenDlg->FilterIndex = 1;
    if ( OpenDlg->Execute() )
        mmSql->Lines->LoadFromFile( OpenDlg->FileName );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::msOpenCustomClick(TObject *Sender)
{
    OpenDlg->FilterIndex = 2;
    if ( OpenDlg->Execute() )
    {
        dsCustom->LoadFromFile( OpenDlg->FileName );
        dsCustom->IndexName = "OrderIdx";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::msSaveSqlClick(TObject *Sender)
{
    SaveDlg->FilterIndex = 1;
    if ( SaveDlg->Execute() )
        mmSql->Lines->SaveToFile( SaveDlg->FileName );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::msSaveCustomClick(TObject *Sender)
{
    SaveDlg->FilterIndex = 2;
    if ( SaveDlg->Execute() )
    {
        dsCustom->MergeChangeLog();
        dsCustom->SaveToFile( SaveDlg->FileName, dfXML );
    }
}
//---------------------------------------------------------------------------
namespace {

const int max_data_type_enum = 8;
TFieldType  data_type_values[max_data_type_enum] = { ftBoolean, ftSmallint, ftInteger, ftFloat, ftDateTime, ftString, ftWideString, ftBlob };
const char *data_type_names[max_data_type_enum] = { "ftBool", "ftShort", "ftInteger", "ftDouble", "ftDateTime", "ftString", "ftWString", "ftBlob" };

const int max_field_kind_enum = 2;
const char *field_kind_names[max_field_kind_enum] = { "fkData", "fkInternalCalc" };

int EnumValue( const char *name, const char *names[], int num_elements )
{
    for ( int n = 0 ; n < num_elements ; ++n )
        if ( strcmp( name, names[n] ) == 0 )
            return ( n );
    throw Exception( "Invalid enum name" );
}

const char *EnumName( const int value, const char *names[], int num_elements )
{
    if ( value < num_elements )
        return ( names[value] );
    throw Exception( "Invalid enum value" );
}

};
//---------------------------------------------------------------------------
void __fastcall TfrmMain::dsCustomTypeGetText( TField *Sender, AnsiString &Text, bool DisplayText )
{
    Text = EnumName( Sender->AsInteger, field_kind_names, max_field_kind_enum );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::dsCustomTypeSetText(TField *Sender, const AnsiString Text)
{
    Sender->Value = EnumValue( Text.c_str(), field_kind_names, max_field_kind_enum );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::dsCustomDataTypeGetText(TField *Sender, AnsiString &Text, bool DisplayText)
{
    Text = EnumName( Sender->AsInteger, data_type_names, max_data_type_enum );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::dsCustomDataTypeSetText(TField *Sender, const AnsiString Text)
{
    Sender->Value = EnumValue( Text.c_str(), data_type_names, max_data_type_enum );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRunCustomClick(TObject *Sender)
{
    DisableControlsGuard<TClientDataSet>    disable( dsCustom );
    std::auto_ptr<TClientDataSet>           ds( new TClientDataSet( 0 ) );

    dsCustom->First();
    while ( ! dsCustom->Eof )
    {
        TFieldDef   *field_def = ds->FieldDefs->AddFieldDef();

        field_def->DataType = data_type_values[dsCustomDataType->Value];
        field_def->Name = dsCustomName->Value;
        field_def->Size = dsCustomSize->Value;
        field_def->FieldNo = dsCustomOrder->Value;
        //field_def->InternalCalcField = ;

        dsCustom->Next();
    }
    ds->CreateDataSet();

    std::vector<AnsiString>     h;

    sub::Run( ds->Fields, edtPrefix->Text, edtTableName->Text, h );
    Memo->Lines->BeginUpdate();
    Memo->Lines->Clear();
    for ( int n = 0, eend = h.size() ; n < eend ; ++n )
        Memo->Lines->Add( h[n] );
    Memo->Lines->EndUpdate();
}
//---------------------------------------------------------------------------

