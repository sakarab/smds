object frmMain: TfrmMain
  Left = 323
  Top = 184
  Width = 883
  Height = 751
  Caption = 'frmMain'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  DesignSize = (
    875
    705)
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 0
    Width = 875
    Height = 23
    Align = alTop
    Shape = bsTopLine
  end
  object Label1: TLabel
    Left = 8
    Top = 6
    Width = 858
    Height = 13
    Anchors = [akLeft, akTop, akRight]
    AutoSize = False
    Caption = 'Statistics'
    Color = clAqua
    ParentColor = False
  end
  object Splitter2: TSplitter
    Left = 0
    Top = 235
    Width = 875
    Height = 3
    Cursor = crVSplit
    Align = alTop
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 686
    Width = 875
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 23
    Width = 875
    Height = 212
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object Splitter1: TSplitter
      Left = 257
      Top = 0
      Width = 3
      Height = 212
      Cursor = crHSplit
    end
    object lbStats: TListBox
      Left = 0
      Top = 0
      Width = 257
      Height = 212
      Align = alLeft
      ItemHeight = 13
      TabOrder = 0
      OnClick = lbStatsClick
      OnDblClick = lbStatsDblClick
    end
    object mmHelp: TMemo
      Left = 260
      Top = 0
      Width = 615
      Height = 212
      Align = alClient
      TabOrder = 1
    end
  end
  object sgGrid: TStringGrid
    Left = 0
    Top = 238
    Width = 875
    Height = 448
    Align = alClient
    ColCount = 100
    DefaultColWidth = 32
    DefaultRowHeight = 18
    DefaultDrawing = False
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine]
    TabOrder = 2
    OnDrawCell = sgGridDrawCell
  end
  object MainMenu1: TMainMenu
    Left = 200
    Top = 6
    object File1: TMenuItem
      Caption = '&File'
      object msLoadData: TMenuItem
        Action = actLoadData
      end
      object msClearReport: TMenuItem
        Caption = 'Clear Report'
        OnClick = msClearReportClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object msRunSelected: TMenuItem
        Action = actRunSelected
      end
      object msRunAll: TMenuItem
        Action = actRunAll
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object msQuit: TMenuItem
        Caption = '&Quit'
        ShortCut = 16465
        OnClick = msQuitClick
      end
    end
  end
  object ActionList: TActionList
    Left = 244
    Top = 4
    object actLoadData: TAction
      Caption = '&Load Data'
      ShortCut = 16460
      OnExecute = actLoadDataExecute
    end
    object actRunSelected: TAction
      Caption = 'Run Selected'
      ShortCut = 16466
      OnExecute = actRunSelectedExecute
    end
    object actRunAll: TAction
      Caption = 'Run All'
      ShortCut = 24658
      OnExecute = actRunAllExecute
    end
  end
end
