#include<reg52.h> //包含標頭檔，一般情況不需要改動，標頭檔包含特殊功能寄存器的定義


#define DataPort P0 //定義資料埠 程式中遇到DataPort 則用P0 替換
#define KeyPort  P1

sbit LATCH1=P2^2;//定義鎖存使能埠 段鎖存
sbit LATCH2=P2^3;//                 位鎖存

unsigned char code dofly_DuanMa[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
		                  	         0x77,0x7c,0x39,0x5e,0x79,0x71};// 顯示段碼值0~F
unsigned char code dofly_WeiMa[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//分別對應相應的數碼管點亮,即位碼
unsigned char TempData[10]; //存儲顯示值的全域變數

void DelayUs2x(unsigned char t);//us級延時函式宣告 
void DelayMs(unsigned char t); //ms級延時
void Display(unsigned char FirstBit,unsigned char Num);//數碼管顯示函數
unsigned char KeyScan(void);//鍵盤掃描
unsigned char KeyPro(void);
void Init_Timer0(void);//計時器初始化
/*------------------------------------------------
                    主函數
------------------------------------------------*/
void main (void)
{
unsigned char num,i,j;                  
unsigned char temp[8];
Init_Timer0();

while (1)         //主迴圈
  {


 num=KeyPro();
 if(num!=0xff)
   {
    if(i<8)
      {
       temp[i]=dofly_DuanMa[num];
	   for(j=0;j<=i;j++)
          TempData[7-i+j]=temp[j];
       }
	i++;
	if(i==9)//多出一個按鍵輸入為了清屏 原本應該為8
      {
	  i=0;
	  	 for(j=0;j<8;j++)//清屏
         TempData[j]=0;
       }
   }
  //Display(0,8); //顯示全部8位元
     //主迴圈中添加其他需要一直工作的程式
	
  }
}
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
 顯示函數，用於動態掃描數碼管
 輸入參數 FirstBit 表示需要顯示的第一位，如賦值2表示從第三個數碼管開始顯示
 如輸入0表示從第一個顯示。
 Num表示需要顯示的位元數，如需要顯示99兩位元數值則該值輸入2
------------------------------------------------*/
void Display(unsigned char FirstBit,unsigned char Num)
{
      static unsigned char i=0;
	  

	   DataPort=0;   //清空資料，防止有交替重影
       LATCH1=1;     //段鎖存
       LATCH1=0;

       DataPort=dofly_WeiMa[i+FirstBit]; //取位碼 
       LATCH2=1;     //位鎖存
       LATCH2=0;

       DataPort=TempData[i]; //取顯示資料，段碼
       LATCH1=1;     //段鎖存
       LATCH1=0;
       
	   i++;
       if(i==Num)
	      i=0;


}
/*------------------------------------------------
                    計時器初始化副程式
------------------------------------------------*/
void Init_Timer0(void)
{
 TMOD |= 0x01;	  //使用模式1，16位元計時器，使用"|"符號可以在使用多個計時器時不受影響		     
 //TH0=0x00;	      //給定初值
 //TL0=0x00;
 EA=1;            //總中斷打開
 ET0=1;           //計時器中斷打開
 TR0=1;           //計時器開關打開
}
/*------------------------------------------------
                 計時器中斷副程式
------------------------------------------------*/
void Timer0_isr(void) interrupt 1 
{
 TH0=(65536-2000)/256;		  //重新賦值 2ms
 TL0=(65536-2000)%256;
 
 Display(0,8);       // 調用數碼管掃描

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