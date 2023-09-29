#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Function prototypes */
void vPrintString(const char *str);
void vPrintStringAndNumber(const char *str, int32_t num);
void vTaskStartScheduler(void);

#include "FreeRTOS.h"
#include "os_queue.h"
#include "os_task.h"

QueueHandle_t xQueue;

/* Sender task */
void vTaskFunction( void *pvParameters )
{
char *pcTaskName;
TickType_t xLastWakeTime;
 pcTaskName = ( char * ) pvParameters;
 xLastWakeTime = xTaskGetTickCount();
 /* As per most tasks, this task is implemented in an infinite loop. */
 for( ;; )
 {
 vPrintString( pcTaskName );
 vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( 250 ) );
 }
}

void vTaskFunction( void *pvParameters )
{
char *pcTaskName;
const TickType_t xDelay250ms = pdMS_TO_TICKS( 250 );
 /* The string to print out is passed in via the parameter. Cast this to a
 character pointer. */
 pcTaskName = ( char * ) pvParameters;
 /* As per most tasks, this task is implemented in an infinite loop. */
 for( ;; )
 {
 /* Print out the name of this task. */
 vPrintString( pcTaskName );
 vTaskDelay( xDelay250ms );
 }
}
