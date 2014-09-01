object frmMain: TfrmMain
  Left = 263
  Top = 170
  Width = 809
  Height = 619
  Caption = 'frmMain'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  DesignSize = (
    801
    573)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 146
    Top = 14
    Width = 56
    Height = 13
    Caption = 'Table name'
  end
  object Label2: TLabel
    Left = 10
    Top = 14
    Width = 26
    Height = 13
    Caption = 'Prefix'
  end
  object btnRunSql: TButton
    Left = 340
    Top = 32
    Width = 75
    Height = 25
    Caption = 'Run Sql'
    TabOrder = 2
    OnClick = btnRunSqlClick
  end
  object edtTableName: TEdit
    Left = 146
    Top = 34
    Width = 173
    Height = 21
    TabOrder = 1
  end
  object edtPrefix: TEdit
    Left = 10
    Top = 34
    Width = 121
    Height = 21
    TabOrder = 0
    Text = 'tbl'
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 75
    Width = 801
    Height = 498
    ActivePage = tsSql
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabIndex = 0
    TabOrder = 3
    object tsSql: TTabSheet
      Caption = 'Sql Text'
      object mmSql: TMemo
        Left = 0
        Top = 0
        Width = 793
        Height = 470
        Align = alClient
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
    object tsCustomFIelds: TTabSheet
      Caption = 'Custom FIelds'
      ImageIndex = 1
      object DBGrid1: TDBGrid
        Left = 0
        Top = 0
        Width = 793
        Height = 470
        Align = alClient
        DataSource = srcCustom
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'MS Sans Serif'
        TitleFont.Style = []
        Columns = <
          item
            Expanded = False
            FieldName = 'Order'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Name'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Type'
            PickList.Strings = (
              'fkData'
              'fkInternalCalc')
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'DataType'
            PickList.Strings = (
              'ftBool'
              'ftShort'
              'ftInteger'
              'ftDouble'
              'ftDateTime'
              'ftString'
              'ftWString'
              'ftBlob')
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Size'
            Visible = True
          end>
      end
    end
    object tsResult: TTabSheet
      Caption = 'Result Text'
      ImageIndex = 2
      object Memo: TMemo
        Left = 0
        Top = 0
        Width = 793
        Height = 470
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
  end
  object btnRunCustom: TButton
    Left = 428
    Top = 32
    Width = 75
    Height = 25
    Caption = 'Run Custom'
    TabOrder = 4
    OnClick = btnRunCustomClick
  end
  object Database: TDatabase
    AliasName = 'SENDATA'
    DatabaseName = 'adb'
    LoginPrompt = False
    Params.Strings = (
      'SERVER NAME=SEN9I.WORLD'
      'USER NAME=s01999'
      'NET PROTOCOL=TNS'
      'OPEN MODE=READ/WRITE'
      'SCHEMA CACHE SIZE=8'
      'LANGDRIVER='
      'SQLQRYMODE='
      'SQLPASSTHRU MODE=SHARED AUTOCOMMIT'
      'SCHEMA CACHE TIME=-1'
      'MAX ROWS=-1'
      'BATCH COUNT=200'
      'ENABLE SCHEMA CACHE=FALSE'
      'SCHEMA CACHE DIR='
      'ENABLE BCD=FALSE'
      'ENABLE INTEGERS=TRUE'
      'LIST SYNONYMS=NONE'
      'ROWSET SIZE=20'
      'BLOBS TO CACHE=64'
      'BLOB SIZE=32'
      'OBJECT MODE=TRUE'
      'PASSWORD=s01999')
    SessionName = 'Default'
    Left = 230
    Top = 60
  end
  object Query: TQuery
    DatabaseName = 'adb'
    Left = 264
    Top = 60
  end
  object MainMenu1: TMainMenu
    Left = 302
    Top = 60
    object File1: TMenuItem
      Caption = '&File'
      object msOpenSql: TMenuItem
        Caption = 'Open Sql'
        OnClick = msOpenSqlClick
      end
      object msOpenCustom: TMenuItem
        Caption = 'Open Custom'
        OnClick = msOpenCustomClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object msSaveSql: TMenuItem
        Caption = 'Save Sql'
        OnClick = msSaveSqlClick
      end
      object msSaveCustom: TMenuItem
        Caption = 'Save Custom'
        OnClick = msSaveCustomClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object msQuit: TMenuItem
        Caption = '&Quit'
        ShortCut = 16465
      end
    end
  end
  object OpenDlg: TOpenDialog
    Filter = 
      'Sql Files (*.sql)|*.sql|Custom Fields Files (*.xml)|*.xml|All Fi' +
      'les (*.*)|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 338
    Top = 60
  end
  object SaveDlg: TSaveDialog
    Filter = 
      'Sql Files (*.sql)|*.sql|Custom Fields Files (*.xml)|*.xml|All Fi' +
      'les (*.*)|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Left = 374
    Top = 60
  end
  object dsCustom: TClientDataSet
    Aggregates = <>
    FieldDefs = <>
    IndexDefs = <
      item
        Name = 'OrderIdx'
        Fields = 'Order'
        Options = [ixUnique]
      end>
    Params = <>
    StoreDefs = True
    Left = 408
    Top = 60
    object dsCustomOrder: TIntegerField
      FieldName = 'Order'
    end
    object dsCustomName: TStringField
      FieldName = 'Name'
      Size = 50
    end
    object dsCustomType: TIntegerField
      FieldName = 'Type'
      OnGetText = dsCustomTypeGetText
      OnSetText = dsCustomTypeSetText
    end
    object dsCustomDataType: TIntegerField
      FieldName = 'DataType'
      OnGetText = dsCustomDataTypeGetText
      OnSetText = dsCustomDataTypeSetText
    end
    object dsCustomSize: TIntegerField
      FieldName = 'Size'
    end
  end
  object srcCustom: TDataSource
    DataSet = dsCustom
    Left = 442
    Top = 60
  end
end
