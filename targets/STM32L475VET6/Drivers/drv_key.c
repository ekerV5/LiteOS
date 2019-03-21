#include "drv_key.h"

/**
 * @brief   �ⲿ�жϳ�ʼ��
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
    
    __HAL_RCC_GPIOC_CLK_ENABLE();                  //����GPIOCʱ��
    __HAL_RCC_GPIOD_CLK_ENABLE();                  //����GPIODʱ��
    
    initParam.Pin = PIN_KEY_MASK;                  //PD8.9.10
    initParam.Mode = GPIO_MODE_IT_FALLING;         //�½��ش���GPIO_MODE_IT_FALLING
    initParam.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOD, &initParam);
	
    initParam.Pin = PIN_KEY_WKUP;                  //PC13
    initParam.Mode = GPIO_MODE_IT_RISING;          //�����ش���
    initParam.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOC, &initParam);
    
    //�ж���8,9
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);      //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);              //ʹ���ж���

    //�ж���10,13
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 1);    //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);            //ʹ���ж���
}
