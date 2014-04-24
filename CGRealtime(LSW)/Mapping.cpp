// Mapping.cpp: implementation of the Mapping class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mapping.h"
#include "math.h"
#include "Public.h"
#include <iostream>
using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mapping::Mapping()
{
  bestAlph = 2.0000;
}

Mapping::~Mapping()
{

}

/******************************************************************
 * ���ܣ�ʵ��Uvi = Urp + alpha*(Uri - Urp),�������鹹��
 * ������Point x	���ʵ��
		 Point F	��������ʵ�㣬��������ͷ�Ĺ�Դ
		 alph		��Ӧ��alphaֵ
 * ���أ�Point nx	���ʵ��x��Ӧ�������
 ******************************************************************/
Point Mapping::CaltPointx(Point x,Point F,float alph)
{
	Point nx;
	nx.setX( F.getX() + alph*( x.getX() - F.getX() ) );
	nx.setY( F.getY() + alph*( x.getY() - F.getY() ) );
	return nx;	
}

/********************************************************************
 * ���ܣ�����ֱ��u1u2��v1v2�Ľ���
 * ������Point u1,u2,v1,v2
 * ���أ�����Point
 ********************************************************************/
Point Mapping::intersection(Point u1,Point u2,Point v1,Point v2)
{
	Point ret=u1;
	double t=((u1.getX()-v1.getX())*(v1.getY()-v2.getY())-(u1.getY()-v1.getY())*(v1.getX()-v2.getX()))
		/((u1.getX()-u2.getX())*(v1.getY()-v2.getY())-(u1.getY()-u2.getY())*(v1.getX()-v2.getX()));
	ret.setX(ret.getX()+(u2.getX()-u1.getX())*t);
	ret.setY(ret.getY()+(u2.getY()-u1.getY())*t);
	return ret;
}

/*********************************************************************
 * ���ܣ�������Ļע�ӵ�
 * ������point[0~3]		�ĸ���ߵ�
		 point[4]		�������ߵ�
		 point[5]		ͫ������
		 float alph		alpha����
		 Point vect		λ��ʸ��	
 * ���أ�void	����ȡ����Ļע�ӵ㸳ֵ��gazePoint��
 *********************************************************************/
void Mapping::calGazePoint(Point point[6], float alph, Point vect){
			Point nx[5];
			
			for(int i=0;i<4;i++)
			{
				nx[i]=CaltPointx(point[i],point[4],alph);	//point[4]Ϊ������ͷ�Ĺ��
			}													//nx[0~3]����ĸ���ߵ������
			
			Point O1;
			Point O2;
			Point M2;
			Point M3;
			Point M1;
			Point M4;
			nx[4].setX(point[5].getX());						//nx[4]���ͫ�����ĵ�
			nx[4].setY(point[5].getY());
			Point  E=intersection(nx[0],nx[2],nx[1],nx[3]);		//�����ĸ������ߵ�Ľ��� 0     1   ��x
																//                            4		  ��y
			                                                    //ת����Ĺ��˳��         3     2
			//���01//32 ����M3��M4
			if((  nx[0].getY()  -  nx[1].getY()  )  /  (  nx[0].getX()  -  nx[1].getX()  ) ==
				 (  nx[3].getY()  -  nx[2].getY()  )  /  (  nx[3].getX()  -  nx[2].getX()  ))
			{
				
				//��ֱ��Ȼ���󽻵�
				int	k1,k2;
				k1=((float)(nx[0].getY()-nx[1].getY())) / ( nx[0].getX() - nx[1].getX() );
				k2=((float)(nx[1].getX()-nx[2].getX())) / ( nx[1].getY() - nx[2].getY() );
				
				if(k1*k2!=1)	//01��12����ֱ
				{
					M3.setY( (k1*k2*nx[1].getY()+k1*nx[4].getX()-nx[4].getY()-k1*nx[1].getX())/ (k1*k2-1) );	
					M4.setY( (k1*k2*nx[1].getY()+k1*E.getX()-E.getY()-k1*nx[1].getX()) / (k1*k2-1) );
					M3.setX( (k1*k2*nx[4].getX()+k2*nx[1].getY()-k2*nx[4].getY()-nx[1].getX()) / (k1*k2-1) );
					M4.setX( (k1*k2*E.getX()+k2*nx[1].getY()-k2*E.getY()-nx[1].getX())  /  (k1*k2-1) );					
				}
				else
				{
					
					M3.setX(nx[1].getX());
					M3.setY(nx[4].getY());
					M4.setX(nx[1].getX());
					M4.setY(E.getY());					
				}				
			}
			else
			{
				O1=intersection(nx[0],nx[1],nx[2],nx[3]);	//01��23�Ľ���
				M3=intersection(nx[1],nx[2],O1,nx[4]);		//ֱ��12��ֱ��O1������ߵĽ���
				M4=intersection(nx[1],nx[2],O1,E);			//ֱ��12��ֱ��O1��ͫ�����ĵĽ���
			}
			//���03//12 ����M1��M2
			if((  nx[0].getX()  -  nx[3].getX()  )  /  (  nx[0].getY()  -  nx[3].getY()  ) ==
				 (  nx[1].getX()  -  nx[2].getX()  )  /  (  nx[1].getY()  -  nx[2].getY()  ))
			{
				
				int k1,k2;
				k1=((float)(nx[0].getX()-nx[3].getX()))/(nx[0].getY()-nx[3].getY());
				k2=((float)(nx[0].getY()-nx[1].getY()))/(nx[0].getX()-nx[1].getX());
				
				if(k1*k2!=1)
				{
					M1.setX( (k1*E.getY()+k2*k1*nx[1].getX()-E.getX()-k1*nx[1].getY()) / (k1*k2-1) );
					M2.setX( (k1*nx[4].getY()+k2*k1*nx[1].getX()-nx[4].getX()-k1*nx[1].getY()) / (k1*k2-1) );
					M1.setY( (k1*k2*E.getY()+k2*nx[1].getX()-nx[1].getY()-k2*E.getX()) / (k1*k2-1) );
					M2.setY( (k1*k2*nx[4].getY()+k2*nx[1].getX()-nx[1].getY()-k2*nx[4].getX()) / (k1*k2-1) );
					
				}
				else
				{
					
					M1.setX(E.getX());
					M1.setY(nx[0].getY());
					M2.setX(nx[4].getX());
					M2.setY(E.getY());					
				}
			}
			else
			{
				O2=intersection(nx[1],nx[2],nx[0],nx[3]);
				M2=intersection(nx[0],nx[1],nx[4],O2);
				M1=intersection(nx[0],nx[1],E,O2);
			}

			//��֪M1��M2��M3��M4������Ļ�������Ϣ�����ݽ��Ȳ����Լ�����Ļע�ӵ�
			double CRx=(  (nx[0].getX()*M1.getY()-M1.getX()*nx[0].getY())*
						 (M2.getX()*nx[1].getY()-M2.getY()*nx[1].getX())  )/
					  (  (nx[0].getX()*M2.getY()-M2.getX()*nx[0].getY())*
						(M1.getX()*nx[1].getY()-M1.getY()*nx[1].getX())   );
			double CRy=((nx[1].getX()*M3.getY()-M3.getX()*nx[1].getY())*
						(M4.getX()*nx[2].getY()-M4.getY()*nx[2].getX()))/
						((nx[1].getX()*M4.getY()-M4.getX()*nx[1].getY())*
						(M3.getX()*nx[2].getY()-M3.getY()*nx[2].getX()));
			if(CRx>0&&CRy>0)
			{
				double Xgaze=width*CRx/(1+CRx);
				double Ygaze=height*CRy/(1+CRy);
		
				Xgaze = Xgaze + vect.getX();
				Ygaze = Ygaze + vect.getY();

				gazePoint.setX(Xgaze);
				gazePoint.setY(Ygaze);	
			}				
		}	


/************************************************************
 *	���ܣ����ݹ����Ϣ�������ѵ�alpha�����Լ�λ��ʸ��
 *	������Point point[6]	0-3Ϊ�ĸ����ʵ��
							4Ϊ��������ʵ��
							5Ϊͫ������
		  Point caliPoint	��Ļע�ӵ�			
 ***********************************************************/
void Mapping::calBestAlph(Point point[6], Point caliPoint)
{
		Point	nx[5];
		float	tempAlph = 2.0;
		double	minDistance = 65535;
		Point	tempVector(0, 0);
		while(1)
		{
			for(int i=0;i<4;i++)
			{
				nx[i]=CaltPointx(point[i],point[4],tempAlph);	//������ĸ���������
			}
		
			Point O1;
			Point O2;
			Point M2;
			Point M3;
			Point M1;
			Point M4;
			nx[4].setX(point[5].getX());						//ͫ������
			nx[4].setY(point[5].getY());
			Point  E=intersection(nx[0],nx[2],nx[1],nx[3]);		//�����ߵ�02��13�Ľ���
			

/**************************************���ݹ�ߵ�ͳ�ʼ�趨��alphaֵ�������Ļע�ӵ㣬������֪����Ļע�ӵ���жԱ�******************************/
			//��ͫ�����Ľ�12��M3����01��M2
			//���Խ�Ϸ���㽻12��M4����01��M1
			//��ֲ�	0		1
			//				4		(pupil)
			//			3		2

			//���01//32
			if((  nx[0].getY()  -  nx[1].getY()  )  /  (  nx[0].getX()  -  nx[1].getX()  ) ==
				 (  nx[3].getY()  -  nx[2].getY()  )  /  (  nx[3].getX()  -  nx[2].getX()  ))
			{
				//��ֱ��Ȼ���󽻵�
				int	k1,k2;
				k1=((float)(nx[0].getY()-nx[1].getY())) / ( nx[0].getX() - nx[1].getX() );
				k2=((float)(nx[1].getX()-nx[2].getX())) / ( nx[1].getY() - nx[2].getY() );
				
				if(k1*k2!=1)
				{
					M3.setY( (k1*k2*nx[1].getY()+k1*nx[4].getX()-nx[4].getY()-k1*nx[1].getX())/ (k1*k2-1) );	
					M4.setY( (k1*k2*nx[1].getY()+k1*E.getX()-E.getY()-k1*nx[1].getX()) / (k1*k2-1) );
					M3.setX( (k1*k2*nx[4].getX()+k2*nx[1].getY()-k2*nx[4].getY()-nx[1].getX()) / (k1*k2-1) );
					M4.setX( (k1*k2*E.getX()+k2*nx[1].getY()-k2*E.getY()-nx[1].getX())  /  (k1*k2-1) );					
				}
				else
				{
					
					M3.setX(nx[1].getX());
					M3.setY(nx[4].getY());
					M4.setX(nx[1].getX());
					M4.setY(E.getY());					
				}				
			}
			else
			{
				O1=intersection(nx[0],nx[1],nx[2],nx[3]);
				M3=intersection(nx[1],nx[2],O1,nx[4]);
				M4=intersection(nx[1],nx[2],O1,E);
			}
			//���AD//BC
			if((  nx[0].getX()  -  nx[3].getX()  )  /  (  nx[0].getY()  -  nx[3].getY()  ) ==
				 (  nx[1].getX()  -  nx[2].getX()  )  /  (  nx[1].getY()  -  nx[2].getY()  ))
			{
				
				int k1,k2;
				k1=((float)(nx[0].getX()-nx[3].getX()))/(nx[0].getY()-nx[3].getY());
				k2=((float)(nx[0].getY()-nx[1].getY()))/(nx[0].getX()-nx[1].getX());
				
				if(k1*k2!=1)
				{
					M1.setX( (k1*E.getY()+k2*k1*nx[1].getX()-E.getX()-k1*nx[1].getY()) / (k1*k2-1) );
					M2.setX( (k1*nx[4].getY()+k2*k1*nx[1].getX()-nx[4].getX()-k1*nx[1].getY()) / (k1*k2-1) );
					M1.setY( (k1*k2*E.getY()+k2*nx[1].getX()-nx[1].getY()-k2*E.getX()) / (k1*k2-1) );
					M2.setY( (k1*k2*nx[4].getY()+k2*nx[1].getX()-nx[1].getY()-k2*nx[4].getX()) / (k1*k2-1) );
					
				}
				else
				{
					M1.setX(E.getX());
					M1.setY(nx[0].getY());
					M2.setX(nx[4].getX());
					M2.setY(E.getY());					
				}
			}
			else
			{
				O2=intersection(nx[1],nx[2],nx[0],nx[3]);
				M2=intersection(nx[0],nx[1],nx[4],O2);
				M1=intersection(nx[0],nx[1],E,O2);
			}
			double CRx=(  (nx[0].getX()*M1.getY()-M1.getX()*nx[0].getY())*
						 (M2.getX()*nx[1].getY()-M2.getY()*nx[1].getX())  )/
					  (  (nx[0].getX()*M2.getY()-M2.getX()*nx[0].getY())*
						(M1.getX()*nx[1].getY()-M1.getY()*nx[1].getX())   );
			double CRy=((nx[1].getX()*M3.getY()-M3.getX()*nx[1].getY())*
						(M4.getX()*nx[2].getY()-M4.getY()*nx[2].getX()))/
						((nx[1].getX()*M4.getY()-M4.getX()*nx[1].getY())*
						(M3.getX()*nx[2].getY()-M3.getY()*nx[2].getX()));
			if(CRx>0&&CRy>0)
			{
				double Xgaze=width*CRx/(1+CRx);
				double Ygaze=height*CRy/(1+CRy);
				double currentDistance = sqrt((Xgaze - caliPoint.getX())*(Xgaze - caliPoint.getX())+(Ygaze - caliPoint.getY())*(Ygaze - caliPoint.getY()));
                
				tempVector.setX(caliPoint.getX() - Xgaze);	//����ǰ��Ļע�ӵ�������֮���Ϊʸ���������һ��Point��
				tempVector.setY(caliPoint.getY() - Ygaze);

                if (currentDistance < minDistance)
                {
					minDistance = currentDistance;
					bestAlph = tempAlph;
					bestVector = tempVector;
					gazePoint.setX(Xgaze);
				    gazePoint.setY(Ygaze);	
                }

// 				if (currentDistance< 20) 
// 				{
// 					bestAlph = tempAlph;				//��ȡ��ǰalphaֵ
// 					CPublic::saveFlag = true;
// 					break;
// 				}

				tempAlph = tempAlph - 0.001;
				if (tempAlph<=0.5)
				{
					CPublic::saveFlag = true;			//�ж�alphaֵ��vectorʸ���Ƿ�Ҫ���浽�ļ���
					break;
				}
			}
			else
			{
				CPublic::saveFlag = true;
				break;
			}
		}	
}
