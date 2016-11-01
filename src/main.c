#include "main.h"
#include "mango.h"
#include "stm32f0xx_hal.h"

static void Error_Handler(void) {
  while (1) {
  }
}

static void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType =
      RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

static void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LD4_Pin | LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOC, LD4_Pin | LD3_Pin, GPIO_PIN_RESET);
}

////////////////////////////////////////////////////////////////////////////////

uint8_t memory[128];

const uint8_t name[12] = {0x0b, 0x7a, 0xe8, 0xfb, 0xdd, 0xc9,
                          0x8b, 0x72, 0xf3, 0x22, 0x45, 0x96};

const uint8_t code[133] = {
    0xff, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x08, 0x00,
    0x01, 0x04, 0x02, 0x00, 0x01, 0x52, 0x13, 0x01, 0x1c, 0xff, 0x67, 0x00,
    0xbb, 0x20, 0x1c, 0xff, 0x6c, 0x00, 0x5b, 0xe8, 0x03, 0x00, 0x00, 0x1c,
    0xff, 0x80, 0x00, 0x1c, 0xff, 0x71, 0x00, 0x10, 0x00, 0x52, 0x20, 0x13,
    0x01, 0x10, 0x00, 0x54, 0x89, 0xbd, 0x03, 0x51, 0x13, 0x01, 0x10, 0x00,
    0x53, 0x89, 0xbd, 0x0c, 0x1c, 0xff, 0x76, 0x00, 0x5a, 0x64, 0x1c, 0xff,
    0x80, 0x00, 0xb9, 0xc8, 0x10, 0x00, 0x52, 0x89, 0xbd, 0x0f, 0x1c, 0xff,
    0x76, 0x00, 0x5b, 0xc8, 0x00, 0x00, 0x00, 0x1c, 0xff, 0x80, 0x00, 0xb9,
    0xb3, 0x1c, 0xff, 0x7b, 0x00, 0xb9, 0xad, 0x02, 0x00, 0x01, 0x63, 0x00,
    0x02, 0x00, 0x00, 0x64, 0x00, 0x02, 0x00, 0x00, 0x65, 0x00, 0x02, 0x00,
    0x00, 0x66, 0x00, 0x02, 0x00, 0x00, 0x67, 0x00, 0x02, 0x01, 0x00, 0x68,
    0x00};

int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  mango_vm *vm = mango_initialize(memory, sizeof(memory), NULL);
  if (!vm) {
    return 0;
  }

  if (mango_module_import(vm, name, code, sizeof(code), NULL,
                          MANGO_IMPORT_TRUSTED_MODULE |
                              MANGO_IMPORT_SKIP_VERIFICATION)) {
    return 0;
  }

  while (1) {
    switch (mango_execute(vm)) {
    default:
      return 0;
    case MANGO_E_SUCCESS:
      return 0;
    case MANGO_E_SYSCALL:
      switch (mango_syscall_function(vm)) {
      case 99:
        mango_write_i32(mango_stack_alloc(vm, 4, 0), 0,
                        HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET);
        break;
      case 100:
        HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
        break;
      case 101:
        HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
        break;
      case 102:
        HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
        break;
      case 103:
        HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
        break;
      case 104:
        HAL_Delay(mango_read_i32(mango_stack_top(vm), 0));
        mango_stack_free(vm, 4);
        break;
      }
      break;
    }
  }
}
