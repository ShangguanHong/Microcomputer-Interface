#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include "ds1302.h"	
#include "stdio.h"

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit K1=P3^0;
sbit K2=P3^1;

unsigned char DisplayData[8];
unsigned char code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

/*******************************************************************************
* �� �� ��      : delay
* ��������		   : ��ʱ������i=1ʱ����Լ��ʱ10us
*******************************************************************************/
void delay(int i)
{
	while(i--);	
}


/*******************************************************************************
* ������         :DigDisplay()
* ��������		   :�������ʾ����
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void DigDisplay()
{
	int i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ	
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ	
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ
		}
		P0=DisplayData[7-i];//��������
		delay(100); // ��ʱ
		P0=0x00;//����
	}		
}

/*******************************************************************************
* �� �� ��       : main
* ��������		   : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void main()
{	
	int k = 0;
	Ds1302Init();//��ʼ��ʱ��
	while(1) {
		Ds1302ReadTime();//��ȡʱ����Ϣ
		if(K1 == 0) { // ����1����
			k = 0;
		} else if(K2 == 0) { //����2����
			k = 1;
		}
		if(k == 0) { //�������1����,����ʾʱ����
			DisplayData[0] = smgduan[TIME[2] / 0X10];
			DisplayData[1] = smgduan[TIME[2] % 0X10];
			DisplayData[2] = 0x00;
			DisplayData[3] = smgduan[TIME[1] % 0X10];
			DisplayData[4] = smgduan[TIME[1] / 0X10];
			DisplayData[5] = 0x00;
			DisplayData[6] = smgduan[TIME[0] / 0X10];
			DisplayData[7] = smgduan[TIME[0] % 0X10];
		} else { // ����ǰ���2����,����ʾ������
			DisplayData[0] = smgduan[2];
			DisplayData[1] = smgduan[0];
			DisplayData[2] = smgduan[TIME[6] / 0X10];
			DisplayData[3] = smgduan[TIME[6] % 0X10];
			DisplayData[4] = smgduan[TIME[4] / 0X10];
			DisplayData[5] = smgduan[TIME[4] % 0X10];
			DisplayData[6] = smgduan[TIME[3] / 0X10];
			DisplayData[7] = smgduan[TIME[6] % 0X10];
		}
		DigDisplay(); // �������ʾ
	}
}