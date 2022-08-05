#pragma once
#include "GPIO.h"
#include "project.h"
#include "thermal_sensor.h"

#include <assert.h>

#define HEATER_TEMP_CUTOFF_HIGH 45
#define HEATER_TEMP_CUTOFF_LOW 42

#define HEATER_STATE_OFF 0
#define HEATER_STATE_ON 1

int set_heater(int state)
{
  assert(state == ON || state == OFF);

  static int last_state = OFF;

  if (state != last_state)
  {
    if (state == ON)
    {
      LOG_PRINT(LOG_LEVEL_DEBUG, "Switching heater ON");
    }
    else
    {
      LOG_PRINT(LOG_LEVEL_DEBUG, "Switching heater OFF");
    }
  }

  digitalWrite(PIN_HEATER, state);
  digitalWrite(PIN_HEATER_LED, state);
  last_state = state;

  return SUCCESS;
}

void init_heater()
{
  pinMode(PIN_HEATER, OUTPUT);
  pinMode(PIN_HEATER_LED, OUTPUT);
}

void heater_routine()
{
  LOG_PRINT(LOG_LEVEL_DEBUG, "Heater routine");
  double temperature = thermal_sensor.get_temperature();
  LOG_PRINT(LOG_LEVEL_DEBUG, temperature);

  if (!thermal_sensor.is_valid())
  {
    LOG_PRINT(LOG_LEVEL_WARN, "Invalid measurement");
    set_heater(OFF);
    return;
  }

  // Switch OFF if temperature is too high
  if (temperature > HEATER_TEMP_CUTOFF_HIGH)
  {
    set_heater(OFF);
    return;
  }

  // Switch ON if temperature is too low
  if (temperature < HEATER_TEMP_CUTOFF_LOW)
  {
    set_heater(ON);
  }
}

/*
// Check if we need to switch on the Heater
// This routine should only be called once every second to avoid excessive switching of the relay
void heater_switch_on_routine()
{
  static unsigned long last_switch_on_time = 0;

  LOG_PRINT(LOG_LEVEL_DEBUG, "heater_switch_on_routine()");

  int heater_status = heater_safety_check();
  LOG_PRINT(LOG_LEVEL_DEBUG, thermal_sensor.get_temperature());

  // Check for Errors
  switch (heater_status)
  {
  case HEATER_ERROR_TEMPERATURE_INVALID:
    LOG_PRINT(LOG_LEVEL_ERROR, "Heater temperature is invalid");
    return;
  }

  if (heater_status == HEATER_ERROR_TEMPERATURE_TOO_HIGH)
  {
    LOG_PRINT(LOG_LEVEL_DEBUG, "Heater is too high");
    return;
  }

  if ((millis() - last_switch_on_time) < MINIMUM_OFF_TIME_MS)
  {
    // heater was switched off too recently
    LOG_PRINT(LOG_LEVEL_DEBUG, "Heater was switched on too recently");
    return;
  }

  // Only switch ON if temperature is below the cutoff
  if ((heater_status == HEATER_SAFE) && (thermal_sensor.get_temperature() < HEATER_TEMP_CUTOFF_LOW))
  {
    LOG_PRINT(LOG_LEVEL_DEBUG, "Switching heater ON");
    LOG_PRINT(LOG_LEVEL_DEBUG, thermal_sensor.get_temperature());

    set_heater(ON);
    last_switch_on_time = millis();
  }
}

*/
