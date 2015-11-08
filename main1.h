
typedef	unsigned char	UCHAR;
typedef unsigned int	UINT;


#define TRIS_INPUT		1
#define TRIS_OUTPUT		0

#define _RUNLED		LATB4	// Run Led

#define _SET_A1		RA0	// 주간 셋팅 볼륨, AN0
#define _SET_A2		RA1	// 중간 셋팅 볼륨, AN1
#define _SET_A3		RA2	// 야간 셋팅 볼륨, AN2

#define _IN_DAY		RB0	// 주간, 60Hz: On / High: Off
#define _IN_NIGHT	RB1	// 야간
#define _IN_BLINK	RB2
#define _SAVE_SW	RB3	// 셋팅 Switch

#define _A_IN		RA3	// AN3
#define _V_IN		RA5	// AN4

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
#define _SAVE_SW_TRIS			TRISB3	// in

#define _A_IN_TRIS		TRISA3	// in
#define _V_IN_TRIS		TRISA5	// in

#define _LAMP_ON_TRIS	TRISC0	// out
#define	_PWM_TRIS		TRISC2	// out


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


volatile const unsigned char Block0[] =	{0};



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


const   unsigned  char    Blanck[20]	= {"                "};
const   unsigned  char    Wait[20]    	= {"..Wait.......(A)"};
const   unsigned  char    ReadBack[20]	= {"Wait.Read......."};
const   unsigned  char    WriteBack[20] = {"Wait.Write......"};
const   unsigned  char    Daesung[20]   = {"Welcome.(v02.0)."};



unsigned       char        Message1[17];
unsigned       char        Message2[17];


unsigned       int        Mes;


////////////////////////////////
unsigned int indayHighTimer = 0;
unsigned int AnalogValidTime = 0;
unsigned int StartTimer;

unsigned char InBlinkTimer = 0;
unsigned char InDayTimer = 0;
unsigned char InNightTimer = 0;


bit bInBlinkLED;

#define SETSW_PUSH		0 // 스위치 눌렀을 때가 0 값이다.
unsigned    char    SetSwCharterTimer = 0;
bit bSetSwPushOK;
bit bSetSw_UpEdge;

#define ON	1
#define	OFF	0

typedef enum{DAY = 0, EVENING = 1, NIGHT = 2, NONE = 100} tag_CurDay;
tag_CurDay	CurDayNight;


unsigned int BeginTimer = 0;



unsigned char     AdChSel;
unsigned long int SumAD = 0;


unsigned char 	PERIOD;
unsigned int 	DutyCycle = 0;
#define DUTI_MAX 0x3ff // 1023




#define	A_SET_V_MAX 5000 // mV
#define	A_SET_V_MIN 0
#define A_SET_A_MAX1 10000 // mA
#define A_SET_A_MIN1 0
#define SET_AMP_PER_VOLT1	((A_SET_A_MAX1 - A_SET_A_MIN1) / (A_SET_V_MAX - A_SET_V_MIN)) // 4
#define A_SET_A_MAX2 10000 // mA
#define A_SET_A_MIN2 0
#define SET_AMP_PER_VOLT2	((A_SET_A_MAX2 - A_SET_A_MIN2) / (A_SET_V_MAX - A_SET_V_MIN)) // 4
#define A_SET_A_MAX3 10000 // mA
#define A_SET_A_MIN3 0
#define SET_AMP_PER_VOLT3	((A_SET_A_MAX3 - A_SET_A_MIN3) / (A_SET_V_MAX - A_SET_V_MIN)) // 4

const long double Multip[] = {SET_AMP_PER_VOLT1, SET_AMP_PER_VOLT2, SET_AMP_PER_VOLT3}; 

#define ADIntFlag			ADIF

// 5000이면 5V이다.
#define ADCH_MAX	5
unsigned int arInPutAD[ADCH_MAX] = {0,}; // 각 채널에서 읽어드린 AD 값 
UCHAR arIs_AdUpd[5] = {0,};

#define WRSIZE	12
volatile const unsigned char  arSavedBuf[WRSIZE] = {0, };

typedef struct 
{
	unsigned int SetA;
}tag_Apl;
tag_Apl		stApl[3] = {
					{0,},	// Set0
					{0,},	// Set1
					{0,},	// Set2
			};

unsigned int CurA_IN;
unsigned int CurV_IN;

unsigned int	AdCurValue;
unsigned int	AdCnt;
unsigned int	tmpSetADCnt_1;
unsigned int	tmpSetADCnt_2;
unsigned int 	tmpSetADCnt[3] = {0,}; 


volatile struct TmpStatusBit
{
unsigned char bTimer0Int				: 1;
unsigned char bAdInterrupt				: 1;
unsigned char bAdSave					: 1;
unsigned char NCFlag					: 5;
};
volatile struct TmpStatusBit   TSB;


bit bCurA_IN_Upd;



extern bit IsUdtAd(UINT*, UCHAR*, UCHAR);
extern void SetAplLamp(tag_CurDay);
extern void OnOffAplLamp(tag_CurDay);
extern void GetMyAD(void);
extern void Set_AdCh(UCHAR);
extern UCHAR ChangeAdChSel(UCHAR, tag_CurDay);
extern void StartAplLamp(void);


