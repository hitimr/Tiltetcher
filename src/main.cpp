#include "timer.h"
#include <thermal_sensor.h>

#define BLOCKING_TIME_MS 10000L

void setup()
{
  init_timer();	
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  while (!Serial)
  {
  }

  Serial.print(F("\nStarting ISR_16_Timers_Array_Complex on "));
  Serial.println(BOARD_TYPE);
  Serial.println(TIMER_INTERRUPT_VERSION);
  Serial.println(TIMER_INTERRUPT_GENERIC_VERSION);
  Serial.print(F("CPU Frequency = "));
  Serial.print(F_CPU / 1000000);
  Serial.println(F(" MHz"));
}

void loop()
{
  // This unadvised blocking task is used to demonstrate the blocking effects onto the execution and
  // accuracy to Software timer You see the time elapse of ISR_Timer still accurate, whereas very
  // inaccurate for Software Timer The time elapse for 2000ms software timer now becomes 3000ms
  // (BLOCKING_TIME_MS) While that of ISR_Timer is still prefect.
  Serial.println(thermal_sensor.get_temperature());

  // You need this Software timer for non-critical tasks. Avoid abusing ISR if not absolutely
  // necessary You don't need to and never call ISR_Timer.run() here in the loop(). It's already
  // handled by ISR timer.
}
