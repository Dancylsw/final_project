// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CGRealtime.h"
#include "MainFrm.h"
#include "CGVidEx.h"
#include "CaliDlg2X2.h"
#include "CaliDlg3X3.h"
#include "CaliDlg4X4.h"
#include "CaliDlg5X5.h"
#include "CaliDlg6X6.h"
#include "ButtonTestDlg.h"
#include "ActDlg.h"
#include "Public.h"
#include "KeyBoardDlg.h"
#include "PassWordDlg.h"
#include "Point.h"

#include "cv.h"
#include "highgui.h"
#include "cxcore.h"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;


//#pragma comment(lib, "CGVidEx.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_SNAPEX_OPEN, OnSnapexOpen)
	ON_UPDATE_COMMAND_UI(ID_SNAPEX_OPEN, OnUpdateSnapexOpen)
	ON_COMMAND(ID_SNAPEX_START, OnSnapexStart)
	ON_UPDATE_COMMAND_UI(ID_SNAPEX_START, OnUpdateSnapexStart)
	ON_COMMAND(ID_SNAPEX_STOP, OnSnapexStop)
	ON_UPDATE_COMMAND_UI(ID_SNAPEX_STOP, OnUpdateSnapexStop)
	ON_COMMAND(ID_SNAPEX_CLOSE, OnSnapexClose)
	ON_UPDATE_COMMAND_UI(ID_SNAPEX_CLOSE, OnUpdateSnapexClose)
	ON_MESSAGE(WM_SNAP_EX_CHANGE, OnSnapExChange)
	ON_WM_CLOSE()
	ON_COMMAND(ID_NEGATIVE, OnNegative)
	ON_UPDATE_COMMAND_UI(ID_NEGATIVE, OnUpdateNegative)
	ON_COMMAND(ID_HKSTOP, OnHkstop)
	ON_COMMAND(ID_BTMAPPING, OnBtmapping)
	ON_COMMAND(ID_BTCALIB, OnBtcalib)
	ON_COMMAND(IDM_ACCUTEST, OnAccutest)
	ON_COMMAND(ID_CALIB3X3, OnCalib3x3)
	ON_COMMAND(ID_BTCALIB4X4, OnBtcalib4x4)
	ON_COMMAND(ID_BTCALIB5X5, OnBtcalib5x5)
	ON_COMMAND(ID_BTCALIB6X6, OnBtcalib6x6)
	ON_COMMAND(IDM_BTEST, OnBtest)
	ON_COMMAND(IDM_GRIDTEST_2X2, OnGridtest2x2)
	ON_COMMAND(IDM_GRIDTEST_3X3, OnGridtest3x3)
	ON_COMMAND(IDM_GRIDTEST_4X4, OnGridtest4x4)
	ON_COMMAND(IDM_GRIDTEST_5X5, OnGridtest5x5)
	ON_COMMAND(IDM_GRIDTEST_6X6, OnGridtest6x6)
	ON_COMMAND(IDM_KEYBOARD, OnKeyboard)
	ON_COMMAND(ID_LSW, MyParameter)
	ON_WM_ACTIVATE()
	ON_COMMAND(ID_FACEDETECT, OnFacedetect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

	/*
	 *	��ʼ�����г�Ա������ͬʱ��ͼ��
	 */
	CGSTATUS status = CG_OK;
	
	m_bOpen			= FALSE;
	m_bStart		= FALSE;

	m_bNegative		= TRUE;

	m_pBmpInfo		= NULL;
	m_pImageBuffer	= NULL;

	//	��ͼ�� 1
	status = BeginCGCard(1, &m_hcg);
	
	//	���麯��ִ��״̬�����ʧ�ܣ��򷵻ش���״̬��Ϣ��
	CG_VERIFY(status);

	//���ó�ʼalphaֵΪ2.0
	m_bestAlph = 2;

	//���ó�ʼλ��ʸ��Ϊ(0,0)
	m_bestVector.setX(0);
	m_bestVector.setY(0);

	m_caliPoint.setX(640);
	m_caliPoint.setY(512);
//	fperror=fopen("error.txt","w");
}

CMainFrame::~CMainFrame()
{
	CGSTATUS status = CG_OK;
	
	//	�ر�ͼ�񿨣��ͷ�ͼ���ڲ���Դ
	status = EndCGCard(m_hcg);
	CG_VERIFY(status);

	//	����ͼ�񻺳���
	if (m_pImageBuffer) {
		delete []m_pImageBuffer;
		m_pImageBuffer= NULL;
	}

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}



	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	/*
	 *	��ʼ��ͼ��Ӳ��״̬���û�Ҳ����������λ�ó�ʼ��ͼ�񿨣�
	 *	��Ӧ��֤ͼ���Ѿ��򿪣������û���Ӧ�ó����ʼ��ʱ��
	 *	ͬʱ��ʼ��ͼ��Ӳ����
	 */

	//������Ƶ��ʽ(PAL / NTSC)���ɵ�ǰ��ƵԴ��ʽ����
	CGSetVideoStandard(m_hcg, PAL);		
	
	/*
	 *	��Ƶ��ʽ�����ɼ�ͼ������������ʽ��	
	 *	����YUV422��RGB888��RGB565��RGB555��RGB8888��ALL8BIT��LIMITED8BIT��
	 *  �ڲɼ�ͼ����Ļʱ����Ҫ��֤��Ƶ��ʽ�͵�ǰϵͳ��Ļλ���һ�£����ɼ����ڴ�û�д����ơ�
	 */
	CGSetVideoFormat(m_hcg, RGB888);	

	//ɨ��ģʽ������ FRAME��FIELD
	CGSetScanMode(m_hcg, FRAME);

	/*
	 *	���񣬰���CRY_OSC_35M��CRY_OSC_28M	
	 *	����DH-CG300ͼ�񿨣�һ��ΪCRY_OSC_35M������DH-QP300ͼ�񿨣�һ��ΪCRY_OSC_28M��
	 *	��������ͼ��û�д�Ӳ�����ã������Ե��ô˽ӿڣ�������CG_NOT_SUPPORT_INTERFACE��Ϣ
	 */
	CGSelectCryOSC(m_hcg, CRY_OSC_35M);
	
	/*
	 *	������ƵԴ·��
	 *  ��ƵԴ·VIDEO_SOURCE������Ƶ���ͺ���ţ�
	 *	����ͼ��֧�ֵ���ƵԴ·������ͬ����ο���ӦӲ��˵��
	 */
	VIDEO_SOURCE source;
	source.type		= COMPOSITE_VIDEO;
	source.nIndex	= 0;
	CGSetVideoSource(m_hcg, source);

	/*
	 *	��Ƶ���봰�ڣ�����Ƶ���뷶Χ�����봰��ȡֵ��Χ��
	 *	������Ƶ��ʽΪPAL�ƣ�ˮƽ����Ϊ0-768����ֱ����Ϊ0-576 
	 *	������Ƶ��ʽΪNTSC�ƣ�ˮƽ����Ϊ0-768����ֱ����Ϊ0-576 
	 *  ��Ƶ�������Ͻ�X����ʹ��ڿ��ӦΪ4�ı��������Ͻ�Y����ʹ��ڸ߶�ӦΪ2�ı���
	 */
	CGSetInputWindow(m_hcg, 0, 0, 768, 576);
	
	/*
	 *	��Ƶ������ڣ�����Ƶ�����Χ���������ȡֵ��Χ���������봰�ڷ�Χ���ڣ�
	 *  ��Ƶ�������Ͻ�X����ʹ��ڿ��ӦΪ4�ı��������Ͻ�Y����ʹ��ڸ߶�ӦΪ2�ı���
	 *	�ڲɼ�����Ļʱ��������ڵ���ʼλ��Ϊͼ����Ļ���λ�õ���Ļ���꣬
	 *	�ڲɼ����ڴ�ʱ��������ڵ���ʼλ������Ϊ(0, 0)���ɡ�
	 */
	CGSetOutputWindow(m_hcg, 0, 0, 768, 576);

	/*
	 *	m_pBmpInfo��ָ��m_chBmpBuf���������û������Լ�����BTIMAPINFO������	
	 */
	m_pBmpInfo								= (BITMAPINFO *)m_chBmpBuf;
	
	/*
	 *	��ʼ��BITMAPINFO �ṹ���˽ṹ�ڱ���bmp�ļ�����ʾ�ɼ�ͼ��ʱʹ��
	 */
	m_pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);

	//	ͼ���ȣ�һ��Ϊ������ڿ��
	m_pBmpInfo->bmiHeader.biWidth			= 768;		
	
	/*
	 *	ͼ��߶ȣ�����ɨ��ģʽ(FRAME/FIELD)�Ĳ�ͬ	
	 *	FRAME���£�һ��Ϊ������ڸ߶�
	 *	FIELD���£�һ��Ϊ������ڸ߶ȵ�һ��
	 */
	m_pBmpInfo->bmiHeader.biHeight			= 576;		

	/*
	 *	ͼ��λ��ȣ�����Ƶ��ʽȷ����
	 *	�ɼ�ͼ����Ƶ��ʽ��RGB565��RGB555��RGB888��ALL8BIT�ȣ�
	 *  ���ʹ��CGDateTransfrom��������15��16λ����ת��Ϊ24λ
	 */
	m_pBmpInfo->bmiHeader.biBitCount		= 24;
	
	/*
	 *	��������һ����ͬ��
	 *	���ڵ���8λ��λͼ����Ӧ������Ӧ��λͼ��ɫ��
	 */
	m_pBmpInfo->bmiHeader.biPlanes			= 1;	
	m_pBmpInfo->bmiHeader.biCompression		= BI_RGB;
	m_pBmpInfo->bmiHeader.biSizeImage		= 0;
	m_pBmpInfo->bmiHeader.biXPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biYPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biClrUsed			= 0;
	m_pBmpInfo->bmiHeader.biClrImportant	= 0;
	
	m_pImageBuffer = new BYTE[768 * 576 * 3];
	if (m_pImageBuffer) {
		FillMemory(m_pImageBuffer, 768 * 576 * 3, 0xff);
	}

	/*
	 *	����ͼ�񻺳�����һ�������洢�ɼ�ͼ��
	 *	�û����Խ��豸��̬�ڴ��ͼ������ֱ��ͨ��ָ���
	 *	��CGDataTransfrom����������ͼ�񻺳���,Ȼ������һ���Ĵ���
	 *	һ��ͼ�񻺳�����С��������ڴ�С����Ƶ��ʽȷ����
	 */
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.cx = 768;
	cs.cy = 572;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

/*
 *	��ӦCardCtrl�����˵��е�Open��ť
 *	��ʼ��ͼ�񿨲ɼ�ͼ���ڴ�Ŀ��ƣ�
 *	ָ���ص�����SnapThreadCallbackEx���û�����m_hWnd
 */
void CMainFrame::OnSnapexOpen() 
{
	// TODO: Add your command handler code here
	CGSTATUS status = CG_OK;

	//cout<<"open"<<endl;
	status = CGOpenSnapEx(m_hcg, SnapThreadCallbackEx, m_hWnd);					
	CG_VERIFY(status);
	if (CG_SUCCESS(status)) {
		m_bOpen = TRUE;			//��־�Ѿ���SnapEx����
	}
}



void CMainFrame::OnUpdateSnapexOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bOpen);
	pCmdUI->SetCheck(m_bOpen);
}


/*
 *	��ӦCardCtrl�����˵��е�Start��ť
 *	����ͼ�񿨲ɼ�ͼ���ڴ�
 *	ָ��ͼ�񿨽�ͼ��ɼ�����̬�ڴ�ƫ��Ϊ0��λ�ã�
 *	�ɼ���������СΪ2��ͼ���С
 */
void CMainFrame::OnSnapexStart() 
{
	// TODO: Add your command handler code here
	CGSTATUS status = CG_OK;

	status = CGStartSnapEx(m_hcg, 0, TRUE, 2);
	CG_VERIFY(status);
	if (CG_SUCCESS(status)) {
		m_bStart = TRUE;
	}
}



void CMainFrame::OnUpdateSnapexStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( (!m_bStart) && (m_bOpen));
	pCmdUI->SetCheck(m_bStart);
}

/*
 *	��ӦCardCtrl�����˵��е�Stop��ť
 *	ֹͣ�ɼ�ͼ���ڴ棬�����ٴε���CGStartSnapEx����ͼ�񿨲ɼ�
 */
void CMainFrame::OnSnapexStop() 
{
	// TODO: Add your command handler code here
	CGSTATUS status =CG_OK;

	status = CGStopSnapEx(m_hcg);
	CG_VERIFY(status);
	if (CG_SUCCESS(status)) {
		m_bStart = FALSE;
	}
}



void CMainFrame::OnUpdateSnapexStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_bStart);
}


/*
 *	��ӦCardCtrl�����˵��е�Close��ť
 *	��ֹͼ�񿨲ɼ�ͼ���ڴ棬ͬʱ�ͷ����вɼ�������
 *	�ٴ�����ͼ�񿨲ɼ����������³�ʼ��	
 */
void CMainFrame::OnSnapexClose() 
{
	// TODO: Add your command handler code here
	CGSTATUS status = CG_OK;

	status = CGCloseSnapEx(m_hcg);
	CG_VERIFY(status);

	if (CG_SUCCESS(status)) {
		m_bOpen		= FALSE;
		m_bStart	= FALSE;
	}
}




void CMainFrame::OnUpdateSnapexClose(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_bOpen);
}



/*
	����:
		SnapThreadCallbackEx
	�������:
		SNAP_INFO *pInfo		SNAP_INFO�ṹ������ǰͼ��SNAPִ��״̬
	�������:
		int						
	˵��:
		ͼ�񿨲ɼ����ڴ�ص����������û�һ�㲻�õ��ã����û��ṩ��SDKʹ�ã�
		�û��ڻص�������ʵ�ֶԲɼ����ݵĴ������ʾ����
 */
int CALLBACK CMainFrame::SnapThreadCallbackEx(SNAP_INFO *pInfo)
{
	HWND hwnd = (HWND)(pInfo->pParam);
	
	/*
	 *	�����Զ�����ϢWM_SNAP_EX_CHANGE�������ڣ�	
	 *	ͬʱ���뵱ǰ���Դ����ͼ�����
	 *	ע�⣺��SendMessage������Ϣ������ȴ���Ϣ������Ϻ󣬲����˳�����SendMessage����
	 */
	::SendMessage(hwnd, WM_SNAP_EX_CHANGE, pInfo->nNumber, 0);

	return 1;
}

/*************************************************************************
*
*	����:�����ҵ��ĵ��ò�ͬ����ɫ
*
**************************************************************************/
void draw3(BYTE* data ,int x,int y ,int i)
{
	int zz;
	if(i==0)
	{
		for(zz=x-2;zz<x+3;zz++)
		{

			*(data+zz*768*3+y*3)=255;
			*(data+zz*768*3+y*3+1)=255;
			*(data+zz*768*3+y*3+2)=255;
		}
		for(zz=y-2;zz<y+3;zz++)
		{
			*(data+x*768*3+zz*3)=255;
			*(data+x*768*3+zz*3+1)=255;
			*(data+x*768*3+zz*3+2)=255;
		}
	}
	else if(i==1)
	{
		for(zz=x-2;zz<x+3;zz++)
		{
			*(data+zz*768*3+y*3)=255;
			*(data+zz*768*3+y*3+1)=255;
			*(data+zz*768*3+y*3+2)=255;
		}
		for(zz=y-2;zz<y+3;zz++)
		{
			*(data+x*768*3+zz*3)=255;
			*(data+x*768*3+zz*3+1)=255;
			*(data+x*768*3+zz*3+2)=255;
		}
	}
	else if(i==2)
	{
		for(zz=x-2;zz<x+3;zz++)
		{
			*(data+zz*768*3+y*3)=255;
			*(data+zz*768*3+y*3+1)=255;
			*(data+zz*768*3+y*3+2)=255;
		}
		for(zz=y-2;zz<y+3;zz++)
		{
			*(data+x*768*3+zz*3)=255;
			*(data+x*768*3+zz*3+1)=255;
			*(data+x*768*3+zz*3+2)=255;
		}
	}
	else if(i==3)
	{
		for(zz=x-2;zz<x+3;zz++)
		{
			*(data+zz*768*3+y*3)=255;
			*(data+zz*768*3+y*3+1)=255;
			*(data+zz*768*3+y*3+2)=255;
		}
		for(zz=y-2;zz<y+3;zz++)
		{
			*(data+x*768*3+zz*3)=255;
			*(data+x*768*3+zz*3+1)=255;
			*(data+x*768*3+zz*3+2)=255;
		}
	}
	else if(i==4) {
		for(zz=x-2;zz<x+3;zz++)
		{
			*(data+zz*768*3+y*3)=200;
			*(data+zz*768*3+y*3+1)=200;
			*(data+zz*768*3+y*3+2)=100;
		}
		for(zz=y-2;zz<y+3;zz++)
		{
			*(data+x*768*3+zz*3)=200;
			*(data+x*768*3+zz*3+1)=200;
			*(data+x*768*3+zz*3+2)=100;
		}
	}
	else{
		for(zz=x-2;zz<x+3;zz++)
		{
			*(data+zz*768*3+y*3)=0;
			*(data+zz*768*3+y*3+1)=0;
			*(data+zz*768*3+y*3+2)=255;
		}
		for(zz=y-2;zz<y+3;zz++)
		{
			*(data+x*768*3+zz*3)=0;
			*(data+x*768*3+zz*3+1)=0;
			*(data+x*768*3+zz*3+2)=255;
		}
	}
}

/*
 * ������ͫ������Ϊ���ĵ�ľ���Ŀ������
 */
void drawrect(BYTE* data, int x, int y)
{
	int i;
	for (i = x-40; i <= x-30; i ++)
	{
		*(data+i*768*3+(y+40)*3)=0;
		*(data+i*768*3+(y+40)*3+1)=0;
		*(data+i*768*3+(y+40)*3+2)=255;
	}
	for (i = y+30; i <= y+40; i ++)
	{
		*(data+(x-40)*768*3+i*3)=0;
		*(data+(x-40)*768*3+i*3+1)=0;
		*(data+(x-40)*768*3+i*3+2)=255;
	}

	for (i = x+30; i <= x+40; i ++)
	{
		*(data+i*768*3+(y+40)*3)=0;
		*(data+i*768*3+(y+40)*3+1)=0;
		*(data+i*768*3+(y+40)*3+2)=255;
	}
	for (i = y+30; i <= y+40; i ++)
	{
		*(data+(x+40)*768*3+i*3)=0;
		*(data+(x+40)*768*3+i*3+1)=0;
		*(data+(x+40)*768*3+i*3+2)=255;
	}

	for (i = x-40; i <= x-30; i ++)
	{
		*(data+i*768*3+(y-40)*3)=0;
		*(data+i*768*3+(y-40)*3+1)=0;
		*(data+i*768*3+(y-40)*3+2)=255;
	}
	for (i = y-40; i <= y-30; i ++)
	{
		*(data+(x-40)*768*3+i*3)=0;
		*(data+(x-40)*768*3+i*3+1)=0;
		*(data+(x-40)*768*3+i*3+2)=255;
	}

	for (i = x+30; i <= x+40; i ++)
	{
		*(data+i*768*3+(y-40)*3)=0;
		*(data+i*768*3+(y-40)*3+1)=0;
		*(data+i*768*3+(y-40)*3+2)=255;
	}
	for (i = y-40; i <= y-30; i ++)
	{
		*(data+(x+40)*768*3+i*3)=0;
		*(data+(x+40)*768*3+i*3+1)=0;
		*(data+(x+40)*768*3+i*3+2)=255;
	}

	for (i = x+30; i <= x+45; i ++)
	{
		*(data+i*768*3+y*3)=0;
		*(data+i*768*3+y*3+1)=0;
		*(data+i*768*3+y*3+2)=255;
	}
	for (i = x-45; i <= x-30; i ++)
	{
		*(data+i*768*3+y*3)=0;
		*(data+i*768*3+y*3+1)=0;
		*(data+i*768*3+y*3+2)=255;
	}
	for (i = y-45; i <= y-30; i ++)
	{
		*(data+x*768*3+i*3)=0;
		*(data+x*768*3+i*3+1)=0;
		*(data+x*768*3+i*3+2)=255;
	}
	for (i = y+30; i <= y+45; i ++)
	{
		*(data+x*768*3+i*3)=0;
		*(data+x*768*3+i*3+1)=0;
		*(data+x*768*3+i*3+2)=255;
	}
}

const char* cascade_name ="haarcascade_frontalface_alt.xml";//������������

/**
 * @author		lsw_sky@outlook.com
 * @date		2014.08.22
 * @brief		�Դ����BYTE��ʽ��ͼ�����������Ⲣ��ʾ����
 * @param[in]	BYTE* m_pData	�����ͼ��
 * @param[in]	int width		�����ͼ��Ŀ�
 * @param[in]	int height		�����ͼ��ĸ�
 * @return		void
 **/
void CMainFrame::detect_and_draw(BYTE* m_pData, int width, int height)				
{
	//��m_pData�������·�ת
	BYTE* tempData;
	tempData = (BYTE*) malloc (width * height * 3 * sizeof(BYTE));
	memset(tempData, 0, width*height*3*sizeof(BYTE));

	int i, j;
	for (i = 0; i < height; i ++)
	{
		for (j = 0; j < width; j ++)
		{
			*(tempData + i*width*3 + j*3) = *(m_pData + (height-1-i)*width*3 + 3*j);
			*(tempData + i*width*3 + j*3 + 1) = *(m_pData + (height-1-i)*width*3 + 3*j + 1);
			*(tempData + i*width*3 + j*3 + 2) = *(m_pData + (height-1-i)*width*3 + 3*j + 2);
		}
	}


	//����(����������)ѵ����
	cascade = (CvHaarClassifierCascade*)cvLoad(cascade_name, 0, 0, 0);

	//���سɹ���������ʶ�𲢱�ʾ�����ز��ɹ���ʾ������Ϣ
	if (cascade)
	{
		//��BYTEͼ���ʽת����IplImage��ʽ
		IplImage* img = cvCreateImageHeader( cvSize(width, height), IPL_DEPTH_8U, 3);
		cvSetData(img, tempData, width*3);

		//����ʶ�𣬲��þ��ο��ʾ
		storage = cvCreateMemStorage(0);
		
		IplImage* tempImg = cvCreateImage(cvSize(img->width, img->height), 8, 1);

		cvCvtColor(img, tempImg, CV_BGR2GRAY);
		cvEqualizeHist(tempImg, tempImg);
		cvClearMemStorage(storage);

		CvSeq* faces = cvHaarDetectObjects( tempImg, cascade, storage, 1.1, 2, 0, cvSize(200, 200));	//���ÿɼ�⵽����С������СΪ(200,200)
		static int face_counter = 0;

		for (i = 0; i < (faces ? faces->total : 0); i++)
		{
			CvRect* rect = (CvRect*)cvGetSeqElem(faces, i);
			
			char pathName[50] = ".\\faces\\";			//�����ļ�����·��
			char faceCounter[5];
			itoa(face_counter, faceCounter, 10);
			strcat(pathName, faceCounter);
			strcat(pathName, ".jpg");
			face_counter++;

			IplImage* face = cvCreateImage(cvSize(150, 150), 8, 3);
					
			cvSetImageROI(img, *rect);					//����ROI(region of interest)
			cvResize(img, face);						//��ROI���򱣴浽faceͼ����
			cvSaveImage(pathName, face);				//���浽�ļ�
			cvResetImageROI(img);						//�ͷ�ROI

			cvReleaseImage(&face);

			CvPoint pt1;
			CvPoint pt2;
			pt1.x = rect->x;
			pt1.y = rect->y;
			pt2.x = rect->x + rect->width;
			pt2.y = rect->y + rect->height;
			cvRectangle( img, pt1, pt2, CV_RGB(255, 0, 0), 2);	
		}
		cvReleaseImage( &tempImg);

		//�����ͼ��IplImage��ʽת��BYTE
		for (i = 0; i < width*height*3; i++)
			tempData[i] = (img->imageDataOrigin)[i];

		//��֮ǰ�ķ�ת�ڷ�ת����
		for (i = 0; i < height; i ++)
		{
			for (j = 0; j < width; j ++)
			{
				*(m_pData + i*width*3 + j*3) = *(tempData + (height-1-i)*width*3 + 3*j);
				*(m_pData + i*width*3 + j*3 + 1) = *(tempData + (height-1-i)*width*3 + 3*j + 1);
				*(m_pData + i*width*3 + j*3 + 2) = *(tempData + (height-1-i)*width*3 + 3*j + 2);
			}
		}	
	}

	else
		AfxMessageBox("�޷����ط���������ȷ�Ϻ����ԣ�");
	cvReleaseHaarClassifierCascade( &cascade);
}




/*
	����:
		OnSnapExChange
	�������:
		WPARAM wParam			�ֲ���������Ϣ��Ϊ��ǰ���Դ����ͼ�����		
		LPARAM lParam			û��ʹ��
	�������:
		LRESULT						
	˵��:
		ʵ�ֶԲɼ����ݵĴ������ʾ
 */

int height=1024;
int width=1280;
int clickTimer = 0; 
//Point caliPoint(640,512);
FILE* pogRecordFile = NULL;

LRESULT CMainFrame::OnSnapExChange(WPARAM wParam, LPARAM lParam)
{
	CGSTATUS status = CG_OK;
	
	CView *pView		= GetActiveView();		//��ȡ��ǰVIEW��ͼ
	CDC *pDC			= pView->GetDC();		//�õ�VIEW��DC
	
	BYTE *pLinearAddr = NULL;		//��̬�ڴ��ַָ��
	DWORD dwImageSize = 0;			//ͼ���С
	HANDLE handle = NULL;			//��̬�ڴ��������
	
	dwImageSize = 768 * 576 * 3;	//����ͼ���С������Ƶ������ں���Ƶ��ʽȷ��

	BYTE *p = NULL, * q = NULL;

	/*
	 *	����ָ��λ�õľ�̬�ڴ棬
	 *	ƫ����ͼ���С��ͼ�����ȷ����������СΪͼ���С
	 *	�û��������κ�ʱ������ָ��λ�õľ�̬�ڴ棬Ȼ��ͨ��pLinearAddrָ�������Ӧ���ڴ档
	 */
	status = CGStaticMemLock(dwImageSize * wParam, dwImageSize, &handle, (PVOID *)&pLinearAddr);
	if (CG_SUCCESS(status)) {
		if (m_pImageBuffer) {
			/*
			 *	����̬�ڴ��е�ͼ�񴫵ݵ��û���������ͬʱ���и�ʽת����
			 *	�����̬�ڴ���ͼ��Ϊ15��16��32λ����ת��Ϊ24λ��
			 *	����ͼ�񿨲ɼ�����̬�ڴ��ͼ�������������ţ�
			 *	��Windows�д����λͼ������Ҫ���ã����һ�㻹Ҫ��ͼ���á�
			 */
			CGDataTransform(m_pImageBuffer,		//ͼ�񻺳���
							pLinearAddr,		//��̬�ڴ�
							768,				//ͼ����
							576,				//ͼ��߶�
							24,					//ͼ��λ���
							TRUE				//�Ƿ���ͼ��
							);
		}
		CGStaticMemUnlock(handle);				//�����̬�ڴ�����
///////////////////////////////////////////////////////////////////////////////////////////////////		
///////////////////////////////////////////////////////////////////////////////////////////////////		
		int i;
		
		if (CPublic::FaceDetected == TRUE)
			detect_and_draw(m_pImageBuffer, 768, 576);

    	if(CPublic::stateTag==0)
		{
		
		}
		else
		{
/*************************************ͼ��Ԥ������ȡ���������ȳ�������***************************************************************/

			preprocess.setThreshold(35);		//--------------------------------21
			preprocess.setScopeHeight(566);
			preprocess.setScopeWidth(384);		//�궨ͼ����������
			preprocess.setWidth(768);
			preprocess.search(m_pImageBuffer,10,0,true);	//����������������ֶ�λͫ������pupilCenter
															//��Ϊͼ��ĵײ��к�ɫ���ƣ����Բ��ܴ�(0,0)��ʼ		
			Point pointL=preprocess.getpupilCenter();

			//�ж����۵�λ��
			if(pointL.getX()>40&&pointL.getX()<536&&pointL.getY()>40&&pointL.getY()<384)
			{
				//����ֱ��ͼ����
				preprocess.setScopeHeight(60);
				preprocess.setScopeWidth(60);
				int thresholdAuto = preprocess.prepupil(m_pImageBuffer,pointL.getX()-30,pointL.getY()-30);	//ֱ��ͼ���������ֵ

				//����ͫ�׵�����
				preprocess.setThreshold(thresholdAuto);
				preprocess.setScopeHeight(80);
				preprocess.setScopeWidth(80);
				preprocess.setWidth(768);
				preprocess.search(m_pImageBuffer, pointL.getX()-40,pointL.getY()-40,false);		//��ROI����������ͫ������
				Point point=preprocess.getpupilCenter();
				
				//�������
				if(point.getX()>=40&&point.getX()<=536&&point.getY()>=40&&point.getY()<=728)
				{
					preprocess.setThreshold(200);//-------------------------200
					preprocess.setScopeHeight(80);
					preprocess.setScopeWidth(80);
					preprocess.setWidth(768);
					preprocess.calGlints2(m_pImageBuffer, point.getX()-40,point.getY()-40);	//��ȡ5�����point[5]
					
					if(preprocess.getPointNumber()>=5)
					{
						//�����
						for(i=0;i<5;i++)
						{
							if(preprocess.getPoint(i).getX()!=0&&preprocess.getPoint(i).getY()!=0)
							preprocess.setScopeHeight(80);
					        preprocess.setScopeWidth(80);
					        preprocess.setWidth(768);
							preprocess.blackened(m_pImageBuffer,preprocess.getPoint(i).getX(),preprocess.getPoint(i).getY(),5);	//????
						}
						
						//������ֵ�˲�
						BYTE * picture1;
						BYTE * picture2;
						picture1=(BYTE*)malloc(80*80*3*sizeof(BYTE));
						picture2=(BYTE*)malloc(80*80*3*sizeof(BYTE));
						memset(picture1,0,80*80*3*sizeof(BYTE));
						memset(picture2,0,80*80*3*sizeof(BYTE));

						//��Ҫ�����ͼ��ɵ�picture1��
						int j;
						for(i=point.getX()-40;i<point.getX()+40;i++)
						{
							for(j=point.getY()-40;j<point.getY()+40;j++)
							{
								int ii=point.getX();
								int jj=point.getY();
								
								*( picture1+ (i-ii+40)*80*3 + (j-jj+40)*3)=*(m_pImageBuffer+i*768*3+j*3);
								*( picture1+ (i-ii+40)*80*3 + (j-jj+40)*3+1)=*(m_pImageBuffer+i*768*3+j*3);
								*( picture1+ (i-ii+40)*80*3 + (j-jj+40)*3+2)=*(m_pImageBuffer+i*768*3+j*3);	
							}
						}

						//ת����openCVʹ�õ������ʽ
						CvSize n_size = cvSize(80,80);
						IplImage* frame = cvCreateImageHeader( n_size, IPL_DEPTH_8U, 3 );
						frame->imageData = (char *)picture1; 
							
						IplImage* frame2 = cvCreateImageHeader( n_size, IPL_DEPTH_8U, 3 );
						frame2->imageData = (char *)picture2;

						//��ֵ�˲�
						cvSmooth(frame,frame2,CV_MEDIAN,9,9,0,0);


						//���˲����ͼ��Żص�ԭʼͼ����
						for(i=point.getX()-40;i<point.getX()+40;i++)
						{
							for(j=point.getY()-40;j<point.getY()+40;j++)
							{
								int ii=point.getX();
								int jj=point.getY();
								*(m_pImageBuffer+i*768*3+j*3)=*( picture2 + (i-ii+40)*80*3 + (j-jj+40)*3);
								*(m_pImageBuffer+i*768*3+j*3+1)=*( picture2 + (i-ii+40)*80*3 + (j-jj+40)*3);
								*(m_pImageBuffer+i*768*3+j*3+2)=*( picture2 + (i-ii+40)*80*3 + (j-jj+40)*3);
							}
						}

						free(picture1);
						free(picture2);	
						
						//����ͫ��
						preprocess.setScopeHeight(80);
						preprocess.setScopeWidth(80);
						thresholdAuto = preprocess.prepupil(m_pImageBuffer,point.getX()-40,point.getY()-40);
						preprocess.setThreshold(thresholdAuto);
						preprocess.setScopeHeight(80);
						preprocess.setScopeWidth(80);
						preprocess.setWidth(768);
						point=preprocess.pupil(m_pImageBuffer,point.getX()-40,point.getY()-40);

						if(point.getX()!=0&&point.getY()!=0)
						{
							//��ͼ���л�����ߵ����ĺ�ͫ������
							for(i=0;i<5;i++)
							{
								draw3(m_pImageBuffer,preprocess.getPoint(i).getX(),preprocess.getPoint(i).getY(),i);
							}
							draw3(m_pImageBuffer,point.getX(),point.getY(),5);
							drawrect(m_pImageBuffer, point.getX(),point.getY());

							//����ת��
							Point pointbobo[6];
							pointbobo[0].setX(768-preprocess.getPoint(1).getY());
							pointbobo[0].setY(576-preprocess.getPoint(1).getX());
							pointbobo[1].setX(768-preprocess.getPoint(3).getY());
							pointbobo[1].setY(576-preprocess.getPoint(3).getX());
							pointbobo[2].setX(768-preprocess.getPoint(2).getY());
							pointbobo[2].setY(576-preprocess.getPoint(2).getX());
							pointbobo[3].setX(768-preprocess.getPoint(0).getY());
							pointbobo[3].setY(576-preprocess.getPoint(0).getX());
							pointbobo[4].setX(768-preprocess.getPoint(4).getY());
							pointbobo[4].setY(576-preprocess.getPoint(4).getX());
							pointbobo[5].setX(768-point.getY());
							pointbobo[5].setY(576-point.getX());


/**********************************************************����������ȡ����**************************************************************/

							
							//����ǻ�ȡ��������ô���������
							if(CPublic::stateTag==1 && NULL!=CPublic::g_pBestAlpha && NULL!=CPublic::g_pCaliPoint)
							{

								mapping.setHeight(height);
								mapping.setWidth(width);

								//����ӳ��
								m_caliPoint.setX(CPublic::g_pCaliPoint->getX());
								m_caliPoint.setY(CPublic::g_pCaliPoint->getY());
								mapping.calBestAlph(pointbobo,m_caliPoint);
								if(mapping.getGazePoint().getX()!=0 && mapping.getGazePoint().getY()!=0 && CPublic::saveFlag==true)
								{							
									*CPublic::g_pBestVector = mapping.bestVector;
                                    *CPublic::g_pBestAlpha = mapping.bestAlph;
									fprintf(CPublic::fpCur,"%f ",*CPublic::g_pBestAlpha);
									fprintf(CPublic::fpCur,"%f ",mapping.bestVector.getX());
									fprintf(CPublic::fpCur,"%f\n",mapping.bestVector.getY());
								}	
							}	


							//��������ӳ��(����Button���)
							else if(CPublic::stateTag==2)
							{							
								//���и�ֵ����
								mapping.setHeight(height);
								mapping.setWidth(width);

								//����ӳ��
								mapping.calGazePoint(pointbobo,m_bestAlph,m_bestVector);		//���Ի�ȡ��ǰע�ӵ�����

								//�жϵ�ǰע�ӵ�������Ļ������
								if(mapping.getGazePoint().getX()!=0&&mapping.getGazePoint().getY()!=0)
								{							
									float minDistance = 65535.0;
									float curDistance = 65535.0;
									int aIndex=0;
									for (int i=0; i<CPublic::g_CaliPointNumber; i++)//ѡ���뵱ǰ��������������alphaֵ��Ϊ��ǰalpha
									{
										curDistance = sqrt((CPublic::g_curCaliPoints[i].getX()-mapping.getGazePoint().getX())*(CPublic::g_curCaliPoints[i].getX()-mapping.getGazePoint().getX())+ (CPublic::g_curCaliPoints[i].getY()-mapping.getGazePoint().getY())*(CPublic::g_curCaliPoints[i].getY()-mapping.getGazePoint().getY()));
										if (curDistance < minDistance)
										{
                                            minDistance = curDistance;
											aIndex = i;
										}
									}
									
									m_bestAlph = CPublic::g_curBestAlpha[aIndex];
									m_bestVector = CPublic::g_curBestVector[aIndex];
									
									//�ڸ������alpha�Լ����λ��ʸ��֮�����¼���ע�ӵ�����
									mapping.calGazePoint(pointbobo,m_bestAlph,m_bestVector);
									Point gazePoint = mapping.getGazePoint();

									//���������̣�������ƶ���ĳ����������ʱ������ͣ���ڸü�����λ��
									if (CPublic::NumFlag == FALSE && CPublic::AlpFlag == FALSE)	//û�п�������
									{
										POINT	curPoint;				//��ȡ��굱ǰλ��
										GetCursorPos(&curPoint);
										if (sqrt((curPoint.x-gazePoint.getX())*(curPoint.x-gazePoint.getX()) + (curPoint.y-gazePoint.getY())*(curPoint.y-gazePoint.getY())) > 30)
											SetCursorPos(gazePoint.getX(), gazePoint.getY());
									}

									else if (CPublic::NumFlag) //�������ּ���
									{
 										for (int Num = 0; Num < 12; Num++)
 										{
											if (CPublic::rectNum[Num].left <= gazePoint.getX() && gazePoint.getX() <= CPublic::rectNum[Num].right &&
												CPublic::rectNum[Num].top <= gazePoint.getY() && gazePoint.getY() <= CPublic::rectNum[Num].bottom)
											{
												SetCursorPos(CPublic::rectNum[Num].CenterPoint().x, CPublic::rectNum[Num].CenterPoint().y);
												break;
											}
 										}
									}

									else if (CPublic::AlpFlag) //����ȫ����
									{
										for (int Alp = 0; Alp < 30; Alp++)
										{
											if (CPublic::rectAlp[Alp].left <= gazePoint.getX() && gazePoint.getX() <= CPublic::rectAlp[Alp].right &&
												CPublic::rectAlp[Alp].top <= gazePoint.getY() && gazePoint.getY() <= CPublic::rectAlp[Alp].bottom)
											{
												SetCursorPos(CPublic::rectAlp[Alp].CenterPoint().x, CPublic::rectAlp[Alp].CenterPoint().y);
												break;
											}
										}
									}
									
									

								/*************	���ۿ���������������ƶ�
									//��ȡ��굱ǰλ��
									Point	gazePoint;
									POINT	curPoint;
									GetCursorPos(&curPoint);
									gazePoint = mapping.getGazePoint();	//��ȡע�ӵ�

									if (gazePoint.getX() < 60)				//��Ե
									{
										gazePoint.setX(gazePoint.getX() - 60);
									}
									else if (gazePoint.getX() > 1220)
									{
										gazePoint.setX(gazePoint.getX() + 60);
									}
									
									if (gazePoint.getY() < 60)
									{
										gazePoint.setY(gazePoint.getY() - 60);
									}
									else if (gazePoint.getY() > 964)
									{
										gazePoint.setX(gazePoint.getX() + 60);
									}

									
									  //�ж�ע�ӵ��뵱ǰ���λ�ù�ϵ
									if (gazePoint.getX() - curPoint.x >= 60)
									{
									  if (gazePoint.getY() - curPoint.y >= 60)
									  {
											SetCursorPos(curPoint.x+20, curPoint.y+20);	//����
									  }
									  else if(gazePoint.getY() - curPoint.y >= 60)
									  {
											SetCursorPos(curPoint.x+20, curPoint.y);		//����
									  }
									  else
									  {
											SetCursorPos(curPoint.x+20, curPoint.y-20);	//����
									  }
									}
									else if (gazePoint.getX() - curPoint.x >= -60)
									{
									  if (gazePoint.getY() - curPoint.y >= 60)
									  {
											SetCursorPos(curPoint.x, curPoint.y+20);		//����
									  }
									  else if(gazePoint.getY() - curPoint.y >= -60)
									  {
											SetCursorPos(curPoint.x, curPoint.y);		//����
									  }
									  else
									  {
											SetCursorPos(curPoint.x, curPoint.y-20);		//����
									  }
									}
									else
									{
									  if (gazePoint.getY() - curPoint.y >= 60)
									  {
											SetCursorPos(curPoint.x-20, curPoint.y+20);	//����
									  }
									  else if(gazePoint.getY() - curPoint.y >= -60)
									  {
											SetCursorPos(curPoint.x-20, curPoint.y);		//����
									  }
									  else
									  {
											SetCursorPos(curPoint.x-20, curPoint.y-20);	//����
									  }
									}	
					*************/
									fprintf(pogRecordFile,"%f	%f\n",mapping.getGazePoint().getX(),mapping.getGazePoint().getY());
									clickTimer++;
									if (30 == clickTimer)		//ע�Ӷ�ð���		
									{
										mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
                                        mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0); 
										clickTimer = 0;
									}
								}						
							}
							//���Ȳ���
							else if (CPublic::stateTag==3)
							{
								//���и�ֵ����
								mapping.setHeight(height);
								mapping.setWidth(width);
								//����ӳ�䣬���Լ��㵱ǰע�ӵ�����
								mapping.calGazePoint(pointbobo, m_bestAlph,m_bestVector);
								//�жϵ�ǰע�ӵ�������Ļ������
								if(mapping.getGazePoint().getX()!=0&&mapping.getGazePoint().getY()!=0)
								{							
									float minDistance = 65535.0;
									float curDistance = 65535.0;
									int aIndex=0;
									for (int i=0; i<CPublic::g_CaliPointNumber; i++)//ѡ���뵱ǰ��������������alphaֵ��Ϊ��ǰalpha
									{
										curDistance = sqrt((CPublic::g_curCaliPoints[i].getX()-mapping.getGazePoint().getX())*(CPublic::g_curCaliPoints[i].getX()-mapping.getGazePoint().getX())+ (CPublic::g_curCaliPoints[i].getY()-mapping.getGazePoint().getY())*(CPublic::g_curCaliPoints[i].getY()-mapping.getGazePoint().getY()));
										if (curDistance < minDistance)
										{
                                            minDistance = curDistance;
											aIndex = i;
										}
										
									}
									m_bestAlph = CPublic::g_curBestAlpha[aIndex];
									m_bestVector = CPublic::g_curBestVector[aIndex];
									
									//�ڸ������alpha�Լ����λ��ʸ��֮�����¼���ע�ӵ�����
									mapping.calGazePoint(pointbobo,m_bestAlph,m_bestVector);
									SetCursorPos(mapping.getGazePoint().getX(),mapping.getGazePoint().getY());
									float errorDistance = 0;
									errorDistance = sqrt((CPublic::g_pCurTestPoint->getX()-mapping.getGazePoint().getX())*(CPublic::g_pCurTestPoint->getX()-mapping.getGazePoint().getX())+(CPublic::g_pCurTestPoint->getY()-mapping.getGazePoint().getY())*(CPublic::g_pCurTestPoint->getY()-mapping.getGazePoint().getY()));
                                    fprintf(CPublic::fpTestCur,"%f	%f	%f\n",CPublic::g_pCurTestPoint->getX()-mapping.getGazePoint().getX(),CPublic::g_pCurTestPoint->getY()-mapping.getGazePoint().getY(),errorDistance);
                                    
								}						

							}
							//���ʵ��ӳ�䲿��
							else if (CPublic::stateTag==4)
							{
								//���и�ֵ����
								mapping.setHeight(height);
								mapping.setWidth(width);

								//����ӳ�䣬���Լ�������ע�ӵ������
								mapping.calGazePoint(pointbobo,m_bestAlph,m_bestVector);
								//�ж�ע�ӵ�������Ļ������
								if(mapping.getGazePoint().getX()!=0&&mapping.getGazePoint().getY()!=0)
								{							
									float minDistance = 65535.0;
									float curDistance = 65535.0;
									int aIndex=0;

									for (int i=0; i<CPublic::g_CaliPointNumber; i++)//ѡ���뵱ǰ��������������alphaֵ��Ϊ��ǰalpha
									{
										curDistance = sqrt((CPublic::g_curCaliPoints[i].getX()-mapping.getGazePoint().getX())*(CPublic::g_curCaliPoints[i].getX()-mapping.getGazePoint().getX())+ (CPublic::g_curCaliPoints[i].getY()-mapping.getGazePoint().getY())*(CPublic::g_curCaliPoints[i].getY()-mapping.getGazePoint().getY()));
										if (curDistance < minDistance)
										{
                                            minDistance = curDistance;
											aIndex = i;
										}
										
									}
									m_bestAlph = CPublic::g_curBestAlpha[aIndex];
									m_bestVector = CPublic::g_curBestVector[aIndex];
									minDistance = 65535.0;
									curDistance = 65535.0;
									aIndex=0;
									for(int j=0; j<CPublic::g_curGridTestPointNumber; j++)
									{
										curDistance = sqrt((CPublic::g_curGridTestPoints[j].getX()-mapping.getGazePoint().getX())*(CPublic::g_curGridTestPoints[j].getX()-mapping.getGazePoint().getX())+ (CPublic::g_curGridTestPoints[j].getY()-mapping.getGazePoint().getY())*(CPublic::g_curGridTestPoints[j].getY()-mapping.getGazePoint().getY()));
										if (curDistance < minDistance)
										{
                                            minDistance = curDistance;
											aIndex = j;
										}
									}
									SetCursorPos(CPublic::g_curGridTestPoints[aIndex].getX(),CPublic::g_curGridTestPoints[aIndex].getY());
								//	float errorDistance = 0;
								//	errorDistance = sqrt((CPublic::g_pCurTestPoint->getX()-mapping.getGazePoint().getX())*(CPublic::g_pCurTestPoint->getX()-mapping.getGazePoint().getX())+(CPublic::g_pCurTestPoint->getY()-mapping.getGazePoint().getY())*(CPublic::g_pCurTestPoint->getY()-mapping.getGazePoint().getY()));
                                //   fprintf(CPublic::fpTestCur,"%f ",errorDistance);
                                    
								}						
								
							}
						}

					}
				}
			}
		}
///////////////////////////////////////////////////////////////////////////////////////////////////	

		//����ͼ�ͻ�����ʾͼ��
		StretchDIBits(pDC->GetSafeHdc(),
						0,
						0,
						768,					//��ʾ���ڿ��
						576,					//��ʾ���ڸ߶�
						0,
						0,
						768,					//ͼ����
						576,					//ͼ��߶�
						m_pImageBuffer,			//ͼ�񻺳���				
						m_pBmpInfo,				//BMPͼ��������Ϣ
						DIB_RGB_COLORS,
						SRCCOPY
						);	
	
	}//��һ��if	
	pView->ReleaseDC(pDC);	
	return 1;
}//��������

/*
 *	�ر�������ܵ�ʱ�򣬽�����Ӧ
 *	�û���û��ͨ���˵��������ر�ͼ�񿨲ɼ���	
 *	��ֱ�ӹر�Ӧ�ó���ʱ��Ӧ��֤ͼ�񿨲ɼ����ر�
 */
void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	
	//AfxMessageBox("mark");
	if (m_bOpen) {
		CGCloseSnapEx(m_hcg);
	}

	CFrameWnd::OnClose();
}

/*
 * ��ӦCardCtrl�����˵��е�negative��ť
 * ����ͼ��ɫ��־
 */
void CMainFrame::OnNegative() 
{
	// TODO: Add your command handler code here
	m_bNegative = !m_bNegative;			
}

void CMainFrame::OnUpdateNegative(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bNegative);
}



/*
 *	��Ӧ״̬���ĵ�һ����ť
 *	����stateTagΪ0����ɲ�����ȡ
 */
void CMainFrame::OnHkstop() 
{
	// TODO: Add your command handler code here
	CPublic::stateTag=0;
	if (NULL != pogRecordFile)
	{
		fclose(pogRecordFile);
	}
}

/*
 *	��Ӧ״̬�������һ����ť
 *	���ܣ���stateTag����Ϊ2����������ӳ��
 */
void CMainFrame::OnBtmapping() 
{
	// TODO: Add your command handler code here
	CPublic::stateTag = 2;
	pogRecordFile = fopen("pogRecordFile.txt","w");
}



/*
 *	״̬����2*2������ȡ
 */
void CMainFrame::OnBtcalib() 
{
	// TODO: Add your command handler code here
	CPublic::g_CaliPointNumber=4;
	CPublic::g_curCaliPoints=CPublic::g_caliPoint;
	CPublic::g_curBestAlpha=CPublic::g_BestAlpha;
	CPublic::g_curBestVector=CPublic::g_BestVector2x2;
	CCaliDlg2X2 *pDlg = new CCaliDlg2X2;
	pDlg->Create(IDD_CAL2X2,this);
	pDlg->ShowWindow(SW_SHOW);
}

/*
 * Acctest �˵�
 * ���뾫�Ȳ��Խ���
 */
void CMainFrame::OnAccutest() 
{
	// TODO: Add your command handler code here
	CActDlg *pActDlg = new CActDlg;
	pActDlg->Create(IDD_ACT,this);
	pActDlg->ShowWindow(SW_SHOW);
}

/*
 * ��Ӧ�˵����±ߵ�״̬���е�3*3���������ȡ
 */
void CMainFrame::OnCalib3x3() 
{
	// TODO: Add your command handler code here
	CPublic::g_CaliPointNumber=9;
	CPublic::g_curCaliPoints=CPublic::g_caliPoint3X3;
	CPublic::g_curBestAlpha=CPublic::g_BestAlpha3X3;
	CPublic::g_curBestVector=CPublic::g_BestVector3x3;
	CCaliDlg3X3 *pCliDlg3X3 = new CCaliDlg3X3;
	pCliDlg3X3->Create(IDD_CAL3X3,this);
	pCliDlg3X3->ShowWindow(SW_SHOW);
}

/*
 *	��Ӧ�˵����±ߵ�״̬���е�4*4���������ȡ
 */
void CMainFrame::OnBtcalib4x4() 
{
	// TODO: Add your command handler code here
	CPublic::g_CaliPointNumber=16;
	CPublic::g_curCaliPoints=CPublic::g_caliPoint4X4;
	CPublic::g_curBestAlpha=CPublic::g_BestAlpha4X4;
	CPublic::g_curBestVector=CPublic::g_BestVector4x4;
	CCaliDlg4X4 *pCliDlg4X4 = new CCaliDlg4X4;
	pCliDlg4X4->Create(IDD_CAL4X4,this);
	pCliDlg4X4->ShowWindow(SW_SHOW);
}

/*
 * 	��Ӧ�˵����±ߵ�״̬���е�5*5���������ȡ
 */
void CMainFrame::OnBtcalib5x5() 
{
	// TODO: Add your command handler code here
	CPublic::g_CaliPointNumber=25;
	CPublic::g_curCaliPoints=CPublic::g_caliPoint5X5;
	CPublic::g_curBestAlpha=CPublic::g_BestAlpha5X5;
	CPublic::g_curBestVector=CPublic::g_BestVector5x5;
	CCaliDlg5X5 *pCliDlg5X5 = new CCaliDlg5X5;
	pCliDlg5X5->Create(IDD_CAL5X5,this);
	pCliDlg5X5->ShowWindow(SW_SHOW);
}

/*
 *	��Ӧ�˵����±ߵ�״̬���е�6*6���������ȡ
 */
void CMainFrame::OnBtcalib6x6() 
{
	// TODO: Add your command handler code here
	CPublic::g_CaliPointNumber=36;
	CPublic::g_curCaliPoints=CPublic::g_caliPoint6X6;
	CPublic::g_curBestAlpha=CPublic::g_BestAlpha6X6;
	CPublic::g_curBestVector=CPublic::g_BestVector6x6;
	CCaliDlg6X6 *pCliDlg6X6 = new CCaliDlg6X6;
	pCliDlg6X6->Create(IDD_CAL6X6,this);
	pCliDlg6X6->ShowWindow(SW_SHOW);
}

//�������еľ������
void CMainFrame::MyParameter()
{
	CPublic::g_CaliPointNumber = 16;
	CPublic::g_curCaliPoints = CPublic::g_caliPoint4X4;
	float tempAlpha[16] = {	
							1.11, 1.17, 1.17, 1.11, 
							1.24, 1.31, 1.31, 1.24,
							1.39, 1.64, 1.64, 1.39, 
							1.41, 1.95, 1.95, 1.41	
						};
	Point tempVector[16] = { 
// 							Point(9.75, -9.53), Point(22.84, -5.15), Point(4.70, 1.43), Point(15.65, 7.14),
// 							Point(12.77, -12.01), Point(24.73, -9.61), Point(32.10, 7.08), Point(29.51, 21.92),
// 							Point(-16.57, 25.62), Point(-1.04, 0.72), Point(53.37, 18.00), Point(56.39, 67.59),
// 							Point(-31.47, 106.00), Point(-32.75, 75.88), Point(78.67, 74.36), Point(47.54, 130.00)
							Point(10, -10), Point(23, -5), Point(5, 2), Point(16, 7),
							Point(13, -12), Point(25, -10), Point(32, 7), Point(29, 22),
							Point(-17, 26), Point(-1, 1), Point(53, 18), Point(56, 67),
							Point(-31, 106), Point(-32, 75), Point(78, 74), Point(47, 130)
						};
	for (int i = 0; i < 16; i++)
	{
		CPublic::g_BestAlpha4X4[i] = tempAlpha[i];
		CPublic::g_BestVector4x4[i] = tempVector[i];
	}
	CPublic::g_curBestAlpha = CPublic::g_BestAlpha4X4;
	CPublic::g_curBestVector = CPublic::g_BestVector4x4;

}

/*
 * ��ӦButtonTest�˵���ť
 * ���밴ť���Խ��棬������������
 */
void CMainFrame::OnBtest()
{

   CButtonTestDlg* pButtonTestDlg = new CButtonTestDlg;
   pButtonTestDlg->Create(IDD_BTTEST,this);
   pButtonTestDlg->ShowWindow(SW_SHOW);

}



/*
 *	��ӦGridTest�����˵��µ�2*2��ť
 *	����2*2�����۹�ע������
 */
void CMainFrame::OnGridtest2x2() 
{
	// TODO: Add your command handler code here
	CPublic::stateTag=4;
	CPublic::g_curGridTestPointNumber=4;
	CPublic::g_curGridTestPoints=CPublic::g_caliPoint;
	
	//	SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR,(LONG)LoadCursor(NULL , IDC_NO));
	
	IplImage* pImg;
	if( (pImg = cvLoadImage( "2X2.bmp", 1)) != 0 )
    {
        cvNamedWindow( "AdsTest", 1 );//��������
		cvMoveWindow("AdsTest",0,0);//��ʾ���ڵ�λ��
        cvShowImage( "AdsTest", pImg );//��ʾͼ��
		
        cvWaitKey(0); //�ȴ�����
		
        cvDestroyWindow( "AdsTest" );//���ٴ���
        cvReleaseImage( &pImg ); //�ͷ�ͼ��
    }
}

/*
 *	��ӦGridTest�����˵��µ�3*3��ť
 *	����3*3�����۹�ע������
 */
void CMainFrame::OnGridtest3x3() 
{
	// TODO: Add your command handler code here
	CPublic::stateTag=4;
	CPublic::g_curGridTestPointNumber=9;
	CPublic::g_curGridTestPoints=CPublic::g_caliPoint3X3;
	
	IplImage* pImg;
	if( (pImg = cvLoadImage( "3X3.bmp", 1)) != 0 )
    {
        cvNamedWindow( "AdsTest", 1 );//��������
		cvMoveWindow("AdsTest",0,0);//��ʾ���ڵ�λ��
        cvShowImage( "AdsTest", pImg );//��ʾͼ��
		
        cvWaitKey(0); //�ȴ�����
		
        cvDestroyWindow( "AdsTest" );//���ٴ���
        cvReleaseImage( &pImg ); //�ͷ�ͼ��
    }
}

/*
 *	��ӦGridTest�����˵��µ�4*4��ť
 *	����4*4�����۹�ע������
 */
void CMainFrame::OnGridtest4x4() 
{
	// TODO: Add your command handler code here
	CPublic::stateTag=4;
	CPublic::g_curGridTestPointNumber=16;
	CPublic::g_curGridTestPoints=CPublic::g_caliPoint4X4;
	
	//	SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR,(LONG)LoadCursor(NULL , IDC_NO));
	
	IplImage* pImg;
	if( (pImg = cvLoadImage( "4X4.bmp", 1)) != 0 )
    {
        cvNamedWindow( "AdsTest", 1 );//��������
		cvMoveWindow("AdsTest",0,0);//��ʾ���ڵ�λ��
        cvShowImage( "AdsTest", pImg );//��ʾͼ��
		
        cvWaitKey(0); //�ȴ�����
		
        cvDestroyWindow( "AdsTest" );//���ٴ���
        cvReleaseImage( &pImg ); //�ͷ�ͼ��
    }	
}

/*
 *	��ӦGridTest�����˵��µ�5*5��ť
 *	����5*5�����۹�ע������
 */
void CMainFrame::OnGridtest5x5() 
{
	// TODO: Add your command handler code here
	CPublic::stateTag=4;
	CPublic::g_curGridTestPointNumber=25;
	CPublic::g_curGridTestPoints=CPublic::g_caliPoint5X5;
	
	//	SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR,(LONG)LoadCursor(NULL , IDC_NO));
	
	IplImage* pImg;
	if( (pImg = cvLoadImage( "5X5.bmp", 1)) != 0 )
    {
        cvNamedWindow( "AdsTest", 1 );//��������
		cvMoveWindow("AdsTest",0,0);//��ʾ���ڵ�λ��
        cvShowImage( "AdsTest", pImg );//��ʾͼ��
		
        cvWaitKey(0); //�ȴ�����
		
        cvDestroyWindow( "AdsTest" );//���ٴ���
        cvReleaseImage( &pImg ); //�ͷ�ͼ��
    }
}

/*
 *	��ӦGridTest�����˵��µ�6*6��ť
 *	����6*6�����۹�ע������
 */
void CMainFrame::OnGridtest6x6() 
{
	// TODO: Add your command handler code here
	CPublic::stateTag=4;
	CPublic::g_curGridTestPointNumber=36;
	CPublic::g_curGridTestPoints=CPublic::g_caliPoint6X6;
	
	//	SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR,(LONG)LoadCursor(NULL , IDC_NO));
	
	IplImage* pImg;
	if( (pImg = cvLoadImage( "6X6.bmp", 1)) != 0 )
    {
        cvNamedWindow( "AdsTest", 1 );//��������
		cvMoveWindow("AdsTest",0,0);//��ʾ���ڵ�λ��
        cvShowImage( "AdsTest", pImg );//��ʾͼ��
		
        cvWaitKey(0); //�ȴ�����
		
        cvDestroyWindow( "AdsTest" );//���ٴ���
        cvReleaseImage( &pImg ); //�ͷ�ͼ��
    }
}

void CMainFrame::OnKeyboard() 
{
	// TODO: Add your command handler code here
	//show the keyboard
	CPassWordDlg *pPWDlg = new CPassWordDlg;
	pPWDlg->Create(IDD_PassWord, this);
	pPWDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::OnFacedetect() 
{
	// TODO: Add your command handler code here
	if (CPublic::FaceDetected == FALSE)
		CPublic::FaceDetected = TRUE;
	else
		CPublic::FaceDetected = FALSE;
}
