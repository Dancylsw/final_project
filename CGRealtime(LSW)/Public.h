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
	static Point* g_pCaliPoint;				//记录当前校准点的指针
	static float* g_pBestAlpha;				//记录当前最佳alpha值的指针
	static Point* g_pBestVector;			//记录当前最佳vector值的指针
	static int g_CaliPointNumber;			//记录当前所用校准点数目(2x2或3x3或4x4或...)
	static Point* g_curCaliPoints;			//指向当前所使用的校准点数组
	static FILE* fpCur;						//指向当前存放alpha值的文件
	static char* curFile;					//指向当前存放alpha值的文件名
	static float* g_curBestAlpha;			//指向当前的g_BestAlpha数组
	static Point* g_curBestVector;			//指向当前的g_BestVector数组
	static int g_curGridTestPointNumber;	//当前GridTest的目标点数
	static Point* g_curGridTestPoints;		//指向当时目标点数组

	static float  g_BestAlpha[4];			//alpha数组(2X2)
	static float  g_BestAlpha3X3[9];		//alpha数组(3X3)
	static float  g_BestAlpha4X4[4*4];		//alpha数组(4X4)
	static float  g_BestAlpha5X5[5*5];		//alpha数组(5X5)
	static float  g_BestAlpha6X6[6*6];		//alpha数组(6X6)

	/*用类型Point(float x, float y)来存储矢量vector*/
	static Point g_BestVector2x2[4];			//vector数组(2x2)
	static Point g_BestVector3x3[9];			//vector数组(3x3)
	static Point g_BestVector4x4[16];			//vector数组(4x4)
	static Point g_BestVector5x5[25];			//vector数组(5x5)
	static Point g_BestVector6x6[36];			//vector数组(6x6)

	static Point  g_caliPoint[4];			//校准点数组(2X2)
	static Point  g_caliPoint3X3[9];		//校准点数组(3X3)
	static Point  g_caliPoint4X4[4*4];		//校准点数组(4X4)
	static Point  g_caliPoint5X5[5*5];		//校准点数组(5X5)
	static Point  g_caliPoint6X6[6*6];		//校准点数组(6X6)

	static FILE *fp[4];						//存放alpha值的文件数组(2X2)
	static FILE *fp3X3[9];					//存放alpha值的文件数组(3X3)
	static FILE *fp4X4[4*4];				//存放alpha值的文件数组(4X4)
	static FILE *fp5X5[5*5];				//存放alpha值的文件数组(5X5)
	static FILE *fp6X6[6*6];				//存放alpha值的文件数组(6X6)

	
	static char* fileName[4];				//存放alpha值的文件名数组(2X2)
	static char* fileName3X3[9];			//存放alpha值的文件名数组(3X3)
	static char* fileName4X4[4*4];			//存放alpha值的文件名数组(4X4)
	static char* fileName5X5[5*5];			//存放alpha值的文件名数组(5X5)
	static char* fileName6X6[6*6];			//存放alpha值的文件名数组(6X6)

	static int stateTag;					//状态标识

	static Point g_TestPoint[9];			//精度测试点数组
	static Point* g_pCurTestPoint;			//指向当前精度测试点
	static FILE* fpTest[9];					//测试点误差文件数组
	static FILE* fpTestCur;					//指向当前误差文件
	static char* testFileName[9];			//存放误差文件的文件名
	static char* curTestFileName;			//指向当前误差文件的文件名

	static bool saveFlag;					//标示计算的alpha参数是否需要被保存到文件中


};

#endif // !defined(AFX_PUBLIC_H__8A8CF828_4F39_43A1_8C2A_C9268D0EF452__INCLUDED_)
