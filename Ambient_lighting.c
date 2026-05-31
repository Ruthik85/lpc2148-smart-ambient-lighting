#include <lpc21xx.h>
#include "uart0.h"
#include "pin_connect_block.h"     
#include "pin_function_defines.h"
#include "adc.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "rtc.h"
#include "delay.h"
#include "defines.h"
#include "kpm.h"
#define led 28
u32 hour,min,sec,day,date,month,year;
u8 keyV;

void edit(void);

#define EINT0_CHNO 14              // Channel number of External Interrupt 0 (EINT0) in VIC

int readn(void)
{
	int sum=0;
	char num;
	while(1)
	{
		num=KeyScan();
		CharLCD(num);
		if((num>='0')&&(num<='9'))
		{
			sum=(sum*10)+(num-48);
		}
		else
			return sum;
	}
}

void menu(void)
{
	char op;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1 for editing");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("2 for exit");
	op=KeyScan();
	while(ColScan()==0);
	switch(op)
	{
		case '1':edit();
		break;
		case '2':break;
	}
	CmdLCD(CLEAR_LCD);
		
}
// *************** EINT0 Interrupt Service Routine ***************
void eint0_isr(void) __irq          // ISR for External Interrupt 0
{
		menu();
    delay_ms(100);                  // Small delay for visible LED toggle
    EXTINT = 1 << 0;                // Clear interrupt flag for EINT0
    VICVectAddr = 0;                // Signal end of ISR to the VIC
}

// *************** Function to Configure and Enable EINT0 ***************
void eint0_enable(void)
{

    cfgportpin(0, 16, FUN2);        // Configure P0.16 pin function as EINT0 (PINSEL1 bits = 10)

    // VICIntSelect = 0;            // (Optional) Configure interrupt as IRQ (not FIQ)
    VICIntEnable = 1 << EINT0_CHNO; // Enable EINT0 interrupt in the VIC
    VICVectCntl0 = (1 << 5) | EINT0_CHNO; // Enable slot 0 and assign EINT0 channel number
    VICVectAddr0 = (unsigned int)eint0_isr; // Load address of ISR into VIC slot 0

    // EXTMODE = 1 << 0;            // (Optional) Configure EINT0 as edge-triggered interrupt
    // EXTPOLAR = 1 << 0;           // (Optional) Configure interrupt to trigger on rising edge
}


int houre(void)
{
	int f=0,s=0,h=0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("enter hour");
	CmdLCD(GOTO_LINE2_POS0);
	keyV=KeyScan();
	CharLCD(keyV);
	while(ColScan()==0);
	f=keyV-48;
	keyV=KeyScan();
	CharLCD(keyV);
	while(ColScan()==0);
	s=keyV-48;
	h=f*10+s;
	if(h>23)
	{
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("invalid hour ");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("enter again");
		delay_ms(1000);
		houre();
	}
	CmdLCD(CLEAR_LCD);
		return h;
}

int minutee(void)
{
	int f=0,s=0,min=0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("enter minute");
	CmdLCD(GOTO_LINE2_POS0);
	keyV=KeyScan();
	
	CharLCD(keyV);
	while(ColScan()==0);
	f=keyV-48;
	keyV=KeyScan();
	
	CharLCD(keyV);
	while(ColScan()==0);
	s=keyV-48;
	min=f*10+s;
	if(min>59)
	{
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("invalid minute");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("enter again");
		delay_ms(1000);
		minutee();
	}
	CmdLCD(CLEAR_LCD);
		return min;
}

int seconde(void)
{
	int f=0,s=0,sec=0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("enter second");
	CmdLCD(GOTO_LINE2_POS0);
	keyV=KeyScan();
	
	CharLCD(keyV);
	while(ColScan()==0);
	f=keyV-48;
	keyV=KeyScan();
	
	CharLCD(keyV);
	while(ColScan()==0);
	s=keyV-48;
	sec=f*10+s;
	if(sec>59)
	{
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("invalid second");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("enter again");
		delay_ms(1000);
		seconde();
	}
	CmdLCD(CLEAR_LCD);
		return sec;
}

int datee(void)
{
	int f=0,s=0,date=0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("enter date");
	CmdLCD(GOTO_LINE2_POS0);
	keyV=KeyScan();
	CharLCD(keyV);
	while(ColScan()==0);
	f=keyV-48;
	keyV=KeyScan();
	CharLCD(keyV);
	while(ColScan()==0);
	s=keyV-48;
	date=f*10+s;
	CmdLCD(CLEAR_LCD);
		return date;
}

int monthe(void)
{
	int f=0,s=0,month=0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("enter month");
	CmdLCD(GOTO_LINE2_POS0);
	keyV=KeyScan();
	CharLCD(keyV);
	while(ColScan()==0);
	f=keyV-48;
	keyV=KeyScan();
	CharLCD(keyV);
	while(ColScan()==0);
	s=keyV-48;
	month=f*10+s;
	CmdLCD(CLEAR_LCD);
		return month;
}

int yeare(void)
{
	int f=0,s=0,year=0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("enter year");
	CmdLCD(GOTO_LINE2_POS0);
	year=readn();
	CmdLCD(CLEAR_LCD);
	return year;
}

int daye(void)
{
	int day=0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("enter day");
	CmdLCD(GOTO_LINE2_POS0);
	keyV=KeyScan();
	CharLCD(keyV);
	while(ColScan()==0);
	day=keyV-48;
	CmdLCD(CLEAR_LCD);
		return day;
}

void edit(void)
{
	char sel;
	int h=0,m=0,s=0,dt=0,yr=0,mth=0,dy=0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1hr,2mn,3sec,4dt,");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("5mth,6yr,7day");
	sel=KeyScan();
	while(ColScan()==0);
	switch(sel)
	{
		case '1':h=houre();
		RTCGetTime(&hour,&min,&sec);
		RTCSetTime(h,min,sec);
		break;
		case '2':m=minutee();
		RTCGetTime(&hour,&min,&sec);
		RTCSetTime(hour,m,sec);		
		break;
		case '3':s=seconde();
		RTCGetTime(&hour,&min,&sec);
		RTCSetTime(hour,min,s);		
		break;
		case '4':dt=datee();
		RTCGetDate(&date,&month,&year);
		RTCSetDate(dt,month,year);
		break;
		case '5':mth=monthe();
		RTCGetDate(&date,&month,&year);
		RTCSetDate(date,mth,year);
		break;
		case '6':yr=yeare();
		RTCGetDate(&date,&month,&year);
		RTCSetDate(date,month,yr);
		break;
		case '7':dy=daye();
		RTCSetDay(dy);
		break;
	}
}




void dispt(void)
{
	RTCGetTime(&hour,&min,&sec);
	RTCGetDate(&date,&month,&year);
	RTCGetDay(&day);
	UART0_TxString("\r\n time : ");
	U32UART0(hour);
	UART0_TxChar(':');
	U32UART0(min);
	UART0_TxChar(':');
	U32UART0(min);
	UART0_TxString("\r\n date : ");
	U32UART0(date);
	UART0_TxChar('/');
	U32UART0(month);
	UART0_TxChar('/');
	U32UART0(year);
}

int main()
{
	f32 eAR; 
  u32 adcDVal,ldrv,vo;
	WBYTE(IODIR1,24,0xFF);	
	InitKPM();
	Init_ADC();
	InitLCD();
	RTC_Init();
	UART0_Init();
	eint0_enable();
	IODIR1|= 1<<led;
	CmdLCD(0x0C);
	RTCSetTime(20,14,50);
	RTCSetDate(28,10,2025);
	RTCSetDay(2);
	IOCLR1=1<<led;
	while(1)
	{
		RTCGetTime(&hour,&min,&sec);		
		DisplayRTCTime(hour,min,sec);
		RTCGetDate(&date,&month,&year);
		DisplayRTCDate(date,month,year);
		RTCGetDay(&day);
		DisplayRTCDay(day);
		
		if(((hour>=18)&&(hour<=24))||((1<=hour)&&(hour<=6)))
		{
		Read_ADC(1,&adcDVal,&eAR);
		ldrv=eAR*100;
		//ldrv=(10000*(3.3-eAR))/eAR;
		UART0_TxString("\r\nLDR readings : ");
		U32UART0(ldrv);
			if(ldrv<200)
			{
				IOSET1=1<<led;
				UART0_TxString("\r\n LED ON");
			}
			else
			{
				IOCLR1=1<<led;
				UART0_TxString("\r\n DAY MODE - LED OFF");
				dispt();
				UART0_TxString("\r\n ligth intensity  :");
				U32UART0(ldrv);
			}
		}
		else
		{
			IOCLR1=1<<led;
			UART0_TxString("\r\n DAY MODE - LED OFF");
			dispt();
			UART0_TxString("\r\n ligth intensity  :");
			U32UART0(ldrv);
		}
	}
}
