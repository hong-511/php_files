#include <stdio.h>
#include <reg52.h>
https://docs.google.com/presentation/d/1fgwxs5Yn5LeqnWZrwyqrnIdQtZReIFTVthRgy-yrbkM/edit?usp=sharing
#define LED7 P0
code unsigned char font[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void delay(unsigned int i)
{
	unsigned int j, k;
	for(j = 0; j < i; j++)
		for (k = 0; k < 100; k++);
}

void main()
{
	unsigned int i = 0;
	while(1)
	{
		LED7 = font[i++];
		delay(500); 
		if (i == 10)
			i = 0;
	}
 }
