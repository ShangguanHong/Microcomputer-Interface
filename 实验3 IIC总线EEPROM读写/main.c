#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include "i2c.h"	
#include "stdio.h"

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

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
		unsigned char i, addr = 0x00, dat[] = {2, 1, 1, 2, 1, 1, 1, 0};
		for(i = 0; i < 8; i ++) {
			At24c02Write(addr + i, dat[i]); // 写入数据
			delay(1000); // 延时
		}
		// printf("Write data successfully!\n");
		for(i = 0; i < 8; i ++) {			
			DisplayData[i] = smgduan[At24c02Read(addr + i)]; // 取出数据
		}
		while(1) {
			DigDisplay(); //数码管显示数据
		}
}