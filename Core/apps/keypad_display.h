/************************************************************************************
*                                                                                   *
*   File Name   : keypad_display.h                                                  *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/


#ifndef keypad_display_h
	#define keypad_display_h

/*define all operation state in the the state machine for  application.*/
#define LCD_DEFAULT_STATE   	0
#define LCD_INIT_SCREEN_STATE   1
#define LCD_MAIN_SCREEN_STATE   2
#define LCD_MENU_SCREEN_STATE   3
#define LCD_LOGIN_SCREEN_STATE  4
#define LCD_OUTPUT_CONTROL_SCREEN_STATE 	5
#define LCD_SETTING_SCREEN_STATE  			6
#define LCD_GENRAL_SCREEN_STATE  			7
#define LCD_FIRMWARE_UPDATE_SCREEN_STATE  	8
#define LCD_EDITING_SCREEN_STATE  			9
#define LCD_ADD_SCREEN_STATE  				10
#define LCD_CELLUAR_SCREEN_STATE  			11
#define LCD_CELLUAR_DATA_SCREEN_STATE  		12
#define LCD_PASSCODE_SCREEN_STATE  			13
#define LCD_NEMA_SCREEN_STATE  				14
#define LCD_DIMABLE_SCREEN_STATE  			15
#define LCD_INPUT_SETUP_SCREEN_STATE  		16
#define LCD_OUTPUT_SETUP_SCREEN_STATE  		17
#define LCD_ABOUT_SCREEN_STATE  			18


extern unsigned char lcdStateMachine;
extern unsigned char lcdSecTimer;

void doDisplay(void);

#endif/*end of keypad_display_h*/

