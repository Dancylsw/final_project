// alibration.cpp: implementation of the Calibration class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Calibration.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Calibration::Calibration()
{

}

Calibration::~Calibration()
{

}

void Calibration::setE(Point ee[6])
{
	int i;
	for(i=0;i<6;i++)
	{
		e[i]=ee[i];
	}
};
void Calibration::setS(Point ss[6])
{
	int i;
	for(i=0;i<6;i++)
	{
		s[i]=ss[i];
	}
};
void Calibration::calibrate()
{
	int i,j,k;
	double ee[6][6];
	//求a[]
	memset(ee,0,6*6*sizeof(double));
	for(i=0;i<6;i++)
	{
		int a[6]={1,e[i].getX(),e[i].getY(),e[i].getX()*e[i].getY(),e[i].getX()*e[i].getX(),e[i].getY()*e[i].getY()};
		for(j=0;j<6;j++)
		{
			for(k=0;k<6;k++)
			{
				ee[j][k]+=a[j]*a[k];
			}
		}
	}
	CvMat matleft = cvMat( 6, 6, CV_64FC1, ee );
	double ss[6];
	memset(ss,0,6*sizeof(double));
	for(i=0;i<6;i++)
	{
		int a[6]={1*s[i].getX(),e[i].getX()*s[i].getX(),e[i].getY()*s[i].getX(),
			e[i].getX()*e[i].getY()*s[i].getX(),e[i].getX()*e[i].getX()*s[i].getX(),
			e[i].getY()*e[i].getY()*s[i].getX()};
		ss[i]+=a[i];
		
	}
	CvMat matright = cvMat( 6, 1, CV_64FC1, ss );
	CvMat* matleftInv = cvCreateMat( 6, 6, CV_64FC1 );
	cvZero( matleftInv );
	//求逆
	cvInvert(&matleft, matleftInv);
	//需要证明他是可以求逆的
	for(i=0;i<6;i++)
	{
		if(cvmGet( matleftInv, i, 0 )!=0)
		{
			break;
		}
	}
	if(i<6)
	{
		CvMat* mata = cvCreateMat( 6, 1, CV_64FC1 );
		cvMatMul(matleftInv, &matright, mata); 
		//复制给a
		for(i=0;i<6;i++)
		{
			a[i]= cvmGet( mata, i, 0 );
		}
		//求b[]
		memset(ss,0,6*sizeof(double));
		for(i=0;i<6;i++)
		{
			int a[6]={1*s[i].getY(),e[i].getX()*s[i].getY(),e[i].getY()*s[i].getY(),
				e[i].getX()*e[i].getY()*s[i].getY(),e[i].getX()*e[i].getX()*s[i].getY(),
				e[i].getY()*e[i].getY()*s[i].getY()};
			ss[i]+=a[i];
		}
		CvMat matright1 = cvMat( 6, 1, CV_64FC1, ss );
		cvMatMul(matleftInv, &matright1, mata);
		for(i=0;i<6;i++)
		{
			b[i]= cvmGet( mata, i, 0 );
		}		
		cvReleaseMat( &mata );
	}
	cvReleaseMat( &matleftInv );
	
};
Point Calibration::Screen(Point x)
{
	///
	Point point;
	int xx=a[0]+a[1]*x.getX()+a[2]*x.getY()+a[3]*x.getX()*x.getY()+a[4]*x.getX()*x.getX()+a[5]*x.getY()*x.getY();
	int yy=b[0]+b[1]*x.getX()+b[2]*x.getY()+b[3]*x.getX()*x.getY()+b[4]*x.getX()*x.getX()+b[5]*x.getY()*x.getY();
	point.setX(xx);
	point.setY(yy);
	return point;
};
