/************************************************************************************
*                                                                                   *
*   File Name   : leds.h                                                            *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/


#ifndef leds_h
	#define leds_h
#define LED_STATUS_RIGHT 0
#define LED_STATUS_LEFT 1

#define LED_STATUS_RIGHT_OFF()		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET) //GPIOC &= ~GPIO_PIN_8
#define LED_STATUS_RIGHT_ON()		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET) //GPIOC |= GPIO_PIN_8
#define LED_STATUS_LEFT_OFF()		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET) //GPIOC &= ~GPIO_PIN_8
#define LED_STATUS_LEFT_ON()		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET) //GPIOC |= GPIO_PIN_8


/* The raw data written to the LED array. */
extern unsigned short	RawLEDdata;
void AllLEDsOff(unsigned short	*ptr);

void LedTimeToggle(unsigned short *LEDptr, unsigned char LEDid, unsigned int rate, unsigned int* led_timer);
void TurnLEDon( unsigned short *LEDptr, unsigned char LEDid);
void TurnLEDoff( unsigned short *LEDptr, unsigned char LEDid);
unsigned char LEDisON( unsigned short *LEDptr, unsigned char LEDid);
void SetLEDstate( unsigned short *LEDptr, signed char On, signed char index);
void ToggleLEDstate( unsigned short *LEDptr, unsigned char LEDid);
void FlashLED( unsigned short *LEDptr, signed char LEDid);
void FastFlashLED( unsigned short *LEDptr, signed char LEDid);
void ESlowFlashLED( unsigned short *LEDptr, signed char LEDid);

#endif/*end of leds*/

