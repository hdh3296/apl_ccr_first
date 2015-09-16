

extern   unsigned char  LcdTimer;  


extern   void  Delay(unsigned char temp);
extern   void  LCD_Command(unsigned char cmd);
extern   void  LcdInit(void);
extern   void  LCD_Cursor(unsigned char x,unsigned char y);
extern   void  LCD_Char_Out(unsigned char Code);
extern   void  LCD_String_Out(unsigned char x,unsigned char y,unsigned char *str);
extern   void  LCD_Line_Clear(unsigned char y);



#define  DSP_CLR_HOME         0x01
#define  CURSOR_HOME          0x02
#define  CHAR_RIGHT_SHIFT     0x04
#define  CHAR_LEFT_SHIFT      0x06

#define  dOFF_cOFF_bOFF       0x08
#define  dOFF_cOFF_bON        0x09
#define  dOFF_cON_bOFF        0x0a
#define  dOFF_cON_bON         0x0b
#define  dON_cOFF_bOFF        0x0c
#define  dON_cOFF_bON         0x0d
#define  dON_cON_bOFF         0x0e
#define  dON_cON_bON          0x0f

#define  CURSOR_LEFT_SHIFT    0x10              
#define  CURSOR_RIGHT_SHIFT   0x14           

