//pin_connect_block.c
#include<lpc214x.h>
void cfgportpin(unsigned int PortNo, unsigned int PinNo, unsigned int Fun)
{
	if(PortNo==0)
	{
		if(PinNo<=15)
		{
			PINSEL0=(PINSEL0&~(3<<(PinNo*2)))|(Fun<<(PinNo*2));
		}
		else
		{
			PINSEL1=(PINSEL1&~(3<<((PinNo-16)*2)))|(Fun<<((PinNo-16)*2));
		}
	}
}