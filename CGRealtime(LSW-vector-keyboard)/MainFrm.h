// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__EB02BF30_EAF6_4BC5_9BD4_B266FB8C9988__INCLUDED_)
#define AFX_MAINFRM_H__EB02BF30_EAF6_4BC5_9BD4_B266FB8C9988__INCLUDED_

#include "CaliDlg2X2.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "CGVideo.h"
#include "Preprocess.h"
#include "Calibration.h"
#include "Mapping.h"
#include "Point.h"	// Added by ClassView

#include "cv.h"
#include "highgui.h"

#define WM_SNAP_EX_CHANGE		(WM_USER + 100)


class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public://HK

	Calibration calibration;
	Mapping mapping;
	Preprocess preprocess;

	//for facedetection
	CvHaarClassifierCascade *cascade;			//特征器分类
	CvMemStorage *storage;						//内存存储块
	void detect_and_draw( BYTE* m_PData, int width, int height);		//检测和标识函数

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
//  int statetag;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSnapexOpen();
	afx_msg void OnUpdateSnapexOpen(CCmdUI* pCmdUI);
	afx_msg void OnSnapexStart();
	afx_msg void OnUpdateSnapexStart(CCmdUI* pCmdUI);
	afx_msg void OnSnapexStop();
	afx_msg void OnUpdateSnapexStop(CCmdUI* pCmdUI);
	afx_msg void OnSnapexClose();
	afx_msg void OnUpdateSnapexClose(CCmdUI* pCmdUI);
	afx_msg LRESULT OnSnapExChange(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnNegative();
	afx_msg void OnUpdateNegative(CCmdUI* pCmdUI);
	afx_msg void OnHkstop();
	afx_msg void OnBtmapping();
	afx_msg void OnBtcalib();
	afx_msg void OnAccutest();
	afx_msg void OnCalib3x3();
	afx_msg void OnBtcalib4x4();
	afx_msg void OnBtcalib5x5();
	afx_msg void OnBtcalib6x6();
	afx_msg void OnBtest();
	afx_msg void OnGridtest2x2();
	afx_msg void OnGridtest3x3();
	afx_msg void OnGridtest4x4();
	afx_msg void OnGridtest5x5();
	afx_msg void OnGridtest6x6();
	afx_msg void OnKeyboard();
	afx_msg void MyParameter();
	afx_msg void OnFacedetect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	Point m_caliPoint;	//校准点
	float m_bestAlph;	//当前最佳alpha值
	Point m_bestVector; //当前最佳位移矢量
	HCG	m_hcg;			//图像卡句柄
	
	BOOL m_bOpen;		//snapEx打开标志
	BOOL m_bStart;		//snapEx开始标志

	BOOL m_bNegative;	//反色标志
	
	BITMAPINFO *m_pBmpInfo;  
	BYTE *m_pImageBuffer;
    char m_chBmpBuf[2048];
	

	static int CALLBACK SnapThreadCallbackEx(SNAP_INFO *pInfo);
		
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__EB02BF30_EAF6_4BC5_9BD4_B266FB8C9988__INCLUDED_)
