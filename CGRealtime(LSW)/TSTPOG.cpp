// TSTPOG.cpp : implementation file
//

#include "stdafx.h"
#include "CGRealtime.h"
#include "TSTPOG.h"
#include "Public.h"

#include <stdio.h>
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTSTPOG dialog


CTSTPOG::CTSTPOG(CWnd* pParent /*=NULL*/)
	: CDialog(CTSTPOG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTSTPOG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	//SetWindowPos(&wndTopMost,CPublic::g_pCurTestPoint->getX(),CPublic::g_pCurTestPoint->getY(),0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
}


void CTSTPOG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTSTPOG)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTSTPOG, CDialog)
	//{{AFX_MSG_MAP(CTSTPOG)
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTSTPOG message handlers

void CTSTPOG::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialog::PostNcDestroy();
}

void CTSTPOG::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	//this->SetWindowPos(&wndTopMost,(int)CPublic::g_pCurTestPoint->getX()-100,(int)CPublic::g_pCurTestPoint->getY()-120,0,0,SWP_NOSIZE|SWP_SHOWWINDOW);

	POINT curPt;
	GetCursorPos(&curPt);
	
	this->SetWindowPos(&wndTopMost, curPt.x - 51, curPt.y - 75, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
}

void CTSTPOG::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(flag == 1)		//flag == 1，
	{
		//关闭窗口
		CDialog::OnCancel();

		if (NULL != CPublic::fpCur)
		{
			fclose(CPublic::fpCur);
		}
		float *fp_data;
		fp_data=(float*)malloc(3000*sizeof(float));
		if(fp_data!=NULL)
		{
		}
		else
		{
			MessageBox("分配存储空间失败！");
			free(fp_data);
			return;
		}
		
		if ((CPublic::fpCur=fopen(CPublic::curFile,"rb"))!=NULL)
		{
			CPublic::calAlph(CPublic::fpCur,fp_data);		//设置 *CPublic::g_pBestAlpha 和 *CPublic::g_pBestVector
		}
		free(fp_data);
		
		if (NULL != CPublic::fpCur)
		{
			fclose(CPublic::fpCur);
		}
		
		CPublic::stateTag=0;
		
		CString tempStr1;
		CString tempStr2;
		tempStr1.Format("%f",*CPublic::g_pBestAlpha);
		tempStr2.Format("(%f,%f)",CPublic::g_pBestVector->getX(),CPublic::g_pBestVector->getY());
		tempStr1 = "Result: " + tempStr1 + " " + tempStr2;  
		MessageBox(tempStr1);
		printf("%s\n",tempStr1);

		flag = 0;
	}
	else if (flag = 2)
	{
		//关闭窗口
		CDialog::OnCancel();

		CPublic::stateTag=0;
		if (NULL != CPublic::fpTestCur)
		{
			fclose(CPublic::fpTestCur);
		}
		
		flag = 0;
	}

	CDialog::OnLButtonDown(nFlags, point);
}
