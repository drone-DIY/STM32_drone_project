#ifndef BOARD_H
#define BOARD_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_tim.h"

/* Matek F405-miniTE board map. Phase A Betaflight resource show all is the
 * primary source for active pin, timer and DMA assignments. The ICD and
 * ArduPilot hwdef supply inactive or planned connections noted below.
 * Peripheral modes are configured in the CubeMX .ioc file; including this
 * header does not initialize hardware or verify this firmware on the board.
 *
 * Sources:
 * https://docs.nova-maker.com/doc/phase-a-diff-all-resource-show-all-ikRSV5S58Y
 * https://docs.nova-maker.com/doc/icd-F5XYnlQ4VH (ICD v2.2, section 2)
 * https://github.com/ArduPilot/ardupilot/blob/master/libraries/AP_HAL_ChibiOS/hwdef/MatekF405-TE/hwdef.dat
 * https://www.mateksys.com/?portfolio=f405-minite
 * Verification record: docs/03-design/BOARD_PIN_VERIFICATION.md
 */

#define BOARD_HSE_HZ                  8000000U
#define BOARD_VBAT_DIVIDER            21.0f

/* PA13/PA14 are shared with the green/blue LEDs. Keep SWD enabled while
 * debugging; do not configure either pin as an LED GPIO in CubeMX. */
#define BOARD_SWDIO_GPIO_PORT         GPIOA
#define BOARD_SWDIO_PIN               GPIO_PIN_13
#define BOARD_SWCLK_GPIO_PORT         GPIOA
#define BOARD_SWCLK_PIN               GPIO_PIN_14

/* ESC connector S1-S4. Motor positions and rotation directions are separate
 * mixer decisions. S3 uses TIM1's complementary channel (CH3N). */
#define BOARD_S1_GPIO_PORT            GPIOC
#define BOARD_S1_PIN                  GPIO_PIN_9
#define BOARD_S1_TIMER                TIM8
#define BOARD_S1_TIMER_CHANNEL        TIM_CHANNEL_4
#define BOARD_S1_COMPLEMENTARY        0U

#define BOARD_S2_GPIO_PORT            GPIOC
#define BOARD_S2_PIN                  GPIO_PIN_8
#define BOARD_S2_TIMER                TIM8
#define BOARD_S2_TIMER_CHANNEL        TIM_CHANNEL_3
#define BOARD_S2_COMPLEMENTARY        0U

#define BOARD_S3_GPIO_PORT            GPIOB
#define BOARD_S3_PIN                  GPIO_PIN_15
#define BOARD_S3_TIMER                TIM1
#define BOARD_S3_TIMER_CHANNEL        TIM_CHANNEL_3
#define BOARD_S3_COMPLEMENTARY        1U

#define BOARD_S4_GPIO_PORT            GPIOA
#define BOARD_S4_PIN                  GPIO_PIN_8
#define BOARD_S4_TIMER                TIM1
#define BOARD_S4_TIMER_CHANNEL        TIM_CHANNEL_1
#define BOARD_S4_COMPLEMENTARY        0U

/* Betaflight's per-output DMA allocation, not a fixed electrical property.
 * Recheck it when selecting the HAL DShot transfer mode in CubeMX. */
#define BOARD_S1_DMA_STREAM           DMA2_Stream7
#define BOARD_S2_DMA_STREAM           DMA2_Stream2
#define BOARD_S3_DMA_STREAM           DMA2_Stream6
#define BOARD_S4_DMA_STREAM           DMA2_Stream1

/* USART2 is active in the Phase A resource map. Betaflight assigned no UART2
 * DMA stream; choose and verify one before using DMA reception here. */
#define BOARD_CRSF_UART               USART2
#define BOARD_CRSF_TX_GPIO_PORT       GPIOA
#define BOARD_CRSF_TX_PIN             GPIO_PIN_2
#define BOARD_CRSF_RX_GPIO_PORT       GPIOA
#define BOARD_CRSF_RX_PIN             GPIO_PIN_3
#define BOARD_CRSF_RX_DMA_STREAM      BOARD_CRSF_RX_DMA_STREAM_UNVERIFIED

/* USART1 PA9/PA10 comes from the ICD and hwdef. Betaflight's resource map
 * leaves these pins free; debug UART is a planned assignment for this firmware. */
#define BOARD_DEBUG_UART              USART1
#define BOARD_DEBUG_TX_GPIO_PORT      GPIOA
#define BOARD_DEBUG_TX_PIN            GPIO_PIN_9
#define BOARD_DEBUG_RX_GPIO_PORT      GPIOA
#define BOARD_DEBUG_RX_PIN            GPIO_PIN_10

/* The IMU shares SPI1 with the unused OSD. OSD CS must be driven high before
 * using SPI1; this header alone does not drive it. */
#define BOARD_IMU_SPI                 SPI1
#define BOARD_IMU_SCK_GPIO_PORT       GPIOA
#define BOARD_IMU_SCK_PIN             GPIO_PIN_5
#define BOARD_IMU_MISO_GPIO_PORT      GPIOB
#define BOARD_IMU_MISO_PIN            GPIO_PIN_4
#define BOARD_IMU_MOSI_GPIO_PORT      GPIOA
#define BOARD_IMU_MOSI_PIN            GPIO_PIN_7
#define BOARD_IMU_CS_GPIO_PORT        GPIOC
#define BOARD_IMU_CS_PIN              GPIO_PIN_14
#define BOARD_IMU_INT_GPIO_PORT       GPIOC
#define BOARD_IMU_INT_PIN             GPIO_PIN_15
#define BOARD_SPI1_RX_DMA_STREAM      DMA2_Stream0
#define BOARD_SPI1_TX_DMA_STREAM      DMA2_Stream3
/* PB12 is PREINIT 3 in Betaflight; the ICD and hwdef identify it as OSD CS. */
#define BOARD_OSD_CS_GPIO_PORT        GPIOB
#define BOARD_OSD_CS_PIN              GPIO_PIN_12

/* Betaflight resource show all assigns PC15 to GYRO_EXTI. The installed IMU
 * model and its physical axis alignment still require bench verification.
 * Referencing either pending value in C before verification fails compilation. */
#define BOARD_IMU_MODEL               BOARD_IMU_MODEL_UNVERIFIED
#define BOARD_IMU_ALIGNMENT           BOARD_IMU_ALIGNMENT_UNVERIFIED

/* Onboard blackbox flash shares SPI2 with the unused SD card. SD CS must be
 * driven high before using SPI2. */
#define BOARD_FLASH_SPI               SPI2
#define BOARD_FLASH_SCK_GPIO_PORT     GPIOB
#define BOARD_FLASH_SCK_PIN           GPIO_PIN_13
#define BOARD_FLASH_MISO_GPIO_PORT    GPIOC
#define BOARD_FLASH_MISO_PIN          GPIO_PIN_2
#define BOARD_FLASH_MOSI_GPIO_PORT    GPIOC
#define BOARD_FLASH_MOSI_PIN          GPIO_PIN_3
#define BOARD_FLASH_CS_GPIO_PORT      GPIOC
#define BOARD_FLASH_CS_PIN            GPIO_PIN_13
#define BOARD_SPI2_RX_DMA_STREAM      DMA1_Stream3
#define BOARD_SPI2_TX_DMA_STREAM      DMA1_Stream4
/* PC1 is absent from Betaflight's active resources; hwdef lists SD card CS. */
#define BOARD_SD_CS_GPIO_PORT         GPIOC
#define BOARD_SD_CS_PIN               GPIO_PIN_1

#define BOARD_BARO_I2C                I2C1
#define BOARD_BARO_SCL_GPIO_PORT      GPIOB
#define BOARD_BARO_SCL_PIN            GPIO_PIN_8
#define BOARD_BARO_SDA_GPIO_PORT      GPIOB
#define BOARD_BARO_SDA_PIN            GPIO_PIN_7

#define BOARD_VBAT_GPIO_PORT          GPIOC
#define BOARD_VBAT_PIN                GPIO_PIN_4
#define BOARD_VBAT_ADC_CHANNEL        ADC_CHANNEL_14
#define BOARD_CURRENT_GPIO_PORT       GPIOC
#define BOARD_CURRENT_PIN             GPIO_PIN_5
#define BOARD_CURRENT_ADC_CHANNEL     ADC_CHANNEL_15
#define BOARD_ADC1_DMA_STREAM         DMA2_Stream4
/* RSSI is not an active Betaflight resource; the ICD and hwdef list PB0. */
#define BOARD_RSSI_GPIO_PORT          GPIOB
#define BOARD_RSSI_PIN                GPIO_PIN_0
#define BOARD_RSSI_ADC_CHANNEL        ADC_CHANNEL_8
#define BOARD_AIRSPEED_GPIO_PORT      GPIOC
#define BOARD_AIRSPEED_PIN            GPIO_PIN_0
#define BOARD_AIRSPEED_ADC_CHANNEL    ADC_CHANNEL_10

/* VERIFY BEFORE USE: current scaling depends on the external ESC sensor.
 * ArduPilot's default is not a measurement of this project's ESC. */
#define BOARD_CURRENT_AMPS_PER_VOLT   BOARD_CURRENT_AMPS_PER_VOLT_UNVERIFIED

#define BOARD_BUZZER_GPIO_PORT        GPIOB
#define BOARD_BUZZER_PIN              GPIO_PIN_9
/* TIM11_CH1 comes from hwdef; resource show all only labels PB9 BEEPER. */
#define BOARD_BUZZER_TIMER            TIM11
#define BOARD_BUZZER_TIMER_CHANNEL    TIM_CHANNEL_1
#define BOARD_LED_STRIP_GPIO_PORT     GPIOB
#define BOARD_LED_STRIP_PIN           GPIO_PIN_1
#define BOARD_LED_STRIP_TIMER         TIM3
#define BOARD_LED_STRIP_TIMER_CHANNEL TIM_CHANNEL_4
#define BOARD_LED_STRIP_DMA_STREAM    DMA1_Stream2

#define BOARD_PINIO1_GPIO_PORT        GPIOA
#define BOARD_PINIO1_PIN              GPIO_PIN_4
#define BOARD_PINIO2_GPIO_PORT        GPIOB
#define BOARD_PINIO2_PIN              GPIO_PIN_5

#define BOARD_USB_DM_GPIO_PORT        GPIOA
#define BOARD_USB_DM_PIN              GPIO_PIN_11
#define BOARD_USB_DP_GPIO_PORT        GPIOA
#define BOARD_USB_DP_PIN              GPIO_PIN_12

#endif /* BOARD_H */
