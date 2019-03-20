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
 * @brief Ӳ����ʼ����LiteOS�ں˳�ʼ��֮ǰ���á�
 *
 * @param   void
 *
 * @return  void
 */
static void hardware_init(void)
{
    SystemClock_Config(); //ʱ�ӳ�ʼ��
    uart_init(115200);    //���ڳ�ʼ��
    printf("Hardware init end.\n");
}

/**
 * @brief Ӧ�ó�ʼ��������LiteOS�����
 *
 * @param void
 *
 * @return UINT32 ��ʼ���ɹ�����LOS_OK
 */
static UINT32 app_init(void)
{
    printf("Application init.\n");
    
    return LOS_OK;
}

/**
 * @brief ������������������
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
