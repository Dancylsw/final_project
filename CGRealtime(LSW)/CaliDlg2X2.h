#if !defined(AFX_CALIDLG2X2_H__312B1E30_F1DB_4D93_A2BF_994364C5F712__INCLUDED_)
#define AFX_CALIDLG2X2_H__312B1E30_F1DB_4D93_A2BF_994364C5F712__INCLUDED_

#include "Point.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CaliDlg2X2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCaliDlg2X2 dialog

class CCaliDlg2X2 : public CDialog
{
// Construction
public:
//	Point m_caliPoint;
//	int m_statetag;
	CCaliDlg2X2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCaliDlg2X2)
	enum { IDD = IDD_CAL2X2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaliDlg2X2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCaliDlg2X2)
	afx_msg void OnBt2x21();
	afx_msg void OnBt2x22();
	afx_msg void OnBt2x23();
	afx_msg void OnBt2x24();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALIDLG2X2_H__312B1E30_F1DB_4D93_A2BF_994364C5F712__INCLUDED_)
