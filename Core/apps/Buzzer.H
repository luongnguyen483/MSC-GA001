/************************************************************************************
*                                                                                   *
*   File Name   : buzzer.h                                                          *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/


#ifndef Buzzer_h
	#define Buzzer_h
#define DUTY_FULL_PERCENT	100
extern unsigned short Duty_Percent;

/*********************************************************************************************/
#define DUTY_FULL_PERCENT	100
extern unsigned short Duty_Percent;
/* Define the macros which enable and disable the buzzer. */
void EnableBuzzer();
void DisableBuzzer();

/* Define the flag definitions of the "BeepControlState" variable. */
#define EnabledFlags	((signed char) (BIT7|BIT6))	/* =11 ===> Doing a multi-beep sequence. */
#define MultiBeepFlag	               	BIT5			/* =1 ===> Doing beep part of a multi-beep sequence. */
#define FastBeeping		                BIT4			/* =1 ===> 2Hz beep rate, =0 ===> 0.5Hz beep rate. */
#define BeepCountMask	                (BIT3|BIT2|BIT1|BIT0)		/* Can do upto 15 beeps in the sequence. */
#define BeepCountMax	                15

typedef struct {
    /* These variables control the multi-beep process. */
    signed char BeepControlState;
    unsigned int BeepTimer;
    unsigned int BuzzerTimer;
    /* Timer used for the control of the multi-beep process. */
    unsigned int MultiBeepTimer;
}BuzzerControlStruct;
extern BuzzerControlStruct BuzzerControl;

/* Define the macro determining when in the beep part of a multi-beep sequence. */
#define DoingMultiBeep()	((BuzzerControl.BeepControlState&(EnabledFlags|MultiBeepFlag))==(EnabledFlags|MultiBeepFlag))
void DoShortBeep(void);
void DoNormalBeep(void);
void DoErrorBeep(void);
void Do3FastBeeps(void);
void Do3SlowBeeps(void);
void Do1HzBeeping(void);
void Do2HzBeeping(void);
void doBeepControl(void);
/* Declare all local functions. */
void DoMultiBeeps(unsigned char DoFastBeeps, unsigned char NumBeeps);
void DoBLE_Connected_Beep(void);
void DoBLE_Disconnected_Beep(void);

void doTimedBeep( BuzzerControlStruct *ptr, int timeRead );
void NoBeepControl(void);
void UpdateBuzzerTimer(BuzzerControlStruct *ptr , unsigned int *timeRead );

//void DoPWM_Buzzer(TIM_HandleTypeDef htim, unsigned short value);


void DoPWM_Buzzer(TIM_HandleTypeDef htim, unsigned short value);

#endif/*end of Buzzer_h*/

