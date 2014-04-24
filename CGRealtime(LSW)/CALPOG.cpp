// CALPOG.cpp : implementation file
//

#include "stdafx.h"
//#include "CGSnapEx.h"
#include "CALPOG.h"
#include "Public.h"
#include "CGRealtime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCALPOG dialog


CCALPOG::CCALPOG(CWnd* pParent /*=NULL*/)
	: CDialog(CCALPOG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCALPOG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCALPOG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCALPOG)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCALPOG, CDialog)
	//{{AFX_MSG_MAP(CCALPOG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCALPOG message handlers




