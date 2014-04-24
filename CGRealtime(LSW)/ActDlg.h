#if !defined(AFX_ACTDLG_H__2EEE4F50_7D85_41A2_AFCA_BF20C9A2F757__INCLUDED_)
#define AFX_ACTDLG_H__2EEE4F50_7D85_41A2_AFCA_BF20C9A2F757__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ActDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CActDlg dialog

class CActDlg : public CDialog
{
// Construction
public:
	CActDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CActDlg)
	enum { IDD = IDD_ACT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CActDlg)
	afx_msg void OnAcbt1();
	afx_msg void OnActdone();
	afx_msg void OnAcbt2();
	afx_msg void OnAcbt3();
	afx_msg void OnAcbt4();
	afx_msg void OnAcbt5();
	afx_msg void OnAcbt6();
	afx_msg void OnAcbt7();
	afx_msg void OnAcbt8();
	afx_msg void OnAcbt9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTDLG_H__2EEE4F50_7D85_41A2_AFCA_BF20C9A2F757__INCLUDED_)
