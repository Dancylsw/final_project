// CaliDlg6X6.cpp : implementation file
//

#include "stdafx.h"
#include "CaliDlg6X6.h"
#include "CGRealtime.h"
#include "MainFrm.h"
#include "CGRealtimeDoc.h"
#include "CGRealtimeView.h"
#include "Public.h"
#include "Point.h"
#include "TSTPOG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaliDlg6X6 dialog


CCaliDlg6X6::CCaliDlg6X6(CWnd* pParent /*=NULL*/)
	: CDialog(CCaliDlg6X6::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCaliDlg6X6)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCaliDlg6X6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCaliDlg6X6)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCaliDlg6X6, CDialog)
	//{{AFX_MSG_MAP(CCaliDlg6X6)
	ON_BN_CLICKED(IDC_BT_6X6_1, OnBt6x61)
	ON_BN_CLICKED(IDC_BT_6X6_2, OnBt6x62)
	ON_BN_CLICKED(IDC_BT_6X6_3, OnBt6x63)
	ON_BN_CLICKED(IDC_BT_6X6_4, OnBt6x64)
	ON_BN_CLICKED(IDC_BT_6X6_5, OnBt6x65)
	ON_BN_CLICKED(IDC_BT_6X6_6, OnBt6x66)
	ON_BN_CLICKED(IDC_BT_6X6_7, OnBt6x67)
	ON_BN_CLICKED(IDC_BT_6X6_8, OnBt6x68)
	ON_BN_CLICKED(IDC_BT_6X6_9, OnBt6x69)
	ON_BN_CLICKED(IDC_BT_6X6_10, OnBt6x610)
	ON_BN_CLICKED(IDC_BT_6X6_11, OnBt6x611)
	ON_BN_CLICKED(IDC_BT_6X6_12, OnBt6x612)
	ON_BN_CLICKED(IDC_BT_6X6_13, OnBt6x613)
	ON_BN_CLICKED(IDC_BT_6X6_14, OnBt6x614)
	ON_BN_CLICKED(IDC_BT_6X6_15, OnBt6x615)
	ON_BN_CLICKED(IDC_BT_6X6_16, OnBt6x616)
	ON_BN_CLICKED(IDC_BT_6X6_17, OnBt6x617)
	ON_BN_CLICKED(IDC_BT_6X6_18, OnBt6x618)
	ON_BN_CLICKED(IDC_BT_6X6_19, OnBt6x619)
	ON_BN_CLICKED(IDC_BT_6X6_20, OnBt6x620)
	ON_BN_CLICKED(IDC_BT_6X6_21, OnBt6x621)
	ON_BN_CLICKED(IDC_BT_6X6_22, OnBt6x622)
	ON_BN_CLICKED(IDC_BT_6X6_23, OnBt6x623)
	ON_BN_CLICKED(IDC_BT_6X6_24, OnBt6x624)
	ON_BN_CLICKED(IDC_BT_6X6_25, OnBt6x625)
	ON_BN_CLICKED(IDC_BT_6X6_26, OnBt6x626)
	ON_BN_CLICKED(IDC_BT_6X6_27, OnBt6x627)
	ON_BN_CLICKED(IDC_BT_6X6_28, OnBt6x628)
	ON_BN_CLICKED(IDC_BT_6X6_29, OnBt6x629)
	ON_BN_CLICKED(IDC_BT_6X6_30, OnBt6x630)
	ON_BN_CLICKED(IDC_BT_6X6_31, OnBt6x631)
	ON_BN_CLICKED(IDC_BT_6X6_32, OnBt6x632)
	ON_BN_CLICKED(IDC_BT_6X6_33, OnBt6x633)
	ON_BN_CLICKED(IDC_BT_6X6_34, OnBt6x634)
	ON_BN_CLICKED(IDC_BT_6X6_35, OnBt6x635)
	ON_BN_CLICKED(IDC_BT_6X6_36, OnBt6x636)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaliDlg6X6 message handlers

void CCaliDlg6X6::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialog::PostNcDestroy();
}

void CCaliDlg6X6::OnBt6x61() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[0];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[0];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[0];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[0];
	CPublic::curFile=CPublic::fileName6X6[0];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x62() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[1];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[1];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[1];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[1];
	CPublic::curFile=CPublic::fileName6X6[1];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x63() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[2];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[2];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[2];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[2];
	CPublic::curFile=CPublic::fileName6X6[2];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x64() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[3];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[3];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[3];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[3];
	CPublic::curFile=CPublic::fileName6X6[3];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x65() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[4];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[4];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[4];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[4];
	CPublic::curFile=CPublic::fileName6X6[4];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x66() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[5];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[5];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[5];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[5];
	CPublic::curFile=CPublic::fileName6X6[5];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x67() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[6];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[6];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[6];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[6];
	CPublic::curFile=CPublic::fileName6X6[6];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x68() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[7];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[7];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[7];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[7];
	CPublic::curFile=CPublic::fileName6X6[7];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x69() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[8];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[8];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[8];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[8];
	CPublic::curFile=CPublic::fileName6X6[8];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x610() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[9];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[9];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[9];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[9];
	CPublic::curFile=CPublic::fileName6X6[9];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x611() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[10];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[10];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[10];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[10];
	CPublic::curFile=CPublic::fileName6X6[10];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x612() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[11];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[11];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[11];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[11];
	CPublic::curFile=CPublic::fileName6X6[11];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x613() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[12];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[12];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[12];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[12];
	CPublic::curFile=CPublic::fileName6X6[12];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x614() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[13];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[13];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[13];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[13];
	CPublic::curFile=CPublic::fileName6X6[13];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x615() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[14];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[14];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[14];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[14];
	CPublic::curFile=CPublic::fileName6X6[14];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x616() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[15];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[15];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[15];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[15];
	CPublic::curFile=CPublic::fileName6X6[15];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x617() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[16];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[16];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[16];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[16];
	CPublic::curFile=CPublic::fileName6X6[16];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x618() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[17];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[17];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[17];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[17];
	CPublic::curFile=CPublic::fileName6X6[17];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x619() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[18];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[18];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[18];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[18];
	CPublic::curFile=CPublic::fileName6X6[18];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x620() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[19];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[19];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[19];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[19];
	CPublic::curFile=CPublic::fileName6X6[19];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x621() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[20];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[20];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[20];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[20];
	CPublic::curFile=CPublic::fileName6X6[20];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x622() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[21];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[21];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[21];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[21];
	CPublic::curFile=CPublic::fileName6X6[21];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x623() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[22];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[22];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[22];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[22];
	CPublic::curFile=CPublic::fileName6X6[22];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x624() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[23];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[23];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[23];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[23];
	CPublic::curFile=CPublic::fileName6X6[23];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x625() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[24];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[24];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[24];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[24];
	CPublic::curFile=CPublic::fileName6X6[24];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x626() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[25];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[25];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[25];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[25];
	CPublic::curFile=CPublic::fileName6X6[25];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x627() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[26];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[26];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[26];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[26];
	CPublic::curFile=CPublic::fileName6X6[26];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x628() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[27];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[27];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[27];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[27];
	CPublic::curFile=CPublic::fileName6X6[27];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x629() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[28];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[28];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[28];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[28];
	CPublic::curFile=CPublic::fileName6X6[28];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x630() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[29];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[29];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[29];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[29];
	CPublic::curFile=CPublic::fileName6X6[29];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x631() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[30];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[30];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[30];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[30];
	CPublic::curFile=CPublic::fileName6X6[30];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x632() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[31];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[31];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[31];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[31];
	CPublic::curFile=CPublic::fileName6X6[31];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x633() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[32];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[32];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[32];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[32];
	CPublic::curFile=CPublic::fileName6X6[32];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
}

void CCaliDlg6X6::OnBt6x634() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[33];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[33];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[33];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[33];
	CPublic::curFile=CPublic::fileName6X6[33];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x635() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[34];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[34];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[34];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[34];
	CPublic::curFile=CPublic::fileName6X6[34];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg6X6::OnBt6x636() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint6X6[35];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha6X6[35];
	CPublic::g_pBestVector=&CPublic::g_BestVector6x6[35];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp6X6[35];
	CPublic::curFile=CPublic::fileName6X6[35];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}
