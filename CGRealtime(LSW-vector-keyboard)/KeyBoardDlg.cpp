// KeyBoardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KeyBoardDlg.h"
#include "PassWordDlg.h"
#include "Public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeyBoardDlg dialog


CKeyBoardDlg::CKeyBoardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyBoardDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeyBoardDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_input = _T("");
	//}}AFX_DATA_INIT
}


void CKeyBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyBoardDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_EDIT, m_input);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKeyBoardDlg, CDialog)
	//{{AFX_MSG_MAP(CKeyBoardDlg)
	ON_BN_CLICKED(IDC_KEY_Q, OnKeyQ)
	ON_BN_CLICKED(IDC_KEY_A, OnKeyA)
	ON_BN_CLICKED(IDC_KEY_E, OnKeyE)
	ON_BN_CLICKED(IDC_KEY_R, OnKeyR)
	ON_BN_CLICKED(IDC_KEY_T, OnKeyT)
	ON_BN_CLICKED(IDC_KEY_Y, OnKeyY)
	ON_BN_CLICKED(IDC_KEY_U, OnKeyU)
	ON_BN_CLICKED(IDC_KEY_I, OnKeyI)
	ON_BN_CLICKED(IDC_KEY_O, OnKeyO)
	ON_BN_CLICKED(IDC_KEY_P, OnKeyP)
	ON_BN_CLICKED(IDC_KEY_W, OnKeyW)
	ON_BN_CLICKED(IDC_KEY_S, OnKeyS)
	ON_BN_CLICKED(IDC_KEY_D, OnKeyD)
	ON_BN_CLICKED(IDC_KEY_F, OnKeyF)
	ON_BN_CLICKED(IDC_KEY_G, OnKeyG)
	ON_BN_CLICKED(IDC_KEY_H, OnKeyH)
	ON_BN_CLICKED(IDC_KEY_J, OnKeyJ)
	ON_BN_CLICKED(IDC_KEY_K, OnKeyK)
	ON_BN_CLICKED(IDC_KEY_L, OnKeyL)
	ON_BN_CLICKED(IDC_KEY_Z, OnKeyZ)
	ON_BN_CLICKED(IDC_KEY_X, OnKeyX)
	ON_BN_CLICKED(IDC_KEY_C, OnKeyC)
	ON_BN_CLICKED(IDC_KEY_V, OnKeyV)
	ON_BN_CLICKED(IDC_KEY_B, OnKeyB)
	ON_BN_CLICKED(IDC_KEY_N, OnKeyN)
	ON_BN_CLICKED(IDC_KEY_M, OnKeyM)
	ON_BN_CLICKED(IDC_KEY_CLEAR, OnKeyClear)
	ON_BN_CLICKED(IDC_KEY_BACKSPACE, OnKeyBackspace)
	ON_BN_CLICKED(IDC_KEY_SPACE, OnKeySpace)
	ON_BN_CLICKED(IDC_KEY_LOCK, OnKeyLock)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyBoardDlg message handlers

void CKeyBoardDlg::OnKeyQ() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("q");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyA() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("a");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyE() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("e");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyR() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("r");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyT() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("t");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyY() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("y");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyU() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("u");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyI() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("i");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyO() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("o");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyP() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("p");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyW() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("w");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyS() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("s");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyD() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("d");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyF() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("f");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyG() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("g");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyH() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("h");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyJ() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("j");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyK() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("k");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyL() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("l");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyZ() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("z");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyX() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("x");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyC() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("c");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyV() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("v");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyB() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("b");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyN() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("n");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyM() 
{
	// TODO: Add your control notification handler code here
	m_input += CString("m");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyClear() 
{
	// TODO: Add your control notification handler code here
	m_input = CString("");

	GetDlgItem(IDC_KEY_A)->GetWindowRect(&CPublic::rectAlp[0]);
	GetDlgItem(IDC_KEY_B)->GetWindowRect(&CPublic::rectAlp[1]);
	GetDlgItem(IDC_KEY_C)->GetWindowRect(&CPublic::rectAlp[2]);
	GetDlgItem(IDC_KEY_D)->GetWindowRect(&CPublic::rectAlp[3]);
	GetDlgItem(IDC_KEY_E)->GetWindowRect(&CPublic::rectAlp[4]);
	GetDlgItem(IDC_KEY_F)->GetWindowRect(&CPublic::rectAlp[5]);
	GetDlgItem(IDC_KEY_G)->GetWindowRect(&CPublic::rectAlp[6]);
	GetDlgItem(IDC_KEY_H)->GetWindowRect(&CPublic::rectAlp[7]);
	GetDlgItem(IDC_KEY_I)->GetWindowRect(&CPublic::rectAlp[8]);
	GetDlgItem(IDC_KEY_J)->GetWindowRect(&CPublic::rectAlp[9]);
	GetDlgItem(IDC_KEY_K)->GetWindowRect(&CPublic::rectAlp[10]);
	GetDlgItem(IDC_KEY_L)->GetWindowRect(&CPublic::rectAlp[11]);
	GetDlgItem(IDC_KEY_M)->GetWindowRect(&CPublic::rectAlp[12]);
	GetDlgItem(IDC_KEY_N)->GetWindowRect(&CPublic::rectAlp[13]);
	GetDlgItem(IDC_KEY_O)->GetWindowRect(&CPublic::rectAlp[14]);
	GetDlgItem(IDC_KEY_P)->GetWindowRect(&CPublic::rectAlp[15]);
	GetDlgItem(IDC_KEY_Q)->GetWindowRect(&CPublic::rectAlp[16]);
	GetDlgItem(IDC_KEY_R)->GetWindowRect(&CPublic::rectAlp[17]);
	GetDlgItem(IDC_KEY_S)->GetWindowRect(&CPublic::rectAlp[18]);
	GetDlgItem(IDC_KEY_T)->GetWindowRect(&CPublic::rectAlp[19]);
	GetDlgItem(IDC_KEY_U)->GetWindowRect(&CPublic::rectAlp[20]);
	GetDlgItem(IDC_KEY_V)->GetWindowRect(&CPublic::rectAlp[21]);
	GetDlgItem(IDC_KEY_W)->GetWindowRect(&CPublic::rectAlp[22]);
	GetDlgItem(IDC_KEY_X)->GetWindowRect(&CPublic::rectAlp[23]);
	GetDlgItem(IDC_KEY_Y)->GetWindowRect(&CPublic::rectAlp[24]);
	GetDlgItem(IDC_KEY_Z)->GetWindowRect(&CPublic::rectAlp[25]);
	GetDlgItem(IDC_KEY_CLEAR)->GetWindowRect(&CPublic::rectAlp[26]);
	GetDlgItem(IDC_KEY_BACKSPACE)->GetWindowRect(&CPublic::rectAlp[27]);
	GetDlgItem(IDC_KEY_LOCK)->GetWindowRect(&CPublic::rectAlp[28]);
	GetDlgItem(IDC_KEY_SPACE)->GetWindowRect(&CPublic::rectAlp[29]);
	CPublic::AlpFlag = TRUE;

	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyBackspace() 
{
	// TODO: Add your control notification handler code here
	int n = m_input.GetLength();
	m_input = m_input.Left(n-1);
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeySpace() 
{
	// TODO: Add your control notification handler code here
	m_input += CString(" ");
	UpdateData(FALSE);
}

void CKeyBoardDlg::OnKeyLock() 
{
	// TODO: Add your control notification handler code here
	CPublic::AlpFlag = FALSE;
	this->EndDialog(0);
	CPassWordDlg *pPWDlg = new CPassWordDlg;
	pPWDlg->Create(IDD_PassWord, this);
	pPWDlg->ShowWindow(SW_SHOW);
}

BOOL CKeyBoardDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CFont * f; 
	f = new CFont; 
	f->CreateFont(75, // nHeight 
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
	GetDlgItem(IDC_EDIT)->SetFont(f);      //IDC_EDIT_RECEIVEÊÇEdit¿ò±êºÅ
	
	//ÉèÖÃ¼üÅÌ×ÖÄ¸×ÖÌå
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
	
	GetDlgItem(IDC_KEY_A)->SetFont(g);
	GetDlgItem(IDC_KEY_B)->SetFont(g);
	GetDlgItem(IDC_KEY_C)->SetFont(g);
	GetDlgItem(IDC_KEY_D)->SetFont(g);
	GetDlgItem(IDC_KEY_E)->SetFont(g);
	GetDlgItem(IDC_KEY_F)->SetFont(g);
	GetDlgItem(IDC_KEY_G)->SetFont(g);
	GetDlgItem(IDC_KEY_H)->SetFont(g);
	GetDlgItem(IDC_KEY_I)->SetFont(g);
	GetDlgItem(IDC_KEY_J)->SetFont(g);
	GetDlgItem(IDC_KEY_K)->SetFont(g);
	GetDlgItem(IDC_KEY_L)->SetFont(g);
	GetDlgItem(IDC_KEY_M)->SetFont(g);
	GetDlgItem(IDC_KEY_N)->SetFont(g);
	GetDlgItem(IDC_KEY_O)->SetFont(g);
	GetDlgItem(IDC_KEY_P)->SetFont(g);
	GetDlgItem(IDC_KEY_Q)->SetFont(g);
	GetDlgItem(IDC_KEY_R)->SetFont(g);
	GetDlgItem(IDC_KEY_S)->SetFont(g);
	GetDlgItem(IDC_KEY_T)->SetFont(g);
	GetDlgItem(IDC_KEY_U)->SetFont(g);
	GetDlgItem(IDC_KEY_V)->SetFont(g);
	GetDlgItem(IDC_KEY_W)->SetFont(g);
	GetDlgItem(IDC_KEY_X)->SetFont(g);
	GetDlgItem(IDC_KEY_Y)->SetFont(g);
	GetDlgItem(IDC_KEY_Z)->SetFont(g);
	GetDlgItem(IDC_KEY_BACKSPACE)->SetFont(g);
	GetDlgItem(IDC_KEY_CLEAR)->SetFont(g);
	GetDlgItem(IDC_KEY_SPACE)->SetFont(g);
	GetDlgItem(IDC_KEY_LOCK)->SetFont(g);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKeyBoardDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CPublic::AlpFlag = FALSE;
	CDialog::OnClose();
}
