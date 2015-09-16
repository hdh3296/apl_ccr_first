/*================================*/
/*      2000, 08, 20              */
/*         Ver 0.1                */
/*================================*/

#include <pic18.h>
#include "textlcd.h"

/*
bit  LCD_RS       = P3.2;
bit  LCD_RW       = P3.3;
bit  LCD_E        = P3.4;
//#define  LCD_DIO        P2
*/

#define  LCD_DIO   	LATB

#define  LCD_RS    	LATC0
#define  LCD_RW     LATC1
#define  LCD_E		LATC2



unsigned char  LcdTimer;  


void  Delay(unsigned char temp)
{
     unsigned char d;
     for(d=0;d<temp;d++);
}


void  LCD_Command(unsigned char cmd)
{
   LCD_RS=0;   
   LCD_E=0;
   
   Delay(50);   
   
   LCD_DIO = cmd;
   LCD_DIO = cmd;

/*
   Latch_E=1;
   Latch_E=1;
   Latch_E=0;
   Latch_E=0;
*/
   LCD_E=1;
   Delay(50);   
   LCD_E=0;
}


void LCD_Char_Out(unsigned char Code)
{

   LCD_RS=1;  
   LCD_E=0;
   
   Delay(50);
       
   LCD_DIO = Code;
   LCD_DIO = Code;

/*   
   Latch_E=1;
   Latch_E=1;
   Latch_E=0;
   Latch_E=0;
*/

   LCD_E=1;
   
   Delay(50);
      
   LCD_E=0;   
   LCD_RS=0;   
}



void LCD_Cursor(unsigned char x,unsigned char y)
{
   unsigned char  position;
        
//   if(y>1)  y=1;
//   if(x>15) x=15;   
//   position=y? x + 0xc0 : x+0x80; 
   
   switch(y){
      case  0:
         position=x+0x80;
         break; 
      case  1:
         position=x+0xc0;
         break; 
      case  2:
         position=x+0x90;
         break; 
      case  3:
         position=x+0xd0;
         break; 
   }   

   LCD_Command(position);
}





void  LCD_String_Out(unsigned char x,unsigned char y,unsigned char *str)
{   
   LCD_Cursor(x,y);
   while(*str){
      LCD_Char_Out(*(str++));         
   }
}


/*
void  LCD_Line_Clear(unsigned char y)
{
   unsigned char i;
   
   LCD_Cursor(0,y);
   i=0;   
   while(i<16){
      LCD_Char_Out(' ');
      i++;         
   }
   LCD_Cursor(0,y);
}
*/


void LcdInit(void)
{
   LCD_RS=1;
   LCD_E =1;
   LCD_RW=1;

	Delay(50);


   LCD_E=0;
   LCD_E=0;
   LCD_E=0;
   
   LCD_RW=0;
   
   LcdTimer=0;
   while(LcdTimer<150) CLRWDT();

   LcdTimer=0;
   while(LcdTimer<150)	CLRWDT();;
   
   LCD_Command(0x38);
   LCD_Command(dON_cOFF_bOFF);
   LCD_Command(CHAR_LEFT_SHIFT);
   LCD_Command(CURSOR_HOME);
   LCD_Command(DSP_CLR_HOME);
   
   LCD_Cursor(0,0);   
}





