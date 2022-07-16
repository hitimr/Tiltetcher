#pragma once
#include "project.h"
#include "GPIO.h"

#define TEMP_CUTOFF_HIGH 45
#define TEMP_CUTOFF_LOW 42

void init_heater()
{
  pinMode(PIN_HEATER, OUTPUT);
  pinMode(PIN_HEATER_LED, OUTPUT);
}

void set_heater(int state)
{
  assert(state == ON || state == OFF);

  digitalWrite(PIN_HEATER, state);
  digitalWrite(PIN_HEATER_LED, state);
}