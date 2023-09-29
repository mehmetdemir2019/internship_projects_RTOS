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
/* Define the strings that will be passed in as the task parameters. These are
defined const and not on the stack to ensure they remain valid when the tasks are
executing. */
static const char *pcTextForTask1 = "Task 1 is running\r\n";
static const char *pcTextForTask2 = "Task 2 is running\r\n";
int main( void )
{
 /* Create one of the two tasks. */
 xTaskCreate( vTaskFunction, /* Pointer to the function that
 implements the task. */
 "Task 1", /* Text name for the task. This is to
 facilitate debugging only. */
 1000, /* Stack depth - small microcontrollers
 will use much less stack than this. */
 (void*)pcTextForTask1, /* Pass the text to be printed into the
 task using the task parameter. */
 1, /* This task will run at priority 1. */
NULL ); /* The task handle is not used in this
 example. */
 /* Create the other task in exactly the same way. Note this time that multiple
 tasks are being created from the SAME task implementation (vTaskFunction). Only
 the value passed in the parameter is different. Two instances of the same
 task are being created. */
 xTaskCreate( vTaskFunction, "Task 2", 1000, (void*)pcTextForTask2, 1, NULL );
 /* Start the scheduler so the tasks start executing. */
 vTaskStartScheduler();

 /* If all is well then main() will never reach here as the scheduler will
 now be running the tasks. If main() does reach here then it is likely that
 there was insufficient heap memory available for the idle task to be created.
 Chapter 2 provides more information on heap memory management. */
 for( ;; );
