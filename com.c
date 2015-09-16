


/*
#include    <io51.h>
#include        "com.h"


void RxUartData(void);
void TxUartData(void);


#define UserDataType    unsigned char



#define     ASCTOHEX(x) ((x <= '9') ? (x - '0') : (x - '7')) 
#define     L_SHIFT(x)  (x << 4)



UserDataType    RxBuffer[MAX_RTX_BUF]={0,0};
UserDataType    RcvBuf[MAX_SAVE_BUF]={0};
UserDataType    RxStatus=0;
UserDataType    RxCurCnt=0;
UserDataType    SerialTime=0x0;
UserDataType    Chksum=0;




void    Chksum_Sum(void)
{
        UserDataType    i;
        UserDataType    temp;

        Chksum=0;
        Chksum=0;
        Chksum=0;
        for(i=0;RxBuffer[i];i++){
            Chksum=Chksum+RxBuffer[i];
        }
        temp=(Chksum & 0xf0) >> 4;
        if(temp < 0x0a) temp=temp+'0';
        else            temp=temp+'7';
        RxBuffer[i]=temp;

        temp=(Chksum & 0x0f);
        if(temp<0x0a)   temp=temp+'0';        
        else            temp=temp+'7';
        RxBuffer[i+1]=temp;
        RxBuffer[i+2]=0;
}



void    Serial(void)
{

      Chksum_Sum();
      
      RxCurCnt=0;
      RxStatus=TX_SET;  
      TXREG=RxBuffer[RxCurCnt];
      RxCurCnt=1;   
}





void TxUartData(void)
{
//    unsigned int  i;


//    TXIF=0;
    
    if(RxBuffer[RxCurCnt] == 0){
        TXREG=0;

//      i=0;
//      while(!TRMT && (i<2000)){
//        i++;
//      }  
      SerialTime=0;
      RxStatus = STX_CHK;
    }
    else{
      TXREG=RxBuffer[RxCurCnt];
      RxCurCnt++;
      SerialTime=0;
      RxStatus = TX_SET;
    
      if(RxCurCnt >= MAX_RTX_BUF){
        RxCurCnt=0;
        RxBuffer[RxCurCnt]=0;
      }
    }

}




void RxUartData(void)
{
      unsigned char   buf;
      unsigned char   temp;

    
    buf=RCREG;

    SerialTime=0;

    if(OERR){
        OERR=0;
    }

    if(FERR){
        FERR=0;
    }
   
    if(RxStatus != TX_SET){   
        SerialTime=0;
        if(RxCurCnt < (MAX_RTX_BUF-1)){
            RxCurCnt++;
        }
        else{
            RxCurCnt=0;
        }

        RxBuffer[RxCurCnt]=buf;

        switch(RxStatus){
            case    STX_CHK:
                if((buf==ACK) || (buf==ENQ)){
                    RxStatus=ETX_CHK;
                    RxBuffer[0]=buf;
                    RxCurCnt=0;
                    Chksum=buf;
                }
                break;
            case    ETX_CHK:
                Chksum=Chksum+buf;
                if((buf==ETX) || (buf == EOT)){
                    RxBuffer[RxCurCnt]=0x0;
                    RxStatus=BCC1_CHK;                  
                }
//                else if(buf < '0')   RxStatus=STX_CHK;
                break;
            case    BCC1_CHK:       
                buf=ASCTOHEX(buf);
                RxBuffer[RxCurCnt]=0x0;
                temp=(Chksum & 0xf0) >> 4; 
           
                if(temp==buf){                 
                    RxStatus=BCC2_CHK;                                                                    
                }
                else    RxStatus=STX_CHK;                  
                break;
            case    BCC2_CHK :
                buf=ASCTOHEX(buf);
                temp=(Chksum & 0x0f);
                RxBuffer[RxCurCnt]=0x0;
                RxBuffer[MAX_RTX_BUF-1]=0x0;
               
//                if((temp==buf) && (RxCurCnt <= (MAX_RTX_BUF-1))){
                if((temp==buf)){ // && (RxCurCnt <= (MAX_RTX_BUF-1))){
                    buf=0; 
                                                                            
                    for(temp=1;(RxBuffer[temp] >= '0');temp++){                   
                        RxBuffer[temp]=ASCTOHEX(RxBuffer[temp]);
                        RxBuffer[temp]=L_SHIFT(RxBuffer[temp]);
                        temp++;
                        RxBuffer[temp]=ASCTOHEX(RxBuffer[temp]);
                        RcvBuf[buf]=(RxBuffer[temp-1] | RxBuffer[temp]);
                        buf++;
                        if(buf > MAX_SAVE_BUF){
                            RxStatus=STX_CHK;
                            RxCurCnt=0;
                            break;
                        }                     
                    }

                    RxStatus=RX_GOOD;
                }
                else    RxStatus=STX_CHK;                  
                break;              
            case    RX_ERROR:
                RxStatus=STX_CHK;
                RxCurCnt=0;
                break;
            default:
                RxStatus=STX_CHK;
                RxCurCnt=0;
                break;
        }
    }    
}

*/






#include    <pic18.h>
#include	"com.h"



#define     ASCTOHEX(x) ((x <= '9') ? (x - '0') : (x - '7')) 
#define     L_SHIFT(x)  (x << 4)

//define COMPARE(x,y) ( ((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1) 



unsigned        char    RxBuffer[MAX_RTX_BUF];
unsigned        char    RxStatus=RX_GOOD;
unsigned        char    RxCurCnt=0;
unsigned        char    SerialTime=0x0;
unsigned        char    Chksum;



void    Chksum_Sum(void)
{
   register unsigned int    i;
   unsigned        char    temp;

   Chksum=0;
   for(i=0;RxBuffer[i];i++){
      Chksum=Chksum+RxBuffer[i];
   }
   temp=(Chksum & 0xf0) >> 4;
   if(temp < 0x0a) temp=temp+'0';
   else            temp=temp+'7';
   RxBuffer[i]=temp;

   temp=(Chksum & 0x0f);
   if(temp<0x0a)   temp=temp+'0';        
   else            temp=temp+'7';
   RxBuffer[i+1]=temp;
   RxBuffer[i+2]=0;
}



void    Serial(void)
{

        Chksum_Sum();

        RxCurCnt=0;
        RxStatus=TX_SET;
        
//        TI=0;
//        SBUF=RxBuffer[RxCurCnt];

		TXREG= RxBuffer[RxCurCnt];
        RxCurCnt=1;

		TXIF=0;
		TXIE=1;
}



void	USART0_RXC(void)
{
   unsigned char   buf;
   unsigned char   temp;

	buf=RCREG;

//      if((RxStatus == RX_GOOD))	LATB6= !LATB6;   

      if((RxStatus != TX_SET) && (RxStatus != RX_GOOD)){   
         SerialTime=0;
         if(RxCurCnt < (MAX_RTX_BUF-2)){
            RxCurCnt++;
         }
         RxBuffer[RxCurCnt]=buf;
         
         if((buf==ACK) || (buf==ENQ)){
           RxStatus=STX_CHK;                           
         }

         switch(RxStatus){
            case    STX_CHK:
               if((buf==ACK) || (buf==ENQ)){
                  RxStatus=ETX_CHK;
                  RxBuffer[0]=buf;
                  RxCurCnt=0;
                  Chksum=buf;
               }
               break;
            case    ETX_CHK:
               Chksum=Chksum+buf;
               if((buf==ETX) || (buf == EOT)){
                  RxBuffer[RxCurCnt]=0x0;
                  RxStatus=BCC1_CHK;                  
               }
               
               break;
            case    BCC1_CHK:               
               buf=ASCTOHEX(buf);
               RxBuffer[RxCurCnt]=0x0;
               temp=(Chksum & 0xf0) >> 4; 
               
                                
               if(temp==buf){                 
                  RxStatus=BCC2_CHK;                                                                    
               }
               else    RxStatus=STX_CHK;                  
               
               break;
            case    BCC2_CHK:
               buf=ASCTOHEX(buf);
               temp=(Chksum & 0x0f);
               
               RxBuffer[RxCurCnt]=0x0;               
                RxBuffer[MAX_RTX_BUF-1]=0x0;
               if(temp==buf){   // && (RxCurCnt <= (MAX_RTX_BUF-1))){
                  buf=0;
                  RxStatus=RX_GOOD;
               }
               else    RxStatus=STX_CHK;                  
               break;              
            case    RX_ERROR:
               RxStatus=STX_CHK;
               RxCurCnt=0;
               break;
            default:
               RxStatus=STX_CHK;
               RxCurCnt=0;
               break;
         }
      }

}




void	USART0_TXC(void)
{
   unsigned char   i;

      if(RxStatus == TX_SET){
         if(RxBuffer[RxCurCnt] == 0){
            for(i=0;i<20;i++);        
            RxStatus=STX_CHK;
            SerialTime=0;
			TXIE=0;
         }
         else{
//            SBUF = RxBuffer[RxCurCnt];
			TXREG= RxBuffer[RxCurCnt];
            RxCurCnt++;
            SerialTime=0; 
            RxStatus = TX_SET;  
         }
      }
	  else{
			TXIE=0;
			TXREG= 0x0;
	  }	
}



/*
interrupt [0x23] void SCON_int (void)
{
   
   unsigned char   buf;
   unsigned char   temp;
   unsigned char   i;
   
   if(TI){
      TI=0;
      if(RxStatus == TX_SET){
         if(RxBuffer[RxCurCnt] == 0){
            for(i=0;i<20;i++);        
            RxStatus=STX_CHK;
            SerialTime=0;
         }
         else{
            SBUF = RxBuffer[RxCurCnt];
            RxCurCnt++;
            SerialTime=0; 
            RxStatus = TX_SET;  
         }
      }
   }     
   else if(RI){
      RI=0;
      buf=SBUF;      
      if((RxStatus != TX_SET) && (RxStatus != RX_GOOD)){   
         SerialTime=0;
         if(RxCurCnt < (MAX_RTX_BUF-2)){
            RxCurCnt++;
         }
         RxBuffer[RxCurCnt]=buf;
         
         if((buf==ACK) || (buf==ENQ)){
           RxStatus=STX_CHK;                           
         }

         switch(RxStatus){
            case    STX_CHK:
               if((buf==ACK) || (buf==ENQ)){
                  RxStatus=ETX_CHK;
                  RxBuffer[0]=buf;
                  RxCurCnt=0;
                  Chksum=buf;
               }
               break;
            case    ETX_CHK:
               Chksum=Chksum+buf;
               if((buf==ETX) || (buf == EOT)){
                  RxBuffer[RxCurCnt]=0x0;
                  RxStatus=BCC1_CHK;                  
               }
//               else if(buf < '0')   RxStatus=STX_CHK;
               
               break;
            case    BCC1_CHK:               
               buf=ASCTOHEX(buf);
               RxBuffer[RxCurCnt]=0x0;
               temp=(Chksum & 0xf0) >> 4; 
               
                                
               if(temp==buf){                 
                  RxStatus=BCC2_CHK;                                                                    
               }
               else    RxStatus=STX_CHK;                  
               
               break;
            case    BCC2_CHK:
               buf=ASCTOHEX(buf);
               temp=(Chksum & 0x0f);
               
               RxBuffer[RxCurCnt]=0x0;               
                RxBuffer[MAX_RTX_BUF-1]=0x0;
//               if((temp==buf) && (RxCurCnt <= (MAX_RTX_BUF-1))){
               if(temp==buf){   // && (RxCurCnt <= (MAX_RTX_BUF-1))){
                  buf=0;
                  RxStatus=RX_GOOD;
               }
               else    RxStatus=STX_CHK;                  
               break;              
            case    RX_ERROR:
               RxStatus=STX_CHK;
               RxCurCnt=0;
               break;
            default:
               RxStatus=STX_CHK;
               RxCurCnt=0;
               break;
         }
      }
   }
}

*/


