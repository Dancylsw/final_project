// Preprocess.cpp: implementation of the Preprocess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Preprocess.h"
#include <iostream>
using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Preprocess::Preprocess()
{
	//方向数组的初始化
	Direction[0][0]=-1;
	Direction[0][1]=-1;
	Direction[1][0]=0;
	Direction[1][1]=-1;
	Direction[2][0]=1;
	Direction[2][1]=-1;
	Direction[3][0]=-1;
	Direction[3][1]=0;
	Direction[4][0]=1;
	Direction[4][1]=0;
	Direction[5][0]=-1;
	Direction[5][1]=1;
	Direction[6][0]=0;
	Direction[6][1]=1;
	Direction[7][0]=1;
	Direction[7][1]=1;		
	queueCount=0;
	head=0;
	tail=0;
	memset(backup,0,768*576*sizeof(bool));
	memset(queue,0,4000*sizeof(Point));
	memset(log,0,200*2*sizeof(long));
	max=0;
	now=0;
	width=768;
	height=576;
	memset(pointCount,0,200*sizeof(int));			
	nowCount=0;	
	memset(point,0,5*sizeof(Point));
	memset(tag,false,5*sizeof(bool));
	leave=0;
	secondS=false;
	weed=false;
	pointNumber=0;
	memset(fault,0,5*sizeof(int));
}

Preprocess::~Preprocess()
{

}

/*
 *	在缓冲图像m_pImageBuffer上，以点(xi，yi)为中心延伸max个像素的矩形范围内
 *	若点的灰度大于阈值，则涂色(49,49,49)
 */
void Preprocess::blackened(BYTE *m_pImageBuffer,int xi,int yi,int max)
{
	if(xi-max>0&&yi-max>0&&xi+max<768&&yi+max<576)
	{
		int i,j;
		for(i=xi-max;i<=xi+max;i++)
		{
			for(j=yi-max;j<=yi+max;j++)
			{
				int tmp=i*width*3+j*3;
				if(*(m_pImageBuffer+tmp)>threshold)
				{
					*(m_pImageBuffer+tmp)=49;
					*(m_pImageBuffer+tmp+1)=49;
					*(m_pImageBuffer+tmp+2)=49;
				}
			}
		}
	}
	
}

/********************************************************************************************
*	功能：搜索光斑
*	参数：m_pImageBuffer		图像缓冲区
*		  x,y					搜索的起始地址
*	条件：要先设定阈值，然后设定搜索的范围
*	原理：找到所有可能的光斑点片，然后用矩形匹配的方式寻找合适的光斑点
*	
*********************************************************************************************/
void Preprocess::calGlints(BYTE *m_pImageBuffer ,int x,int y)
{
	//初始化用到的所有数据
	leave=0;
	memset(tag,false,5*sizeof(bool));
	secondS=false;
	weed=false;
	memset(point,0,5*sizeof(Point));
	pointNumber=0;
	while(threshold>65)//65
	{
		//初始化搜索的数据结构
		queueCount=0;
		head=0;
		tail=0;
		memset(backup,0,768*576*sizeof(bool));
		memset(queue,0,4000*sizeof(Point));
		memset(log,0,200*2*sizeof(long));
		memset(pointCount,0,200*sizeof(int));
		nowCount=0;	

		int i,j;//临时变量

		//对指定区域进行广度搜索
		for(i=x;i<x+scope_height;i++)
		{
			for(j=y;j<y+scope_width;j++)
			{
				if(backup[i][j]==false)
				{
					backup[i][j]=true;
					int tmp=i*768*3+j*3;
					//有问题
				//	cout<<(int)*(m_pImageBuffer+tmp)<<" ";
					if(*(m_pImageBuffer+tmp) >= threshold)
					{
						nowCount++;
						if(nowCount>=9)//200   ？？？？？？？？？？？全部找出来挑选最大的五个点片？？？
						{
							return;
						}
						glintSearch(m_pImageBuffer,x,y,i,j); //以i，j为起点进行广度优先搜索，对搜索过的点标记backup为true，并将有效点入队列queue
					}										 //并将计数值为nowCount的点片的x,y累加值保存在log[][]中
				}			
			}
		}

		leave=nowCount;
		//剔除不符合条件的点,算出他们的坐标,
		j=1;
		for(i=1;i<=nowCount&&i<9;i++)//i<200
		{
//			cout<<pointCount[i]<<" ";
			if(pointCount[i]>60)//点片中点的个数大于一定数目则不可能是	
			{				
				leave--;
			}
			else
			{	
				log[j][0]=log[i][0]/pointCount[i];		//log中由之前的累加值变成质心的坐标
				log[j][1]=log[i][1]/pointCount[i];
				pointCount[j]=pointCount[i];		
				j++;
			}
		}		
		/*if(leave==4&&nowCount==4)
		{
			
			for(i=0;i<4;i++)
			{
				fprintf(fpout,"%d,%d\t",log[i+1][0],log[i+1][1]);
			}
			fprintf(fpout,"\n");
		}
		*/
		//匹配余下的点还是首次搜索矩形中的主要点

		//首次搜索矩形中的主要点
		if(secondS==false)
		{
			if(leave>=3)
			{
				//初始化存储点的数据结构和点的标记

				memset(point,0,5*sizeof(Point));	//存放光斑中心
				memset(tag,false,5*sizeof(bool));	
				weed=false;
				
				//找矩形中的点赋给point[5]，并
				detect();
				if(pointNumber>=3)
				{
					secondS=true;
				}
				else
				{
					secondS=false;
				}
			}
		}
		//匹配余下的点
		else
		{
			for(i=0;i<5;i++)
			{
				if(tag[i]==false)
				{
					//循环匹配
					for(j=1;j<=leave;j++)
					{
						if(log[j][0]>=point[i].getX()-2		
						   &&log[j][0]<=point[i].getX()+2
						   &&log[j][1]>=point[i].getY()-2
						   &&log[j][1]<=point[i].getY()+2)
						{
							
							point[i].setX(log[j][0]);
							point[i].setY(log[j][1]);
							tag[i]=true;
							pointNumber++;
							break;
						}
					}
					
				}//end if(tag[i]==false)
			}//end for(i=5)
		}//end else
		if(pointNumber<=4)
		{
			threshold=threshold-5;	
		}
		else if(pointNumber>=5)
		{
			break;
		}
		//	cout<<threshold<<" "<<endl;
	}//end while
}

/********************************************************************
 * 功能：新的光斑搜索算法，根据光斑数量动态调整阈值，并分配光斑的位置
 * 参数：*m_pImageBuffer	图像缓冲区
		 x,y				搜索起始点
 * 结果：将搜索到的光斑中心点保存到Point point[5]中
 ********************************************************************/
void Preprocess::calGlints2(BYTE *m_pImageBuffer ,int x,int y)
{
    leave=0;
	memset(tag,false,5*sizeof(bool));
	memset(point,0,5*sizeof(Point));

	int loopcount = 0;

	while(threshold>100 && loopcount < 20)//65
	{
		//初始化搜索的数据结构
		leave=0;
		queueCount=0;
		pointNumber=0;
		head=0;
		tail=0;
		memset(backup,0,768*576*sizeof(bool));
		memset(queue,0,4000*sizeof(Point));
		memset(log,0,200*2*sizeof(long));
		memset(logTag,false,200*sizeof(bool));
		memset(pointCount,0,200*sizeof(int));
		nowCount=0;	

		int i,j;//临时变量

		//对指定区域进行广度搜索
		for(i=x;i<x+scope_height;i++)
		{
			for(j=y;j<y+scope_width;j++)
			{
				if(backup[i][j]==false)
				{
					backup[i][j]=true;
					int tmp=i*768*3+j*3;
					//有问题
				//	cout<<(int)*(m_pImageBuffer+tmp)<<" ";
					if(*(m_pImageBuffer+tmp) >= threshold)
					{
						nowCount++;
						if (nowCount > 9)
						{
							return;
						}
						glintSearch(m_pImageBuffer,x,y,i,j);

					}			
				}			
			}
		}

//place1:

		leave=nowCount;
//		cout<<leave<<": ";
		if(leave >= 5)
		{
		//剔除不符合条件的点,算出他们的坐标,
			j=1;
			for(i=1;i<=nowCount;i++)//i<200
			{
				//cout<<pointCount[i]<<" ";
				if(pointCount[i]>60)//60	
				{				
					leave--;
				}
				else
				{
					log[j][0]=log[i][0]/pointCount[i];
					log[j][1]=log[i][1]/pointCount[i];
					pointCount[j]=pointCount[i];
				//	cout<<"("<<log[j][1]<<","<<log[j][0]<<")"<<" "; 
					j++;
				}
			}
		}

        if(leave>=5)
		{
		int tempCount=1;
		int k=1;

			for(tempCount=1;tempCount<=leave;tempCount++)
			{
				if (!logTag[tempCount])
				{
					
					point[pointNumber].setX(log[tempCount][0]);		//不怕pointNumber大于4么？
					point[pointNumber].setY(log[tempCount][1]);
					for (k=tempCount+1;k<=leave;k++)
					{
	//				    cout<<"ABS:"<<abs(point[pointNumber].getX()-log[k][0])<<","<<abs(point[pointNumber].getY()-log[k][1])<<" ";
						if (!logTag[k] && abs(point[pointNumber].getX()-log[k][0])<4 && abs(point[pointNumber].getY()-log[k][1])<4)
						{
							point[pointNumber].setX((point[pointNumber].getX()+log[k][0])/2);
							point[pointNumber].setY((point[pointNumber].getY()+log[k][1])/2);
							logTag[k] = true;
						}
					}
	//				cout<<endl;
					pointNumber++;
				}
			}
		}
//		cout<<pointNumber<<"++";
   //     cout<<"threshold:"<<threshold<<endl;
		//匹配余下的点还是首次搜索矩形中的主要点

		if(pointNumber < 5 && threshold > 5)
		{
			threshold=threshold-5;	
		}
		else if (pointNumber>5 && threshold < 250)
		{
			threshold = threshold + 3;
		}
		else if(pointNumber == 5)
		{

			//调整5个光斑的顺序
            float leastLength = 65535;
			int leastIndex = 0;
			bool glintFlag[5] = {false,false,false,false,false};//是否分配好点的位置
			Point adjustedPoint[5];
			int j;

			//第1个(白)
			for (j = 0; j<5; j++)
			{
				if (!glintFlag[j])
				{
					if (leastLength > sqrt((x-point[j].getX())*(x-point[j].getX())+(y-point[j].getY())*(y-point[j].getY())))
					{
						leastLength = sqrt((x-point[j].getX())*(x-point[j].getX())+(y-point[j].getY())*(y-point[j].getY()));
						leastIndex = j;
					}
				}
			}
			glintFlag[leastIndex] = true;
			adjustedPoint[0] = point[leastIndex];
			leastLength = 65535;
		    leastIndex = 0;
				

			//第2个(绿)
			for (j = 0; j<5; j++)
			{
				if (!glintFlag[j])
				{
					if (leastLength > sqrt((x+scope_height-point[j].getX())*(x+scope_height-point[j].getX())+(y-point[j].getY())*(y-point[j].getY())))
					{
                        leastLength = sqrt((x+scope_height-point[j].getX())*(x+scope_height-point[j].getX())+(y-point[j].getY())*(y-point[j].getY()));
						leastIndex = j;
					}
				}
			}
			glintFlag[leastIndex] = true;
			adjustedPoint[1] = point[leastIndex];
			leastLength = 65535;
		    leastIndex = 0;

            //第3个(红)
			for (j = 0; j<5; j++)
			{
				if (!glintFlag[j])
				{
					if (leastLength > sqrt((x-point[j].getX())*(x-point[j].getX())+(y+scope_width-point[j].getY())*(y+scope_width-point[j].getY())))
					{
                        leastLength = sqrt((x-point[j].getX())*(x-point[j].getX())+(y+scope_width-point[j].getY())*(y+scope_width-point[j].getY()));
						leastIndex = j;
					}
				}
			}
			glintFlag[leastIndex] = true;
			adjustedPoint[2] = point[leastIndex];
			leastLength = 65535;
		    leastIndex = 0;

			//第4个(灰)
			for (j = 0; j<5; j++)
			{
				if (!glintFlag[j])
				{
					if (leastLength > sqrt((x+scope_height-point[j].getX())*(x+scope_height-point[j].getX())+(y+scope_width-point[j].getY())*(y+scope_width-point[j].getY())))
					{
                        leastLength = sqrt((x+scope_height-point[j].getX())*(x+scope_height-point[j].getX())+(y+scope_width-point[j].getY())*(y+scope_width-point[j].getY()));
						leastIndex = j;
					}
				}
			}
			glintFlag[leastIndex] = true;
			adjustedPoint[3] = point[leastIndex];
			leastLength = 65535;
	        leastIndex = 0;
			
			//第五个点
			for ( j = 0; j<5; j++)
			{
				if (!glintFlag[j])
				{
					adjustedPoint[4] = point[j];
					glintFlag[j] = true;
				}
			}

			for (i=0;i<5;i++)
			{
				point[i].setX(adjustedPoint[i].getX());
				point[i].setY(adjustedPoint[i].getY());
			}
			break;
		}

		loopcount++;
		//	cout<<threshold<<" "<<endl;
	}//end while
}

/*******************************************************************************************
*
*	功能：根据找到的leave个点片寻找符合条件光斑点(可能没有找齐五个)
*	说明：在这个过程中记得leave的变化，他会代表找到了几个有用的点
*		  记得把找到的点放回log[][];
*
*******************************************************************************************/
void Preprocess::detect()
{
	memset(fault,0,5*sizeof(int));
	weed=false;
	int i,j;
	pointNumber=0;
	if(leave>=5)
	{		
		//找出最大的五个亮斑		
		for(i=1;i<=5;i++)
		{
			for(j=i;j<=leave;j++)
			{
				if(pointCount[i]<pointCount[j])
				{
					long tmp=log[j][0];	
					log[j][0]=log[i][0];
					log[i][0]=tmp;
					tmp=log[j][1];	
					log[j][1]=log[i][1];
					log[i][1]=tmp;
					int t=pointCount[i];
					pointCount[i]=pointCount[j];
					pointCount[j]=t;
				}
			}
		}
		leave=5;

		//对其按照X轴排序
		for(i=1;i<=leave;i++)
		{
			for(j=i;j<=leave;j++)
			{
				if(log[j][0]<log[i][0])
				{
					long tmp=log[j][0];	
					log[j][0]=log[i][0];
					log[i][0]=tmp;
					tmp=log[j][1];	
					log[j][1]=log[i][1];
					log[i][1]=tmp;
				}
			}
		}
		
		//按坐标将不同的点赋给point
		int memwho=0;
		
		//按坐标将不同的点赋给point
		point[4].setX(log[3][0]);
		point[4].setY(log[3][1]);
		if(log[1][1]>log[2][1])
		{
			point[2].setX(log[1][0]);
			point[2].setY(log[1][1]);
			point[0].setX(log[2][0]);
			point[0].setY(log[2][1]);
		}
		else
		{
			point[2].setX(log[2][0]);
			point[2].setY(log[2][1]);
			point[0].setX(log[1][0]);
			point[0].setY(log[1][1]);
		}
		if(log[4][1]>log[5][1])
		{
			point[1].setX(log[5][0]);
			point[1].setY(log[5][1]);
			point[3].setX(log[4][0]);	
			point[3].setY(log[4][1]);
		}
		else
		{
			point[1].setX(log[4][0]);
			point[1].setY(log[4][1]);
			point[3].setX(log[5][0]);	
			point[3].setY(log[5][1]);	
		}
		//进行判定
		//检查范围（1）
		if(abs(point[1].getY()-point[0].getY())<=2
			&&abs(point[1].getX()-point[0].getX()-12)<=2)
		{
		
		}
		else
		{
			fault[0]++;
			fault[1]++;
		}
		//(2)
		if(abs(point[3].getY()-point[1].getY()-14)<=2
			&&abs(point[3].getX()-point[1].getX())<=2)
		{
		
		}
		else
		{
			fault[1]++;
			fault[3]++;
		}
		//(3)
		if(abs(point[3].getY()-point[2].getY())<=2
			&&abs(point[3].getX()-point[2].getX()-12)<=2)
		{
		
		}
		else
		{
			fault[2]++;
			fault[3]++;
		}
		//(4)
		if(abs(point[2].getY()-point[0].getY()-14)<=2
			&&abs(point[2].getX()-point[0].getX())<=2)
		{
		
		}
		else
		{
			fault[0]++;
			fault[2]++;
		}
		//(5)
		if(abs(point[4].getY()-point[1].getY()-7)<=2
			&&abs(point[1].getX()-point[4].getX()-8)<=2)
		{
		
		}
		else
		{
			fault[1]++;
			fault[4]++;
		}
		//(6)
		if(abs(point[3].getY()-point[4].getY()-7)<=2
			&&abs(point[3].getX()-point[4].getX()-8)<=2)
		{
		
		}
		else
		{
			fault[3]++;
			fault[4]++;
		}
		//(7)
		if(abs(point[4].getY()-point[0].getY()-5)<=2
			&&abs(point[4].getX()-point[0].getX()-2)<=2)
		{
		
		}
		else
		{
			fault[0]++;
			fault[4]++;
		}
		//(8)
		if(abs(point[2].getY()-point[4].getY()-5)<=2
			&&abs(point[4].getX()-point[2].getX()-2)<=2)
		{
		
		}
		else
		{
			fault[4]++;
			fault[2]++;
		}
		//(9)
		if(abs(point[2].getY()-point[1].getY()-14)<=2
			&&abs(point[1].getX()-point[2].getX()-10)<=2)
		{
		
		}
		else
		{
			fault[2]++;
			fault[1]++;
		}
		//(10)
		if(abs(point[3].getY()-point[0].getY()-14)<=2
			&&abs(point[3].getX()-point[0].getX()-10)<=2)
		{
		
		}
		else
		{
			fault[3]++;
			fault[0]++;
		}
		//找到那个没有错误的点
		for(i=0;i<5;i++)
		{
			if(fault[i]>=3)
			{
				//剔除
				leave--;
				tag[i]=false;				
			}
			//有效点
			else
			{				
				tag[i]=true;	
			}
		}

		//预测没有找到的点
		if(leave==4)
		{			
			if(tag[0]==false)
			{
				point[0].setX(point[2].getX());
				point[0].setY(point[1].getY());
			}
			else if(tag[1]==false)
			{
				point[1].setX(point[3].getX());
				point[1].setY(point[0].getY());
			}
			else if(tag[2]==false)
			{
				point[2].setX(point[0].getX());
				point[2].setY(point[3].getY());
			}
			else if(tag[3]==false)
			{
				point[3].setX(point[1].getX());
				point[3].setY(point[2].getY());
			}
			else if(tag[4]==false)
			{
				point[4].setX(point[0].getX()+2);
				point[4].setY(point[0].getY()+5);
			}

		}
		else if(leave==3)
		{
			//(1)
			if(tag[1]==false&&tag[0]==false)
			{
				point[1].setX(point[3].getX());
				point[1].setY(point[3].getY()-14);
				point[0].setX(point[2].getX());
				point[0].setY(point[2].getY()-14);
			} 
			else if(tag[1]==false&&tag[4]==false)
			{
				point[1].setX(point[3].getX());
				point[1].setY(point[0].getY());
				point[4].setX(point[0].getX()+2);
				point[4].setY(point[0].getY()+7);
			}
			else if(tag[1]==false&&tag[2]==false)
			{
				point[1].setX(point[3].getX());
				point[1].setY(point[0].getY());
				point[2].setX(point[0].getX());
				point[2].setY(point[3].getY());
			}
			else if(tag[2]==false&&tag[3]==false)
			{
				point[2].setX(point[0].getX());
				point[2].setY(point[0].getY()+14);
				point[3].setX(point[1].getX());
				point[3].setY(point[1].getY()+14);
			}
			else if(tag[3]==false&&tag[4]==false)
			{
				point[3].setX(point[1].getX());
				point[3].setY(point[2].getY());
				point[4].setX(point[0].getX()+2);
				point[4].setY(point[0].getY()+7);
			}
			else if(tag[0]==false&&tag[3]==false)
			{
				point[0].setX(point[2].getX());
				point[0].setY(point[1].getY());
				point[3].setX(point[1].getX());
				point[3].setY(point[2].getY());
			}
			else if(tag[2]==false&&tag[4]==false)
			{
				point[2].setX(point[0].getX());
				point[2].setY(point[3].getY());
				point[4].setX(point[0].getX()+2);
				point[4].setY(point[0].getY()+7);
			}
			else if(tag[0]==false&&tag[4]==false)
			{	
				point[0].setX(point[2].getX());
				point[0].setY(point[1].getY());
				point[4].setX(point[2].getX()+2);
				point[4].setY(point[2].getY()-7);
			}
			else if(tag[0]==false&&tag[2]==false)
			{
				point[0].setX(point[1].getX()-12);
				point[0].setY(point[1].getY());
				point[2].setX(point[3].getX()-12);
				point[2].setY(point[3].getY());
			}
			else if(tag[1]==false&&tag[3]==false)
			{
				point[1].setX(point[0].getX()+12);
				point[1].setY(point[0].getY());
				point[3].setX(point[2].getX()+12);
				point[3].setY(point[2].getY());
			}
		}
		pointNumber=leave;
	}
	else if(leave==4)
	{
		/*for(i=1;i<=4;i++)
		{
			fprintf(fpout,"%d,%d\t",log[i][0],log[i][1]);
		}
		fprintf(fpout,"\n");
		*/
		int memwho;
		//对其按照X轴排序
		for(i=1;i<=leave;i++)
		{
			for(j=i;j<=leave;j++)
			{
				if(log[j][0]<log[i][0])
				{
					long tmp=log[j][0];	
					log[j][0]=log[i][0];
					log[i][0]=tmp;
					tmp=log[j][1];	
					log[j][1]=log[i][1];
					log[i][1]=tmp;
				}
			}
		}
		
		//
		if(abs(log[4][0]-log[3][0]-8)<=3&&abs(log[3][0]-log[2][0]-4)<=2&&abs(log[2][0]-log[1][0])<=2)
		{
			//对其按y轴排序
			for(i=1;i<=3;i++)
			{
				for(j=i;j<=3;j++)
				{
					if(log[j][1]<log[i][1])
					{
						long tmp=log[j][0];	
						log[j][0]=log[i][0];
						log[i][0]=tmp;
						tmp=log[j][1];	
						log[j][1]=log[i][1];
						log[i][1]=tmp;
					}
				}
			}
			if(abs(log[2][1]-log[1][1]-7)<=2&&abs(log[2][0]-log[1][0]-4)<=2
				&&abs(log[3][1]-log[2][1]-7)<=2&&abs(log[2][0]-log[3][0]-4)<=2
				&&abs(log[3][1]-log[1][1]-14)<=2&&abs(log[1][1]-log[3][0])<=2)
			{
				point[0].setX(log[1][0]);
				point[0].setY(log[1][1]);
				point[4].setX(log[2][0]);
				point[4].setY(log[2][1]);
				point[2].setX(log[3][0]);
				point[2].setY(log[3][1]);
				tag[0]=true;			
				tag[2]=true;			
				tag[4]=true;				
			}
			if(abs(log[4][0]-point[0].getX()-12)<=2&&abs(log[4][1]-point[0].getY())<=2
				&&abs(log[4][0]-point[2].getX()-12)<=2&&abs(point[2].getY()-log[4][1]-14)<=2
				&&abs(log[4][0]-point[4].getX()-8)<=2&&abs(point[4].getY()-log[4][1]-8)<=2)
			{
				point[1].setX(log[4][0]);
				point[1].setY(log[4][1]);
				point[3].setX(point[1].getX());
				point[3].setY(point[2].getY());
				tag[1]=true;
			}
			else if(abs(log[4][0]-point[0].getX()-12)<=2&&abs(log[4][1]-point[0].getY()-14)<=2
				&&abs(log[4][0]-point[2].getX()-12)<=2&&abs(point[2].getY()-log[4][1])<=2
				&&abs(log[4][0]-point[4].getX()-8)<=2&&abs(log[4][1]-point[4].getY()-8)<=2)
			{
				point[3].setX(log[4][0]);
				point[3].setY(log[4][1]);
				point[1].setX(point[3].getX());
				point[1].setY(point[0].getY());
				tag[3]=true;
				
			}
		}
		else 
		{
			if(log[3][1]>log[4][1])
			{
				long tmp=log[3][1];
				log[3][1]=log[4][1];
				log[4][1]=tmp;
				tmp=log[3][0];
				log[3][0]=log[4][0];
				log[4][0]=tmp;
			}
			if(log[1][1]>log[2][1])
			{
				long tmp=log[1][1];
				log[1][1]=log[2][1];
				log[2][1]=tmp;
				tmp=log[1][0];
				log[1][0]=log[2][0];
				log[2][0]=tmp;
			}
			//5
			if(abs(log[4][0]-log[3][0])<=2&&abs(log[4][1]-log[3][1]-14)<=2
				&&abs(log[3][0]-log[2][0]-8)<=2&&abs(log[2][1]-log[3][1]-7)<=2
				&&abs(log[4][0]-log[2][0]-8)<=2&&abs(log[4][1]-log[2][1]-7)<=2
				&&abs(log[3][0]-log[1][0]-12)<=2&&abs(log[3][1]-log[1][1])<=2
				&&abs(log[4][0]-log[1][0]-12)<=2&&abs(log[4][1]-log[1][1]-14)<=2
				&&abs(log[2][0]-log[1][0]-4)<=2&&abs(log[2][1]-log[1][1]-7)<=2)
			{
				point[0].setX(log[1][0]);
				point[0].setY(log[1][1]);
				point[1].setX(log[3][0]);
				point[1].setY(log[3][1]);
				point[3].setX(log[4][0]);
				point[3].setY(log[4][1]);
				point[4].setX(log[2][0]);
				point[4].setY(log[2][1]);
				point[2].setX(point[0].getX());
				point[2].setY(point[3].getY());	
				tag[0]=true;
				tag[1]=true;			
				tag[3]=true;
				tag[4]=true;

			}
			//3
			else if(abs(log[4][0]-log[3][0])<=2&&abs(log[4][1]-log[3][1]-14)<=2
				&&abs(log[3][0]-log[2][0]-12)<=2&&abs(log[2][1]-log[3][1]-14)<=2
				&&abs(log[4][0]-log[2][0]-12)<=2&&abs(log[4][1]-log[2][1])<=2
				&&abs(log[3][0]-log[1][0]-12)<=2&&abs(log[3][1]-log[1][1])<=2
				&&abs(log[4][0]-log[1][0]-12)<=2&&abs(log[4][1]-log[1][1]-14)<=2
				&&abs(log[2][0]-log[1][0])<=2&&abs(log[2][1]-log[1][1]-14)<=2)
			{
				point[0].setX(log[1][0]);
				point[0].setY(log[1][1]);
				point[1].setX(log[3][0]);
				point[1].setY(log[3][1]);
				point[2].setX(log[2][0]);
				point[2].setY(log[2][1]);
				point[3].setX(log[4][0]);
				point[3].setY(log[4][1]);
				point[4].setX(point[0].getX()+4);
				point[4].setY(point[0].getY()+7);
				tag[0]=true;
				tag[1]=true;
				tag[2]=true;
				tag[3]=true;
				
			}
			//4
			else if(abs(log[4][0]-log[3][0])<=2&&abs(log[4][1]-log[3][1]-14)<=2
				&&abs(log[3][0]-log[2][0]-12)<=2&&abs(log[2][1]-log[3][1]-14)<=2
				&&abs(log[4][0]-log[2][0]-12)<=2&&abs(log[4][1]-log[2][1])<=2
				&&abs(log[3][0]-log[1][0]-8)<=2&&abs(log[1][1]-log[3][1]-7)<=2
				&&abs(log[4][0]-log[1][0]-8)<=2&&abs(log[4][1]-log[1][1]-7)<=2
				&&abs(log[1][0]-log[2][0]-4)<=2&&abs(log[2][1]-log[1][1]-7)<=2)
			{
				point[4].setX(log[1][0]);
				point[4].setY(log[1][1]);
				point[1].setX(log[3][0]);
				point[1].setY(log[3][1]);
				point[2].setX(log[2][0]);
				point[2].setY(log[2][1]);
				point[3].setX(log[4][0]);
				point[3].setY(log[4][1]);
				point[0].setX(point[2].getX());
				point[0].setY(point[1].getY());
			
				tag[1]=true;
				tag[2]=true;
				tag[3]=true;
				tag[4]=true;

			}
		
		
		}
		
		leave=0;
		for(i=0;i<5;i++)
		{
			if(tag[i]==true)
			{
				leave++;
			}
			
		}
		pointNumber=leave;
	}
	else if(leave==3)
	{
		//直接分类在分类时就判断一旦有错的就停止
		//对其按照X轴排序
		for(i=1;i<=leave;i++)
		{
			for(j=i;j<=leave;j++)
			{
				if(log[j][0]<log[i][0])
				{
					long tmp=log[j][0];	
					log[j][0]=log[i][0];
					log[i][0]=tmp;
					tmp=log[j][1];	
					log[j][1]=log[i][1];
					log[i][1]=tmp;
				}
			}
		}
		//(1)
		if(log[3][0]-log[1][0]<=4&&abs(log[3][1]-(log[1][1]+log[2][1])/2)<=2)
		{
			point[4].setX(log[3][0]);
			point[4].setY(log[3][1]);
			tag[4]=true;
			tag[0]=true;
			tag[2]=true;
			if(abs(log[1][1]-log[2][1]-14)<=2)
			{
				point[0].setX(log[2][0]);
				point[0].setY(log[2][1]);
				point[2].setX(log[1][0]);
				point[2].setY(log[1][1]);
				
			}
			else if(abs(log[2][1]-log[1][1]-14)<=2)
			{
				point[0].setX(log[1][0]);
				point[0].setY(log[1][1]);
				point[2].setX(log[2][0]);
				point[2].setY(log[2][1]);
			}
		}
		//(2)
		else if(log[2][0]-log[1][0]>=6&&log[3][0]-log[1][0]>=6)
		{
			tag[1]=true;
			tag[3]=true;
			
			if(abs(log[2][1]-log[3][1]-14)<=2)
			{
				point[1].setX(log[3][0]);
				point[1].setY(log[3][1]);
				point[3].setX(log[2][0]);
				point[3].setY(log[2][1]);
			}
			else if(abs(log[3][1]-log[2][1]-14)<=2)
			{
				point[1].setX(log[2][0]);
				point[1].setY(log[2][1]);
				point[3].setX(log[3][0]);
				point[3].setY(log[3][1]);
			}
			if(abs(log[1][1]-point[1].getY())<=2)
			{
				point[0].setX(log[1][0]);
				point[0].setY(log[1][1]);
				tag[0]=true;
			}
			else if(abs(log[1][1]-(point[1].getY()+point[3].getY())/2)<=2)
			{
				point[4].setX(log[1][0]);
				point[4].setY(log[1][1]);
				tag[4]=true;
			}
			else if(abs(log[1][0]-point[3].getY())<=2)
			{
				point[2].setX(log[1][0]);
				point[2].setY(log[1][1]);
				tag[2]=true;
			}		
		}
		//(3)
		else if(log[3][0]-log[1][0]>=5&&log[3][0]-log[2][0]>=5)
		{
			//红色
			if(abs(log[2][0]-log[1][0]-4)<=2&&abs(log[2][1]-log[1][1]-6)<=2)
			{
				point[0].setX(log[1][0]);
				point[0].setX(log[1][1]);
				point[4].setX(log[2][0]);
				point[4].setX(log[2][1]);
				tag[0]=true;
				tag[4]=true;
				if(abs(log[3][0]-log[1][0]-12)<=2&&abs(log[1][1]-log[3][1])<=2)
				{
					point[1].setX(log[3][0]);
					point[1].setX(log[3][1]);
					tag[1]=true;
				}
				else if(abs(log[3][0]-log[1][0]-12)<=2&&abs(log[1][1]-log[3][1]-14)<=2)
				{
					point[3].setX(log[3][0]);
					point[3].setX(log[3][1]);
					tag[3]=true;
				}
			}
			//黄色
			else if(abs(log[2][0]-log[1][0]-2)<=2&&abs(log[2][1]-log[1][1]-14)<=2)
			{
				point[2].setX(log[2][0]);
				point[2].setX(log[2][1]);
				point[0].setX(log[1][0]);
				point[0].setX(log[1][1]);
				tag[0]=true;
				tag[2]=true;
				if(abs(log[3][0]-point[0].getX()-12)<=2&&abs(log[3][1]-point[0].getY())<=2)
				{
					point[1].setX(log[3][0]);
					point[1].setX(log[3][1]);
					tag[1]=true;
				}
				else if(abs(log[3][0]-point[0].getX()-12)<=2&&abs(log[3][1]-point[2].getY())<=2)
				{
					point[3].setX(log[3][0]);
					point[3].setX(log[3][1]);
					tag[3]=true;
				}
			}
			//黄色
			else if(abs(log[1][0]-log[2][0]-2)<=2&&abs(log[2][1]-log[1][1]-14)<=2)
			{
				point[0].setX(log[2][0]);
				point[0].setX(log[2][1]);
				point[2].setX(log[1][0]);
				point[2].setX(log[1][1]);
				tag[0]=true;
				tag[2]=true;
				if(abs(log[3][0]-point[0].getX()-12)<=2&&abs(log[3][1]-point[0].getY())<=2)
				{
					point[1].setX(log[3][0]);
					point[1].setX(log[3][1]);
					tag[1]=true;
				}
				else if(abs(log[3][0]-point[0].getX()-12)<=2&&abs(log[3][1]-point[2].getY())<=2)
				{
					point[3].setX(log[3][0]);
					point[3].setX(log[3][1]);
					tag[3]=true;
				}
			}
			//橙色
			else if(abs(log[2][0]-log[1][0]-4)<=2&&abs(log[1][1]-log[2][1]-6)<=2)
			{
				point[2].setX(log[1][0]);
				point[2].setX(log[1][1]);
				point[4].setX(log[2][0]);
				point[4].setX(log[2][1]);
				tag[2]=true;
				tag[4]=true;
				if(abs(point[2].getY()-log[3][1]-14)<=2&&abs(log[3][0]-point[2].getX()-12)<=2)
				{
					point[1].setX(log[3][0]);
					point[1].setY(log[3][1]);
					tag[1]=true;
				}
				else if(abs(log[3][1]-point[2].getY())<=2&&abs(log[3][0]-point[2].getX()-12)<=2)
				{
					point[3].setX(log[3][0]);
					point[3].setY(log[3][1]);
					tag[3]=true;
				}
			}
		}//end (3)
		if(tag[1]==false&&tag[0]==false)
			{
				point[1].setX(point[3].getX());
				point[1].setY(point[3].getY()-14);
				point[0].setX(point[2].getX());
				point[0].setY(point[2].getY()-14);
			} 
			else if(tag[1]==false&&tag[4]==false)
			{
				point[1].setX(point[3].getX());
				point[1].setY(point[0].getY());
				point[4].setX(point[0].getX()+4);
				point[4].setY(point[0].getY()+7);
			}
			else if(tag[1]==false&&tag[2]==false)
			{
				point[1].setX(point[3].getX());
				point[1].setY(point[0].getY());
				point[2].setX(point[0].getX());
				point[2].setY(point[3].getY());
			}
			else if(tag[2]==false&&tag[3]==false)
			{
				point[2].setX(point[0].getX());
				point[2].setY(point[0].getY()+14);
				point[3].setX(point[1].getX());
				point[3].setY(point[1].getY()+14);
			}
			else if(tag[3]==false&&tag[4]==false)
			{
				point[3].setX(point[1].getX());
				point[3].setY(point[2].getY());
				point[4].setX(point[0].getX()+4);
				point[4].setY(point[0].getY()+7);
			}
			else if(tag[0]==false&&tag[3]==false)
			{
				point[0].setX(point[2].getX());
				point[0].setY(point[1].getY());
				point[3].setX(point[1].getX());
				point[3].setY(point[2].getY());
			}
			else if(tag[2]==false&&tag[4]==false)
			{
				point[2].setX(point[0].getX());
				point[2].setY(point[3].getY());
				point[4].setX(point[0].getX()+4);
				point[4].setY(point[0].getY()+7);
			}
			else if(tag[0]==false&&tag[4]==false)
			{	
				point[0].setX(point[2].getX());
				point[0].setY(point[1].getY());
				point[4].setX(point[2].getX()+4);
				point[4].setY(point[2].getY()-7);
			}
			else if(tag[0]==false&&tag[2]==false)
			{
				point[0].setX(point[1].getX()-12);
				point[0].setY(point[1].getY());
				point[2].setX(point[3].getX()-12);
				point[2].setY(point[3].getY());
			}
			else if(tag[1]==false&&tag[3]==false)
			{
				point[1].setX(point[0].getX()+12);
				point[1].setY(point[0].getY());
				point[3].setX(point[2].getX()+12);
				point[3].setY(point[2].getY());
			}
			
			int i;
			leave=0;
			for(i=0;i<5;i++)
			{
				if(tag[i]==true)
					leave++;
			}			
			pointNumber=leave;
	}
	
}


/*********************************************************************
*
*	功能：对瞳孔图像进行光斑去除，做填充处理，同时重新计算圆心的坐标
*	参数：data				图像缓冲区
*		  x,y				处理块的起点
*			r				瞳孔的半径
*	条件：预先设置好光斑阈值
*	返回：返回一个新的圆心点point
***************************************************************/
Point Preprocess::fill(BYTE *data,int x,int y,float r)
{
	float newR=r;
	float oldR=0;
	float newX=x;
	float newY=y;
	long  xx;
	long  yy;
	int count;
	int i,j;
	Point point;
	int tmp=0;
	while(abs(newR-oldR)>=0.2)
	{	
		tmp++;
		count=0;
		xx=0;
		yy=0;
		for(i=(int)(newX-newR);i<(int)(newX+newR);i++)
		{
			for(j=(int)(newY-newR);j<(int)(newY+newR);j++)
			{
				//如果在以(newX,newY)为圆心newR为半径的圆范围内
				if((i-newX)*(i-newX)+(j-newY)*(j-newY)<=newR*newR)
				{	
					//灰度大于阈值的点即为光斑点，进行去除填充
					if(*(data+i*width*3+j*3)>threshold)
					{
						*(data+i*width*3+j*3)=50;
						*(data+i*width*3+j*3+1)=50;		//将光斑点的灰度值统一设置为50
						*(data+i*width*3+j*3+2)=50;
					}
					count++;
					xx+=i;		//xx,yy分别保存在以(newX,newY)为圆心newR为半径的圆范围内的点的x，y累加值
					yy+=j;
				}
			}
		}//end for 循环
		oldR=newR;
		newR=sqrt((float)count/3.1415926);
		newX=xx/count;
		newY=yy/count;			//统计完成后，重新赋值圆心以及半径
	}
	point.setX(newX);
	point.setY(newY);
//	fprintf(fpout,"%d\n",tmp);
	return point;				//返回圆心
}

/************************************************************************************
 * 功能：以(i,j)为起点在以(x,y)为区域起点的768*576搜索范围内进行广度优先搜索光斑
 * 参数：*m_pImageBuffer	图像缓冲区
		 x,y				搜索区域起始点(768*576区域中的(0,0))
		 i,j				搜索起始点
 * 结果：搜索过程中对搜索过的点进行backup标记同时将大于阈值的点入队列queue
		 同时pointCount[nowCount]对点片进行计数，log[nowCount][]对点片x，y值累加
 ************************************************************************************/
void Preprocess::glintSearch(BYTE *m_pImageBuffer ,int x,int y,int i,int j)
{
	queueCount=0;
	head=0;
	tail=0;
	width = 768;
	height = 576;
	//更改访问标识
	backup[i][j]=true;//在外层已经设过true了
	//数据入队列
	queueCount++;
	queue[tail].setX(i);
	queue[tail].setY(j);
	tail=(tail++)%3900;
	pointCount[nowCount]++;
	
	//当队列不空就进行下面的动作
	while(queueCount>0&&queueCount<=3900)
	{	
		//出队列
		queueCount--;
		int xx=queue[head].getX();
		int yy=queue[head].getY();
		//出队列之后把他的灰度变为65		？？？？
		
		
		head=((head+1)%3900);
		log[nowCount][0]=  log[nowCount][0] + xx  ;		//将点片保存在log中
		log[nowCount][1]=  log[nowCount][1] + yy  ;
		int tmpDirect;
		for(tmpDirect=0;tmpDirect<8;tmpDirect++)
		{
			int xi=xx+Direction[tmpDirect][0];
			int yi=yy+Direction[tmpDirect][1];
			
			
			//判定是否符在搜索的范围内
         if( xi >= x && xi < x+scope_height && yi >= y && yi < y+scope_width && (x+scope_height)<height && (y+scope_width)<width)			
		 {
				//看是否访问过
				if( backup[xi][yi] == false )
				{
					backup[xi][yi] =true;
					int tmp=0;
					int index = xi*width*3+yi*3;		
					tmp = *(m_pImageBuffer+index);					
					//看是否满足阈值
					//	cout<<tmp<<" ";
					if(tmp >= threshold)
					{
						pointCount[nowCount]++;
						//入队
						queueCount++;
						queue[tail].setX((float)xi);
						queue[tail].setY((float)yi);
						tail=(tail++)%3900;	
						//					cvCircle(pImg,cvPoint(yi,xi),1,cvScalar(0,0,255),-1);
					}					
				}
			}		
		}//end for 循环
		
	}//end while循环	
}


/***************************************************************************************************************
 *	功能：对以(x,y)为中心的60*60矩形区域下半部分的进行直方图分析，并对直方图进行平滑处理，计算出瞳孔灰度阈值
 *	参数：	*data		图像缓冲区
			x,y			区域中心点
 *	返回值：返回区域瞳孔阈值
 *****************************************************************************************************************/
int Preprocess::HistogramDown(BYTE* data,int x,int y)
{
	if(x>50&&x<450&&y>50&&y<550)	
	{
		int *color;
		int *target;
		color=(int*)malloc(300*sizeof(int));
		target=(int*)malloc(300*sizeof(int));
		memset(color,0,300*sizeof(int));

		int	swidth=60;//查找的宽
		int sheight=60;//查找的高
		int i,j;
		//统计直方图
		for(i=x-sheight/2;i<=x;i++)
		{
			for(j=y-swidth/2;j<y+swidth/2;j++)
			{
				int tmp=i*width*3+j*3;
				color[*(data+tmp)]++;			//统计区域内该灰度值的点的个数
			}
		}
		
		//显示源直方图
		for(i=0;i<255;i++)
		{
			if(color[i])						//color[i] == 灰度值为i的点的个数
			{
				int xx=(color[i])%100;			//为什么要对100求余？
				int zz;
				for(zz=452;zz<xx+452;zz++)		//以452~xx+452表示点的个数，在图像上绘制直方图
				{
					*(data+zz*width*3+(i)*3)=0;			
					*(data+zz*width*3+(i)*3+1)=125;
					*(data+zz*width*3+(i)*3+2)=90;
				}
			}
		}
		//显示原点线和终点线
		int zz;
		for(zz=452;zz<552;zz++)		//i==0,绘制原点线
		{
			*(data+zz*width*3+0*3)=0;
			*(data+zz*width*3+0*3+1)=125;
			*(data+zz*width*3+0*3+2)=90;
		}
		for(zz=452;zz<552;zz++)		//i==255,绘制终点线
		{
			*(data+zz*width*3+255*3)=0;
			*(data+zz*width*3+255*3+1)=125;
			*(data+zz*width*3+255*3+2)=90;
		}
		//显示阈值
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+50*3)=0;			//阈值就等于50？
			*(data+zz*width*3+50*3+1)=225;
			*(data+zz*width*3+50*3+2)=0;
		}
		//对直方图进行平滑处理
		int oo=6;
		for ( j=0;j<oo;j++)
		{
			target[0] = (color[0] + color[1]) / 2;
			for (int i=1;i<=254;i++)
				target[i] = (color[i-1] + color[i] + color[i+1])/3;
			target[255] = (color[254] + color[255]) / 2;
			int *tmp = color;
			color = &target[0];
			target = tmp;
		}
		//显示平滑后的直方图
		for(i=0;i<255;i++)
		{
			if(color[i])
			{
				int xx=(color[i])%100;
				int zz;
				for(zz=452;zz<xx+452;zz++)
				{
					*(data+zz*width*3+(i+255)*3)=0;
					*(data+zz*width*3+(i+255)*3+1)=125;
					*(data+zz*width*3+(i+255)*3+2)=90;
				}
			}
		}
		//显示原点线和终点线
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+255*3)=0;
			*(data+zz*width*3+255*3+1)=125;
			*(data+zz*width*3+255*3+2)=90;
		}
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+510*3)=0;
			*(data+zz*width*3+510*3+1)=125;
			*(data+zz*width*3+510*3+2)=90;
		}
		//显示阈值
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+315*3)=0;
			*(data+zz*width*3+315*3+1)=255;
			*(data+zz*width*3+315*3+2)=0;
		}
		//寻找我们要的波谷  为什么是波谷而不是波峰？		
		bool can;		
		for (i=55 ;i<150;i++)
		{
			can=true;
			for (j=-6;j<=6;j++)
			{
				if (color[i]>color[i+j])
				{
					can=false;
				}						
			}					
			if (can)
				break;
		}
		//显示算的的阈值

		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+(i)*3)=255;
			*(data+zz*width*3+(i)*3+1)=0;
			*(data+zz*width*3+(i)*3+2)=0;
		}	
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+(i+255)*3)=255;
			*(data+zz*width*3+(i+255)*3+1)=0;
			*(data+zz*width*3+(i+255)*3+2)=0;
		}
		free(color);
		free(target);
		return i;
	}
	else
	{
		return	0;
	}
}

/**********************************************************************************************************
 *	功能：对以(x,y)为中心点的60*60区域的上半部分进行直方图分析，并对直方图进行平滑处理，计算出瞳孔灰度阈值
 *	参数：	*data	图像缓冲区
			x,y		区域中心点坐标
 *	返回值：区域瞳孔阈值
 ***********************************************************************************************************/
int Preprocess::HistogramUp(BYTE* data,int x,int y)
{
	if(x>50&&x<450&&y>50&&y<550)
	{
		int *color;
		int *target;
		color=(int*)malloc(300*sizeof(int));
		target=(int*)malloc(300*sizeof(int));
		memset(color,0,300*sizeof(int));

		int	swidth=60;//查找的宽
		int sheight=60;//查找的高
		int i,j;
		//统计直方图
		for(i=x;i<=x+sheight/2;i++)
		{
			for(j=y-swidth/2;j<y+swidth/2;j++)
			{
				int tmp=i*width*3+j*3;
				color[*(data+tmp)]++;
			}
		}		
		//显示源直方图
		for(i=0;i<255;i++)
		{
			if(color[i])
			{
				int xx=(color[i])%100;
				int zz;
				for(zz=452;zz<xx+452;zz++)
				{
					*(data+zz*width*3+(i+510)*3)=0;
					*(data+zz*width*3+(i+510)*3+1)=125;
					*(data+zz*width*3+(i+510)*3+2)=90;
				}
			}
		}
		//显示原点线和终点线
		int zz;
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+510*3)=0;
			*(data+zz*width*3+510*3+1)=125;
			*(data+zz*width*3+510*3+2)=90;
		}
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+765*3)=0;
			*(data+zz*width*3+765*3+1)=125;
			*(data+zz*width*3+765*3+2)=90;
		}
		//显示阈值
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+560*3)=0;
			*(data+zz*width*3+560*3+1)=225;
			*(data+zz*width*3+560*3+2)=0;
		}
		//对直方图进行平滑处理
		int oo=6;
		for ( j=0;j<oo;j++)
		{
			target[0] = (color[0] + color[1]) / 2;
			for (int i=1;i<=254;i++)
				target[i] = (color[i-1] + color[i] + color[i+1])/3;
			target[255] = (color[254] + color[255]) / 2;
			int *tmp = color;
			color = &target[0];
			target = tmp;
		}
		//显示平滑后的直方图
		for(i=0;i<255;i++)
		{
			if(color[i])
			{
				int xx=(color[i])%100;
				int zz;
				for(zz=352;zz<xx+352;zz++)
				{
					*(data+zz*width*3+(i+510)*3)=0;
					*(data+zz*width*3+(i+510)*3+1)=125;
					*(data+zz*width*3+(i+510)*3+2)=90;
				}
			}
		}
		//显示原点线和终点线
		for(zz=352;zz<452;zz++)
		{
			*(data+zz*width*3+510*3)=0;
			*(data+zz*width*3+510*3+1)=125;
			*(data+zz*width*3+510*3+2)=90;
		}
		for(zz=352;zz<452;zz++)
		{
			*(data+zz*width*3+765*3)=0;
			*(data+zz*width*3+765*3+1)=125;
			*(data+zz*width*3+765*3+2)=90;
		}
		//显示阈值
		for(zz=352;zz<452;zz++)
		{
			*(data+zz*width*3+560*3)=0;
			*(data+zz*width*3+560*3+1)=255;
			*(data+zz*width*3+560*3+2)=0;
		}
		//寻找我们要的波谷		
		bool can;		
		for (i=55 ;i<150;i++)
		{
			can=true;
			for (j=-6;j<=6;j++)
			{
				if (color[i]>color[i+j])
				{
					can=false;
				}						
			}					
			if (can)
				break;
		}
		//显示算的的阈值

		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+(i+510)*3)=255;
			*(data+zz*width*3+(i+510)*3+1)=0;
			*(data+zz*width*3+(i+510)*3+2)=0;
		}	
		for(zz=352;zz<452;zz++)
		{
			*(data+zz*width*3+(i+510)*3)=255;
			*(data+zz*width*3+(i+510)*3+1)=0;
			*(data+zz*width*3+(i+510)*3+2)=0;
		}
		free(color);
		free(target);
		return i;
	}
	else
	{
		return 0;
	}
}

/***************************************************************************************************
 *	功能：对以(x,y)为起点的scope_heigh*scope_width区域进行直方图分析，并在平滑后计算出瞳孔灰度阈值
 *	参数：	*data	图像缓冲区
			x,y		区域起点
 *	返回值：阈值
 ***************************************************************************************************/
int Preprocess::prepupil(BYTE *data,int x,int y)
{
	width=768;
	if(x>30&&x<546&&y>30&&y<736)
	{
		
		int *color;
		int *target;
		long total=0;
		color=(int*)malloc(300*sizeof(int));
		target=(int*)malloc(300*sizeof(int));
		//int color2[300];
		memset(color,0,300*sizeof(int));
		int i,j;
		//统计直方图
		for(i=x;i<x+scope_height;i++)
		{
			for(j=y;j<y+scope_width;j++)
			{
				int tmp=i*width*3+j*3;
				color[*(data+tmp)]++;
				total+=*(data+tmp);
			}
		}
		//fprintf(fpout,"%d\n",total/(80*80));
		//看看白天的灰度值是多少
		total=total/(scope_width*scope_height);
		//fprintf(fpout,"%d\n",total);
		//显示源直方图
		for(i=0;i<255;i++)
		{
			if(color[i])
			{
				int xx=(color[i])%100;	
				int zz;
				for(zz=452;zz<xx+452;zz++)
				{
					*(data+zz*width*3+(i+20)*3)=0;
					*(data+zz*width*3+(i+20)*3+1)=125;
					*(data+zz*width*3+(i+20)*3+2)=90;
				}
			}
		}		
		//显示原点线和终点线
		int zz;
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+20*3)=0;
			*(data+zz*width*3+20*3+1)=125;
			*(data+zz*width*3+20*3+2)=90;
		}
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+276*3)=0;
			*(data+zz*width*3+276*3+1)=125;
			*(data+zz*width*3+276*3+2)=90;
		}

		//对直方图进行平滑处理
		int oo=9;
		for ( j=0;j<oo;j++)
		{
			target[0] = (color[0] + color[1]) / 2;
			for (int i=1;i<=254;i++)
				target[i] = (color[i-1] + color[i] + color[i+1])/3;
			target[255] = (color[254] + color[255]) / 2;
			int *tmp = color;
			color = &target[0];
			target = tmp;
		}
		//显示平滑后的直方图
		for(i=0;i<255;i++)
		{
			if(color[i])
			{
				int xx=(color[i])%100;
				int zz;
				for(zz=452;zz<xx+452;zz++)
				{
					*(data+zz*width*3+(i+295)*3)=0;
					*(data+zz*width*3+(i+295)*3+1)=125;
					*(data+zz*width*3+(i+295)*3+2)=90;
				}
			}
		}
		//显示原点线和终点线
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+295*3)=0;
			*(data+zz*width*3+295*3+1)=125;
			*(data+zz*width*3+295*3+2)=90;
		}
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+550*3)=0;
			*(data+zz*width*3+550*3+1)=125;
			*(data+zz*width*3+550*3+2)=90;
		}
		
		//寻找我们要的波谷	
		bool can;		
		for (i=30 ;i<100;i++)
		{
			can=true;
			for (j=-5;j<=5;j++)
			{
				// 波谷
				if (color[i]>color[i+j])
				{
					can=false;
				}	
			}					
			if (can)
				break;
		}
		//显示算的的阈值

		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+(i+20)*3)=255;
			*(data+zz*width*3+(i+20)*3+1)=0;
			*(data+zz*width*3+(i+20)*3+2)=0;
		}
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+(i+295)*3)=255;
			*(data+zz*width*3+(i+295)*3+1)=0;
			*(data+zz*width*3+(i+295)*3+2)=0;
		}
		free(color);
		free(target);
		return i;
	}
	else
	{
		return 0;
	}
}

/****************************************************************
*
*	功能：寻找瞳孔的边界，进行椭圆拟合，返回瞳孔中心点
*	参数：m_pImageBuffer		图像缓冲区
*		  x，y					搜索区域的首地址
*	条件：调用之前先设定阈值和搜索范围,设置的搜索范围比实际要大6
*
*****************************************************************/
Point Preprocess::pupil(BYTE *m_pImageBuffer,int x,int y)
{
	PupilBFS(m_pImageBuffer,x,y);//瞳孔边缘点检测，检测到的边缘点保存在数组Point queue[]中
	int count= NumOfVertex ;	 //瞳孔边缘点个数
	int i;
	int k;
	Point point;
	point.setX(x+40);//0
	point.setY(y+40);//0
	//进行4遍假点的剔除
	for(i=0;i<4;i++)
	{
		//椭圆拟合的数据结构
		CvPoint2D32f *PointArray2D32f;
		CvBox2D32f *box;
		PointArray2D32f = (CvPoint2D32f*)malloc(count*sizeof(CvPoint2D32f));
		box = (CvBox2D32f *)malloc(sizeof(CvBox2D32f));
		//进行椭圆拟合
		if(count>=6)
		{
			for (k=0;k<count;k++)
			{
				PointArray2D32f[k].x=(float)queue[k].getX();
				PointArray2D32f[k].y=(float)queue[k].getY();				
			}
			//拟合当前轮廓
			cvFitEllipse(PointArray2D32f,count,box);
		}
		//否则跳出
		else
		{
			//释放内存
			free(PointArray2D32f);
			free(box);
			break;
		}

		//剔除假点
		int j=0;
		for(k=0;k<count;k++)
		{
			//得到椭圆的中心
			float x;
			float y;
			x=box->center.x;
			y=box->center.y;
			//得到队列中的点
			float x1=queue[k].getX();
			float y1=queue[k].getY();
			//算出这个点到椭圆中心的距离
			float t1=sqrt( (x-x1)*(x-x1) + (y-y1)*(y-y1) );
			//计算余弦值
			float cs=(float)(x1-x)/t1;
			//计算反余弦的值
			float sit=acos(cs);
			//如果在三四限像
			if( (y1-y) < 0 )
			{
				sit=2*M_PI - sit;	
			}
			//计算sit2的值
			float sit2=sit - box->angle;
			//找到椭圆的长轴
			float a;
			float b;
			if(box->size.height >box->size.width)
			{
				a=box->size.height/2;
				b=box->size.width/2;
			}
			else
			{
				b=box->size.height/2;
				a=box->size.width/2;
			}
			float t2=sqrt(  ( a * cos( sit2 ) ) * ( a * cos( sit2 ) ) + ( b * sin( sit2 ) ) * ( b * sin( sit2 ) ) );
			//对假点进行剔除
			if(abs(t1-t2)<0.8)
			{
				//进行涂色
				int tmpx=queue[k].getX();
				int tmpy=queue[k].getY();
				if(i==3)
				{
					*( m_pImageBuffer+ tmpx*768*3+tmpy*3+1)=255;
				}
				queue[j].setX(queue[k].getX());
				queue[j].setY(queue[k].getY());
				j++;
			}
			
		}
		count=j;
		//end剔除假点
		
		//如果没有问题就可以传出了
		if(i==3)
		{
			point.setX(box->center.x);
			point.setY(box->center.y);
		}
		//释放内存
		free(PointArray2D32f);
		free(box);
	}

   
	return point;	
}

/*****************************************************************************
 *	功能：瞳孔边缘点检测
 *	参数：	*m_pImageBuffer		图像缓冲区
			xi,yi				区域检测起始点
 *	条件：瞳孔中心点pupilCenter
 *	结果：将检测到的瞳孔边缘点保存到数组Point queue[]中
 ****************************************************************************/
void Preprocess::PupilBFS(BYTE *m_pImageBuffer,int xi,int yi)
{
	memset(queue,0,4000*sizeof(Point));	
	NumOfVertex=0;

	BYTE *p=NULL,*q=NULL;
	int i,j;
	for ( i=xi+2;i<xi+scope_height-2;i++)
	{
		p = m_pImageBuffer + i * width * 3;
		for (j=yi+2;j<yi+scope_width-2;j++)
		{
			
			q = p + j * 3;
			//看是否满足阈值
			if ( *q <= threshold )
			{
				
				//如果这个点在瞳孔中心的上边
				if(i>pupilCenter.getX())
				{
					//如果这个点在瞳孔中心的右上边
					if(j<pupilCenter.getY())
					{
						//进行边缘检测，若为边缘点，再往右上灰度大于阈值，往左下小于阈值(一维边缘检测算子)
						if( 
							*( m_pImageBuffer + (i+1) * width* 3 + (j-1)*3  ) > threshold
							&&*(   m_pImageBuffer + (i+2) * width * 3 + (j-2)*3  ) > threshold
							&&*(m_pImageBuffer + (i-1) * width * 3 + (j+1)*3) < threshold
							&&*(m_pImageBuffer + (i-2) * width * 3 + (j+2)*3) < threshold
						  )
						{
							queue[NumOfVertex].setX(i);
							queue[NumOfVertex++].setY(j);
						}
					}
					//如果这个点在瞳孔中心的左上边
					else if(j>pupilCenter.getY())
					{
						//进行边缘检测
						if( *(m_pImageBuffer + (i+1) * width * 3 + (j+1)*3) > threshold
							&&*(m_pImageBuffer + (i+2) * width * 3 + (j+2)*3) > threshold
							&&*(m_pImageBuffer + (i-1) * width * 3 + (j-1)*3) < threshold
							&&*(m_pImageBuffer + (i-2) * width * 3 + (j-2)*3) < threshold
							)
						{
							queue[NumOfVertex].setX(i);
							queue[NumOfVertex++].setY(j);
						}
					}
					//在瞳孔中心的正上方
					else
					{
						//进行边缘检测
						if( *(m_pImageBuffer + (i+1) * width * 3 + (j)*3) > threshold
							&&*(m_pImageBuffer + (i+2) * width * 3 + (j)*3) > threshold
							&&*(m_pImageBuffer + (i-1) * width * 3 + (j)*3) < threshold
							&&*(m_pImageBuffer + (i-2) * width * 3 + (j)*3) < threshold
							)
						{
							queue[NumOfVertex].setX(i);
							queue[NumOfVertex++].setY(j);
						}
					}
				}
				//如果这个点在瞳孔中心的下方
				else if(i<pupilCenter.getX())
				{
					//在瞳孔的右下方
					if(j<pupilCenter.getY())
					{
						//进行边缘检测
						if( *(m_pImageBuffer + (i-1) * width * 3 + (j-1)*3) > threshold
							&&*(m_pImageBuffer + (i-2) * width * 3 + (j-2)*3) > threshold
							&&*(m_pImageBuffer + (i+1) * width * 3 + (j+1)*3) < threshold
							&&*(m_pImageBuffer + (i+2) * width * 3 + (j+2)*3) < threshold
							)
						{
							queue[NumOfVertex].setX(i);
							queue[NumOfVertex++].setY(j);
						}	
					}
					//在瞳孔的左下方
					else if(j>pupilCenter.getY())
					{
						//进行边缘检测
						if( *(m_pImageBuffer + (i-1) * width * 3 + (j+1)*3) > threshold
							&&*(m_pImageBuffer + (i-2) * width * 3 + (j+2)*3) > threshold
							&&*(m_pImageBuffer + (i+1) * width * 3 + (j-1)*3) < threshold
							&&*(m_pImageBuffer + (i+2) * width * 3 + (j-2)*3) < threshold
							)
						{
							queue[NumOfVertex].setX(i);
							queue[NumOfVertex++].setY(j);
						}
					}
					//在瞳孔的正下方
					else
					{
						if( *(m_pImageBuffer + (i-1) * width * 3 + (j)*3) > threshold
							&&*(m_pImageBuffer + (i-2) * width * 3 + (j)*3) > threshold
							&&*(m_pImageBuffer + (i+1) * width * 3 + (j)*3) < threshold
							&&*(m_pImageBuffer + (i+2) * width * 3 + (j)*3) < threshold
							)
						{
							queue[NumOfVertex].setX(i);
							queue[NumOfVertex++].setY(j);
						}
					}
				}
				//和瞳孔中心在一条线上
				else
				{
					//在瞳孔的右边
					if(j<pupilCenter.getY())
					{
						if( *(m_pImageBuffer + (i) * width * 3 + (j-1)*3) > threshold
							&&*(m_pImageBuffer + (i) * width * 3 + (j-2)*3) > threshold
							&&*(m_pImageBuffer + (i) * width * 3 + (j+1)*3) < threshold
							&&*(m_pImageBuffer + (i) * width * 3 + (j+2)*3) < threshold
							)
						{
							queue[NumOfVertex].setX(i);
							queue[NumOfVertex++].setY(j);
						}
					}
					//在瞳孔的左边
					else if(i>pupilCenter.getY())
					{
						if( *(m_pImageBuffer + (i) * width * 3 + (j+1)*3) > threshold
							&&*(m_pImageBuffer + (i) * width * 3 + (j+2)*3) > threshold
							&&*(m_pImageBuffer + (i) * width * 3 + (j-1)*3) < threshold
							&&*(m_pImageBuffer + (i) * width * 3 + (j-2)*3) < threshold
							)
						{
							queue[NumOfVertex].setX(i);
							queue[NumOfVertex++].setY(j);
						}
					}
					//有一种情况没有考虑就是是瞳孔那个点的情况，那个点一定不是边缘点
				}
				
			}
		}
	}

}


/*********************************************************************
 *	功能：
 *	参数：*m_pImageBuffer	图像缓冲区
 *********************************************************************/
void Preprocess::refine(BYTE* m_pImageBuffer)
{
	int i,j;
	float diff[4];//存放差值
	Point bb[5];//存放找到的点
	int pos;//记录那个梯度最大值的位置
	int pos1;//记录点三个点
	for(i=0;i<NumOfVertex;i++)
	{
		//先判断他们所处的区域
		//处在位置(1)
		if( abs( queue[i].getX()-pupilCenter.getX() ) >= abs( queue[i].getY()-pupilCenter.getY() ) )
		{
			//得到他的斜率
			float k= (float)(queue[i].getY()-pupilCenter.getY())/( queue[i].getX() - pupilCenter.getX() );
			//找出他旁边的五个点
			for(j=queue[i].getX()-2;j<=queue[i].getX()+2;j++)
			{
				int tm=j-queue[i].getX()+2;
				int tt=(int)(  k*(j-queue[i].getX())+queue[i].getY()  );
				bb[tm].setX(j);
				bb[tm].setY( tt);				
			}
			//计算他们之间的梯度
			for(j=0;j<4;j++)
			{
				int tm1= bb[j].getX() * width * 3 + bb[j].getY() * 3;
				int tm2=bb[j+1].getX() * width * 3 + bb[j+1].getY() * 3;
				diff[j]= abs( *( m_pImageBuffer + tm1) - 
					*( m_pImageBuffer +  tm2 )	);
			}
			//查找最大的梯度值的位置
			float	tmp1;	//记录最大梯度
			pos=0;
			tmp1=diff[0];
			for(j=0;j<4;j++)
			{
				if(tmp1<diff[j])
				{
					pos=j;
					tmp1=diff[j];
				}
			}
			queue[i].setX(bb[pos].getX());
			queue[i].setY(bb[pos].getY());	
			//涂色
			int tm3=bb[pos].getX()*3*width+bb[pos].getY()*3;
			*( m_pImageBuffer + tm3 )=125; 
			*( m_pImageBuffer + tm3 + 1 )=255; 
			*( m_pImageBuffer + tm3 + 2 )=125; 
			
		}
		//处在位置(2)
		else
		{
			//得到他的斜率的倒数
			float k= (float)( queue[i].getX() - pupilCenter.getX() ) / (queue[i].getY()-pupilCenter.getY());
			//找出他旁边的五个点
			for(j=queue[i].getY()-2;j<=queue[i].getY()+2;j++)
			{
				int tm=j-queue[i].getY()+2;
				int tt=(int)(k * ( j - queue[i].getY() ) + queue[i].getX() );
				bb[tm].setX(  tt);
				bb[tm].setY( j );				
			}
			//计算他们之间的梯度
			for(j=0;j<4;j++)
			{
				int tm1=bb[j].getX() * width * 3 + bb[j].getY() * 3 ;
				int tm2=bb[j+1].getX() * width * 3 + bb[j+1].getY() * 3;
				
				diff[j]= abs( *( m_pImageBuffer + tm1 ) -  *( m_pImageBuffer +  tm2 )	);
			}
			//查找最大的梯度值的位置
			int	tmp1;	//记录最大梯度
			pos=0;
			tmp1=diff[0];
			for(j=0;j<4;j++)
			{
				if(tmp1<diff[j])
				{
					pos=j;
					tmp1=diff[j];
				}
			}
			queue[i].setX(bb[pos].getX());
			queue[i].setY(bb[pos].getY());		
			int tm3=bb[pos].getX()*3*width+bb[pos].getY()*3;
			*( m_pImageBuffer + tm3 )=125; 
			*( m_pImageBuffer + tm3 + 1 )=255; 
			*( m_pImageBuffer + tm3 + 2 )=125; 
		}
	}
}

/*************************************************************************
*
*	功能：寻找眼睛的瞳孔,要先设定阈值，设定搜索范围
*	条件：当首次寻找瞳孔时,transform为true，scope_heigth=300,scope_width=400	  
*		  当粗定位瞳孔时,transform为false，scope_height=17，scope_width=17
*	参数：*m_pImageBuffer	图像首地址
*		  x，y				分别是图像处理的左上角坐标
*		  transform			图像是否需要转成灰度图的标记
*	Author：韩锴 时间：2010/6/23	
*	版本：
*
**************************************************************************/

/******************************************************************************
 * 功能：以(x,y)为起点在预设区域内搜索符合瞳孔阈值的最大点片，也即搜索瞳孔区域
		 进行瞳孔粗定位，确定粗定位瞳孔中心pupilCenter
 * 参数：*m_pImageBuffer	图像首地址
 		  x，y				分别是图像处理的左上角坐标
		  transform			图像是否需要转成灰度图的标记
 * 条件：scope_height, scope_widtd
 ******************************************************************************/
void Preprocess::search(BYTE *m_pImageBuffer , int x,int y,bool transform)
{
	//数据结构初始化
	queueCount=0;
	head=0;
	tail=0;
	memset(backup,0,768*576*sizeof(bool));
	memset(queue,0,4000*sizeof(Point));
	memset(log,0,200*2*sizeof(long));
	max=0;
	now=0;
	width=768;

	int i,j;//临时变量

	//确保搜索是在图像上，对区域内的每个点进行广度搜索
	//获取最大点簇，max为点的个数，log[0][]存放x,y坐标
	for(i=x;i<x+scope_height;i++)//x表示height
	{
		for(j=y;j<y+scope_width;j++)//y表示width
		{
			if(backup[i][j] == false )
			{
				int index = i*width*3+j*3;
				long tmp=0;
				BYTE* p;
				p=m_pImageBuffer+index;
				int a[3];
				a[0]=*p;
				a[1]=*(p+1);
				a[2]=*(p+2);
				if(transform==true)
				{
					//将彩色图像转换成灰度图像
				
					tmp = (int)(a[0] * 0.3 + a[1] * 0.59 + a[2] * 0.11);
					*(p)=*(p+1)=*(p+2)=tmp;
				}
				else
				{
					//计算灰度图的灰度
					tmp=a[0];
				}
				
				//满足阈值对其进行广度搜索
				if(tmp < threshold)
				{					
					//判断用不用更改存储位置					
					//searchHelp(m_pImageBuffer ,scope_height, scope_width, i,j,transform);
					searchHelp(m_pImageBuffer,scope_height, scope_width, x,y,i,j,transform);
					if(now>max)		//now==广度搜索满足阈值的点的个数
					{
						max=now;
						log[0][0]=log[1][0];//log[0]存储着当前最大点簇的x坐标和 log[1]是searchHelp里面一次搜索的x坐标和结果
						log[0][1]=log[1][1];//log[0]存储着当前最大点簇的y坐标和 log[1]是searchHelp里面一次搜索的y坐标和结果
					}
				}			
				
				backup[i][j] = true;
				
			}			
		}
	}
	if(max>0)
	{
		
		//寻找大的点片
		pupilCenter.setX((float)(log[0][0]/max));
		pupilCenter.setY((float)(log[0][1]/max));
		
	}
}

/*************************************************************************
*
*	功能：在设定的范围内进行广度搜索，将灰度值小于阈值的保存到queue中
*	条件：当首次寻找瞳孔时,transform为true，scope_heigth=768,scope_width=576	  
*		  当粗定位瞳孔时,transform为false，scope_height=17，scope_width=17
*	参数：*m_pImageBuffer	图像首地址
		  x，y				分别是图像处理的左上角坐标
		  i，j				当前搜索点
*		  transform			图像是否需要转成灰度图的标记
*	Author：韩锴 时间：2010/6/23	
*	版本：
*
**************************************************************************/
void Preprocess::searchHelp(BYTE *m_pImageBuffer,int scope_heigth,int scope_width,int x ,int y , int i,int j,bool transform)
{
	// 对用的数据进行初始化
	head=0;
	tail=0;
	now=0;
	log[1][0]=0;
	log[1][1]=0;
	queueCount=0;
	//更改访问标识
	backup[i][j]=true;
	//数据入队列
	queueCount++;
	now++;
	queue[tail].setX((float)i);
	queue[tail].setY((float)j);
	tail=(tail++)%3900;
	 
	//当队列不空就进行下面的动作
	while(queueCount>0 && queueCount<=3900)
	{
		//出队列
		queueCount--;
		int xx=(int )queue[head].getX();
		int yy=(int )queue[head].getY();
		head=(head++)%3900;
		log[1][0]=  log[1][0] += xx  ;
		log[1][1]=  log[1][1] += yy  ;
		//看其周围有没有满足条件的进队列
		int tmpDirect;
		for(tmpDirect=0;tmpDirect<8;tmpDirect++)
		{
			int xi=xx+Direction[tmpDirect][0];
			int yi=yy+Direction[tmpDirect][1];
			//判定是否符在搜索的范围内
			if( xi >= x && xi < x+scope_heigth && yi >= y && yi < y+scope_width )
			{
				//看是否访问过
				if( backup[xi][yi] == false )
				{
					int tmp;
					int index = xi*width*3+yi*3;
					//根据条件判断需要不需要进行灰度转换
					if(transform)
					{
						tmp = (int) (*(m_pImageBuffer+index) * 0.3 + *(m_pImageBuffer+1+index) * 0.59 + *(m_pImageBuffer+2+index) * 0.11);
						*(m_pImageBuffer+index)=*(m_pImageBuffer+index+1)=*(m_pImageBuffer+index+2)=tmp;	
					}
					else
					{
						tmp = *(m_pImageBuffer+index);
					}
					//看是否满足阈值
					if(tmp < threshold)
					{
						now++;
						//入队
						queueCount++;
						queue[tail].setX((float)xi);
						queue[tail].setY((float)yi);
						tail=(tail++)%3900;	
			//			cvCircle(pImg,cvPoint(yi,xi),1,cvScalar(155,0,0),-1);
 //                     cvCircle(pImg,cvPoint(yi,xi),1,CV_RGB(0,0,255),1,8,3);//因为在search中x表示h,y表示w，所以这里cvPoint的x,y要交换位置
//						cvRectangle(cvPoint(xi,yi),cvPoint(xi+10,yi+10),cvScalar(0, 0, 255), 3, 4, 0 );

					}
					backup[xi][yi] =true;
				}
			}
		
		}//end for 循环
				
	}//end while循环	
}


/**************************************************************
*
*	功能：对图像做平滑处理
*	参数：data				图像缓冲区
*		  x,y				处理块的起点
*	方法：对(x,y)点的平滑处理即以(x,y)为中心的3*3区域内的
		  每个点赋予权重，加权平均
***************************************************************/
bool Preprocess::smooth(BYTE *data,int x,int y)
{
	int direction[9][2]={{-1,-1},{-1,0},{-1,1},
						{0,-1},{0,0},{0,1},
						{1,-1},{1,0},{1,1}};
	int weight[9]={1,2,1,2,4,2,1,2,1};
	int* tmp;
	tmp=(int*)malloc(width*height*sizeof(int));
	memset(tmp,0,width*height*sizeof(int));
	//保证不会越界
	if( x > 50  &&  x < 450  && y > 50 
		&& y < 550 && x + scope_height < 450
		&& y + scope_width < 550)
	{
		//获取空间
		width=768;
		//边缘不能进行滤波
		int i,j,k;
		int ii,jj;
		for(i=x+1;i<x+scope_height-1;i++)
		{
			for(j=y+1;j<y+scope_width-1;j++)
			{
				for(k=0;k<9;k++)
				{
					
					ii=i+direction[k][0];
					jj=j+direction[k][1];
					*(tmp+(i)*width+(j)) +=weight[k]*(   *(data+i*width*3+j*3)	);
				}
				//*(tmp+(i)*width+(j))=*(tmp+(i)*width+(j))/16;		师兄的
				*(tmp+(i)*width+(j))=*(tmp+(i)*width+(j))/9;
			}
		}
		//进行赋值
		for(i=x+1;i<x+scope_height-1;i++)
		{
			for(j=y+1;j<y+scope_width-1;j++)
			{
				*(data+i*width*3+j*3)=*(tmp+(i)*width+(j));
				*(data+i*width*3+j*3+1)=*(tmp+(i)*width+(j));
				*(data+i*width*3+j*3+2)=*(tmp+(i)*width+(j));
			}
		}
		//释放空间
		free(tmp);
		return true;
	}
	else
	{
		free(tmp);
		return false;
	}
}