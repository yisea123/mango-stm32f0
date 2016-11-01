#pragma once

#define HSE_VALUE ((uint32_t)8000000)
#define HSE_STARTUP_TIMEOUT ((uint32_t)100)
#define HSI_VALUE ((uint32_t)8000000)
#define HSI_STARTUP_TIMEOUT ((uint32_t)5000)
#define HSI14_VALUE ((uint32_t)14000000)
#define HSI48_VALUE ((uint32_t)48000000)
#define LSI_VALUE ((uint32_t)40000)
#define LSE_VALUE ((uint32_t)32768)
#define LSE_STARTUP_TIMEOUT ((uint32_t)5000)
#define VDD_VALUE ((uint32_t)3300)
#define TICK_INT_PRIORITY ((uint32_t)0)
#define USE_RTOS 0
#define PREFETCH_ENABLE 1
#define INSTRUCTION_CACHE_ENABLE 0
#define DATA_CACHE_ENABLE 0

#ifdef HAL_RCC_MODULE_ENABLED
#include "stm32f0xx_hal_rcc.h"
#endif

#ifdef HAL_GPIO_MODULE_ENABLED
#include "stm32f0xx_hal_gpio.h"
#endif

#ifdef HAL_DMA_MODULE_ENABLED
#include "stm32f0xx_hal_dma.h"
#endif

#ifdef HAL_CORTEX_MODULE_ENABLED
#include "stm32f0xx_hal_cortex.h"
#endif

#ifdef HAL_ADC_MODULE_ENABLED
#include "stm32f0xx_hal_adc.h"
#endif

#ifdef HAL_CAN_MODULE_ENABLED
#include "stm32f0xx_hal_can.h"
#endif

#ifdef HAL_CEC_MODULE_ENABLED
#include "stm32f0xx_hal_cec.h"
#endif

#ifdef HAL_COMP_MODULE_ENABLED
#include "stm32f0xx_hal_comp.h"
#endif

#ifdef HAL_CRC_MODULE_ENABLED
#include "stm32f0xx_hal_crc.h"
#endif

#ifdef HAL_DAC_MODULE_ENABLED
#include "stm32f0xx_hal_dac.h"
#endif

#ifdef HAL_FLASH_MODULE_ENABLED
#include "stm32f0xx_hal_flash.h"
#endif

#ifdef HAL_I2C_MODULE_ENABLED
#include "stm32f0xx_hal_i2c.h"
#endif

#ifdef HAL_I2S_MODULE_ENABLED
#include "stm32f0xx_hal_i2s.h"
#endif

#ifdef HAL_IRDA_MODULE_ENABLED
#include "stm32f0xx_hal_irda.h"
#endif

#ifdef HAL_IWDG_MODULE_ENABLED
#include "stm32f0xx_hal_iwdg.h"
#endif

#ifdef HAL_PCD_MODULE_ENABLED
#include "stm32f0xx_hal_pcd.h"
#endif

#ifdef HAL_PWR_MODULE_ENABLED
#include "stm32f0xx_hal_pwr.h"
#endif

#ifdef HAL_RTC_MODULE_ENABLED
#include "stm32f0xx_hal_rtc.h"
#endif

#ifdef HAL_SMARTCARD_MODULE_ENABLED
#include "stm32f0xx_hal_smartcard.h"
#endif

#ifdef HAL_SMBUS_MODULE_ENABLED
#include "stm32f0xx_hal_smbus.h"
#endif

#ifdef HAL_SPI_MODULE_ENABLED
#include "stm32f0xx_hal_spi.h"
#endif

#ifdef HAL_TIM_MODULE_ENABLED
#include "stm32f0xx_hal_tim.h"
#endif

#ifdef HAL_TSC_MODULE_ENABLED
#include "stm32f0xx_hal_tsc.h"
#endif

#ifdef HAL_UART_MODULE_ENABLED
#include "stm32f0xx_hal_uart.h"
#endif

#ifdef HAL_USART_MODULE_ENABLED
#include "stm32f0xx_hal_usart.h"
#endif

#ifdef HAL_WWDG_MODULE_ENABLED
#include "stm32f0xx_hal_wwdg.h"
#endif

#define assert_param(expr) ((void)0)
