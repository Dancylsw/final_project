#if !defined(AFX_CALIDLG4X4_H__2F4C64CF_7284_426F_A596_A16373C070FA__INCLUDED_)
#define AFX_CALIDLG4X4_H__2F4C64CF_7284_426F_A596_A16373C070FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CaliDlg4X4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCaliDlg4X4 dialog
#include "resource.h"
#include "Point.h"

class CCaliDlg4X4 : public CDialog
{
// Construction
public:
	CCaliDlg4X4(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCaliDlg4X4)
	enum { IDD = IDD_CAL4X4 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaliDlg4X4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCaliDlg4X4)
	afx_msg void OnBt4x41();
	afx_msg void OnBt4x42();
	afx_msg void OnBt4x43();
	afx_msg void OnBt4x44();
	afx_msg void OnBt4x45();
	afx_msg void OnBt4x46();
	afx_msg void OnBt4x47();
	afx_msg void OnBt4x48();
	afx_msg void OnBt4x49();
	afx_msg void OnBt4x410();
	afx_msg void OnBt4x411();
	afx_msg void OnBt4x412();
	afx_msg void OnBt4x413();
	afx_msg void OnBt4x414();
	afx_msg void OnBt4x415();
	afx_msg void OnBt4x416();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALIDLG4X4_H__2F4C64CF_7284_426F_A596_A16373C070FA__INCLUDED_)
