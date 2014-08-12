// CaliDlg3X3.cpp : implementation file
//

#include "stdafx.h"
#include "CGRealtime.h"
#include "CaliDlg3X3.h"

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
// CCaliDlg3X3 dialog


CCaliDlg3X3::CCaliDlg3X3(CWnd* pParent /*=NULL*/)
	: CDialog(CCaliDlg3X3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCaliDlg3X3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCaliDlg3X3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCaliDlg3X3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCaliDlg3X3, CDialog)
	//{{AFX_MSG_MAP(CCaliDlg3X3)
	ON_BN_CLICKED(IDC_BT_3X3_1, OnBt3x31)
	ON_BN_CLICKED(IDC_BT_3X3_2, OnBt3x32)
	ON_BN_CLICKED(IDC_BT_3X3_3, OnBt3x33)
	ON_BN_CLICKED(IDC_BT_3X3_4, OnBt3x34)
	ON_BN_CLICKED(IDC_BT_3X3_5, OnBt3x35)
	ON_BN_CLICKED(IDC_BT_3X3_6, OnBt3x36)
	ON_BN_CLICKED(IDC_BT_3X3_7, OnBt3x37)
	ON_BN_CLICKED(IDC_BT_3X3_8, OnBt3x38)
	ON_BN_CLICKED(IDC_BT_3X3_9, OnBt3x39)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaliDlg3X3 message handlers

void CCaliDlg3X3::OnBt3x31() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint3X3[0];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha3X3[0];
	CPublic::g_pBestVector=&CPublic::g_BestVector3x3[0];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp3X3[0];
	CPublic::curFile=CPublic::fileName3X3[0];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg3X3::OnBt3x32() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint3X3[1];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha3X3[1];
	CPublic::g_pBestVector=&CPublic::g_BestVector3x3[1];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp3X3[1];
	CPublic::curFile=CPublic::fileName3X3[1];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg3X3::OnBt3x33() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint3X3[2];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha3X3[2];
	CPublic::g_pBestVector=&CPublic::g_BestVector3x3[2];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp3X3[2];
	CPublic::curFile=CPublic::fileName3X3[2];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg3X3::OnBt3x34() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint3X3[3];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha3X3[3];
	CPublic::g_pBestVector=&CPublic::g_BestVector3x3[3];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp3X3[3];
	CPublic::curFile=CPublic::fileName3X3[3];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg3X3::OnBt3x35() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint3X3[4];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha3X3[4];
	CPublic::g_pBestVector=&CPublic::g_BestVector3x3[4];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp3X3[4];
	CPublic::curFile=CPublic::fileName3X3[4];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg3X3::OnBt3x36() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint3X3[5];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha3X3[5];
	CPublic::g_pBestVector=&CPublic::g_BestVector3x3[5];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp3X3[5];
	CPublic::curFile=CPublic::fileName3X3[5];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg3X3::OnBt3x37() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint3X3[6];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha3X3[6];
	CPublic::g_pBestVector=&CPublic::g_BestVector3x3[6];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp3X3[6];
	CPublic::curFile=CPublic::fileName3X3[6];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg3X3::OnBt3x38() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint3X3[7];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha3X3[7];
	CPublic::g_pBestVector=&CPublic::g_BestVector3x3[7];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp3X3[7];
	CPublic::curFile=CPublic::fileName3X3[7];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg3X3::OnBt3x39() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint3X3[8];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha3X3[8];
	CPublic::g_pBestVector=&CPublic::g_BestVector3x3[8];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fpCur=CPublic::fp3X3[8];
	CPublic::curFile=CPublic::fileName3X3[8];
	CPublic::fpCur=fopen(CPublic::curFile,"w");

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	
	//设置标示
	pTestPogDlg->flag = 1;
}


void CCaliDlg3X3::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialog::PostNcDestroy();
}
