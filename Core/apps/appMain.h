/************************************************************************************
*                                                                                   *
*   File Name   : appMain.h                                                         *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/


#ifndef appMain_h
	#define appMain_h

/*define all operation state in the the state machine for  application.*/
#define APP_DEFAULT_STATE   0
#define GSM_INIT_STATE    1
#define LCD_INIT_STATE    2
#define APP_INIT_STATE   3
#define APP_RUNNING_STATE   4
extern unsigned char appSecTimer;

#endif/*end of appMain_h*/

