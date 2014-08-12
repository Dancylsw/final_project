// Point.h: interface for the Point class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT_H__CF5FC6CB_5B86_49B2_BC4C_BF791AFFBC88__INCLUDED_)
#define AFX_POINT_H__CF5FC6CB_5B86_49B2_BC4C_BF791AFFBC88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

class Point  
{
private:
	float x,y;

public:
	float getX(){
		return x;	
	}
	float getY(){
		return y;	
	}
	void setX(float nx){
		x=nx;	
	}
	void setY(float ny){
		y=ny;	
	}
public:
	Point(float nx,float ny)
	{
		x=nx;
		y=ny;
	}
	Point(int nx,int ny)
	{
		x=(float)nx;
		y=(float)ny;
	}
	Point()
	{
		x=0;
		y=0;
	}
	virtual ~Point();
	
};

#endif // !defined(AFX_POINT_H__CF5FC6CB_5B86_49B2_BC4C_BF791AFFBC88__INCLUDED_)
