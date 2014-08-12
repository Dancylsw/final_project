#if !defined(AFX_CALIDLG5X5_H__FC42F138_CA41_4B4F_A052_A79A250B2141__INCLUDED_)
#define AFX_CALIDLG5X5_H__FC42F138_CA41_4B4F_A052_A79A250B2141__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CaliDlg5X5.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCaliDlg5X5 dialog
#include "Point.h"
#include "resource.h"
class CCaliDlg5X5 : public CDialog
{
// Construction
public:
	CCaliDlg5X5(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCaliDlg5X5)
	enum { IDD = IDD_CAL5X5 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaliDlg5X5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCaliDlg5X5)
	afx_msg void OnBt5x51();
	afx_msg void OnBt5x52();
	afx_msg void OnBt5x53();
	afx_msg void OnBt5x54();
	afx_msg void OnBt5x55();
	afx_msg void OnBt5x56();
	afx_msg void OnBt5x57();
	afx_msg void OnBt5x58();
	afx_msg void OnBt5x59();
	afx_msg void OnBt5x510();
	afx_msg void OnBt5x511();
	afx_msg void OnBt5x512();
	afx_msg void OnBt5x513();
	afx_msg void OnBt5x514();
	afx_msg void OnBt5x515();
	afx_msg void OnBt5x516();
	afx_msg void OnBt5x517();
	afx_msg void OnBt5x518();
	afx_msg void OnBt5x519();
	afx_msg void OnBt5x520();
	afx_msg void OnBt5x521();
	afx_msg void OnBt5x522();
	afx_msg void OnBt5x523();
	afx_msg void OnBt5x524();
	afx_msg void OnBt5x525();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALIDLG5X5_H__FC42F138_CA41_4B4F_A052_A79A250B2141__INCLUDED_)
