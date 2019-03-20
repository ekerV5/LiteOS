#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "los_base.h"
#include "los_config.h"
#include "los_event.h"
#include "los_hwi.h"
#include "los_memory.h"
#include "los_queue.ph"
#include "los_sem.h"
#include "los_task.ph"
#include "los_typedef.h"

#include "delay.h"
#include "sys.h"
#include "usart.h"

/**
 * @brief 硬件初始化，LiteOS内核初始化之前调用。
 *
 * @param   void
 *
 * @return  void
 */
static void hardware_init(void)
{
    SystemClock_Config(); //时钟初始化
    uart_init(115200);    //串口初始化
    printf("Hardware init end.\n");
}

/**
 * @brief 应用初始化，创建LiteOS任务等
 *
 * @param void
 *
 * @return UINT32 初始化成功返回LOS_OK
 */
static UINT32 app_init(void)
{
    printf("Application init.\n");
    
    return LOS_OK;
}

/**
 * @brief 主函数，即程序的入口
 *
 * @param void
 *
 * @return int
 */
int main(void)
{
    UINT32 ret = LOS_OK;

    hardware_init();

    ret = LOS_KernelInit();
    if (ret != LOS_OK)
    {
        return LOS_NOK;
    }

    app_init();

    LOS_Start();
}
