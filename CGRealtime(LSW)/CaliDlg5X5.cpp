// CaliDlg5X5.cpp : implementation file
//

#include "stdafx.h"
#include "CaliDlg5X5.h"
#include "CGRealtime.h"
#include "MainFrm.h"
#include "CGRealtimeDoc.h"
#include "CGRealtimeView.h"
#include "Public.h"
#include "TSTPOG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaliDlg5X5 dialog


CCaliDlg5X5::CCaliDlg5X5(CWnd* pParent /*=NULL*/)
	: CDialog(CCaliDlg5X5::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCaliDlg5X5)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCaliDlg5X5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCaliDlg5X5)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCaliDlg5X5, CDialog)
	//{{AFX_MSG_MAP(CCaliDlg5X5)
	ON_BN_CLICKED(IDC_BT_5X5_1, OnBt5x51)
	ON_BN_CLICKED(IDC_BT_5X5_2, OnBt5x52)
	ON_BN_CLICKED(IDC_BT_5X5_3, OnBt5x53)
	ON_BN_CLICKED(IDC_BT_5X5_4, OnBt5x54)
	ON_BN_CLICKED(IDC_BT_5X5_5, OnBt5x55)
	ON_BN_CLICKED(IDC_BT_5X5_6, OnBt5x56)
	ON_BN_CLICKED(IDC_BT_5X5_7, OnBt5x57)
	ON_BN_CLICKED(IDC_BT_5X5_8, OnBt5x58)
	ON_BN_CLICKED(IDC_BT_5X5_9, OnBt5x59)
	ON_BN_CLICKED(IDC_BT_5X5_10, OnBt5x510)
	ON_BN_CLICKED(IDC_BT_5X5_11, OnBt5x511)
	ON_BN_CLICKED(IDC_BT_5X5_12, OnBt5x512)
	ON_BN_CLICKED(IDC_BT_5X5_13, OnBt5x513)
	ON_BN_CLICKED(IDC_BT_5X5_14, OnBt5x514)
	ON_BN_CLICKED(IDC_BT_5X5_15, OnBt5x515)
	ON_BN_CLICKED(IDC_BT_5X5_16, OnBt5x516)
	ON_BN_CLICKED(IDC_BT_5X5_17, OnBt5x517)
	ON_BN_CLICKED(IDC_BT_5X5_18, OnBt5x518)
	ON_BN_CLICKED(IDC_BT_5X5_19, OnBt5x519)
	ON_BN_CLICKED(IDC_BT_5X5_20, OnBt5x520)
	ON_BN_CLICKED(IDC_BT_5X5_21, OnBt5x521)
	ON_BN_CLICKED(IDC_BT_5X5_22, OnBt5x522)
	ON_BN_CLICKED(IDC_BT_5X5_23, OnBt5x523)
	ON_BN_CLICKED(IDC_BT_5X5_24, OnBt5x524)
	ON_BN_CLICKED(IDC_BT_5X5_25, OnBt5x525)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaliDlg5X5 message handlers

void CCaliDlg5X5::OnBt5x51() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[0];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[0];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[0];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[0];
	CPublic::curFile=CPublic::fileName5X5[0];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x52() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[1];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[1];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[1];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[1];
	CPublic::curFile=CPublic::fileName5X5[1];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x53() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[2];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[2];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[2];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[2];
	CPublic::curFile=CPublic::fileName5X5[2];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x54() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[3];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[3];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[3];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[3];
	CPublic::curFile=CPublic::fileName5X5[3];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x55() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[4];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[4];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[4];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[4];
	CPublic::curFile=CPublic::fileName5X5[4];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x56() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[5];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[5];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[6];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[5];
	CPublic::curFile=CPublic::fileName5X5[5];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x57() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[6];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[6];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[6];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[6];
	CPublic::curFile=CPublic::fileName5X5[6];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x58() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[7];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[7];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[7];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[7];
	CPublic::curFile=CPublic::fileName5X5[7];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x59() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[8];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[8];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[8];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[8];
	CPublic::curFile=CPublic::fileName5X5[8];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x510() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[9];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[9];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[9];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[9];
	CPublic::curFile=CPublic::fileName5X5[9];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x511() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[10];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[10];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[10];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[10];
	CPublic::curFile=CPublic::fileName5X5[10];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x512() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[11];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[11];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[11];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[11];
	CPublic::curFile=CPublic::fileName5X5[11];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x513() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[12];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[12];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[12];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[12];
	CPublic::curFile=CPublic::fileName5X5[12];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x514() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[13];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[13];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[13];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[13];
	CPublic::curFile=CPublic::fileName5X5[13];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x515() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[14];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[14];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[14];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[14];
	CPublic::curFile=CPublic::fileName5X5[14];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x516() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[15];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[15];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[15];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[15];
	CPublic::curFile=CPublic::fileName5X5[15];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x517() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[16];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[16];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[16];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[16];
	CPublic::curFile=CPublic::fileName5X5[16];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x518() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[17];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[17];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[17];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[17];
	CPublic::curFile=CPublic::fileName5X5[17];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x519() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[18];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[18];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[18];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[18];
	CPublic::curFile=CPublic::fileName5X5[18];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x520() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[19];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[19];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[19];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[19];
	CPublic::curFile=CPublic::fileName5X5[19];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x521() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[20];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[20];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[20];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[20];
	CPublic::curFile=CPublic::fileName5X5[20];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x522() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[21];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[21];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[21];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[21];
	CPublic::curFile=CPublic::fileName5X5[21];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x523() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[22];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[22];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[22];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[22];
	CPublic::curFile=CPublic::fileName5X5[22];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x524() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[23];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[23];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[23];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[23];
	CPublic::curFile=CPublic::fileName5X5[23];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg5X5::OnBt5x525() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint5X5[24];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha5X5[24];
	CPublic::g_pBestVector=&CPublic::g_BestVector5x5[24];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp5X5[24];
	CPublic::curFile=CPublic::fileName5X5[24];
	CPublic::fpCur=fopen(CPublic::curFile,"w");
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}


void CCaliDlg5X5::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialog::PostNcDestroy();
}
