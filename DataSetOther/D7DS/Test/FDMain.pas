unit FDMain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, DBTables, DB, Provider, DBClient, ADODB;

type
  TfrmMain = class(TForm)
    ClientDataSet: TClientDataSet;
    DataSetProvider: TDataSetProvider;
    Database: TDatabase;
    Query: TQuery;
    Button2: TButton;
    ADOConnection: TADOConnection;
    ADOQuery: TADOQuery;
    Button1: TButton;
    procedure Button2Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    procedure DoFetchBDE;
    procedure DoFetchADO;
  public
  end;

var
  frmMain: TfrmMain;

implementation

{$R *.dfm}

//procedure Foo( path_name:string );
//begin
//  ShowMessage( ExtractFilePath( path_name ) );
//  if not DirectoryExists( 'aaa' ) then
//    CreateDir( 'aaa' );
//  ForceDirectories( ExtractFilePath( path_name ) );
//end;

procedure TfrmMain.Button2Click(Sender: TObject);
begin
  DoFetchADO();
  ShowMessage( 'Done' );
end;

procedure DoLoop_01( ds:TClientDataSet );
begin
  while not ds.Eof do
    ds.Next;
end;

procedure ClientDatasetModify_1( ds:TClientDataSet ; fldFileID,fldPathID,fldDescr:TField );
var
  n : integer;
  descr : string;
begin
  n := 0;
  descr := 'File';

  ds.First;
  while not ds.Eof do begin
    ds.Edit;
    fldFileID.AsInteger := n;
    fldPathID.AsInteger := n;
    //fldDescr.AsString := descr;
    ds.Post;
    Inc( n );
    ds.Next;
  end;
end;

procedure ClientDatasetModify_2( ds:TClientDataSet ; fldFileID,fldPathID,fldDescr:TField );
var
  n : integer;
  descr : string;
begin
  n := 0;
  descr := 'File';

  ds.First;
  while not ds.Eof do begin
    ds.Edit;
    fldFileID.AsInteger := n;
    fldPathID.AsInteger := n;
    //fldDescr.AsString := descr;
    ds.Post;
    Inc( n );
    ds.Next;
  end;
end;

procedure AddRecords( ds:TClientDataSet );
begin
end;

procedure CreateIndex_g1( ds:TClientDataSet );
begin
end;

procedure CreateIndex_g2( ds:TClientDataSet );
begin
end;

procedure TfrmMain.DoFetchADO;
begin
  DataSetProvider.DataSet := ADOQuery;
  ClientDataSet.Active := True;
  ClientDataSet.First;
  DoLoop_01( ClientDataSet );

  ClientDataSet.DisableControls;
  try
    ClientDatasetModify_1( ClientDataSet, ClientDataSet.FieldByName( 'FileID' ),
                                          ClientDataSet.FieldByName( 'PathID' ),
                                          ClientDataSet.FieldByName( 'Description' ) );
    ClientDatasetModify_2( ClientDataSet, ClientDataSet.FieldByName( 'FileID' ),
                                          ClientDataSet.FieldByName( 'PathID' ),
                                          ClientDataSet.FieldByName( 'Description' ) );
    AddRecords( ClientDataSet );
    CreateIndex_g1( ClientDataSet );
  finally
    ClientDataSet.EnableControls;
  end;
end;

procedure TfrmMain.DoFetchBDE;
begin
  DataSetProvider.DataSet := Query;
  ClientDataSet.Active := True;
  ClientDataSet.First;
  DoLoop_01( ClientDataSet );

  ClientDataSet.DisableControls;
  try
    ClientDatasetModify_1( ClientDataSet, ClientDataSet.FieldByName( 'FileID' ),
                                          ClientDataSet.FieldByName( 'PathID' ),
                                          ClientDataSet.FieldByName( 'Description' ) );
    ClientDatasetModify_2( ClientDataSet, ClientDataSet.FieldByName( 'FileID' ),
                                          ClientDataSet.FieldByName( 'PathID' ),
                                          ClientDataSet.FieldByName( 'Description' ) );
  finally
    ClientDataSet.EnableControls;
  end;
end;

procedure Foo( const v:Variant );
begin
end;

procedure VariantTest;
var
  v : Variant;
  dd : double;
begin
  dd := 8;
  v := True;
  Foo( v );
  v := 4;
  Foo( v );
  v := dd;
  Foo( v );
end;

procedure TfrmMain.Button1Click(Sender: TObject);
begin
  VariantTest;
  ShowMessage( IntToStr( sizeof(double) ) );
end;

end.
