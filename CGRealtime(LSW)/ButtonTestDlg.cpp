// ButtonTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CGRealtime.h"
#include "ButtonTestDlg.h"
#include "MainFrm.h"
#include "CGRealtimeDoc.h"
#include "CGRealtimeView.h"
#include "Public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonTestDlg dialog


CButtonTestDlg::CButtonTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CButtonTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CButtonTestDlg)
	m_input = _T("");
	//}}AFX_DATA_INIT
}


void CButtonTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CButtonTestDlg)
	DDX_Text(pDX, IDC_EDIT1, m_input);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CButtonTestDlg, CDialog)
	//{{AFX_MSG_MAP(CButtonTestDlg)
	ON_BN_CLICKED(IDC_BTST_ABC, OnBtstAbc)
	ON_BN_CLICKED(IDC_BTST_DEF, OnBtstDef)
	ON_BN_CLICKED(IDC_BTST_GHI, OnBtstGhi)
	ON_BN_CLICKED(IDC_BTST_JKL, OnBtstJkl)
	ON_BN_CLICKED(IDC_BTST_MNO, OnBtstMno)
	ON_BN_CLICKED(IDC_BTST_PQRS, OnBtstPqrs)
	ON_BN_CLICKED(IDC_BTST_TUV, OnBtstTuv)
	ON_BN_CLICKED(IDC_BTST_WXYZ, OnBtstWxyz)
	ON_BN_CLICKED(IDC_BTTEST_A, OnBttestA)
	ON_BN_CLICKED(IDC_BTTEST_B, OnBttestB)
	ON_BN_CLICKED(IDC_BTTEST_C, OnBttestC)
	ON_BN_CLICKED(IDC_BTTEST_D, OnBttestD)
	ON_BN_CLICKED(IDC_BTTEST_E, OnBttestE)
	ON_BN_CLICKED(IDC_BTTEST_F, OnBttestF)
	ON_BN_CLICKED(IDC_BTTEST_G, OnBttestG)
	ON_BN_CLICKED(IDC_BTTEST_H, OnBttestH)
	ON_BN_CLICKED(IDC_BTTEST_I, OnBttestI)
	ON_BN_CLICKED(IDC_BTTEST_J, OnBttestJ)
	ON_BN_CLICKED(IDC_BTTEST_K, OnBttestK)
	ON_BN_CLICKED(IDC_BTTEST_L, OnBttestL)
	ON_BN_CLICKED(IDC_BTTEST_M, OnBttestM)
	ON_BN_CLICKED(IDC_BTTEST_N, OnBttestN)
	ON_BN_CLICKED(IDC_BTTEST_O, OnBttestO)
	ON_BN_CLICKED(IDC_BTTEST_T, OnBttestT)
	ON_BN_CLICKED(IDC_BTTEST_U, OnBttestU)
	ON_BN_CLICKED(IDC_BTTEST_V, OnBttestV)
	ON_BN_CLICKED(IDC_BTST_W, OnBtstW)
	ON_BN_CLICKED(IDC_BTST_X, OnBtstX)
	ON_BN_CLICKED(IDC_BTST_Y, OnBtstY)
	ON_BN_CLICKED(IDC_BTST_Z, OnBtstZ)
	ON_BN_CLICKED(IDC_BTST_BACKSPACE, OnBtstBackspace)
	ON_BN_CLICKED(IDC_BTST_CLEAR, OnBtstClear)
	ON_BN_CLICKED(IDC_BTST_INBACK, OnBtstInback)
	ON_BN_CLICKED(IDC_BTST_SPACE, OnBtstSpace)
	ON_BN_CLICKED(IDC_BTTEST_BACK, OnBttestBack)
	ON_BN_CLICKED(IDC_BTST_P, OnBtstP)
	ON_BN_CLICKED(IDC_BTST_Q, OnBtstQ)
	ON_BN_CLICKED(IDC_BTST_R, OnBtstR)
	ON_BN_CLICKED(IDC_BTST_S, OnBtstS)
	ON_WM_CANCELMODE()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CButtonTestDlg)
EASYSIZE(IDC_EDIT1, ES_BORDER,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)
EASYSIZE(IDC_BTST_SPACE,ES_BORDER,IDC_EDIT1,IDC_BTST_BACKSPACE,IDC_BTST_CLEAR,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_BACKSPACE, IDC_BTST_SPACE,IDC_EDIT1,IDC_BTST_ABC,IDC_BTST_GHI,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_ABC, IDC_BTST_BACKSPACE,IDC_EDIT1,IDC_BTST_DEF,IDC_BTST_JKL,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_DEF, IDC_BTST_ABC,IDC_EDIT1,ES_BORDER,IDC_BTST_MNO,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_GHI, IDC_BTST_SPACE,IDC_BTST_BACKSPACE,IDC_BTST_JKL,IDC_BTST_PQRS,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_JKL, IDC_BTST_GHI,IDC_BTST_ABC,IDC_BTST_MNO,IDC_BTST_TUV,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_MNO, IDC_BTST_JKL,IDC_BTST_DEF,ES_BORDER,IDC_BTST_WXYZ,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_CLEAR, ES_BORDER,IDC_BTST_SPACE,IDC_BTST_PQRS,ES_BORDER,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_PQRS, IDC_BTST_CLEAR,IDC_BTST_GHI,IDC_BTST_TUV,ES_BORDER,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_TUV, IDC_BTST_PQRS,IDC_BTST_JKL,IDC_BTST_WXYZ,ES_BORDER,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_WXYZ, IDC_BTST_TUV,IDC_BTST_MNO,ES_BORDER,ES_BORDER,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_A,ES_BORDER,IDC_EDIT1,IDC_BTTEST_B,IDC_BTTEST_C,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_B,IDC_BTTEST_A,IDC_EDIT1,ES_BORDER,IDC_BTTEST_BACK,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_C,ES_BORDER,IDC_BTTEST_A,IDC_BTTEST_BACK,ES_BORDER,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_BACK,IDC_BTTEST_C,IDC_BTTEST_B,ES_BORDER,ES_BORDER,ES_HCENTER|ES_VCENTER)

EASYSIZE(IDC_BTTEST_D,ES_BORDER,IDC_EDIT1,IDC_BTTEST_E,IDC_BTTEST_F,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_E,IDC_BTTEST_D,IDC_EDIT1,ES_BORDER,IDC_BTTEST_BACK,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_F,ES_BORDER,IDC_BTTEST_D,IDC_BTTEST_BACK,ES_BORDER,ES_HCENTER|ES_VCENTER)

EASYSIZE(IDC_BTTEST_G,ES_BORDER,IDC_EDIT1,IDC_BTTEST_H,IDC_BTTEST_I,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_H,IDC_BTTEST_G,IDC_EDIT1,ES_BORDER,IDC_BTTEST_BACK,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_I,ES_BORDER,IDC_BTTEST_G,IDC_BTTEST_BACK,ES_BORDER,ES_HCENTER|ES_VCENTER)

EASYSIZE(IDC_BTTEST_J,ES_BORDER,IDC_EDIT1,IDC_BTTEST_K,IDC_BTTEST_L,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_K,IDC_BTTEST_G,IDC_EDIT1,ES_BORDER,IDC_BTTEST_BACK,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_L,ES_BORDER,IDC_BTTEST_J,IDC_BTTEST_BACK,ES_BORDER,ES_HCENTER|ES_VCENTER)

EASYSIZE(IDC_BTTEST_M,ES_BORDER,IDC_EDIT1,IDC_BTTEST_N,IDC_BTTEST_O,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_N,IDC_BTTEST_M,IDC_EDIT1,ES_BORDER,IDC_BTTEST_BACK,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_O,ES_BORDER,IDC_BTTEST_M,IDC_BTTEST_BACK,ES_BORDER,ES_HCENTER|ES_VCENTER)

EASYSIZE(IDC_BTTEST_T,ES_BORDER,IDC_EDIT1,IDC_BTTEST_U,IDC_BTTEST_V,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_U,IDC_BTTEST_T,IDC_EDIT1,ES_BORDER,IDC_BTTEST_BACK,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTTEST_V,ES_BORDER,IDC_BTTEST_T,IDC_BTTEST_BACK,ES_BORDER,ES_HCENTER|ES_VCENTER)

EASYSIZE(IDC_BTST_INBACK,ES_BORDER,IDC_EDIT1,IDC_BTST_P,ES_BORDER,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_P,IDC_BTST_INBACK,IDC_EDIT1,IDC_BTST_Q,IDC_BTST_R,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_Q,IDC_BTST_P,IDC_EDIT1,ES_BORDER,IDC_BTST_S,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_R,IDC_BTST_INBACK,IDC_BTST_P,IDC_BTST_S,ES_BORDER,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_S,IDC_BTST_R,IDC_BTST_P,ES_BORDER,ES_BORDER,ES_HCENTER|ES_VCENTER)

EASYSIZE(IDC_BTST_W,IDC_BTST_INBACK,IDC_EDIT1,IDC_BTST_X,IDC_BTST_Y,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_X,IDC_BTST_W,IDC_EDIT1,ES_BORDER,IDC_BTST_Z,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_Y,IDC_BTST_INBACK,IDC_BTST_W,IDC_BTST_Z,ES_BORDER,ES_HCENTER|ES_VCENTER)
EASYSIZE(IDC_BTST_Z,IDC_BTST_Y,IDC_BTST_W,ES_BORDER,ES_BORDER,ES_HCENTER|ES_VCENTER)
END_EASYSIZE_MAP

/////////////////////////////////////////////////////////////////////////////
// CButtonTestDlg message handlers

void CButtonTestDlg::OnBtstAbc() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTTEST_A)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_B)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_C)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_D)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_E)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_F)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_G)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_H)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_I)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_J)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_K)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_L)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_M)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_N)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_O)->ShowWindow(false);
	GetDlgItem(IDC_BTST_P)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Q)->ShowWindow(false);
	GetDlgItem(IDC_BTST_R)->ShowWindow(false);
	GetDlgItem(IDC_BTST_S)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_T)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_U)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_V)->ShowWindow(false);
	GetDlgItem(IDC_BTST_W)->ShowWindow(false);
	GetDlgItem(IDC_BTST_X)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Y)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Z)->ShowWindow(false);
	GetDlgItem(IDC_BTST_ABC)->ShowWindow(false);
	GetDlgItem(IDC_BTST_DEF)->ShowWindow(false);
	GetDlgItem(IDC_BTST_GHI)->ShowWindow(false);
	GetDlgItem(IDC_BTST_JKL)->ShowWindow(false);
	GetDlgItem(IDC_BTST_MNO)->ShowWindow(false);
	GetDlgItem(IDC_BTST_PQRS)->ShowWindow(false);
	GetDlgItem(IDC_BTST_TUV)->ShowWindow(false);
	GetDlgItem(IDC_BTST_WXYZ)->ShowWindow(false);
	GetDlgItem(IDC_BTST_BACKSPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTST_CLEAR)->ShowWindow(false);
	GetDlgItem(IDC_BTST_INBACK)->ShowWindow(false);
	GetDlgItem(IDC_BTST_SPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_BACK)->ShowWindow(true);
}

void CButtonTestDlg::OnBtstDef() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTTEST_A)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_B)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_C)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_D)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_E)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_F)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_G)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_H)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_I)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_J)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_K)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_L)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_M)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_N)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_O)->ShowWindow(false);
	GetDlgItem(IDC_BTST_P)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Q)->ShowWindow(false);
	GetDlgItem(IDC_BTST_R)->ShowWindow(false);
	GetDlgItem(IDC_BTST_S)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_T)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_U)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_V)->ShowWindow(false);
	GetDlgItem(IDC_BTST_W)->ShowWindow(false);
	GetDlgItem(IDC_BTST_X)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Y)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Z)->ShowWindow(false);
	GetDlgItem(IDC_BTST_ABC)->ShowWindow(false);
	GetDlgItem(IDC_BTST_DEF)->ShowWindow(false);
	GetDlgItem(IDC_BTST_GHI)->ShowWindow(false);
	GetDlgItem(IDC_BTST_JKL)->ShowWindow(false);
	GetDlgItem(IDC_BTST_MNO)->ShowWindow(false);
	GetDlgItem(IDC_BTST_PQRS)->ShowWindow(false);
	GetDlgItem(IDC_BTST_TUV)->ShowWindow(false);
	GetDlgItem(IDC_BTST_WXYZ)->ShowWindow(false);
	GetDlgItem(IDC_BTST_BACKSPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTST_CLEAR)->ShowWindow(false);
	GetDlgItem(IDC_BTST_INBACK)->ShowWindow(false);
	GetDlgItem(IDC_BTST_SPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_BACK)->ShowWindow(true);
}

void CButtonTestDlg::OnBtstGhi() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTTEST_A)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_B)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_C)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_D)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_E)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_F)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_G)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_H)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_I)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_J)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_K)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_L)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_M)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_N)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_O)->ShowWindow(false);
	GetDlgItem(IDC_BTST_P)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Q)->ShowWindow(false);
	GetDlgItem(IDC_BTST_R)->ShowWindow(false);
	GetDlgItem(IDC_BTST_S)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_T)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_U)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_V)->ShowWindow(false);
	GetDlgItem(IDC_BTST_W)->ShowWindow(false);
	GetDlgItem(IDC_BTST_X)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Y)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Z)->ShowWindow(false);
	GetDlgItem(IDC_BTST_ABC)->ShowWindow(false);
	GetDlgItem(IDC_BTST_DEF)->ShowWindow(false);
	GetDlgItem(IDC_BTST_GHI)->ShowWindow(false);
	GetDlgItem(IDC_BTST_JKL)->ShowWindow(false);
	GetDlgItem(IDC_BTST_MNO)->ShowWindow(false);
	GetDlgItem(IDC_BTST_PQRS)->ShowWindow(false);
	GetDlgItem(IDC_BTST_TUV)->ShowWindow(false);
	GetDlgItem(IDC_BTST_WXYZ)->ShowWindow(false);
	GetDlgItem(IDC_BTST_BACKSPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTST_CLEAR)->ShowWindow(false);
	GetDlgItem(IDC_BTST_INBACK)->ShowWindow(false);
	GetDlgItem(IDC_BTST_SPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_BACK)->ShowWindow(true);
}

void CButtonTestDlg::OnBtstJkl() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTTEST_A)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_B)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_C)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_D)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_E)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_F)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_G)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_H)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_I)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_J)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_K)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_L)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_M)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_N)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_O)->ShowWindow(false);
	GetDlgItem(IDC_BTST_P)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Q)->ShowWindow(false);
	GetDlgItem(IDC_BTST_R)->ShowWindow(false);
	GetDlgItem(IDC_BTST_S)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_T)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_U)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_V)->ShowWindow(false);
	GetDlgItem(IDC_BTST_W)->ShowWindow(false);
	GetDlgItem(IDC_BTST_X)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Y)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Z)->ShowWindow(false);
	GetDlgItem(IDC_BTST_ABC)->ShowWindow(false);
	GetDlgItem(IDC_BTST_DEF)->ShowWindow(false);
	GetDlgItem(IDC_BTST_GHI)->ShowWindow(false);
	GetDlgItem(IDC_BTST_JKL)->ShowWindow(false);
	GetDlgItem(IDC_BTST_MNO)->ShowWindow(false);
	GetDlgItem(IDC_BTST_PQRS)->ShowWindow(false);
	GetDlgItem(IDC_BTST_TUV)->ShowWindow(false);
	GetDlgItem(IDC_BTST_WXYZ)->ShowWindow(false);
	GetDlgItem(IDC_BTST_BACKSPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTST_CLEAR)->ShowWindow(false);
	GetDlgItem(IDC_BTST_INBACK)->ShowWindow(false);
	GetDlgItem(IDC_BTST_SPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_BACK)->ShowWindow(true);
}

void CButtonTestDlg::OnBtstMno() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTTEST_A)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_B)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_C)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_D)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_E)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_F)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_G)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_H)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_I)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_J)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_K)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_L)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_M)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_N)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_O)->ShowWindow(true);
	GetDlgItem(IDC_BTST_P)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Q)->ShowWindow(false);
	GetDlgItem(IDC_BTST_R)->ShowWindow(false);
	GetDlgItem(IDC_BTST_S)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_T)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_U)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_V)->ShowWindow(false);
	GetDlgItem(IDC_BTST_W)->ShowWindow(false);
	GetDlgItem(IDC_BTST_X)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Y)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Z)->ShowWindow(false);
	GetDlgItem(IDC_BTST_ABC)->ShowWindow(false);
	GetDlgItem(IDC_BTST_DEF)->ShowWindow(false);
	GetDlgItem(IDC_BTST_GHI)->ShowWindow(false);
	GetDlgItem(IDC_BTST_JKL)->ShowWindow(false);
	GetDlgItem(IDC_BTST_MNO)->ShowWindow(false);
	GetDlgItem(IDC_BTST_PQRS)->ShowWindow(false);
	GetDlgItem(IDC_BTST_TUV)->ShowWindow(false);
	GetDlgItem(IDC_BTST_WXYZ)->ShowWindow(false);
	GetDlgItem(IDC_BTST_BACKSPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTST_CLEAR)->ShowWindow(false);
	GetDlgItem(IDC_BTST_INBACK)->ShowWindow(false);
	GetDlgItem(IDC_BTST_SPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_BACK)->ShowWindow(true);
}

void CButtonTestDlg::OnBtstPqrs() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTTEST_A)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_B)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_C)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_D)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_E)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_F)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_G)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_H)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_I)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_J)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_K)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_L)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_M)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_N)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_O)->ShowWindow(false);
	GetDlgItem(IDC_BTST_P)->ShowWindow(true);
	GetDlgItem(IDC_BTST_Q)->ShowWindow(true);
	GetDlgItem(IDC_BTST_R)->ShowWindow(true);
	GetDlgItem(IDC_BTST_S)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_T)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_U)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_V)->ShowWindow(false);
	GetDlgItem(IDC_BTST_W)->ShowWindow(false);
	GetDlgItem(IDC_BTST_X)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Y)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Z)->ShowWindow(false);
	GetDlgItem(IDC_BTST_ABC)->ShowWindow(false);
	GetDlgItem(IDC_BTST_DEF)->ShowWindow(false);
	GetDlgItem(IDC_BTST_GHI)->ShowWindow(false);
	GetDlgItem(IDC_BTST_JKL)->ShowWindow(false);
	GetDlgItem(IDC_BTST_MNO)->ShowWindow(false);
	GetDlgItem(IDC_BTST_PQRS)->ShowWindow(false);
	GetDlgItem(IDC_BTST_TUV)->ShowWindow(false);
	GetDlgItem(IDC_BTST_WXYZ)->ShowWindow(false);
	GetDlgItem(IDC_BTST_BACKSPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTST_CLEAR)->ShowWindow(false);
	GetDlgItem(IDC_BTST_INBACK)->ShowWindow(true);
	GetDlgItem(IDC_BTST_SPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_BACK)->ShowWindow(false);
}

void CButtonTestDlg::OnBtstTuv() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTTEST_A)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_B)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_C)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_D)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_E)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_F)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_G)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_H)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_I)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_J)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_K)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_L)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_M)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_N)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_O)->ShowWindow(false);
	GetDlgItem(IDC_BTST_P)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Q)->ShowWindow(false);
	GetDlgItem(IDC_BTST_R)->ShowWindow(false);
	GetDlgItem(IDC_BTST_S)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_T)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_U)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_V)->ShowWindow(true);
	GetDlgItem(IDC_BTST_W)->ShowWindow(false);
	GetDlgItem(IDC_BTST_X)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Y)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Z)->ShowWindow(false);
	GetDlgItem(IDC_BTST_ABC)->ShowWindow(false);
	GetDlgItem(IDC_BTST_DEF)->ShowWindow(false);
	GetDlgItem(IDC_BTST_GHI)->ShowWindow(false);
	GetDlgItem(IDC_BTST_JKL)->ShowWindow(false);
	GetDlgItem(IDC_BTST_MNO)->ShowWindow(false);
	GetDlgItem(IDC_BTST_PQRS)->ShowWindow(false);
	GetDlgItem(IDC_BTST_TUV)->ShowWindow(false);
	GetDlgItem(IDC_BTST_WXYZ)->ShowWindow(false);
	GetDlgItem(IDC_BTST_BACKSPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTST_CLEAR)->ShowWindow(false);
	GetDlgItem(IDC_BTST_INBACK)->ShowWindow(false);
	GetDlgItem(IDC_BTST_SPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_BACK)->ShowWindow(true);
}

void CButtonTestDlg::OnBtstWxyz() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTTEST_A)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_B)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_C)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_D)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_E)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_F)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_G)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_H)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_I)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_J)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_K)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_L)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_M)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_N)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_O)->ShowWindow(false);
	GetDlgItem(IDC_BTST_P)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Q)->ShowWindow(false);
	GetDlgItem(IDC_BTST_R)->ShowWindow(false);
	GetDlgItem(IDC_BTST_S)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_T)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_U)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_V)->ShowWindow(false);
	GetDlgItem(IDC_BTST_W)->ShowWindow(true);
	GetDlgItem(IDC_BTST_X)->ShowWindow(true);
	GetDlgItem(IDC_BTST_Y)->ShowWindow(true);
	GetDlgItem(IDC_BTST_Z)->ShowWindow(true);
	GetDlgItem(IDC_BTST_ABC)->ShowWindow(false);
	GetDlgItem(IDC_BTST_DEF)->ShowWindow(false);
	GetDlgItem(IDC_BTST_GHI)->ShowWindow(false);
	GetDlgItem(IDC_BTST_JKL)->ShowWindow(false);
	GetDlgItem(IDC_BTST_MNO)->ShowWindow(false);
	GetDlgItem(IDC_BTST_PQRS)->ShowWindow(false);
	GetDlgItem(IDC_BTST_TUV)->ShowWindow(false);
	GetDlgItem(IDC_BTST_WXYZ)->ShowWindow(false);
	GetDlgItem(IDC_BTST_BACKSPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTST_CLEAR)->ShowWindow(false);
	GetDlgItem(IDC_BTST_INBACK)->ShowWindow(true);
	GetDlgItem(IDC_BTST_SPACE)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_BACK)->ShowWindow(false);
}

void CButtonTestDlg::OnBttestA() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("A");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestB() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("B");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestC() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("C");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestD() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("D");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestE() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("E");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestF() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("F");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestG() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("G");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestH() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("H");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestI() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("I");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestJ() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("J");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestK() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("K");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestL() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("L");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestM() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("M");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestN() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("N");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestO() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("O");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBtstP() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("P");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBtstQ() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("Q");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBtstR() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("R");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBtstS() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("S");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestT() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("T");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestU() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("U");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBttestV() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("V");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBtstW() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("W");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBtstX() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("X");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBtstY() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("Y");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBtstZ() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("Z");
	UpdateData(FALSE);
}

void CButtonTestDlg::OnBtstBackspace() 
{
	// TODO: Add your control notification handler code here
	int n=m_input.GetLength();
	m_input=m_input.Left(n-1);
	UpdateData(false);
}

void CButtonTestDlg::OnBtstClear() 
{
	// TODO: Add your control notification handler code here
	m_input=CString("");
	UpdateData(false);
}

void CButtonTestDlg::OnBtstInback() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTTEST_A)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_B)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_C)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_D)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_E)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_F)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_G)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_H)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_I)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_J)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_K)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_L)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_M)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_N)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_O)->ShowWindow(false);
	GetDlgItem(IDC_BTST_P)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Q)->ShowWindow(false);
	GetDlgItem(IDC_BTST_R)->ShowWindow(false);
	GetDlgItem(IDC_BTST_S)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_T)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_U)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_V)->ShowWindow(false);
	GetDlgItem(IDC_BTST_W)->ShowWindow(false);
	GetDlgItem(IDC_BTST_X)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Y)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Z)->ShowWindow(false);
	GetDlgItem(IDC_BTST_ABC)->ShowWindow(true);
	GetDlgItem(IDC_BTST_DEF)->ShowWindow(true);
	GetDlgItem(IDC_BTST_GHI)->ShowWindow(true);
	GetDlgItem(IDC_BTST_JKL)->ShowWindow(true);
	GetDlgItem(IDC_BTST_MNO)->ShowWindow(true);
	GetDlgItem(IDC_BTST_PQRS)->ShowWindow(true);
	GetDlgItem(IDC_BTST_TUV)->ShowWindow(true);
	GetDlgItem(IDC_BTST_WXYZ)->ShowWindow(true);
	GetDlgItem(IDC_BTST_BACKSPACE)->ShowWindow(true);
	GetDlgItem(IDC_BTST_CLEAR)->ShowWindow(true);
	GetDlgItem(IDC_BTST_INBACK)->ShowWindow(false);
	GetDlgItem(IDC_BTST_SPACE)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_BACK)->ShowWindow(false);
}

void CButtonTestDlg::OnBtstSpace() 
{
	// TODO: Add your control notification handler code here
	m_input += CString(" ");
	UpdateData(false);
}

void CButtonTestDlg::OnBttestBack() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTTEST_A)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_B)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_C)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_D)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_E)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_F)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_G)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_H)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_I)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_J)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_K)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_L)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_M)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_N)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_O)->ShowWindow(false);
	GetDlgItem(IDC_BTST_P)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Q)->ShowWindow(false);
	GetDlgItem(IDC_BTST_R)->ShowWindow(false);
	GetDlgItem(IDC_BTST_S)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_T)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_U)->ShowWindow(false);
	GetDlgItem(IDC_BTTEST_V)->ShowWindow(false);
	GetDlgItem(IDC_BTST_W)->ShowWindow(false);
	GetDlgItem(IDC_BTST_X)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Y)->ShowWindow(false);
	GetDlgItem(IDC_BTST_Z)->ShowWindow(false);
	GetDlgItem(IDC_BTST_ABC)->ShowWindow(true);
	GetDlgItem(IDC_BTST_DEF)->ShowWindow(true);
	GetDlgItem(IDC_BTST_GHI)->ShowWindow(true);
	GetDlgItem(IDC_BTST_JKL)->ShowWindow(true);
	GetDlgItem(IDC_BTST_MNO)->ShowWindow(true);
	GetDlgItem(IDC_BTST_PQRS)->ShowWindow(true);
	GetDlgItem(IDC_BTST_TUV)->ShowWindow(true);
	GetDlgItem(IDC_BTST_WXYZ)->ShowWindow(true);
	GetDlgItem(IDC_BTST_BACKSPACE)->ShowWindow(true);
	GetDlgItem(IDC_BTST_CLEAR)->ShowWindow(true);
	GetDlgItem(IDC_BTST_INBACK)->ShowWindow(false);
	GetDlgItem(IDC_BTST_SPACE)->ShowWindow(true);
	GetDlgItem(IDC_BTTEST_BACK)->ShowWindow(false);
}

void CButtonTestDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialog::PostNcDestroy();
}



BOOL CButtonTestDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	


	// TODO: Add extra initialization here

/*	ASSERT((IDD_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDD_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	*/
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
//设置EDIT字体大小

	CFont * f; 
 f = new CFont; 
 f->CreateFont(75, // nHeight 
 0, // nWidth 
 0, // nEscapement 
 0, // nOrientation 
 FW_BOLD, // nWeight 
 TRUE, // bItalic 
 FALSE, // bUnderline 
 0, // cStrikeOut 
 ANSI_CHARSET, // nCharSet 
 OUT_DEFAULT_PRECIS, // nOutPrecision 
 CLIP_DEFAULT_PRECIS, // nClipPrecision 
 DEFAULT_QUALITY, // nQuality 
 DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
 _T("Arial")); // lpszFac 
  GetDlgItem(IDC_EDIT1)->SetFont(f);      //IDC_EDIT_RECEIVE是Edit框标号
	//字体大小


 CFont * g; 
 g = new CFont; 
 g->CreateFont(42, // nHeight 
 0, // nWidth 
 0, // nEscapement 
 0, // nOrientation 
 FW_BOLD, // nWeight 
 FALSE, // bItalic 
 FALSE, // bUnderline 
 0, // cStrikeOut 
 ANSI_CHARSET, // nCharSet 
 OUT_DEFAULT_PRECIS, // nOutPrecision 
 CLIP_DEFAULT_PRECIS, // nClipPrecision 
 DEFAULT_QUALITY, // nQuality 
 DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
 _T("Arial")); // lpszFac 
  
 GetDlgItem(IDC_BTTEST_A)->SetFont(g);
	GetDlgItem(IDC_BTTEST_B)->SetFont(g);
	GetDlgItem(IDC_BTTEST_C)->SetFont(g);
	GetDlgItem(IDC_BTTEST_D)->SetFont(g);
	GetDlgItem(IDC_BTTEST_E)->SetFont(g);
	GetDlgItem(IDC_BTTEST_F)->SetFont(g);
	GetDlgItem(IDC_BTTEST_G)->SetFont(g);
	GetDlgItem(IDC_BTTEST_H)->SetFont(g);
	GetDlgItem(IDC_BTTEST_I)->SetFont(g);
	GetDlgItem(IDC_BTTEST_J)->SetFont(g);
	GetDlgItem(IDC_BTTEST_K)->SetFont(g);
	GetDlgItem(IDC_BTTEST_L)->SetFont(g);
	GetDlgItem(IDC_BTTEST_M)->SetFont(g);
	GetDlgItem(IDC_BTTEST_N)->SetFont(g);
	GetDlgItem(IDC_BTTEST_O)->SetFont(g);
	GetDlgItem(IDC_BTST_P)->SetFont(g);
	GetDlgItem(IDC_BTST_Q)->SetFont(g);
	GetDlgItem(IDC_BTST_R)->SetFont(g);
	GetDlgItem(IDC_BTST_S)->SetFont(g);
	GetDlgItem(IDC_BTTEST_T)->SetFont(g);
	GetDlgItem(IDC_BTTEST_U)->SetFont(g);
	GetDlgItem(IDC_BTTEST_V)->SetFont(g);
	GetDlgItem(IDC_BTST_W)->SetFont(g);
	GetDlgItem(IDC_BTST_X)->SetFont(g);
	GetDlgItem(IDC_BTST_Y)->SetFont(g);
	GetDlgItem(IDC_BTST_Z)->SetFont(g);
	GetDlgItem(IDC_BTST_ABC)->SetFont(g);
	GetDlgItem(IDC_BTST_DEF)->SetFont(g);
	GetDlgItem(IDC_BTST_GHI)->SetFont(g);
	GetDlgItem(IDC_BTST_JKL)->SetFont(g);
	GetDlgItem(IDC_BTST_MNO)->SetFont(g);
	GetDlgItem(IDC_BTST_PQRS)->SetFont(g);
	GetDlgItem(IDC_BTST_TUV)->SetFont(g);
	GetDlgItem(IDC_BTST_WXYZ)->SetFont(g);
	GetDlgItem(IDC_BTST_BACKSPACE)->SetFont(g);
	GetDlgItem(IDC_BTST_CLEAR)->SetFont(g);
	GetDlgItem(IDC_BTST_INBACK)->SetFont(g);
	GetDlgItem(IDC_BTST_SPACE)->SetFont(g);
	GetDlgItem(IDC_BTTEST_BACK)->SetFont(g);


	
//==================全屏
/*CRect rect;
 GetDesktopWindow()->GetWindowRect(rect);
 SetWindowPos(0,0,0,rect.right,rect.bottom,0);*/
	//===============

 INIT_EASYSIZE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CButtonTestDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CButtonTestDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	 UPDATE_EASYSIZE;
}

void CButtonTestDlg::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);
	
	// TODO: Add your message handler code here
	 EASYSIZE_MINSIZE(768,576,fwSide,pRect);
}

void CButtonTestDlg::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CButtonTestDlg::OnQueryDragIcon() 
{
	// TODO: Add your message handler code here and/or call default
	
//	return CDialog::OnQueryDragIcon();
	return (HCURSOR) m_hIcon;
}

void CButtonTestDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	

		CDialog::OnSysCommand(nID, lParam);
	
	//CDialog::OnSysCommand(nID, lParam);
}
