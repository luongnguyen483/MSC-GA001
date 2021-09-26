/************************************************************************************
*                                                                                   *
*   File Name   : TimeBaseTimer.h                                                   *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/

#ifndef TIMEBASETIMER_H
	#define TIMEBASETIMER_H
/* Define the crystal frequency.*/
#define BASE_CLOCK_KHZ			48000
#define PERIPHERAL_CLOCK_KHZ	BASE_CLOCK_KHZ/2

/* Increments on each time base interrupt. */
extern volatile unsigned short InterruptCount;
extern unsigned short SecondTimer;
extern unsigned short Timer_100mS;
extern unsigned short Timer_10mS;
void DoTimers(void);

/* Define how to reset the watchdog timer count back to zero. */
#define ResetWatchdogTimer()	WDT.WDTRR = 0x00;\
								WDT.WDTRR = 0xFF
								

#endif	/* TIMEBASETIMER_H */

