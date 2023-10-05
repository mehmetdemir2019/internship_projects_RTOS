#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Function prototypes */
void vPrintString(const char *str);
void vPrintStringAndNumber(const char *str, int32_t num);
void vTaskStartScheduler(void);

void vTaskFunction( void *pvParameters )
{
char *pcTaskName;
const TickType_t xDelay250ms = pdMS_TO_TICKS( 250 );
 pcTaskName = ( char * ) pvParameters;
 for( ;; )
 {
 vPrintStringAndNumber( pcTaskName, ulIdleCycleCount );
 /* Delay for a period of 250 milliseconds. */
 vTaskDelay( xDelay250ms );
 }
}

void vPeriodicTask( void *pvParameters )
{
TickType_t xLastWakeTime;
const TickType_t xDelay3ms = pdMS_TO_TICKS( 3 );
 xLastWakeTime = xTaskGetTickCount();
 /* As per most tasks, this task is implemented in an infinite loop. */
 for( ;; )
 {
 /* Print out the name of this task. */
 vPrintString( "Periodic task is running\r\n" );
 /* The task should execute every 3 milliseconds exactly – see the
 declaration of xDelay3ms in this function. */
 vTaskDelayUntil( &xLastWakeTime, xDelay3ms );
 }
}

int main(void)
{
    /* Initialize FreeRTOS */
    vTaskStartScheduler();

    /* Create the tasks */
    xTaskCreate(vContinuousProcessingTask, "ContinuousTask", configMINIMAL_STACK_SIZE, "Continuous task is running\r\n", tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(vPeriodicTask, "PeriodicTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);

    /* Start the scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    while (true)
    {
    }

    return 0;
}
