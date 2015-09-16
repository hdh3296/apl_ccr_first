#include	<pic18.h>

unsigned char flash_read(unsigned long addr)
{
	TBLPTRL=((addr)&0xFF);
	TBLPTRH=(((addr)>>8)&0xFF);
	TBLPTRU=(((addr)>>8)>>8);
	asm("\tTBLRD*+");
	return TABLAT;
}



void flash_write(far unsigned char * source_addr,unsigned char length,far unsigned char * dest_addr)
{
	unsigned char BUFFER[64];
	unsigned char index;
	unsigned char offset;

	offset=(unsigned char)dest_addr;
	while(offset>64)	offset-=64;

	dest_addr-=offset;
	
	while(length)
	{
		// fill the 64 byte data buffer either from ...
		for(index=0;index<64;index++)
		{
			if((index>=offset)&&(length))	// specifed data area or ...
			{
				BUFFER[index]=*(source_addr++);
				length--;
			}
			else				// otherwise from destination sector.
				BUFFER[index]=*(dest_addr+index);
		}

		FLASH_ERASE(dest_addr);
	
// now begin to copy the buffer to the destination area
#if defined(SMALL_DATA)
		TBLPTRU=0;	// if 16 bit code pointers selected, TBLPTRU must be cleared manually
#endif
		TBLPTR=--dest_addr;	// load the destination address
		
		offset=0;
		for(index=0;index<64;index++)
		{
			
			TABLAT=BUFFER[index];	// copy the data buffer to the
			asm("\tTBLWT+*");	// internal write buffer	
			
			if(++offset==8)	// after every 8th byte, the
			{			// the write buffer is written to flash.
				EEPGD=1;WREN=1;		// this is the required sequence
				CARRY=0;if(GIE)CARRY=1;GIE=0;
				EECON2=0x55;
				EECON2=0xAA;
				WR=1;
				asm("\tNOP");
				if(CARRY)GIE=1;
				WREN=0;
				offset=0;
			}
		}
		dest_addr+=65;
	}
}

