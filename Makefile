ARMGNU = tools/gcc-arm-none-eabi-5_4-2016q3/bin/arm-none-eabi

STM32Cube = lib/STM32Cube_FW_F0_V1.6.0

CPU = -mthumb -mcpu=cortex-m0 -mfloat-abi=soft

SPECS = nano.specs
#SPECS = rdimon.specs

DEFINES += MANGO_NO_I64
DEFINES += MANGO_NO_F32
DEFINES += MANGO_NO_F64
#DEFINES += MANGO_NO_REFS
DEFINES += MANGO_NO_VERIFICATION

DEFINES += STM32F0xx
DEFINES += STM32F051x8
DEFINES += USE_HAL_DRIVER

DEFINES += HAL_MODULE_ENABLED
#DEFINES += HAL_ADC_MODULE_ENABLED
#DEFINES += HAL_CAN_MODULE_ENABLED
#DEFINES += HAL_CEC_MODULE_ENABLED
#DEFINES += HAL_COMP_MODULE_ENABLED
DEFINES += HAL_CORTEX_MODULE_ENABLED
#DEFINES += HAL_CRC_MODULE_ENABLED
#DEFINES += HAL_CRYP_MODULE_ENABLED
#DEFINES += HAL_DAC_MODULE_ENABLED
#DEFINES += HAL_DMA_MODULE_ENABLED
DEFINES += HAL_FLASH_MODULE_ENABLED
DEFINES += HAL_GPIO_MODULE_ENABLED
#DEFINES += HAL_I2C_MODULE_ENABLED
#DEFINES += HAL_I2S_MODULE_ENABLED
#DEFINES += HAL_IRDA_MODULE_ENABLED
#DEFINES += HAL_IWDG_MODULE_ENABLED
#DEFINES += HAL_LCD_MODULE_ENABLED
#DEFINES += HAL_LPTIM_MODULE_ENABLED
#DEFINES += HAL_PCD_MODULE_ENABLED
#DEFINES += HAL_PWR_MODULE_ENABLED
DEFINES += HAL_RCC_MODULE_ENABLED
#DEFINES += HAL_RNG_MODULE_ENABLED
#DEFINES += HAL_RTC_MODULE_ENABLED
#DEFINES += HAL_SMARTCARD_MODULE_ENABLED
#DEFINES += HAL_SMBUS_MODULE_ENABLED
#DEFINES += HAL_SPI_MODULE_ENABLED
#DEFINES += HAL_TIM_MODULE_ENABLED
#DEFINES += HAL_TSC_MODULE_ENABLED
#DEFINES += HAL_UART_MODULE_ENABLED
#DEFINES += HAL_USART_MODULE_ENABLED
#DEFINES += HAL_WWDG_MODULE_ENABLED

INCLUDES += src

INCLUDES += lib/mango/src

INCLUDES += $(STM32Cube)/Drivers/STM32F0xx_HAL_Driver/Inc
INCLUDES += $(STM32Cube)/Drivers/CMSIS/Include
INCLUDES += $(STM32Cube)/Drivers/CMSIS/Device/ST/STM32F0xx/Include

SOURCES += src/main.c
SOURCES += src/stm32f0xx_hal_msp.c
SOURCES += src/stm32f0xx_it.c

SOURCES += lib/mango/src/mango.c

SOURCES += $(STM32Cube)/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.c
SOURCES += $(STM32Cube)/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.c
SOURCES += $(STM32Cube)/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.c
SOURCES += $(STM32Cube)/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.c
SOURCES += $(STM32Cube)/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.c
SOURCES += $(STM32Cube)/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.c
SOURCES += $(STM32Cube)/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.c
SOURCES += $(STM32Cube)/Drivers/CMSIS/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.c
SOURCES += $(STM32Cube)/Drivers/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f051x8.s

LDSCRIPT = STM32F051R8_FLASH.ld

#-------------------------------------------------------------------------------

OBJ_FILES = $(addprefix obj/,$(addsuffix .o,$(basename $(SOURCES))))

CFLAGS = $(CPU) --specs=$(SPECS) \
	-Wall -Wextra -Wno-unused-parameter -Werror \
	-std=c11 -O3 -fvisibility=hidden \
	-Wl,--gc-sections,--error-unresolved-symbols,--fatal-warnings \
	-fdata-sections -ffunction-sections \
	"-D__weak=__attribute__((weak))" \
	"-D__packed=__attribute__((__packed__))" \
	$(addprefix -I,$(INCLUDES)) \
	$(addprefix -D,$(DEFINES))

AFLAGS = $(CPU) --warn --fatal-warnings

all: bin/program.bin

bin/program.bin: bin/program.elf
	@mkdir -p $(dir $@)
	@$(ARMGNU)-objcopy -O binary $< $@

bin/program.list: bin/program.elf 
	@mkdir -p $(dir $@)
	@$(ARMGNU)-objdump -D $< > $@

bin/program.elf: $(OBJ_FILES)
	@mkdir -p $(dir $@)
	@$(ARMGNU)-gcc $(CFLAGS) -T$(LDSCRIPT) -o $@ $^
	@$(ARMGNU)-size $@

obj/%.o: %.c
	@mkdir -p $(dir $@)
	@$(ARMGNU)-gcc $(CFLAGS) -o $@ -c $<

obj/%.o: %.s
	@mkdir -p $(dir $@)
	@$(ARMGNU)-as $(AFLAGS) -o $@ $<

clean:
	@rm -rf obj bin

.PHONY: all clean
