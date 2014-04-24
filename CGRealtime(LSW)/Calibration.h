// alibration.h: interface for the Calibration class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALIBRATION_H__5F42B651_DB17_44FB_A3CF_2FDA3209398D__INCLUDED_)
#define AFX_ALIBRATION_H__5F42B651_DB17_44FB_A3CF_2FDA3209398D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include "cv.h"
#include "highgui.h"

#include "Point.h"
class Calibration  
{
public:
	Point s[6];
	Point e[6];
	float a[6];
	float b[6];
	//������Ļ�ϵĵ�
	Point Screen(Point x);
	//�õ�У׼����
	void calibrate();
	//��У׼���ע�ӵ����괫��
	void setE(Point ee[6]);
	//����Ļע�ӵ���Ļ���괫��
	void setS(Point ss[6]);
	Point getS(int i)
	{
		return s[i];
	}
	Point getE(int i)
	{
		return e[i];
	}
	
public:
	Calibration();
	virtual ~Calibration();
	
};

#endif // !defined(AFX_ALIBRATION_H__5F42B651_DB17_44FB_A3CF_2FDA3209398D__INCLUDED_)
