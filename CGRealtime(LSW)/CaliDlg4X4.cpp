// CaliDlg4X4.cpp : implementation file
//

#include "stdafx.h"
#include "CaliDlg4X4.h"
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
// CCaliDlg4X4 dialog


CCaliDlg4X4::CCaliDlg4X4(CWnd* pParent /*=NULL*/)
	: CDialog(CCaliDlg4X4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCaliDlg4X4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCaliDlg4X4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCaliDlg4X4)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCaliDlg4X4, CDialog)
	//{{AFX_MSG_MAP(CCaliDlg4X4)
	ON_BN_CLICKED(IDC_BT_4X4_1, OnBt4x41)
	ON_BN_CLICKED(IDC_BT_4X4_2, OnBt4x42)
	ON_BN_CLICKED(IDC_BT_4X4_3, OnBt4x43)
	ON_BN_CLICKED(IDC_BT_4X4_4, OnBt4x44)
	ON_BN_CLICKED(IDC_BT_4X4_5, OnBt4x45)
	ON_BN_CLICKED(IDC_BT_4X4_6, OnBt4x46)
	ON_BN_CLICKED(IDC_BT_4X4_7, OnBt4x47)
	ON_BN_CLICKED(IDC_BT_4X4_8, OnBt4x48)
	ON_BN_CLICKED(IDC_BT_4X4_9, OnBt4x49)
	ON_BN_CLICKED(IDC_BT_4X4_10, OnBt4x410)
	ON_BN_CLICKED(IDC_BT_4X4_11, OnBt4x411)
	ON_BN_CLICKED(IDC_BT_4X4_12, OnBt4x412)
	ON_BN_CLICKED(IDC_BT_4X4_13, OnBt4x413)
	ON_BN_CLICKED(IDC_BT_4X4_14, OnBt4x414)
	ON_BN_CLICKED(IDC_BT_4X4_15, OnBt4x415)
	ON_BN_CLICKED(IDC_BT_4X4_16, OnBt4x416)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaliDlg4X4 message handlers

void CCaliDlg4X4::OnBt4x41() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[0];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[0];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[0];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[0];
	CPublic::curFile=CPublic::fileName4X4[0];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x42() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[1];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[1];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[1];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[1];
	CPublic::curFile=CPublic::fileName4X4[1];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x43() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[2];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[2];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[2];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[2];
	CPublic::curFile=CPublic::fileName4X4[2];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x44() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[3];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[3];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[3];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[3];
	CPublic::curFile=CPublic::fileName4X4[3];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x45() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[4];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[4];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[4];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[4];
	CPublic::curFile=CPublic::fileName4X4[4];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x46() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[5];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[5];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[5];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[5];
	CPublic::curFile=CPublic::fileName4X4[5];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x47() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[6];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[6];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[6];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[6];
	CPublic::curFile=CPublic::fileName4X4[6];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x48() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[7];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[7];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[7];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[7];
	CPublic::curFile=CPublic::fileName4X4[7];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x49() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[8];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[8];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[8];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[8];
	CPublic::curFile=CPublic::fileName4X4[8];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x410() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[9];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[9];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[9];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[9];
	CPublic::curFile=CPublic::fileName4X4[9];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x411() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[10];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[10];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[10];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[10];
	CPublic::curFile=CPublic::fileName4X4[10];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x412() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[11];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[11];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[11];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[11];
	CPublic::curFile=CPublic::fileName4X4[11];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x413() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[12];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[12];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[12];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[12];
	CPublic::curFile=CPublic::fileName4X4[12];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x414() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[13];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[13];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[13];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[13];
	CPublic::curFile=CPublic::fileName4X4[13];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x415() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[14];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[14];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[14];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[14];
	CPublic::curFile=CPublic::fileName4X4[14];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::OnBt4x416() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint4X4[15];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha4X4[15];
	CPublic::g_pBestVector=&CPublic::g_BestVector4x4[15];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp4X4[15];
	CPublic::curFile=CPublic::fileName4X4[15];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg4X4::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialog::PostNcDestroy();
}
