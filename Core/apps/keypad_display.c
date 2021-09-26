/************************************************************************************
*                                                                                   *
*   File Name   : keypad_display.c                                                  *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/

/* Include all other required application header files. */
#include "resource.h"
#define MAX_MENU_ITEMS	3
#define MAX_OUTPUT_CONTROL_ITEMS	5
#define MAX_LEFT_RIGHT_ON_OFF	2
unsigned char upDownIdx;
unsigned char leftRightIdx;

//*****************************************************************************************//

//Define up/down and ESC/OK buttons used
const struct ButtonEventStruct UpDownEscOKButtons[]={
		{ESC_BUTTON,TRUE,0},{ENTER_BUTTON,TRUE,0},
		{UP_BUTTON,TRUE,0},{DOWN_BUTTON,TRUE,0},
		{0,FALSE,0}};
//Define enter activate button used
const struct ButtonEventStruct EnterButtonAct[]={
	{ENTER_BUTTON,TRUE,0},{0,FALSE,0}};

//Define esc activate button used
const struct ButtonEventStruct EscButtonAct[]={
	{ESC_BUTTON,TRUE,0},{0,FALSE,0}};

//Define esc de-activate button used
const struct ButtonEventStruct EscButtonDeact[]={
	{ESC_BUTTON,FALSE,0},{0,FALSE,0}};

/*********************************************************************************************/
//Define all the buttons used
const struct ButtonEventStruct AllButtons[]={
	{ESC_BUTTON,TRUE,0},{ENTER_BUTTON,TRUE,0},
	{RIGHT_BUTTON,TRUE,0},{LEFT_BUTTON,TRUE,0},
	{UP_BUTTON,TRUE,0},{DOWN_BUTTON,TRUE,0},
	{0,FALSE,0}};

/***************************MAIN SCREEN******************************************************/
void MainScreenEnter(void){
	//go to other screen
	lcdStateMachine = LCD_MENU_SCREEN_STATE;
    /*Set up the application timer.*/
    lcdSecTimer = 5;//5secs
}
const unsigned int MainScreenFunctionTable[] = {
		(unsigned int)MainScreenEnter
};
/*****************************OUTPUT CONTROL**************************************************/

void OutputControlScreenEsc(void){
	//go back to menu screen
	lcdStateMachine = LCD_MENU_SCREEN_STATE;
}

void OutputControlScreenEnter(void){
	// implement ...???
}
void OutputControlScreenRight(void){
	leftRightIdx++;
	if (leftRightIdx >= MAX_LEFT_RIGHT_ON_OFF) leftRightIdx = 0;
}
void OutputControlScreenLeft(void){
	if (leftRightIdx == 0) leftRightIdx = MAX_LEFT_RIGHT_ON_OFF;
	leftRightIdx--;
}
void OutputControlScreenUp(void){
	if (upDownIdx == 0) upDownIdx = MAX_OUTPUT_CONTROL_ITEMS;
	upDownIdx--;
}
void OutputControlScreenDown(void){
	upDownIdx++;
	if (upDownIdx >= MAX_OUTPUT_CONTROL_ITEMS) upDownIdx = 0;
}
/*  Define all functions co-respond to activating button presses.
   The index of this array must be matching to the index of
   const struct ButtonEventStruct AllButtons[]
*/
const unsigned int OutputControlScreenFunctionTable[] = {
		(unsigned int)OutputControlScreenEsc,(unsigned int)OutputControlScreenEnter,
		(unsigned int)OutputControlScreenRight,(unsigned int)OutputControlScreenLeft,
        (unsigned int)OutputControlScreenUp,(unsigned int)OutputControlScreenDown
};

void OutputControlScreenState(void) {
    const struct ButtonEventStruct *ButtonEventPtr;
    const unsigned int	*FunctionPtr;
    /*Define Button Pressed Index based on the function table*/
    signed char Button_Pressed_Index;
	ButtonEventPtr = AllButtons;
	FunctionPtr = OutputControlScreenFunctionTable;
	/* Need to respond to any pushbutton presses. */
	Button_Pressed_Index = DoButtonFunction(ButtonEventPtr,FunctionPtr);
	if (Button_Pressed_Index <0 );//error ???
	/*Add more code here if required*/
//	if (operateMode == MANUAL){
//		;//update output straight away...
//	}

}/*end of OutputControlScreenState*/
/***********************************MENU***************************************************/
void MenuScreenEsc(void){
	//go to other screen
	lcdStateMachine = LCD_MAIN_SCREEN_STATE;
}
void MenuScreenEnter(void){
	//go to other screen
	if (upDownIdx == 0) lcdStateMachine = LCD_OUTPUT_CONTROL_SCREEN_STATE;
	else if (upDownIdx == 1) lcdStateMachine = LCD_SETTING_SCREEN_STATE;
	else if (upDownIdx == 2) lcdStateMachine = LCD_ABOUT_SCREEN_STATE;
}
void MenuScreenUp(void){
	if (upDownIdx == 0) upDownIdx = MAX_MENU_ITEMS;
	upDownIdx--;
}
void MenuScreenDown(void){
	upDownIdx++;
	if (upDownIdx >= MAX_MENU_ITEMS) upDownIdx = 0;
}
const unsigned int MenuFunctionTable[] = {
		(unsigned int)MenuScreenEsc,(unsigned int)MenuScreenEnter,
        (unsigned int)MenuScreenUp,(unsigned int)MenuScreenDown
};

/*********************************************************************************************/
void AboutScreenEsc(void) {
	lcdStateMachine = LCD_MAIN_SCREEN_STATE;
}
const unsigned int AboutFunctionTable[] = {
		(unsigned int)AboutScreenEsc
};
/*******************************MAIN STATE MACHINE******************************************************/
unsigned char lcdStateMachine;
unsigned char lcdSecTimer;

void doDisplay(void) {
     /*State machine for LCd application*/
    switch (lcdStateMachine) {
    case LCD_INIT_SCREEN_STATE:
    	if (lcdSecTimer == 0) lcdStateMachine = LCD_MAIN_SCREEN_STATE;
        break;
    case LCD_MAIN_SCREEN_STATE:
    	ESlowFlashLED(&RawLEDdata, LED_STATUS_RIGHT);
    	DoButtonFunction(EnterButtonAct, MainScreenFunctionTable);
        break;
    case LCD_MENU_SCREEN_STATE:
    	FastFlashLED(&RawLEDdata, LED_STATUS_RIGHT);
    	if (lcdSecTimer == 0) lcdStateMachine = LCD_MAIN_SCREEN_STATE;
    	DoButtonFunction(UpDownEscOKButtons, MenuFunctionTable);
        break;

    case LCD_OUTPUT_CONTROL_SCREEN_STATE:
    	FlashLED(&RawLEDdata, LED_STATUS_RIGHT);
    	OutputControlScreenState();
        break;
    case LCD_ABOUT_SCREEN_STATE:
    	TurnLEDoff(&RawLEDdata, LED_STATUS_RIGHT);
    	DoButtonFunction(EscButtonDeact, AboutFunctionTable);
        break;
    default: //LCD_DEFAULT_STATE
        //
        if (lcdSecTimer == 0) {
        	TurnLEDon(&RawLEDdata, LED_STATUS_RIGHT);
//        	GLCD_Initial();
//        	GlcdStartingPage(LcdTheme);
        	lcdStateMachine = LCD_INIT_SCREEN_STATE;
            /*Set up the application timer.*/
            lcdSecTimer = 3;
        }
        break;
    }
}

