// ActDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CGRealtime.h"
#include "ActDlg.h"
#include "Public.h"
#include "TSTPOG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActDlg dialog


CActDlg::CActDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CActDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CActDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CActDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CActDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CActDlg, CDialog)
	//{{AFX_MSG_MAP(CActDlg)
	ON_BN_CLICKED(IDC_ACBT1, OnAcbt1)
	ON_BN_CLICKED(IDC_ACTDONE, OnActdone)
	ON_BN_CLICKED(IDC_ACBT2, OnAcbt2)
	ON_BN_CLICKED(IDC_ACBT3, OnAcbt3)
	ON_BN_CLICKED(IDC_ACBT4, OnAcbt4)
	ON_BN_CLICKED(IDC_ACBT5, OnAcbt5)
	ON_BN_CLICKED(IDC_ACBT6, OnAcbt6)
	ON_BN_CLICKED(IDC_ACBT7, OnAcbt7)
	ON_BN_CLICKED(IDC_ACBT8, OnAcbt8)
	ON_BN_CLICKED(IDC_ACBT9, OnAcbt9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActDlg message handlers

void CActDlg::OnAcbt1() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=3;
	CPublic::g_pCurTestPoint = &CPublic::g_TestPoint[0];
	SetCursorPos(CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY());
//	SetWindowPos(&wndTopMost,CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY(),0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
	CPublic::curTestFileName = CPublic::testFileName[0];
	CPublic::fpTestCur = CPublic::fpTest[0];
	CPublic::fpTestCur = fopen(CPublic::curTestFileName,"w"); 
	
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	pTestPogDlg->flag = 2;
}

void CActDlg::OnAcbt2() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=3;
	CPublic::g_pCurTestPoint = &CPublic::g_TestPoint[1];
	SetCursorPos(CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY());
//	SetWindowPos(&wndTopMost,CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY(),0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
	CPublic::curTestFileName = CPublic::testFileName[1];
	CPublic::fpTestCur = CPublic::fpTest[1];
	CPublic::fpTestCur = fopen(CPublic::curTestFileName,"w");
	
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	pTestPogDlg->flag = 2;
}

void CActDlg::OnAcbt3() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=3;
	CPublic::g_pCurTestPoint = &CPublic::g_TestPoint[2];
	SetCursorPos(CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY());
	//	SetWindowPos(&wndTopMost,CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY(),0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
	CPublic::curTestFileName = CPublic::testFileName[2];
	CPublic::fpTestCur = CPublic::fpTest[2];
	CPublic::fpTestCur = fopen(CPublic::curTestFileName,"w");
	
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	pTestPogDlg->flag = 2;
}

void CActDlg::OnAcbt4() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=3;
	CPublic::g_pCurTestPoint = &CPublic::g_TestPoint[3];
	SetCursorPos(CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY());
	//	SetWindowPos(&wndTopMost,CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY(),0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
	CPublic::curTestFileName = CPublic::testFileName[3];
	CPublic::fpTestCur = CPublic::fpTest[3];
	CPublic::fpTestCur = fopen(CPublic::curTestFileName,"w");
	
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	pTestPogDlg->flag = 2;
}

void CActDlg::OnAcbt5() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=3;
	CPublic::g_pCurTestPoint = &CPublic::g_TestPoint[4];
	SetCursorPos(CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY());
	//	SetWindowPos(&wndTopMost,CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY(),0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
	CPublic::curTestFileName = CPublic::testFileName[4];
	CPublic::fpTestCur = CPublic::fpTest[4];
	CPublic::fpTestCur = fopen(CPublic::curTestFileName,"w");
	
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	pTestPogDlg->flag = 2;
}

void CActDlg::OnAcbt6() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=3;
	CPublic::g_pCurTestPoint = &CPublic::g_TestPoint[5];
	SetCursorPos(CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY());
	//	SetWindowPos(&wndTopMost,CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY(),0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
	CPublic::curTestFileName = CPublic::testFileName[5];
	CPublic::fpTestCur = CPublic::fpTest[5];
	CPublic::fpTestCur = fopen(CPublic::curTestFileName,"w");
	
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	pTestPogDlg->flag = 2;
}

void CActDlg::OnAcbt7() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=3;
	CPublic::g_pCurTestPoint = &CPublic::g_TestPoint[6];
	SetCursorPos(CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY());
	//	SetWindowPos(&wndTopMost,CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY(),0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
	CPublic::curTestFileName = CPublic::testFileName[6];
	CPublic::fpTestCur = CPublic::fpTest[6];
	CPublic::fpTestCur = fopen(CPublic::curTestFileName,"w");
	
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	pTestPogDlg->flag = 2;
}

void CActDlg::OnAcbt8() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=3;
	CPublic::g_pCurTestPoint = &CPublic::g_TestPoint[7];
	SetCursorPos(CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY());
	//	SetWindowPos(&wndTopMost,CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY(),0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
	CPublic::curTestFileName = CPublic::testFileName[7];
	CPublic::fpTestCur = CPublic::fpTest[7];
	CPublic::fpTestCur = fopen(CPublic::curTestFileName,"w");
	
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	pTestPogDlg->flag = 2;
}

void CActDlg::OnAcbt9() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=3;
	CPublic::g_pCurTestPoint = &CPublic::g_TestPoint[8];
	SetCursorPos(CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY());
	//	SetWindowPos(&wndTopMost,CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY(),0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
	CPublic::curTestFileName = CPublic::testFileName[8];
	CPublic::fpTestCur = CPublic::fpTest[8];
	CPublic::fpTestCur = fopen(CPublic::curTestFileName,"w");
	
	CTSTPOG *pTestPogDlg = new CTSTPOG;
	pTestPogDlg->Create(IDD_TSTPOG,this);
	pTestPogDlg->ShowWindow(SW_SHOW);
	pTestPogDlg->flag = 2;
}

void CActDlg::OnActdone() 
{
	// TODO: Add your control notification handler code here
	CPublic::stateTag=0;
	if (NULL != CPublic::fpTestCur)
	{
		fclose(CPublic::fpTestCur);
	}
}

void CActDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialog::PostNcDestroy();
}