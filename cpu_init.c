

#include    <pic18.h>
#include    "serial.h"
#include    "cpu_init.h"


void    Init_Comms(void)
{

	BAUDCON=0;
	SPBRG = DIVIDER;     	

	TXSTA = (SPEED | NINE_BITS | 0x20);

	RCSTA = (NINE_BITS | 0x90);


	IPEN=0;
	PEIE=1;

	TRISC6=OUTPUT;
	TRISC7=INPUT;

    RCIE=1;	    // USART RX interrupt enable
    TXIE=0;	    // USART TX interrupt enable

    RCIF=0;	    // USART RX interrupt enable
    TXIF=0;	    // USART TX interrupt enable
}




void  Timer0Init(void)
{
  TMR0IE=1;
  TMR0IF=0;

  TMR0ON=1;	    // TMR0 on/off
  T08BIT=0;	    // 8/16 bit select    ..(16bit)
  T0CS=0;	    // TMR0 Source Select ..(internal clock)
  T0SE=0;	    // TMR0 Source Edge Select
  PSA=0;	    // Prescaler Assignment ..(enable)

  T0PS2=0;	    // Prescaler..............(1:2)
  T0PS1=1;
  T0PS0=0;
 
  TMR0L=MSEC_L;
  TMR0H=MSEC_H;
} 



void  Initial(void)
{

///////////////////////////////////////////////
// INTCON Register
  GIE=0;        // global interrupt enable
//  GIEH=0;     // enable high priority interrupts
  PEIE=1;	    // peripheral interrupt enable
//  GIEL=0;	    // enable low priority peripheral interrupts
  TMR0IE=1;	    // TMR0 overflow interrupt enable
  INT0IE=0;	    // external interrupt 0 enable
  RBIE=0;	    // RB port change interrupt enable
  TMR0IF=0;	    // TMR0 overflow interrupt flag
  INT0IF=0;	    // external interrupt 0 flag
  RBIF=0;	    // RB port change interrupt flag

///////////////////////////////////////////////
// INTCON2 Register
  RBPU=1;	    // port B pull-up enable
  INTEDG0=0;	// external interrupt 0 edge select
  INTEDG1=0;	// external interrupt 1 edge select
  INTEDG2=0;	// external interrupt 2 edge select
  TMR0IP=1;	    // TMR0 overflow interrupt priority
  RBIP=0;	    // RB port change interrupt priority

///////////////////////////////////////////////
// INTCON3 Register
  INT2IP=0;	    // external interrupt 2 priority
  INT1IP=0;	    // external interrupt 1 priority
  INT2IE=0;	    // external interrupt 2 enable
  INT1IE=0;	    // external interrupt 1 enable
  INT2IF=0;	    // external interrupt 2 flag
  INT1IF=0;	    // external interrupt 1 flag

///////////////////////////////////////////////
// T0CON Register
  TMR0ON=1;	    // TMR0 on/off
  T08BIT=0;	    // 8/16 bit select    ..(16bit)
  T0CS=0;	    // TMR0 Source Select ..(internal clock)
  T0SE=0;	    // TMR0 Source Edge Select
  PSA=0;	    // Prescaler Assignment ..(enable)
  T0PS2=0;	    // Prescaler..............(1:2)
  T0PS1=0;
  T0PS0=1;

// OSCCON Register
  SCS0=0;	    // system clock switch bit

// LVDCON Register
  IRVST=0;	    // input reference voltage stable status..(read only)
  LVDEN=1;	    // low voltage detect enable..............(enable)
  LVDL3=1;	    // low voltage detection limits...........(4.16V - 4.5V)
  LVDL2=1;
  LVDL1=0;
  LVDL0=1;

// WDTCON Register
  SWDTEN=0;	    // software watchdog timer enable.......(disable)

// RCON Register
  IPEN=0;	    // interrupt priority enable............(disable)?????
  RI=0;	        // RESET instruction status
  TO=0;	        // watchdog timeout flag
  PD=0;	        // power-down detection
  POR=0;	    // power-on reset status
  BOR=0;	    // brown-our reset status

// T1CON Register
//  RD1=1;	// 16 Bit Read/Write Enable
  T1RD16=1;	// 16 Bit Read/Write Enable
  T1CKPS1=1;	// Prescaler ........(1/8)
  T1CKPS0=1;
  T1OSCEN=0;	// Oscillator Enable....(disable)
  T1SYNC=0;	    // Sync Selct
  TMR1CS=0;	    // TMR Clock Source Select..(internal clock)
  TMR1ON=1;	    // TMR on/off...............( tmr run)

// T2CON Register
  TOUTPS3=0;	// Postscale
  TOUTPS2=0;
  TOUTPS1=0;
  TOUTPS0=0;
  TMR2ON=0;	    // TMR2 On/Off............(off)
  T2CKPS1=0;	// Prescale
  T2CKPS0=0;

// SSPSTAT Register..........(not use)
  SMP=0;	    // Sample Bit
  CKE=0;	    // SPI Clk Edge Select
  DA=0;	        // Data/Address Bit
  STOP=0;	    // STOP Bit detected
  START=0;	    // START Bit detected
  RW=0;	        // Read/Write bit Information
  UA=0;	        // Update Adress
  BF=0;	        // Buffer Full Status bit

// SSPCON1 Register..........(not use)
  WCOL=0;	    // write collision detect
  SSPOV=0;	    // recieve overflow indicator
  SSPEN=0;	    // SSP enable
  CKP=0;	    // clock polarity select
  SSPM3=0;	    // SSP mode select 
  SSPM2=1;
  SSPM1=0;
  SSPM0=1;


// SSPCON2 Register.......(not use)
  GCEN=0;	    // general call enable
//  ACKSTA=0;	    // acknowledge status bit
  ACKDT=0;	    // acknowledge data bit
  ACKEN=0;	    // acknowledge sequence enable
  RCEN=0;	    // recieve enable bit
  PEN=0;	    // STOP condition enable
  RSEN=0;	    // repeated START enable
  SEN=0;	    // START condition enable


// ADCON0 Register...(not use)  
  ADCS1=0;	    // AD conv. clock select bits
  ADCS0=0;
  CHS2=0;	    // channel select
  CHS1=0;
  CHS0=0;
  GODONE=0;	    // AD conversion status
  ADON=0;	    // AD on status


// ADCON1 Register....(not use)
  ADFM=0;	    // AD result format
  ADCS2=0;	    // AD conv. clock select bits
  PCFG3=0;	    // AD port config bits....(all digital)
  PCFG2=1;
  PCFG1=1;
  PCFG0=0;


// CCP1CON Register......(not use)
  DC1B1=0;	    // Duty Cycle Bits 1 & 0
  DC1B0=0;
  CCP1M3=0;	    // Mode Select Bits...(can messag receive)
  CCP1M2=0;
  CCP1M1=1;
  CCP1M0=1;


/*
// ECCP1CON Register.......(not use)     
  EPWM1M1=0;	// PWM output config bits
  EPWM1M0=0;
  EDC1B1=0;	// PWM duty cycle LSBs
  EDC1B0=0;
  ECCP1M3=0;	// EEPC1 mode select bits
  ECCP1M2=0;
  ECCP1M1=0;
  ECCP1M0=1;
*/


/*
// ECCP1DEL Register.....(not use)
  PRSEN=0;	// PWM delay
  PDC6=0;
  PDC5=0;
  PDC4=0;
  PDC3=0;
  PDC2=0;
  PDC1=0;
  PDC0=0;

// ECCPAS Register.....(not use)
  ECCPASE=0;	// ECCP auto-shutdown event status
  ECCPAS2=0;	// EECP auto-shutdown bits
  ECCPAS1=0;
  ECCPAS0=0;
  PSSAC1=1;	    // pin A & C auto-shutdown control
  PSSAC0=0;
  PSSBD1=1;	    // pin B & D auto-shutdown control
  PSSBD0=0;
*/


// CVRCON Register...............(not use)
  CVREN=0;	    // comparator voltage reference enable
  CVROE=0;	    // comparator VREF output enable
  CVRR=0;	    // comparator VREF range select
  CVRSS=0;	    // comparator VREF source select
  CVR3=0;	    // comparator VREF value selection
  CVR2=0;
  CVR1=0;
  CVR0=0;


// CMCON Comparator module register.....(not use)
  C2OUT=0;	   // comparator 2 output
  C1OUT=0;	   // comparator 1 output
  C2INV=0;	   // select to invert comp2 output
  C1INV=0;	   // select to invert comp1 output
  CIS=0;	   // comp input switch bit
  CM2=1;	   // comp mode select bits
  CM1=1;
  CM0=1;


// T3CON Register.......(not use) 
  T3RD16=0;	    // 16-Bit Read/Write select
  T3CCP1=0;	// TMR3 & TMR1 CCPx Enable
  T3CKPS1=0;	// Prescaler
  T3CKPS0=0;
  T3CCP1=0;	    // TMR3 & TMR1 CCPx Enable
  T3SYNC=0;	    // Sync Select
  TMR3CS=0;	    // TMR3 source Select
  TMR3ON=0;	    // TMR3 on/off

// TXSTA Register
  CSRC=0;      // CLK source select
  TX9=0	;	   // 8/9 bit TX data select
  TXEN=1;	   // transmit enable bit
  SYNC=0;	   // USART mode select
  BRGH=1;	   // high baud rate select
  TRMT=1;	   // TX shift reg. status bit
  TX9D=1;	   // 9th Bit of TX data

// RCSTA Register  
  SPEN=0;	  // serial port enable...(disable)
  RX9=0;	  // 8/9 bit data reception
  SREN=0;	  // single recieve enable
  CREN=0;	  // continuous recieve enable
  ADEN=0;	  // address detect enable
  FERR=0;	  // framing error
  OERR=0;	  // overrun error
  RX9D=0;	  // 9th Bit of RX data



// EECON1 Register
  EEPGD=0;	  // FLASH/EEPROM select
  CFGS=0;	  // access config regs./access FLASH-EEPROM

// alternate definition
  CFGS=0; 	  //Config./Calibration Select
  FREE=0;	  // FLASH row erase enable
  WRERR=0;	  // write error flag
  WREN=0;	  // write enable
  WR=0;	      // write control
  RD=0;	      // read control


/*
// IPR3 Register
  IRXIP=0;	  // CAN invalid rec. message interrupt priority
  WAKIP=0;	  // CANbus activity wake-up interrupt priority
  ERRIP=0;	  // CANbus error interrupt priority
  TXB2IP=0;	  // CAN TX buffer 2 interrupt priority
  TXB1IP=0;	  // CAN TX buffer 1 interrupt priority
  TXB0IP=0;	  // CAN TX buffer 0 interrupt priority
  RXB1IP=0;	  // CAN RX buffer 1 interrupt priority
  RXB0IP=1;	  // CAN RX buffer 0 interrupt priority	     

// PIR3 Register
  IRXIF=0;	  // CAN invalid rec. message interrupt flag
  WAKIF=0;	  // CANbus activity wake-up interrupt flag
  ERRIF=0;	  // CANbus error interrupt flag
  TXB2IF=0;	  // CAN TX buffer 2 interrupt flag
  TXB1IF=0;	  // CAN TX buffer 1 interrupt flag
  TXB0IF=0;	  // CAN TX buffer 0 interrupt flag
  RXB1IF=0;	  // CAN RX buffer 1 interrupt flag
  RXB0IF=0;	  // CAN RX buffer 0 interrupt flag		

// PIE3 Register
  IRXIE=0;	  // CAN invalid rec. message interrupt enable
  WAKIE=0;	  // CANbus activity wake-up interrupt enable
  ERRIE=0;	  // CANbus error interrupt enable
  TXB2IE=0;	  // CAN TX buffer 2 interrupt enable
  TXB1IE=0;	  // CAN TX buffer 1 interrupt enable
  TXB0IE=0;	  // CAN TX buffer 0 interrupt enable
  RXB1IE=0;	  // CAN RX buffer 1 interrupt enable
  RXB0IE=0;	  // CAN RX buffer 0 interrupt enable	     
*/

// IPR2 Register
  CMIP=0;	     // comparator interrupt priority		
  EEIP=0;   	// EEPROM write interrupt priority
  BCLIP=0;   	// bus collision interrupt priority
  LVDIP=0;	    // low voltage detect interrupt priority
  TMR3IP=0;	    // TMR3 overflow interrupt priority
  CCP1IP=0;	// ECCP1 interrupt priority
  OSCFIP=0;	




// PIR2 Register
  CMIF=0;	   // comparator interrupt flag		
  EEIF=0;	   // EEPROM write interrupt flag
  BCLIF=0;	   // bus collision interrupt flag
  LVDIF=0;	   // low voltage detect interrupt flag
  TMR3IF=0;	   // TMR3 overflow interrupt flag
  CCP1IF=0;   // ECCP1 interrupt flag


// PIE2 Register
  CMIE=0;	  // comparator interrupt enable		
  EEIE=0;	  // EEPROM write interrupt enable
  BCLIE=0; 	  // bus collision interrupt enable
  LVDIE=0;	  // low voltage detect interrupt enable
  TMR3IE=0;	  // TMR3 overflow interrupt enable
  CCP1IE=0;  // ECCP1 interrupt enable


// IPR1 Register


  SPPIP=0;	  // para. slave port rd/wr interrupt priority
  ADIP=0;	  // AD conv. interrupt priority
  RCIP=0;	  // USART RX interrupt priority
  TXIP=0;	  // USART TX interrupt priority
  SSPIP=0;    // master SSP interrupt priority
  CCP1IP=0;	  // CCP1 interrupt priority
  TMR2IP=0;	  // TMR2 - PR2 match interrupt priority
  TMR1IP=0;	  // TMR1 overflow interrupt priority


// PIR1 Register
  SPPIF=0;	     // para. slave port rd/wr interrupt flag
  ADIF=0;	     // AD conv. interrupt flag
  RCIF=0;	     // USART RX interrupt flag
  TXIF=0;	     // USART TX interrupt flag
  SSPIF=0;	     // master SSP interrupt flag
  CCP1IF=0;	     // CCP1 interrupt flag
  TMR2IF=0;	     // TMR2 - PR2 match interrupt flag
  TMR1IF=0;	     // TMR1 overflow interrupt flag

// PIE1 Register
  SPPIE=0;	    // para. slave port rd/wr interrupt enable
  ADIE=0;	    // AD conv. interrupt enable
  RCIE=0;	    // USART RX interrupt enable
  TXIE=0;	    // USART TX interrupt enable
  SSPIE=0;	    // master SSP interrupt enable
  CCP1IE=0;	    // CCP1 interrupt enable
  TMR2IE=0;	    // TMR2 - PR2 match interrupt enable
  TMR1IE=0;	    // TMR1 overflow interrupt enable


// TRISE Register
/*
  IBF=0;   	    // input buffer full status
  OBF=0;	    // output buffer full status
  IBOV=0;	    // input buffer overflow
  PSPMODE=0;	// parallel slave port mode select
*/
/*
  TRISE2=1;	    // port E data direction...(output)
  TRISE1=1;
  TRISE0=1;
*/
/*
// TRISD Register
  TRISD7=1;	// port D data direction....(output)
  TRISD6=1;
  TRISD5=1;
  TRISD4=1;
  TRISD3=1;
  TRISD2=1;
  TRISD1=1;
  TRISD0=1;
*/

// TRISC Register
  TRISC7=INPUT;	// port C data direction
  TRISC6=OUTPUT;
  TRISC2=OUTPUT;
  TRISC1=OUTPUT;
  TRISC0=OUTPUT;


// TRISB Register
  TRISB7=OUTPUT;	// port B data direction
  TRISB6=OUTPUT;
  TRISB5=OUTPUT;
  TRISB4=OUTPUT;
  TRISB3=OUTPUT;   //can rx 
  TRISB2=OUTPUT;   //can tx
  TRISB1=OUTPUT;   //in
  TRISB0=OUTPUT;   //in


// TRISA Register
//  TRISA7=1;	// port A data direction
//  TRISA6=INPUT;
  TRISA5=INPUT;
  TRISA4=INPUT;
  TRISA3=INPUT;
  TRISA2=INPUT;
  TRISA1=INPUT;
  TRISA0=INPUT;



/*
// LATE Register
  LATE2=1;	// port E data latch
  LATE1=1;
  LATE0=1;

// LATD Register
  LATD7=1;	// port D data latch
  LATD6=1;
  LATD5=1;
  LATD4=1;
  LATD3=1;
  LATD2=1;
  LATD1=1;
  LATD0=1;
*/


// LATC Register
  LATC7=1;	// port C data latch
  LATC6=1;
//  LATC5=1;
//  LATC4=1;
//  LATC3=1;
  LATC2=1;
  LATC1=1;
  LATC0=1;

// LATB Register
  LATB7=1;	// port B data latch
  LATB6=1;
  LATB5=1;
  LATB4=1;
  LATB3=1;
  LATB2=1;
  LATB1=1;
  LATB0=1;

// LATA Register
//  LATA7=1;	// port A data latch
/*
  LATA6=1;
  LATA5=1;
  LATA4=1;
  LATA3=1;
  LATA2=1;
  LATA1=1;
  LATA0=1; 
*/

//PBADEN=0;
ADCON1=0x0f;


PIE1=0;   
PIE2=0;   
}




void  Initialx(void)
{

///////////////////////////////////////////////
// INTCON Register
/*
  GIE=0;        // global interrupt enable
  PEIE=1;	    // peripheral interrupt enable
  TMR0IE=1;	    // TMR0 overflow interrupt enable
  INT0IE=0;	    // external interrupt 0 enable
  RBIE=0;	    // RB port change interrupt enable
  TMR0IF=0;	    // TMR0 overflow interrupt flag
  INT0IF=0;	    // external interrupt 0 flag
  RBIF=0;	    // RB port change interrupt flag

///////////////////////////////////////////////
// INTCON2 Register
  RBPU=1;	    // port B pull-up enable
  INTEDG0=0;	// external interrupt 0 edge select
  INTEDG1=0;	// external interrupt 1 edge select
  INTEDG2=0;	// external interrupt 2 edge select
  TMR0IP=1;	    // TMR0 overflow interrupt priority
  RBIP=0;	    // RB port change interrupt priority

///////////////////////////////////////////////
// INTCON3 Register
  INT2IP=0;	    // external interrupt 2 priority
  INT1IP=0;	    // external interrupt 1 priority
  INT2IE=0;	    // external interrupt 2 enable
  INT1IE=0;	    // external interrupt 1 enable
  INT2IF=0;	    // external interrupt 2 flag
  INT1IF=0;	    // external interrupt 1 flag

///////////////////////////////////////////////
// T0CON Register
  TMR0ON=1;	    // TMR0 on/off
  T08BIT=0;	    // 8/16 bit select    ..(16bit)
  T0CS=0;	    // TMR0 Source Select ..(internal clock)
  T0SE=0;	    // TMR0 Source Edge Select
  PSA=0;	    // Prescaler Assignment ..(enable)
  T0PS2=0;	    // Prescaler..............(1:2)
  T0PS1=0;
  T0PS0=1;

// OSCCON Register
  SCS0=0;	    // system clock switch bit

// LVDCON Register
  IRVST=0;	    // input reference voltage stable status..(read only)
  LVDEN=1;	    // low voltage detect enable..............(enable)
  LVDL3=1;	    // low voltage detection limits...........(4.16V - 4.5V)
  LVDL2=1;
  LVDL1=0;
  LVDL0=1;

// WDTCON Register
  SWDTEN=0;	    // software watchdog timer enable.......(disable)


// RCON Register
  IPEN=0;	    // interrupt priority enable............(disable)?????
  RI=0;	        // RESET instruction status
  TO=0;	        // watchdog timeout flag
  PD=0;	        // power-down detection
  POR=0;	    // power-on reset status
  BOR=0;	    // brown-our reset status

// T1CON Register
//  RD1=1;	// 16 Bit Read/Write Enable
  T1RD16=1;	// 16 Bit Read/Write Enable
  T1CKPS1=1;	// Prescaler ........(1/8)
  T1CKPS0=1;
  T1OSCEN=0;	// Oscillator Enable....(disable)
  T1SYNC=0;	    // Sync Selct
  TMR1CS=0;	    // TMR Clock Source Select..(internal clock)
  TMR1ON=1;	    // TMR on/off...............( tmr run)


// T2CON Register
  TOUTPS3=0;	// Postscale
  TOUTPS2=0;
  TOUTPS1=0;
  TOUTPS0=0;
  TMR2ON=0;	    // TMR2 On/Off............(off)
  T2CKPS1=0;	// Prescale
  T2CKPS0=0;

// SSPSTAT Register..........(not use)
  SMP=0;	    // Sample Bit
  CKE=0;	    // SPI Clk Edge Select
  DA=0;	        // Data/Address Bit
  STOP=0;	    // STOP Bit detected
  START=0;	    // START Bit detected
  RW=0;	        // Read/Write bit Information
  UA=0;	        // Update Adress
  BF=0;	        // Buffer Full Status bit


// SSPCON1 Register..........(not use)
  WCOL=0;	    // write collision detect
  SSPOV=0;	    // recieve overflow indicator
  SSPEN=0;	    // SSP enable
  CKP=0;	    // clock polarity select
  SSPM3=0;	    // SSP mode select 
  SSPM2=1;
  SSPM1=0;
  SSPM0=1;


// SSPCON2 Register.......(not use)
  GCEN=0;	    // general call enable
//  ACKSTA=0;	    // acknowledge status bit
  ACKDT=0;	    // acknowledge data bit
  ACKEN=0;	    // acknowledge sequence enable
  RCEN=0;	    // recieve enable bit
  PEN=0;	    // STOP condition enable
  RSEN=0;	    // repeated START enable
  SEN=0;	    // START condition enable


// ADCON0 Register...(not use)  
  ADCS1=0;	    // AD conv. clock select bits
  ADCS0=0;
  CHS2=0;	    // channel select
  CHS1=0;
  CHS0=0;
  GODONE=0;	    // AD conversion status
  ADON=0;	    // AD on status


// ADCON1 Register....(not use)
  ADFM=0;	    // AD result format
  ADCS2=0;	    // AD conv. clock select bits
  PCFG3=0;	    // AD port config bits....(all digital)
  PCFG2=1;
  PCFG1=1;
  PCFG0=0;


// CCP1CON Register......(not use)
  DC1B1=0;	    // Duty Cycle Bits 1 & 0
  DC1B0=0;
  CCP1M3=0;	    // Mode Select Bits...(can messag receive)
  CCP1M2=0;
  CCP1M1=1;
  CCP1M0=1;




// CVRCON Register...............(not use)
  CVREN=0;	    // comparator voltage reference enable
  CVROE=0;	    // comparator VREF output enable
  CVRR=0;	    // comparator VREF range select
  CVRSS=0;	    // comparator VREF source select
  CVR3=0;	    // comparator VREF value selection
  CVR2=0;
  CVR1=0;
  CVR0=0;


// CMCON Comparator module register.....(not use)
  C2OUT=0;	   // comparator 2 output
  C1OUT=0;	   // comparator 1 output
  C2INV=0;	   // select to invert comp2 output
  C1INV=0;	   // select to invert comp1 output
  CIS=0;	   // comp input switch bit
  CM2=1;	   // comp mode select bits
  CM1=1;
  CM0=1;



// T3CON Register.......(not use) 
  T3RD16=0;	    // 16-Bit Read/Write select
  T3CCP1=0;	// TMR3 & TMR1 CCPx Enable
  T3CKPS1=0;	// Prescaler
  T3CKPS0=0;
  T3CCP1=0;	    // TMR3 & TMR1 CCPx Enable
  T3SYNC=0;	    // Sync Select
  TMR3CS=0;	    // TMR3 source Select
  TMR3ON=0;	    // TMR3 on/off

// TXSTA Register
  CSRC=0;      // CLK source select
  TX9=0	;	   // 8/9 bit TX data select
  TXEN=1;	   // transmit enable bit
  SYNC=0;	   // USART mode select
  BRGH=1;	   // high baud rate select
  TRMT=1;	   // TX shift reg. status bit
  TX9D=0;	   // 9th Bit of TX data
*/

// RCSTA Register  
  SPEN=0;	  // serial port enable...(disable)
  RX9=0;	  // 8/9 bit data reception
  SREN=0;	  // single recieve enable
  CREN=0;	  // continuous recieve enable
  ADEN=0;	  // address detect enable
  FERR=0;	  // framing error
  OERR=0;	  // overrun error
  RX9D=0;	  // 9th Bit of RX data


/*
// EECON1 Register
  EEPGD=0;	  // FLASH/EEPROM select
  CFGS=0;	  // access config regs./access FLASH-EEPROM

// alternate definition
  CFGS=0; 	  //Config./Calibration Select
  FREE=0;	  // FLASH row erase enable
  WRERR=0;	  // write error flag
  WREN=0;	  // write enable
  WR=0;	      // write control
  RD=0;	      // read control



// IPR2 Register
  CMIP=0;	     // comparator interrupt priority		
  EEIP=0;   	// EEPROM write interrupt priority
  BCLIP=0;   	// bus collision interrupt priority
  LVDIP=0;	    // low voltage detect interrupt priority
  TMR3IP=0;	    // TMR3 overflow interrupt priority
  CCP1IP=0;	// ECCP1 interrupt priority
  OSCFIP=0;	




// PIR2 Register
  CMIF=0;	   // comparator interrupt flag		
  EEIF=0;	   // EEPROM write interrupt flag
  BCLIF=0;	   // bus collision interrupt flag
  LVDIF=0;	   // low voltage detect interrupt flag
  TMR3IF=0;	   // TMR3 overflow interrupt flag
  CCP1IF=0;   // ECCP1 interrupt flag


// PIE2 Register
  CMIE=0;	  // comparator interrupt enable		
  EEIE=0;	  // EEPROM write interrupt enable
  BCLIE=0; 	  // bus collision interrupt enable
  LVDIE=0;	  // low voltage detect interrupt enable
  TMR3IE=0;	  // TMR3 overflow interrupt enable
  CCP1IE=0;  // ECCP1 interrupt enable


// IPR1 Register


  SPPIP=0;	  // para. slave port rd/wr interrupt priority
  ADIP=0;	  // AD conv. interrupt priority
  RCIP=0;	  // USART RX interrupt priority
  TXIP=0;	  // USART TX interrupt priority
  SSPIP=0;    // master SSP interrupt priority
  CCP1IP=0;	  // CCP1 interrupt priority
  TMR2IP=0;	  // TMR2 - PR2 match interrupt priority
  TMR1IP=0;	  // TMR1 overflow interrupt priority


// PIR1 Register
  SPPIF=0;	     // para. slave port rd/wr interrupt flag
  ADIF=0;	     // AD conv. interrupt flag
  RCIF=0;	     // USART RX interrupt flag
  TXIF=0;	     // USART TX interrupt flag
  SSPIF=0;	     // master SSP interrupt flag
  CCP1IF=0;	     // CCP1 interrupt flag
  TMR2IF=0;	     // TMR2 - PR2 match interrupt flag
  TMR1IF=0;	     // TMR1 overflow interrupt flag

// PIE1 Register
  SPPIE=0;	    // para. slave port rd/wr interrupt enable
  ADIE=0;	    // AD conv. interrupt enable
  RCIE=0;	    // USART RX interrupt enable
  TXIE=0;	    // USART TX interrupt enable
  SSPIE=0;	    // master SSP interrupt enable
  CCP1IE=0;	    // CCP1 interrupt enable
  TMR2IE=0;	    // TMR2 - PR2 match interrupt enable
  TMR1IE=0;	    // TMR1 overflow interrupt enable



// TRISC Register
  TRISC7=INPUT;	// port C data direction
  TRISC6=OUTPUT;
  TRISC2=OUTPUT;
  TRISC1=OUTPUT;
  TRISC0=OUTPUT;


// TRISB Register
  TRISB7=OUTPUT;	// port B data direction
  TRISB6=OUTPUT;
  TRISB5=OUTPUT;
  TRISB4=OUTPUT;
  TRISB3=OUTPUT;   //can rx 
  TRISB2=OUTPUT;   //can tx
  TRISB1=OUTPUT;   //in
  TRISB0=OUTPUT;   //in


  TRISA5=INPUT;
  TRISA4=INPUT;
  TRISA3=INPUT;
  TRISA2=INPUT;
  TRISA1=INPUT;
  TRISA0=INPUT;





// LATC Register
  LATC7=1;	// port C data latch
  LATC6=1;
//  LATC5=1;
//  LATC4=1;
//  LATC3=1;
  LATC2=1;
  LATC1=1;
  LATC0=1;

// LATB Register
  LATB7=1;	// port B data latch
  LATB6=1;
  LATB5=1;
  LATB4=1;
  LATB3=1;
  LATB2=1;
  LATB1=1;
  LATB0=1;


//PBADEN=0;
ADCON1=0x0f;


PIE1=0;   
PIE2=0;
*/
   
}


