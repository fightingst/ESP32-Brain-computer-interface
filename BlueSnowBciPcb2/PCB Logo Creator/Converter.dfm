object ConverterForm: TConverterForm
  Left = 18
  Top = 9
  BorderStyle = bsDialog
  Caption = 'PCB Logo Creator'
  ClientHeight = 295
  ClientWidth = 650
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = ConverterFormCreate
  DesignSize = (
    650
    295)
  PixelsPerInch = 96
  TextHeight = 16
  object Image1: TImage
    Left = 10
    Top = 10
    Width = 250
    Height = 250
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Center = True
    Proportional = True
    Stretch = True
  end
  object XStatusBar1: TXStatusBar
    Left = 0
    Top = 270
    Width = 650
    Height = 25
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Enabled = False
    Panels = <>
    ParentShowHint = False
    ShowHint = False
    SimplePanel = True
    SimpleText = '   Ready...'
    SizeGrip = False
  end
  object XPProgressBar1: TXPProgressBar
    Left = 95
    Top = 271
    Width = 544
    Height = 19
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Position = 0
    Smooth = True
    Step = 0
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 2
  end
  object GroupBox1: TGroupBox
    Left = 269
    Top = 6
    Width = 261
    Height = 252
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Caption = ' Converter Options '
    TabOrder = 1
    object lImageSize: TLabel
      Left = 90
      Top = 90
      Width = 56
      Height = 16
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = ' 0 x 0 mils'
    end
    object ImageSizeLabel: TLabel
      Left = 16
      Top = 90
      Width = 74
      Height = 16
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = 'Image size : '
    end
    object lScalingFactor: TLabel
      Left = 16
      Top = 126
      Width = 95
      Height = 16
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = 'Scaling Factor : '
    end
    object Label2: TLabel
      Left = 16
      Top = 26
      Width = 83
      Height = 16
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = 'Board Layer : '
    end
    object Label1: TLabel
      Left = 180
      Top = 126
      Width = 71
      Height = 16
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = '(mils/pixels)'
    end
    object cbNegative: TCheckBox
      Left = 16
      Top = 159
      Width = 122
      Height = 26
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = 'Negative'
      TabOrder = 0
    end
    object cbMirrorX: TCheckBox
      Left = 16
      Top = 185
      Width = 73
      Height = 26
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = 'Mirror X'
      TabOrder = 1
    end
    object cbMirrorY: TCheckBox
      Left = 16
      Top = 211
      Width = 70
      Height = 27
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = 'Mirror Y'
      TabOrder = 2
    end
    object UpDown1: TUpDown
      Left = 153
      Top = 121
      Width = 18
      Height = 24
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Associate = eScalingFactor
      Position = 1
      TabOrder = 3
    end
    object eScalingFactor: TEdit
      Left = 114
      Top = 121
      Width = 39
      Height = 24
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      TabOrder = 4
      Text = '1'
      OnChange = eScalingFactorChange
    end
    object ComboBoxLayers: TComboBox
      Left = 16
      Top = 45
      Width = 235
      Height = 24
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Style = csDropDownList
      TabOrder = 5
    end
  end
  object exitbutton: TButton
    Left = 540
    Top = 83
    Width = 94
    Height = 31
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Anchors = [akTop, akRight]
    Cancel = True
    Caption = 'Exit'
    TabOrder = 3
  end
  object convertbutton: TButton
    Left = 540
    Top = 48
    Width = 94
    Height = 31
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Anchors = [akTop, akRight]
    Caption = 'Convert'
    Enabled = False
    TabOrder = 4
  end
  object loadbutton: TButton
    Left = 540
    Top = 13
    Width = 94
    Height = 31
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Anchors = [akTop, akRight]
    Caption = 'Load'
    TabOrder = 5
  end
  object OpenPictureDialog1: TOpenPictureDialog
    Left = 43
    Top = 105
  end
end
