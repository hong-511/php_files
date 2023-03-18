#include <stdio.h>
#include <reg52.h>

#define BUS P0
#define N_us 10000

sbit font_ct1 = P2^0;
sbit scan_ct1 = P2^1;

code unsigned char font[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
code unsigned char scan[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};

unsigned char Oneunit = 0;
/*------------------------------------------------
                 計時器中斷副程式
------------------------------------------------*/
void timer0_ISR(void) interrupt 1 using 1
{
	//N_us passed, so Oneunit++
	TH0 = (0xff - N_us)/256;
	TL0 = (0xff - N_us)%256;
	Oneunit = (Oneunit%10)+1;//1~10
}
/*----------------*/
void initial_timer0(void);
void delay(unsigned int i);
void put_font(unsigned char i);
void put_digital(unsigned char i);
void display(unsigned long temp);

/*----------------*/

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

void display(unsigned long temp)//display temp number
{
	unsigned int i = 0;
	for(i = 0; temp; i++)
	{
		put_font(temp % 10);
		put_digital(7 - i);
		delay(5);
		temp /= 10;
	}
}

void main()
{
	unsigned int oneOverFifty = 0;
	unsigned int oneOverTen = 0;
	unsigned long displayNumber = 0;
	Oneunit = 0;
	initial_timer0();
	while (1)
	{
		if((Oneunit/2) == 0)
			(oneOverFifty++)%10000;
		if(Oneunit == 10)
			(oneOverTen++)%10000;
		displayNumber = oneOverTen << 4;
		displayNumber |= oneOverFifty;
		display(displayNumber);
	}
 }

void initial_timer0(void)
{
	TMOD |= 0x01;	  //使用模式1，16位元計時器，使用"|"符號可以在使用多個計時器時不受影響		     
	TH0 = (0xff - N_us)/256;
	TL0 = (0xff - N_us)%256;
	EA = 1;            //總中斷打開
	ET0 = 1;           //計時器中斷打開
	TR0 = 1;           //計時器開關打開
}
