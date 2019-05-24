object fUltraSki: TfUltraSki
  Left = 0
  Top = 0
  Caption = 'UltraSki'
  ClientHeight = 376
  ClientWidth = 481
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object lClear: TLabel
    Left = 48
    Top = 168
    Width = 49
    Height = 13
    AutoSize = False
    Caption = 'Clear'
    Color = clAqua
    ParentColor = False
    Transparent = False
  end
  object lClearResponse: TLabel
    Left = 103
    Top = 168
    Width = 25
    Height = 13
    Caption = 'Clear'
    Color = clAqua
    ParentColor = False
    Transparent = False
  end
  object lRaceInfo: TLabel
    Left = 48
    Top = 187
    Width = 49
    Height = 13
    AutoSize = False
    Caption = 'RaceInfo'
    Color = clAqua
    ParentColor = False
    Transparent = False
  end
  object lRaceInfoResponse: TLabel
    Left = 103
    Top = 187
    Width = 25
    Height = 13
    Caption = 'Clear'
    Color = clAqua
    ParentColor = False
    Transparent = False
  end
  object lMessage: TLabel
    Left = 48
    Top = 229
    Width = 49
    Height = 13
    AutoSize = False
    Caption = 'Message'
    Color = clAqua
    ParentColor = False
    Transparent = False
  end
  object lMessageResponse: TLabel
    Left = 103
    Top = 229
    Width = 25
    Height = 13
    Caption = 'Clear'
    Color = clAqua
    ParentColor = False
    Transparent = False
  end
  object lActiveRun: TLabel
    Left = 48
    Top = 317
    Width = 49
    Height = 13
    AutoSize = False
    Caption = 'ActiveRun'
    Color = clAqua
    ParentColor = False
    Transparent = False
  end
  object lActiveRunResponse: TLabel
    Left = 103
    Top = 317
    Width = 25
    Height = 13
    Caption = 'Clear'
    Color = clAqua
    ParentColor = False
    Transparent = False
  end
  object lMessage1: TLabel
    Left = 48
    Top = 248
    Width = 49
    Height = 13
    AutoSize = False
    Caption = 'Message'
    Color = clAqua
    ParentColor = False
    Transparent = False
    OnClick = lMessage1Click
  end
  object lMessage1Response: TLabel
    Left = 103
    Top = 248
    Width = 25
    Height = 13
    Caption = 'Clear'
    Color = clAqua
    ParentColor = False
    Transparent = False
  end
  object lHumidity: TLabel
    Left = 50
    Top = 301
    Width = 49
    Height = 13
    AutoSize = False
    Caption = 'Humidity'
    Color = clAqua
    ParentColor = False
    Transparent = False
  end
  object lHumidityResponse: TLabel
    Left = 105
    Top = 301
    Width = 25
    Height = 13
    Caption = 'Clear'
    Color = clAqua
    ParentColor = False
    Transparent = False
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 56
    Top = 56
  end
  object XMLDocument1: TXMLDocument
    Left = 208
    Top = 48
  end
  object LiveFIS: TIdTCPClient
    ConnectTimeout = 0
    Host = 'live.fisski.com'
    IPVersion = Id_IPv4
    Port = 1550
    ReadTimeout = -1
    Left = 112
    Top = 24
  end
  object ADOTable1: TADOTable
    ConnectionString = 
      'Provider=MSDASQL.1;Persist Security Info=False;User ID=mysql_nat' +
      'ive_password;Data Source=SQLite3 Datasource'
    Left = 264
    Top = 144
  end
  object DataSource1: TDataSource
    Left = 336
    Top = 152
  end
  object ADOConnection1: TADOConnection
    Left = 296
    Top = 216
  end
end
