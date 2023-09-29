#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Function prototypes */
void vPrintString(const char *str);
void vPrintStringAndNumber(const char *str, int32_t num);
void vTaskStartScheduler(void);

void vContinuousProcessingTask( void *pvParameters )
{
char *pcTaskName;
 /* The string to print out is passed in via the parameter. Cast this to a
 character pointer. */
 pcTaskName = ( char * ) pvParameters;
 /* As per most tasks, this task is implemented in an infinite loop. */
 for( ;; )
 {
 /* Print out the name of this task. This task just does this repeatedly
 without ever blocking or delaying. */
 vPrintString( pcTaskName );
 }
}
void vPeriodicTask( void *pvParameters )
{
TickType_t xLastWakeTime;
const TickType_t xDelay3ms = pdMS_TO_TICKS( 3 );
 /* The xLastWakeTime variable needs to be initialized with the current tick
 count. Note that this is the only time the variable is explicitly written to.
 After this xLastWakeTime is managed automatically by the vTaskDelayUntil()
 API function. */
 xLastWakeTime = xTaskGetTickCount();
 /* As per most tasks, this task is implemented in an infinite loop. */
 for( ;; )
 {
 /* Print out the name of this task. */
 vPrintString( "Periodic task is running\r\n" );
 /* The task should execute every 3 milliseconds exactly � see the
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
