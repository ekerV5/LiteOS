#include "los_base.h"
#include "los_config.h"
#include "los_event.h"
#include "los_hwi.h"
#include "los_memory.h"
#include "los_queue.ph"
#include "los_sem.h"
#include "los_task.ph"
#include "los_typedef.h"

#include "test.h"

//#define KEY_TEST_ENABLE
//#define LED_TEST_ENABLE

/* KEY 测试代码 */
#ifdef KEY_TEST_ENABLE
#include "drv_key.h"

static void key_process(void)
{
    printf("Key pressed.\r\n");
    __HAL_GPIO_EXTI_CLEAR_IT(PIN_KEY_0);
    __HAL_GPIO_EXTI_CLEAR_IT(PIN_KEY_1);
    __HAL_GPIO_EXTI_CLEAR_IT(PIN_KEY_2);
    __HAL_GPIO_EXTI_CLEAR_IT(PIN_KEY_WKUP);
}

static UINT32 key_irq_init(void)
{
    UINTPTR uvIntSave;
    
    printf("Key irq init.\r\n");
    
    uvIntSave = LOS_IntLock();
    
    key_init();
    
    //注册中断处理函数
    LOS_HwiCreate(EXTI9_5_IRQn, 2, 0, key_process, 0);
    LOS_HwiCreate(EXTI15_10_IRQn, 2, 0, key_process, 0);
    
    LOS_IntRestore(uvIntSave);
    
    return LOS_OK;
}
#endif

/* LED 测试代码 */
#ifdef LED_TEST_ENABLE
#include "drv_led.h"

static UINT32 task_led_handler;

static void task_led(void)
{
    while(1)
    {
        led_r_on();
        LOS_TaskDelay(1 * LOSCFG_BASE_CORE_TICK_PER_SECOND);
        led_r_off();
        led_g_on();
        LOS_TaskDelay(1 * LOSCFG_BASE_CORE_TICK_PER_SECOND);
        led_g_off();
        led_b_on();
        LOS_TaskDelay(1 * LOSCFG_BASE_CORE_TICK_PER_SECOND);
        led_b_off();
    }
}

static UINT32 task_led_create(void)
{
    UINT32 ret;
    TSK_INIT_PARAM_S initParam;

    initParam.pfnTaskEntry = (TSK_ENTRY_FUNC)task_led;
    initParam.usTaskPrio = 4;
    initParam.pcName = "TASK LED";
    initParam.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
    //initParam.uwResved   = LOS_TASK_STATUS_DETACHED;
    
    ret = LOS_TaskCreate(&task_led_handler, &initParam);
    if (ret != LOS_OK)
    {
        printf("Task led create Failed!\r\n");
        return LOS_NOK;
    }
    printf("Task led create success.\r\n");
    
    return LOS_OK;
}
#endif

#ifdef APP_TEST_ENABLE
UINT32 app_test_init(void)
{
    UINT32 ret = LOS_OK;

#ifdef KEY_TEST_ENABLE
    key_irq_init();
#endif

#ifdef LED_TEST_ENABLE    
    ret = task_led_create();
    if(ret != LOS_OK)
    {
        return LOS_NOK;
    }
#endif
    
    return ret;
}
#else
UINT32 app_test_init(void)
{
    return LOS_OK;
}
#endif
