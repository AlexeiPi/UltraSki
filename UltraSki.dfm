object fUltraSki: TfUltraSki
  Left = 0
  Top = 0
  Caption = 'UltraSki'
  ClientHeight = 318
  ClientWidth = 509
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 48
    Top = 168
    Width = 297
    Height = 73
    Caption = 'Label1'
    Color = clActiveCaption
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
end
