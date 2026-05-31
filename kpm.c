//kpm.c
#include <LPC21xx.h>
#include "types.h"
#include "defines.h"
#include "delay.h"
#include "kpm_defines.h"

/*
u8 kpmLUT[4][4]=
{
	{1,2,3,4},
	{5,6,7,8},
	{9,10,11,12},
	{13,14,15,16}
};
*/

u8 kpmLUT[4][4]=
{
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'c','0','=','+'}
};

u32 ColScan(void)
{
	return (RNIBBLE(IOPIN1,COL0)<15) ? 0 : 1;
}

u32 RowCheck(void)
{
	u32 r;
	for(r=0;r<=3;r++)
	{
		//grounding row 0 to 3 iteratively
		WNIBBLE(IOPIN1,ROW0,~(1<<r));
		//check wrt row grounded if cols is other than
		//all ones
		if(ColScan()==0)
			break ;
	}
	//re-initialize all rows to ground
	WNIBBLE(IOPIN1,ROW0,0);
	return r;
}	

u32 ColCheck(void)
{
	u32 c;
	for(c=0;c<=3;c++)
	{
		if(RBIT(IOPIN1,COL0+c)==0)
			break;
	}
	return c;
}

void InitKPM(void)
{ 
	//initialize all rows as output to ground
	WNIBBLE(IODIR1,ROW0,15);
	//WNIBBLE(IOPIN1,ROW0,0);
	//all cols are default input high
}	
		
u32 KeyScan(void)
{
	u32 r,c;
	//wait to detect any key press
	while(ColScan());
	//Identify row in which key was pressed
	r=RowCheck();
	//Identify col in which key was pressed
	c=ColCheck();
	//extract key value from LUT
	while(ColScan()==0);
	delay_ms(100);
	return kpmLUT[r][c];
}
