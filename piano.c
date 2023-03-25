/*-----------------------------------------------
  名稱：音樂播放
  內容：
------------------------------------------------*/
#include<reg52.h>        //包含標頭檔，一般情況不需要改動?
                         //標頭檔包含特殊功能寄存器的定義

/*------------------------------------------------
                 硬體埠定義
------------------------------------------------*/
#define KeyPort  P1
#define Button  P2
sbit      SPK=P3^2;  //定義音樂輸出埠

void DelayUs2x(unsigned char t);//us級延時函式宣告 
void DelayMs(unsigned char t); //ms級延時
unsigned char KeyScan(void);//鍵盤掃描
unsigned char KeyPro(void);

unsigned char Timer0_H,Timer0_L,Time;
					
code unsigned char FREQH[]={
		0xF1,0xF2,0xF4,0xF4,0xF6,0xF7,0xF8,//C3~B3
		0xF8,0xF9,0xFA,0xFA,0xFB,0xFB,0xFC,//C4~B4
		0xFC,0xFC,0xFD,0xFD,0xFD,0xFD,0xFE,//C5~B5
                            } ;
                         // 音階頻率表 低八位元
code unsigned char FREQL[]={
		0x17,0xB7,0x2A,0xD7,0x09,0x1F,0x18,//C3~B3
		0x8C,0x5B,0x15,0x67,0x04,0x90,0x0C,//C4~B4
		0x44,0xAC,0x09,0x34,0x82,0xC8,0x06,//C5~B5
                                };
/*------------------------------------------------
 uS延時函數，含有輸入參數 unsigned char t，無返回值
 unsigned char 是定義無符號字元變數，其值的範圍是
 0~255 這裡使用晶振12M，精確延時請使用彙編,大致延時
 長度如下 T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS延時函數，含有輸入參數 unsigned char t，無返回值
 unsigned char 是定義無符號字元變數，其值的範圍是
 0~255 這裡使用晶振12M，精確延時請使用彙編
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //大致延時1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
/*------------------------------------------------
                節拍延時函數
 各調1/4節拍時間：
 調4/4  125ms
 調2/4  250ms
 調3/4  187ms
------------------------------------------------*/
void delay(unsigned char t)
{
    unsigned char i;
	for(i=0;i<t;i++)
	    DelayMs(250);
    TR0=0;
 }
/*------------------------------------------------
               計時器0中斷
------------------------------------------------*/
void TIM0_ISR() interrupt 1
{
 TR0=0;      
 SPK=!SPK;
 TH0=Timer0_H;
 TL0=Timer0_L;
 TR0=1;
 }
/*------------------------------------------------
                歌曲處理函數
------------------------------------------------*/
void Song()
{
 TH0=Timer0_H;//賦值計時器時間，決定頻率
 TL0=Timer0_L;
 TR0=1;       //打開計時器
 delay(Time); //延時所需要的節拍                      
 }
/*------------------------------------------------
                主函數
------------------------------------------------*/
 void main(void)
 {
 unsigned char k,i;
 TMOD|=0x01; //置計時器0工作方式1
 EA=1;       //打開全域中斷
 ET0=1;      //打開定時0中斷
 
 unsigned char num;
 unsigned char press;
 Time=2; 
 while(1)
 {
	 
		 if(Button == 0xfe)
			 press = 0;
		 else if(Button == 0xfd)
			 press = 1;
		 else if(Button == 0xfb)
			 press = 2;
		 else if(Button == 0xf7)
			 press = 3;
		 else if(Button == 0xef)
			 press = 4;
		 else if(Button == 0xdf)
			 press = 5;
		 else if(Button == 0xbf)
			 press = 6;
		 else
			 press = 7;
		 if(press != 7)
		 {
			Timer0_H=FREQH[press];
			Timer0_L=FREQL[press];
			Song();
		 }
		
		num=KeyPro();
		if(num!=0xff)
		{
			if(num >= 0 && num <= 7)
			{
				Timer0_H=FREQH[num+7];
				Timer0_L=FREQL[num+7];
			}
			else if(num == 15);
			else
			{
				Timer0_H=FREQH[num+6];
				Timer0_L=FREQL[num+6];
			}
			Song();
		}
       
        
 }

/*------------------------------------------------
        按鍵掃描函數，返回掃描鍵值
------------------------------------------------*/
unsigned char KeyScan(void)  //鍵盤掃描函數，使用行列逐級掃描法
{
 unsigned char Val;
 KeyPort=0xf0;//高四位置高，低四位拉低
 if(KeyPort!=0xf0)//表示有按鍵按下
   {
    DelayMs(10);  //去抖
	if(KeyPort!=0xf0)
	  {           //表示有按鍵按下
    		KeyPort=0xfe; //檢測第一行
		if(KeyPort!=0xfe)
	  	{
			  Val=KeyPort&0xf0;
	  	      	  Val+=0x0e;
	  		  while(KeyPort!=0xfe);
			  DelayMs(10); //去抖
			  while(KeyPort!=0xfe);
	     	  return Val;
	        }
        KeyPort=0xfd; //檢測第二行
		if(KeyPort!=0xfd)
	  		{
			  Val=KeyPort&0xf0;
	  	      Val+=0x0d;
	  		  while(KeyPort!=0xfd);
			  DelayMs(10); //去抖
			  while(KeyPort!=0xfd);
	     	  return Val;
	        }
    	KeyPort=0xfb; //檢測第三行
		if(KeyPort!=0xfb)
	  		{
			  Val=KeyPort&0xf0;
	  	      Val+=0x0b;
	  		  while(KeyPort!=0xfb);
			  DelayMs(10); //去抖
			  while(KeyPort!=0xfb);
	     	  return Val;
	        }
    	KeyPort=0xf7; //檢測第四行
		if(KeyPort!=0xf7)
	  		{
			  Val=KeyPort&0xf0;
	  	      Val+=0x07;
	  		  while(KeyPort!=0xf7);
			  DelayMs(10); //去抖
			  while(KeyPort!=0xf7);
	     	  return Val;
	        }
     }
   }
  return 0xff;
}
/*------------------------------------------------
         按鍵值處理函數，返回掃鍵值
------------------------------------------------*/
unsigned char KeyPro(void)
{
 switch(KeyScan())
 {
  case 0x7e:return 0;break;//0 按下相應的鍵顯示相對應的碼值
  case 0x7d:return 1;break;//1
  case 0x7b:return 2;break;//2
  case 0x77:return 3;break;//3
  case 0xbe:return 4;break;//4
  case 0xbd:return 5;break;//5
  case 0xbb:return 6;break;//6
  case 0xb7:return 7;break;//7
  case 0xde:return 8;break;//8
  case 0xdd:return 9;break;//9
  case 0xdb:return 10;break;//a
  case 0xd7:return 11;break;//b
  case 0xee:return 12;break;//c
  case 0xed:return 13;break;//d
  case 0xeb:return 14;break;//e
  case 0xe7:return 15;break;//f
  default:return 0xff;break;
 }
}