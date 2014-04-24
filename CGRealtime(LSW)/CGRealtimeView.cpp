// CGRealtimeView.cpp : implementation of the CCGRealtimeView class
//

#include "stdafx.h"
#include "CGRealtime.h"

#include "CGRealtimeDoc.h"
#include "CGRealtimeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGRealtimeView

IMPLEMENT_DYNCREATE(CCGRealtimeView, CView)

BEGIN_MESSAGE_MAP(CCGRealtimeView, CView)
	//{{AFX_MSG_MAP(CCGRealtimeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGRealtimeView construction/destruction

CCGRealtimeView::CCGRealtimeView()
{
	// TODO: add construction code here

}

CCGRealtimeView::~CCGRealtimeView()
{
}

BOOL CCGRealtimeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCGRealtimeView drawing

void CCGRealtimeView::OnDraw(CDC* pDC)
{
	CCGRealtimeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCGRealtimeView printing

BOOL CCGRealtimeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCGRealtimeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCGRealtimeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCGRealtimeView diagnostics

#ifdef _DEBUG
void CCGRealtimeView::AssertValid() const
{
	CView::AssertValid();
}

void CCGRealtimeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGRealtimeDoc* CCGRealtimeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGRealtimeDoc)));
	return (CCGRealtimeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGRealtimeView message handlers

