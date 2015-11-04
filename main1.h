
bit	bAn0_Updated = 0;
bit	bAn1_Updated = 0;
bit	bAn2_Updated = 0;
bit	bAn3_Updated = 0;
bit	bAn4_Updated = 0;

unsigned    char    AdSel;
unsigned long int SumAD = 0;


extern void	CalcuAd(void);
extern void SetApaLamp(void);
extern void ApaLampOnOff(void);
extern void SaveADtoEachChannel_ifSetNone(void);
extern void SaveADtoEachChannel(void);
extern void SaveADtoEachChannel_ifSetDay(void);
extern void SaveADtoEachChannel_ifSetEvening(void);
extern void SaveADtoEachChannel_ifSetNight(void);


