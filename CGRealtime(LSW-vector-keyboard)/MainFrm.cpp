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
	 *	初始化所有成员变量，同时打开图像卡
	 */
	CGSTATUS status = CG_OK;
	
	m_bOpen			= FALSE;
	m_bStart		= FALSE;

	m_bNegative		= TRUE;

	m_pBmpInfo		= NULL;
	m_pImageBuffer	= NULL;

	//	打开图像卡 1
	status = BeginCGCard(1, &m_hcg);
	
	//	检验函数执行状态，如果失败，则返回错误状态消息框
	CG_VERIFY(status);

	//设置初始alpha值为2.0
	m_bestAlph = 2;

	//设置初始位移矢量为(0,0)
	m_bestVector.setX(0);
	m_bestVector.setY(0);

	m_caliPoint.setX(640);
	m_caliPoint.setY(512);
//	fperror=fopen("error.txt","w");
}

CMainFrame::~CMainFrame()
{
	CGSTATUS status = CG_OK;
	
	//	关闭图像卡，释放图像卡内部资源
	status = EndCGCard(m_hcg);
	CG_VERIFY(status);

	//	回收图像缓冲区
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
	 *	初始化图像卡硬件状态，用户也可以在其他位置初始化图像卡，
	 *	但应保证图像卡已经打开，建议用户在应用程序初始化时，
	 *	同时初始化图像卡硬件。
	 */

	//设置视频制式(PAL / NTSC)，由当前视频源制式决定
	CGSetVideoStandard(m_hcg, PAL);		
	
	/*
	 *	视频格式，即采集图像数据描述方式，	
	 *	包括YUV422、RGB888、RGB565、RGB555、RGB8888、ALL8BIT、LIMITED8BIT，
	 *  在采集图像到屏幕时，需要保证视频格式和当前系统屏幕位深度一致，而采集到内存没有此限制。
	 */
	CGSetVideoFormat(m_hcg, RGB888);	

	//扫描模式，包括 FRAME、FIELD
	CGSetScanMode(m_hcg, FRAME);

	/*
	 *	晶振，包括CRY_OSC_35M、CRY_OSC_28M	
	 *	对于DH-CG300图像卡，一般为CRY_OSC_35M，对于DH-QP300图像卡，一般为CRY_OSC_28M，
	 *	其他类型图像卡没有此硬件设置，但可以调用此接口，并返回CG_NOT_SUPPORT_INTERFACE信息
	 */
	CGSelectCryOSC(m_hcg, CRY_OSC_35M);
	
	/*
	 *	设置视频源路，
	 *  视频源路VIDEO_SOURCE包括视频类型和序号，
	 *	各种图像卡支持的视频源路不尽相同，请参看相应硬件说明
	 */
	VIDEO_SOURCE source;
	source.type		= COMPOSITE_VIDEO;
	source.nIndex	= 0;
	CGSetVideoSource(m_hcg, source);

	/*
	 *	视频输入窗口，即视频输入范围，输入窗口取值范围：
	 *	对于视频制式为PAL制，水平方向为0-768，垂直方向为0-576 
	 *	对于视频制式为NTSC制，水平方向为0-768，垂直方向为0-576 
	 *  视频窗口左上角X坐标和窗口宽度应为4的倍数，左上角Y坐标和窗口高度应为2的倍数
	 */
	CGSetInputWindow(m_hcg, 0, 0, 768, 576);
	
	/*
	 *	视频输出窗口，即视频输出范围，输出窗口取值范围必须在输入窗口范围以内，
	 *  视频窗口左上角X坐标和窗口宽度应为4的倍数，左上角Y坐标和窗口高度应为2的倍数
	 *	在采集到屏幕时，输出窗口的起始位置为图像屏幕输出位置的屏幕坐标，
	 *	在采集到内存时，输出窗口的起始位置设置为(0, 0)即可。
	 */
	CGSetOutputWindow(m_hcg, 0, 0, 768, 576);

	/*
	 *	m_pBmpInfo即指向m_chBmpBuf缓冲区，用户可以自己分配BTIMAPINFO缓冲区	
	 */
	m_pBmpInfo								= (BITMAPINFO *)m_chBmpBuf;
	
	/*
	 *	初始化BITMAPINFO 结构，此结构在保存bmp文件、显示采集图像时使用
	 */
	m_pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);

	//	图像宽度，一般为输出窗口宽度
	m_pBmpInfo->bmiHeader.biWidth			= 768;		
	
	/*
	 *	图像高度，根据扫描模式(FRAME/FIELD)的不同	
	 *	FRAME制下，一般为输出窗口高度
	 *	FIELD制下，一般为输出窗口高度的一半
	 */
	m_pBmpInfo->bmiHeader.biHeight			= 576;		

	/*
	 *	图像位深度，由视频格式确定，
	 *	采集图像视频格式有RGB565、RGB555、RGB888、ALL8BIT等，
	 *  如果使用CGDateTransfrom函数，则将15，16位数据转换为24位
	 */
	m_pBmpInfo->bmiHeader.biBitCount		= 24;
	
	/*
	 *	以下设置一般相同，
	 *	对于低于8位的位图，还应设置相应的位图调色板
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
	 *	分配图像缓冲区，一般用来存储采集图像
	 *	用户可以将设备静态内存的图像数据直接通过指针或
	 *	用CGDataTransfrom函数拷贝到图像缓冲区,然后做进一步的处理，
	 *	一般图像缓冲区大小由输出窗口大小和视频格式确定。
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
 *	响应CardCtrl下拉菜单中的Open按钮
 *	初始化图像卡采集图像到内存的控制，
 *	指定回调函数SnapThreadCallbackEx和用户参数m_hWnd
 */
void CMainFrame::OnSnapexOpen() 
{
	// TODO: Add your command handler code here
	CGSTATUS status = CG_OK;

	//cout<<"open"<<endl;
	status = CGOpenSnapEx(m_hcg, SnapThreadCallbackEx, m_hWnd);					
	CG_VERIFY(status);
	if (CG_SUCCESS(status)) {
		m_bOpen = TRUE;			//标志已经打开SnapEx环境
	}
}



void CMainFrame::OnUpdateSnapexOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bOpen);
	pCmdUI->SetCheck(m_bOpen);
}


/*
 *	响应CardCtrl下拉菜单中的Start按钮
 *	启动图像卡采集图像到内存
 *	指定图像卡将图像采集到静态内存偏移为0的位置，
 *	采集缓冲区大小为2幅图像大小
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
 *	响应CardCtrl下拉菜单中的Stop按钮
 *	停止采集图像到内存，可以再次调用CGStartSnapEx启动图像卡采集
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
 *	响应CardCtrl下拉菜单中的Close按钮
 *	终止图像卡采集图像到内存，同时释放所有采集环境，
 *	再次启动图像卡采集，必须重新初始化	
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
	函数:
		SnapThreadCallbackEx
	输入参数:
		SNAP_INFO *pInfo		SNAP_INFO结构包括当前图像卡SNAP执行状态
	输出参数:
		int						
	说明:
		图像卡采集到内存回调函数，但用户一般不用调用，由用户提供给SDK使用，
		用户在回调函数内实现对采集数据的处理和显示即可
 */
int CALLBACK CMainFrame::SnapThreadCallbackEx(SNAP_INFO *pInfo)
{
	HWND hwnd = (HWND)(pInfo->pParam);
	
	/*
	 *	发送自定义消息WM_SNAP_EX_CHANGE到主窗口，	
	 *	同时传入当前可以处理的图像序号
	 *	注意：用SendMessage发送消息，必须等待消息处理完毕后，才能退出整个SendMessage函数
	 */
	::SendMessage(hwnd, WM_SNAP_EX_CHANGE, pInfo->nNumber, 0);

	return 1;
}

/*************************************************************************
*
*	功能:画出找到的点用不同的颜色
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
 * 绘制以瞳孔中心为中心点的矩形目标区域
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

const char* cascade_name ="haarcascade_frontalface_alt.xml";//分类器的名称

/**
 * @author		lsw_sky@outlook.com
 * @date		2014.08.22
 * @brief		对传入的BYTE格式的图像进行人脸检测并标示出来
 * @param[in]	BYTE* m_pData	待检测图像
 * @param[in]	int width		待检测图像的宽
 * @param[in]	int height		待检测图像的高
 * @return		void
 **/
void CMainFrame::detect_and_draw(BYTE* m_pData, int width, int height)				
{
	//将m_pData进行上下翻转
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


	//加载(级联分类器)训练库
	cascade = (CvHaarClassifierCascade*)cvLoad(cascade_name, 0, 0, 0);

	//加载成功进行人脸识别并标示，加载不成功显示出错信息
	if (cascade)
	{
		//将BYTE图像格式转换成IplImage格式
		IplImage* img = cvCreateImageHeader( cvSize(width, height), IPL_DEPTH_8U, 3);
		cvSetData(img, tempData, width*3);

		//人脸识别，并用矩形框标示
		storage = cvCreateMemStorage(0);
		
		IplImage* tempImg = cvCreateImage(cvSize(img->width, img->height), 8, 1);

		cvCvtColor(img, tempImg, CV_BGR2GRAY);
		cvEqualizeHist(tempImg, tempImg);
		cvClearMemStorage(storage);

		CvSeq* faces = cvHaarDetectObjects( tempImg, cascade, storage, 1.1, 2, 0, cvSize(200, 200));	//设置可检测到的最小人脸大小为(200,200)
		static int face_counter = 0;

		for (i = 0; i < (faces ? faces->total : 0); i++)
		{
			CvRect* rect = (CvRect*)cvGetSeqElem(faces, i);
			
			char pathName[50] = ".\\faces\\";			//生成文件保存路径
			char faceCounter[5];
			itoa(face_counter, faceCounter, 10);
			strcat(pathName, faceCounter);
			strcat(pathName, ".jpg");
			face_counter++;

			IplImage* face = cvCreateImage(cvSize(150, 150), 8, 3);
					
			cvSetImageROI(img, *rect);					//设置ROI(region of interest)
			cvResize(img, face);						//将ROI区域保存到face图像中
			cvSaveImage(pathName, face);				//保存到文件
			cvResetImageROI(img);						//释放ROI

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

		//检测完图像将IplImage格式转回BYTE
		for (i = 0; i < width*height*3; i++)
			tempData[i] = (img->imageDataOrigin)[i];

		//将之前的翻转在翻转回来
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
		AfxMessageBox("无法加载分类器，请确认后重试！");
	cvReleaseHaarClassifierCascade( &cascade);
}




/*
	函数:
		OnSnapExChange
	输入参数:
		WPARAM wParam			字参数，在消息中为当前可以处理的图像序号		
		LPARAM lParam			没有使用
	输出参数:
		LRESULT						
	说明:
		实现对采集数据的处理和显示
 */

int height=1024;
int width=1280;
int clickTimer = 0; 
//Point caliPoint(640,512);
FILE* pogRecordFile = NULL;

LRESULT CMainFrame::OnSnapExChange(WPARAM wParam, LPARAM lParam)
{
	CGSTATUS status = CG_OK;
	
	CView *pView		= GetActiveView();		//获取当前VIEW视图
	CDC *pDC			= pView->GetDC();		//得到VIEW的DC
	
	BYTE *pLinearAddr = NULL;		//静态内存地址指针
	DWORD dwImageSize = 0;			//图像大小
	HANDLE handle = NULL;			//静态内存描述句柄
	
	dwImageSize = 768 * 576 * 3;	//计算图像大小，由视频输出窗口和视频格式确定

	BYTE *p = NULL, * q = NULL;

	/*
	 *	锁定指定位置的静态内存，
	 *	偏移由图像大小和图像序号确定，锁定大小为图像大小
	 *	用户可以在任何时候锁定指定位置的静态内存，然后通过pLinearAddr指针访问相应的内存。
	 */
	status = CGStaticMemLock(dwImageSize * wParam, dwImageSize, &handle, (PVOID *)&pLinearAddr);
	if (CG_SUCCESS(status)) {
		if (m_pImageBuffer) {
			/*
			 *	将静态内存中的图像传递到用户缓冲区，同时进行格式转换。
			 *	如果静态内存中图像为15、16、32位，则转换为24位。
			 *	由于图像卡采集到静态内存的图像数据是正向存放，
			 *	而Windows中处理的位图数据需要倒置，因此一般还要将图像倒置。
			 */
			CGDataTransform(m_pImageBuffer,		//图像缓冲区
							pLinearAddr,		//静态内存
							768,				//图像宽度
							576,				//图像高度
							24,					//图像位深度
							TRUE				//是否倒置图像
							);
		}
		CGStaticMemUnlock(handle);				//解除静态内存锁定
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
/*************************************图像预处理，提取人眼特征等初步工作***************************************************************/

			preprocess.setThreshold(35);		//--------------------------------21
			preprocess.setScopeHeight(566);
			preprocess.setScopeWidth(384);		//标定图像的左半区域
			preprocess.setWidth(768);
			preprocess.search(m_pImageBuffer,10,0,true);	//对区域进行搜索，粗定位瞳孔中心pupilCenter
															//因为图像的底部有黑色条纹，所以不能从(0,0)开始		
			Point pointL=preprocess.getpupilCenter();

			//判断左眼的位置
			if(pointL.getX()>40&&pointL.getX()<536&&pointL.getY()>40&&pointL.getY()<384)
			{
				//进行直方图分析
				preprocess.setScopeHeight(60);
				preprocess.setScopeWidth(60);
				int thresholdAuto = preprocess.prepupil(m_pImageBuffer,pointL.getX()-30,pointL.getY()-30);	//直方图分析获得阈值

				//搜索瞳孔的中心
				preprocess.setThreshold(thresholdAuto);
				preprocess.setScopeHeight(80);
				preprocess.setScopeWidth(80);
				preprocess.setWidth(768);
				preprocess.search(m_pImageBuffer, pointL.getX()-40,pointL.getY()-40,false);		//在ROI区域内搜索瞳孔中心
				Point point=preprocess.getpupilCenter();
				
				//搜索光斑
				if(point.getX()>=40&&point.getX()<=536&&point.getY()>=40&&point.getY()<=728)
				{
					preprocess.setThreshold(200);//-------------------------200
					preprocess.setScopeHeight(80);
					preprocess.setScopeWidth(80);
					preprocess.setWidth(768);
					preprocess.calGlints2(m_pImageBuffer, point.getX()-40,point.getY()-40);	//获取5个光斑point[5]
					
					if(preprocess.getPointNumber()>=5)
					{
						//画光斑
						for(i=0;i<5;i++)
						{
							if(preprocess.getPoint(i).getX()!=0&&preprocess.getPoint(i).getY()!=0)
							preprocess.setScopeHeight(80);
					        preprocess.setScopeWidth(80);
					        preprocess.setWidth(768);
							preprocess.blackened(m_pImageBuffer,preprocess.getPoint(i).getX(),preprocess.getPoint(i).getY(),5);	//????
						}
						
						//进行中值滤波
						BYTE * picture1;
						BYTE * picture2;
						picture1=(BYTE*)malloc(80*80*3*sizeof(BYTE));
						picture2=(BYTE*)malloc(80*80*3*sizeof(BYTE));
						memset(picture1,0,80*80*3*sizeof(BYTE));
						memset(picture2,0,80*80*3*sizeof(BYTE));

						//把要处理的图像采到picture1中
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

						//转换成openCV使用的数组格式
						CvSize n_size = cvSize(80,80);
						IplImage* frame = cvCreateImageHeader( n_size, IPL_DEPTH_8U, 3 );
						frame->imageData = (char *)picture1; 
							
						IplImage* frame2 = cvCreateImageHeader( n_size, IPL_DEPTH_8U, 3 );
						frame2->imageData = (char *)picture2;

						//中值滤波
						cvSmooth(frame,frame2,CV_MEDIAN,9,9,0,0);


						//将滤波后的图像放回到原始图像中
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
						
						//搜索瞳孔
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
							//在图像中画出光斑点中心和瞳孔中心
							for(i=0;i<5;i++)
							{
								draw3(m_pImageBuffer,preprocess.getPoint(i).getX(),preprocess.getPoint(i).getY(),i);
							}
							draw3(m_pImageBuffer,point.getX(),point.getY(),5);
							drawrect(m_pImageBuffer, point.getX(),point.getY());

							//坐标转化
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


/**********************************************************人眼特征提取结束**************************************************************/

							
							//如果是获取参数，那么把数据输出
							if(CPublic::stateTag==1 && NULL!=CPublic::g_pBestAlpha && NULL!=CPublic::g_pCaliPoint)
							{

								mapping.setHeight(height);
								mapping.setWidth(width);

								//进行映射
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


							//进行坐标映射(或者Button点击)
							else if(CPublic::stateTag==2)
							{							
								//进行赋值操作
								mapping.setHeight(height);
								mapping.setWidth(width);

								//进行映射
								mapping.calGazePoint(pointbobo,m_bestAlph,m_bestVector);		//粗略获取当前注视点坐标

								//判断当前注视点所在屏幕子区域
								if(mapping.getGazePoint().getX()!=0&&mapping.getGazePoint().getY()!=0)
								{							
									float minDistance = 65535.0;
									float curDistance = 65535.0;
									int aIndex=0;
									for (int i=0; i<CPublic::g_CaliPointNumber; i++)//选择离当前点最近的子区域的alpha值作为当前alpha
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
									
									//在更新最佳alpha以及最佳位移矢量之后，重新计算注视点坐标
									mapping.calGazePoint(pointbobo,m_bestAlph,m_bestVector);
									Point gazePoint = mapping.getGazePoint();

									//若开启键盘，则当鼠标移动到某个键的区域时，令光标停留在该键中心位置
									if (CPublic::NumFlag == FALSE && CPublic::AlpFlag == FALSE)	//没有开启键盘
									{
										POINT	curPoint;				//获取光标当前位置
										GetCursorPos(&curPoint);
										if (sqrt((curPoint.x-gazePoint.getX())*(curPoint.x-gazePoint.getX()) + (curPoint.y-gazePoint.getY())*(curPoint.y-gazePoint.getY())) > 30)
											SetCursorPos(gazePoint.getX(), gazePoint.getY());
									}

									else if (CPublic::NumFlag) //开启数字键盘
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

									else if (CPublic::AlpFlag) //开启全键盘
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
									
									

								/*************	人眼控制鼠标上下左右移动
									//获取鼠标当前位置
									Point	gazePoint;
									POINT	curPoint;
									GetCursorPos(&curPoint);
									gazePoint = mapping.getGazePoint();	//获取注视点

									if (gazePoint.getX() < 60)				//边缘
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

									
									  //判断注视点与当前点的位置关系
									if (gazePoint.getX() - curPoint.x >= 60)
									{
									  if (gazePoint.getY() - curPoint.y >= 60)
									  {
											SetCursorPos(curPoint.x+20, curPoint.y+20);	//右上
									  }
									  else if(gazePoint.getY() - curPoint.y >= 60)
									  {
											SetCursorPos(curPoint.x+20, curPoint.y);		//正右
									  }
									  else
									  {
											SetCursorPos(curPoint.x+20, curPoint.y-20);	//右下
									  }
									}
									else if (gazePoint.getX() - curPoint.x >= -60)
									{
									  if (gazePoint.getY() - curPoint.y >= 60)
									  {
											SetCursorPos(curPoint.x, curPoint.y+20);		//正上
									  }
									  else if(gazePoint.getY() - curPoint.y >= -60)
									  {
											SetCursorPos(curPoint.x, curPoint.y);		//不变
									  }
									  else
									  {
											SetCursorPos(curPoint.x, curPoint.y-20);		//正下
									  }
									}
									else
									{
									  if (gazePoint.getY() - curPoint.y >= 60)
									  {
											SetCursorPos(curPoint.x-20, curPoint.y+20);	//左上
									  }
									  else if(gazePoint.getY() - curPoint.y >= -60)
									  {
											SetCursorPos(curPoint.x-20, curPoint.y);		//正左
									  }
									  else
									  {
											SetCursorPos(curPoint.x-20, curPoint.y-20);	//左下
									  }
									}	
					*************/
									fprintf(pogRecordFile,"%f	%f\n",mapping.getGazePoint().getX(),mapping.getGazePoint().getY());
									clickTimer++;
									if (30 == clickTimer)		//注视多久按键		
									{
										mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
                                        mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0); 
										clickTimer = 0;
									}
								}						
							}
							//精度测试
							else if (CPublic::stateTag==3)
							{
								//进行赋值操作
								mapping.setHeight(height);
								mapping.setWidth(width);
								//进行映射，粗略计算当前注视点坐标
								mapping.calGazePoint(pointbobo, m_bestAlph,m_bestVector);
								//判断当前注视点坐在屏幕子区域
								if(mapping.getGazePoint().getX()!=0&&mapping.getGazePoint().getY()!=0)
								{							
									float minDistance = 65535.0;
									float curDistance = 65535.0;
									int aIndex=0;
									for (int i=0; i<CPublic::g_CaliPointNumber; i++)//选择离当前点最近的子区域的alpha值作为当前alpha
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
									
									//在更新最佳alpha以及最佳位移矢量之后，重新计算注视点坐标
									mapping.calGazePoint(pointbobo,m_bestAlph,m_bestVector);
									SetCursorPos(mapping.getGazePoint().getX(),mapping.getGazePoint().getY());
									float errorDistance = 0;
									errorDistance = sqrt((CPublic::g_pCurTestPoint->getX()-mapping.getGazePoint().getX())*(CPublic::g_pCurTestPoint->getX()-mapping.getGazePoint().getX())+(CPublic::g_pCurTestPoint->getY()-mapping.getGazePoint().getY())*(CPublic::g_pCurTestPoint->getY()-mapping.getGazePoint().getY()));
                                    fprintf(CPublic::fpTestCur,"%f	%f	%f\n",CPublic::g_pCurTestPoint->getX()-mapping.getGazePoint().getX(),CPublic::g_pCurTestPoint->getY()-mapping.getGazePoint().getY(),errorDistance);
                                    
								}						

							}
							//广告实验映射部分
							else if (CPublic::stateTag==4)
							{
								//进行赋值操作
								mapping.setHeight(height);
								mapping.setWidth(width);

								//进行映射，粗略计算人眼注视点的坐标
								mapping.calGazePoint(pointbobo,m_bestAlph,m_bestVector);
								//判断注视点所在屏幕子区域
								if(mapping.getGazePoint().getX()!=0&&mapping.getGazePoint().getY()!=0)
								{							
									float minDistance = 65535.0;
									float curDistance = 65535.0;
									int aIndex=0;

									for (int i=0; i<CPublic::g_CaliPointNumber; i++)//选择离当前点最近的子区域的alpha值作为当前alpha
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

		//在视图客户区显示图像
		StretchDIBits(pDC->GetSafeHdc(),
						0,
						0,
						768,					//显示窗口宽度
						576,					//显示窗口高度
						0,
						0,
						768,					//图像宽度
						576,					//图像高度
						m_pImageBuffer,			//图像缓冲区				
						m_pBmpInfo,				//BMP图像描述信息
						DIB_RGB_COLORS,
						SRCCOPY
						);	
	
	}//第一个if	
	pView->ReleaseDC(pDC);	
	return 1;
}//函数结束

/*
 *	关闭整个框架的时候，进行响应
 *	用户在没有通过菜单项正常关闭图像卡采集，	
 *	而直接关闭应用程序时，应保证图像卡采集被关闭
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
 * 响应CardCtrl下拉菜单中的negative按钮
 * 重置图像反色标志
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
 *	响应状态栏的第一个按钮
 *	设置stateTag为0，完成参数获取
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
 *	响应状态栏的最后一个按钮
 *	功能：将stateTag设置为2，进行坐标映射
 */
void CMainFrame::OnBtmapping() 
{
	// TODO: Add your command handler code here
	CPublic::stateTag = 2;
	pogRecordFile = fopen("pogRecordFile.txt","w");
}



/*
 *	状态栏的2*2参数提取
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
 * Acctest 菜单
 * 进入精度测试界面
 */
void CMainFrame::OnAccutest() 
{
	// TODO: Add your command handler code here
	CActDlg *pActDlg = new CActDlg;
	pActDlg->Create(IDD_ACT,this);
	pActDlg->ShowWindow(SW_SHOW);
}

/*
 * 响应菜单栏下边的状态栏中的3*3矩阵参数获取
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
 *	响应菜单栏下边的状态栏中的4*4矩阵参数获取
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
 * 	响应菜单栏下边的状态栏中的5*5矩阵参数获取
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
 *	响应菜单栏下边的状态栏中的6*6矩阵参数获取
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

//或许现有的经验参数
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
 * 响应ButtonTest菜单按钮
 * 进入按钮测试界面，进行人眼输入
 */
void CMainFrame::OnBtest()
{

   CButtonTestDlg* pButtonTestDlg = new CButtonTestDlg;
   pButtonTestDlg->Create(IDD_BTTEST,this);
   pButtonTestDlg->ShowWindow(SW_SHOW);

}



/*
 *	响应GridTest下拉菜单下的2*2按钮
 *	进入2*2的人眼关注度试验
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
        cvNamedWindow( "AdsTest", 1 );//创建窗口
		cvMoveWindow("AdsTest",0,0);//显示窗口的位置
        cvShowImage( "AdsTest", pImg );//显示图像
		
        cvWaitKey(0); //等待按键
		
        cvDestroyWindow( "AdsTest" );//销毁窗口
        cvReleaseImage( &pImg ); //释放图像
    }
}

/*
 *	响应GridTest下拉菜单下的3*3按钮
 *	进入3*3的人眼关注度试验
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
        cvNamedWindow( "AdsTest", 1 );//创建窗口
		cvMoveWindow("AdsTest",0,0);//显示窗口的位置
        cvShowImage( "AdsTest", pImg );//显示图像
		
        cvWaitKey(0); //等待按键
		
        cvDestroyWindow( "AdsTest" );//销毁窗口
        cvReleaseImage( &pImg ); //释放图像
    }
}

/*
 *	响应GridTest下拉菜单下的4*4按钮
 *	进入4*4的人眼关注度试验
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
        cvNamedWindow( "AdsTest", 1 );//创建窗口
		cvMoveWindow("AdsTest",0,0);//显示窗口的位置
        cvShowImage( "AdsTest", pImg );//显示图像
		
        cvWaitKey(0); //等待按键
		
        cvDestroyWindow( "AdsTest" );//销毁窗口
        cvReleaseImage( &pImg ); //释放图像
    }	
}

/*
 *	响应GridTest下拉菜单下的5*5按钮
 *	进入5*5的人眼关注度试验
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
        cvNamedWindow( "AdsTest", 1 );//创建窗口
		cvMoveWindow("AdsTest",0,0);//显示窗口的位置
        cvShowImage( "AdsTest", pImg );//显示图像
		
        cvWaitKey(0); //等待按键
		
        cvDestroyWindow( "AdsTest" );//销毁窗口
        cvReleaseImage( &pImg ); //释放图像
    }
}

/*
 *	响应GridTest下拉菜单下的6*6按钮
 *	进入6*6的人眼关注度试验
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
        cvNamedWindow( "AdsTest", 1 );//创建窗口
		cvMoveWindow("AdsTest",0,0);//显示窗口的位置
        cvShowImage( "AdsTest", pImg );//显示图像
		
        cvWaitKey(0); //等待按键
		
        cvDestroyWindow( "AdsTest" );//销毁窗口
        cvReleaseImage( &pImg ); //释放图像
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
