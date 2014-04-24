#if !defined(AFX_TSTPOG_H__8BB7BBD9_3A9F_4B12_B761_691B98310924__INCLUDED_)
#define AFX_TSTPOG_H__8BB7BBD9_3A9F_4B12_B761_691B98310924__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TSTPOG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTSTPOG dialog

class CTSTPOG : public CDialog
{
// Construction
public:
	int flag;
	CTSTPOG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTSTPOG)
	enum { IDD = IDD_TSTPOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTSTPOG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTSTPOG)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TSTPOG_H__8BB7BBD9_3A9F_4B12_B761_691B98310924__INCLUDED_)
