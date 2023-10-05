#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Function prototypes */
void vPrintString(const char *str);
void vPrintStringAndNumber(const char *str, int32_t num);
void vTaskStartScheduler(void);

void vTask1( void *pvParameters )
{
UBaseType_t uxPriority;
 uxPriority = uxTaskPriorityGet( NULL );
 for( ;; )
 {
 /* Print out the name of this task. */
 vPrintString( "Task 1 is running\r\n" );
 vPrintString( "About to raise the Task 2 priority\r\n" );
 vTaskPrioritySet( xTask2Handle, ( uxPriority + 1 ) );
 }
}




void vTask2( void *pvParameters )
{
UBaseType_t uxPriority;
 uxPriority = uxTaskPriorityGet( NULL );

 for( ;; )
 {
 vPrintString( "Task 2 is running\r\n" );
 vPrintString( "About to lower the Task 2 priority\r\n" );
 vTaskPrioritySet( NULL, ( uxPriority - 2 ) );
 }
}

TaskHandle_t xTask2Handle = NULL;
int main( void )
{
 and set to NULL. The task handle is also not used so is also set to NULL. */
 xTaskCreate( vTask1, "Task 1", 1000, NULL, 2, NULL );
 xTaskCreate( vTask2, "Task 2", 1000, NULL, 1, &xTask2Handle );

 for( ;; );
}
