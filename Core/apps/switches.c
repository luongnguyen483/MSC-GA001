/************************************************************************************
*                                                                                   *
*   File Name   : switches.c                                                        *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/
#include "resource.h"

/* Used to track the number of presses of a specified key, for
	the security access process.
*/
unsigned char MultiPressCount;
/*	Lookup table for translating from bit-number to
	equivalent SET-bit pattern for index range of
	1...14 inclusive.
*/
const unsigned short IndexToMaskTable[]={
	0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,
	0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000};
	
const unsigned short SwitchEnumTable[]={ ENTER_BUTTON,RIGHT_BUTTON,LEFT_BUTTON,UP_BUTTON,DOWN_BUTTON,ESC_BUTTON };
BOOL	PendingSwitchEvent;

/* Variables used in decoding the button events. */
unsigned short	LastButtonPattern;
unsigned char	ButtonPressedTimer;		/* 100mS resolution. */
unsigned char buttonTimer;		/* 1s resolution. */

/* This variable is used to software-force (emulate) a button event. */
const struct ButtonEventStruct	*ForcedButton;
/*	This function translates the "RawAtoDvalue" to ButtonStatus.
*/
/* The raw data from the switch matrix. */
unsigned short	SwitchRaw[2];


/*********************************************************************/
/* THIS CODE RELATING TO THE PUSH BUTTON INTERFACE.                  */
/*********************************************************************/

void UpdateAllSwitches(void){
   	UpdateSwitchRaw(&SwitchRaw[0], GetButtonStatusPressed((unsigned short)ENTER, ButtonsPortC), ENTER_BUTTON);
   	UpdateSwitchRaw(&SwitchRaw[0],GetButtonStatusPressed((unsigned short)RIGHT, ButtonsPortA),RIGHT_BUTTON);
   	UpdateSwitchRaw(&SwitchRaw[0],GetButtonStatusPressed((unsigned short)LEFT, ButtonsPortA),LEFT_BUTTON);
   	UpdateSwitchRaw(&SwitchRaw[0],GetButtonStatusPressed((unsigned short)UP, ButtonsPortA),UP_BUTTON);
   	UpdateSwitchRaw(&SwitchRaw[0],GetButtonStatusPressed((unsigned short)DOWN, ButtonsPortA),DOWN_BUTTON);
   	UpdateSwitchRaw(&SwitchRaw[0],GetButtonStatusPressed((unsigned short)ESC, ButtonsPortA),ESC_BUTTON);
   	//read second time
   	UpdateSwitchRaw(&SwitchRaw[1],GetButtonStatusPressed((unsigned short)ENTER,ButtonsPortC),ENTER_BUTTON);
   	UpdateSwitchRaw(&SwitchRaw[1],GetButtonStatusPressed((unsigned short)RIGHT,ButtonsPortA),RIGHT_BUTTON);
   	UpdateSwitchRaw(&SwitchRaw[1],GetButtonStatusPressed((unsigned short)LEFT, ButtonsPortA),LEFT_BUTTON);
   	UpdateSwitchRaw(&SwitchRaw[1],GetButtonStatusPressed((unsigned short)UP, ButtonsPortA),UP_BUTTON);
   	UpdateSwitchRaw(&SwitchRaw[1],GetButtonStatusPressed((unsigned short)DOWN, ButtonsPortA),DOWN_BUTTON);
   	UpdateSwitchRaw(&SwitchRaw[1],GetButtonStatusPressed((unsigned short)ESC, ButtonsPortA),ESC_BUTTON);
}

/*	This function returns the button pressed status, if Pressed the value is 0
 and the return value is TRUE.
*/
BOOL GetButtonStatusPressed(unsigned short ButtonIndex, unsigned long Port) {
	if (Port&ButtonIndex) return(FALSE);
	return(TRUE);	
}	

/*	This function returns with the number of set bits of "mask".
*/
unsigned char NumberOfSetBits(unsigned short mask) {
	unsigned char	count=0;
	while (mask) {
		if (mask&1) count++;
		mask>>=1;
	}
	return(count);
}

/*	This function translates an index (or bit number) to a SET-bit of a mask.
	Valid range of "index" is 0...15.  Return values is:-
				0x0001 for index<=0
				...
				0x8000 for index>=15
*/
unsigned short IndexToMask(signed short index) {
	if (index<=0) return(1);
	if (((unsigned char) index)>=15) return(0x8000);
	return(GetConstUINT((signed char*) (IndexToMaskTable+((unsigned char) index)-1)));
}

/*	This function returns with the keypress bit assignment, given the
	raw key-matrix index.
*/
unsigned short GetKeyBit(unsigned char SwitchIndex) {
	return(GetConstShort(SwitchEnumTable+SwitchIndex));
}

/*	This general switch-update function updates the "mask"ed bit of "dest" according to
	the state of "Activated" (bit is set if Activated<>0, or cleared if Activated==0).
*/
void UpdateSwitchRaw(unsigned short *dest, unsigned char Activated, unsigned short mask) {

   	if (Activated != 0) {
   		*dest|=mask;
   	}
   	else *dest&=~mask;
}
/*************************************************************************************/
/******** THIS FUNCTION IS THE APPLICATION'S INTERFACE TO THE BUTTONS. ***************/
/*************************************************************************************/

/*	This function checks the button event type:-
		- BUTTON_UNCHANGED, or
		- BUTTON_ACTIVATED, or
		- BUTTON_DEACTIVATED.
*/
unsigned char ButtonEventType(unsigned short ButtonPattern) {
	/* See if the button pattern has changed. */
	if (LastButtonPattern==ButtonPattern) return(BUTTON_UNCHANGED);
	/* The button pattern has changed and so reset the button-pressed timer. */
	ButtonPressedTimer=0;
	/* Determine whether a button has activated or deactivated. */
	if (NumberOfSetBits(LastButtonPattern)<NumberOfSetBits(ButtonPattern))
		return(BUTTON_ACTIVATED);
	return(BUTTON_DEACTIVATED);
}

/*	This function searches "ButtonEventList[]" for the specified timed button event
	of "ButtonPattern".  The return value is:-
			>=0 ===> Event was in list, the return value being the "ButtonEventList[]" index.
			-1 ===> Event was not in the list.
*/
signed char FindTimedButtonEvent(const struct ButtonEventStruct *ButtonEventList, unsigned short ButtonPattern) {
	signed char index=0;
	/* Search the list for the event. */
	while (ButtonEventList->Buttons!=0) {
		/* See if this is the event. */
		if ((ButtonEventList->Buttons==ButtonPattern)&&(ButtonEventList->Seconds!=0)) {
			/*	This is a timed button pattern.  See if the required time has expired.
			*/
			if (ButtonPressedTimer>=(ButtonEventList->Seconds)*10) {
				/* Reset the button-pressed timer. */
				ButtonPressedTimer=0;
				/* Have found the event. */
				return(index);
			}
		}
		/* Keep searching. */
		index++;
		ButtonEventList++;
	}
	/* The given event was not found. */
	return(-1);
}
/*	This function searches "ButtonEventList[]" to see if the specified "ButtonPattern" is used
	at all.  The return value is:-
			FALSE ===> This button is used.
			TRUE ===> This button is not used.
*/
BOOL ButtonNotUsed(const struct ButtonEventStruct *ButtonEventList, unsigned short ButtonPattern) {
	/* Search the list for the event. */
	while (ButtonEventList->Buttons!=0) {
		/* See if this button pattern is used. */
		if (((ButtonEventList->Buttons)&ButtonPattern)==ButtonPattern) {
			/*	This button is used. */
			return(FALSE);
		}
		/* Keep searching. */
		ButtonEventList++;
	}
	/* This button is not used. */
	return(TRUE);
}


/*	This function searches "ButtonEventList[]" for the specified "ActivateEvent"
	of "ButtonPattern".  The return value is:-
			>=0 ===> Event was in list, the return value being the "ButtonEventList[]" index.
			-1 ===> Event was not in the list.
*/
signed char FindButtonEvent(const struct ButtonEventStruct *ButtonEventList, unsigned short ButtonPattern,
		BOOL ActivateEvent) {
	signed char index=0;
	/* Search the list for the event. */
	while (ButtonEventList->Buttons!=0) {
		/* See if this is the event. */
		if ((ButtonEventList->Buttons==ButtonPattern)&&(ButtonEventList->Activate==ActivateEvent)) {
			/*	Both the button pattern and ACTIVATE type matches.  This is not an event if a
				timed button is deactivating.
			*/
			if ((ButtonEventList->Activate==TRUE)||(ButtonEventList->Seconds==0)) {
				/* Have found the event. */
				return(index);
			}
		}
		/* Keep searching. */
		index++;
		ButtonEventList++;
	}
	/* The given event was not found. */
	return(-1);
}
/*	This routine is the low-level routine, decoding "SwitchRaw[]" determining which
	switches are presently closed.  If the reading is noisy then B15 is set (in which case this reading
	is to be ignored). 
*/
unsigned short GetButtonPattern(void) {
	unsigned short	ReturnValue,SwitchMask,status;
	unsigned char	SwitchIndex;
	/* Setup default of no buttons pressed. */
	ReturnValue=0;
	/* See what buttons are pressed, if any. */
	for (SwitchIndex=0,SwitchMask=BIT0; SwitchIndex<=MAX_SWITCH_INDEX; SwitchIndex++,SwitchMask<<=1) {
		/* Read first interrupt-level raw value. */
		status = SwitchRaw[0]&SwitchMask;
		/* Check to see if the reading is noisy. */
		if (status!=(SwitchRaw[1]&SwitchMask)) {
			/* The button reading is noisy, and so ignore. */
			return(NOISY_BUTTONS);
		}
		/* The switch reading is not noisy and so process it. */
		if (status) {
			/* Record the button press. */
			ReturnValue+=GetKeyBit(SwitchIndex);
		}
	}
	/* Return with the button status. */
	return(ReturnValue);
}
/*	This function checks
	to see if any button event, as defined by "ButtonEventList[]", has occurred.
	The return values are:-
		>=0 ===> Have a valid button event, this being the corresponding
					index of ButtonEventList[].
		-1 ===> No button event (NO_BUTTONS).
		-2 ===> Illegal button activation event (ILLEGAL_BUTTON_ACTIVATION).
*/
signed char GetButtonEvent(const struct ButtonEventStruct *ButtonEventList) {
	unsigned short	ButtonPattern;
	signed char	ButtonEvent,index;
	/* Default of no button event. */
	ButtonEvent=NO_BUTTONS;
	/* Get the latest button pattern, and check for it being noisy. */
	ButtonPattern=GetButtonPattern();
	if (ButtonPattern!=NOISY_BUTTONS) {
		/* Not a noisy button pattern and so see what button event has occurred. */
		switch (ButtonEventType(ButtonPattern)) {
		case BUTTON_UNCHANGED:
			if (ButtonPattern) {
				/*	Have at least 1 activated button whose pattern has not changed.
					Therefore need to see if a timed button event is required.
				*/
				index=FindTimedButtonEvent(ButtonEventList,ButtonPattern);
				if (index>=0) {
					ButtonEvent=index;
					/* Need to indicate an event having occurred. */
					PendingSwitchEvent=FALSE;
				}
			}
			break;
		case BUTTON_ACTIVATED:
			/*	Have at least 1 button which has activated.  Therefore need to see if
				this event is required.  If this button is not required in any pattern,
				then return with "illegal button activation" event.
			*/
			index=FindButtonEvent(ButtonEventList,ButtonPattern,TRUE);
			if (index>=0) {
				ButtonEvent=index;
				/* Need to indicate an event having occurred. */
				PendingSwitchEvent=FALSE;
			}
			else {
				/* Need to flag the need for an event for this button. */
				PendingSwitchEvent=TRUE;
				/* Need to see if this button pattern is required at all. */
				if (ButtonNotUsed(ButtonEventList,LastButtonPattern^ButtonPattern))
					ButtonEvent=ILLEGAL_BUTTON_ACTIVATION;
			}
			break;
		case BUTTON_DEACTIVATED:
			/*	Have at least 1 button which has deactivated.
				Therefore need to see if this event is required.
			*/
			index=FindButtonEvent(ButtonEventList,LastButtonPattern,FALSE);
			if (index>=0) {
				ButtonEvent=index;
				/* Need to indicate an event having occurred. */
				PendingSwitchEvent=FALSE;
			}
			break;
		}
	}
	/* Save button pattern history. */
	LastButtonPattern=ButtonPattern;
	/* Return with the button event. */
	return(ButtonEvent);
}


signed char FindForcedButtonEvent(const struct ButtonEventStruct *ButtonEventList,
		const struct ButtonEventStruct *ForcedButtonEvent);

/*	This routine checks to see if a button is pressed (either "forced" or "from the input"
	button).  The return status is:-
		>=0 ===> Have a valid button event, this being the corresponding
					index of ButtonEventList[].
		-1 ===> No button event (NO_BUTTONS).
		-2 ===> Illegal button activation event (ILLEGAL_BUTTON_ACTIVATION).
*/
signed char SinglePressBeep( const struct ButtonEventStruct *ButtonEventList) {
	signed char	Button;
	/* See if a forced button is pending (this being a non-NULL pointer). */
	if (ForcedButton) {
		/*	A forced button takes priority over a front panel button.
			Must have immediate response to a forced button.
		*/
		Button=FindForcedButtonEvent(ButtonEventList,ForcedButton);
		ForcedButton=NULL_POINTER;
		/* Return if there is a valid forced button event. */
		if (Button>=0) return(Button);
	}
	/*	There is no forced button event and so see if there is a normal
		button event.
	*/
	/* See if the button presses are locked out. */
//	if ( BeepTimer ) return(NO_BUTTONS);
	/* See if a controller button event has occurred. */
	Button = GetButtonEvent(ButtonEventList);
	if (Button!=NO_BUTTONS) {
		/*	A button press has occurred, and so do normal
			beep, locking out the button presses during
			the beep.
		*/
		if (Button!=ILLEGAL_BUTTON_ACTIVATION) DoNormalBeep();
		else DoErrorBeep();
	}
	return(Button);
}

/*	This function responds to a button event as listed in "ButtonEvents[]" (using
	"SinglePressBeep()"), by calling the corresponding response function as listed
	in "function[]".  The return status is:-
	<0 ===> No button event.
	>=0 ===> Have responded to a button event, return value = event index of "ButtonEvents[]".
*/
signed char DoButtonFunction(const struct ButtonEventStruct *ButtonEvents, const unsigned int *function) {
//	short rtn;
    signed char	ButtonPress;
    /* See if there is a button event. */
    ButtonPress = SinglePressBeep(ButtonEvents);
    if (ButtonPress>=0) {
	   	/*	There is a button event, and so call the corresponding response function,
   			returning with the function's return value.
	   	*/
//		rtn = CallFunction(function,(unsigned char) ButtonPress);
		CallFunction(function,(unsigned char) ButtonPress);
	}
   	/* Return with which button being pressed, if any. */
    return(ButtonPress);
}

/***********************************************************************/
/*              High level Button control functions                    */
/***********************************************************************/
/*	This function searches "ButtonEventList[]" for the specified "ForcedButtonEvent".
	The return value is:-
			>=0 ===> Event was in list, the return value being the "ButtonEventList[]" index.
			-1 ===> Event was not in the list.
*/
signed char FindForcedButtonEvent(const struct ButtonEventStruct *ButtonEventList,
		const struct ButtonEventStruct *ForcedButtonEvent) {
	signed char index=0;
	/* Search the list for the event. */
	while (GetConstUINT(&(ButtonEventList->Buttons))!=0) {
		/* See if this is the event. */
		if ((GetConstUINT(&(ButtonEventList->Buttons))==GetConstUINT(&(ForcedButtonEvent->Buttons)))
				&&(GetConstUCHAR(&(ButtonEventList->Activate))==GetConstUCHAR(&(ForcedButtonEvent->Activate)))) {
			/*	Both the button pattern and ACTIVATE type matches.  If "ForcedButtonEvent"
				is a timed button event, then there is a match if "ButtonEventList[]"
				contains the same timed button event, even though the time period might
				be different.
			*/
			if (((GetConstUCHAR(&(ForcedButtonEvent->Seconds))==0)&&(GetConstUCHAR(&(ButtonEventList->Seconds))==0))
					||((GetConstUCHAR(&(ForcedButtonEvent->Seconds))!=0)&&(GetConstUCHAR(&(ButtonEventList->Seconds))!=0))) {
				/* Have found the event. */
				return(index);
			}
		}
		/* Keep searching. */
		index++;
		ButtonEventList++;
	}
	/* The given event was not found. */
	return(-1);
}
/*	Initialize all button control variables.  This clears all history
	for the button control.
*/
void InitButtons(void) {
//	BuzzerControl.BeepTimer=0;
	SwitchRaw[0]=SwitchRaw[1]=0;
//   	DisableBuzzer();
}
/*	This routine calls a function whose address is in the ROM-resident
	"FunctionTable" at "index".
	Special Note:	The called function can return "void", "BOOL",
						"unsigned char", "char", "unsigned short", or "short".
*/
short CallFunction(const unsigned int *FunctionTable, unsigned char index) {
	/* Get the pointer to the indexed function. */
	short (*ptr) ();
	ptr=(short(*)()) GetConstWord((signed char*) (FunctionTable+index));
	/* Call the indexed function. */
	return((*ptr)());
}

/*	This routine calls a BOOL function whose address is in the ROM-resident
	"FunctionTable" at "index".
*/
BOOL Call_BOOL_Function(const unsigned int *FunctionTable, unsigned char index) {
	return(CallFunction(FunctionTable,index));
}


