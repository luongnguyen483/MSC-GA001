/************************************************************************************
*                                                                                   *
*   File Name   : appMain.c                                                         *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/

/* Include all other required application header files. */
#include "resource.h"
//*****************************************************************************************//
unsigned char appStateMachine;
unsigned char appSecTimer;

//Main application
void doApplication(void) {
     /*State machine for main application*/
    switch (appStateMachine) {
    case GSM_INIT_STATE://Initialize the application parameters
        appStateMachine = APP_RUNNING_STATE;
        break;        
    case LCD_INIT_STATE://Initialize
        if (appSecTimer == 0){
            /*Go to the next state*/
            appStateMachine = APP_INIT_STATE;
            appSecTimer = 1;
        }
        break;
    case APP_RUNNING_STATE:
        if (appSecTimer == 0){
        	appSecTimer = 10;//10secs
        }
        break;
    default: //APP_DEFAULT_STATE Application start here.
        //Check to see if the time out for not connecting too
        if (appSecTimer == 0) {
            appStateMachine = GSM_INIT_STATE;
            /*Set up the application timer.*/
            appSecTimer = 3;
        }
        break;
    }
}

