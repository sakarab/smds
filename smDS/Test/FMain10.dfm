object frmMain: TfrmMain
  Left = 88
  Top = 93
  Caption = 'frmMain'
  ClientHeight = 672
  ClientWidth = 833
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 352
    Top = 20
    Width = 90
    Height = 25
    Caption = 'cDataSet'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 22
    Top = 20
    Width = 90
    Height = 25
    Caption = 'ClientDataSet'
    TabOrder = 1
    OnClick = Button2Click
  end
  object DBNavigator1: TDBNavigator
    Left = 26
    Top = 112
    Width = 240
    Height = 25
    TabOrder = 2
  end
  object DBEdit1: TDBEdit
    Left = 48
    Top = 164
    Width = 121
    Height = 21
    DataField = 'fDate'
    TabOrder = 3
  end
  object DBEdit2: TDBEdit
    Left = 204
    Top = 164
    Width = 215
    Height = 21
    DataField = 'Title'
    TabOrder = 4
  end
  object lvList: TListView
    Left = 20
    Top = 192
    Width = 797
    Height = 465
    Columns = <>
    OwnerData = True
    RowSelect = True
    TabOrder = 5
    ViewStyle = vsReport
    OnData = lvListData
  end
  object ADOConnection: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=G:\Da' +
      'ta\Dirdata82.mdb;Mode=Share Deny None;Extended Properties="";Per' +
      'sist Security Info=False;Jet OLEDB:System database="";Jet OLEDB:' +
      'Registry Path="";Jet OLEDB:Database Password="";Jet OLEDB:Engine' +
      ' Type=5;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Parti' +
      'al Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New' +
      ' Database Password="";Jet OLEDB:Create System Database=False;Jet' +
      ' OLEDB:Encrypt Database=False;Jet OLEDB:Don'#39't Copy Locale on Com' +
      'pact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OL' +
      'EDB:SFP=False'
    LoginPrompt = False
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 218
    Top = 16
  end
  object ADOQuery: TADOQuery
    Connection = ADOConnection
    Parameters = <>
    SQL.Strings = (
      'select * from tblFiles')
    Left = 258
    Top = 16
  end
  object ClientDataSet: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider'
    Left = 126
    Top = 16
  end
  object DataSetProvider: TDataSetProvider
    DataSet = Query
    Left = 166
    Top = 16
  end
  object Database: TDatabase
    AliasName = 'Dir82'
    DatabaseName = 'adb'
    LoginPrompt = False
    Params.Strings = (
      'DATABASE NAME=G:\Data\Dirdata82.mdb'
      'USER NAME=Admin'
      'OPEN MODE=READ/WRITE'
      'LANGDRIVER='
      'SYSTEM DATABASE='
      'PASSWORD=')
    SessionName = 'Default'
    Left = 218
    Top = 58
  end
  object Query: TQuery
    DatabaseName = 'adb'
    SQL.Strings = (
      'select * from tblFiles')
    Left = 256
    Top = 58
  end
end
