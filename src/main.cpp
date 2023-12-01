#include <Arduino.h>
#include "motorDriver.h"

void taskOne( void * parameter);
void taskTwo( void * parameter);
#define LED_BOARD 2 //change here the pin of the board to V2

void setup(){
  pinMode(LED_BOARD, OUTPUT);
  Serial.begin(9600);
  Serial.println("HI there"); // already wrote this
  delay(1000);
  xTaskCreate(
                    taskOne,          /* Task function. */
                    "TaskOne",        /* String with name of task. */
                    1024,              /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */

  xTaskCreate(
                    taskTwo,          /* Task function. */
                    "TaskTwo",        /* String with name of task. */
                    1024,              /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */    
  motorobject.SETUP();                
}

void loop(){
  motorobject.set_speed(MotorA, Forward, 255);
  motorobject.set_speed(MotorB, Forward, 255);
  delay(5000);

  motorobject.set_speed(MotorA, Forward, 0);
  motorobject.set_speed(MotorB, Forward, 0);
  delay(1000);

  motorobject.set_speed(MotorA, Backward, 255);
  motorobject.set_speed(MotorB, Backward, 255);
  delay(5000);

  motorobject.set_speed(MotorA, Backward, 0);
  motorobject.set_speed(MotorB, Backward, 0);
  delay(1000);
}

void taskOne( void * parameter )
{
    //example of a task that executes for some time and then is deleted
    for( int i = 0; i < 10; i++ )
    {
      Serial.println("Hello from task 1");
      
      // If we need to 
      //Switch on the LED
      digitalWrite(LED_BOARD, HIGH); 
      // Pause the task for 1000ms
      //delay(1000); //This delay doesn't give a chance to the other tasks to execute
      vTaskDelay(1000 / portTICK_PERIOD_MS); //this pauses the task, so others can execute
      // Switch off the LED
      digitalWrite(LED_BOARD, LOW);
      // Pause the task again for 500ms
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    Serial.println("Ending task: 1");
    vTaskDelete( NULL );
}
 
void taskTwo( void * parameter)
{
    //create an endless loop so the task executes forever
    for(;;)
    {
        Serial.println("Hello from task: 2");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    Serial.println("Ending task 2"); //should not reach this point but in case...
    vTaskDelete( NULL );
}
