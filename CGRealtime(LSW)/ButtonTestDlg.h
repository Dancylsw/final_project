#if !defined(AFX_BUTTONTESTDLG_H__DFA69060_5FF7_417A_9BC4_C00C9115E015__INCLUDED_)
#define AFX_BUTTONTESTDLG_H__DFA69060_5FF7_417A_9BC4_C00C9115E015__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonTestDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButtonTestDlg dialog
#include "EasySize.h"
class CButtonTestDlg : public CDialog
{
	DECLARE_EASYSIZE
// Construction
public:
	CButtonTestDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CButtonTestDlg)
	enum { IDD = IDD_BTTEST };
	CString	m_input;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;


	// Generated message map functions
	//{{AFX_MSG(CButtonTestDlg)
	afx_msg void OnBtstAbc();
	afx_msg void OnBtstDef();
	afx_msg void OnBtstGhi();
	afx_msg void OnBtstJkl();
	afx_msg void OnBtstMno();
	afx_msg void OnBtstPqrs();
	afx_msg void OnBtstTuv();
	afx_msg void OnBtstWxyz();
	afx_msg void OnBttestA();
	afx_msg void OnBttestB();
	afx_msg void OnBttestC();
	afx_msg void OnBttestD();
	afx_msg void OnBttestE();
	afx_msg void OnBttestF();
	afx_msg void OnBttestG();
	afx_msg void OnBttestH();
	afx_msg void OnBttestI();
	afx_msg void OnBttestJ();
	afx_msg void OnBttestK();
	afx_msg void OnBttestL();
	afx_msg void OnBttestM();
	afx_msg void OnBttestN();
	afx_msg void OnBttestO();
	afx_msg void OnBttestT();
	afx_msg void OnBttestU();
	afx_msg void OnBttestV();
	afx_msg void OnBtstW();
	afx_msg void OnBtstX();
	afx_msg void OnBtstY();
	afx_msg void OnBtstZ();
	afx_msg void OnBtstBackspace();
	afx_msg void OnBtstClear();
	afx_msg void OnBtstInback();
	afx_msg void OnBtstSpace();
	afx_msg void OnBttestBack();
	afx_msg void OnBtstP();
	afx_msg void OnBtstQ();
	afx_msg void OnBtstR();
	afx_msg void OnBtstS();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONTESTDLG_H__DFA69060_5FF7_417A_9BC4_C00C9115E015__INCLUDED_)
