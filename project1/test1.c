#include <AT89X51.H>
#include <stdio.h>
void main(void)
{
	SCON = 0x50; // ���ڷ�ʽ1,�������
	TMOD = 0x20; // ��ʱ��1��ʱ��ʽ2
	TCON = 0x40; // �趨ʱ��1��ʼ����
	TH1 = 0xE6; // 12MHz 1200������
	TL1 = 0xE6;
	TI = 1;
	TR1 = 1; // ������ʱ��
	while(1)
	{
		printf ("Hello World!\n"); //��ʾ Hello World
	}
}