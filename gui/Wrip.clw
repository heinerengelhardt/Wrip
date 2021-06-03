; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CConversionDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "wrip.h"
LastPage=0

ClassCount=13
Class1=CCommonDlg
Class2=CConversionDlg
Class3=CInformationDlg
Class4=CMp3Dlg
Class5=CPreferencesDlg
Class6=CSplashDlg
Class7=CTrackDlg
Class8=CWavDlg
Class9=CWripApp
Class10=CAboutDlg
Class11=CWripDlg

ResourceCount=13
Resource1=IDD_TRACKS
Resource2=IDD_CONVERSION
Resource3=IDD_MP3
Resource4=IDD_COMMON
Resource5=IDD_OGG
Resource6=IDD_PREFERENCES
Resource7=IDD_ABOUTBOX
Resource8=IDD_INFORMATION
Resource9=IDD_WRIP_DIALOG
Resource10=IDD_WAV
Resource11=IDD_ENCODER
Resource12=IDD_SPLASH
Class12=CEncoderDlg
Class13=COggDlg
Resource13=IDR_MENU

[CLS:CCommonDlg]
Type=0
BaseClass=CDialog
HeaderFile=CommonDlg.h
ImplementationFile=CommonDlg.cpp
Filter=D
VirtualFilter=dWC

[CLS:CConversionDlg]
Type=0
BaseClass=CDialog
HeaderFile=ConversionDlg.h
ImplementationFile=ConversionDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CConversionDlg

[CLS:CInformationDlg]
Type=0
BaseClass=CDialog
HeaderFile=InformationDlg.h
ImplementationFile=InformationDlg.cpp

[CLS:CMp3Dlg]
Type=0
BaseClass=CDialog
HeaderFile=Mp3Dlg.h
ImplementationFile=Mp3Dlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CMp3Dlg

[CLS:CPreferencesDlg]
Type=0
BaseClass=CDialog
HeaderFile=PreferencesDlg.h
ImplementationFile=PreferencesDlg.cpp

[CLS:CSplashDlg]
Type=0
BaseClass=CDialog
HeaderFile=SplashDlg.h
ImplementationFile=SplashDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_PROGRESS

[CLS:CTrackDlg]
Type=0
BaseClass=CDialog
HeaderFile=TrackDlg.h
ImplementationFile=TrackDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CTrackDlg

[CLS:CWavDlg]
Type=0
BaseClass=CDialog
HeaderFile=WavDlg.h
ImplementationFile=WavDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHECK_DELETEAFTERENCODE

[CLS:CWripApp]
Type=0
BaseClass=CWinApp
HeaderFile=Wrip.h
ImplementationFile=Wrip.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=WripDlg.cpp
ImplementationFile=WripDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CAboutDlg

[CLS:CWripDlg]
Type=0
BaseClass=CDialog
HeaderFile=WripDlg.h
ImplementationFile=WripDlg.cpp
Filter=W
VirtualFilter=dWC
LastObject=CWripDlg

[DLG:IDD_COMMON]
Type=1
Class=CCommonDlg
ControlCount=19
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,button,1342177287
Control3=IDC_EDIT_DESTINATION,edit,1350631552
Control4=IDC_BUTTON_BROWSE,button,1342246656
Control5=IDC_STATIC,static,1342308864
Control6=IDC_STATIC,static,1342308864
Control7=IDC_STATIC,static,1342308864
Control8=IDC_COMBO_FOLDER,combobox,1344339970
Control9=IDC_COMBO_FILE,combobox,1344339970
Control10=IDC_STATIC,static,1342177296
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308864
Control13=IDC_COMBO_CDDB,combobox,1344339971
Control14=IDC_CHECK_PROXY,button,1342242819
Control15=IDC_STATIC,static,1342308864
Control16=IDC_STATIC,static,1342308864
Control17=IDC_EDIT_PROXY,edit,1350631552
Control18=IDC_EDIT_PORT,edit,1350631554
Control19=IDC_STATIC,static,1342177296

[DLG:IDD_CONVERSION]
Type=1
Class=CConversionDlg
ControlCount=31
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,button,1342177287
Control3=IDC_BUTTON_CANCEL,button,1342242816
Control4=IDC_PROGRESS_WAV,msctls_progress32,1350565888
Control5=IDC_PROGRESS_MP3,msctls_progress32,1350565888
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC_WAV_PERCENT,static,1342308354
Control9=IDC_STATIC_MP3_PERCENT,static,1342308866
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC_WAV_TRACK,static,1342308364
Control13=IDC_STATIC_MP3_TRACK,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC_WAV_CURRENTSECTOR,static,1342308354
Control18=IDC_STATIC_WAV_ENDSECTOR,static,1342308354
Control19=IDC_STATIC_WAV_STARTSECTOR,static,1342308354
Control20=IDC_STATIC_WAV_COUNT,static,1342308354
Control21=IDC_STATIC_MP3_COUNT,static,1342308354
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC_WAV_SIZE,static,1342308354
Control25=IDC_STATIC_MP3_SIZE,static,1342308354
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308354
Control30=IDC_STATIC_WAV_CURRENTSIZE,static,1342308354
Control31=IDC_CHECK_SHUTDOWN,button,1342251011

[DLG:IDD_INFORMATION]
Type=1
Class=CInformationDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342177294
Control7=IDC_STATIC,static,1342177298
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_MP3]
Type=1
Class=CMp3Dlg
ControlCount=23
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308864
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308864
Control5=IDC_STATIC,static,1342308864
Control6=IDC_CHECK_CRC,button,1342242819
Control7=IDC_COMBO_BITRATE,combobox,1344339971
Control8=IDC_COMBO_FREQUENCY,combobox,1344339971
Control9=IDC_COMBO_QUALITY,combobox,1344339971
Control10=IDC_COMBO_MODE,combobox,1344339971
Control11=IDC_STATIC,static,1342308864
Control12=IDC_STATIC,static,1342308864
Control13=IDC_STATIC,static,1342308864
Control14=IDC_COMBO_VERSION,combobox,1344339971
Control15=IDC_CHECK_VBR,button,1342242819
Control16=IDC_STATIC,static,1342308864
Control17=IDC_STATIC,static,1342308864
Control18=IDC_COMBO_VBRQUALITY,combobox,1344339971
Control19=IDC_COMBO_ID3,combobox,1344339971
Control20=IDC_STATIC,static,1342308864
Control21=IDC_COMBO_MAXBITRATE,combobox,1344339971
Control22=IDC_STATIC,static,1342308864
Control23=IDC_COMBO_PLAYLIST,combobox,1344339971

[DLG:IDD_PREFERENCES]
Type=1
Class=CPreferencesDlg
ControlCount=1
Control1=IDC_TAB,SysTabControl32,1342194752

[DLG:IDD_SPLASH]
Type=1
Class=CSplashDlg
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PROGRESS,msctls_progress32,1342177281
Control3=IDC_STATIC,static,1342177294

[DLG:IDD_TRACKS]
Type=1
Class=CTrackDlg
ControlCount=8
Control1=IDC_LIST,SysListView32,1350631949
Control2=IDC_STATIC,static,1342308864
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308864
Control5=IDC_EDIT_ARTIST,edit,1350631552
Control6=IDC_EDIT_ALBUM,edit,1350631552
Control7=IDC_COMBO_GENRE,combobox,1344342083
Control8=IDC_BUTTON_SELECTALL,button,1342246720

[DLG:IDD_WAV]
Type=1
Class=CWavDlg
ControlCount=11
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308864
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308864
Control5=IDC_CHECK_JITTER,button,1342242819
Control6=IDC_BUTTON_RESET,button,1342242816
Control7=IDC_EDIT_READSECTORS,edit,1350639746
Control8=IDC_EDIT_BLOCKCOMPARE,edit,1350639746
Control9=IDC_EDIT_READOVERLAP,edit,1350639746
Control10=IDC_CHECK_DELETEAFTERENCODE,button,1342242819
Control11=IDC_STATIC,static,1342177296

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDOK,button,1342373889
Control2=IDC_STATIC,static,1342177294
Control3=IDC_EDIT_ABOUT,edit,1352730756

[DLG:IDD_WRIP_DIALOG]
Type=1
Class=CWripDlg
ControlCount=13
Control1=IDC_BUTTON_TOMP3,button,1342246720
Control2=IDC_BUTTON_EXIT,button,1342246721
Control3=IDC_BUTTON_TOWAV,button,1342246720
Control4=IDC_BUTTON_CDDB,button,1342246720
Control5=IDC_BUTTON_EJECT,button,1342246720
Control6=IDC_BUTTON_STOP,button,1342246720
Control7=IDC_BUTTON_PLAY,button,1342246720
Control8=IDC_BUTTON_PREV,button,1342246720
Control9=IDC_BUTTON_NEXT,button,1342246720
Control10=IDC_TAB,SysTabControl32,1350648896
Control11=IDC_COMBO_DRIVES,combobox,1344340995
Control12=IDC_BUTTON_INFO,button,1342246720
Control13=IDC_BUTTON_REFRESH,button,1342246720

[MNU:IDR_MENU]
Type=1
Class=?
Command1=ID_MENU_PLAY
Command2=ID_MENU_STOP
Command3=ID_MENU_TOWAV
Command4=ID_MENU_TOMP3
CommandCount=4

[DLG:IDD_OGG]
Type=1
Class=COggDlg
ControlCount=20
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308864
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308864
Control5=IDC_COMBO_MINBITRATE,combobox,1344339971
Control6=IDC_COMBO_NOMBITRATE,combobox,1344339971
Control7=IDC_COMBO_MAXBITRATE,combobox,1344339971
Control8=IDC_STATIC,static,1342308864
Control9=IDC_STATIC,static,1342308864
Control10=IDC_STATIC,static,1342308864
Control11=IDC_COMBO_FREQUENCY,combobox,1344339971
Control12=IDC_STATIC,static,1342308864
Control13=IDC_STATIC,static,1342308864
Control14=IDC_COMBO_CHANNELS,combobox,1344339971
Control15=IDC_STATIC,static,1342308864
Control16=IDC_CHECK_VBR,button,1342242819
Control17=IDC_STATIC,static,1342308864
Control18=IDC_COMBO_VBRQUALITY,combobox,1344339971
Control19=IDC_STATIC,static,1342308864
Control20=IDC_COMBO_PLAYLIST,combobox,1344339971

[DLG:IDD_ENCODER]
Type=1
Class=CEncoderDlg
ControlCount=4
Control1=65535,static,1342308864
Control2=IDC_COMBO_THREADPRIORITY,combobox,1344339971
Control3=65535,static,1342308864
Control4=IDC_COMBO_ENCODER,combobox,1344339971

[CLS:CEncoderDlg]
Type=0
HeaderFile=EncoderDlg.h
ImplementationFile=EncoderDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=65535

[CLS:COggDlg]
Type=0
HeaderFile=OggDlg.h
ImplementationFile=OggDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=COggDlg
VirtualFilter=dWC

