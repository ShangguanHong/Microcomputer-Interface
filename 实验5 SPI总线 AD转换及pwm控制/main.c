#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include "XPT2046.h"	

typedef unsigned int u16;
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit LED=P2^0;

u8 DisplayData[8];
u8 code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
u16 cnt, temp, step = 41, lightTime, counter;

/*******************************************************************************
* 函 数 名         : delay
* 函数功能		   : 延时函数，i=1时，大约延时10us
*******************************************************************************/
void delay(u16 i)
{
	while(i--);	
}

/*******************************************************************************
* 函数名         :readData()
* 函数功能		 :数据处理函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void readData()
{
	if(cnt == 25) 
	{
		cnt = 0;
		temp = Read_AD_Data(0x94);		// 电位器
		DisplayData[0]=smgduan[temp/1000];//千位
		DisplayData[1]=smgduan[temp%1000/100];//百位
		DisplayData[2]=smgduan[temp%1000%100/10];//十位
		DisplayData[3]=smgduan[temp%1000%100%10];//个位		
		lightTime = temp / step;	// 设置亮灯的时间
	}
	cnt ++;
}

/*******************************************************************************
* 函数名         :DigDisplay()
* 函数功能		 :数码管显示函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void DigDisplay()
{
	int i;
	for(i=0;i<4;i++)
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
		}
		P0=DisplayData[3-i];//发送数据
		delay(100); // 延时
		P0=0x00;//消隐
	}		
}

/*******************************************************************************
* 函 数 名       : timer
* 函数功能		   : 中断函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void timer() interrupt 1 {
	counter ++;         
	if(counter >= 100) {   //重置counter
		counter = 1;
	}
	if(counter <= lightTime) {	//在1~lightTime范围内让灯亮
		LED = 0;
	} else {	//否则灯灭
		LED = 1;
	}
}

/*******************************************************************************
* 函 数 名       : main
* 函数功能		   : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main() {
	TMOD = 0x02; // 开启中断方式2
	TH0 = 0xa0;	// 0.1us
	TL0 = 0xa0;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
	while(1) {
		readData();		// 数据处理
		DigDisplay(); 	//数码管显示
	}
}