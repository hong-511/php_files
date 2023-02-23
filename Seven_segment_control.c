#include <stdio.h>
#include <reg52.h>

#define BUS P0

sbit font_ct1 = P2^0;
sbit scan_ct1 = P2^1;

code unsigned char font[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
code unsigned char scan[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};

void delay(unsigned int i)
{
	unsigned int j, k;
	for(j = 0; j < i; j++)
		for (k = 0; k < 10; k++);
}

void put_font(unsigned char i)
{
	BUS = 0xff - font[i];
	font_ct1 = 1;
	font_ct1 = 0;
}

void put_digital(unsigned char i)
{
	BUS = scan[i];
	scan_ct1 = 1;
	scan_ct1 = 0;
}

void main()
{
	unsigned int i = 0;
	unsigned long temp = 0;
	while (1)
	{
		temp = 100957043;
		for(i = 0; i < 8; i++)
		{
			put_font(temp % 10);
			put_digital(7 - i);
			delay(5);
			temp /= 10;
		}
	}
 }