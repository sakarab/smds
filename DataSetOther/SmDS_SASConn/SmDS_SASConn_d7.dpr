library SmDS_SASConn_d7;

{ Important note about DLL memory management: ShareMem must be the
  first unit in your library's USES clause AND your project's (select
  Project-View Source) USES clause if your DLL exports any procedures or
  functions that pass strings as parameters or function results. This
  applies to all strings passed to and from your DLL--even those that
  are nested in records and classes. ShareMem is the interface unit to
  the BORLNDMM.DLL shared memory manager, which must be deployed along
  with your DLL. To avoid using BORLNDMM.DLL, pass string information
  using PChar or ShortString parameters. }

uses
  SasShareMem,
  SysUtils,
  Classes,
  SasDbComp,
  SasCommon,
  Db,
  Contnrs,
  uSenList,
  Variants,
  Math;

{$R *.res}

var
  gSasSession : ISasSession;
  gMainAlias : string;
  gCompanyAlias : string;

// these must be in sync with "cFieldDataType" enum in "dsFields.h"
const
  cFieldDataType_ftBool     = 0;
  cFieldDataType_ftChar     = 1;
  cFieldDataType_ftWChar    = 2;
  cFieldDataType_ftShort    = 3;
  cFieldDataType_ftInteger  = 4;
  cFieldDataType_ftLong     = 5;
  cFieldDataType_ftDouble   = 6;
  cFieldDataType_ftDateTime = 7;
  cFieldDataType_ftString   = 8;
  cFieldDataType_ftWString  = 9;
  cFieldDataType_ftBlob     = 10;

type
  IDataProvider = Interface;

//***********************************************************************
//******    IDatabase
//***********************************************************************
  IDatabase = Interface
  ['{309FC0E0-5159-430A-BBB8-EE82271E0B64}']
    function CreateDataProvider : Pointer; stdcall;
    procedure DestroyDataProvider( conn:Pointer ); stdcall;
  end;

//***********************************************************************
//******    IFieldValuesAcceptor
//***********************************************************************
  IFieldValuesAcceptor = Interface
  ['{8B47BEDC-CE51-4C43-8FA7-43AEA6377ACA}']
    function FieldValue( field_name:PChar ; field_data_type:integer ; data:Pointer ; buff:Pointer ; field_data_size:integer ) : boolean; stdcall;
  end;

//***********************************************************************
//******    IDataProvider
//***********************************************************************
  IDataProvider = Interface
  ['{9E6BDCE5-3041-4430-9CFE-1C3970AF41C3}']
    procedure OpenSql( sql:PChar ); stdcall;
    function Eof() : boolean; stdcall;
    procedure Next(); stdcall;
    procedure CloseSql(); stdcall;

    procedure InitDataTransfer(); stdcall;
    procedure StepInitDataTransfer( field_name:PChar ; field_data_size:integer ; field_data_type:integer ; data:Pointer ); stdcall;
    procedure EndInitDataTransfer(); stdcall;

    function GetFieldValues( values_acceptor:Pointer {IFieldValuesAcceptor} ) : boolean; stdcall;
    procedure EndDataTransfer(); stdcall;

    procedure StartTransaction(); stdcall;
    procedure Commit(); stdcall;
    procedure RollBack(); stdcall;
    procedure ExecSql( sql:PChar ); stdcall;
  end;

//***********************************************************************
//******    TNRCInterfacedObject
//***********************************************************************
  TNRCInterfacedObject = class(TObject,IInterface)
  protected
    function QueryInterface(const IID: TGUID; out Obj): HResult; stdcall;
    function _AddRef: Integer; stdcall;
    function _Release: Integer; stdcall;
  end;

//***********************************************************************
//******    cDataConnection
//***********************************************************************
  cDataConnection = class(TNRCInterfacedObject, IDatabase)
  private
    mDatabase : TSasDbConnection;
  protected
    // IDatabase
    function CreateDataProvider : Pointer; stdcall;
    procedure DestroyDataProvider( conn:Pointer ); stdcall;
  public
    constructor Create( const connection_string:string );
    destructor Destroy; override;
    function GetDatabase : TSasDbConnection;
  end;

//***********************************************************************
//******    cDataProvider
//***********************************************************************
  TFieldFieldPair = class
  public
    mNativeField : TField;
    mFieldName : string;
    mFieldDataSize : integer;
    mFieldDataType : integer;
    mData : Pointer;
  end;

  cDataProvider = class(TNRCInterfacedObject, IDataProvider)
  private
    mDataConnection : cDataConnection;
    mQuery : TSasDataset;
    mFieldPairMap : TObjectList;
  protected
    // IDataProvider
    procedure OpenSql( sql:PChar ); stdcall;
    function Eof() : boolean; stdcall;
    procedure Next(); stdcall;
    procedure CloseSql(); stdcall;

    procedure InitDataTransfer(); stdcall;
    procedure StepInitDataTransfer( field_name:PChar ; field_data_size:integer ; field_data_type:integer ; data:Pointer ); stdcall;
    procedure EndInitDataTransfer(); stdcall;

    function GetFieldValues( values_acceptor:Pointer {IFieldValuesAcceptor} ) : boolean; stdcall;
    procedure EndDataTransfer(); stdcall;

    procedure StartTransaction(); stdcall;
    procedure Commit(); stdcall;
    procedure RollBack(); stdcall;
    procedure ExecSql( sql:PChar ); stdcall;
  public
    constructor Create( conn:cDataConnection );
    destructor Destroy; override;
  end;

// ADO-Delphi interaction spesific routines
procedure Proc(Reason: Integer);
begin
  Set8087CW( Default8087CW );
end;

procedure SetDefault;
var
  cw : Word;
begin
  asm FNSTCW cw end;
  Default8087CW := cw;
end;

function CmpSortFieldPairMap( item1,item2:pointer ) : integer;
begin
  Result := CompareText( TFieldFieldPair(item1).mFieldName, TFieldFieldPair(item2).mFieldName );
end;

function CmpFindFieldPairMap( item1,what:pointer ) : integer;
begin
  Result := CompareText( TFieldFieldPair(item1).mFieldName, PString(what)^ );
end;

{ TNRCInterfacedObject }

function TNRCInterfacedObject._AddRef: Integer;
begin
  Result := -1;
end;

function TNRCInterfacedObject._Release: Integer;
begin
  Result := -1;
end;

function TNRCInterfacedObject.QueryInterface(const IID: TGUID; out Obj): HResult;
begin
  pointer(Obj) := Self;
  Result := E_NOINTERFACE;
end;

{ cDataConnection }

constructor cDataConnection.Create(const connection_string:string);
begin
  inherited Create;
  mDatabase := TSasDbConnection.Create( nil );
  mDatabase.Session := gSasSession;
  mDatabase.Alias := connection_string;
end;

function cDataConnection.CreateDataProvider: Pointer;
var
  prov : IDataProvider;
begin
  prov := cDataProvider.Create( Self );
  Result := Pointer(prov);
end;

destructor cDataConnection.Destroy;
begin
  mDatabase.Free;
  inherited;
end;

procedure cDataConnection.DestroyDataProvider(conn: Pointer);
var
  data_provider : cDataProvider;
begin
  IDataProvider(conn).QueryInterface( IDataProvider, data_provider );
  data_provider.Free;
end;

function cDataConnection.GetDatabase: TSasDbConnection;
begin
  Result := mDatabase;
end;

{ cDataProvider }

procedure cDataProvider.CloseSql;
begin
  FreeAndNil( mQuery );
end;

procedure cDataProvider.Commit;
begin
end;

constructor cDataProvider.Create(conn: cDataConnection);
begin
  inherited Create;
  mDataConnection := conn;
  mFieldPairMap := TObjectList.Create;
end;

destructor cDataProvider.Destroy;
begin
  mFieldPairMap.Free;
  mQuery.Free;
  inherited;
end;

procedure cDataProvider.EndDataTransfer;
begin
  mFieldPairMap.Clear;
end;

procedure cDataProvider.EndInitDataTransfer;
begin
  mFieldPairMap.Sort( CmpSortFieldPairMap );
end;

function cDataProvider.Eof: boolean;
begin
  Result := mQuery.Eof;
end;

procedure cDataProvider.ExecSql(sql: PChar);
begin
end;

function cDataProvider.GetFieldValues( values_acceptor:Pointer {IFieldValuesAcceptor} ) : boolean;
var
  rec : TFieldFieldPair;
  value : Variant;
  v_bool : boolean;
  v_str : string;
  n : integer;
begin
  Result := False;
  for n := 0 to mFieldPairMap.Count - 1 do begin
    rec := TFieldFieldPair(mFieldPairMap[n]);
    value := rec.mNativeField.Value;
    if VarIsNull( value ) then
      IFieldValuesAcceptor(values_acceptor).FieldValue( PChar(rec.mFieldName), rec.mFieldDataType, rec.mData, nil, rec.mFieldDataSize )
    else case rec.mFieldDataType of
      cFieldDataType_ftBool     :
        begin
          v_bool := value;
          Result := IFieldValuesAcceptor(values_acceptor).FieldValue( PChar(rec.mFieldName), rec.mFieldDataType, rec.mData, @v_bool, rec.mFieldDataSize );
        end;
      cFieldDataType_ftChar     :
        begin
          v_str := value;
          Result := IFieldValuesAcceptor(values_acceptor).FieldValue( PChar(rec.mFieldName), rec.mFieldDataType, rec.mData, PChar(v_str), rec.mFieldDataSize );
        end;
      cFieldDataType_ftWChar    :
          raise Exception.Create( 'Field type not supported' );
      cFieldDataType_ftShort    :
        begin
          Result := IFieldValuesAcceptor(values_acceptor).FieldValue( PChar(rec.mFieldName), rec.mFieldDataType, rec.mData, @TVarData(value).VSmallInt, rec.mFieldDataSize );
        end;
      cFieldDataType_ftInteger  :
        begin
          Result := IFieldValuesAcceptor(values_acceptor).FieldValue( PChar(rec.mFieldName), rec.mFieldDataType, rec.mData, @TVarData(value).VInteger, rec.mFieldDataSize );
        end;
      cFieldDataType_ftLong     :
        begin
          Result := IFieldValuesAcceptor(values_acceptor).FieldValue( PChar(rec.mFieldName), rec.mFieldDataType, rec.mData, @TVarData(value).VInteger, rec.mFieldDataSize );
        end;
      cFieldDataType_ftDouble   :
        begin
          Result := IFieldValuesAcceptor(values_acceptor).FieldValue( PChar(rec.mFieldName), rec.mFieldDataType, rec.mData, @TVarData(value).VDouble, rec.mFieldDataSize );
        end;
      cFieldDataType_ftDateTime :
        begin
          Result := IFieldValuesAcceptor(values_acceptor).FieldValue( PChar(rec.mFieldName), rec.mFieldDataType, rec.mData, @TVarData(value).VDate, rec.mFieldDataSize );
        end;
      cFieldDataType_ftString   :
        begin
          v_str := value;
          Result := IFieldValuesAcceptor(values_acceptor).FieldValue( PChar(rec.mFieldName), rec.mFieldDataType, rec.mData, PChar(v_str), rec.mFieldDataSize );
        end;
      cFieldDataType_ftWString  :
          raise Exception.Create( 'Field type not supported' );
      cFieldDataType_ftBlob     :
          raise Exception.Create( 'Field type not supported' );
    end;
  end;
end;

procedure cDataProvider.InitDataTransfer;
begin
  mFieldPairMap.Clear;
end;

procedure cDataProvider.Next;
begin
  mQuery.Next;
end;

procedure cDataProvider.OpenSql(sql: PChar);
begin
  mQuery := TSasDataset.Create( nil );
  mQuery.Database := mDataConnection.GetDatabase;
  mQuery.Options := [dsoEnableIntegers, {dsoTransAnsiJoins,} dsoServerCursor];
  mQuery.Sql.Text := sql;
  mQuery.Open;
end;

procedure cDataProvider.RollBack;
begin
end;

procedure cDataProvider.StartTransaction;
begin
end;

procedure cDataProvider.StepInitDataTransfer( field_name:PChar ;
                                              field_data_size,field_data_type:integer ; data:Pointer );
var
  rec : TFieldFieldPair;
begin
  rec := TFieldFieldPair.Create;
  try
    mFieldPairMap.Add( rec );
  except
    rec.Free;
    raise;
  end;
  rec.mFieldName := field_name;
  rec.mNativeField := mQuery.FieldByName( rec.mFieldName );
  rec.mFieldDataSize := field_data_size;
  rec.mFieldDataType := field_data_type;
  rec.mData := data;

  if (field_data_type = cFieldDataType_ftDateTime) and (rec.mNativeField.DataSize <> field_data_size) then
    raise Exception.Create( 'double size mismatch!!!!' );

  if rec.mNativeField.DataSize > field_data_size then
    raise Exception.Create( 'DataSize mismatch!!!!' );
end;

// ---- exports start -------------------------------------------------------
function _CreateDataConnection( connection_string:PChar ) : Pointer; cdecl;
var
  conn : IDatabase;
  conn_str : string;
begin
  if StrIComp( connection_string, 'SENDATA' ) = 0 then
    conn_str := gMainAlias
  else if StrIComp( connection_string, 'COMPANY' ) = 0 then
    conn_str := gCompanyAlias;
  conn := cDataConnection.Create( conn_str );
  Result := pointer(conn);
end;

procedure _DeleteDataConnection( connection:Pointer ); cdecl;
var
  data_connection : cDataConnection;
begin
  IDatabase(connection).QueryInterface( IDatabase, data_connection );
  data_connection.Free;
end;

procedure SetSasSession( session:ISasSession ; main_alias,company_alias:PChar ); cdecl;
begin
  gSasSession := session;
  gMainAlias := main_alias;
  gCompanyAlias := company_alias;
end;

procedure ClearSasSession; cdecl;
begin
  gCompanyAlias := '';
  gMainAlias := '';
  gSasSession := nil;
end;

exports
  _CreateDataConnection,
  _DeleteDataConnection,
  SetSasSession,
  ClearSasSession;
// ---- exports end ---------------------------------------------------------

begin
  SetDefault;
  DllProc := Proc;
end.
