// Public.cpp: implementation of the CPublic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CGRealtime.h"
#include "Public.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPublic::CPublic()
{

}

CPublic::~CPublic()
{

}

void CPublic:: calAlph(FILE *fp,float *p)
{
	int j=0,i;

	//将文件里的alpha值，位移矢量(x,y)保存到指针p中
	for(i=0;i<3000;i++)
	{
		j=fscanf(fp,"%f",&p[i]);
		if(j!=1)
		{
			break;
		}
	}
	fclose(fp);

	//如果读取文件为空
	if(i==0)
	{
		*CPublic::g_pBestAlpha = 2.0;
		*CPublic::g_pBestVector = Point(0,0);
	}
	
	else
	{
		j=i;				//alpha和x，y的总数
		int counter = 0;	//三元组(alpha,x,y)的个数

		int k;
		float al = 0;
		float ax = 0;
		float ay = 0;

		float pl[1000];				// alpha
		float px[1000];				// x
		float py[1000];				// y

		for (i = 0; i < j;)			//将alpha，x，y分别存到三个数组
		{
			pl[counter] = p[i++];
			px[counter] = p[i++];
			py[counter] = p[i++];
			counter ++;
		}
		
		//计算alpha平均值
		j = counter;
		for(k = 0; k < 4; k++)
		{
			al = 0;

			for(i = 0; i < j; i++)
			{
				al += pl[i];
			}

			if(j > 0)
			{
				al = al/j;		//对alpha求平均值

				int z = 0;
				for(i = 0; i < j; i++)
				{
					if(abs(al - pl[i]) < 0.5)	//将与alpha平均值差值小于0.5的alpha值保存，进行再次平均
					{
						pl[z] = pl[i];
						z++;
					}
				}
				j = z;
			}
			else
			{
				al = 2.0;
				break;
			}	
		}
		
		//对位移矢量x求平均值
		j = counter;
		for (k = 0; k < 3; k++)
		{
			ax = 0;

			for (i = 0; i < j; i++)
			{
				ax += px[i];
			}

			if (j > 0)
			{
				ax = ax/j;
				
				int z = 0;
				for (i = 0; i < j; i++)
				{
					if (abs(ax - px[i]) < 10)
					{
						px[z] = px[i];
						z++;
					}
				}
				j = z;
			}
			else
			{
				ax = 0;
				break;
			}
		}

		//对位移矢量y求平均值
		j = counter;
		for (k = 0; k < 3; k++)
		{
			ay = 0;
			
			for (i = 0; i < j; i++)
			{
				ay += py[i];
			}
			
			if (j > 0)
			{
				ay = ay/j;
				
				int z = 0;
				for (i = 0; i < j; i++)
				{
					if (abs(ay - py[i]) < 10)
					{
						py[z] = py[i];
						z++;
					}
				}
				j = z;
			}
			else
			{
				ay = 0;
				break;
			}
		}

		*CPublic::g_pBestAlpha = al;
		*CPublic::g_pBestVector = Point(ax,ay);
	}	
}

int CPublic::stateTag=0;

int CPublic::g_CaliPointNumber = 4;

float* CPublic::g_pBestAlpha=NULL;

Point* CPublic::g_pBestVector=NULL;

Point* CPublic::g_pCaliPoint=NULL;

FILE* CPublic::fpCur=NULL;

char* CPublic::curFile=NULL;

Point* CPublic::g_curCaliPoints=NULL;

float* CPublic::g_curBestAlpha=NULL;

Point* CPublic::g_curBestVector=NULL;

//FILE* CPublic::g_pogRecordFile=NULL;

//2x2校准参数
float CPublic::g_BestAlpha[4] = {2.0, 2.0, 2.0, 2.0};

Point CPublic::g_BestVector2x2[4] = {Point(0,0),Point(0,0),Point(0,0),Point(0,0)};

Point CPublic::g_caliPoint[4] = {Point(320,256),Point(960,256),Point(320,768),Point(960,768)};

FILE* CPublic::fp[4]={NULL,NULL,NULL,NULL};

char* CPublic::fileName[4]={"2X2_alph_1.txt","2X2_alph_2.txt","2X2_alph_3.txt","2X2_alph_4.txt"};



//精度测试标准参数
Point CPublic::g_TestPoint[9]={Point(213,171),Point(640,171),Point(1067,171),Point(213,512),Point(640,512),Point(1067,512),Point(213,853),Point(640,853),Point(1067,853)};

Point* CPublic::g_pCurTestPoint = NULL;

FILE* CPublic::fpTest[9]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

FILE* CPublic::fpTestCur = NULL;

char* CPublic::testFileName[9]={"3X3_error_1.txt","3X3_error_2.txt","3X3_error_3.txt","3X3_error_4.txt","3X3_error_5.txt","3X3_error_6.txt","3X3_error_7.txt","3X3_error_8.txt","3X3_error_9.txt"};

char* CPublic::curTestFileName=NULL;

//3X3校准参数
float CPublic::g_BestAlpha3X3[9] = {2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0};

Point CPublic::g_BestVector3x3[9] = {Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0)};

FILE* CPublic::fp3X3[9]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

Point CPublic::g_caliPoint3X3[9] = {Point(213,171),Point(640,171),Point(1067,171),Point(213,512),Point(640,512),Point(1067,512),Point(213,853),Point(640,853),Point(1067,853)};

char* CPublic::fileName3X3[9]={"3X3_alph_1.txt","3X3_alph_2.txt","3X3_alph_3.txt","3X3_alph_4.txt","3X3_alph_5.txt","3X3_alph_6.txt","3X3_alph_7.txt","3X3_alph_8.txt","3X3_alph_9.txt"};

//4X4校准参数

float CPublic::g_BestAlpha4X4[4*4] = {
	                                  2.0, 2.0, 2.0, 2.0, 
                                      2.0, 2.0, 2.0, 2.0, 
									  2.0, 2.0, 2.0, 2.0,
									  2.0, 2.0, 2.0, 2.0
									  };
Point CPublic::g_BestVector4x4[16] = {
									Point(0,0),Point(0,0),Point(0,0),Point(0,0),
									Point(0,0),Point(0,0),Point(0,0),Point(0,0),
									Point(0,0),Point(0,0),Point(0,0),Point(0,0),
									Point(0,0),Point(0,0),Point(0,0),Point(0,0)
									};

FILE* CPublic::fp4X4[4*4]={
	                       NULL,NULL,NULL,NULL,
                           NULL,NULL,NULL,NULL,
						   NULL,NULL,NULL,NULL,
						   NULL,NULL,NULL,NULL
						   };

Point CPublic::g_caliPoint4X4[4*4] = {
	                                   Point(160,128),Point(480,128),Point(800,128),Point(1120,128),
									   Point(160,384),Point(480,384),Point(800,384),Point(1120,384),
									   Point(160,640),Point(480,640),Point(800,640),Point(1120,640),
                                       Point(160,896),Point(480,896),Point(800,896),Point(1120,896)};

char* CPublic::fileName4X4[4*4]={"4X4_alph_1.txt","4X4_alph_2.txt","4X4_alph_3.txt","4X4_alph_4.txt",
                                  "4X4_alph_5.txt","4X4_alph_6.txt","4X4_alph_7.txt","4X4_alph_8.txt",
								  "4X4_alph_9.txt","4X4_alph_10.txt","4X4_alph_11.txt","4X4_alph_12.txt",
                                  "4X4_alph_13.txt","4X4_alph_14.txt","4X4_alph_15.txt","4X4_alph_16.txt"};

//5X5校准参数
float CPublic::g_BestAlpha5X5[5*5] = {
	    2.0, 2.0, 2.0, 2.0, 2.0,
		2.0, 2.0, 2.0, 2.0, 2.0,
		2.0, 2.0, 2.0, 2.0, 2.0,
		2.0, 2.0, 2.0, 2.0, 2.0,
		2.0, 2.0, 2.0, 2.0, 2.0
};

Point CPublic::g_BestVector5x5[25] = {
	Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),
	Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),
	Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),
	Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),
	Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0)
									};

FILE* CPublic::fp5X5[5*5]={
	    NULL,NULL,NULL,NULL,NULL,
		NULL,NULL,NULL,NULL,NULL,
		NULL,NULL,NULL,NULL,NULL,
		NULL,NULL,NULL,NULL,NULL,
		NULL,NULL,NULL,NULL,NULL
};

Point CPublic::g_caliPoint5X5[5*5] = {
	Point(128,103),Point(384,103),Point(640,103),Point(896,103),Point(1152,103),
	Point(128,308),Point(384,308),Point(640,308),Point(896,308),Point(1152,308),
	Point(128,513),Point(384,513),Point(640,513),Point(896,513),Point(1152,513),
	Point(128,718),Point(384,718),Point(640,718),Point(896,718),Point(1152,718),
	Point(128,923),Point(384,923),Point(640,923),Point(896,923),Point(1152,923),
};
	
char* CPublic::fileName5X5[5*5]={
	    "5X5_alph_1.txt","5X5_alph_2.txt","5X5_alph_3.txt","5X5_alph_4.txt","5X5_alph_5.txt",
		"5X5_alph_6.txt","5X5_alph_7.txt","5X5_alph_8.txt","5X5_alph_9.txt","5X5_alph_10.txt",
		"5X5_alph_11.txt","5X5_alph_12.txt","5X5_alph_13.txt","5X5_alph_14.txt","5X5_alph_15.txt",
		"5X5_alph_16.txt","5X5_alph_17.txt","5X5_alph_18.txt","5X5_alph_19.txt","5X5_alph_20.txt",
		"5X5_alph_21.txt","5X5_alph_22.txt","5X5_alph_23.txt","5X5_alph_24.txt","5X5_alph_25.txt"
};

//6X6校准参数
float CPublic::g_BestAlpha6X6[6*6] = {
	    2.0, 2.0, 2.0, 2.0, 2.0, 2.0,
		2.0, 2.0, 2.0, 2.0, 2.0, 2.0,
		2.0, 2.0, 2.0, 2.0, 2.0, 2.0,
		2.0, 2.0, 2.0, 2.0, 2.0, 2.0,
		2.0, 2.0, 2.0, 2.0, 2.0, 2.0,
		2.0, 2.0, 2.0, 2.0, 2.0, 2.0
};

Point CPublic::g_BestVector6x6[36] = {
		Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),
		Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),
		Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),
		Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),
		Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),
		Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0),Point(0,0)
									};

FILE* CPublic::fp6X6[6*6]={
	    NULL,NULL,NULL,NULL,NULL,NULL,
		NULL,NULL,NULL,NULL,NULL,NULL,
		NULL,NULL,NULL,NULL,NULL,NULL,
		NULL,NULL,NULL,NULL,NULL,NULL,
		NULL,NULL,NULL,NULL,NULL,NULL,
		NULL,NULL,NULL,NULL,NULL,NULL
};

Point CPublic::g_caliPoint6X6[6*6] = {
	    Point(107,85),Point(320,85),Point(533,85),Point(746,85),Point(959,85),Point(1172,85),
		Point(107,256),Point(320,256),Point(533,256),Point(746,256),Point(959,256),Point(1172,256),
		Point(107,427),Point(320,427),Point(533,427),Point(746,427),Point(959,427),Point(1172,427),
		Point(107,598),Point(320,598),Point(533,598),Point(746,598),Point(959,598),Point(1172,598),
		Point(107,769),Point(320,769),Point(533,769),Point(746,769),Point(959,769),Point(1172,769),
		Point(107,940),Point(320,940),Point(533,940),Point(746,940),Point(959,940),Point(1172,940)
};

char* CPublic::fileName6X6[6*6]={
	        "6X6_alph_1.txt","6X6_alph_2.txt","6X6_alph_3.txt","6X6_alph_4.txt","6X6_alph_5.txt","6X6_alph_6.txt",
			"6X6_alph_7.txt","6X6_alph_8.txt","6X6_alph_9.txt","6X6_alph_10.txt","6X6_alph_11.txt","6X6_alph_12.txt",
			"6X6_alph_13.txt","6X6_alph_14.txt","6X6_alph_15.txt","6X6_alph_16.txt","6X6_alph_17.txt","6X6_alph_18.txt",
			"6X6_alph_19.txt","6X6_alph_20.txt","6X6_alph_21.txt","6X6_alph_22.txt","6X6_alph_23.txt","6X6_alph_24.txt",
			"6X6_alph_25.txt","6X6_alph_26.txt","6X6_alph_27.txt","6X6_alph_28.txt","6X6_alph_29.txt","6X6_alph_30.txt",
			"6X6_alph_31.txt","6X6_alph_32.txt","6X6_alph_33.txt","6X6_alph_34.txt","6X6_alph_35.txt","6X6_alph_36.txt"
};

int CPublic::g_curGridTestPointNumber=16;

Point* CPublic::g_curGridTestPoints=NULL;

bool CPublic::saveFlag = true;

CRect CPublic::rectNum[12] = {
	CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), 
	CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0)
};

CRect CPublic::rectAlp[30] = {
	CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0),
	CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0),
	CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0), CRect(0,0,0,0)
};

bool CPublic::NumFlag = FALSE;		//初始状态都设置为关闭
bool CPublic::AlpFlag = FALSE;		//此标志并不跟键盘真实打开相关联，而是与获取键盘中按键的位置同步
bool CPublic::FaceDetected = FALSE;	//初始设置为否，点击按钮factdetection开启，再次点击关闭

