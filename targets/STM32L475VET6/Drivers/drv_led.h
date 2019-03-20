#ifndef __DRV_LED_H__
#define __DRV_LED_H__

#include "sys.h"

#define PIN_LED_R            GPIO_PIN_7
#define PIN_LED_G            GPIO_PIN_8
#define PIN_LED_B            GPIO_PIN_9
#define PIN_LED_MASK         (PIN_LED_R | PIN_LED_G | PIN_LED_B)

#define led_r_on()			 HAL_GPIO_WritePin(GPIOE, PIN_LED_R,GPIO_PIN_RESET)
#define led_r_off()          HAL_GPIO_WritePin(GPIOE, PIN_LED_R,GPIO_PIN_SET)
#define led_r_state_toggle   HAL_GPIO_TogglePin(GPIOE, PIN_LED_R)

#define led_g_on()			 HAL_GPIO_WritePin(GPIOE, PIN_LED_G,GPIO_PIN_RESET)
#define led_g_off()          HAL_GPIO_WritePin(GPIOE, PIN_LED_G,GPIO_PIN_SET)
#define led_g_state_toggle   HAL_GPIO_TogglePin(GPIOE, PIN_LED_G)

#define led_b_on()			 HAL_GPIO_WritePin(GPIOE, PIN_LED_B,GPIO_PIN_RESET)
#define led_b_off()          HAL_GPIO_WritePin(GPIOE, PIN_LED_B,GPIO_PIN_SET)
#define led_b_state_toggle   HAL_GPIO_TogglePin(GPIOE, PIN_LED_B)

void led_init(void);

#endif
