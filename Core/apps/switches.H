/************************************************************************************
*                                                                                   *
*   File Name   : switches.h                                                         *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/

#ifndef switches_h
	#define switches_h
	
#define ButtonsPortA GPIOA->IDR
#define ButtonsPortC GPIOC->IDR

#define ESC		BIT9  	/* switch location. PC9*/
#define ENTER	BIT12  	/* switch location. PA12*/
#define LEFT	BIT8  	/* switch location. PA8*/
#define RIGHT	BIT11  	/* switch location. port A11*/
#define DOWN	BIT10  	/* switch location. PA10*/
#define UP		BIT9  	/* switch location. PA9*/

/*	Lookup table for translating from bit-number to
	equivalent SET-bit pattern.
*/
extern const unsigned short	IndexToMaskTable[];
/* Used to track the number of presses of a specified key, for
	the security access process.
*/
extern unsigned char MultiPressCount;
/* Define the bit-representation for each button. */

#define ENTER_BUTTON	(unsigned short)BIT0
#define RIGHT_BUTTON	BIT1
#define LEFT_BUTTON		BIT2
#define UP_BUTTON		BIT3
#define DOWN_BUTTON		BIT4
#define ESC_BUTTON		BIT5
#define SECURITY_BUTTON	(LEFT_BUTTON|RIGHT_BUTTON)

#define MAJOR_BUTTON_MASK		0x3FFF	/* the mask for all valid switch bits */
#define MAX_SWITCH_INDEX		12		/* the maximum allowable push switch index */
#define MISSING_BUTTON			BIT14		/* reserved */
#define NOISY_BUTTONS			BIT15		/* reserved */
#define NO_BUTTON				0



/* This variable is used to software-force (emulate) a button event. */
extern const struct ButtonEventStruct	*ForcedButton;
extern unsigned char ButtonPressedTimer;		/* 100mS resolution. */
extern unsigned char buttonTimer;		/* 1s resolution. */


/* The raw data from the switch matrix. */
extern unsigned short	SwitchRaw[2];
/* Need to define the structure for specifying a required button event:-
		- List of all buttons (can be more than 1).
		- Event type (ACTIVATE or DEACTIVATE).
		- Button-pressed period in seconds (0 ===> Not applicable).
*/
struct ButtonEventStruct {
	unsigned short	Buttons;
	BOOL			Activate;
	unsigned char	Seconds;
};
/* Define the basic button event types. */
#define BUTTON_UNCHANGED	0
#define BUTTON_ACTIVATED	1
#define BUTTON_DEACTIVATED	2

/* Some return statuses of "GetButtonEvent()". */
#define NO_BUTTONS					-1
#define ILLEGAL_BUTTON_ACTIVATION	-2
/* Define the return status of the security-access function. */
#define SECURE_BUSY		0
#define SECURE_TIMEOUT	1
#define SECURE_PASSED	2
#define SECURE_FAILED	3

/***********************************************************************/
/* Declare all global functions. */
/*	This function returns the button pressed status, if Pressed the value is 0
 and the return value is TRUE.
*/
BOOL GetButtonStatusPressed(unsigned short ButtonIndex, unsigned long Port);
unsigned short IndexToMask(signed short index);
void InitButtons(void);
signed char SinglePressBeep( const struct ButtonEventStruct *ButtonEventList);


signed char DoButtonFunction( const struct ButtonEventStruct *ButtonEvents, const unsigned int *function);
short CallFunction(const unsigned int *function, unsigned char index);
BOOL Call_BOOL_Function(const unsigned int *FunctionTable, unsigned char index);
void UpdateSwitchRaw(unsigned short *dest, unsigned char Activated, unsigned short index);
void UpdateAllSwitches(void);
#endif  /*end of switches_h*/

