

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






void main(void)
{
   	unsigned char  i;
	
	di();
	Initial();
	Init_Comms();
	Timer0Init();
    ei();

   	RxStatus=STX_CHK;


   	LcdInit();
   	LcdInit();

	CLRWDT();

    for(i=0;i<16;i++){
        Message1[i]=Blanck[i];  
    }
    Message1[16]=0x0;  
    LCD_String_Out(0,0,&Message1[0]);
    LCD_String_Out(0,1,&Message1[0]);

    for(i=0;i<16;i++){
        Message1[i]=Daesung[i];  
    }
    Message1[16]=0x0;  
	CLRWDT();
    LCD_String_Out(0,0,&Message1[0]);


    for(i=0;i<16;i++){
        Message1[i]=Wait[i];  
    }
    Message1[14]=MY_COMPANY;  
    Message1[16]=0x0;  
	CLRWDT();
	
    LCD_String_Out(0,1,&Message1[0]);     

   	LCD_Command(dON_cOFF_bOFF);

	
	for(i=0;i<5;i++){
	   	LcdTimer=0;
	   	while(LcdTimer<150) CLRWDT();
	}
   
   	LcdTimer=0;
   	RxStatus=STX_CHK;
   
   while(1){
		CLRWDT();

      if(RxStatus==RX_GOOD){
            RxStatus=STX_CHK;
            NewDisplayLadder();   
            
            if(bKeyValid){
               SlaveTx();            
               bKeyValid=0;
               main_timer=0;                  
            }      
      }
      KeyCheck();		
   }
}




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

	if((RCIE)&&(RCIF))										/*receive interrupt routine*/
	{
        RCIF=0;
        USART0_RXC();
	}	

	if((TXIE)&&(TXIF))										/*transmit interrupt routine*/
	{
        USART0_TXC();
        TXIF=0;
	}	


	if(FERR || OERR){
		RCREG=RCREG;
		FERR=0;
 		OERR=0;	

		RCSTA=0;	
		RCSTA = (NINE_BITS | 0x90);
	}
}




