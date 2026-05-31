#include <LPC21xx.H>

#include "rtc_defines.h"
#include "types.h"
#include "lcd.h"

signed char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

// RTC Initialization: Configures and enables the RTC
void RTC_Init(void) 
{
    PCONP |= (1 << 9);        // ?? ENABLE RTC POWER (MOST IMPORTANT)

    CCR = 0x00;               // Disable RTC
    CCR = RTC_CTC_RESET;      // Reset counters
    CCR = 0x00;               // Clear reset

    PREINT  = PREINT_VAL;
    PREFRAC = PREFRAC_VAL;

    CCR = RTC_CCR_EN | RTC_CLKSRC;  // Enable RTC + external crystal
}


void RTCGetTime(u32 *hr,u32 *mi,u32 *se)
{
	*hr = HOUR;
	*mi = MIN;
	*se = SEC;	
}

void DisplayRTCTime(u32 hr,u32 mi,u32 se)
{
	//SetCursor(1,0);
	CmdLCD(0x80);
	CharLCD((hr/10)+48);
	CharLCD((hr%10)+48);
	CharLCD(':');
	CharLCD((mi/10)+48);
	CharLCD((mi%10)+48);
	CharLCD(':');
	CharLCD((se/10)+48);
	CharLCD((se%10)+48);	
}

void RTCGetDate(u32 *dt,u32 *mo,u32 *yr)
{
	*dt = DOM;
	*mo = MONTH;
	*yr = YEAR;	
}

void DisplayRTCDate(u32 dt,u32 mo,u32 yr)
{
	CmdLCD(0xC0);
	//SetCursor(2,0);
	CharLCD((dt/10)+48);
	CharLCD((dt%10)+48);
	CharLCD('/');
	CharLCD((mo/10)+48);
	CharLCD((mo%10)+48);
	CharLCD('/');
	U32LCD(yr);	
}

void RTCGetDay(u32 *day)
{
	*day = DOW;
}
void DisplayRTCDay(u32 day)
{
	CmdLCD(0x8A);
	//SetCursor(1,10);
	StrLCD(week[day]);	
}

void RTCSetTime(u32 hr,u32 mi,u32 se)
{
	HOUR = hr;
	MIN = mi;
	SEC = se;
}
void RTCSetDate(u32 dt,u32 mo,u32 yr)
{
	DOM = dt;
	MONTH = mo;
	YEAR = yr;
}
void RTCSetDay(u32 day)
{
	DOW = day;
}

