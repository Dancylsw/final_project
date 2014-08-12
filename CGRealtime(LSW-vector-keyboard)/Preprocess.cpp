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
	//��������ĳ�ʼ��
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
 *	�ڻ���ͼ��m_pImageBuffer�ϣ��Ե�(xi��yi)Ϊ��������max�����صľ��η�Χ��
 *	����ĻҶȴ�����ֵ����Ϳɫ(49,49,49)
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
*	���ܣ��������
*	������m_pImageBuffer		ͼ�񻺳���
*		  x,y					��������ʼ��ַ
*	������Ҫ���趨��ֵ��Ȼ���趨�����ķ�Χ
*	ԭ���ҵ����п��ܵĹ�ߵ�Ƭ��Ȼ���þ���ƥ��ķ�ʽѰ�Һ��ʵĹ�ߵ�
*	
*********************************************************************************************/
void Preprocess::calGlints(BYTE *m_pImageBuffer ,int x,int y)
{
	//��ʼ���õ�����������
	leave=0;
	memset(tag,false,5*sizeof(bool));
	secondS=false;
	weed=false;
	memset(point,0,5*sizeof(Point));
	pointNumber=0;
	while(threshold>65)//65
	{
		//��ʼ�����������ݽṹ
		queueCount=0;
		head=0;
		tail=0;
		memset(backup,0,768*576*sizeof(bool));
		memset(queue,0,4000*sizeof(Point));
		memset(log,0,200*2*sizeof(long));
		memset(pointCount,0,200*sizeof(int));
		nowCount=0;	

		int i,j;//��ʱ����

		//��ָ��������й������
		for(i=x;i<x+scope_height;i++)
		{
			for(j=y;j<y+scope_width;j++)
			{
				if(backup[i][j]==false)
				{
					backup[i][j]=true;
					int tmp=i*768*3+j*3;
					//������
				//	cout<<(int)*(m_pImageBuffer+tmp)<<" ";
					if(*(m_pImageBuffer+tmp) >= threshold)
					{
						nowCount++;
						if(nowCount>=9)//200   ����������������������ȫ���ҳ�����ѡ���������Ƭ������
						{
							return;
						}
						glintSearch(m_pImageBuffer,x,y,i,j); //��i��jΪ�����й���������������������ĵ���backupΪtrue��������Ч�������queue
					}										 //��������ֵΪnowCount�ĵ�Ƭ��x,y�ۼ�ֵ������log[][]��
				}			
			}
		}

		leave=nowCount;
		//�޳������������ĵ�,������ǵ�����,
		j=1;
		for(i=1;i<=nowCount&&i<9;i++)//i<200
		{
//			cout<<pointCount[i]<<" ";
			if(pointCount[i]>60)//��Ƭ�е�ĸ�������һ����Ŀ�򲻿�����	
			{				
				leave--;
			}
			else
			{	
				log[j][0]=log[i][0]/pointCount[i];		//log����֮ǰ���ۼ�ֵ������ĵ�����
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
		//ƥ�����µĵ㻹���״����������е���Ҫ��

		//�״����������е���Ҫ��
		if(secondS==false)
		{
			if(leave>=3)
			{
				//��ʼ���洢������ݽṹ�͵�ı��

				memset(point,0,5*sizeof(Point));	//��Ź������
				memset(tag,false,5*sizeof(bool));	
				weed=false;
				
				//�Ҿ����еĵ㸳��point[5]����
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
		//ƥ�����µĵ�
		else
		{
			for(i=0;i<5;i++)
			{
				if(tag[i]==false)
				{
					//ѭ��ƥ��
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
 * ���ܣ��µĹ�������㷨�����ݹ��������̬������ֵ���������ߵ�λ��
 * ������*m_pImageBuffer	ͼ�񻺳���
		 x,y				������ʼ��
 * ��������������Ĺ�����ĵ㱣�浽Point point[5]��
 ********************************************************************/
void Preprocess::calGlints2(BYTE *m_pImageBuffer ,int x,int y)
{
    leave=0;
	memset(tag,false,5*sizeof(bool));
	memset(point,0,5*sizeof(Point));

	int loopcount = 0;

	while(threshold>100 && loopcount < 20)//65
	{
		//��ʼ�����������ݽṹ
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

		int i,j;//��ʱ����

		//��ָ��������й������
		for(i=x;i<x+scope_height;i++)
		{
			for(j=y;j<y+scope_width;j++)
			{
				if(backup[i][j]==false)
				{
					backup[i][j]=true;
					int tmp=i*768*3+j*3;
					//������
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
		//�޳������������ĵ�,������ǵ�����,
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
					
					point[pointNumber].setX(log[tempCount][0]);		//����pointNumber����4ô��
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
		//ƥ�����µĵ㻹���״����������е���Ҫ��

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

			//����5����ߵ�˳��
            float leastLength = 65535;
			int leastIndex = 0;
			bool glintFlag[5] = {false,false,false,false,false};//�Ƿ����õ��λ��
			Point adjustedPoint[5];
			int j;

			//��1��(��)
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
				

			//��2��(��)
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

            //��3��(��)
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

			//��4��(��)
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
			
			//�������
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
*	���ܣ������ҵ���leave����ƬѰ�ҷ���������ߵ�(����û���������)
*	˵��������������мǵ�leave�ı仯����������ҵ��˼������õĵ�
*		  �ǵð��ҵ��ĵ�Ż�log[][];
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
		//�ҳ������������		
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

		//���䰴��X������
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
		
		//�����꽫��ͬ�ĵ㸳��point
		int memwho=0;
		
		//�����꽫��ͬ�ĵ㸳��point
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
		//�����ж�
		//��鷶Χ��1��
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
		//�ҵ��Ǹ�û�д���ĵ�
		for(i=0;i<5;i++)
		{
			if(fault[i]>=3)
			{
				//�޳�
				leave--;
				tag[i]=false;				
			}
			//��Ч��
			else
			{				
				tag[i]=true;	
			}
		}

		//Ԥ��û���ҵ��ĵ�
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
		//���䰴��X������
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
			//���䰴y������
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
		//ֱ�ӷ����ڷ���ʱ���ж�һ���д�ľ�ֹͣ
		//���䰴��X������
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
			//��ɫ
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
			//��ɫ
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
			//��ɫ
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
			//��ɫ
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
*	���ܣ���ͫ��ͼ����й��ȥ��������䴦��ͬʱ���¼���Բ�ĵ�����
*	������data				ͼ�񻺳���
*		  x,y				���������
*			r				ͫ�׵İ뾶
*	������Ԥ�����úù����ֵ
*	���أ�����һ���µ�Բ�ĵ�point
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
				//�������(newX,newY)ΪԲ��newRΪ�뾶��Բ��Χ��
				if((i-newX)*(i-newX)+(j-newY)*(j-newY)<=newR*newR)
				{	
					//�Ҷȴ�����ֵ�ĵ㼴Ϊ��ߵ㣬����ȥ�����
					if(*(data+i*width*3+j*3)>threshold)
					{
						*(data+i*width*3+j*3)=50;
						*(data+i*width*3+j*3+1)=50;		//����ߵ�ĻҶ�ֵͳһ����Ϊ50
						*(data+i*width*3+j*3+2)=50;
					}
					count++;
					xx+=i;		//xx,yy�ֱ𱣴�����(newX,newY)ΪԲ��newRΪ�뾶��Բ��Χ�ڵĵ��x��y�ۼ�ֵ
					yy+=j;
				}
			}
		}//end for ѭ��
		oldR=newR;
		newR=sqrt((float)count/3.1415926);
		newX=xx/count;
		newY=yy/count;			//ͳ����ɺ����¸�ֵԲ���Լ��뾶
	}
	point.setX(newX);
	point.setY(newY);
//	fprintf(fpout,"%d\n",tmp);
	return point;				//����Բ��
}

/************************************************************************************
 * ���ܣ���(i,j)Ϊ�������(x,y)Ϊ��������768*576������Χ�ڽ��й�������������
 * ������*m_pImageBuffer	ͼ�񻺳���
		 x,y				����������ʼ��(768*576�����е�(0,0))
		 i,j				������ʼ��
 * ��������������ж��������ĵ����backup���ͬʱ��������ֵ�ĵ������queue
		 ͬʱpointCount[nowCount]�Ե�Ƭ���м�����log[nowCount][]�Ե�Ƭx��yֵ�ۼ�
 ************************************************************************************/
void Preprocess::glintSearch(BYTE *m_pImageBuffer ,int x,int y,int i,int j)
{
	queueCount=0;
	head=0;
	tail=0;
	width = 768;
	height = 576;
	//���ķ��ʱ�ʶ
	backup[i][j]=true;//������Ѿ����true��
	//���������
	queueCount++;
	queue[tail].setX(i);
	queue[tail].setY(j);
	tail=(tail++)%3900;
	pointCount[nowCount]++;
	
	//�����в��վͽ�������Ķ���
	while(queueCount>0&&queueCount<=3900)
	{	
		//������
		queueCount--;
		int xx=queue[head].getX();
		int yy=queue[head].getY();
		//������֮������ĻҶȱ�Ϊ65		��������
		
		
		head=((head+1)%3900);
		log[nowCount][0]=  log[nowCount][0] + xx  ;		//����Ƭ������log��
		log[nowCount][1]=  log[nowCount][1] + yy  ;
		int tmpDirect;
		for(tmpDirect=0;tmpDirect<8;tmpDirect++)
		{
			int xi=xx+Direction[tmpDirect][0];
			int yi=yy+Direction[tmpDirect][1];
			
			
			//�ж��Ƿ���������ķ�Χ��
         if( xi >= x && xi < x+scope_height && yi >= y && yi < y+scope_width && (x+scope_height)<height && (y+scope_width)<width)			
		 {
				//���Ƿ���ʹ�
				if( backup[xi][yi] == false )
				{
					backup[xi][yi] =true;
					int tmp=0;
					int index = xi*width*3+yi*3;		
					tmp = *(m_pImageBuffer+index);					
					//���Ƿ�������ֵ
					//	cout<<tmp<<" ";
					if(tmp >= threshold)
					{
						pointCount[nowCount]++;
						//���
						queueCount++;
						queue[tail].setX((float)xi);
						queue[tail].setY((float)yi);
						tail=(tail++)%3900;	
						//					cvCircle(pImg,cvPoint(yi,xi),1,cvScalar(0,0,255),-1);
					}					
				}
			}		
		}//end for ѭ��
		
	}//end whileѭ��	
}


/***************************************************************************************************************
 *	���ܣ�����(x,y)Ϊ���ĵ�60*60���������°벿�ֵĽ���ֱ��ͼ����������ֱ��ͼ����ƽ�����������ͫ�׻Ҷ���ֵ
 *	������	*data		ͼ�񻺳���
			x,y			�������ĵ�
 *	����ֵ����������ͫ����ֵ
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

		int	swidth=60;//���ҵĿ�
		int sheight=60;//���ҵĸ�
		int i,j;
		//ͳ��ֱ��ͼ
		for(i=x-sheight/2;i<=x;i++)
		{
			for(j=y-swidth/2;j<y+swidth/2;j++)
			{
				int tmp=i*width*3+j*3;
				color[*(data+tmp)]++;			//ͳ�������ڸûҶ�ֵ�ĵ�ĸ���
			}
		}
		
		//��ʾԴֱ��ͼ
		for(i=0;i<255;i++)
		{
			if(color[i])						//color[i] == �Ҷ�ֵΪi�ĵ�ĸ���
			{
				int xx=(color[i])%100;			//ΪʲôҪ��100���ࣿ
				int zz;
				for(zz=452;zz<xx+452;zz++)		//��452~xx+452��ʾ��ĸ�������ͼ���ϻ���ֱ��ͼ
				{
					*(data+zz*width*3+(i)*3)=0;			
					*(data+zz*width*3+(i)*3+1)=125;
					*(data+zz*width*3+(i)*3+2)=90;
				}
			}
		}
		//��ʾԭ���ߺ��յ���
		int zz;
		for(zz=452;zz<552;zz++)		//i==0,����ԭ����
		{
			*(data+zz*width*3+0*3)=0;
			*(data+zz*width*3+0*3+1)=125;
			*(data+zz*width*3+0*3+2)=90;
		}
		for(zz=452;zz<552;zz++)		//i==255,�����յ���
		{
			*(data+zz*width*3+255*3)=0;
			*(data+zz*width*3+255*3+1)=125;
			*(data+zz*width*3+255*3+2)=90;
		}
		//��ʾ��ֵ
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+50*3)=0;			//��ֵ�͵���50��
			*(data+zz*width*3+50*3+1)=225;
			*(data+zz*width*3+50*3+2)=0;
		}
		//��ֱ��ͼ����ƽ������
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
		//��ʾƽ�����ֱ��ͼ
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
		//��ʾԭ���ߺ��յ���
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
		//��ʾ��ֵ
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+315*3)=0;
			*(data+zz*width*3+315*3+1)=255;
			*(data+zz*width*3+315*3+2)=0;
		}
		//Ѱ������Ҫ�Ĳ���  Ϊʲô�ǲ��ȶ����ǲ��壿		
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
		//��ʾ��ĵ���ֵ

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
 *	���ܣ�����(x,y)Ϊ���ĵ��60*60������ϰ벿�ֽ���ֱ��ͼ����������ֱ��ͼ����ƽ�����������ͫ�׻Ҷ���ֵ
 *	������	*data	ͼ�񻺳���
			x,y		�������ĵ�����
 *	����ֵ������ͫ����ֵ
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

		int	swidth=60;//���ҵĿ�
		int sheight=60;//���ҵĸ�
		int i,j;
		//ͳ��ֱ��ͼ
		for(i=x;i<=x+sheight/2;i++)
		{
			for(j=y-swidth/2;j<y+swidth/2;j++)
			{
				int tmp=i*width*3+j*3;
				color[*(data+tmp)]++;
			}
		}		
		//��ʾԴֱ��ͼ
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
		//��ʾԭ���ߺ��յ���
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
		//��ʾ��ֵ
		for(zz=452;zz<552;zz++)
		{
			*(data+zz*width*3+560*3)=0;
			*(data+zz*width*3+560*3+1)=225;
			*(data+zz*width*3+560*3+2)=0;
		}
		//��ֱ��ͼ����ƽ������
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
		//��ʾƽ�����ֱ��ͼ
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
		//��ʾԭ���ߺ��յ���
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
		//��ʾ��ֵ
		for(zz=352;zz<452;zz++)
		{
			*(data+zz*width*3+560*3)=0;
			*(data+zz*width*3+560*3+1)=255;
			*(data+zz*width*3+560*3+2)=0;
		}
		//Ѱ������Ҫ�Ĳ���		
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
		//��ʾ��ĵ���ֵ

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
 *	���ܣ�����(x,y)Ϊ����scope_heigh*scope_width�������ֱ��ͼ����������ƽ��������ͫ�׻Ҷ���ֵ
 *	������	*data	ͼ�񻺳���
			x,y		�������
 *	����ֵ����ֵ
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
		//ͳ��ֱ��ͼ
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
		//��������ĻҶ�ֵ�Ƕ���
		total=total/(scope_width*scope_height);
		//fprintf(fpout,"%d\n",total);
		//��ʾԴֱ��ͼ
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
		//��ʾԭ���ߺ��յ���
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

		//��ֱ��ͼ����ƽ������
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
		//��ʾƽ�����ֱ��ͼ
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
		//��ʾԭ���ߺ��յ���
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
		
		//Ѱ������Ҫ�Ĳ���	
		bool can;		
		for (i=30 ;i<100;i++)
		{
			can=true;
			for (j=-5;j<=5;j++)
			{
				// ����
				if (color[i]>color[i+j])
				{
					can=false;
				}	
			}					
			if (can)
				break;
		}
		//��ʾ��ĵ���ֵ

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
*	���ܣ�Ѱ��ͫ�׵ı߽磬������Բ��ϣ�����ͫ�����ĵ�
*	������m_pImageBuffer		ͼ�񻺳���
*		  x��y					����������׵�ַ
*	����������֮ǰ���趨��ֵ��������Χ,���õ�������Χ��ʵ��Ҫ��6
*
*****************************************************************/
Point Preprocess::pupil(BYTE *m_pImageBuffer,int x,int y)
{
	PupilBFS(m_pImageBuffer,x,y);//ͫ�ױ�Ե���⣬��⵽�ı�Ե�㱣��������Point queue[]��
	int count= NumOfVertex ;	 //ͫ�ױ�Ե�����
	int i;
	int k;
	Point point;
	point.setX(x+40);//0
	point.setY(y+40);//0
	//����4��ٵ���޳�
	for(i=0;i<4;i++)
	{
		//��Բ��ϵ����ݽṹ
		CvPoint2D32f *PointArray2D32f;
		CvBox2D32f *box;
		PointArray2D32f = (CvPoint2D32f*)malloc(count*sizeof(CvPoint2D32f));
		box = (CvBox2D32f *)malloc(sizeof(CvBox2D32f));
		//������Բ���
		if(count>=6)
		{
			for (k=0;k<count;k++)
			{
				PointArray2D32f[k].x=(float)queue[k].getX();
				PointArray2D32f[k].y=(float)queue[k].getY();				
			}
			//��ϵ�ǰ����
			cvFitEllipse(PointArray2D32f,count,box);
		}
		//��������
		else
		{
			//�ͷ��ڴ�
			free(PointArray2D32f);
			free(box);
			break;
		}

		//�޳��ٵ�
		int j=0;
		for(k=0;k<count;k++)
		{
			//�õ���Բ������
			float x;
			float y;
			x=box->center.x;
			y=box->center.y;
			//�õ������еĵ�
			float x1=queue[k].getX();
			float y1=queue[k].getY();
			//�������㵽��Բ���ĵľ���
			float t1=sqrt( (x-x1)*(x-x1) + (y-y1)*(y-y1) );
			//��������ֵ
			float cs=(float)(x1-x)/t1;
			//���㷴���ҵ�ֵ
			float sit=acos(cs);
			//�������������
			if( (y1-y) < 0 )
			{
				sit=2*M_PI - sit;	
			}
			//����sit2��ֵ
			float sit2=sit - box->angle;
			//�ҵ���Բ�ĳ���
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
			//�Լٵ�����޳�
			if(abs(t1-t2)<0.8)
			{
				//����Ϳɫ
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
		//end�޳��ٵ�
		
		//���û������Ϳ��Դ�����
		if(i==3)
		{
			point.setX(box->center.x);
			point.setY(box->center.y);
		}
		//�ͷ��ڴ�
		free(PointArray2D32f);
		free(box);
	}

   
	return point;	
}

/*****************************************************************************
 *	���ܣ�ͫ�ױ�Ե����
 *	������	*m_pImageBuffer		ͼ�񻺳���
			xi,yi				��������ʼ��
 *	������ͫ�����ĵ�pupilCenter
 *	���������⵽��ͫ�ױ�Ե�㱣�浽����Point queue[]��
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
			//���Ƿ�������ֵ
			if ( *q <= threshold )
			{
				
				//����������ͫ�����ĵ��ϱ�
				if(i>pupilCenter.getX())
				{
					//����������ͫ�����ĵ����ϱ�
					if(j<pupilCenter.getY())
					{
						//���б�Ե��⣬��Ϊ��Ե�㣬�������ϻҶȴ�����ֵ��������С����ֵ(һά��Ե�������)
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
					//����������ͫ�����ĵ����ϱ�
					else if(j>pupilCenter.getY())
					{
						//���б�Ե���
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
					//��ͫ�����ĵ����Ϸ�
					else
					{
						//���б�Ե���
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
				//����������ͫ�����ĵ��·�
				else if(i<pupilCenter.getX())
				{
					//��ͫ�׵����·�
					if(j<pupilCenter.getY())
					{
						//���б�Ե���
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
					//��ͫ�׵����·�
					else if(j>pupilCenter.getY())
					{
						//���б�Ե���
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
					//��ͫ�׵����·�
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
				//��ͫ��������һ������
				else
				{
					//��ͫ�׵��ұ�
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
					//��ͫ�׵����
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
					//��һ�����û�п��Ǿ�����ͫ���Ǹ����������Ǹ���һ�����Ǳ�Ե��
				}
				
			}
		}
	}

}


/*********************************************************************
 *	���ܣ�
 *	������*m_pImageBuffer	ͼ�񻺳���
 *********************************************************************/
void Preprocess::refine(BYTE* m_pImageBuffer)
{
	int i,j;
	float diff[4];//��Ų�ֵ
	Point bb[5];//����ҵ��ĵ�
	int pos;//��¼�Ǹ��ݶ����ֵ��λ��
	int pos1;//��¼��������
	for(i=0;i<NumOfVertex;i++)
	{
		//���ж���������������
		//����λ��(1)
		if( abs( queue[i].getX()-pupilCenter.getX() ) >= abs( queue[i].getY()-pupilCenter.getY() ) )
		{
			//�õ�����б��
			float k= (float)(queue[i].getY()-pupilCenter.getY())/( queue[i].getX() - pupilCenter.getX() );
			//�ҳ����Աߵ������
			for(j=queue[i].getX()-2;j<=queue[i].getX()+2;j++)
			{
				int tm=j-queue[i].getX()+2;
				int tt=(int)(  k*(j-queue[i].getX())+queue[i].getY()  );
				bb[tm].setX(j);
				bb[tm].setY( tt);				
			}
			//��������֮����ݶ�
			for(j=0;j<4;j++)
			{
				int tm1= bb[j].getX() * width * 3 + bb[j].getY() * 3;
				int tm2=bb[j+1].getX() * width * 3 + bb[j+1].getY() * 3;
				diff[j]= abs( *( m_pImageBuffer + tm1) - 
					*( m_pImageBuffer +  tm2 )	);
			}
			//���������ݶ�ֵ��λ��
			float	tmp1;	//��¼����ݶ�
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
			//Ϳɫ
			int tm3=bb[pos].getX()*3*width+bb[pos].getY()*3;
			*( m_pImageBuffer + tm3 )=125; 
			*( m_pImageBuffer + tm3 + 1 )=255; 
			*( m_pImageBuffer + tm3 + 2 )=125; 
			
		}
		//����λ��(2)
		else
		{
			//�õ�����б�ʵĵ���
			float k= (float)( queue[i].getX() - pupilCenter.getX() ) / (queue[i].getY()-pupilCenter.getY());
			//�ҳ����Աߵ������
			for(j=queue[i].getY()-2;j<=queue[i].getY()+2;j++)
			{
				int tm=j-queue[i].getY()+2;
				int tt=(int)(k * ( j - queue[i].getY() ) + queue[i].getX() );
				bb[tm].setX(  tt);
				bb[tm].setY( j );				
			}
			//��������֮����ݶ�
			for(j=0;j<4;j++)
			{
				int tm1=bb[j].getX() * width * 3 + bb[j].getY() * 3 ;
				int tm2=bb[j+1].getX() * width * 3 + bb[j+1].getY() * 3;
				
				diff[j]= abs( *( m_pImageBuffer + tm1 ) -  *( m_pImageBuffer +  tm2 )	);
			}
			//���������ݶ�ֵ��λ��
			int	tmp1;	//��¼����ݶ�
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
*	���ܣ�Ѱ���۾���ͫ��,Ҫ���趨��ֵ���趨������Χ
*	���������״�Ѱ��ͫ��ʱ,transformΪtrue��scope_heigth=300,scope_width=400	  
*		  ���ֶ�λͫ��ʱ,transformΪfalse��scope_height=17��scope_width=17
*	������*m_pImageBuffer	ͼ���׵�ַ
*		  x��y				�ֱ���ͼ��������Ͻ�����
*		  transform			ͼ���Ƿ���Ҫת�ɻҶ�ͼ�ı��
*	Author������ ʱ�䣺2010/6/23	
*	�汾��
*
**************************************************************************/

/******************************************************************************
 * ���ܣ���(x,y)Ϊ�����Ԥ����������������ͫ����ֵ������Ƭ��Ҳ������ͫ������
		 ����ͫ�״ֶ�λ��ȷ���ֶ�λͫ������pupilCenter
 * ������*m_pImageBuffer	ͼ���׵�ַ
 		  x��y				�ֱ���ͼ��������Ͻ�����
		  transform			ͼ���Ƿ���Ҫת�ɻҶ�ͼ�ı��
 * ������scope_height, scope_widtd
 ******************************************************************************/
void Preprocess::search(BYTE *m_pImageBuffer , int x,int y,bool transform)
{
	//���ݽṹ��ʼ��
	queueCount=0;
	head=0;
	tail=0;
	memset(backup,0,768*576*sizeof(bool));
	memset(queue,0,4000*sizeof(Point));
	memset(log,0,200*2*sizeof(long));
	max=0;
	now=0;
	width=768;

	int i,j;//��ʱ����

	//ȷ����������ͼ���ϣ��������ڵ�ÿ������й������
	//��ȡ����أ�maxΪ��ĸ�����log[0][]���x,y����
	for(i=x;i<x+scope_height;i++)//x��ʾheight
	{
		for(j=y;j<y+scope_width;j++)//y��ʾwidth
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
					//����ɫͼ��ת���ɻҶ�ͼ��
				
					tmp = (int)(a[0] * 0.3 + a[1] * 0.59 + a[2] * 0.11);
					*(p)=*(p+1)=*(p+2)=tmp;
				}
				else
				{
					//����Ҷ�ͼ�ĻҶ�
					tmp=a[0];
				}
				
				//������ֵ������й������
				if(tmp < threshold)
				{					
					//�ж��ò��ø��Ĵ洢λ��					
					//searchHelp(m_pImageBuffer ,scope_height, scope_width, i,j,transform);
					searchHelp(m_pImageBuffer,scope_height, scope_width, x,y,i,j,transform);
					if(now>max)		//now==�������������ֵ�ĵ�ĸ���
					{
						max=now;
						log[0][0]=log[1][0];//log[0]�洢�ŵ�ǰ����ص�x����� log[1]��searchHelp����һ��������x����ͽ��
						log[0][1]=log[1][1];//log[0]�洢�ŵ�ǰ����ص�y����� log[1]��searchHelp����һ��������y����ͽ��
					}
				}			
				
				backup[i][j] = true;
				
			}			
		}
	}
	if(max>0)
	{
		
		//Ѱ�Ҵ�ĵ�Ƭ
		pupilCenter.setX((float)(log[0][0]/max));
		pupilCenter.setY((float)(log[0][1]/max));
		
	}
}

/*************************************************************************
*
*	���ܣ����趨�ķ�Χ�ڽ��й�����������Ҷ�ֵС����ֵ�ı��浽queue��
*	���������״�Ѱ��ͫ��ʱ,transformΪtrue��scope_heigth=768,scope_width=576	  
*		  ���ֶ�λͫ��ʱ,transformΪfalse��scope_height=17��scope_width=17
*	������*m_pImageBuffer	ͼ���׵�ַ
		  x��y				�ֱ���ͼ��������Ͻ�����
		  i��j				��ǰ������
*		  transform			ͼ���Ƿ���Ҫת�ɻҶ�ͼ�ı��
*	Author������ ʱ�䣺2010/6/23	
*	�汾��
*
**************************************************************************/
void Preprocess::searchHelp(BYTE *m_pImageBuffer,int scope_heigth,int scope_width,int x ,int y , int i,int j,bool transform)
{
	// ���õ����ݽ��г�ʼ��
	head=0;
	tail=0;
	now=0;
	log[1][0]=0;
	log[1][1]=0;
	queueCount=0;
	//���ķ��ʱ�ʶ
	backup[i][j]=true;
	//���������
	queueCount++;
	now++;
	queue[tail].setX((float)i);
	queue[tail].setY((float)j);
	tail=(tail++)%3900;
	 
	//�����в��վͽ�������Ķ���
	while(queueCount>0 && queueCount<=3900)
	{
		//������
		queueCount--;
		int xx=(int )queue[head].getX();
		int yy=(int )queue[head].getY();
		head=(head++)%3900;
		log[1][0]=  log[1][0] += xx  ;
		log[1][1]=  log[1][1] += yy  ;
		//������Χ��û�����������Ľ�����
		int tmpDirect;
		for(tmpDirect=0;tmpDirect<8;tmpDirect++)
		{
			int xi=xx+Direction[tmpDirect][0];
			int yi=yy+Direction[tmpDirect][1];
			//�ж��Ƿ���������ķ�Χ��
			if( xi >= x && xi < x+scope_heigth && yi >= y && yi < y+scope_width )
			{
				//���Ƿ���ʹ�
				if( backup[xi][yi] == false )
				{
					int tmp;
					int index = xi*width*3+yi*3;
					//���������ж���Ҫ����Ҫ���лҶ�ת��
					if(transform)
					{
						tmp = (int) (*(m_pImageBuffer+index) * 0.3 + *(m_pImageBuffer+1+index) * 0.59 + *(m_pImageBuffer+2+index) * 0.11);
						*(m_pImageBuffer+index)=*(m_pImageBuffer+index+1)=*(m_pImageBuffer+index+2)=tmp;	
					}
					else
					{
						tmp = *(m_pImageBuffer+index);
					}
					//���Ƿ�������ֵ
					if(tmp < threshold)
					{
						now++;
						//���
						queueCount++;
						queue[tail].setX((float)xi);
						queue[tail].setY((float)yi);
						tail=(tail++)%3900;	
			//			cvCircle(pImg,cvPoint(yi,xi),1,cvScalar(155,0,0),-1);
 //                     cvCircle(pImg,cvPoint(yi,xi),1,CV_RGB(0,0,255),1,8,3);//��Ϊ��search��x��ʾh,y��ʾw����������cvPoint��x,yҪ����λ��
//						cvRectangle(cvPoint(xi,yi),cvPoint(xi+10,yi+10),cvScalar(0, 0, 255), 3, 4, 0 );

					}
					backup[xi][yi] =true;
				}
			}
		
		}//end for ѭ��
				
	}//end whileѭ��	
}


/**************************************************************
*
*	���ܣ���ͼ����ƽ������
*	������data				ͼ�񻺳���
*		  x,y				���������
*	��������(x,y)���ƽ��������(x,y)Ϊ���ĵ�3*3�����ڵ�
		  ÿ���㸳��Ȩ�أ���Ȩƽ��
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
	//��֤����Խ��
	if( x > 50  &&  x < 450  && y > 50 
		&& y < 550 && x + scope_height < 450
		&& y + scope_width < 550)
	{
		//��ȡ�ռ�
		width=768;
		//��Ե���ܽ����˲�
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
				//*(tmp+(i)*width+(j))=*(tmp+(i)*width+(j))/16;		ʦ�ֵ�
				*(tmp+(i)*width+(j))=*(tmp+(i)*width+(j))/9;
			}
		}
		//���и�ֵ
		for(i=x+1;i<x+scope_height-1;i++)
		{
			for(j=y+1;j<y+scope_width-1;j++)
			{
				*(data+i*width*3+j*3)=*(tmp+(i)*width+(j));
				*(data+i*width*3+j*3+1)=*(tmp+(i)*width+(j));
				*(data+i*width*3+j*3+2)=*(tmp+(i)*width+(j));
			}
		}
		//�ͷſռ�
		free(tmp);
		return true;
	}
	else
	{
		free(tmp);
		return false;
	}
}