/************************************************************************************
*                                                                                   *
*   File Name   : buzzer.c                                                          *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/

/* Include all other required application header files. */
#include "../apps/resource.h"
unsigned short Duty_Percent =100;
void DoPWM_Buzzer(TIM_HandleTypeDef htim, unsigned short value){
	unsigned long pwm_full_scale_value = DUTY_FULL_PERCENT ;
	htim.Init.Period = 1000-1;
	htim.Instance->CCR1 = (unsigned short) (((uint32_t) value)*1000/pwm_full_scale_value);
}
void EnableBuzzer(){
	Duty_Percent = 50;
}
void DisableBuzzer(){
	//check to see 0% is off or 100% is off
	Duty_Percent =100;
}

/*********************************************************************************************/
BuzzerControlStruct BuzzerControl;
/***************************************************************************/
/***************************************************************************/
/* ALL THE FOLLOWING CODE DOES MULTI-BEEP CONTROL.                         */
/***************************************************************************/
/***************************************************************************/

void UpdateBuzzerTimer(BuzzerControlStruct *ptr , unsigned int *timeRead ){
    unsigned int timeCount = *timeRead;
    /* Decrement accordingly. */
    if ( ptr->BeepTimer ) {
        if ( ptr->BeepTimer >  timeCount ) ptr->BeepTimer -= timeCount;
        else {
            /* Beep timer has just expired, and so turn off the
            beeper if not doing the beep part of a multi-beep
            sequence.
            */
            ptr->BeepTimer = 0;
            if ( !DoingMultiBeep() ) DisableBuzzer();
        }
    }
    if ( ptr->BuzzerTimer > timeCount )
        ptr->BuzzerTimer -= timeCount;
    else ptr->BuzzerTimer = 0;

    if ( ptr->MultiBeepTimer > timeCount )
        ptr->MultiBeepTimer -= timeCount;
    else ptr->MultiBeepTimer=0;
}
/*  Do a timed beep.  Note that while "BeepTimer!=0", the pushbuttons are
  locked out.
*/
void DoTimedBeep( BuzzerControlStruct *ptr, int timeRead) {
    ptr->BeepTimer=timeRead;
    EnableBuzzer();
}
void DoShortBeep(void) {
    DoTimedBeep(&BuzzerControl, Time_10mS);
}

void DoNormalBeep(void) {
    DoTimedBeep(&BuzzerControl, Time_100mS);
}

void DoErrorBeep(void) {
    DoTimedBeep(&BuzzerControl, Time_250mS);
}

/*  Beep continuously at the rate required.*/
void DoSlowHzBeeping( BuzzerControlStruct *ptr, unsigned int rate) {
    if (ptr->BeepTimer == 0) {
        ptr->BeepTimer = rate;
        DoNormalBeep();
    }
}

/*  Beep at a 1Hz rate.  Need to continuously call this function.*/
void Do1HzBeeping(void) {
    DoSlowHzBeeping( &BuzzerControl, Time_1S);
}

/*  Beep at a 2Hz rate.  Need to continuously call this function.*/
void Do2HzBeeping(void) {
    DoSlowHzBeeping( &BuzzerControl, Time_500mS);
}
/* Do a 3 x 2Hz beep sequence.  If you want 3 fast beeps every ?? minutes,
  then you need to continuously call this function.
*/
void Do3FastBeeps(void) {
    DoMultiBeeps(TRUE,3);
}
void Do3SlowBeeps(void) {
    DoMultiBeeps(FALSE,3);
}

void DoBLE_Disconnected_Beep(void) {
    DoTimedBeep(&BuzzerControl, Time_1S);
}
void DoBLE_Connected_Beep(void) {
    DoTimedBeep(&BuzzerControl, Time_100mS);
}

/*  Turn off any multi-beep control which is currently happening.
*/
void NoBeepControl(void) {
    /* If not doing a  beep, and in the beep part of a multi-beep
      sequence, then turn the beeper off.
    */
    if (( BuzzerControl.BeepTimer==0 )&&DoingMultiBeep()) DisableBuzzer();
    /* Disable the multi-beep control. */
    BuzzerControl.BeepControlState=0;
}

/* Start a multi-beep sequence. */
void DoMultiBeeps(unsigned char DoFastBeeps, unsigned char NumBeeps) {
    if (NumBeeps==0) return;
    /* Make sure there are no more than the maximum number of beeps. */
    if (NumBeeps>BeepCountMax) NumBeeps = BeepCountMax;
    /* Start the sequence with the first beep, doing fast beeps if required. */
    BuzzerControl.BeepControlState=EnabledFlags+MultiBeepFlag+NumBeeps;
    if (DoFastBeeps) {
        BuzzerControl.BeepControlState|=FastBeeping;
        BuzzerControl.MultiBeepTimer = Time_150mS;
    }
    else BuzzerControl.MultiBeepTimer = Time_1S;
    EnableBuzzer();
}

/*  This is the general purpose multi-beep driver routine.  Each beep occurs
  at a:-
    - 0.5Hz rate for the slow beep sequence, or
    - 2Hz rate for the fast beep sequence.
*/
void doBeepControl(void) {
    if (( (BuzzerControl.BeepControlState&EnabledFlags) == EnabledFlags)&&( BuzzerControl.MultiBeepTimer==0)) {
        /* Doing a multi-beep sequence and it is time to do the next stage
          of the sequence.
        */
        if (DoingMultiBeep()) {
            /* If not doing a keyboard beep, then turn the beeper off. */
            if (BuzzerControl.BeepTimer==0) DisableBuzzer();
            /* Just finished a beep and so see if further beeps are required. */
            BuzzerControl.BeepControlState--;
            if ((BuzzerControl.BeepControlState&BeepCountMask)==0) {
              /* Finished the multi-beep sequence. */
              BuzzerControl.BeepControlState=0;
            }
            else {
              /* Still busy doing the multi-beep sequence. */
              BuzzerControl.BeepControlState&=~MultiBeepFlag;
            }
        }
        else {
            /* Need to start the next beep. */
            BuzzerControl.BeepControlState |= MultiBeepFlag;
            EnableBuzzer();
        }
        if (BuzzerControl.BeepControlState&FastBeeping) BuzzerControl.MultiBeepTimer = Time_150mS;
        else BuzzerControl.MultiBeepTimer = Time_1S;
    }
}
