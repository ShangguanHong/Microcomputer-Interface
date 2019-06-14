#ifndef __TEMP_H_
#define __TEMP_H_

#include<reg52.h>
//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//--����ʹ�õ�IO��--//
sbit DSPORT=P3^7;
sbit BEEP=P1^5;

//--����ȫ�ֺ���--//
void Delay1ms(uint);
uchar Ds18b20Init();
void Ds18b20WriteByte(uchar com);
uchar Ds18b20ReadByte();
void Ds18b20ChangTemp();
void Ds18b20ReadTempCom();
int Ds18b20ReadTemp();
void Ds18b20SetAlarm(int , int);
int Ds18b20AlarmSearch();
void delay(int i);

#endif
