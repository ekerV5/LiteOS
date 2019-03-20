#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "sys.h"

#define PIN_KEY_0           GPIO_PIN_10
#define PIN_KEY_1           GPIO_PIN_9
#define PIN_KEY_2           GPIO_PIN_8
#define PIN_KEY_WKUP        GPIO_PIN_13

#define PIN_KEY_MASK        (PIN_KEY_0 | PIN_KEY_1 | PIN_KEY_2)

void key_init(void);

#endif
