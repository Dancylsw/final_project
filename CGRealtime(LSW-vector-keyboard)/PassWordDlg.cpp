// PassWordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PassWordDlg.h"
#include "KeyBoardDlg.h"
#include "Public.h"

#include <iostream>
#include <afxwin.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPassWordDlg dialog


CPassWordDlg::CPassWordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPassWordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPassWordDlg)
		// NOTE: the ClassWizard will add member initialization here
	password = _T("8888");
	display  = _T("请输入密码");
	input	 = _T("");
	//}}AFX_DATA_INIT
}

void CPassWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPassWordDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_INPUT, display);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPassWordDlg, CDialog)
	//{{AFX_MSG_MAP(CPassWordDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON0, OnButton0)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON10, OnButtonClear)
	ON_WM_CLOSE()
	ON_WM_CANCELMODE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPassWordDlg message handlers

BOOL CPassWordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CFont * f; 
	f = new CFont; 
	f->CreateFont(40, // nHeight 
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
  GetDlgItem(IDC_INPUT)->SetFont(f);      //IDC_EDIT_RECEIVE是Edit框标号

  
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString temp = _T("请输入密码");

void CPassWordDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	int n = display.GetLength();
	
	if (n >= 4)					//提示信息，则先清空
	{
		display = CString("");
	}
	
	display += CString("*");	//键盘输入一位密码
	input += CString("1");
	n ++;						//长度加一

	if (n == 4)					//输入满四位，判断密码是否正确
	{
		if (input == password)
		{
			CPublic::NumFlag = FALSE;
			this->EndDialog(0);
			CKeyBoardDlg *pKeyBoardDlg = new CKeyBoardDlg;
			pKeyBoardDlg->Create(IDD_KeyBoard, this);
			pKeyBoardDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			display = CString("密码错误，请重新输入密码");
			input = CString("");
		}
	}
	
	UpdateData(FALSE);
}

void CPassWordDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	int n = display.GetLength();
	
	if (n >= 4)					//提示信息，则先清空
	{
		display = CString("");
	}
	
	display += CString("*");	//键盘输入一位密码
	input += CString("2");
	n ++;						//长度加一

	if (n == 4)					//输入满四位，判断密码是否正确
	{
		if (input == password)
		{
			CPublic::NumFlag = FALSE;
			this->EndDialog(0);
			CKeyBoardDlg *pKeyBoardDlg = new CKeyBoardDlg;
			pKeyBoardDlg->Create(IDD_KeyBoard, this);
			pKeyBoardDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			display = CString("密码错误，请重新输入密码");
			input = CString("");
		}
	}
	
	UpdateData(FALSE);
}



void CPassWordDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	int n = display.GetLength();
	
	if (n >= 4)					//提示信息，则先清空
	{
		display = CString("");
	}
	
	display += CString("*");	//键盘输入一位密码
	input += CString("3");
	n ++;						//长度加一

	if (n == 4)					//输入满四位，判断密码是否正确
	{
		if (input == password)
		{
			CPublic::NumFlag = FALSE;
			this->EndDialog(0);
			CKeyBoardDlg *pKeyBoardDlg = new CKeyBoardDlg;
			pKeyBoardDlg->Create(IDD_KeyBoard, this);
			pKeyBoardDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			display = CString("密码错误，请重新输入密码");
			input = CString("");
		}
	}
	
	UpdateData(FALSE);
}

void CPassWordDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	int n = display.GetLength();
	
	if (n >= 4)					//提示信息，则先清空
	{
		display = CString("");
	}
	
	display += CString("*");	//键盘输入一位密码
	input += CString("4");
	n ++;						//长度加一

	if (n == 4)					//输入满四位，判断密码是否正确
	{
		if (input == password)
		{
			CPublic::NumFlag = FALSE;
			this->EndDialog(0);
			CKeyBoardDlg *pKeyBoardDlg = new CKeyBoardDlg;
			pKeyBoardDlg->Create(IDD_KeyBoard, this);
			pKeyBoardDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			display = CString("密码错误，请重新输入密码");
			input = CString("");
		}
	}
	
	UpdateData(FALSE);
}

void CPassWordDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	int n = display.GetLength();
	
	if (n >= 4)					//提示信息，则先清空
	{
		display = CString("");
	}
	
	display += CString("*");	//键盘输入一位密码
	input += CString("5");
	n ++;						//长度加一

	if (n == 4)					//输入满四位，判断密码是否正确
	{
		if (input == password)
		{
			CPublic::NumFlag = FALSE;
			this->EndDialog(0);
			CKeyBoardDlg *pKeyBoardDlg = new CKeyBoardDlg;
			pKeyBoardDlg->Create(IDD_KeyBoard, this);
			pKeyBoardDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			display = CString("密码错误，请重新输入密码");
			input = CString("");
		}
	}
	
	UpdateData(FALSE);
}

void CPassWordDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	int n = display.GetLength();
	
	if (n >= 4)					//提示信息，则先清空
	{
		display = CString("");
	}
	
	display += CString("*");	//键盘输入一位密码
	input += CString("6");
	n ++;						//长度加一

	if (n == 4)					//输入满四位，判断密码是否正确
	{
		if (input == password)
		{
			CPublic::NumFlag = FALSE;
			this->EndDialog(0);
			CKeyBoardDlg *pKeyBoardDlg = new CKeyBoardDlg;
			pKeyBoardDlg->Create(IDD_KeyBoard, this);
			pKeyBoardDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			display = CString("密码错误，请重新输入密码");
			input = CString("");
		}
	}
	
	UpdateData(FALSE);
}

void CPassWordDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	int n = display.GetLength();
	
	if (n >= 4)					//提示信息，则先清空
	{
		display = CString("");
	}
	
	display += CString("*");	//键盘输入一位密码
	input += CString("7");
	n ++;						//长度加一

	if (n == 4)					//输入满四位，判断密码是否正确
	{
		if (input == password)
		{
			CPublic::NumFlag = FALSE;
			this->EndDialog(0);
			CKeyBoardDlg *pKeyBoardDlg = new CKeyBoardDlg;
			pKeyBoardDlg->Create(IDD_KeyBoard, this);
			pKeyBoardDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			display = CString("密码错误，请重新输入密码");
			input = CString("");
		}
	}
	
	UpdateData(FALSE);
}

void CPassWordDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	int n = display.GetLength();
	
	if (n >= 4)					//提示信息，则先清空
	{
		display = CString("");
	}
	
	display += CString("*");	//键盘输入一位密码
	input += CString("8");
	n ++;						//长度加一

	if (n == 4)					//输入满四位，判断密码是否正确
	{
		if (input == password)
		{	
			CPublic::NumFlag = FALSE;
			this->EndDialog(0);
			CKeyBoardDlg *pKeyBoardDlg = new CKeyBoardDlg;
			pKeyBoardDlg->Create(IDD_KeyBoard, this);
			pKeyBoardDlg->ShowWindow(SW_SHOW);
			
		}
		else
		{
			display = CString("密码错误，请重新输入密码");
			input = CString("");
		}
	}
	
	UpdateData(FALSE);
}

void CPassWordDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	int n = display.GetLength();
	
	if (n >= 4)					//提示信息，则先清空
	{
		display = CString("");
	}
	
	display += CString("*");	//键盘输入一位密码
	input += CString("9");
	n ++;						//长度加一

	if (n == 4)					//输入满四位，判断密码是否正确
	{
		if (input == password)
		{
			CPublic::NumFlag = FALSE;
			this->EndDialog(0);
			CKeyBoardDlg *pKeyBoardDlg = new CKeyBoardDlg;
			pKeyBoardDlg->Create(IDD_KeyBoard, this);
			pKeyBoardDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			display = CString("密码错误，请重新输入密码");
			input = CString("");
		}
	}
	
	UpdateData(FALSE);
}

void CPassWordDlg::OnButton0() 
{
	// TODO: Add your control notification handler code here
	int n = display.GetLength();
	
	if (n >= 4)					//提示信息，则先清空
	{
		display = CString("");
	}
	
	display += CString("*");	//键盘输入一位密码
	input += CString("0");
	n ++;						//长度加一

	if (n == 4)					//输入满四位，判断密码是否正确
	{
		if (input == password)
		{
			CPublic::NumFlag = FALSE;
			this->EndDialog(0);
			CKeyBoardDlg *pKeyBoardDlg = new CKeyBoardDlg;
			pKeyBoardDlg->Create(IDD_KeyBoard, this);
			pKeyBoardDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			display = CString("密码错误，请重新输入密码");
			input = CString("");
		}
	}
	
	UpdateData(FALSE);
}

void CPassWordDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	int n = input.GetLength();
	input = input.Left(n-1);
	display = display.Left(n-1);
	UpdateData(FALSE);
}

void CPassWordDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	input = CString("");
	display = CString("请输入密码");
	
	GetDlgItem(IDC_BUTTON0)->GetWindowRect(&CPublic::rectNum[0]);
	GetDlgItem(IDC_BUTTON1)->GetWindowRect(&CPublic::rectNum[1]);
	GetDlgItem(IDC_BUTTON2)->GetWindowRect(&CPublic::rectNum[2]);
	GetDlgItem(IDC_BUTTON3)->GetWindowRect(&CPublic::rectNum[3]);
	GetDlgItem(IDC_BUTTON4)->GetWindowRect(&CPublic::rectNum[4]);
	GetDlgItem(IDC_BUTTON5)->GetWindowRect(&CPublic::rectNum[5]);
	GetDlgItem(IDC_BUTTON6)->GetWindowRect(&CPublic::rectNum[6]);
	GetDlgItem(IDC_BUTTON7)->GetWindowRect(&CPublic::rectNum[7]);
	GetDlgItem(IDC_BUTTON8)->GetWindowRect(&CPublic::rectNum[8]);
	GetDlgItem(IDC_BUTTON9)->GetWindowRect(&CPublic::rectNum[9]);
	GetDlgItem(IDC_BUTTON10)->GetWindowRect(&CPublic::rectNum[10]);
	GetDlgItem(IDC_BUTTON_DELETE)->GetWindowRect(&CPublic::rectNum[11]);
	CPublic::NumFlag = TRUE;

	UpdateData(FALSE);
}

void CPassWordDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CPublic::NumFlag = FALSE;
	CDialog::OnClose();
}
