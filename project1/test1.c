#include <AT89X51.H>
#include <stdio.h>
void main(void)
{
	SCON = 0x50; // 串口方式1,允许接受
	TMOD = 0x20; // 定时器1定时方式2
	TCON = 0x40; // 设定时器1开始计数
	TH1 = 0xE6; // 12MHz 1200波特率
	TL1 = 0xE6;
	TI = 1;
	TR1 = 1; // 启动定时器
	while(1)
	{
		printf ("Hello World!\n"); //显示 Hello World
	}
}