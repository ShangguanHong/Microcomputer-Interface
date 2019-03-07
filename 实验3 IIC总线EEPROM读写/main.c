#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include "i2c.h"	
#include "stdio.h"

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

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
		unsigned char i, addr = 0x00, dat[] = {2, 1, 1, 2, 1, 1, 1, 0};
		for(i = 0; i < 8; i ++) {
			At24c02Write(addr + i, dat[i]); // д������
			delay(1000); // ��ʱ
		}
		// printf("Write data successfully!\n");
		for(i = 0; i < 8; i ++) {			
			DisplayData[i] = smgduan[At24c02Read(addr + i)]; // ȡ������
		}
		while(1) {
			DigDisplay(); //�������ʾ����
		}
}