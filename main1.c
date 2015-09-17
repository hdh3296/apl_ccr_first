

#include    <pic18.h>

//#include <io51.h>
#include "cpu_init.h"
#include "com.h"
#include "textlcd.h"
#include "serial.h"


    __CONFIG(1, 0x0e09);          
    __CONFIG(2, 0x1019);         
    __CONFIG(3, 0x8100);                         
    __CONFIG(4, 0x0081);    
    __CONFIG(5, 0xc00f);                                          
    __CONFIG(6, 0xe00f);                                              
    __CONFIG(7, 0x400f);                                              


#define	 MY_COMPANY		'A'

#define TRUE	1
#define FALSE   0
#define HIGH	1
#define LOW   	0



#define	 KeyPORT	PORTA
 
#define  EEP_SAVE_CMD    0x28
#define  EEP_READ_CMD    0x27


#define     MODEKEY        0x7f      
#define     ESCKEY         0xfd      
#define     UPKEY          0xef      
#define     DOWNKEY        0xdf
#define     ENTKEY         0xbf      

#define     READ_TIME      0
#define     WRITE_TIME     1

//#define     MSEC_L	100
//#define     MSEC_H	100    


//#define     TIME_READ_MODE      1
//#define     TIME_READ_MODE      1
//#define     TIME_EDIT_MODE      0


#define     VER_READ_MODE        0
#define     LOCK_READ_MODE       1
#define     SERVICE_READ_MODE    2
#define     PCBID_READ_MODE      3
#define     MENU_END             4


#define     LOCK_EDIT_MODE       10
#define     LOCK_WRITE_MODE      11
#define     SERVICE_EDIT_MODE    20
#define     SERVICE_WRITE_MODE   21
#define     PCBID_EDIT_MODE      30
#define     PCBID_WRITE_MODE     31




#define     BASE_RUN_TIME        100
#define     BASE_SET_TIME        102
#define     BOARD_ID             104


extern  void	Serial(void);
extern  void	USART0_RXC(void);
extern  void	USART0_TXC(void);

/*
extern  void    Initial();
extern  void    Init_Comms();
extern  void    Timer0Init();
*/


volatile const unsigned char Block0[]=	{  0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										   0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
										};

	
										
unsigned char tmpram[16];
far unsigned char * source_ptr = (far unsigned char *)tmpram;                    /*pointers to data*/
far unsigned char * dest_ptr;
unsigned char size = 16;						




unsigned char  src;
unsigned char  firstdata;
unsigned char  seconddata;
unsigned char  BefKey;     
unsigned char  CurKey;     
unsigned char  Charter;     
unsigned char  CurMode;     
unsigned char  EqualMode;
unsigned char  BaseAddress;
unsigned char  Data_Cnt;  
unsigned char  Value;  
unsigned char  pt;  

unsigned char  VerPt;  

unsigned int  main_timer;  


bit   bKeyValid;
bit   bKeyOn;



//const   unsigned  char    Daesung[20]	={"<Daesung I.D.S> "};


const   unsigned  char    Blanck[20]	={"                "};
const   unsigned  char    Wait[20]    	={"..Wait.......(A)"};
const   unsigned  char    ReadBack[20]	={"Wait.Read......."};
const   unsigned  char    WriteBack[20] ={"Wait.Write......"};
const   unsigned  char    Daesung[20]   ={"Welcome.(v02.0)."};



unsigned       char        Message1[17];
unsigned       char        Message2[17];


unsigned       int        Mes;


/*******************************************************
   manual play and record
*******************************************************/

void  LcdBuf1Clr(void)
{
/*
   unsigned char i;
   for(i=0;i<16;i++) LcdBuf1[i]=' ';            
   LcdBuf1[16]=0;            
*/   
}

void    HextoASCIIByte(void)
{
        unsigned char   i;

        i=(src & 0xf0) >> 4;
        if(i<0x0a)   i= i + '0';
        else         i= i + '7';
        firstdata=i;
        
        i=(src & 0x0f);
        if(i<0x0a)   i= i + '0';
        else         i= i + '7';
        seconddata=i;        
}



int    SlaveTx(void)
{
   RxBuffer[0]  = ACK;
   RxBuffer[1]  = MY_COMPANY;
   RxBuffer[2]  = CurKey;
   RxBuffer[3]  = ETX; 
   RxBuffer[4]  = 0; 

   Serial();
   
   return(1);
}



void  KeyCheck(void)
{
   unsigned char  tmpkey;

   
   tmpkey = (KeyPORT | 0xc0);

   if((BefKey == tmpkey) && (tmpkey < 0xff)){
      if(Charter>50){
			Charter=0;

         if(!bKeyOn){

            bKeyOn=1;
            bKeyValid=1;
            tmpkey=~tmpkey;

            switch(tmpkey){
               case  0x20:
                  CurKey='m';
                  break;   
               case  0x10:
                  CurKey='c';
                  break;         
               case  0x08:
                  CurKey='r';
                  break;                     

               case  0x04:
                  CurKey='u';
                  break;                  
               case  0x02:
                  CurKey='d';
                  break;                  
               case  0x01:
                  CurKey='e';
                  break;                                      
               default:
                  CurKey='n';
		            bKeyOn=0;
		            bKeyValid=0;
                  break;                                      
            }
         }            
      }   
   } 
   else{
      BefKey = tmpkey;
      Charter=0;            
      bKeyOn=0;
      CurKey='n';
   }     
}






unsigned int ImportData(void)
{
	unsigned char high,low,good;
	unsigned char i,j,k;

	unsigned int  blkpt;

	good=0;

	if(RxBuffer[3] >= 'A') 	j=(RxBuffer[3] - '7');
	else 					j=(RxBuffer[3] - '0');

	if(RxBuffer[4] >= 'A') 	k=(RxBuffer[4] - '7');
	else 					k=(RxBuffer[4] - '0');

	j=(j * 10)+ k;

	blkpt=(unsigned int)(j * 16);


	for(i=0;i<16;i++){
		k=(2*i);
		if(RxBuffer[5+k] >= 'A') 	high=(RxBuffer[5+k] - '7');
		else 						high=(RxBuffer[5+k] - '0');

		high=((high << 4) & 0xf0);
		if(RxBuffer[6+k] >= 'A') 	low =(RxBuffer[6+k] - '7');
		else 						low =(RxBuffer[6+k] - '0');

		if(Block0[blkpt+i] != (high | low) )	good=1;	

		tmpram[i] = (high | low);
	}

	if(good==1){
		dest_ptr =(far unsigned char *)(&Block0[blkpt]);
		flash_write(source_ptr,size,dest_ptr);
	}


	RxBuffer[0] = ACK;
	RxBuffer[1] = 'w';
	RxBuffer[2] = 'F';
	RxBuffer[37] = ETX;
	RxBuffer[38] = 0;

	Serial();


	for(i=0;i<16;i++){
		Message2[i]=ReadBack[i];
	}

	Message2[14]=RxBuffer[3];
	Message2[15]=RxBuffer[4];
	Message2[16]=0x0;
	LCD_String_Out(0,1,&Message2[0]);

	bKeyValid=0;
	main_timer=0;

	return(1);
}


unsigned int ExportData(void)
{
	unsigned char i,j,k,high,low,good;

	unsigned int  blkpt;

	good=1;

	if(RxBuffer[3] >= 'A') 	j=(RxBuffer[3] - '7');
	else 					j=(RxBuffer[3] - '0');

	if(RxBuffer[4] >= 'A') 	k=(RxBuffer[4] - '7');
	else 					k=(RxBuffer[4] - '0');

	j=(j * 10)+ k;


	blkpt=(unsigned int)(j * 16);


	for(i=0;i<16;i++){
		k=(2*i);
		if(RxBuffer[5+k] >= 'A') 	high=(RxBuffer[5+k] - '7');
		else 						high=(RxBuffer[5+k] - '0');

		high=((high << 4) & 0xf0);
		if(RxBuffer[6+k] >= 'A') 	low =(RxBuffer[6+k] - '7');
		else 						low =(RxBuffer[6+k] - '0');

		if(Block0[blkpt + i] != (high | low)) good=0;
	}


	if(good) j++;

	RxBuffer[0] = ACK;
	RxBuffer[1] = 'r';
	RxBuffer[2] = 'F';

	j=(j%100);
	RxBuffer[3] = (j/10) + '0';
	RxBuffer[4] = (j%10) + '0';

	blkpt=(unsigned int)(j * 16);


	for(i=0;i<16;i++){
		k=(i*2);
		src=Block0[blkpt+i];
		HextoASCIIByte();
		RxBuffer[5+k] = firstdata;
		RxBuffer[6+k] = seconddata;
	}

	k=(i*2);
	RxBuffer[5+k] = ETX;
	RxBuffer[6+k] = 0;


	Serial();

	for(i=0;i<16;i++){
		Message2[i]=WriteBack[i];
	}

	Message2[14]=RxBuffer[3];
	Message2[15]=RxBuffer[4];
	Message2[16]=0x0;
	LCD_String_Out(0,1,&Message2[0]);


	bKeyValid=0;
	main_timer=0;
	return(1);
}


unsigned int NewLadderChk(void)
{
	if((RxBuffer[1] == 'W') && (RxBuffer[2] == 'F')){
		ImportData();
		return(1);
	}
	else if((RxBuffer[1] == 'R') && (RxBuffer[2] == 'F')){
		ExportData(); 
		return(1);   
	}
	
	return(0);
}




unsigned int  NewDisplayLadder(void)
{
    unsigned char i;

	if(NewLadderChk())	return(0);
    
    for(i=0;i<16;i++){
        Message1[i]=RxBuffer[4+i];  
    }
    Message1[16]=0x0;  


    for(i=0;i<16;i++){
        Message2[i]=RxBuffer[20+i];  
    }        
    Message2[16]=0x0;  

              
    LCD_String_Out(0,0,&Message1[0]);
    LCD_String_Out(0,1,&Message2[0]);   

    i=RxBuffer[3];
    if(     (i >= 'A') && (i <= 'F'))    i=i-'7';
    else if((i >= '0') && (i <= '9'))    i=i-'0';
    else                                 i=0xff;
    
    if((i <= 0x0f) && (RxBuffer[2] > 0)){
        LCD_Cursor(i,1);    
        LCD_Command(dON_cOFF_bON);
    }
    else{
        LCD_Command(dON_cOFF_bOFF);    
    }
    
	return(0);

}

#define TRIS_INPUT		1
#define TRIS_OUTPUT		0

#define _RUNLED		LATB4	// Run Led

#define _SET_A1		LATA0	// 주간 셋팅 볼륨, AN0
#define _SET_A2		LATA1	// 중간 셋팅 볼륨, AN1
#define _SET_A3		LATA2	// 야간 셋팅 볼륨, AN2

#define _IN_DAY		LATB0	// 주간, 60Hz: On / High: Off
#define _IN_NIGHT	LATB1	// 야간
#define _IN_BLINK	LATB2	
#define _SAVE		LATB3	// 셋팅 Switch

#define _A_IN		LATA3	// AN3
#define _V_IN		LATA5	// AN4

#define _LAMP_ON	LATC0	// 등 On, Off  
#define	_PWM		LATC2		

// TRIS
#define _RUNLED_TRIS		TRISB4 	// out

#define _SET_A1_TRIS		TRISA0	// in 
#define _SET_A2_TRIS		TRISA1	// in
#define _SET_A3_TRIS		TRISA2	// in

#define _IN_DAY_TRIS		TRISB0	// in
#define _IN_NIGHT_TRIS		TRISB1	// in
#define _IN_BLINK_TRIS		TRISB2	// in
#define _SAVE_TRIS			TRISB3	// in

#define _A_IN_TRIS		TRISA3	// in		
#define _V_IN_TRIS		TRISA5	// in

#define _LAMP_ON_TRIS	TRISC0	// out  
#define	_PWM_TRIS		TRISC2	// out


InitPort(void)
{
	_RUNLED = HIGH;
	_RUNLED_TRIS = TRIS_OUTPUT;
	
	_SET_A1 = HIGH;
	_SET_A1_TRIS = TRIS_INPUT;
}


unsigned int	AdAvrValue;
unsigned int	AdCurValue;
unsigned int	AdCnt;

volatile struct TmpStatusBit
{
  unsigned char bTimer0Int				:1;
  unsigned char bAdInterrupt			:1;
  unsigned char bAdSave					:1;
  unsigned char NCFlag					:5;
};
volatile struct TmpStatusBit   TSB;


void  InitAD(void)
{
	// ADCON2<2:0>: A/D Conversion Clock Select bits
	ADCS2=1;	// 111 = FRC (clock derived from A/D RC oscillator)		 
	ADCS1=1;		
	ADCS0=1;		
	// Analog Select bits : AN0~AN3 포트에 대하여 AD 또는 일반 포트로 설정할지 여부 설정
	PCFG3=1;	// 1010 = AN0~AN4 Ananlog 
	PCFG2=0;		
	PCFG1=1;		
	PCFG0=0;		 


	ADFM=1; // A/D Result Format Select bit, if ADFM=1 : ADRESH(MSB), ADRESL(LSB)
	VCFG1=0; // Voltage Reference bit
	VCFG0=0;

	// Analog Channel Select bits
	CHS3=0;
	CHS2=0;
	CHS1=0;
	CHS0=0;
	
	GODONE=0; 	// A/D Conversion Status bit
	ADON=1; 	// A/D On bit

	// When IPEN = 0:
	// PEIE=1 : Enables all unmasked peripheral interrupts
	IPEN=0;	// Interrupt Priority Enable bit
	PEIE=1; // Peripheral Interrupt Enable bit

	ADIE=1; // A/D Converter (ADC) Interrupt Enable bit / 1 = Enables the A/D interrupt
	ADIF=0; // A/D Converter Interrupt Flag bit / 0 = The A/D conversion is not complete

	AdCurValue=0;
	AdAvrValue=0;
	AdCnt=0;

	TSB.bAdInterrupt=0;
	TSB.bAdSave=0;
}

unsigned    char    AdSel;
unsigned long AdSumValue=0;
// 5000이면 5V이다.
unsigned int SetA1_Volt=0; // SER A1 Voltage, AN0
unsigned int InVoltage=0; // A_IN Voltage, AN3

void SaveADtoEachChannel(void)
{    
	switch(AdSel){
	case 0:
		//if(bSetSwPushOK){
			SetA1_Volt = AdAvrValue; //204->46,
		//}		
		CHS3=0;
		CHS2=0;
		CHS1=0;
		CHS0=0;
		AdSel=0;
		break;
	case 1:
		InVoltage = AdAvrValue; //204->46,
		CHS3=0;
		CHS2=0;
		CHS1=1;
		CHS0=0;
		AdSel=2;
		break;		
	default:
		CHS3=0;
		CHS2=0;
		CHS1=0;
		CHS0=0;
		AdSel=0;
		break;
	}
}


void	CalcuAd(void)
{
	unsigned long	tmpad;
	unsigned int 	itmpad;

	if(TSB.bAdInterrupt){		
		TSB.bAdInterrupt = FALSE;
		
		AdCurValue = (unsigned int)ADRESH;	
		AdCurValue = AdCurValue << 8;
		AdCurValue = (AdCurValue & 0xff00);
		itmpad = (unsigned int)ADRESL;
		itmpad = (itmpad & 0x00ff);	
		AdCurValue = (AdCurValue | itmpad);

		AdSumValue = AdSumValue + (unsigned long)AdCurValue;
		AdCnt++;

		if(AdCnt >= 50)
		{
			CLRWDT();
			
			tmpad = AdSumValue / AdCnt;
			tmpad = (tmpad * 1000) / 208; 	//204		
			AdAvrValue = (unsigned int)tmpad;
			SaveADtoEachChannel();

			AdSumValue = 0;			
			AdCnt = 0;
			AdAvrValue = 0;
			TSB.bAdSave = TRUE;
		}
		GODONE = TRUE;	//AD (Because.....Auto GODONE = 0)
	}
}





void main(void)
{	
	di();
	Initial();
	Timer0Init();
	InitPort();
	InitAD();
	ei();

	GODONE = TRUE;	// A/D Conversion Status bit
	TMR0IE = TRUE;
	SWDTEN = TRUE;  // Software Controlled Watchdog Timer Enable bit / 1 = Watchdog Timer is on

	AdSel=0;

	while(1){
		CLRWDT();

		CalcuAd(); // AD 값을 읽는다.

		if(TSB.bAdSave){
			TSB.bAdSave = FALSE;
			if(SetA1_Volt >= 2000)
				_RUNLED = LOW; // Off
			else
				_RUNLED = HIGH; // On
		}



	}
}



#define ADIntFlag			ADIF

void interrupt isr(void)
{
	if( TMR0IF ){
        TMR0IF = 0 ;
        TMR0L=MSEC_L;
        TMR0H=MSEC_H;    
		SerialTime++;
		LcdTimer++;           
		if(Charter<150)   Charter++;
			
		main_timer++;
	}

	if(ADIntFlag && ADIE){
		ADIntFlag = 0;
		TSB.bAdInterrupt = TRUE;	
	}
}




