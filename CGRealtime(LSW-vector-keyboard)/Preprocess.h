// Preprocess.h: interface for the Preprocess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PREPROCESS_H__C5DCE41C_93E2_41E0_8DF0_33AD86EF206C__INCLUDED_)
#define AFX_PREPROCESS_H__C5DCE41C_93E2_41E0_8DF0_33AD86EF206C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Point.h"
#include <windows.h>
#include <math.h>
#include "cv.h"
#include "highgui.h"
#define M_PI  3.14159265358979323846


class Preprocess  
{
private:
	int		NumOfVertex;				//记录搜索瞳孔边界点的个数
	int		Direction[8][2];
	bool	backup[576][768];			//这个是做广度搜索的标记用的
	Point	queue[4000];				//做广度搜索的队列
	int		head;						//队列头部
	int		tail;						//队列尾部
	long	log[200][2];				//记录找到的点片			//改变了
	bool    logTag[200];                 //找光斑时标记点片是否已经被分类
	int		pointCount[200];			//记录每个点片中的个数
	int		nowCount;					//
	long	now;
	Point	point[5];					//存放找到的五个光斑亮点
	Point	pupilCenter;
	int		threshold;
	int		queueCount;
	int		width;						//大图像的宽（在运行时不变）
	int		height;						//大图像的高（在运行时不变）
	int		scope_width;				//搜索区域的宽（会变换）
	int		scope_height;				//搜索区域的高（会变化）
	int		leave;						//剔除假点后剩下的点的个数
	bool	tag[5];						//标记是否找到这五个点
	bool	secondS;					//是否在匹配余下的点
	bool	weed;						//是否有点剔除
	int		pointNumber;				//点的个数
	int		fault[5];					//剔除点时的错误标记
	IplImage* pImg;

public:
	void refine(BYTE *m_pImageBuffer);
	int getPointCount(int i)
	{
		return pointCount[i];
	}
	long	max;
	long getMax()
	{
		return max;
	}
	void setScopeWidth(int i)
	{
		scope_width=i;
	}
	void setScopeHeight(int i)
	{
		scope_height=i;
	}
	void setPupilX(float xx)
	{
		pupilCenter.setX(xx);
	}
	void setPupilY(float yy)
	{
		pupilCenter.setY(yy);
	}
	void setImage(IplImage* image)
	{
	  pImg = image;
	}
	IplImage* getImage()
    {
		return pImg;
	}
	
	void searchHelp(BYTE *m_pImageBuffer,int scope_heigth,int scope_width,int x ,int y , int i,int j,bool transform);
	Point getpupilCenter()
	{
		return pupilCenter;
	}
	int getNowCount()
	{
		return nowCount;
	}
	Point getPoint(int i)
	{
		if(i>=0&&i<=4)
		{
			return point[i];
		}
		else
			return Point(0,0);
	}
	int getPointNumber()
	{
		return pointNumber;
	}
	void calGlints2(BYTE *m_pImageBuffer ,int x,int y);
	/********************************************************************************************
	*	功能：搜索光斑
	*	参数：m_pImageBuffer		图像缓冲区
	*		  x,y					搜索的起始地址
	*	条件：要先设定阈值，然后设定搜索的范围
	*
	*********************************************************************************************/
	void calGlints(BYTE *m_pImageBuffer ,int x,int y); 
	/*
	*
	*
	*/
	void glintSearch(BYTE *m_pImageBuffer ,int x,int y,int i,int j);

	void search(BYTE *m_pImageBuffer , int x,int y,bool transform);

	void setThreshold(int i)
	{
		threshold = i;	
	}
	void setWidth(int x)
	{
		width=x;
	}
	/****************************************************************
	*
	*	功能：寻找瞳孔的边界，进行椭圆拟合，返回瞳孔中心点
	*	参数：m_pImageBuffer		图像缓冲区
	*		  x，y					搜索区域的首地址
	*	条件：调用之前先设定阈值和搜索范围
	*
	*****************************************************************/
	Point pupil(BYTE *m_pImageBuffer,int x,int y);

	void PupilBFS(BYTE *m_pImageBuffer,int xi,int yi);
	void blackened(BYTE *m_pImageBuffer,int xi,int yi,int max);
	/**************************************************************
	*
	*	功能：对图像做平滑处理
	*	参数：data				图像缓冲区
	*		  x,y				处理块的起点
	*
	***************************************************************/
	bool smooth(BYTE *data,int x,int y);
	void detect();
	/*直方图分析(整幅图像的分析，不区分上下)*/
	int prepupil(BYTE *data,int x,int y);
	Point fill(BYTE *data,int x,int y,float r);
	/**************************************************************
	*
	*	功能:	眼睛下半部分的直方图分析
	*	参数:	data	图像缓冲区
	*			x,y		瞳孔中心
	*
	***************************************************************/
	int HistogramDown(BYTE *data,int x,int y);
	/**************************************************************
	*
	*	功能:	眼睛上半部分的直方图分析
	*	参数:	data	图像缓冲区
	*			x,y		瞳孔中心
	*
	***************************************************************/
	int HistogramUp(BYTE *data,int x,int y);

public:
	Preprocess();
	virtual ~Preprocess();

};

#endif // !defined(AFX_PREPROCESS_H__C5DCE41C_93E2_41E0_8DF0_33AD86EF206C__INCLUDED_)
