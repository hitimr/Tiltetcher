#pragma once
#include "GPIO.h"
#include "project.h"
#include "thermal_sensor.h"

#include <assert.h>

#define HEATER_TEMP_CUTOFF_HIGH 30
#define HEATER_TEMP_CUTOFF_LOW 28
#define HEATER_UNSAFE 1
#define HEATER_SAFE 0

int set_heater(int state)
{
  assert(state == ON || state == OFF);

  digitalWrite(PIN_HEATER, state);
  digitalWrite(PIN_HEATER_LED, state);

  return SUCCESS;
}

void init_heater()
{
  pinMode(PIN_HEATER, OUTPUT);
  pinMode(PIN_HEATER_LED, OUTPUT);
}

// Check if we need to switch OFF the heater
// This routine should be called every time the temperature is read
int heater_safety_check()
{
  // Measured temperature is not valid
  if (!thermal_sensor.is_valid())
  {
    set_heater(OFF);
    return HEATER_UNSAFE;
  }

  // Temperature is too high
  if (thermal_sensor.get_temperature() > HEATER_TEMP_CUTOFF_HIGH)
  {
    set_heater(OFF);
    return HEATER_UNSAFE;
  }

  // All checks passed. HEater can be turned ON
  return HEATER_SAFE;
}

// Check if we need to switch on the Heater
// This routine should only be called once every second to avoid excessive switching of the relay
void heater_switch_on_routine()
{
  LOG_PRINT(LOG_LEVEL_DEBUG, "heater_switch_on_routine()");

  int heater_status = heater_safety_check();
  if (heater_status == HEATER_UNSAFE)
  {
    LOG_PRINT(LOG_LEVEL_DEBUG, "Heater is UNSAFE()");
    return;
  }

  // Only switch ON if temperature is below the cutoff
  if (thermal_sensor.get_temperature() < HEATER_TEMP_CUTOFF_LOW)
  {
    LOG_PRINT(LOG_LEVEL_DEBUG, "Switching heater ON");
    set_heater(ON);
  }
}
