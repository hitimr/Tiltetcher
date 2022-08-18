#include "project.h"
#include "timer.h"
#include "thermal_sensor.h"
#include "lcd.h"

void setup()
{
  display.init();
  init_heater();

#ifdef STEPPER_MOTOR_ENABLED
  init_motor();
#endif
  

  Serial.begin(SERIAL_BAUD_RATE);
  while (!Serial)
  {
  }

  while (millis() < WARMUP_TIME_MS)
  {
    Serial.println("Warming up...");
  }

  init_timer();

  LOG_PRINT(LOG_LEVEL_INFO, "Init complete");
}


void loop()
{
  // This unadvised blocking task is used to demonstrate the blocking effects onto the execution and
  // accuracy to Software timer You see the time elapse of ISR_Timer still accurate, whereas very
  // inaccurate for Software Timer The time elapse for 2000ms software timer now becomes 3000ms
  // (BLOCKING_TIME_MS) While that of ISR_Timer is still prefect.

  // You need this Software timer for non-critical tasks. Avoid abusing ISR if not absolutely
  // necessary You don't need to and never call ISR_Timer.run() here in the loop(). It's already
  // handled by ISR timer.

}
