/************************************************************************************
*                                                                                   *
*   File Name   : timebasetimer.c                                                   *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/

/* Include all other required application header files. */
#include "../apps/resource.h"

unsigned short SecondTimer;
unsigned short Timer_100mS;
unsigned short Timer_10mS;

/* Increments on each time base interrupt. */
volatile unsigned short InterruptCount;
/**********************************************************************************/
//unsigned short Led_index;

/* Update all system timers.
	Caution:	This routine must not read the EEPROM.*/
void DoTimers( void ) {
	unsigned short TimebaseCount;
	/* Read the number of timebase interrupts since last time. */
//	di();
	TimebaseCount = InterruptCount;
	InterruptCount=0;
//	ei();

    UpdateBuzzerTimer(&BuzzerControl, &TimebaseCount);
	if (Timer_10mS > ((unsigned short) TimebaseCount)){
		Timer_10mS -= TimebaseCount;
	}
	else {
		/* Get here every 10 millisecond. */
		if (Time_10mS>=TimebaseCount) Timer_10mS += Time_10mS-TimebaseCount;
	}
	
	if (Timer_100mS > ((unsigned short) TimebaseCount))
		Timer_100mS -= TimebaseCount;
	else {
		/* Get here every 100 millisecond. */
		if (Time_100mS>=TimebaseCount) Timer_100mS += Time_100mS-TimebaseCount;
		ToggleLEDstate(&RawLEDdata,LED_STATUS_LEFT);
	}
	/*	Decrement "SecondTimer" accordingly. */
	if (SecondTimer>((unsigned short) TimebaseCount))
		SecondTimer -= TimebaseCount;
	else {
		/* Get here every 1 second. */
		if (SecondTimer>=TimebaseCount) SecondTimer += Time_1S - TimebaseCount;
		if (buttonTimer>0)buttonTimer--;
		if (appSecTimer>0)appSecTimer--;
		if (lcdSecTimer>0)lcdSecTimer--;

	}
}

void HAL_SYSTICK_Callback(void){
	;
}

void HAL_IncTick(void)
{
	uwTick += uwTickFreq;
	/* Increment the timebase count once every interrupt. */
	InterruptCount++;
	/* Start A/D conversion of the next channel. */
}



