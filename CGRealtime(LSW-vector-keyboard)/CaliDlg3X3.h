#if !defined(AFX_CALIDLG3X3_H__92186A05_63DE_4311_A47A_DA750016A28A__INCLUDED_)
#define AFX_CALIDLG3X3_H__92186A05_63DE_4311_A47A_DA750016A28A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CaliDlg3X3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCaliDlg3X3 dialog
#include "Point.h"

class CCaliDlg3X3 : public CDialog
{
// Construction
public:
	CCaliDlg3X3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCaliDlg3X3)
	enum { IDD = IDD_CAL3X3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaliDlg3X3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCaliDlg3X3)
	afx_msg void OnBt3x31();
	afx_msg void OnBt3x32();
	afx_msg void OnBt3x33();
	afx_msg void OnBt3x34();
	afx_msg void OnBt3x35();
	afx_msg void OnBt3x36();
	afx_msg void OnBt3x37();
	afx_msg void OnBt3x38();
	afx_msg void OnBt3x39();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALIDLG3X3_H__92186A05_63DE_4311_A47A_DA750016A28A__INCLUDED_)
