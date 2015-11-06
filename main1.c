

#include    <pic18.h>

//#include <io51.h>
#include "cpu_init.h"
#include "com.h"
#include "textlcd.h"
#include "serial.h"
#include "main1.h"


__CONFIG(1, 0x0e09);
__CONFIG(2, 0x1019);
__CONFIG(3, 0x8100);
__CONFIG(4, 0x0081);
__CONFIG(5, 0xc00f);
__CONFIG(6, 0xe00f);
__CONFIG(7, 0x400f);



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

    i = (src & 0xf0) >> 4;
    if (i < 0x0a)   i = i + '0';
    else         i = i + '7';
    firstdata = i;

    i = (src & 0x0f);
    if (i < 0x0a)   i = i + '0';
    else         i = i + '7';
    seconddata = i;
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

    if ((BefKey == tmpkey) && (tmpkey < 0xff))
    {
        if (Charter > 50)
        {
            Charter = 0;

            if (!bKeyOn)
            {

                bKeyOn = 1;
                bKeyValid = 1;
                tmpkey = ~tmpkey;

                switch (tmpkey)
                {
                case  0x20:
                    CurKey = 'm';
                    break;
                case  0x10:
                    CurKey = 'c';
                    break;
                case  0x08:
                    CurKey = 'r';
                    break;

                case  0x04:
                    CurKey = 'u';
                    break;
                case  0x02:
                    CurKey = 'd';
                    break;
                case  0x01:
                    CurKey = 'e';
                    break;
                default:
                    CurKey = 'n';
                    bKeyOn = 0;
                    bKeyValid = 0;
                    break;
                }
            }
        }
    }
    else
    {
        BefKey = tmpkey;
        Charter = 0;
        bKeyOn = 0;
        CurKey = 'n';
    }
}






unsigned int ImportData(void)
{
    unsigned char high, low, good;
    unsigned char i, j, k;

    unsigned int  blkpt;

    good = 0;

    if (RxBuffer[3] >= 'A') 	j = (RxBuffer[3] - '7');
    else 					j = (RxBuffer[3] - '0');

    if (RxBuffer[4] >= 'A') 	k = (RxBuffer[4] - '7');
    else 					k = (RxBuffer[4] - '0');

    j = (j * 10) + k;

    blkpt = (unsigned int)(j * 16);


    for (i = 0;i < 16;i++)
    {
        k = (2 * i);
        if (RxBuffer[5+k] >= 'A') 	high = (RxBuffer[5+k] - '7');
        else 						high = (RxBuffer[5+k] - '0');

        high = ((high << 4) & 0xf0);
        if (RxBuffer[6+k] >= 'A') 	low = (RxBuffer[6+k] - '7');
        else 						low = (RxBuffer[6+k] - '0');

        if (Block0[blkpt+i] != (high | low))	good = 1;

        tmpram[i] = (high | low);
    }

    if (good == 1)
    {
        dest_ptr = (far unsigned char *)(&Block0[blkpt]);
        flash_write(source_ptr, size, dest_ptr);
    }


    RxBuffer[0] = ACK;
    RxBuffer[1] = 'w';
    RxBuffer[2] = 'F';
    RxBuffer[37] = ETX;
    RxBuffer[38] = 0;

    Serial();


    for (i = 0;i < 16;i++)
    {
        Message2[i] = ReadBack[i];
    }

    Message2[14] = RxBuffer[3];
    Message2[15] = RxBuffer[4];
    Message2[16] = 0x0;
    LCD_String_Out(0, 1, &Message2[0]);

    bKeyValid = 0;
    main_timer = 0;

    return(1);
}


unsigned int ExportData(void)
{
    unsigned char i, j, k, high, low, good;

    unsigned int  blkpt;

    good = 1;

    if (RxBuffer[3] >= 'A') 	j = (RxBuffer[3] - '7');
    else 					j = (RxBuffer[3] - '0');

    if (RxBuffer[4] >= 'A') 	k = (RxBuffer[4] - '7');
    else 					k = (RxBuffer[4] - '0');

    j = (j * 10) + k;


    blkpt = (unsigned int)(j * 16);


    for (i = 0;i < 16;i++)
    {
        k = (2 * i);
        if (RxBuffer[5+k] >= 'A') 	high = (RxBuffer[5+k] - '7');
        else 						high = (RxBuffer[5+k] - '0');

        high = ((high << 4) & 0xf0);
        if (RxBuffer[6+k] >= 'A') 	low = (RxBuffer[6+k] - '7');
        else 						low = (RxBuffer[6+k] - '0');

        if (Block0[blkpt + i] != (high | low)) good = 0;
    }


    if (good) j++;

    RxBuffer[0] = ACK;
    RxBuffer[1] = 'r';
    RxBuffer[2] = 'F';

    j = (j % 100);
    RxBuffer[3] = (j / 10) + '0';
    RxBuffer[4] = (j % 10) + '0';

    blkpt = (unsigned int)(j * 16);


    for (i = 0;i < 16;i++)
    {
        k = (i * 2);
        src = Block0[blkpt+i];
        HextoASCIIByte();
        RxBuffer[5+k] = firstdata;
        RxBuffer[6+k] = seconddata;
    }

    k = (i * 2);
    RxBuffer[5+k] = ETX;
    RxBuffer[6+k] = 0;


    Serial();

    for (i = 0;i < 16;i++)
    {
        Message2[i] = WriteBack[i];
    }

    Message2[14] = RxBuffer[3];
    Message2[15] = RxBuffer[4];
    Message2[16] = 0x0;
    LCD_String_Out(0, 1, &Message2[0]);


    bKeyValid = 0;
    main_timer = 0;
    return(1);
}


unsigned int NewLadderChk(void)
{
    if ((RxBuffer[1] == 'W') && (RxBuffer[2] == 'F'))
    {
        ImportData();
        return(1);
    }
    else if ((RxBuffer[1] == 'R') && (RxBuffer[2] == 'F'))
    {
        ExportData();
        return(1);
    }

    return(0);
}




unsigned int  NewDisplayLadder(void)
{
    unsigned char i;

    if (NewLadderChk())	return(0);

    for (i = 0;i < 16;i++)
    {
        Message1[i] = RxBuffer[4+i];
    }
    Message1[16] = 0x0;


    for (i = 0;i < 16;i++)
    {
        Message2[i] = RxBuffer[20+i];
    }
    Message2[16] = 0x0;


    LCD_String_Out(0, 0, &Message1[0]);
    LCD_String_Out(0, 1, &Message2[0]);

    i = RxBuffer[3];
    if ((i >= 'A') && (i <= 'F'))    i = i - '7';
    else if ((i >= '0') && (i <= '9'))    i = i - '0';
    else                                 i = 0xff;

    if ((i <= 0x0f) && (RxBuffer[2] > 0))
    {
        LCD_Cursor(i, 1);
        LCD_Command(dON_cOFF_bON);
    }
    else
    {
        LCD_Command(dON_cOFF_bOFF);
    }

    return(0);

}




InitPort(void)
{
    _RUNLED 		= HIGH;
    _RUNLED_TRIS 	= TRIS_OUTPUT;

    _SET_A1 		= HIGH;
    _SET_A1_TRIS 	= TRIS_INPUT;
    _SET_A2 		= HIGH;
    _SET_A2_TRIS 	= TRIS_INPUT;
    _SET_A3			= HIGH;
    _SET_A3_TRIS 	= TRIS_INPUT;
    _A_IN 			= HIGH;
    _A_IN_TRIS 		= TRIS_INPUT;
    _V_IN			= HIGH;
    _V_IN_TRIS 		= TRIS_INPUT;

    _IN_DAY			= HIGH;
    _IN_DAY_TRIS	= TRIS_INPUT;
    _IN_NIGHT		= HIGH;
    _IN_NIGHT_TRIS	= TRIS_INPUT;
    _IN_BLINK		= HIGH;
    _IN_BLINK_TRIS	= TRIS_INPUT;
    _SAVE_SW			= HIGH;
    _SAVE_SW_TRIS		= TRIS_INPUT;

    _LAMP_ON		= HIGH;
    _LAMP_ON_TRIS	= TRIS_OUTPUT;
    _PWM			= HIGH;
    _PWM_TRIS		= TRIS_OUTPUT;

    _RUNLED			= LOW;
    _SET_A1			= LOW;
    _SET_A2			= LOW;
    _SET_A3			= LOW;
    _A_IN			= LOW;
    _V_IN			= LOW;
    _IN_DAY			= LOW;
    _IN_NIGHT		= LOW;
    _IN_BLINK		= LOW;
    _SAVE_SW			= LOW;
    _LAMP_ON		= LOW;
    _PWM			= LOW;
}





void  InitAD(void)
{
    // ADCON2<2:0>: A/D Conversion Clock Select bits
    ADCS2 = 1;	// 111 = FRC (clock derived from A/D RC oscillator)
    ADCS1 = 1;
    ADCS0 = 1;
    // Analog Select bits : AN0~AN3 포트에 대하여 AD 또는 일반 포트로 설정할지 여부 설정
    PCFG3 = 1;	// 1010 = AN0~AN4 Ananlog
    PCFG2 = 0;
    PCFG1 = 1;
    PCFG0 = 0;


    ADFM = 1; // A/D Result Format Select bit, if ADFM=1 : ADRESH(MSB), ADRESL(LSB)
    VCFG1 = 0; // Voltage Reference bit
    VCFG0 = 0;

    // Analog Channel Select bits
    CHS3 = 0;
    CHS2 = 0;
    CHS1 = 0;
    CHS0 = 0;

    GODONE = 0; 	// A/D Conversion Status bit
    ADON = 1; 	// A/D On bit

    // When IPEN = 0:
    // PEIE=1 : Enables all unmasked peripheral interrupts
    IPEN = 0;	// Interrupt Priority Enable bit
    PEIE = 1; // Peripheral Interrupt Enable bit

    ADIE = 1; // A/D Converter (ADC) Interrupt Enable bit / 1 = Enables the A/D interrupt
    ADIF = 0; // A/D Converter Interrupt Flag bit / 0 = The A/D conversion is not complete

    AdCurValue = 0;
    AdCnt = 0;

    TSB.bAdInterrupt = 0;
    TSB.bAdSave = FALSE;

    AdChSel = 0;
}


void Set_AdCh(UCHAR AdSel)
{
	switch (AdSel)
	{
	case 0:
		CHS3 = 0;
        CHS2 = 0;
        CHS1 = 0;
        CHS0 = 0;
		break;
	case 1:
		CHS3 = 0;
        CHS2 = 0;
        CHS1 = 0;
        CHS0 = 1;		
		break;
	case 2:
		CHS3 = 0;
        CHS2 = 0;
        CHS1 = 1;
        CHS0 = 0;		
		break;
	case 3:
		CHS3 = 0;
        CHS2 = 0;
        CHS1 = 1;
        CHS0 = 1;		
		break;
	case 4:
		CHS3 = 0;
        CHS2 = 1;
        CHS1 = 0;
        CHS0 = 0;		
		break;
	default:
		CHS3 = 0;
        CHS2 = 0;
        CHS1 = 0;
        CHS0 = 0;		
		break;
	}
}



UCHAR ChangeAdChSel(UCHAR AdSel, tag_CurDay ch)
{	
    switch (AdSel)
    {
    case 0: // AN0, 낮 
        AdSel = 3;
        break;
    case 1: // AN1, 저녘 
        AdSel = 3;
        break;
    case 2: // AN2, 밤 
        AdSel = 3;
        break;
    case 3: // AN3, A_IN
        AdSel = 4;
        break;
    case 4: // AN4, V_IN      
		AdSel = ch;					
        break;
    default:
		AdSel = 3;		        
        break;
    }
	return AdSel;
}



bit	IsGet_InPutAd(UINT* InPutAD, UCHAR* bAD_Updated, UCHAR AdSel)
{
    unsigned long int tmpad;
    unsigned int 	itmpad;
	unsigned int	AvrAD;
	
    if (TSB.bAdInterrupt)
    {
        TSB.bAdInterrupt = FALSE;

        AdCurValue = (unsigned int)ADRESH;
        AdCurValue = AdCurValue << 8;
        AdCurValue = (AdCurValue & 0xff00);
        itmpad = (unsigned int)ADRESL;
        itmpad = (itmpad & 0x00ff);
        AdCurValue = (AdCurValue | itmpad);

        SumAD = SumAD + (unsigned long int)AdCurValue;
        AdCnt++;

        if (AdCnt >= 10)
        {
			if (SumAD > 0)
			{
				tmpad = SumAD / AdCnt;
				tmpad = (tmpad * 1000) / 192;	//204
				AvrAD = (unsigned int)tmpad;
			}
			else
			{
				AvrAD = 0;
			}
			
			InPutAD[AdSel] = AvrAD;
			bAD_Updated[AdSel] = TRUE;
			
            SumAD = 0;
            AdCnt = 0;
			return TRUE;
        }
		
        GODONE = 1;	//AD (Because.....Auto GODONE = 0)
    }
	return FALSE;
}





void InitPwm(void)
{
    unsigned char T2PreScale; //Timer2 Clock Prescale Select bits

    TMR2IE = FALSE;
    TMR2IF = FALSE;
    CCP1CON = 0x0C;	/* select PWM mode */

    //PERIOD=124;
    PERIOD = DUTI_MAX;
    PR2 = PERIOD;					// update the PWM period 주기 레지스터

    T2PreScale = 1;
    T2CON = (0x04 + T2PreScale);
}

void PwmOut(unsigned int DutyCycle)
{
    DC1B0 = (bit)DutyCycle;		//update the PWM duty cycle
    DC1B1 = (bit)(DutyCycle >> 1);
    CCPR1L = (DutyCycle >> 2);	//13.04.30
}





void WriteVal(unsigned int DutiCycle, unsigned int SetAVoltage, volatile const unsigned char* DestBuf)
{
    unsigned char SrcBuf[4];

    SrcBuf[0] = (unsigned char)DutiCycle;
    SrcBuf[1] = (unsigned char)(DutiCycle >> 8);
    SrcBuf[2] = (unsigned char)SetAVoltage;
    SrcBuf[3] = (unsigned char)(SetAVoltage >> 8);

    flash_write((far unsigned char *)SrcBuf, 4, (far unsigned char *)DestBuf);
}

void ReadVal(unsigned int* pSavedDutyCycle, unsigned int* pSavedSetA_Volt,
             volatile const unsigned char* SavedBuf, unsigned int* pSetA_Volt)
{
    unsigned int temp;

    temp = 0x0000;
    temp = SavedBuf[1];
    temp = temp << 8;
    *pSavedDutyCycle = temp | ((unsigned int)SavedBuf[0] & 0x00ff);
    DutyCycle = *pSavedDutyCycle;
	DutyCycle = DutyCycle + 5;
//	DutyCycle = (DutyCycle/100)*2 + DutyCycle;

    temp = 0x0000;
    temp = SavedBuf[3];
    temp = temp << 8;
    *pSavedSetA_Volt = temp | ((unsigned int)SavedBuf[2] & 0x00ff);
    *pSetA_Volt = *pSavedSetA_Volt; // 주간 셋팅 값
}


bit IsSetSw_UpEdge(void)
{
    if (_SAVE_SW == SETSW_PUSH) // 스위치를 눌렀을 때 !!!
    {
        if (SetSwCharterTimer > 100)
        {
            bSetSwPushOK = TRUE;
        }
    }
    else  // 스위치를 뗐을 때 !
    {
        SetSwCharterTimer = 0;
        if (bSetSwPushOK)
        {
            bSetSw_UpEdge = TRUE;
        }
        bSetSwPushOK = FALSE;
    }

    return bSetSw_UpEdge;
}



unsigned int GetDutyByCompareCurrent(unsigned int duty, unsigned int setVolt,
                                     unsigned int inVolt, unsigned char CurDayNight)
{
    long double Set_Current; // 변환된 볼륨에의한 셋팅 전류 값
    long double In_Current;  // 변환된 입력 피드백 전류 값
    long double Offset;

    if (CurDayNight == DAY) Set_Current = (long double)setVolt * SET_AMP_PER_VOLT1; // 166 x 4 = 664
    else if (CurDayNight == EVENING) Set_Current = (long double)setVolt * SET_AMP_PER_VOLT2; // 166 x 4 = 664
    else if (CurDayNight == NIGHT) Set_Current = (long double)setVolt * SET_AMP_PER_VOLT3; // 380 x 2 = 760
    else Set_Current = 0;
    In_Current = (((long double)inVolt - 600) / 60) * 1000;  // (635 - 600)/60 * 1000 = 583
    Offset = 100 - (Set_Current/20); // 오프셋 값
    if(Offset == 0) Offset = 10;

    if (In_Current < Set_Current) // 760 > 583
    {
        if ((In_Current + Offset) < Set_Current)   // 760 > (583+82)=645
        {
            if (duty < DUTI_MAX)	duty++;
            else					duty = DUTI_MAX;
        }
    }
    else if (In_Current > Set_Current)
    {
		Offset = Offset * 2;
        if (In_Current > (Set_Current + Offset))
        {
            if (duty > 0)		duty--;
        }
    }

    if (AnalogValidTime > 20)
    {
        if (setVolt <= A_SET_V_MIN)
            DutyCycle = 0;
        if (setVolt >= A_SET_V_MAX)
            DutyCycle = DUTI_MAX;
    }

    return duty;
}

// Blink Led On, Off 판별
bit IsInLED_ON(unsigned char bLedState, unsigned char* Timer)
{
    static bit bBlkLedOn;

    bBlkLedOn = TRUE;
    if (bLedState)
    {
        if (*Timer > 90) // LED OFF
            bBlkLedOn = FALSE;
    }
    else 	// LED ON
    {
        *Timer = 0;
        bBlkLedOn =  TRUE;
    }

    return bBlkLedOn;
}

unsigned char GetDayEveningNight(void)
{
    static bit bDayLed, bNightLed;
    unsigned char ret;

    bDayLed = IsInLED_ON(_IN_DAY, &InDayTimer);
    bNightLed = IsInLED_ON(_IN_NIGHT, &InNightTimer);

    if (bDayLed && (bNightLed == FALSE)) // 낮
        ret = DAY;
    else if (bDayLed && bNightLed) // 저녘
        ret = EVENING;
    else if ((bDayLed == FALSE) && bNightLed) // 밤
        ret = NIGHT;
    else
        ret = NONE;

    return ret;

}


void GetSetAD(void)
{
	if (arIs_AdUpd[0])
	{
		arIs_AdUpd[0] = FALSE;
		
		tmpSumSet[0] = tmpSumSet[0] + (unsigned long int)arInPutAD[0];
		tmpSetADCnt[0]++;

		if (tmpSetADCnt[0] >= 10)
		{
			stApl[0].SetA = (unsigned int)(tmpSumSet[0] / tmpSetADCnt[0]);
			tmpSetADCnt[0] = 0;
			tmpSumSet[0] = 0;
		}			
	}
	
	if (arIs_AdUpd[1])
	{
		arIs_AdUpd[1] = FALSE;
		
		tmpSumSet_1 = tmpSumSet_1 + (unsigned long int)arInPutAD[1];
		tmpSetADCnt_1++;

		if (tmpSetADCnt_1 >= 10)
		{
			stApl[1].SetA = (unsigned int)(tmpSumSet_1 / tmpSetADCnt_1);
			tmpSetADCnt_1 = 0;
			tmpSumSet_1 = 0;
		}			
	}
	
	if (arIs_AdUpd[2])
	{
		arIs_AdUpd[2] = FALSE;
		
		tmpSumSet_2 = tmpSumSet_2 + (unsigned long int)arInPutAD[2];
		tmpSetADCnt_2++;

		if (tmpSetADCnt_2 >= 10)
		{
			stApl[2].SetA = (unsigned int)(tmpSumSet_2 / tmpSetADCnt_2);
			tmpSetADCnt_2 = 0;
			tmpSumSet_2 = 0;
		}			
	}	

	
}

// 셋팅 스위치 눌렀을 때 APL 램프 셋팅 
void SetApaLamp(void)
{	
	if (arIs_AdUpd[3])
	{
		stApl[0].A_IN = arInPutAD[3];
		arIs_AdUpd[3] = FALSE;	
	
		if (CurDayNight == DAY) 			SetAVoltage = stApl[0].SetA;
		else if (CurDayNight == EVENING) 	SetAVoltage = stApl[1].SetA;
		else if (CurDayNight == NIGHT) 		SetAVoltage = stApl[2].SetA;
		else	SetAVoltage = 0;
	
		DutyCycle = GetDutyByCompareCurrent(DutyCycle, SetAVoltage, stApl[0].A_IN, CurDayNight);
		
	}
	PwmOut(DutyCycle);
	_LAMP_ON = TRUE; // LAMP ON		
}


void ApaLampOnOff(void)
{
	if ((IsInLED_ON(_IN_BLINK, &InBlinkTimer)) && (CurDayNight != NONE)) // Blink Led 가 On 일 때
	{
		if (bAgoBlkLedOff)
		{
			bAgoBlkLedOff = FALSE;
			StartTimer = 0;
	
			if (CurDayNight == DAY)
				ReadVal(&SavedDutyCycle1, &SavedSetA1_Volt, Saved1Buf, &stApl[0].SetA);
			else if (CurDayNight == EVENING)
				ReadVal(&SavedDutyCycle2, &SavedSetA2_Volt, Saved2Buf, &stApl[1].SetA);
			else if (CurDayNight == NIGHT)
				ReadVal(&SavedDutyCycle3, &SavedSetA3_Volt, Saved3Buf, &stApl[2].SetA);
			else
				DutyCycle = 0x0;
		}
		else if (CurDayNight != NONE)
		{
			if (StartTimer >= 100)
			{
				if (arIs_AdUpd[3])
				{
					stApl[0].A_IN = arInPutAD[3];
					arIs_AdUpd[3] = FALSE;
	
					if (CurDayNight == DAY) SetAVoltage = stApl[0].SetA;
					else if (CurDayNight == EVENING) SetAVoltage = stApl[1].SetA;
					else if (CurDayNight == NIGHT) SetAVoltage = stApl[2].SetA;
					else	SetAVoltage = 0;
	
					DutyCycle = GetDutyByCompareCurrent(DutyCycle, SetAVoltage, stApl[0].A_IN, CurDayNight);
				}
			}
		}
		PwmOut(DutyCycle);
		_LAMP_ON = TRUE; // LAMP ON			
	}
	else // Blink Led 가 Off 일 때
	{
		bAgoBlkLedOff = TRUE;
		DutyCycle = 0;		
		PwmOut(DutyCycle);
		_LAMP_ON = FALSE; // LAMP OFF 
	}
}





void main(void)
{
    di();
    Initial();
    Timer0Init();
    InitPort();
    InitAD();
    InitPwm();
    ei();

    GODONE = 1;	// A/D Conversion Status bit
    TMR0IE = 1;
    SWDTEN = 1;  // Software Controlled Watchdog Timer Enable bit / 1 = Watchdog Timer is on

    do
    {
        CurDayNight = GetDayEveningNight(); // NONE, DAY , EVENING , NIGHT 값 저장
        if (CurDayNight == DAY)
            ReadVal(&SavedDutyCycle1, &SavedSetA1_Volt, Saved1Buf, &stApl[0].SetA);
        else if (CurDayNight == EVENING)
            ReadVal(&SavedDutyCycle2, &SavedSetA2_Volt, Saved2Buf, &stApl[1].SetA);
        else if (CurDayNight == NIGHT)
            ReadVal(&SavedDutyCycle3, &SavedSetA3_Volt, Saved3Buf, &stApl[2].SetA);
        else
            DutyCycle = 0x0;

        _LAMP_ON = TRUE;
        PwmOut(DutyCycle);
        CLRWDT();
    }
    while (BeginTimer < 100);

    bSetSw_UpEdge = FALSE;
    bSetSwPushOK = FALSE;
    StartTimer = 0;
    bAgoBlkLedOff = FALSE;
    bInBlinkLED = FALSE;

    while (1)
    {
        CLRWDT();

		// NONE, DAY , EVENING , NIGHT 값 저장
        CurDayNight = GetDayEveningNight(); 
        
        // 셋업 스위치 누르고 뗐을 때 !
        if (IsSetSw_UpEdge())
        {
            bSetSw_UpEdge = FALSE;

            if (CurDayNight == DAY) WriteVal(DutyCycle, stApl[0].SetA, Saved1Buf);
            else if (CurDayNight == EVENING) WriteVal(DutyCycle, stApl[1].SetA, Saved2Buf);
            else if (CurDayNight == NIGHT) WriteVal(DutyCycle, stApl[2].SetA, Saved3Buf);
        }

		// AD 처리 
        if(IsGet_InPutAd(arInPutAD, arIs_AdUpd, AdChSel))
        {
			if(bSetSwPushOK)	AdChSel = ChangeAdChSel(AdChSel, CurDayNight);
			else				AdChSel = ChangeAdChSel(AdChSel, 3);	
			Set_AdCh(AdChSel);
			GODONE = 1;
        }
		
// Set1 에 대해서만 일단 적용 하였다. 
		// AMP Lamp 출력 처리 
		if (bSetSwPushOK)
		{
			GetSetAD();
			SetApaLamp();		
		}
		else
		{
			ApaLampOnOff();
			tmpSumSet[0] = 0;
			tmpSetADCnt[0] = 0;
			tmpSumSet_1 = 0;
			tmpSetADCnt_1 = 0;
			tmpSumSet_2 = 0;
			tmpSetADCnt_2 = 0;			
		}
    }
}





void interrupt isr(void)
{
    if (TMR0IF)
    {
        TMR0IF = 0 ;
        TMR0L = MSEC_L;
        TMR0H = MSEC_H;

        if (SetSwCharterTimer < 250)	SetSwCharterTimer++;

        if (indayHighTimer < 1000) indayHighTimer++;

        if (AnalogValidTime < 200)
            AnalogValidTime++;

        if (StartTimer < 1000)
            StartTimer++;

        if (InBlinkTimer < 200)
            InBlinkTimer++;
        if (InDayTimer < 200)
            InDayTimer++;
        if (InNightTimer < 200)
            InNightTimer++;

        if (BeginTimer < 1000)
            BeginTimer++;
    }

    if (ADIntFlag && ADIE)
    {
        ADIntFlag = 0;
        TSB.bAdInterrupt = TRUE;
    }
}




