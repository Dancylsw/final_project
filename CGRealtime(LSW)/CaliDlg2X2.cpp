// CaliDlg2X2.cpp : implementation file
//

#include "stdafx.h"
//#include "CGSnapEx.h"

#include "CGRealtime.h"
#include "CaliDlg2X2.h"
#include "MainFrm.h"
#include "CGRealtimeDoc.h"
#include "CGRealtimeView.h"
#include "Public.h"
#include "TSTPOG.h"

#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaliDlg2X2 dialog


CCaliDlg2X2::CCaliDlg2X2(CWnd* pParent /*=NULL*/)
	: CDialog(CCaliDlg2X2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCaliDlg2X2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
//	m_statetag = 0;
//	m_caliPoint.setX(0);
//	m_caliPoint.setY(0);
}


void CCaliDlg2X2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCaliDlg2X2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCaliDlg2X2, CDialog)
	//{{AFX_MSG_MAP(CCaliDlg2X2)
	ON_BN_CLICKED(IDC_BT_2X2_1, OnBt2x21)
	ON_BN_CLICKED(IDC_BT_2X2_2, OnBt2x22)
	ON_BN_CLICKED(IDC_BT_2X2_3, OnBt2x23)
	ON_BN_CLICKED(IDC_BT_2X2_4, OnBt2x24)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaliDlg2X2 message handlers

void CCaliDlg2X2::OnBt2x21() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint[0];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha[0];
	CPublic::g_pBestVector=&CPublic::g_BestVector2x2[0];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fp[0]=fopen(CPublic::fileName[0],"w");
	CPublic::fpCur=CPublic::fp[0];
	CPublic::curFile=CPublic::fileName[0];

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);

	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg2X2::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialog::PostNcDestroy();
}

void CCaliDlg2X2::OnBt2x22() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint[1];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha[1];
	CPublic::g_pBestVector=&CPublic::g_BestVector2x2[1];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fp[1]=fopen(CPublic::fileName[1],"w");
	CPublic::fpCur=CPublic::fp[1];
	CPublic::curFile=CPublic::fileName[1];

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);

	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg2X2::OnBt2x23() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint[2];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha[2];
	CPublic::g_pBestVector=&CPublic::g_BestVector2x2[2];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fp[2]=fopen(CPublic::fileName[2],"w");
	CPublic::fpCur=CPublic::fp[2];
	CPublic::curFile=CPublic::fileName[2];

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);

	//设置标示
	pTestPogDlg->flag = 1;
}

void CCaliDlg2X2::OnBt2x24() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=1;
	CPublic::g_pCaliPoint=&CPublic::g_caliPoint[3];
	CPublic::g_pBestAlpha=&CPublic::g_BestAlpha[3];
	CPublic::g_pBestVector=&CPublic::g_BestVector2x2[3];
	SetCursorPos(CPublic::g_pCaliPoint->getX(),CPublic::g_pCaliPoint->getY());
	CPublic::fp[3]=fopen(CPublic::fileName[3],"w");
	CPublic::fpCur=CPublic::fp[3];
	CPublic::curFile=CPublic::fileName[3];

	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);

	//设置标示
	pTestPogDlg->flag = 1;
}
