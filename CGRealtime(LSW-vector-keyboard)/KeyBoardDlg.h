#if !defined(AFX_KEYBOARDDLG_H__8E89068A_258B_44D7_906D_C8F6DD7124C1__INCLUDED_)
#define AFX_KEYBOARDDLG_H__8E89068A_258B_44D7_906D_C8F6DD7124C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KeyBoardDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKeyBoardDlg dialog

#include "resource.h"

class CKeyBoardDlg : public CDialog
{
// Construction
public:
	CKeyBoardDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKeyBoardDlg)
	enum { IDD = IDD_KeyBoard };
	CString m_input;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyBoardDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	HICON m_hicon;
	// Generated message map functions
	//{{AFX_MSG(CKeyBoardDlg)
	afx_msg void OnKeyQ();
	afx_msg void OnKeyA();
	afx_msg void OnKeyE();
	afx_msg void OnKeyR();
	afx_msg void OnKeyT();
	afx_msg void OnKeyY();
	afx_msg void OnKeyU();
	afx_msg void OnKeyI();
	afx_msg void OnKeyO();
	afx_msg void OnKeyP();
	afx_msg void OnKeyW();
	afx_msg void OnKeyS();
	afx_msg void OnKeyD();
	afx_msg void OnKeyF();
	afx_msg void OnKeyG();
	afx_msg void OnKeyH();
	afx_msg void OnKeyJ();
	afx_msg void OnKeyK();
	afx_msg void OnKeyL();
	afx_msg void OnKeyZ();
	afx_msg void OnKeyX();
	afx_msg void OnKeyC();
	afx_msg void OnKeyV();
	afx_msg void OnKeyB();
	afx_msg void OnKeyN();
	afx_msg void OnKeyM();
	afx_msg void OnKeyClear();
	afx_msg void OnKeyBackspace();
	afx_msg void OnKeySpace();
	virtual BOOL OnInitDialog();
	afx_msg void OnKeyLock();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYBOARDDLG_H__8E89068A_258B_44D7_906D_C8F6DD7124C1__INCLUDED_)
