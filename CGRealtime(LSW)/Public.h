// Public.h: interface for the CPublic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBLIC_H__8A8CF828_4F39_43A1_8C2A_C9268D0EF452__INCLUDED_)
#define AFX_PUBLIC_H__8A8CF828_4F39_43A1_8C2A_C9268D0EF452__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Point.h"
class CPublic  
{
public:
	CPublic();
	virtual ~CPublic();
	static void calAlph(FILE *fp,float *p);
public:
	static Point* g_pCaliPoint;				//��¼��ǰУ׼���ָ��
	static float* g_pBestAlpha;				//��¼��ǰ���alphaֵ��ָ��
	static Point* g_pBestVector;			//��¼��ǰ���vectorֵ��ָ��
	static int g_CaliPointNumber;			//��¼��ǰ����У׼����Ŀ(2x2��3x3��4x4��...)
	static Point* g_curCaliPoints;			//ָ��ǰ��ʹ�õ�У׼������
	static FILE* fpCur;						//ָ��ǰ���alphaֵ���ļ�
	static char* curFile;					//ָ��ǰ���alphaֵ���ļ���
	static float* g_curBestAlpha;			//ָ��ǰ��g_BestAlpha����
	static Point* g_curBestVector;			//ָ��ǰ��g_BestVector����
	static int g_curGridTestPointNumber;	//��ǰGridTest��Ŀ�����
	static Point* g_curGridTestPoints;		//ָ��ʱĿ�������

	static float  g_BestAlpha[4];			//alpha����(2X2)
	static float  g_BestAlpha3X3[9];		//alpha����(3X3)
	static float  g_BestAlpha4X4[4*4];		//alpha����(4X4)
	static float  g_BestAlpha5X5[5*5];		//alpha����(5X5)
	static float  g_BestAlpha6X6[6*6];		//alpha����(6X6)

	/*������Point(float x, float y)���洢ʸ��vector*/
	static Point g_BestVector2x2[4];			//vector����(2x2)
	static Point g_BestVector3x3[9];			//vector����(3x3)
	static Point g_BestVector4x4[16];			//vector����(4x4)
	static Point g_BestVector5x5[25];			//vector����(5x5)
	static Point g_BestVector6x6[36];			//vector����(6x6)

	static Point  g_caliPoint[4];			//У׼������(2X2)
	static Point  g_caliPoint3X3[9];		//У׼������(3X3)
	static Point  g_caliPoint4X4[4*4];		//У׼������(4X4)
	static Point  g_caliPoint5X5[5*5];		//У׼������(5X5)
	static Point  g_caliPoint6X6[6*6];		//У׼������(6X6)

	static FILE *fp[4];						//���alphaֵ���ļ�����(2X2)
	static FILE *fp3X3[9];					//���alphaֵ���ļ�����(3X3)
	static FILE *fp4X4[4*4];				//���alphaֵ���ļ�����(4X4)
	static FILE *fp5X5[5*5];				//���alphaֵ���ļ�����(5X5)
	static FILE *fp6X6[6*6];				//���alphaֵ���ļ�����(6X6)

	
	static char* fileName[4];				//���alphaֵ���ļ�������(2X2)
	static char* fileName3X3[9];			//���alphaֵ���ļ�������(3X3)
	static char* fileName4X4[4*4];			//���alphaֵ���ļ�������(4X4)
	static char* fileName5X5[5*5];			//���alphaֵ���ļ�������(5X5)
	static char* fileName6X6[6*6];			//���alphaֵ���ļ�������(6X6)

	static int stateTag;					//״̬��ʶ

	static Point g_TestPoint[9];			//���Ȳ��Ե�����
	static Point* g_pCurTestPoint;			//ָ��ǰ���Ȳ��Ե�
	static FILE* fpTest[9];					//���Ե�����ļ�����
	static FILE* fpTestCur;					//ָ��ǰ����ļ�
	static char* testFileName[9];			//�������ļ����ļ���
	static char* curTestFileName;			//ָ��ǰ����ļ����ļ���

	static bool saveFlag;					//��ʾ�����alpha�����Ƿ���Ҫ�����浽�ļ���


};

#endif // !defined(AFX_PUBLIC_H__8A8CF828_4F39_43A1_8C2A_C9268D0EF452__INCLUDED_)
