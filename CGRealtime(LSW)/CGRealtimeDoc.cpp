// CGRealtimeDoc.cpp : implementation of the CCGRealtimeDoc class
//

#include "stdafx.h"
#include "CGRealtime.h"

#include "CGRealtimeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGRealtimeDoc

IMPLEMENT_DYNCREATE(CCGRealtimeDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGRealtimeDoc, CDocument)
	//{{AFX_MSG_MAP(CCGRealtimeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGRealtimeDoc construction/destruction

CCGRealtimeDoc::CCGRealtimeDoc()
{
	// TODO: add one-time construction code here

}

CCGRealtimeDoc::~CCGRealtimeDoc()
{
}

BOOL CCGRealtimeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCGRealtimeDoc serialization

void CCGRealtimeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCGRealtimeDoc diagnostics

#ifdef _DEBUG
void CCGRealtimeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCGRealtimeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGRealtimeDoc commands
