#include "sys.h"


/*********************************************************************************
 * ϵͳʱ�ӳ�ʼ��
 * ����ʱ������/�жϹ���/GPIO���õ�
 *********************************************************************************/


/**
 * @brief ʱ��ϵͳ���ú���
 *
 * @remark SYSCLK = HSE / PLLM * PLLN / PLLR
 *         SYSCLK = 8M  / 1 * 20 / 2 = 80M
 *
 * @param void
 *
 * @return void
 */
void SystemClock_Config(void)
{
    HAL_StatusTypeDef	ret = HAL_OK;

    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    __HAL_RCC_PWR_CLK_ENABLE(); //ʹ��PWRʱ��

    /*Initializes the CPU, AHB and APB busses clocks*/
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 1;
    RCC_OscInitStruct.PLL.PLLN = 20;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;

    ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);

    if(ret != HAL_OK)	while(1);

    /*Initializes the CPU, AHB and APB busses clocks*/
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;


    ret	= HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);

    if(ret != HAL_OK)	while(1);

    /*Configure the main internal regulator output voltage*/
    ret = HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

    if(ret != HAL_OK)	while(1);
}

/**
 * @brief THUMBָ�֧�ֻ��������
 *        �������·���ʵ��ִ�л��ָ��WFI 
 *
 * @param void
 *
 * @return __asm
 */
__asm void WFI_SET(void)
{
	WFI;		  
}

/**
 * @brief �ر������ж�(���ǲ�����fault��NMI�ж�)
 *
 * @param void
 *
 * @return __asm
 */
__asm void INTX_DISABLE(void)
{
	CPSID I
	BX LR	  
}

/**
 * @brief ���������ж�
 *
 * @param void
 *
 * @return __asm
 */
__asm void INTX_ENABLE(void)
{
	CPSIE I
	BX LR  
}

/**
 * @brief ����ջ����ַ
 *
 * @param addr ջ����ַ
 *
 * @return __asm
 */
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 //set Main Stack value
	BX r14
}
