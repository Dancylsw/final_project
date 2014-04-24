// Mapping.h: interface for the Mapping class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPPING_H__CEBFECB3_3DEC_4984_9C0D_CECC321BDB83__INCLUDED_)
#define AFX_MAPPING_H__CEBFECB3_3DEC_4984_9C0D_CECC321BDB83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Point.h"

class Mapping  
{
		private:
			
		//float alph;
//		float alph[4];
		float width;
		float height;
		Point gazePoint;
		
		public:
			float bestAlph;
			Point bestVector;
		public :
			void setWidth(double x){
				width=x;	
			}
			void setHeight(double x){
				height=x;	
			}
			
			double getWidth(){
				return width;	
			}
			double getHeight(){
				return height;	
			}

			Point getGazePoint(){
				return gazePoint;	
			}
			
			//Calt the points A',B',C',D'
			Point CaltPointx(Point x,Point F,float alph);

			//计算俩直线交点 
			Point intersection(Point u1,Point u2,Point v1,Point v2);

			void calGazePoint(Point point[6], float alph, Point vect);

		public:
			void calBestAlph(Point point[6], Point caliPoint);
			Mapping();
			virtual ~Mapping();
			
};

#endif // !defined(AFX_MAPPING_H__CEBFECB3_3DEC_4984_9C0D_CECC321BDB83__INCLUDED_)
