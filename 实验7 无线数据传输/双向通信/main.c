#include "reg52.h" //此文件中定义了单片机的一些特殊功能寄存器
#include "nrf24l01.h"
#include "lcd.h"
#include "XPT2046.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit beep = P1^5;
uchar DATA[5] = {0}, rx_buf[5] = {0};
u16 cnt = 0, temp = 0;

int readData()
{
	u16 t, change = 0;
	if(cnt == 25) 
	{
		cnt = 0;
		t = Read_AD_Data(0x94);		// 电位器
		if(t != temp) {
			change = 1;
			temp = t;
			DATA[0]= temp/1000;//千位
			DATA[1]= temp%1000/100;//百位
			DATA[2]= temp%1000%100/10;//十位
			DATA[3]= temp%1000%100%10;//个位	
		}	
	}
	cnt ++;
	return change;
}

uchar NRF24L01_Check(void)
{
	uchar bu[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uchar bu1[5];
	uchar i;   	 
	SPI_Write_Buf(WRITE_REG+TX_ADDR,bu,5);	  //写入5个字节的地址.	
	SPI_Read_Buf(TX_ADDR,bu1,5);              //读出写入的地址  	
	for(i=0;i<5;i++)if(bu1[i]!=0XA5)break;					   
	if(i!=5)return 1;                               //NRF24L01不在位	
	return 0;		                                //NRF24L01在位
}

/*******************************************************************************
* 函 数 名       : main
* 函数功能		   : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{
	LcdInit();
	NRF24L01_Config();
	
	while(NRF24L01_Check())					//检查不到24l01则报警 
	{
		beep=0;
		Delay1ms(20);
		beep=1;
		Delay1ms(20);
	}
	while (1)
	{
		RX_Mode();		
		if(NRF24L01_RxPacket(rx_buf)) {			
			LcdWriteCom(0x80);  //设置数据指针起点			
			LcdWriteData(rx_buf[0] % 10 + '0');
			LcdWriteData(rx_buf[1] % 10 + '0');
			LcdWriteData(rx_buf[2] % 10 + '0');
			LcdWriteData(rx_buf[3] % 10 + '0');
		}
		if(readData()) {
			TX_Mode();			
			NRF24L01_TxPacket(DATA);
		}
	}
}
