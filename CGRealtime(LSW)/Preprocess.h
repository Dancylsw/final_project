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
	int		NumOfVertex;				//��¼����ͫ�ױ߽��ĸ���
	int		Direction[8][2];
	bool	backup[576][768];			//���������������ı���õ�
	Point	queue[4000];				//����������Ķ���
	int		head;						//����ͷ��
	int		tail;						//����β��
	long	log[200][2];				//��¼�ҵ��ĵ�Ƭ			//�ı���
	bool    logTag[200];                 //�ҹ��ʱ��ǵ�Ƭ�Ƿ��Ѿ�������
	int		pointCount[200];			//��¼ÿ����Ƭ�еĸ���
	int		nowCount;					//
	long	now;
	Point	point[5];					//����ҵ�������������
	Point	pupilCenter;
	int		threshold;
	int		queueCount;
	int		width;						//��ͼ��Ŀ�������ʱ���䣩
	int		height;						//��ͼ��ĸߣ�������ʱ���䣩
	int		scope_width;				//��������Ŀ���任��
	int		scope_height;				//��������ĸߣ���仯��
	int		leave;						//�޳��ٵ��ʣ�µĵ�ĸ���
	bool	tag[5];						//����Ƿ��ҵ��������
	bool	secondS;					//�Ƿ���ƥ�����µĵ�
	bool	weed;						//�Ƿ��е��޳�
	int		pointNumber;				//��ĸ���
	int		fault[5];					//�޳���ʱ�Ĵ�����
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
	*	���ܣ��������
	*	������m_pImageBuffer		ͼ�񻺳���
	*		  x,y					��������ʼ��ַ
	*	������Ҫ���趨��ֵ��Ȼ���趨�����ķ�Χ
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
	*	���ܣ�Ѱ��ͫ�׵ı߽磬������Բ��ϣ�����ͫ�����ĵ�
	*	������m_pImageBuffer		ͼ�񻺳���
	*		  x��y					����������׵�ַ
	*	����������֮ǰ���趨��ֵ��������Χ
	*
	*****************************************************************/
	Point pupil(BYTE *m_pImageBuffer,int x,int y);

	void PupilBFS(BYTE *m_pImageBuffer,int xi,int yi);
	void blackened(BYTE *m_pImageBuffer,int xi,int yi,int max);
	/**************************************************************
	*
	*	���ܣ���ͼ����ƽ������
	*	������data				ͼ�񻺳���
	*		  x,y				���������
	*
	***************************************************************/
	bool smooth(BYTE *data,int x,int y);
	void detect();
	/*ֱ��ͼ����(����ͼ��ķ���������������)*/
	int prepupil(BYTE *data,int x,int y);
	Point fill(BYTE *data,int x,int y,float r);
	/**************************************************************
	*
	*	����:	�۾��°벿�ֵ�ֱ��ͼ����
	*	����:	data	ͼ�񻺳���
	*			x,y		ͫ������
	*
	***************************************************************/
	int HistogramDown(BYTE *data,int x,int y);
	/**************************************************************
	*
	*	����:	�۾��ϰ벿�ֵ�ֱ��ͼ����
	*	����:	data	ͼ�񻺳���
	*			x,y		ͫ������
	*
	***************************************************************/
	int HistogramUp(BYTE *data,int x,int y);

public:
	Preprocess();
	virtual ~Preprocess();

};

#endif // !defined(AFX_PREPROCESS_H__C5DCE41C_93E2_41E0_8DF0_33AD86EF206C__INCLUDED_)
