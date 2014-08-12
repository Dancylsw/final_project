#if !defined(AFX_CALPOG_H__12F8A9B6_8FB6_4843_87D1_C6CEA0E7F442__INCLUDED_)
#define AFX_CALPOG_H__12F8A9B6_8FB6_4843_87D1_C6CEA0E7F442__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CALPOG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCALPOG dialog

class CCALPOG : public CDialog
{
// Construction
public:
	CCALPOG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCALPOG)
	enum { IDD = IDD_CALPOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCALPOG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCALPOG)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALPOG_H__12F8A9B6_8FB6_4843_87D1_C6CEA0E7F442__INCLUDED_)
