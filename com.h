
extern void Serial(void);
extern void RxUartData(void);
extern void TxUartData(void);


#define         MAX_RTX_BUF     50
//#define         MAX_SAVE_BUF    30


#define         NAK             0x15
#define         EOT             0x04
#define         ETX             0x03
#define         ENQ             0x05
#define         ACK             0x06

#define         STX_CHK         0
#define         ETX_CHK         6
#define         RX_ERROR        7
#define         RX_GOOD         8
#define         TX_SET          9
#define         BCC1_CHK        13
#define         BCC2_CHK        14

#define         PLC_200SH       0x31
#define         PLC_200SL       0x46


extern  unsigned        char    RxBuffer[MAX_RTX_BUF];
//extern  unsigned        char    RcvBuf[MAX_SAVE_BUF];
extern  unsigned        char    RxStatus;
extern  unsigned        char    RxCurCnt;
extern  unsigned        char    SerialTime;
extern  unsigned        char    Chksum;
extern  unsigned        char    Pt;




