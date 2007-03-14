//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "bcbTest.h"
//---------------------------------------------------------------------------
void __fastcall FillList( TListView *lv, const ds::cFieldDefs_& field_defs, tblFiles_ptr dataset )
{
    lv->Items->Clear();
    lv->Columns->Clear();
    lv->ViewStyle = vsReport;
    for ( int n = 0 ; n < field_defs.mCount ; ++n )
    {
        TListColumn    *col = lv->Columns->Add();

        col->Caption = field_defs.mFieldDefs[n].mName;
        if ( field_defs.mFieldDefs[n].mDataType == ds::ftInteger )
            col->Alignment = taRightJustify;
    }

    tblFiles::iterator      ds = dataset->GetIterator();

    lv->Items->Count = ds.RecordCount();
}
//---------------------------------------------------------------------------
static void DoLoop_01( TClientDataSet *ds )
{
    while ( ! ds->Eof )
        ds->Next();
}

void __fastcall ClientDatasetModify( TClientDataSet *ds, TField *FileID, TField *PathID )
{
    int     n = 0;

    while ( ! ds->Eof )
    {
        ds->Edit();
        FileID->AsInteger = n;
        PathID->AsInteger = n;
        ds->Post();
        ++n;
        ds->Next();
    }
}

void __fastcall CreateIndex( TClientDataSet *ds,
                             const AnsiString& idx_name, const AnsiString& fields,
                             Db::TIndexOptions options, const AnsiString& empty_str )
{
    ds->AddIndex( idx_name, fields, options, empty_str, empty_str, 0 );
    ds->IndexName = idx_name;
}

int __fastcall CheckIndex( TClientDataSet *ds, TField *PathID )
{
    int     result = 0;
    int     first_value = PathID->AsInteger;

    ds->Next();
    while ( ! ds->Eof )
    {
        int     second_value = PathID->AsInteger;

        if ( first_value > second_value )
            ++result;
        first_value = second_value;
        ds->Next();
    }
    return ( result );
}

void __fastcall AddRecords( TClientDataSet *ds, TField *FileID, TField *PathID, TField *fSize )
{
    for ( int n = 0 ; n < 20000 ; ++n )
    {
        ds->Insert();
        FileID->AsInteger = n;
        PathID->AsInteger = n;
        fSize->AsInteger = n;
        ds->Post();
    }
}

bool __fastcall LocateRecord( TClientDataSet *ds )
{
    return ( ds->Locate( "FileID;PathID", VarArrayOf( OPENARRAY(Variant,(19999,19998)) ), TLocateOptions() ) );
}

bool __fastcall FindRecord( TClientDataSet *ds )
{
    return ( ds->Locate( "PathID;fSize", VarArrayOf( OPENARRAY(Variant,(19999,19998)) ), TLocateOptions() ) );
}

__int64 __fastcall SaveToStream( TClientDataSet *ds )
{
    std::auto_ptr<TMemoryStream>    st( new TMemoryStream() );

    ds->SaveToStream( st.get(), dfBinary );
    return ( st->Size );
}

void __fastcall DoFetch( TADOQuery *ADOQuery, TDataSetProvider* Provider, TClientDataSet *ClientDataSet )
{
    Provider->DataSet = ADOQuery;
    ADOQuery->SQL->Text = "select * from tblFiles";
    ClientDataSet->Active = true;
    ClientDataSet->First();
    DoLoop_01( ClientDataSet );

    ClientDataSet->First();
    ClientDataSet->DisableControls();
    ClientDatasetModify( ClientDataSet, ClientDataSet->FieldByName( "FileID" ), ClientDataSet->FieldByName( "fSize" ) );
    ClientDataSet->EnableControls();

    Db::TIndexOptions   opts;

    CreateIndex( ClientDataSet, "idx_ByPathID", "PathID", opts, "" );
    ClientDataSet->First();
    CheckIndex( ClientDataSet, ClientDataSet->FieldByName( "PathID" ) );
    ClientDataSet->DeleteIndex( "idx_ByPathID" );

    ClientDataSet->DisableControls();
    AddRecords( ClientDataSet, ClientDataSet->FieldByName( "FileID" ),
                               ClientDataSet->FieldByName( "PathID" ),
                               ClientDataSet->FieldByName( "fSize" ) );
    ClientDataSet->EnableControls();

    LocateRecord( ClientDataSet );
    CreateIndex( ClientDataSet, "idx_ByPathID", "PathID;fSize", opts, "" );
    FindRecord( ClientDataSet );

    ShowMessage( IntToStr( SaveToStream( ClientDataSet ) ) );

    //ClientDataSet->AddIndex( "idx_ByPathID", "PathID", opts, "", "", 0 );
    //ClientDataSet->IndexName = "idx_ByPathID";
    //ClientDataSet->First();
    //DoLoop_01( ClientDataSet );
}
//---------------------------------------------------------------------------

