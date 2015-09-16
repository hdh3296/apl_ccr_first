

#define     LOCAL_NM        0
#define     HIB_HPI         0
#define     SUBDOOR_SEL     0
#define     OFFSET_FLR      0
#define     BAGGAGE         0

#define     SEARCH2         'J'
#define     SEARCH3         'S'
#define     SEARCH4         'Y'
#define     SEARCH5         'S'
#define     NC_END          'E'




//#define     TOGGLE_BUTTON_ON   



extern  void    TopResetting(void);
extern  void    SetupCheck(void);


extern  void    SetupMode(void);
extern  void    LoadSetupValue(void);
extern  void    CompanyWrite(unsigned char cmp);

                                    
extern  unsigned    char    SrcAddress;
extern  unsigned    char    LocalNumber;
extern  unsigned    char    Model;
extern  unsigned    char    SubDoor;
extern  unsigned    char    Offset_Flr;
extern  unsigned    char    Company;
extern  unsigned    char    ButtonType;

//extern  unsigned    char    TopFloor;
extern  unsigned    char    DspModel;
extern  unsigned    char    UpButtonTime;
extern  unsigned    char    DnButtonTime;
extern  unsigned    char    MainTimer;
extern  unsigned    char    shiftTime;


extern  bit   UpKeyBit;
extern  bit   DnKeyBit;
extern  bit   FDsp;
extern  bit   CmpSetBit;
extern  bit   MaskSetBit;



extern volatile const unsigned char Block[10][64];
extern unsigned char tmpram[64];


extern	void    BlockWrite(unsigned char blk); 
extern  void    BlockRead(unsigned char blk); 
