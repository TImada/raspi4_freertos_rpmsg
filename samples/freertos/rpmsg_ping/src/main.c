#include <stddef.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "uart.h"

/* External functions */
void TaskRPMSG(void *pvParameters);

/* 
 * Prototypes for the standard FreeRTOS callback/hook functions implemented
 * within this file.
 */
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );

/*-----------------------------------------------------------*/

void main(void)
{
    TaskHandle_t task_rpmsg;

    uart_init();
    uart_puts("\r\n****************************\r\n");
    uart_puts("\r\n   FreeRTOS RPMSG Sample\r\n");
    uart_puts("\r\n  (This sample uses UART2)\r\n");
    uart_puts("\r\n****************************\r\n");

    xTaskCreate(TaskRPMSG, "Task RPMSG", 512, NULL, 0x10, &task_rpmsg);

    vTaskStartScheduler();
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
}

/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
}
