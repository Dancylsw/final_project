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
 * 功能：实现Uvi = Urp + alpha*(Uri - Urp),计算光斑虚构点
 * 参数：Point x	光斑实点
		 Point F	第五个光斑实点，即靠近镜头的光源
		 alph		对应的alpha值
 * 返回：Point nx	光斑实点x对应的虚拟点
 ******************************************************************/
Point Mapping::CaltPointx(Point x,Point F,float alph)
{
	Point nx;
	nx.setX( F.getX() + alph*( x.getX() - F.getX() ) );
	nx.setY( F.getY() + alph*( x.getY() - F.getY() ) );
	return nx;	
}

/********************************************************************
 * 功能：计算直线u1u2，v1v2的交点
 * 参数：Point u1,u2,v1,v2
 * 返回：交点Point
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
 * 功能：计算屏幕注视点
 * 参数：point[0~3]		四个光斑点
		 point[4]		第五个光斑点
		 point[5]		瞳孔中心
		 float alph		alpha参数
		 Point vect		位移矢量	
 * 返回：void	将获取的屏幕注视点赋值到gazePoint中
 *********************************************************************/
void Mapping::calGazePoint(Point point[6], float alph, Point vect){
			Point nx[5];
			
			for(int i=0;i<4;i++)
			{
				nx[i]=CaltPointx(point[i],point[4],alph);	//point[4]为靠近镜头的光斑
			}													//nx[0~3]存放四个光斑的虚拟点
			
			Point O1;
			Point O2;
			Point M2;
			Point M3;
			Point M1;
			Point M4;
			nx[4].setX(point[5].getX());						//nx[4]存放瞳孔中心点
			nx[4].setY(point[5].getY());
			Point  E=intersection(nx[0],nx[2],nx[1],nx[3]);		//计算四个虚拟光斑点的交点 0     1   ←x
																//                            4		  ↓y
			                                                    //转换后的光斑顺序         3     2
			//如果01//32 计算M3，M4
			if((  nx[0].getY()  -  nx[1].getY()  )  /  (  nx[0].getX()  -  nx[1].getX()  ) ==
				 (  nx[3].getY()  -  nx[2].getY()  )  /  (  nx[3].getX()  -  nx[2].getX()  ))
			{
				
				//求直线然后求交点
				int	k1,k2;
				k1=((float)(nx[0].getY()-nx[1].getY())) / ( nx[0].getX() - nx[1].getX() );
				k2=((float)(nx[1].getX()-nx[2].getX())) / ( nx[1].getY() - nx[2].getY() );
				
				if(k1*k2!=1)	//01与12不垂直
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
				O1=intersection(nx[0],nx[1],nx[2],nx[3]);	//01与23的交点
				M3=intersection(nx[1],nx[2],O1,nx[4]);		//直线12与直线O1与第五光斑的交点
				M4=intersection(nx[1],nx[2],O1,E);			//直线12与直线O1与瞳孔中心的交点
			}
			//如果03//12 计算M1，M2
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

			//已知M1，M2，M3，M4，和屏幕的相关信息，根据交比不变性计算屏幕注视点
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
 *	功能：根据光斑信息计算出最佳的alpha参数以及位移矢量
 *	参数：Point point[6]	0-3为四个光斑实点
							4为第五个光斑实点
							5为瞳孔中心
		  Point caliPoint	屏幕注视点			
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
				nx[i]=CaltPointx(point[i],point[4],tempAlph);	//计算出四个光斑虚拟点
			}
		
			Point O1;
			Point O2;
			Point M2;
			Point M3;
			Point M1;
			Point M4;
			nx[4].setX(point[5].getX());						//瞳孔中心
			nx[4].setY(point[5].getY());
			Point  E=intersection(nx[0],nx[2],nx[1],nx[3]);		//虚拟光斑点02与13的交点
			

/**************************************根据光斑点和初始设定的alpha值计算出屏幕注视点，并与已知的屏幕注视点进行对比******************************/
			//过瞳孔中心交12于M3，交01于M2
			//过对角戏交点交12于M4，交01于M1
			//点分布	0		1
			//				4		(pupil)
			//			3		2

			//如果01//32
			if((  nx[0].getY()  -  nx[1].getY()  )  /  (  nx[0].getX()  -  nx[1].getX()  ) ==
				 (  nx[3].getY()  -  nx[2].getY()  )  /  (  nx[3].getX()  -  nx[2].getX()  ))
			{
				//求直线然后求交点
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
			//如果AD//BC
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
                
				tempVector.setX(caliPoint.getX() - Xgaze);	//将当前屏幕注视点与计算点之差保存为矢量，存放在一个Point中
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
// 					bestAlph = tempAlph;				//获取当前alpha值
// 					CPublic::saveFlag = true;
// 					break;
// 				}

				tempAlph = tempAlph - 0.001;
				if (tempAlph<=0.5)
				{
					CPublic::saveFlag = true;			//判断alpha值，vector矢量是否要保存到文件中
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
