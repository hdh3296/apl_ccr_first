

#include    <pic18.h>

#include        "setup.h"
//#include        "fontout.h"
//#include        "iodef.h"
//#include        "..\can_4480\you_can.h"
//#include        "..\..\system_com\memory_map.h"




//volatile const unsigned char Block[10][64];	/*this is the variable in FLASH where the old text resides*/
//unsigned char tmpram[64];


/*
volatile const unsigned char information[]={LOCAL_NM,HIB_HPI,SUBDOOR_SEL,OFFSET_FLR,BAGGAGE,COMPANY,SEARCH2,SEARCH3,SEARCH4,SEARCH5,NC_END};
unsigned char new_value[]={0,0,0,0,0,0,0,0,0,0,0};	                                
far unsigned char * source_ptr = (far unsigned char *)new_value;                   
far unsigned char * dest_ptr = (far unsigned char *)information;
unsigned char size = 11;						
*/


/*
unsigned    char    SrcAddress;
unsigned    char    LocalNumber=0;
unsigned    char    SubDoor=0;
unsigned    char    offset_flr;
unsigned    char    ButtonType;


bit   ChangeSetup=0;
bit   UpKeyOn=0;
bit   UpKeyLong=0;
bit   UpKeyOneTouch=0;
bit   DnKeyOn=0;
bit   DnKeyLong=0;
bit   DnKeyOneTouch=0;
bit   CmpSetBit=0;
bit   MaskSetBit=0;


void    LoadSetupValue(void)
{
    LocalNumber=flash_read((unsigned long)(&information[0]));
    LocalNumber=LocalNumber;

    DspModel=flash_read((unsigned long)(&information[1]));
    DspModel=DspModel;
    if(DspModel > 2)   DspModel = ES00;     

    SubDoor=flash_read((unsigned long)(&information[2]));
    SubDoor=SubDoor;
    if(SubDoor > 1)   SubDoor = 0;     

    offset_flr=flash_read((unsigned long)(&information[3]));
    if(offset_flr > 7)   offset_flr = 0;     

    ButtonType=flash_read((unsigned long)(&information[4]));

    Company=flash_read((unsigned long)(&information[5]));
}






void    UpDnKeyCheck(void)
{
    
    if(UpKeyBit){
        if(UpButtonTime > 100){
            UpKeyLong=1;
            UpKeyOn=0;
        }
        else if(UpButtonTime > 0){
            UpKeyOn=1;
            UpKeyLong=0;
        }
        else{
            UpKeyOn=0;
            UpKeyLong=0;
        }
    }
    else{
        UpButtonTime=0;
        if(UpKeyOn){
            UpKeyOn=0;
            UpKeyOneTouch=1;
        }
        UpKeyLong=0;
    }

    if(DnKeyBit){
        if(DnButtonTime > 100){
            DnKeyLong=1;
            DnKeyOn=0;
        }
        else if(DnButtonTime > 0){
            DnKeyOn=1;
            DnKeyLong=0;
        }
        else{
            DnKeyOn=0;
            DnKeyLong=0;
        }
    }
    else{
        DnButtonTime=0;
        if(DnKeyOn){
            DnKeyOn=0;
            DnKeyOneTouch=1;
        }
        DnKeyLong=0;
    }
}








void    CompanyWrite(unsigned char cmp) //new
{
    unsigned char i;

    for(i=0;i<size;i++){
        new_value[i]=flash_read((unsigned long)(&information[i]));
    }

    new_value[5]=cmp;
    flash_write(source_ptr,size,dest_ptr);
}




void    SetupMode(void)
{

    unsigned char i,j,k,mode,topchar;

    i=0;
    mode=0;

    for(i=0;i<size;i++){
        new_value[i]=flash_read((unsigned long)(&information[i]));
    }

    do{
        CLRWDT();

        #ifdef  __TYPE_ES15
            if(mode==1)         mode=2;
//            else if(mode==3)    mode=0;
        #endif     

        switch(mode){
            case    0:
                j=28;   //l local number
                topchar=4;
                break;
            case    1:
                j=24;   //H hib hpi
                topchar=2;
                break;
            case    2:  //s subdoor
                j=35;
                topchar=2;
                break;
            case    3:  //F offset floor
                j=22;
                topchar=8;
                break;
            case    4:  //B offset floor
                j=18;
                topchar=2;
                break;
    
        }        
        Display(new_value[mode],j,mode);
        UpDnKeyCheck();
        if(UpKeyOneTouch){
            mode=(mode+1)%5;
            UpKeyOneTouch=0;
        }
        else if(DnKeyOneTouch){
            k=new_value[mode];
            k=(k+1)%topchar;
            new_value[mode]=k;
            DnKeyOneTouch=0;
            ChangeSetup=1;    
       }
    }while(!UpKeyLong && !DnKeyLong);

    if(ChangeSetup){
		flash_write(source_ptr,size,dest_ptr);
        ChangeSetup=0;
    }

    LoadSetupValue();
    asm("reset");
}



void SetupCheck(void)
{

    unsigned char i;

    i=1;

    ChangeSetup=0;
    UpButtonTime = 0;
    DnButtonTime = 0;


    shiftTime=0;
    while(shiftTime==0);


    do{
        UpDnKeyCheck();
        if(UpKeyLong){
            i=0;
            break;        
        }                
        CLRWDT();    
//    }while(UpKeyBit && DnKeyBit);
    }while(UpKeyBit);

    if(i==0){
        for(i=0;i<size;i++){
            new_value[i]=flash_read((unsigned long)(&information[i]));
        }

        do{
            i=0;
            Display(new_value[i],28,0);
            UpDnKeyCheck();
            CLRWDT();            
        }while(UpKeyLong || DnKeyLong);

        SetupMode();
    }    

    if(ChangeSetup){
		flash_write(source_ptr,size,dest_ptr);
        ChangeSetup=0;
    }

    LoadSetupValue();

}
*/


volatile const unsigned char Block[10][64];
	/*this is the variable in FLASH where the old text resides*/
unsigned char tmpram[64];


far unsigned char * source_ptr;
far unsigned char * dest_ptr;
unsigned char size = 64;						

void    BlockWrite(unsigned char blk) 
{
	dest_ptr   = (far unsigned char *)(Block[blk]);
	source_ptr = (far unsigned char *)tmpram;   
	
    flash_write(source_ptr,size,dest_ptr);
}


/*
void    BlockRead(unsigned char blk) 
{
	unsigned char i;

    for(i=0;i<size;i++){
        tmpram[i]=flash_read((unsigned long)(&Block[blk][i]));
    }
}
*/
