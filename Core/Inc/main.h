/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RF_CS_Pin GPIO_PIN_2
#define RF_CS_GPIO_Port GPIOE
#define RF_RESET_Pin GPIO_PIN_3
#define RF_RESET_GPIO_Port GPIOE
#define EM_ZX_Pin GPIO_PIN_4
#define EM_ZX_GPIO_Port GPIOE
#define RF_ENA_Pin GPIO_PIN_5
#define RF_ENA_GPIO_Port GPIOE
#define Buzzer_Pin GPIO_PIN_6
#define Buzzer_GPIO_Port GPIOE
#define RF_PRESENCE_Pin GPIO_PIN_13
#define RF_PRESENCE_GPIO_Port GPIOC
#define NC_Res_pulldown_Pin GPIO_PIN_14
#define NC_Res_pulldown_GPIO_Port GPIOC
#define NC_Res_pulldownC15_Pin GPIO_PIN_15
#define NC_Res_pulldownC15_GPIO_Port GPIOC
#define FB_4V4_Pin GPIO_PIN_0
#define FB_4V4_GPIO_Port GPIOC
#define TEMP_SENSOR_Pin GPIO_PIN_1
#define TEMP_SENSOR_GPIO_Port GPIOC
#define FB_CR2032_Pin GPIO_PIN_2
#define FB_CR2032_GPIO_Port GPIOC
#define FB_VDD_Pin GPIO_PIN_3
#define FB_VDD_GPIO_Port GPIOC
#define PCF_INT_Pin GPIO_PIN_0
#define PCF_INT_GPIO_Port GPIOA
#define W25QXX_CS_Pin GPIO_PIN_1
#define W25QXX_CS_GPIO_Port GPIOA
#define DEBUG_TX_Pin GPIO_PIN_2
#define DEBUG_TX_GPIO_Port GPIOA
#define DEBUG_RX_Pin GPIO_PIN_3
#define DEBUG_RX_GPIO_Port GPIOA
#define W25QXX_RESET_Pin GPIO_PIN_4
#define W25QXX_RESET_GPIO_Port GPIOA
#define EM_CS_Pin GPIO_PIN_4
#define EM_CS_GPIO_Port GPIOC
#define FB_VBAT_Pin GPIO_PIN_5
#define FB_VBAT_GPIO_Port GPIOC
#define RES_0_Pin GPIO_PIN_0
#define RES_0_GPIO_Port GPIOB
#define RES_1_Pin GPIO_PIN_1
#define RES_1_GPIO_Port GPIOB
#define RES_2_Pin GPIO_PIN_2
#define RES_2_GPIO_Port GPIOB
#define RF_RX_Pin GPIO_PIN_7
#define RF_RX_GPIO_Port GPIOE
#define RF_TX_Pin GPIO_PIN_8
#define RF_TX_GPIO_Port GPIOE
#define INPUT_3_Pin GPIO_PIN_9
#define INPUT_3_GPIO_Port GPIOE
#define INPUT_2_Pin GPIO_PIN_10
#define INPUT_2_GPIO_Port GPIOE
#define INPUT_1_Pin GPIO_PIN_11
#define INPUT_1_GPIO_Port GPIOE
#define RF_SCK_Pin GPIO_PIN_12
#define RF_SCK_GPIO_Port GPIOE
#define RF_MISO_Pin GPIO_PIN_13
#define RF_MISO_GPIO_Port GPIOE
#define RF_MOSI_Pin GPIO_PIN_14
#define RF_MOSI_GPIO_Port GPIOE
#define NC_Res_pulldownE15_Pin GPIO_PIN_15
#define NC_Res_pulldownE15_GPIO_Port GPIOE
#define RS485_RX_Pin GPIO_PIN_12
#define RS485_RX_GPIO_Port GPIOB
#define RS485_TX_Pin GPIO_PIN_13
#define RS485_TX_GPIO_Port GPIOB
#define RS485_DIR_Pin GPIO_PIN_14
#define RS485_DIR_GPIO_Port GPIOB
#define GSM_ON_OFF_Pin GPIO_PIN_15
#define GSM_ON_OFF_GPIO_Port GPIOB
#define SIM_RSET_Pin GPIO_PIN_8
#define SIM_RSET_GPIO_Port GPIOD
#define LED_STATUS_LEFT_Pin GPIO_PIN_9
#define LED_STATUS_LEFT_GPIO_Port GPIOD
#define GSM_RI_Pin GPIO_PIN_10
#define GSM_RI_GPIO_Port GPIOD
#define SIM_STATUS_Pin GPIO_PIN_11
#define SIM_STATUS_GPIO_Port GPIOD
#define GSM_PRESENCE_Pin GPIO_PIN_12
#define GSM_PRESENCE_GPIO_Port GPIOD
#define NC_Res_pulldownD13_Pin GPIO_PIN_13
#define NC_Res_pulldownD13_GPIO_Port GPIOD
#define GSM_RX_Pin GPIO_PIN_14
#define GSM_RX_GPIO_Port GPIOD
#define GSM_TX_Pin GPIO_PIN_15
#define GSM_TX_GPIO_Port GPIOD
#define RS232_TX_Pin GPIO_PIN_6
#define RS232_TX_GPIO_Port GPIOC
#define RS232_RX_Pin GPIO_PIN_7
#define RS232_RX_GPIO_Port GPIOC
#define LED_STATUS_RIGHT_Pin GPIO_PIN_8
#define LED_STATUS_RIGHT_GPIO_Port GPIOC
#define BTN_ESC_Pin GPIO_PIN_9
#define BTN_ESC_GPIO_Port GPIOC
#define BTN_LEFT_Pin GPIO_PIN_8
#define BTN_LEFT_GPIO_Port GPIOA
#define BTN_UP_Pin GPIO_PIN_9
#define BTN_UP_GPIO_Port GPIOA
#define BTN_DOWN_Pin GPIO_PIN_10
#define BTN_DOWN_GPIO_Port GPIOA
#define BTN_RIGHT_Pin GPIO_PIN_11
#define BTN_RIGHT_GPIO_Port GPIOA
#define BTN_ENTER_Pin GPIO_PIN_12
#define BTN_ENTER_GPIO_Port GPIOA
#define GSM_EN_Pin GPIO_PIN_15
#define GSM_EN_GPIO_Port GPIOA
#define PSU_IO_2_Pin GPIO_PIN_10
#define PSU_IO_2_GPIO_Port GPIOC
#define PSU_IO_1_Pin GPIO_PIN_11
#define PSU_IO_1_GPIO_Port GPIOC
#define BAT_PGOOD_Pin GPIO_PIN_12
#define BAT_PGOOD_GPIO_Port GPIOC
#define PSU_CS_Pin GPIO_PIN_0
#define PSU_CS_GPIO_Port GPIOD
#define RELAY_3_Pin GPIO_PIN_1
#define RELAY_3_GPIO_Port GPIOD
#define RELAY_2_Pin GPIO_PIN_2
#define RELAY_2_GPIO_Port GPIOD
#define RELAY_1_Pin GPIO_PIN_3
#define RELAY_1_GPIO_Port GPIOD
#define PSU_RESET_Pin GPIO_PIN_4
#define PSU_RESET_GPIO_Port GPIOD
#define LCD_BL_Pin GPIO_PIN_5
#define LCD_BL_GPIO_Port GPIOD
#define LCD_CS_Pin GPIO_PIN_6
#define LCD_CS_GPIO_Port GPIOD
#define LCD_A0_Pin GPIO_PIN_7
#define LCD_A0_GPIO_Port GPIOD
#define LCD_RST_Pin GPIO_PIN_3
#define LCD_RST_GPIO_Port GPIOB
#define LCD_CLK_Pin GPIO_PIN_4
#define LCD_CLK_GPIO_Port GPIOB
#define LCD_SDA_Pin GPIO_PIN_5
#define LCD_SDA_GPIO_Port GPIOB
#define EM_RST_Pin GPIO_PIN_8
#define EM_RST_GPIO_Port GPIOB
#define EM_RX_Pin GPIO_PIN_0
#define EM_RX_GPIO_Port GPIOE
#define EM_TX_Pin GPIO_PIN_1
#define EM_TX_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
