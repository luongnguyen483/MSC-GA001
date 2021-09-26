/************************************************************************************
*                                                                                   *
*   File Name   : led.c                                                             *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/

/* Include all other required application header files. */
#include "../apps/resource.h"
unsigned short	RawLEDdata;
/*This function is to update the all the LEDs output*/
void UpdateLEDoutputs(unsigned short *ledData){
	unsigned short leds = *ledData;
	if (leds & IndexToMask(LED_STATUS_RIGHT)) LED_STATUS_RIGHT_ON();
	else LED_STATUS_RIGHT_OFF();

	if (leds & IndexToMask(LED_STATUS_LEFT)) LED_STATUS_LEFT_ON();
	else LED_STATUS_LEFT_OFF();
}

void LedTimeToggle(unsigned short *LEDptr, unsigned char LEDid, unsigned int rate, unsigned int* led_timer){
    if (*led_timer == 0) {
    	ToggleLEDstate(LEDptr, LEDid);
        *led_timer = rate;
    }
}

/* Turn all LEDs OFF*/
void AllLEDsOff(unsigned short	*LEDptr) {
	*LEDptr=0x00;
}

/* Turn a given LED on. */
void TurnLEDon(unsigned short *LEDptr, unsigned char LEDid) {
	*LEDptr |= IndexToMask(LEDid); 
}

/* Turn a given LED off. */
void TurnLEDoff(unsigned short *LEDptr, unsigned char LEDid) {
	*LEDptr &= ~IndexToMask(LEDid); 
}

/* See if a given LED is ON. */
unsigned char LEDisON(unsigned short *LEDptr, unsigned char LEDid) {
	return((*LEDptr) & IndexToMask(LEDid));
}
/* Toggle the state of a given LED. */
void ToggleLEDstate(unsigned short *LEDptr, unsigned char LEDid) {
	if (LEDisON(LEDptr,LEDid)) TurnLEDoff(LEDptr,LEDid);
	else TurnLEDon(LEDptr, LEDid);
}

/* Define the proportion of time the LED is ON for the slow flash rate
	(ON for 800mS, OFF for 200mS).
*/
#define SlowOnTime()	(signed char) (SecondTimer>=Time_200mS)
/* Define the proportion of time the LED is ON for the Extra slow flash rate
	(ON for 800mS, OFF for 750mS).
*/
#define ExtraSlowOnTime()	(signed char) ((SecondTimer)>=Time_750mS)

/*	Turn the specified LED on or off as required.
*/
void SetLEDstate( unsigned short *LEDptr, signed char On, signed char index) {
	if (On) TurnLEDon(LEDptr,index);
	else TurnLEDoff(LEDptr,index);
}

/*	This routine flashes a defined LED at a 0.250Hz rate.
*/
void ESlowFlashLED(unsigned short *LEDptr, signed char LEDid) {
	SetLEDstate(LEDptr, ExtraSlowOnTime(),LEDid);
}

/*	This routine flashes a defined LED at a 1Hz rate.
*/
void FlashLED( unsigned short *LEDptr, signed char LEDid) {
	SetLEDstate(LEDptr, SlowOnTime(), LEDid);
}

/*	This routine flashes a defined LED at a 4Hz rate.
*/
void FastFlashLED( unsigned short *LEDptr, signed char LEDid) {
	short	time;
	BOOL Flag=FALSE;
	time=SecondTimer;
/*	This routine determines if a 4Hz-flashing LED is to be on or off.
	The return status is:-
			TRUE ===> LED is on.
			FALSE ===> LED is off.
*/
	while (time>=Time_250mS) time-=Time_250mS;
	if (time>Time_125mS) Flag=TRUE;	
	SetLEDstate( LEDptr, Flag, LEDid );
}




