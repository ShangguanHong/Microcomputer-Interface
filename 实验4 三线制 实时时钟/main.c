#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
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
* 函 数 名      : delay
* 函数功能		   : 延时函数，i=1时，大约延时10us
*******************************************************************************/
void delay(int i)
{
	while(i--);	
}


/*******************************************************************************
* 函数名         :DigDisplay()
* 函数功能		   :数码管显示函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void DigDisplay()
{
	int i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
			case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位	
			case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位	
			case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位
		}
		P0=DisplayData[7-i];//发送数据
		delay(100); // 延时
		P0=0x00;//消隐
	}		
}

/*******************************************************************************
* 函 数 名       : main
* 函数功能		   : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
	int k = 0;
	Ds1302Init();//初始化时钟
	while(1) {
		Ds1302ReadTime();//读取时钟信息
		if(K1 == 0) { // 按键1按下
			k = 0;
		} else if(K2 == 0) { //按键2按下
			k = 1;
		}
		if(k == 0) { //如果按键1按下,则显示时分秒
			DisplayData[0] = smgduan[TIME[2] / 0X10];
			DisplayData[1] = smgduan[TIME[2] % 0X10];
			DisplayData[2] = 0x00;
			DisplayData[3] = smgduan[TIME[1] % 0X10];
			DisplayData[4] = smgduan[TIME[1] / 0X10];
			DisplayData[5] = 0x00;
			DisplayData[6] = smgduan[TIME[0] / 0X10];
			DisplayData[7] = smgduan[TIME[0] % 0X10];
		} else { // 如果是按键2按下,则显示年月日
			DisplayData[0] = smgduan[2];
			DisplayData[1] = smgduan[0];
			DisplayData[2] = smgduan[TIME[6] / 0X10];
			DisplayData[3] = smgduan[TIME[6] % 0X10];
			DisplayData[4] = smgduan[TIME[4] / 0X10];
			DisplayData[5] = smgduan[TIME[4] % 0X10];
			DisplayData[6] = smgduan[TIME[3] / 0X10];
			DisplayData[7] = smgduan[TIME[6] % 0X10];
		}
		DigDisplay(); // 数码管显示
	}
}