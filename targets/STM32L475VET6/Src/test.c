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

//#define LED_TEST_ENABLE

/* LED ≤‚ ‘¥˙¬Î */
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
