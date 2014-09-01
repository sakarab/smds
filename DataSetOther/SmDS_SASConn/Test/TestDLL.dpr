program TestDLL;

{$APPTYPE CONSOLE}

uses
  SysUtils;

type
  IDataProvider = Interface;

//***********************************************************************
//******    IDatabase
//***********************************************************************
  IDatabase = Interface
  ['{309FC0E0-5159-430A-BBB8-EE82271E0B64}']
    function CreateDataProvider : IDataProvider; stdcall;
    procedure DestroyDataProvider( conn:IDataProvider ); stdcall;
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
    procedure StepInitDataTransfer( field_name:PChar ; field_data_size:integer ; field_data_type:integer ); stdcall;
    procedure EndInitDataTransfer(); stdcall;

    function FieldValue( field_name:PChar ; field_data_size:integer ; field_data_type:integer ; buff:Pointer ) : boolean; stdcall;
    procedure EndDataTransfer(); stdcall;

    procedure StartTransaction(); stdcall;
    procedure Commit(); stdcall;
    procedure RollBack(); stdcall;
    procedure ExecSql( sql:PChar ); stdcall;
  end;

function _CreateDataConnection( connection_string:PChar ) : Pointer; cdecl; external 'SmDS_SASConn_d7.dll';
procedure _DeleteDataConnection( connection:IDatabase ); cdecl; external 'SmDS_SASConn_d7.dll';

var
  Obj : TObject;

begin
  _CreateDataConnection( 'SomeText' );
  Obj := TObject.Create;
  try
    _DeleteDataConnection( Obj );
  finally
    Obj.Free;
  end;
end.
