#if !defined(AFX_PASSWORDDLG_H__F53E8F4F_D73D_4622_B2CC_1B973FFB4414__INCLUDED_)
#define AFX_PASSWORDDLG_H__F53E8F4F_D73D_4622_B2CC_1B973FFB4414__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PassWordDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPassWordDlg dialog

#include "resource.h"

class CPassWordDlg : public CDialog
{
// Construction
public:
	CPassWordDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPassWordDlg)
	enum { IDD = IDD_PassWord };
	CString display;
	CString input;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPassWordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CPassWordDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton0();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonClear();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString password;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSWORDDLG_H__F53E8F4F_D73D_4622_B2CC_1B973FFB4414__INCLUDED_)
