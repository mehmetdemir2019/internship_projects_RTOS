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
void vTask1( void *pvParameters )
{
const char *pcTaskName = "Task 1 is running\r\n";
volatile uint32_t ul; /* volatile to ensure ul is not optimized away. */
 /* As per most tasks, this task is implemented in an infinite loop. */
 for( ;; )
 {
 /* Print out the name of this task. */
 vPrintString( pcTaskName );
 /* Delay for a period. */
 for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
 {
 /* This loop is just a very crude delay implementation. There is
 nothing to do in here. Later examples will replace this crude
 loop with a proper delay/sleep function. */
 }
 }
}

/* Receiver task */
void vTask2( void *pvParameters )
{
const char *pcTaskName = "Task 2 is running\r\n";
volatile uint32_t ul; /* volatile to ensure ul is not optimized away. */
 /* As per most tasks, this task is implemented in an infinite loop. */
 for( ;; )
 {
 /* Print out the name of this task. */
 vPrintString( pcTaskName );
 /* Delay for a period. */
 for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
 {
 /* This loop is just a very crude delay implementation. There is
 nothing to do in here. Later examples will replace this crude
 loop with a proper delay/sleep function. */
 }
 }
}


int main( void )
{
 /* Create one of the two tasks. Note that a real application should check
 the return value of the xTaskCreate() call to ensure the task was created
 successfully. */
 xTaskCreate( vTask1, /* Pointer to the function that implements the task. */
 "Task 1",/* Text name for the task. This is to facilitate
 debugging only. */
 1000, /* Stack depth - small microcontrollers will use much
 less stack than this. */
 NULL, /* This example does not use the task parameter. */
 1, /* This task will run at priority 1. */
 NULL ); /* This example does not use the task handle. */
 /* Create the other task in exactly the same way and at the same priority. */
 xTaskCreate( vTask2, "Task 2", 1000, NULL, 1, NULL );
 /* Start the scheduler so the tasks start executing. */
 vTaskStartScheduler();

 /* If all is well then main() will never reach here as the scheduler will
 now be running the tasks. If main() does reach here then it is likely that
 there was insufficient heap memory available for the idle task to be created.
 Chapter 2 provides more information on heap memory management. */
 for( ;; );
}

