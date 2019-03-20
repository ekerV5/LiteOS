#include "drv_key.h"

/**
 * @brief   外部中断初始化
 *
 * @param   void
 *
 * @return  void
 */
void key_init(void)
{
    /*
        KEY0 	- PD10
        KEY1 	- PD9
        KEY2 	- PD8
        WK_UP 	- PC13
    */
    GPIO_InitTypeDef initParam;
    
    __HAL_RCC_GPIOC_CLK_ENABLE();                  //开启GPIOC时钟
    __HAL_RCC_GPIOD_CLK_ENABLE();                  //开启GPIOD时钟
    
    initParam.Pin = PIN_KEY_MASK;                  //PD8.9.10
    initParam.Mode = GPIO_MODE_IT_FALLING;         //下降沿触发GPIO_MODE_IT_FALLING
    initParam.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOD, &initParam);
	
    initParam.Pin = PIN_KEY_WKUP;                  //PC13
    initParam.Mode = GPIO_MODE_IT_RISING;          //上升沿触发
    initParam.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOC, &initParam);
    
    //中断线8,9
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);      //抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);              //使能中断线

    //中断线10,13
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 1);    //抢占优先级为2，子优先级为1
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);            //使能中断线
}
