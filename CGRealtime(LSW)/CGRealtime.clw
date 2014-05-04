; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCALPOG
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CGSnapEx.h"
LastPage=0

ClassCount=13
Class1=CCGSnapExApp
Class2=CCGSnapExDoc
Class3=CCGSnapExView
Class4=CMainFrame

ResourceCount=12
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CButtonTestDlg
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDD_CAL2X2
Class6=CCaliDlg2X2
Resource5=IDD_CAL4X4
Class7=CActDlg
Resource6=IDD_ACT
Class8=CTSTPOG
Resource7=IDD_BTTEST
Class9=CCaliDlg3X3
Resource8=IDD_CAL5X5
Class10=CCaliDlg4X4
Resource9=IDD_CAL3X3
Class11=CCaliDlg5X5
Resource10=IDD_TSTPOG
Class12=CCaliDlg6X6
Resource11=IDD_CAL6X6
Class13=CCALPOG
Resource12=IDR_MAINFRAME (English (U.S.))

[CLS:CCGSnapExApp]
Type=0
HeaderFile=CGSnapEx.h
ImplementationFile=CGSnapEx.cpp
Filter=N

[CLS:CCGSnapExDoc]
Type=0
HeaderFile=CGSnapExDoc.h
ImplementationFile=CGSnapExDoc.cpp
Filter=N

[CLS:CCGSnapExView]
Type=0
HeaderFile=CGSnapExView.h
ImplementationFile=CGSnapExView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=?

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=16
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_SNAPEX_OPEN
Command2=ID_SNAPEX_START
Command3=ID_SNAPEX_STOP
Command4=ID_SNAPEX_CLOSE
Command5=ID_NEGATIVE
Command6=IDM_ACCUTEST
Command7=IDM_GRIDTEST_2X2
Command8=IDM_GRIDTEST_3X3
Command9=IDM_GRIDTEST_4X4
Command10=IDM_GRIDTEST_5X5
Command11=IDM_GRIDTEST_6X6
Command12=IDM_BTEST
CommandCount=12

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_HKSTOP
Command2=ID_BTCALIB
Command3=ID_CALIB3X3
Command4=ID_BTCALIB4X4
Command5=ID_BTCALIB5X5
Command6=ID_BTCALIB6X6
Command7=ID_BTMAPPING
CommandCount=7

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CAL2X2]
Type=1
Class=CCaliDlg2X2
ControlCount=4
Control1=IDC_BT_2X2_1,button,1342242816
Control2=IDC_BT_2X2_2,button,1342242816
Control3=IDC_BT_2X2_3,button,1342242816
Control4=IDC_BT_2X2_4,button,1342242816

[CLS:CCaliDlg2X2]
Type=0
HeaderFile=CaliDlg2X2.h
ImplementationFile=CaliDlg2X2.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_2X2CAL
VirtualFilter=dWC

[DLG:IDD_ACT]
Type=1
Class=CActDlg
ControlCount=10
Control1=IDC_ACBT1,button,1342242816
Control2=IDC_ACBT4,button,1342242816
Control3=IDC_ACBT7,button,1342242816
Control4=IDC_ACBT2,button,1342242816
Control5=IDC_ACBT5,button,1342242816
Control6=IDC_ACBT8,button,1342242816
Control7=IDC_ACBT3,button,1342242816
Control8=IDC_ACBT6,button,1342242816
Control9=IDC_ACBT9,button,1342242816
Control10=IDC_ACTDONE,button,1342242816

[CLS:CActDlg]
Type=0
HeaderFile=ActDlg.h
ImplementationFile=ActDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CActDlg
VirtualFilter=dWC

[DLG:IDD_TSTPOG]
Type=1
Class=CTSTPOG
ControlCount=1
Control1=IDC_STATIC,static,1342181383

[CLS:CTSTPOG]
Type=0
HeaderFile=TSTPOG.h
ImplementationFile=TSTPOG.cpp
BaseClass=CDialog
Filter=D
LastObject=CTSTPOG
VirtualFilter=dWC

[DLG:IDD_CAL3X3]
Type=1
Class=CCaliDlg3X3
ControlCount=9
Control1=IDC_BT_3X3_1,button,1342242816
Control2=IDC_BT_3X3_4,button,1342242816
Control3=IDC_BT_3X3_7,button,1342242816
Control4=IDC_BT_3X3_2,button,1342242816
Control5=IDC_BT_3X3_5,button,1342242816
Control6=IDC_BT_3X3_8,button,1342242816
Control7=IDC_BT_3X3_3,button,1342242816
Control8=IDC_BT_3X3_6,button,1342242816
Control9=IDC_BT_3X3_9,button,1342242816

[CLS:CCaliDlg3X3]
Type=0
HeaderFile=CaliDlg3X3.h
ImplementationFile=CaliDlg3X3.cpp
BaseClass=CDialog
Filter=D
LastObject=CCaliDlg3X3
VirtualFilter=dWC

[DLG:IDD_CAL4X4]
Type=1
Class=CCaliDlg4X4
ControlCount=16
Control1=IDC_BT_4X4_1,button,1342242816
Control2=IDC_BT_4X4_2,button,1342242816
Control3=IDC_BT_4X4_3,button,1342242816
Control4=IDC_BT_4X4_4,button,1342242816
Control5=IDC_BT_4X4_5,button,1342242816
Control6=IDC_BT_4X4_6,button,1342242816
Control7=IDC_BT_4X4_7,button,1342242816
Control8=IDC_BT_4X4_8,button,1342242816
Control9=IDC_BT_4X4_9,button,1342242816
Control10=IDC_BT_4X4_10,button,1342242816
Control11=IDC_BT_4X4_11,button,1342242816
Control12=IDC_BT_4X4_12,button,1342242816
Control13=IDC_BT_4X4_13,button,1342242816
Control14=IDC_BT_4X4_14,button,1342242816
Control15=IDC_BT_4X4_15,button,1342242816
Control16=IDC_BT_4X4_16,button,1342242816

[CLS:CCaliDlg4X4]
Type=0
HeaderFile=CaliDlg4X4.h
ImplementationFile=CaliDlg4X4.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_4X4CAL

[DLG:IDD_CAL5X5]
Type=1
Class=CCaliDlg5X5
ControlCount=25
Control1=IDC_BT_5X5_1,button,1342242816
Control2=IDC_BT_5X5_2,button,1342242816
Control3=IDC_BT_5X5_3,button,1342242816
Control4=IDC_BT_5X5_4,button,1342242816
Control5=IDC_BT_5X5_5,button,1342242816
Control6=IDC_BT_5X5_6,button,1342242816
Control7=IDC_BT_5X5_7,button,1342242816
Control8=IDC_BT_5X5_8,button,1342242816
Control9=IDC_BT_5X5_9,button,1342242816
Control10=IDC_BT_5X5_10,button,1342242816
Control11=IDC_BT_5X5_11,button,1342242816
Control12=IDC_BT_5X5_12,button,1342242816
Control13=IDC_BT_5X5_13,button,1342242816
Control14=IDC_BT_5X5_14,button,1342242816
Control15=IDC_BT_5X5_15,button,1342242816
Control16=IDC_BT_5X5_16,button,1342242816
Control17=IDC_BT_5X5_17,button,1342242816
Control18=IDC_BT_5X5_18,button,1342242816
Control19=IDC_BT_5X5_19,button,1342242816
Control20=IDC_BT_5X5_20,button,1342242816
Control21=IDC_BT_5X5_21,button,1342242816
Control22=IDC_BT_5X5_22,button,1342242816
Control23=IDC_BT_5X5_23,button,1342242816
Control24=IDC_BT_5X5_24,button,1342242816
Control25=IDC_BT_5X5_25,button,1342242816

[CLS:CCaliDlg5X5]
Type=0
HeaderFile=CaliDlg5X5.h
ImplementationFile=CaliDlg5X5.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCaliDlg5X5

[DLG:IDD_CAL6X6]
Type=1
Class=CCaliDlg6X6
ControlCount=36
Control1=IDC_BT_6X6_1,button,1342242816
Control2=IDC_BT_6X6_2,button,1342242816
Control3=IDC_BT_6X6_3,button,1342242816
Control4=IDC_BT_6X6_4,button,1342242816
Control5=IDC_BT_6X6_5,button,1342242816
Control6=IDC_BT_6X6_6,button,1342242816
Control7=IDC_BT_6X6_7,button,1342242816
Control8=IDC_BT_6X6_8,button,1342242816
Control9=IDC_BT_6X6_9,button,1342242816
Control10=IDC_BT_6X6_10,button,1342242816
Control11=IDC_BT_6X6_11,button,1342242816
Control12=IDC_BT_6X6_12,button,1342242816
Control13=IDC_BT_6X6_13,button,1342242816
Control14=IDC_BT_6X6_14,button,1342242816
Control15=IDC_BT_6X6_15,button,1342242816
Control16=IDC_BT_6X6_16,button,1342242816
Control17=IDC_BT_6X6_17,button,1342242816
Control18=IDC_BT_6X6_18,button,1342242816
Control19=IDC_BT_6X6_19,button,1342242816
Control20=IDC_BT_6X6_20,button,1342242816
Control21=IDC_BT_6X6_21,button,1342242816
Control22=IDC_BT_6X6_22,button,1342242816
Control23=IDC_BT_6X6_23,button,1342242816
Control24=IDC_BT_6X6_24,button,1342242816
Control25=IDC_BT_6X6_25,button,1342242816
Control26=IDC_BT_6X6_26,button,1342242816
Control27=IDC_BT_6X6_27,button,1342242816
Control28=IDC_BT_6X6_28,button,1342242816
Control29=IDC_BT_6X6_29,button,1342242816
Control30=IDC_BT_6X6_30,button,1342242816
Control31=IDC_BT_6X6_31,button,1342242816
Control32=IDC_BT_6X6_32,button,1342242816
Control33=IDC_BT_6X6_33,button,1342242816
Control34=IDC_BT_6X6_34,button,1342242816
Control35=IDC_BT_6X6_35,button,1342242816
Control36=IDC_BT_6X6_36,button,1342242816

[CLS:CCaliDlg6X6]
Type=0
HeaderFile=CaliDlg6X6.h
ImplementationFile=CaliDlg6X6.cpp
BaseClass=CDialog
Filter=D
LastObject=CCaliDlg6X6
VirtualFilter=dWC

[DLG:IDD_BTTEST]
Type=1
Class=CButtonTestDlg
ControlCount=40
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_BTST_BACKSPACE,button,1342242816
Control3=IDC_BTST_ABC,button,1342242816
Control4=IDC_BTST_DEF,button,1342242816
Control5=IDC_BTST_GHI,button,1342242816
Control6=IDC_BTST_JKL,button,1342242816
Control7=IDC_BTST_MNO,button,1342242816
Control8=IDC_BTST_PQRS,button,1342242816
Control9=IDC_BTST_TUV,button,1342242816
Control10=IDC_BTST_WXYZ,button,1342242816
Control11=IDC_BTST_SPACE,button,1342242816
Control12=IDC_BTST_CLEAR,button,1342242816
Control13=IDC_BTTEST_A,button,1073807360
Control14=IDC_BTTEST_B,button,1073807360
Control15=IDC_BTTEST_C,button,1073807360
Control16=IDC_BTTEST_BACK,button,1073807360
Control17=IDC_BTTEST_D,button,1073807360
Control18=IDC_BTTEST_E,button,1073807360
Control19=IDC_BTTEST_F,button,1073807360
Control20=IDC_BTTEST_G,button,1073807360
Control21=IDC_BTTEST_H,button,1073807360
Control22=IDC_BTTEST_I,button,1073807360
Control23=IDC_BTTEST_J,button,1073807360
Control24=IDC_BTTEST_K,button,1073807360
Control25=IDC_BTTEST_L,button,1073807360
Control26=IDC_BTTEST_M,button,1073807360
Control27=IDC_BTTEST_N,button,1073807360
Control28=IDC_BTTEST_O,button,1073807360
Control29=IDC_BTST_P,button,1073807360
Control30=IDC_BTST_Q,button,1073807360
Control31=IDC_BTST_R,button,1073807360
Control32=IDC_BTST_S,button,1073807360
Control33=IDC_BTTEST_T,button,1073807360
Control34=IDC_BTTEST_U,button,1073807360
Control35=IDC_BTTEST_V,button,1073807360
Control36=IDC_BTST_W,button,1073807360
Control37=IDC_BTST_X,button,1073807360
Control38=IDC_BTST_Y,button,1073807360
Control39=IDC_BTST_Z,button,1073807360
Control40=IDC_BTST_INBACK,button,1073807360

[CLS:CButtonTestDlg]
Type=0
HeaderFile=ButtonTestDlg.h
ImplementationFile=ButtonTestDlg.cpp
BaseClass=CDialog
Filter=W
LastObject=IDM_GRIDTEST_2X2
VirtualFilter=dWC

[CLS:CCALPOG]
Type=0
HeaderFile=CALPOG.h
ImplementationFile=CALPOG.cpp
BaseClass=CDialog
Filter=D
LastObject=CCALPOG
VirtualFilter=dWC

