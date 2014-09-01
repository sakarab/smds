object frmMain: TfrmMain
  Left = 356
  Top = 368
  Width = 547
  Height = 313
  Caption = 'frmMain'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button2: TButton
    Left = 22
    Top = 20
    Width = 90
    Height = 25
    Caption = 'ClientDataSet'
    TabOrder = 0
    OnClick = Button2Click
  end
  object Button1: TButton
    Left = 32
    Top = 92
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 1
    OnClick = Button1Click
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
  object ADOConnection: TADOConnection
    Connected = True
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=G:\Data\Dirdata82.m' +
      'db;Persist Security Info=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 222
    Top = 100
  end
  object ADOQuery: TADOQuery
    Connection = ADOConnection
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from tblFiles')
    Left = 260
    Top = 100
  end
end
