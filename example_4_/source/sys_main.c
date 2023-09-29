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
volatile uint32_t ul; /* volatile to ensure ul is not optimized away. */
 /* The string to print out is passed in via the parameter. Cast this to a
 character pointer. */
 pcTaskName = ( char * ) pvParameters;
 /* As per most tasks, this task is implemented in an infinite loop. */
 for( ;; )
 {
 /* Print out the name of this task. */
 vPrintString( pcTaskName );
 /* Delay for a period. */
 for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
 {
 /* This loop is just a very crude delay implementation. There is
 nothing to do in here. Later exercises will replace this crude
 loop with a proper delay/sleep function. */
 }
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
