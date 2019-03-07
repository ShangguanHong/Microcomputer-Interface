#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include "temp.h"
#include "lcd.h"
#include "stdio.h"

typedef unsigned char u8;

u8 DisplayData[5], tempIsNegative;

/*******************************************************************************
* 函 数 名         : datapros()
* 函数功能		     : 温度读取处理转换函数
* 输    入         : temp
* 输    出         : 无
*******************************************************************************/

void datapros(int temp) {
	float tp;
	if(temp < 0) {//当温度值为负数
		tempIsNegative = 1;
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;

	} else {
		tempIsNegative = 0;
		tp=temp;
		temp=tp*0.0625*100+0.5;
	}
	DisplayData[0] = temp / 10000;
	DisplayData[1] = temp % 10000 / 1000;
	DisplayData[2] = temp % 1000 / 100 ;
	DisplayData[3] = temp % 100 / 10;
	DisplayData[4] = temp % 10;
}

/*******************************************************************************
* 函 数 名       : main
* 函数功能		   : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main() {
	LcdInit();
	Ds18b20SetAlarm(30, 0);
	LcdWriteData('T');
	LcdWriteData('e');
	LcdWriteData('m');
	LcdWriteData('p');
	LcdWriteData(':');
	while(1) {
		LcdWriteCom(0x85);  //设置数据指针起点
		datapros(Ds18b20ReadTemp());
		if(tempIsNegative) {
			LcdWriteData('-');
		}
		LcdWriteData(DisplayData[0] + '0');
		LcdWriteData(DisplayData[1] + '0');
		LcdWriteData(DisplayData[2] + '0');
		LcdWriteData('.');
		LcdWriteData(DisplayData[3] + '0');
		LcdWriteData(DisplayData[4] + '0');
		LcdWriteData(0xDF);
		LcdWriteData('C');
		LcdWriteData(0x20);
	}
}
